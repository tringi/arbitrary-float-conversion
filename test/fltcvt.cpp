#include <cstdio>
#include "../fltcvt.hpp"

int main () {
    float f = -1.23f;
    unsigned short h = 0;
    float f2 = 0;
    
    fltcvt <32, 8, 16, 5> (&f, &h);
    fltcvt <16, 5, 32, 8> (&h, &f2);

    std::printf ("%.4f => %04X => %.4f\n", f, h, f2);

    double d = -1.23;
    double d2 = 0;
    fltcvt <64, 11, 16, 5> (&d, &h);
    fltcvt <16, 5, 64, 11> (&h, &d2);

    std::printf ("%.4f => %04X => %.4f\n", d, h, d2);
    return 0;
}
