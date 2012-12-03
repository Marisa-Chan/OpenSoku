#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

float atan2_deg(float h, float w);
float cos_deg(float angl);
float sin_deg(float angl);
void euler_mult(float x1, float y1, float z1, float x2, float y2, float z2, float &rx,float &ry,float &rz);
char * TrimLeft(char *buf);
char * TrimRight(char *buf);
#endif
