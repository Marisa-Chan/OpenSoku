#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

float atan2_deg(float h, float w);
float cos_deg(float angl);
float sin_deg(float angl);
float tan_deg(float angl);
void euler_mult(float x1, float y1, float z1, float x2, float y2, float z2, float &rx,float &ry,float &rz);
char * TrimLeft(char *buf);
char * TrimRight(char *buf);

struct vec2d
{
    float x;
    float y;
};

void vec2d_hermit(vec2d *pOut, const vec2d *pV1, const vec2d *pT1, const vec2d *pV2, const vec2d *pT2, float s);
void vec2d_normolize(vec2d *pOut, const vec2d *pV);

#endif
