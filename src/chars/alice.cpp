#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "alice.h"

char_alice::char_alice(inp_ab *func):
    char_c::char_c(func)
{
    load_dat("alice",0);
    char_loadsfx(this,"alice");
};

char_alice::char_alice(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    load_dat("alice",pal);
    char_loadsfx(this,"alice");
};


void char_alice::func10()
{

    int32_t sq = get_seq();

    switch(sq)
    {
    case 0:
        sub10func(this);
        if (h_inerc == 0)
            field_49A = 0;
        stopping(0.5);
        process();
        break;
    case 1:
        sub10func(this);
        stopping(0.5);
        if (process() && get_frame() == 0)
            set_seq(2);
        break;
    case 2:
        sub10func(this);
        stopping(0.5);
        process();
        break;
    case 3:
        sub10func(this);
        stopping(0.5);
        if (process() && get_frame() == 0)
            set_seq(0);
        break;
    case 4:
        sub10func(this);
        char_h_move(this, 6.0);
        process();
        break;
    case 5:
        sub10func(this);
        char_h_move(this, -6.0);
        process();
        break;
    case 6:
        if (get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }
        if (get_subseq()>0)
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
        process();

        if (get_subseq()       == 1 &&
                get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            v_inerc = 15.0;
            v_force = 0.65;
        }
        break;
    case 7:
        if (get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (get_subseq()>0)
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

        process();

        if (get_subseq()       == 1 &&
                get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            v_inerc = 15.0;
            v_force = 0.65;
            char_h_move(this, 5.0);
            field_49A = 0;
        }
        break;
    case 8:
        if (get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (get_subseq()>0)
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

        process();

        if (get_subseq()       == 1 &&
                get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            v_inerc = 15.0;
            v_force = 0.65;
            char_h_move(this, -5.0);
        }
        break;
    case 9:
        if (v_force == 0)
            v_force = 0.6;

        v_inerc -=v_force;

        if (char_on_ground_down(this))
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
            break;
        }

        process();
        break;
    case 10:
        sub10func(this);
        reset_forces();
        if (process())
        {
            if (input->gY() < 0)
                set_seq(2);
            else
                set_seq(0);
        }
        break;
    default:
        process();
    }
}

void char_alice::set_seq_params()
{
    uint32_t sq = get_seq();
    switch(sq)
    {
    default:
        char_c::set_seq_params();
        break;
    }
}


void char_alice::func20()
{


    /*v1 = a1;
      v2 = a1->current_frame_params;
      v3 = v2->fflags;
      v147 = a1->current_seq_frames_vector->cprior;
      v4 = v2->fflags & FF_CANCELLEABLE;
      v148 = v2->fflags & FF_CANCELLEABLE;
      v5 = v3 & FF_UNK200000;*/

    uint16_t cprior = get_cprior();
    uint32_t fflags = get_pframe()->fflags;

    bool cc = (fflags & FF_CANCELLEABLE) != 0;
    bool cu = (fflags & FF_UNK200000) != 0;
    //int32_t sq = get_seq();

    if ( /* !sub_4870A0(a1, v2)*/ true ) // !sub_4870A0(a1, v2) - AB input check
    {
        if ( cc || cu )
        {
            /*
             if ( pres_comb >= 700 && pres_comb < 800 )
             {
               //v1->class->func2_set_seq(v1, LOWORD(v1->pressed_combination));
               return;
             }
             else*/
            if ( char_on_ground_flag(this) )
            {
                if ( (cu && cprior >= 10 && sub_487110(this))
                        || sub_4871A0(this)
                        || sub_4896A0(this, cprior, cu)
                        || sub_489A30(this, cprior, cu) )
                    return;
            }
            else
            {
                int8_t mx = (weather_var == 10) + 2;
                if ( sub_4872C0(this)
                        || sub_489B90(this, cprior, cu, mx, 2)
                        || sub_489C80(this, cprior, cu, mx, 2)
                        || sub_489D70(this, cprior, cu, mx) )
                    return;
            }
        }
        if ( field_84C == 0 && cc )
        {
        }
    }
}
