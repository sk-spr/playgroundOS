#pragma once
#define PI 3.14159265359
#define TAU 6.28318530718
#define E 2.71828182846
namespace math{
    //floor function
    //returns lower integer bound of the float
    int floor(float f);
    //floating point modulo function
    //returns remainder of division a/b
    float fmod(float a, float b);
    float logn(float x, int base);
    float nlog(float x);
}
