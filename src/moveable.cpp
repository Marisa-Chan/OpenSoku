#include "global_types.h"
#include <math.h>
#include "moveable.h"

float lvl_height[BKG_WIDTH];

void init_lvl_height()
{
    for(uint32_t i=0; i< BKG_WIDTH; i++)
        lvl_height[i] = 0;
}

void setlvl_height_rng(int32_t from, int32_t to, float lvl)
{
    int32_t mini = from < 0 ? 0 : (from >= 1280 ? 1279 : from);
    int32_t maxi = to < 0 ? 0 : (to >= 1280 ? 1279 : to);

    for (int32_t i= mini; i<= maxi; i++)
        lvl_height[i] = (uint32_t)(lvl+0.5);
}

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

//Borders:
// 0 - center
//-1 - right border
// 1 - left border
s_border moveable::get_border_near()
{
    if ( x - 40.0 > 0.0 )
    {
        if ( x + 40.0 < 1280.0 )
            return BORD_CENT;
        else
            return BORD_RIGHT;
    }
    return BORD_LEFT;
}

float moveable::getlvl_height()
{
    if ( x > 0.0 )
    {
        if ( x < BKG_WIDTH )
            return lvl_height[(uint32_t)(x+0.5)];
        else
            return lvl_height[BKG_WIDTH - 1];
    }
    return lvl_height[0];
}

float moveable::getlvl_height(float dx)
{
    float t = x + dx;
    if ( t > 0.0 )
    {
        if ( t < BKG_WIDTH )
            return lvl_height[(uint32_t)(t+0.5)];
        else
            return lvl_height[BKG_WIDTH - 1];
    }
    return lvl_height[0];
}



bool moveable::char_on_ground()
{
    return getlvl_height() >= y;
}
