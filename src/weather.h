#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

#include "graph_efx.h"
#include "map"
#include "vector"
#include "deque"

using namespace std;


class c_weather_fx: public gfx_meta
{
protected:
    int16_t par1;
    int16_t par2;
    float par3;

public:
    c_weather_fx(int32_t idx, gfx_seq *sq, float x, float y, int8_t dir, int8_t order);

    void func10();
    void set_seq_params(); //func15
};


class c_weather_sp: public gfx_holder
{
public:
    c_weather_sp();

    void addeffect(int32_t idx, float x, float y, int8_t dir, int8_t order);
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
    void draw(int8_t weather, int32_t alpha, int8_t plane);

};

enum WEATHER_ID
{
    WEATHER_UNK = -1,
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
void weather_forecast_set(WEATHER_ID id);
WEATHER_ID weather_setted_get();

void weather_setted_change(WEATHER_ID id);
void weather_change(WEATHER_ID id, bool setted);

typedef vector<int32_t> sky_of_bkg;
typedef map<int32_t,sky_of_bkg> mapsky;

struct s_asky
{
    int16_t alpha;
    int32_t sky_id;
};

typedef deque<s_asky> t_askies;

struct t_weather_manager
{
    c_weather_sp wfx_holder;
    c_weather_bg skys;
    mapsky       sky_mapping;
    t_askies     sky_deque;

    WEATHER_ID   current_sky_weather;

    float field_DC;
    float field_E0;
    float field_E4;
    float field_E8;
};

void weather_init_manager();

void weather_spawn_effects_by_id(WEATHER_ID wid);
t_weather_manager *weather_manager_get();
void weather_forecast_next();

#endif // WEATHER_H_INCLUDED
