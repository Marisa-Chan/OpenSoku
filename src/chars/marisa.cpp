#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "marisa.h"

char_marisa::char_marisa(inp_ab *func):
    char_c::char_c(func)
{
    viz.load_dat("marisa",0);
};

char_marisa::char_marisa(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    viz.load_dat("marisa",pal);
};

void char_marisa::set_seq_params()
{

}

void char_marisa::stopping()
{
        if (h_inerc > 0)
        {
            h_inerc -= 0.5;
            if (h_inerc < 0)
            {
                reset_forces();
                //field_49A = 0;
            }
        }
        if ( h_inerc < 0)
        {
            h_inerc += 0.5;
            if (h_inerc > 0)
            {
                reset_forces();
                //field_49A = 0;
            }
        }
}

void char_marisa::func10()
{

    int32_t sq = get_seq();

    switch(sq)
    {
    case 0:
        stopping();
        viz.process();
        break;
    case 1:
        stopping();
        if (viz.process() && viz.get_frame() == 0)
            set_seq(2);
        break;
    case 2:
        stopping();
        viz.process();
        break;
    case 3:
        stopping();
        if (viz.process() && viz.get_frame() == 0)
            set_seq(0);
        break;
    case 4:
        char_h_move(this,6.0);
        viz.process();
        break;
    case 5:
        char_h_move(this,-5.0);
        viz.process();
        break;
    case 6:

        if (viz.get_subseq()>1)
        {
            v_inerc -=v_force;
            if (char_on_ground_down(this))
            {
                set_seq(10);
                y = getlvl_height(this);
                reset_forces();
                break;
            }
        }

        viz.process();

        if (viz.get_subseq()!=0 || viz.get_frame_time() || viz.get_frame()>1 || viz.get_elaps_frames()>1)
            break;

        v_inerc = 16.0;
        v_force = 0.75;
        break;
    default:
        viz.process();
    }
}
