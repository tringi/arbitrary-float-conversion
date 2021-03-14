#ifndef FLTCVT_TCC
#define FLTCVT_TCC

#include <cstdint>
#include <cstring>

namespace fltcvt_implementation {
    template <typename T, unsigned W>
    constexpr T mask = (T{1} << W) - 1;

    // fast (masking? direct?)
    //  - uses native 64-bit integer type to perform all the bit shifting
    //
    template <unsigned IN, unsigned IE, unsigned ON, unsigned OE, typename T>
    void fast (T input, T & output);
}

template <unsigned IN, unsigned IE, unsigned ON, unsigned OE>
void fltcvt (const void * input, void * output) {
    static_assert (IN > 3);
    static_assert (IE > 1);
    static_assert (ON > 3);
    static_assert (OE > 1);
    static_assert (IN > IE, "`IN` represents total bits in the input variable, `IE` just the part of exponent");
    static_assert (ON > OE, "`ON` represents total bits in the output variable, `OE` just the part of exponent");

    using fast_type = std::int64_t;
    if constexpr ((IN <= 8 * sizeof (fast_type))
               && (ON <= 8 * sizeof (fast_type))) {

        fast_type in {};
        fast_type out {};

        std::memcpy (&in, input, (IN + 7) / 8);
        fltcvt_implementation::fast <IN,IE,ON,OE> (in, out);
        std::memcpy (output, &out, (ON + 7) / 8);

    } else {
        static_assert (false, "only 64-bit or smaller types are support in this version");
    }
}

template <unsigned IN, unsigned IE, unsigned ON, unsigned OE, typename T>
void fltcvt_implementation::fast (T input, T & output) {

    // mantissa widths
    constexpr auto IM = IN - IE - 1;
    constexpr auto OM = ON - OE - 1;

    // extract sign bit
    T sign = (input & (T (1) << (IN - 1)));

    // adjust position
    if constexpr (IN > ON) {
        sign >>= IN - ON;
    } else {
        sign <<= ON - IN;
    }

    // extract exponent
    T exponent = (input >> IM) & mask <T, IE>;

    // adjust zero
    exponent -= mask <T, IE - 1> - mask <T, OE - 1>;

    // extract mantissa
    T mantissa = input & mask <T, IM>;

    // adjust precission
    if constexpr (IM > OM) {
        mantissa >>= IM - OM;
    } else {
        mantissa <<= OM - IM;
    }

    // TODO: fix inf
    // TODO: fix nan
    // TODO: fix denormals

    output = sign | (exponent << (ON - OE - 1)) | mantissa;
}

#endif
