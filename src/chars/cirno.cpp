#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "cirno.h"
#include <math.h>

char_cirno::char_cirno(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    char_id = CHAR_ID_CIRNO;
    pgp->load_dat("chirno",pal);
    char_loadsfx("chirno");
    cards_load_cards(&chr_cards,"chirno");
    load_face("chirno");
    load_spells("chirno");
    stand_gfx->init(this,"chirno");
}

void char_cirno::init_vars()
{
    field_890 = 0;
    field_138 = -6.0;
    char_c::init_vars();
}


void char_cirno::func10()
{
    x_delta = 0;
    y_delta = 100;


    if ( hit_stop != 0 /*|| enemy->time_stop != 0 */)
        return;

    int32_t sq = get_seq();

    switch(sq)
    {
    case 0:
        sub10func();
        if (h_inerc == 0)
            field_49A = 0;
        stopping(0.5);
        process();
        break;
    case 1:
        sub10func();
        stopping(0.5);
        if (process() && get_frame() == 0)
            set_seq(2);
        break;
    case 2:
        sub10func();
        stopping(0.5);
        process();
        break;
    case 3:
        sub10func();
        stopping(0.5);
        if (process() && get_frame() == 0)
            set_seq(0);
        break;
    case 4:
        sub10func();
        char_h_move( 6.0);
        process();
        break;
    case 5:
        sub10func();
        char_h_move( -6.0);
        process();
        break;
    case 6:
        if (get_subseq() == 0)
        {
            sub10func();
            if (field_49A == 0)
                reset_forces();
        }
        if (get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down())
            {
                set_seq(10);
                y = getlvl_height();
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
            sub10func();
            if (field_49A == 0)
                reset_forces();
        }

        if (get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down())
            {
                set_seq(10);
                y = getlvl_height();
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
            char_h_move( 5.0);
            field_49A = 0;
        }
        break;
    case 8:
        if (get_subseq() == 0)
        {
            sub10func();
            if (field_49A == 0)
                reset_forces();
        }

        if (get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down())
            {
                set_seq(10);
                y = getlvl_height();
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
            char_h_move( -5.0);
        }
        break;
    case 9:
        if (v_force == 0)
            v_force = 0.6;

        v_inerc -=v_force;

        if (char_on_ground_down())
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }

        process();
        break;
    case 10:
        sub10func();
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
        char_c::func10();
    }
}


void char_cirno::func20()
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
    bool cu = (fflags & FF_HJC) != 0;
    //int32_t sq = get_seq();

    if ( !check_AB_pressed() ) // !sub_4870A0(a1, v2) - AB input check
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
            if ( char_on_ground_flag() )
            {
                if ( (cu && cprior >= 10 && hi_jump_after_move())
                        || border_escape_ground()
                        || hi_jump(cprior, cu)
                        || fw_bk_dash_ground(cprior, cu) )
                    return;
            }
            else
            {
                int8_t mx = (weather_id == WEATHER_TEMPEST) + 2;
                if ( border_escape_air()
                        || fwd_dash_air(cprior, cu, mx, 2)
                        || bkg_dash_air(cprior, cu, mx, 2)
                        || flying_air(cprior, cu, mx) )
                    return;
            }
        }
        if ( field_84C == 0 && cc )
        {
            if (input->keyHit(INP_B))
            {
                if (char_on_ground_flag()) // On Ground
                {
                    if (gX(dir) > 0 && gY() == 0)
                    {
                        if ( cprior <= get_prior(401) )
                        {
                            angZ = 0;
                            set_seq(401);
                            return;
                        }
                    }
                }
            }
        }
    }
}

c_bullet *char_cirno::new_bullet()
{
    c_bullet *tmp = new cirno_bullets();
    return tmp;
}

void char_cirno::set_seq_params()
{
    switch(get_seq())
    {
    default:
        char_c::set_seq_params();
        break;
    }
}








