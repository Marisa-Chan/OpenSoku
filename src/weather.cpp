#include "global_types.h"
#include "scene.h"
#include "graph.h"

#include "file_read.h"
#include "archive.h"

#include "infoeffect.h"
#include "battle_ui.h"
#include "weather.h"


c_weather_fx::c_weather_fx(int32_t idx, gfx_seq *sq, int8_t _order)
{
    index = idx;
    sprite.set_seq(sq);
    x = 600;
    y = 0;
    dir = 1;

    active = true;
    order = _order;

    set_seq_params();
}

void c_weather_fx::func10()
{
    process();
}

void c_weather_fx::set_seq_params()
{

}


c_weather_sp::c_weather_sp()
{
    load_dat("effect.pat","data/weather/effect");
}

void c_weather_sp::addeffect(int32_t idx, int8_t order)
{
    gfx_seq *sq = get_seq(idx);
    if (sq)
    {
        c_weather_fx *ff = new c_weather_fx(idx, sq, order);
        fx.push_back(ff);
    }
}

void c_weather_sp::draw(int8_t order, int8_t plane)
{
    for(uint32_t i=0; i<fx.size(); i++)
        if (fx[i]->order == order)
            fx[i]->draw(plane);
}





c_weather_bg::c_weather_bg()
{
    cur_weather = -1;
    char buf[CHRBUF];
    for (int8_t i=0; i<20; i++)
    {
        sprintf(buf,"data/weather/%02d.cv2",i);
        filehandle *f = arc_get_file(buf);
        if (f)
        {
            bg[i] = gr_load_cv2(f,NULL);
            delete f;
        }
    }
}

c_weather_bg::~c_weather_bg()
{
    for (int8_t i=0; i<20; i++)
        delete bg[i];
}

void c_weather_bg::draw(int8_t weather, int8_t plane)
{
    if (weather != cur_weather)
    {
        gr_set_spr_tex(&sprite, bg[weather]);
        cur_weather = weather;
    }
    //gr_setxy_sprite(&sprite,-BKG_WIDTH / 2,0);
    //gr_setorigin_sprite(&sprite,,0);
    gr_setscale_sprite(&sprite,3.0,3.0);

    gr_draw_sprite(&sprite,gr_alpha,plane,NULL);
}


WEATHER_ID weather = WEATHER_CLEAR;
int32_t weather_time = 0;
WEATHER_ID weather_index_for_name = WEATHER_CLEAR;
WEATHER_ID weather_setted = WEATHER_CLEAR;

WEATHER_ID weather_get()
{
    return weather;
}

void weather_set(WEATHER_ID id)
{
    weather = id;
}

int32_t weather_time_mul(float m)
{
    weather_time = (int32_t)((float)weather_time * m);
    return weather_time;
}

int32_t weather_time_add(int32_t vl)
{
    weather_time += vl;
    return weather_time;
}

int32_t weather_time_sub(int32_t vl)
{
    weather_time -= vl;
    return weather_time;
}

int32_t weather_time_set(int32_t vl)
{
    weather_time = vl;
    return weather_time;
}

int32_t weather_time_get()
{
    return weather_time;
}

WEATHER_ID weather_index_for_name_get()
{
    return weather_index_for_name;
}

WEATHER_ID weather_setted_get()
{
    return weather_setted;
}

void weather_setted_change(WEATHER_ID id)
{
    weather_setted = id;
    battle_ui_effect(get_ieid_by_weather(id), 320, 42, 1, 1);
    //weather_set_sky
}

void weather_change(WEATHER_ID id, bool setted)
{
    if (setted)
        weather_setted_change(id);

  if ( id != WEATHER_CLEAR )
  {
      scene_play_sfx(53);
        battle_ui_effect(get_ieid_by_weather(id) + 2, 320, 42, 1, 1);
  }
  weather_index_for_name = id;

  if ( id == WEATHER_AURORA )
    weather = (WEATHER_ID)scene_rand_rng(19);
  else
    weather = id;
}
