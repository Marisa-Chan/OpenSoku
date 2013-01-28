#ifndef INFOEFFECT_H_INCLUDED
#define INFOEFFECT_H_INCLUDED

#include "graph_efx.h"

using namespace std;


class c_infoef_fx: public gfx_meta
{
    public:
    c_infoef_fx(int32_t idx, gfx_seq *sq, int8_t order);

    void func10();
    void set_seq_params(); //func15
};

//spawner
class c_infoef_sp: public gfx_holder
{
    public:
    c_infoef_sp();

    void addeffect(int32_t idx, int8_t order);
    void draw(int8_t order);
};


#endif // INFOEFFECT_H_INCLUDED
