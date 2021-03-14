#ifndef FLTCVT_HPP
#define FLTCVT_HPP

// fltcvt
//  - 
//  - [I|O][N|E] - bit width of a floating point number component
//     - I - input type
//     - O - output type
//     - N - type width (sign + mantissa + exponent) in bits
//     - E - number of exponent bits
//  - input - 
//  - output - 
//
template <unsigned IN, unsigned IE,
          unsigned ON, unsigned OE>
void fltcvt (const void * in, void * out);

#include "fltcvt.tcc"
#endif
