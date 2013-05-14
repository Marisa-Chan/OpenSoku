#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

#include "graph_efx.h"

using namespace std;


class c_weather_fx: public gfx_meta
{
    public:
    c_weather_fx(int32_t idx, gfx_seq *sq, int8_t order);

    void func10();
    void set_seq_params(); //func15
};


class c_weather_sp: public gfx_holder
{
    public:
    c_weather_sp();

    void addeffect(int32_t idx, int8_t order);
    void draw(int8_t order);
};

class c_weather_bg
{
    private:
    gr_sprite sprite;
    gr_tex   *bg[20];

    int8_t   cur_weather;
    public:

    c_weather_bg();
    ~c_weather_bg();

    void draw(int8_t weather, int8_t plane);

};


int32_t weather_get();
void weather_set(int32_t id);

int32_t weather_time_mul(float m);
int32_t weather_time_add(int32_t vl);
int32_t weather_time_sub(int32_t vl);
int32_t weather_time_set(int32_t vl);
int32_t weather_time_get();

#endif // WEATHER_H_INCLUDED
