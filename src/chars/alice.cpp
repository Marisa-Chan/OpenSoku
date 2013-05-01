#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "alice.h"

char_alice::char_alice(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    char_id = CHAR_ID_ALICE;
    pgp->load_dat("alice",pal);
    char_loadsfx(this,"alice");
    cards_load_cards(&chr_cards,"alice");
};

c_bullet *char_alice::new_bullet()
{
    c_bullet *tmp = new alice_bullets();
    return tmp;
}


void char_alice::func10()
{
    x_delta = 0;
    y_delta = 100;


    if ( hit_stop != 0 /*|| enemy->time_stop != 0 */)
        return;

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
    case 199:
        sub10func(this);
        if ( process() )
        {

            /*if ( LOBYTE(v2->controlling_type) == 2 )
            {
                set_seq(700);

                field_51C = 3;
                field_520 = 3;
            }
            else*/
            {
                set_seq(0);
                if ( gY() < 0)
                    set_seq(1);
            }
        }
        else if ( get_frame_time() == 0  && get_frame() == 5)
        {
            if (enemy->x < x)
                dir = -1;
            else
                dir = 1;
        }
        break;
    case 401:
        sub10func(this);
        if ( !keyDown(INP_B) )
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0  && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = -74;
            tmp[1] = 40;
            tmp[2] = 0;

            addbullet(this, NULL, 803,x - 74*dir, y + 104, dir, 1,tmp,3 );
            play_sfx(2);
            field_190 = 1;
            //sub_479FF0(this, 200, 45);
            //add_card_energy(v2, 30);
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
            set_seq(0);
        else if ((get_subseq() == 2 && get_elaps_frames() >= 30) ||
                 (get_subseq() == 4 && get_elaps_frames() >= 25) ||
                 (get_subseq() == 6 && get_elaps_frames() >= 45))
            next_subseq();
        break;
    default:
        char_c::func10();
    }
}

void char_alice::set_seq_params()
{
    uint32_t sq = get_seq();
    switch(sq)
    {
    case 400:
    case 401:
    case 410:
    case 411:
    case 412:
    case 419:
    case 520:
    case 521:
    case 522:
    case 523:
    case 525:
    case 526:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        not_charge_attack = 1;
        break;
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
    bool cu = (fflags & FF_HJC) != 0;
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
                if ( (cu && cprior >= 10 && hi_jump_after_move(this))
                        || border_escape_ground(this)
                        || hi_jump(this, cprior, cu)
                        || fw_bk_dash_ground(this, cprior, cu) )
                    return;
            }
            else
            {
                int8_t mx = (weather_var == 10) + 2;
                if ( border_escape_air(this)
                        || fwd_dash_air(this, cprior, cu, mx, 2)
                        || bkg_dash_air(this, cprior, cu, mx, 2)
                        || flying_air(this, cprior, cu, mx) )
                    return;
            }
        }
        if ( field_84C == 0 && cc )
        {
            if (input->keyHit(INP_B))
            {
                if (char_on_ground_flag(this)) // On Ground
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
