#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


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

inline void euler2matrix(float x, float y, float z, float (*m)[3])
{
    if (x != 0 && y != 0 && z != 0)
    {
        float sx = sin_deg(x);
        float cx = cos_deg(x);
        float sy = sin_deg(y);
        float cy = cos_deg(y);
        float sz = sin_deg(z);
        float cz = cos_deg(z);

        m[0][0] = cy*cz;
        m[0][1] = cy*sz;
        m[0][2] = -sy;
        m[1][0] = sx*sy*cz+cx*(-sz);
        m[1][1] = sx*sy*sz+cx*cz;
        m[1][2] = sx*cy;
        m[2][0] = cx*sy*cz+sx*sz;
        m[2][1] = cx*sy*sz+(-sx)*cz;
        m[2][2] = cx*cy;
    }
    else if (x != 0 && y != 0 && z == 0)
    {
        float sx = sin_deg(x);
        float cx = cos_deg(x);
        float sy = sin_deg(y);
        float cy = cos_deg(y);
        m[0][0] = cy;
        m[0][1] = 0;
        m[0][2] = -sy;
        m[1][0] = sx*sy;
        m[1][1] = cx;
        m[1][2] = sx*cy;
        m[2][0] = cx*sy;
        m[2][1] = -sx;
        m[2][2] = cx*cy;
    }
    else if (x != 0 && y == 0 && z != 0)
    {
        float sx = sin_deg(x);
        float cx = cos_deg(x);
        float sz = sin_deg(z);
        float cz = cos_deg(z);
        m[0][0] = cz;
        m[0][1] = sz;
        m[0][2] = 0;
        m[1][0] = cx*(-sz);
        m[1][1] = cx*cz;
        m[1][2] = sx;
        m[2][0] = sx*sz;
        m[2][1] = (-sx)*cz;
        m[2][2] = cx;
    }
    else if  (x == 0 && y != 0 && z != 0)
    {
        float sy = sin_deg(y);
        float cy = cos_deg(y);
        float sz = sin_deg(z);
        float cz = cos_deg(z);

        m[0][0] = cy*cz;
        m[0][1] = cy*sz;
        m[0][2] = -sy;
        m[1][0] = -sz;
        m[1][1] = cz;
        m[1][2] = 0;
        m[2][0] = sy*cz;
        m[2][1] = sy*sz;
        m[2][2] = cy;
    }
    else if (x == 0 && y == 0 && z != 0)
    {
        float sz = sin_deg(z);
        float cz = cos_deg(z);
        m[0][0] = cz;
        m[0][1] = sz;
        m[0][2] = 0;
        m[1][0] = -sz;
        m[1][1] = cz;
        m[1][2] = 0;
        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 1;
    }
    else if (x == 0 && y != 0 && z == 0)
    {
        float sy = sin_deg(y);
        float cy = cos_deg(y);
        m[0][0] = cy;
        m[0][1] = 0;
        m[0][2] = -sy;
        m[1][0] = 0;
        m[1][1] = 1;
        m[1][2] = 0;
        m[2][0] = sy;
        m[2][1] = 0;
        m[2][2] = cy;
    }
    else if (x != 0 && y == 0 && z == 0)
    {
        float sx = sin_deg(x);
        float cx = cos_deg(x);
        m[0][0] = 1;
        m[0][1] = 0;
        m[0][2] = 0;
        m[1][0] = 0;
        m[1][1] = cx;
        m[1][2] = sx;
        m[2][0] = 0;
        m[2][1] = -sx;
        m[2][2] = cx;
    }
    else
    {
        m[0][0] = 1;
        m[0][1] = 0;
        m[0][2] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
        m[1][2] = 0;
        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 1;
    }
}

void euler_mult(float x1, float y1, float z1, float x2, float y2, float z2, float &rx,float &ry,float &rz)
{
    if (x1 != 0 || y1 != 0 || z1 != 0)
    {
        if (x2 != 0 || y2 != 0 || z2 != 0)
        {
            float a[3][3],
            b[3][3],
            c[3][3];

            euler2matrix(x1,y1,z1,a);
            euler2matrix(x2,y2,z2,b);

            c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];
            c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];
            c[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];
            c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];
            //c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];
            //c[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];
            c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];
            c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];
            c[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];

            if (fabs(c[2][0]) != 1)
            {
                float tmp = -asin(fabs(c[2][0]));
                ry = tmp  * 180.0/3.1415926;
                tmp = cos(tmp);
                if (tmp != 0)
                {
                    rx = atan2_deg(c[2][1]/tmp,c[2][2]/tmp);
                    rz = atan2_deg(c[1][0]/tmp,c[0][0]/tmp);
                }
                else
                {
                    rx = x1;
                    ry = y1;
                    rz = z1;
                }
            }
            else
            {
                rz = 0;
                float tmp = atan2_deg(c[0][1],c[0][2]);
                if (c[2][0] == -1)
                {
                    ry = 90;
                    rx = tmp;
                }
                else
                {
                    ry = -90;
                    rx = tmp;
                }
            }
        }
        else
        {
            rx = x1;
            ry = y1;
            rz = z1;
        }
    }
    else
    {
        rx = x2;
        ry = y2;
        rz = z2;
    }
}


char * TrimLeft(char *buf)
{
    if (buf == NULL)
        return NULL;

    int len = strlen(buf);

    char *str=buf;

    for (int i=0; i<len; i++)
        if (buf[i]!=0x20 && buf[i]!=0x09)
        {
            str=buf + i;
            break;
        }
    return str;
}

char * TrimRight(char *buf)
{
    if (buf == NULL)
        return NULL;
    int len = strlen(buf);

    char *str=buf;

    for (int i=len-1; i>=0; i--)
        if (buf[i]==0x20 || buf[i]==0x09 || buf[i]==0x0A || buf[i]==0x0D)
            buf[i] = 0x0;
        else
            break;
    return str;
}



void vec2d_hermit(vec2d *pOut, const vec2d *pV1, const vec2d *pT1, const vec2d *pV2, const vec2d *pT2, float s)
{
    float tmp[4];

    tmp[0] = 2.0 * s*s*s - 3.0 * s*s + 1.0;
    tmp[1] = s*s*s - 2.0 * s*s + s;
    tmp[2] = -2.0 * s*s*s + 3.0 * s*s;
    tmp[3] = s*s*s - s*s;

    pOut->x = tmp[0] * pV1->x + tmp[1] * pT1->x + tmp[2] * pV2->x + tmp[3] * pT2->x;
    pOut->y = tmp[0] * pV1->y + tmp[1] * pT1->y + tmp[2] * pV2->y + tmp[3] * pT2->y;
}

void vec2d_normolize(vec2d *pOut, const vec2d *pV)
{
    float l = sqrt(pV->x * pV->x + pV->y * pV->y);

    if (l != 0.0)
    {
        pOut->x = pV->x / l;
        pOut->y = pV->y / l;
    }
    else
    {
        pOut->x = 0.0;
        pOut->y = 0.0;
    }
}
