#include "graph.h"
#include "weather.h"
#include "infoeffect.h"

#include "effects.h"

//c_infoef_sp  *infoef_spawner = NULL;
c_weather_sp *weatef_spawner = NULL;
c_weather_bg *weath_bg = NULL;

void init_effects()
{
    //if (!infoef_spawner)
    //    infoef_spawner = new c_infoef_sp;
    //if (!weatef_spawner)
      //  weatef_spawner = new c_weather_sp;
    if (!weath_bg)
        weath_bg = new c_weather_bg;
}

void add_infoeffect(int32_t idx, int8_t order)
{
    //infoef_spawner->addeffect(idx, order);
}

void update_infoeffect()
{
    //infoef_spawner->update();
}

void draw_infoeffect(int8_t order)
{
    //infoef_spawner->draw(order);
}

void draw_weather_bkg(int8_t sky_id)
{
    weath_bg->draw(sky_id, 2);
}
