#include "global_types.h"
#include "scene.h"
#include "graph.h"
#include "moveable.h"
#include "infoeffect.h"

c_infoef_fx::c_infoef_fx(int32_t idx, gfx_seq *sq, int8_t _order)
{
    index = idx;
    sprite.set_seq(sq);
    x = 100;
    y = -100;
    dir = 1;

    active = true;
    order = _order;

    set_seq_params();
}

void c_infoef_fx::func10()
{
    process();
}

void c_infoef_fx::set_seq_params()
{

}


c_infoef_sp::c_infoef_sp()
{
    load_dat("effect.pat","data/infoeffect");
}

void c_infoef_sp::addeffect(int32_t idx, int8_t order)
{
    gfx_seq *sq = get_seq(idx);
    if (sq)
    {
        c_infoef_fx *ff = new c_infoef_fx(idx, sq, order);
        fx.push_back(ff);
    }
}

void c_infoef_sp::draw(int8_t order)
{
    for(uint32_t i=0; i<fx.size(); i++)
        if (fx[i]->order == order)
            fx[i]->draw(0);
}
