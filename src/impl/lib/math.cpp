#include "../../intf/math.hpp"
int math::floor(float f){
    return (int) f - fmod(f, 1.0);
}
float math::fmod(float a, float b){
    return a - (b * (int)a/b);
}
float math::logn(float x, int base){
    return nlog(x) / nlog((float)base);
}
float math::nlog(float x){
    unsigned int bx = * (unsigned int *) (&x);
    unsigned int ex = bx >> 23;
    signed int t = (signed int)ex-(signed int)127;
    unsigned int s = (t < 0) ? (-t) : t;
    bx = 1065353216 | (bx & 8388607);
    x = * (float *) (&bx);
    return -1.49278+(2.11263+(-0.729104+0.10969*x)*x)*x+0.6931471806*t;
}
