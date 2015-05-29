#ifndef SCENE_FX_H_INCLUDED
#define SCENE_FX_H_INCLUDED

#include "graph_efx.h"

using namespace std;

class c_meta;

class c_scene_fx: public gfx_meta
{
public:
    c_scene_fx(gfx_IdSeq sq, c_meta *chr, float x, float y, int8_t dir, int8_t order);

    float par1;
    float par2;

    c_meta *parent;

    void func10();
    void set_seq_params(); //func15
};


class c_scene_sp: public gfx_SeqData
{
public:
    c_scene_sp();

    void addeffect(c_meta *chr, int32_t idx, float x, float y, int8_t dir, int8_t order);
};


#endif // SCENE_FX_H_INCLUDED
