#include "global_types.h"
#include <math.h>
#include "moveable.h"



moveable::moveable()
{
    x = 0;
    y = 0;
    dir = 1;

    h_inerc = 0;
    v_inerc = 0;
    v_force = 0;

    angX = 0;
    angY = 0;
    angZ = 0;

    x_off = 0;
    y_off = 0;

    scaleX = 1.0;
    scaleY = 1.0;

	c_A = 255;
	c_R = 255;
	c_G = 255;
	c_B = 255;

	rs_w = 0;
	rs_h = 0;
	scale_real = false;
}

void moveable::setOrigin(float x, float y)
{
    x_off = x;
    y_off = y;
}

void moveable::reset_ofs()
{
    x_off = 0;
    y_off = 0;
    scaleX = 1.0;
    scaleY = 1.0;
    angX = 0;
    angY = 0;
    angZ = 0;
    c_A = 255;
    c_R = 255;
    c_G = 255;
    c_B = 255;
}


float moveable::getX()
{
    return x;
}

float moveable::getY()
{
    return y;
}

void moveable::set_real_size(int16_t w, int16_t h)
{
    rs_w = w;
    rs_h = h;
    scale_real = true;
}

void moveable::set_vec_speed(float angle, float speed)
{
    h_inerc = cos_deg(angle) * speed;
    v_inerc = -sin_deg(angle) * speed;
}

void moveable::set_vec_speed_2(float angle, float speed)
{
    h_inerc = cos_deg(angle) * speed;
    v_inerc = sin_deg(angle) * speed;
}
