#include "global_types.h"
#include "scene.h"
#include "graph.h"
#include "moveable.h"
#include "infoeffect.h"

c_infoef_fx::c_infoef_fx(int32_t idx, gfx_seq *sq, float _x, float _y, int8_t _dir, int8_t _order)
{
    index = idx;
    sprite.set_seq(sq);
    x = _x;
    y = _y;
    dir = _dir;

    active = true;
    order = _order;

    set_seq_params();
}

void c_infoef_fx::func10()
{
    switch(get_seq())
    {
        case 32:
        case 33:
        default:
            if (process())
                active = false;
    }
}

void c_infoef_fx::set_seq_params()
{
    switch(get_seq())
    {

    }
}


c_infoef_sp::c_infoef_sp()
{
    load_dat("effect.pat","data/infoeffect");
}

c_infoef_fx *c_infoef_sp::addeffect(int32_t idx, float x, float y, int8_t dir, int8_t order)
{
    gfx_seq *sq = get_seq(idx);
    if (sq)
    {
        c_infoef_fx *ff = new c_infoef_fx(idx, sq, x, y, dir, order);
        fx.push_back(ff);
        return ff;
    }
    return NULL;
}
