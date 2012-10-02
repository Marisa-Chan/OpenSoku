#include <math.h>


float atan2_deg(float h, float w)
{
    return atan2(h,w) * 180.0 / 3.1415926;
}

float cos_deg(float angl)
{
    return cos(angl * 3.1415926 / 180.0) ;
}

float sin_deg(float angl)
{
    return sin(angl * 3.1415926 / 180.0);
}
