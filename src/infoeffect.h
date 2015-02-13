#ifndef INFOEFFECT_H_INCLUDED
#define INFOEFFECT_H_INCLUDED

#include "graph_efx.h"
#include "weather.h"

using namespace std;


class c_infoef_fx: public gfx_meta
{
public:
    c_infoef_fx(int32_t idx, gfx_seq *sq, float x, float y, int8_t dir, int8_t order);
    float par2;

    void func10();
    void set_seq_params(); //func15
};

//spawner
class c_infoef_sp: public gfx_holder
{
public:
    c_infoef_sp();

    c_infoef_fx *addeffect(int32_t idx, float x, float y, int8_t dir, int8_t order);
};

//get infoeffect effect id for weather id
int32_t get_ieid_by_weather(WEATHER_ID id);

#endif // INFOEFFECT_H_INCLUDED
