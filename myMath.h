#ifndef MYMATH_H_INCLUDED
#define MYMATH_H_INCLUDED

#define M_PI 3.14159265358979323846
#define SQ_R 0.70710678118;

struct mathMains
{
    float sineLookup[1024];
    float cosLookup[1024];
};

struct mathMains mM;

float toZero(float rads)
{
    if(rads < -M_PI)
    {
        while (rads < -M_PI) rads += M_PI;
    }
    else if (rads > M_PI)
    {
        while (rads > M_PI) rads -= M_PI;
    }
    return rads;
}


#endif // MYMATH_H_INCLUDED
