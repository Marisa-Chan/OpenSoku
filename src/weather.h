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
    void draw(int8_t order, int8_t plane = 0);
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

    void draw(int8_t weather, int8_t plane = 0);

};

enum WEATHER_ID
{
    WEATHER_SUNNY = 0,
    WEATHER_DRIZZLE = 1,
    WEATHER_CLOUDY = 2,
    WEATHER_BLUE_SKY = 3,
    WEATHER_HAIL = 4,
    WEATHER_SPRING_HAZE = 5,
    WEATHER_HEAVY_FOG = 6,
    WEATHER_SNOW = 7,
    WEATHER_SUNSHOWER = 8,
    WEATHER_SPRINKLE = 9,
    WEATHER_TEMPEST = 10,
    WEATHER_MOUNTAIN_VAPOR = 11,
    WEATHER_RIVER_MIST = 12,
    WEATHER_TYPHOON = 13,
    WEATHER_CALM = 14,
    WEATHER_DIAMOND_DUST = 15,
    WEATHER_DUST_STORM = 16,
    WEATHER_SCORCHING_SUN = 17,
    WEATHER_MONSOON = 18,
    WEATHER_AURORA = 19,
    WEATHER_HISOUTEN = 20,
    WEATHER_CLEAR = 21,
    WEATHER_ID_COUNT = 22
};


WEATHER_ID weather_get();
void weather_set(WEATHER_ID id);

int32_t weather_time_mul(float m);
int32_t weather_time_add(int32_t vl);
int32_t weather_time_sub(int32_t vl);
int32_t weather_time_set(int32_t vl);
int32_t weather_time_get();

WEATHER_ID weather_index_for_name_get();
WEATHER_ID weather_setted_get();

void weather_setted_change(WEATHER_ID id);
void weather_change(WEATHER_ID id, bool setted);

#endif // WEATHER_H_INCLUDED
