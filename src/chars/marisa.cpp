#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "marisa.h"
#include <math.h>

char_marisa::char_marisa(inp_ab *func):
    char_c::char_c(func)
{
    load_dat("marisa",0);
    char_loadsfx(this,"marisa");
};

char_marisa::char_marisa(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    load_dat("marisa",pal);
    char_loadsfx(this,"marisa");
};




void char_marisa::func10()
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
        char_h_move(this, -5.0);
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
            v_inerc = 16.0;
            v_force = 0.75;
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
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move(this, 5.0);
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
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move(this, -4.0);
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
    case 200:
        sub10func(this);
        field_49A = 1;

        if ( h_inerc > 12.0 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 12.0 )
                h_inerc = 12.0;
        }

        process();

        if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
        {
            char_h_move(this, 15.0);
            scene_add_effect(this, 125, 80*dir+x, y+80, dir,1);
            scene_add_effect(this, 126, x, y+80, dir,1);
            scene_play_sfx(31);
        }
        else if (get_subseq() == 1)
        {
            if ( (get_elaps_frames() % 5) == 0 )
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,dir,1);
            }
            if ( input->gY() <= 0)
            {
                field_7D0++;
                if ( ! ((input->gX(dir) > 0 || field_7D0 <= 5 ) && field_7D0 <=45) )
                    set_seq(204);
            }
            else
            {
                if (input->gX(dir) <= 0)
                    set_seq(211);
                else
                    set_seq(212);
            }
        }
        break;
    case 201:
        if ( get_subseq() == 0 || get_subseq() == 3 )
            sub10func(this);

        if ( get_subseq() == 3 )
        {
            h_inerc += 2.0;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( !char_on_ground_flag(this) )
        {
            if ( (get_elaps_frames() % 5) == 0)
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,-dir,1);
            }
        }
        if ( get_subseq() < 3 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down(this) )
            {
                v_inerc = 0.0;
                v_force = 0.0;
                y = getlvl_height(this);
                set_subseq(3);
                break;
            }
        }
        if ( process() )
        {
            set_seq(0);
            reset_forces();
        }
        else if ( get_elaps_frames() ==0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            char_h_move(this, -14.0);
            v_inerc = 4.0;
            v_force = 0.5;
            scene_add_effect(this, 125, x, y+80, -dir,1);
            scene_add_effect(this, 126, x, y+80, -dir,1);
            scene_play_sfx(31);
        }
        break;
    case 202:
        v_inerc -= v_force;
        if ( char_on_ground_down(this) )
        {
            reset_forces();
            y = getlvl_height(this);
            set_seq(10);
        }
        else
        {
            if ( (get_subseq() == 1 || get_subseq() == 2 ) &&  (get_elaps_frames() % 5) == 0 )
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,dir,1);
            }

            process();

            if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
            {
                field_7D0 = 0;
                char_h_move(this, 11.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x+80*dir, y+110, dir,1);
                scene_add_effect(this, 126, x, y+110, dir,1);
                scene_play_sfx(31);
            }
            else if (get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0)
                flip_with_force();
        }
        break;
    case 203:
        v_inerc -= v_force;
        if ( char_on_ground_down(this) )
        {
            reset_forces();
            y = getlvl_height(this);
            set_seq(10);
        }
        else
        {
            if ( get_subseq() < 3 && (get_elaps_frames() % 5) == 0 )
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,-dir,1);
            }

            process();

            if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
            {
                field_7D0 = 0;
                char_h_move(this, -11.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x, y+120, -dir,1);
                scene_add_effect(this, 126, x, y+120, -dir,1);
                scene_play_sfx(31);
            }
            else if (get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0)
                flip_with_force();
        }
        break;
    case 204:
        sub10func(this);
        h_inerc -= 0.5;
        if ( h_inerc < 0.0 )
        {
            h_inerc = 0.0;
            field_49A = 0;
        }
        if ( process() )
        {
            set_seq(0);
            field_49A = 0;
        }
        break;
    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
    case 221:
    case 222:
        if ( get_subseq() == 0 )
            sub10func(this);

        if ( char_on_ground_down(this) )
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( char_on_ground_flag(this) || v_inerc > 0.0 )
                field_522 = 2;
            if ( get_subseq() > 0 )
            {
                v_inerc -= v_force;
                if ( v_inerc < -20.0 )
                    v_inerc = -20.0;

                if ( get_subseq() == 1 && v_inerc < 4.0 )
                    set_subseq(2);
            }

            process();

            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
            {
                if (sq == 208)
                {
                    //char_h_move(this, 0);
                    v_inerc = 22.5;
                    v_force = 0.85;
                }
                else if (sq == 209 || sq == 221)
                {
                    char_h_move(this, 10.0);
                    v_inerc = 18.0;
                    v_force = 0.85;
                }
                else if (sq == 210 || sq == 222)
                {
                    char_h_move(this, -10.0);
                    v_inerc = 18.0;
                    v_force = 0.85;
                }
                else if (sq == 211)
                {
                    char_h_move(this, 3.0);
                    v_inerc = 22.5;
                    v_force = 0.85;
                }
                else if (sq == 212)
                {
                    char_h_move(this, 10.0);
                    v_inerc = 16.0;
                    v_force = 0.7;
                }
                field_49A = 0;
                scene_add_effect(this, 63, x, y, dir,1);
            }
        }
        break;
    case 214:
        if ( process())
            set_seq(9);
        else
        {

            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
                scene_play_sfx(31);

            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6)
                set_seq(9);
            else
            {

                if ( input->gY() > 0)
                {
                    field_7D2 = 90 - input->gX(dir) * 45;
                }
                else if (input->gY() == 0)
                {
                    if (input->gX(dir) > 0 )
                        field_7D2 = 0;
                    else if (input->gX(dir) < 0 )
                        field_7D2 = 180;
                }
                else if (input->gY() < 0)
                {
                    field_7D2 = -90 - input->gX(dir) * 45;
                }

                if ( get_subseq() == 5 || get_subseq() == 6 )
                    v_inerc -= v_force;
                if ( get_subseq() > 0 && get_subseq() < 5 )
                {
                    field_7D6 ++;
                    field_7D4 = field_7D2 - dash_angle;
                    if ( field_7D4 >180 )
                        field_7D4 -= 360;
                    else if (field_7D4 < -180)
                        field_7D4 += 360;

                    if ( field_7D4 > 0 )
                    {
                        if ( weather_var != 0 )
                            dash_angle += 0.5;
                        else
                            dash_angle += 1.5;
                    }
                    else if ( field_7D4 < 0 )
                    {
                        if ( weather_var != 0 )
                            dash_angle -= 0.5;
                        else
                            dash_angle -= 1.5;
                    }

                    h_inerc = cos(dash_angle * 3.1415/180.0) * field_7DC;
                    v_inerc = sin(dash_angle * 3.1415/180.0) * field_7DC;

                    if ( y > 680.0 )
                        if ( v_inerc > 0.0 )
                            v_inerc = 0.0;

                    field_7DC += 0.3;
                    if ( field_7DC > 12.0 )
                        field_7DC = 12.0;

                    //v1417 = weather_var != 0 ? 10 : 5;
                    //sub_479FF0(v3, v1417, 1);
                    angZ = -dash_angle;


                      if ( h_inerc < 0.0 )
                       // angZ = 180 -angZ;
                       angZ = 180.0 + dash_angle;

                    if ( h_inerc < 0.0 )
                        if ( get_subseq() == 1 )
                            set_subseq(3);

                    if ( h_inerc >= 0 )
                        if ( get_subseq() == 3 )
                            set_subseq(1);

                    if ( h_inerc < 0.0 )
                        if ( get_subseq() == 2 )
                            set_subseq(4);

                    if ( h_inerc >= 0)
                        if ( get_subseq() == 4 )
                            set_subseq(2);

                    if ( get_elaps_frames() % 5 == 1 )
                    {
                        float yy = sin(dash_angle * 3.1415/180.0) * 100.0 + y + 100.0;
                        float xx = cos(dash_angle * 3.1415/180.0) * 100.0 * dir + x;
                        scene_add_effect(this, 125, xx, yy, dir, 1);
                    }
                    if ( (input->keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
                    {
                        reset_ofs();
                        angZ = 0;

                        if ( get_subseq() == 1 || get_subseq() == 2 )
                        {
                            if ( dir == 1 )
                            {
                                if ( enemy->x >= x )
                                    set_subseq(5);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(6);
                                }
                            }
                            else
                            {
                                if ( enemy->x <= x )
                                    set_subseq(5);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(6);
                                }
                            }
                        }
                        else if ( get_subseq() == 3 || get_subseq() == 4 )
                        {
                            if ( dir == 1 )
                            {
                                if ( enemy->x >= x )
                                    set_subseq(6);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(5);
                                }
                            }
                            else
                            {
                                if ( enemy->x <= x )
                                    set_subseq(6);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(5);
                                }
                            }
                        }
                        break;
                    }
                }
            }
            if ( char_on_ground_down(this) )
            {
                y = getlvl_height(this);
                v_force = 0.0;
                v_inerc = 0.0;
                if ( get_subseq() < 5 )
                {
                    reset_ofs();
                    angZ = 0;
                    set_seq(215);
                }
                else
                {
                    set_seq(10);
                    reset_forces();
                }
            }
        }
        break;
    case 215:
        sub10func(this);
        stopping(0.75);
        if ( process())
            set_seq(0);
        break;
    case 300: //near A-attack
        sub10func(this);
        stopping_posit(0.5);

        if ( process())
            set_seq(0);
        if ( get_frame_time() == 0 && get_frame() == 4 )
        {
            scene_play_sfx(27);
            field_49A = 0;
        }
        break;
    case 301: //far A-attack
        sub10func(this);
        stopping_posit(0.5);
        if (get_frame() > 4 )
            stopping_posit(1.5);

        if ( process() )
            set_seq(0);
        if ( get_frame_time() == 0 )
        {
            if ( get_frame() == 3 )
                h_inerc = 30.0;
            if ( get_frame() == 4 )
            {
                h_inerc = 10.0;
                scene_play_sfx(27);
                field_49A = 0;
            }
        }
        if ( get_frame() > 3 )
            stopping_posit(0.5);
        break;

    case 302: //6A(A)
    {
        uint32_t ssq = get_subseq();
        if ( ssq == 0 || ssq == 1 || ssq == 4 )
            sub10func(this);

        if ( get_frame() < 2 )
            if ( !input->keyDown(INP_A))
                not_charge_attack = 0;  // yeah, CHARGE

        if ( ssq == 0 )
            if ( h_inerc > 0)
                stopping_posit(0.75);

        if (get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            if (ssq == 2)
            {
                play_sfx(17);
                h_inerc = 15.5;
                v_inerc = 4.0;
                v_force = 0.55;
            }
            else if (ssq == 3)
            {
                play_sfx(17);
                h_inerc = 18.5;
                v_inerc = 7.5;
                v_force = 0.55;
            }
        }

        if ( process() )
            set_seq(0);

        ssq = get_subseq();
        uint32_t tf = get_elaps_frames();

        if (get_frame_time() == 0 &&
                get_frame()      == 0 &&
                tf  == 0 &&
                ssq == 5)
            set_seq(0);

        if (ssq == 1)
        {
            if ( not_charge_attack == 0 && tf < 2 )
                next_subseq();
            else if ( tf > 12 )
                set_subseq(3);
            else if ( tf == 2 ) // charge effect
                scene_add_effect(this, 62,x,y+68,dir,1);
        }
        else if ( ssq == 3 || ssq == 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down(this) )
            {
                play_sfx(18);
                if ( ssq == 2 )
                    set_subseq(4);
                else
                    set_subseq(5);

                y = getlvl_height(this);
                v_inerc = 0.0;
                h_inerc = 5.0;
            }
        }
        else if ( ssq == 4 || ssq == 5 )
            stopping_posit(0.5);
    }
    break;

    case 303:
        sub10func(this);
        stopping_posit(0.6);
        if ( process() )
            set_seq(2);
        if ( get_frame_time() == 0 )
            if ( get_frame() == 3 )
                scene_play_sfx(27);
        break;

    case 304:
        sub10func(this);
        if ( h_inerc > 0.0 )
        {
            h_inerc -= 2.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( !input->keyDown(INP_A))
            not_charge_attack = 0;

        if ( process() )
            set_seq(0);

        if ( get_elaps_frames() == 0 &&
                get_frame_time() == 0 &&
                get_frame() == 0 &&
                get_subseq() == 1 )
        {
            set_seq(0);
        }
        else if ( get_subseq() != 0 || get_frame_time() != 0 || get_frame() != 4 )
        {
            if ( get_subseq() == 1 && get_frame_time() == 0 )
            {
                if ( get_frame() == 1 )
                {
                    h_inerc = 25.0;
                    scene_play_sfx(28);
                }
                else if ( get_frame() == 4 )
                    h_inerc = 0.0;
            }
        }
        else if ( not_charge_attack == 1 )
        {
            next_subseq();
            scene_add_effect(this, 62,x+dir*75,y+98,dir,1);
        }
        else if (not_charge_attack == 0)
        {
            h_inerc = 15.0;
            scene_play_sfx(28);

            if ( get_subseq() == 1 && get_frame_time() == 0 )
            {
                if ( get_frame() == 1 )
                {
                    h_inerc = 25.0;
                    scene_play_sfx(28);
                }
                else if ( get_frame() == 4 )
                    h_inerc = 0.0;
            }
        }
        break;

    case 305:
        sub10func(this);

        if ( get_frame() > 4 )
        {
            h_inerc --;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( process() )
            set_seq(0);
        if ( get_frame_time() == 0 )
            if ( get_frame() == 4 )
                scene_play_sfx(28);
        break;

    case 306:
        v_inerc -= v_force;
        if ( char_on_ground_down(this) )
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( get_subseq() == 1 &&
                    get_elaps_frames() > 12 )
                next_subseq();

            if ( process() )
                set_seq(9);
            if ( get_subseq() == 0 &&
                    get_frame()  == 1 &&
                    get_frame_time() ==0 )
                scene_play_sfx(27);
        }
        return;

    case 307:
        if ( input->keyDown(INP_A) == 0 )
            not_charge_attack = 0;

        v_inerc -= v_force;

        if ( char_on_ground_down(this) )
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {

            if ( process() )
                set_seq(9);

            if ( get_elaps_frames() == 0 &&
                    get_frame_time() == 0 &&
                    get_frame() == 0 &&
                    get_subseq() == 1 )
            {
                set_seq(9);
            }
            else
            {
                if ( get_frame() == 3 && not_charge_attack == 1 &&
                        get_subseq() == 0 && get_frame_time() == 0)
                {
                    next_subseq();
                }
                else
                {
                    if ( get_subseq() == 0 && get_frame_time() == 0 )
                    {
                        if (get_frame() == 5 )
                        {
                            play_sfx(1);
                            h_inerc = -8.0;
                            v_inerc = 7.0;
                            v_force = 0.5;

                            float params[3];
                            params[0] = 0;
                            params[1] = 0;
                            params[2] = 1;
                            addbullet(this,NULL,848,x + dir*67, y+110, dir, 1, params,3);
                        }
                    }
                    if ( get_subseq() == 1 )
                    {
                        if ( get_frame() == 0 )
                        {
                            if ( not_charge_attack == 0 &&  get_elaps_frames() < 5 )
                            {
                                set_subseq(0);
                                set_frame(3);
                                return;
                            }

                            if ( get_elaps_frames() == 5 )
                                scene_add_effect(this, 62, x-70*dir , y+180 , dir,1);

                        }
                        if ( get_frame_time() == 0 && get_frame() == 3 )
                        {

                            play_sfx(1);
                            h_inerc = -8.0;
                            v_force = 0.5;
                            v_inerc = 7.0;

                            float params[3];
                            params[0] = 0;
                            params[1] = 20;
                            params[2] = 0;
                            addbullet(this,NULL,804,x + dir*67, y+110, dir, 1, params,2);
                            field_190 = 1;
                        }
                    }
                }
            }
        }
        break;
    case 308:

        if ( input->keyDown(INP_A) == 0 )
            not_charge_attack = 0;

        v_inerc -= v_force;

        if ( char_on_ground_down(this) )
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( process() )
                set_seq(9);


            if ( get_elaps_frames() == 0 &&
                    get_frame_time() == 0 &&
                    get_frame() == 0 &&
                    get_subseq() == 1 )
            {
                set_seq(9);
            }
            else
            {
                if ( get_frame() == 3 && not_charge_attack == 1 &&
                        get_subseq() == 0 && get_frame_time() == 0)
                {
                    next_subseq();
                }
                else
                {
                    if ( get_subseq() == 0 && get_frame_time() == 0 )
                    {
                        if (get_frame() == 5 )
                        {
                            play_sfx(1);
                            h_inerc = -4.0;
                            v_inerc = 8.0;
                            v_force = 0.5;
                            float params[3];
                            params[0] = 60;
                            params[1] = 1;
                            params[2] = 1;
                            addbullet(this,NULL,848,x + dir*30, y+30, dir, 1, params,3);
                        }
                    }

                    if ( get_subseq() == 1 )
                    {
                        if ( get_frame() == 0 )
                        {
                            if ( not_charge_attack == 0 &&  get_elaps_frames() < 5 )
                            {
                                set_subseq(0);
                                set_frame(3);
                                return;
                            }

                            if ( get_elaps_frames() == 5 )
                                scene_add_effect(this, 62, x-70*dir , y+180 , dir,1);

                        }

                        if ( get_frame_time() == 0 && get_frame() == 3 )
                        {

                            play_sfx(1);
                            h_inerc = -4.0;
                            v_force = 0.5;
                            v_inerc = 8.0;
                            float params[3];
                            params[0] = 60;
                            params[1] = 20;
                            params[2] = 0;
                            addbullet(this,NULL,804,x + dir*30, y+30, dir, 1, params,2);
                            field_190 = 1;
                        }
                    }

                }
            }
        }

        break;

    case 309:

        v_inerc -= v_force;

        if ( h_inerc > 0)
        {
            h_inerc -= 0.3;
            if ( h_inerc < 2.0 )
                h_inerc = 2.0;
        }

        if ( char_on_ground_down(this) )
        {
            set_seq(10);
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if (process())
                set_seq(9);

            if ( get_subseq() == 0 && get_frame() == 3 )
            {
                if (get_frame_time() == 0)
                {
                    scene_play_sfx(29);
                    h_inerc = 10.0;
                    v_inerc = 15.0;
                    v_force = 0.85;
                }
            }
            if (get_frame_time() == 0 && get_frame() == 4)
            {
                field_194 = 1;
                field_190 = 0;
            }
        }
        break;

    case 320:
        sub10func(this);
        if ( get_frame() > 1 )
        {
            h_inerc -= 2.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( process() )
            set_seq(0);
        if ( get_frame_time() == 0 &&
                get_frame() == 2 )
        {
            scene_play_sfx(28);
            field_49A = 0;
        }
        break;
    case 321:
        sub10func(this);
        if ( get_frame() > 1 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( process() )
            set_seq(0);
        if ( get_frame_time() == 0 &&
                get_frame() == 3 )
        {
            scene_play_sfx(28);
            field_49A = 0;
            h_inerc = 7.5;
        }
        break;

    case 322:
        sub10func(this);

        if ( get_frame() > 5 )
        {
            h_inerc -= 3.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( process() )
            set_seq(0);
        if ( get_frame_time() == 0 )
        {
            if ( get_frame() == 4 )
            {
                h_inerc = 15.0;

                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 0;
                addbullet(this, NULL, 848, x, y, dir, 1, t, 3);
            }

            if ( get_frame_time() == 0  &&
                    get_frame() == 5 )
            {
                scene_play_sfx(29);
                field_49A = 0;
            }
        }
        break;
    case 400:
        sub10func(this);

        if ( get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 4))
            if ( input->keyDown(INP_B) == 0)
                not_charge_attack = 0;

        if ( field_7D0 > 0 )
        {
            field_7D0++;
            if ( not_charge_attack )
            {
                if ( (field_7D0 % 3) == 1 && field_7D2 < 5 )
                {
                    field_190 = 1;
                    //add_card_energy(v3, 10);
                    float t[4];
                    t[0] = (-10 * field_7D2) + field_7F0;
                    t[1] = 10;
                    t[2] = 0;
                    t[3] = 0.5;

                    addbullet(this, NULL, 800, dir*94 + x, y+102, dir, 1, t, 4);
                    play_sfx(0);
                    field_7D2++;
                }
            }
            else
            {
                if ( (field_7D0 % 3) == 1 && field_7D2 < 3 )
                {
                    field_190 = 1;
                    //add_card_energy(v3, 10);
                    float t[4];
                    t[0] = (-10 * field_7D2) + field_7F0;
                    t[1] = 7;
                    t[2] = 0;
                    t[3] = 0;

                    addbullet(this, NULL, 800, dir*94 + x, y+102, dir, 1, t, 4);
                    play_sfx(0);
                    field_7D2++;
                }
            }
        }

        if ( process() )
            set_seq(0);
        if ( get_subseq() == 1 )
        {
            if ( (not_charge_attack == 0 && get_elaps_frames() >= 2 && get_elaps_frames() < 5)
                    || get_elaps_frames() > 15)
            {
                next_subseq();
                break;
            }

            if ( get_elaps_frames() == 5 )
                scene_add_effect(this, 62, x - 12*dir, y+100, dir, 1);
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            sub_486FD0(25.0, -25.0);
            field_7D0 = 1;
            //sub_479FF0(v3, 200, 45);
        }
        break;

    case 401:
        sub10func(this);

        if ( get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 4))
            if ( input->keyDown(INP_B) == 0 )
                not_charge_attack = 0;


        if ( field_7D0 > 0 )
        {
            field_7D0++;
            if ( not_charge_attack )
            {
                if ( (field_7D0 % 3) == 1 && field_7D2 < 5 )
                {
                    field_190 = 1;
                    //add_card_energy(v3, 10);
                    float t[4];
                    t[0] = (-10 * field_7D2) + field_7F0;
                    t[1] = 10;
                    t[2] = 0;
                    t[3] = 0.5;

                    addbullet(this, NULL, 800, dir*96 + x, y+130, dir, 1, t, 4);
                    play_sfx(0);
                    field_7D2++;
                }
            }
            else
            {
                if ( (field_7D0 % 3) == 1 && field_7D2 < 3 )
                {
                    field_190 = 1;
                    //add_card_energy(v3, 10);
                    float t[4];
                    t[0] = (-10 * field_7D2) + field_7F0;
                    t[1] = 7;
                    t[2] = 0;
                    t[3] = 0;

                    addbullet(this, NULL, 800, dir*96 + x, y+130, dir, 1, t, 4);
                    play_sfx(0);
                    field_7D2++;
                }
            }
        }

        if ( process() )
            set_seq(0);
        if ( get_subseq() == 1 )
        {
            if ( (not_charge_attack == 0 && get_elaps_frames() >= 2 && get_elaps_frames() < 5)
                    || get_elaps_frames() > 15)
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() == 5 )
                scene_add_effect(this, 62, x - 12*dir, y+100, dir, 1);
        }

        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
            if ( field_7D4 < -40 )
                field_7D4 = -40;
            else if ( field_7D4 > -20 )
                field_7D4 = -20;

            sub_486FD0(-20.0, -55.0);
            field_7D0 = 1;
            /*sub_479FF0(v3, 200, 45);*/
        }
        break;

    case 402:
        sub10func(this);
        if ( input->keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( field_7D0 >= 0)
        {

            field_7D0--;

            if (field_7D0 == 0 && get_subseq() < 4)
            {
                field_190 = 1;
                play_sfx(0);
                //add_card_energy(v3, 5);
                float t[3];
                t[0] = (scene_rand() % 30) - 15.0;
                t[1] = field_7D2*2 + 15;
                t[2] = (scene_rand() & 3) + 2;
                addbullet(this, NULL, 800, 87*dir + x, y+67, dir, 1, t, 3);

                field_7D0 = 4;
                field_7D2++;
            }
        }
        if ( process() )
            set_seq(2);
        if ( get_subseq() == 3 && (not_charge_attack == 0 || get_elaps_frames() >= 30) )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0  && get_frame() == 2 )
        {
            field_7D0 = 1;
            //sub_479FF0(v3, 200, 45);
            scene_add_effect(this, 62, 90*dir + x, y+70, dir, 1);
        }
        break;

    case 404:
        if ( get_subseq() == 3 )
            sub10func(this);
        v_inerc -= v_force;
        if ( char_on_ground_down(this) && get_subseq() < 3 )
        {
            set_subseq(3);
            air_dash_cnt = 0;
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( field_7D0 > 0 )
            {
                field_7D0++;
                if ( not_charge_attack != 0 )
                {
                    if ( (field_7D0 %3) == 1 && field_7D2 < 5 )
                    {
                        field_190 = 1;
                        //add_card_energy(v3, 10);
                        float t[4];
                        t[0] = (-10 * field_7D2) + field_7F0;
                        t[1] = 10.0;
                        t[2] = 0;
                        t[3] = 0.5;

                        addbullet(this, NULL, 800, 80*dir +x, y+115, dir,1, t,4);
                        play_sfx(0);
                        field_7D2++;
                    }
                }
                else
                {
                    if ( (field_7D0 %3) == 1 && field_7D2 < 3 )
                    {
                        field_190 = 1;
                        //add_card_energy(v3, 10);
                        float t[4];
                        t[0] = (-10 * field_7D2) + field_7F0;
                        t[1] = 7.0;
                        t[2] = 0;
                        t[3] = 0.0;

                        addbullet(this, NULL, 800, 80*dir +x, y+115, dir,1, t,4);
                        play_sfx(0);
                        field_7D2++;
                    }
                }
            }
            if ( process() )
                set_seq(0);

            if ( get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 4))
                if ( input->keyDown(INP_B) == 0 )
                    not_charge_attack = 0;

            if ( get_subseq() == 1 )
            {

                if ( (not_charge_attack == 0 && get_elaps_frames() >= 2 && get_elaps_frames() < 5)
                        || get_elaps_frames() > 15)
                {
                    next_subseq();
                    break;
                }

                if ( get_elaps_frames() == 5 )
                    scene_add_effect(this, 62, x - 25*dir, y+125, dir, 1);
            }
            if ( get_subseq() == 2  && get_frame_time() == 0 && get_frame() == 2 )
            {
                h_inerc = -6.0;
                v_inerc = 6.0;
                v_force = 0.5;

                field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
                if ( field_7D4 < -10 )
                    field_7D4 = -10;
                else if ( field_7D4 > 10 )
                    field_7D4 = 10;

                field_7F0 = 25; //sub_486FD0(25.0, 25.0);

                field_7D0 = 1;
                //sub_479FF0(v3, 200, 45);
            }

            if ( get_subseq() == 3  && get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 )
                set_seq(9);
        }
        break;

    case 406:
        if ( get_subseq() == 3 )
            sub10func(this);
        v_inerc -= v_force;
        if ( char_on_ground_down(this) && get_subseq() < 3 )
        {
            set_subseq(3);
            air_dash_cnt = 0;
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( field_7D0 > 0 )
            {
                field_7D0++;

                if ( not_charge_attack != 0 )
                {
                    if ( (field_7D0 %3) == 1 && field_7D2 < 5 )
                    {
                        field_190 = 1;
                        //add_card_energy(v3, 10);
                        float t[4];
                        t[0] = (10 * field_7D2) + field_7F0;
                        t[1] = 10.0;
                        t[2] = 0;
                        t[3] = 0.5;

                        addbullet(this, NULL, 800, 69*dir +x, y+87, dir,1, t,4);
                        play_sfx(0);
                        field_7D2++;
                    }
                }
                else
                {
                    if ( (field_7D0 %3) == 1 && field_7D2 < 3 )
                    {
                        field_190 = 1;
                        //add_card_energy(v3, 10);
                        float t[4];
                        t[0] = (10 * field_7D2) + field_7F0;
                        t[1] = 7.0;
                        t[2] = 0;
                        t[3] = 0.0;

                        addbullet(this, NULL, 800, 69*dir +x, y+87, dir,1, t,4);
                        play_sfx(0);
                        field_7D2++;
                    }
                }
            }
            if ( process() )
                set_seq(0);

            if ( get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 4))
                if ( input->keyDown(INP_B) == 0 )
                    not_charge_attack = 0;

            if ( get_subseq() == 1 )
            {
                if ( (not_charge_attack == 0 && get_elaps_frames() >= 2 && get_elaps_frames() < 5)
                        || get_elaps_frames() > 15)
                {
                    next_subseq();
                    break;
                }
                if ( get_elaps_frames() == 5 && not_charge_attack == 1 )
                    scene_add_effect(this, 62, x - 25*dir, y+125, dir, 1);
            }
            if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
            {
                h_inerc = -6.0;
                v_inerc = 6.0;
                v_force = 0.5;

                field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
                if ( field_7D4 < 20 )
                    field_7D4 = 20;
                else if ( field_7D4 > 40 )
                    field_7D4 = 40;

                sub_486FD0(60.0, 20.0);

                field_7D0 = 1;
                //sub_479FF0(v3, 200, 45);
            }
            if ( get_subseq() == 3  && get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 )
                set_seq(9);
        }
        break;
    case 408:
        sub10func(this);
        h_inerc -= 0.75;
        if ( h_inerc < 0.0 )
            h_inerc = 0.0;

        if ( process() )
            set_seq(0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
        {
            play_sfx(1);
            float t[3];
            t[0] = 0;
            t[1] = 2;
            t[2] = 1;
            addbullet(this,NULL, 848,x +dir*106, y+103, dir ,1, t ,3);
        }
        break;
    case 409:
        v_inerc -= v_force;

        if ( char_on_ground_down(this) )
        {
            set_seq(10);
            reset_forces();
            y = getlvl_height(this);
        }
        else if ( process() )
            set_seq(9);

        break;
    case 410:
        sub10func(this);

        if ( input->keyDown(INP_C) == 0)
            not_charge_attack = 0;
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
            if ( field_7D4 < -20 )
                field_7D4 = -20;
            else if ( field_7D4 > 20 )
                field_7D4 = 20;

            play_sfx(2);
            //sub_479FF0(200, 60);
            field_190 = 1;
            //add_card_energy(v3, 50);
            if ( field_7D8 )
            {
                float t[3];
                t[0] = field_7D4;
                t[1] = 5;
                t[2] = 1.0;
                addbullet(this, NULL, 801, x+dir*44, y+85, dir, 1, t, 3);
            }
            else
            {
                float t[3];
                t[0] = field_7D4;
                t[1] = 5;
                t[2] = 0;
                addbullet(this, NULL, 801, x+dir*44, y+85, dir, 1, t, 3);
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 1 && get_elaps_frames() > 0)
        {
            if ( (not_charge_attack == 0 && get_elaps_frames() <= 9) || get_elaps_frames() >= 30 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() == 10 )
            {
                scene_add_effect(this, 62, x - 23*dir, y + 93, dir, 1);
                field_7D8 = 1;
            }
        }

        if ( get_subseq() == 3 && get_elaps_frames() > 20 )
            next_subseq();
        break;
    case 411:
        sub10func(this);

        if ( get_subseq() < 2 )
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            //add_card_energy(v3, 50);
            field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
            if ( field_7D4 < -10 )
                field_7D4 = -10;
            else if ( field_7D4 > 10 )
                field_7D4 = 10;

            play_sfx(4);
            field_190 = 1;
            //sub_479FF0(v3, 200, 60);

            float t[3];
            t[0] = 0;
            t[1] = 0;
            t[2] = 4;
            addbullet(this, NULL,803, 44*dir + x, y+85, dir, 1, t, 3);
        }

        if ( process() )
            set_seq(0);

        if ( (get_subseq() == 1 && get_elaps_frames() > 4 && (not_charge_attack == 0  || get_elaps_frames() > 25))
                || (get_subseq() == 4 && get_elaps_frames() > 12 ))
            next_subseq();

        break;
    case 412:
        sub10func(this);

        if ( get_subseq() < 2 )
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

        if ( get_subseq() == 2 && get_frame() == 1 && get_frame_time() == 0 )
        {
            play_sfx(7);
            float t[3];
            t[0] = 0;
            t[1] = field_7DC / 40.0;
            t[2] = 0;
            field_190 = 1;
            //sub_479FF0(v3, 200, 60);
            //add_card_energy(v3, 50);
            addbullet(this, NULL,802, 70*dir + x, y+162, dir, 1, t, 3);
        }

        if ( process() )
            set_seq(0);

        if ( get_subseq() == 1 && get_elaps_frames() > 4)
        {
            field_7DC++;
            if (get_elaps_frames() > 40 || not_charge_attack == 0)
                next_subseq();
        }
        break;
    case 414:
        if ( get_subseq() == 5 )
            sub10func(this);

        v_inerc -= v_force;

        if ( char_on_ground_down(this) && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

            if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
            {
                //sub_479FF0(v3, 200, 60);
                field_190 = 1;
                //add_card_energy(v3, 50);
                field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
                if ( field_7D4 < -40 )
                    field_7D4 = -40;
                else if ( field_7D4 > 40 )
                    field_7D4 = 40;

                play_sfx(2);
                if ( field_7D8 )
                {
                    float t[3];
                    t[0] = field_7D4;
                    t[1] = 0;
                    t[2] = 1;

                    addbullet(this, NULL,801, 48*dir + x, y+104, dir, 1, t, 3);
                }
                else
                {
                    float t[3];
                    t[0] = field_7D4;
                    t[1] = 0;
                    t[2] = 0;

                    addbullet(this, NULL,801, 48*dir + x, y+104, dir, 1, t, 3);
                }
            }

            if ( process() )
                set_seq(0);

            if ( get_subseq() == 5 && get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
                set_seq(9);
            else if ( get_subseq() == 1 )
            {

                v_inerc -= 0.01;
                if ( (not_charge_attack == 0 && get_elaps_frames() <= 9) || get_elaps_frames() > 30 )
                {
                    next_subseq();
                    break;
                }
                if ( get_elaps_frames() == 10 )
                {
                    field_7D8 = 1;
                    scene_add_effect(this, 62, x -23*dir , y + 107, dir, 1);
                }
            }
            else if ( get_subseq() == 3 && get_elaps_frames() > 20 )
                next_subseq();
            else if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5 )
                v_force = 0.6;
        }
        break;
    case 415:
        if ( get_subseq() == 6 )
            sub10func(this);

        v_inerc -= v_force;

        if ( char_on_ground_down(this) && get_subseq() < 6 )
        {
            set_subseq(6);
            air_dash_cnt = 0;
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( get_subseq() < 2 )
                if ( input->keyDown(INP_C) == 0)
                    not_charge_attack = 0;

            if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
            {
                play_sfx(4);
                field_190 = 1;
                //sub_479FF0(v3, 200, 60);
                //add_card_energy(v3, 50);
                if ( field_7D8 == 1 )
                {
                    float t[3];
                    t[0] = 0;
                    t[1] = 2;
                    t[2] = 4;
                    addbullet(this, NULL,803, 48*dir + x, y+104, dir, 1, t, 3);
                    /*v1790 = 0.0;
                    v1426 = &v1790;
                    v1791 = 2.0;
                    v1403 = 1;
                    v1792 = 4.0;
                    v1380 = v3->rend_cls.dir;
                    v441 = v3->rend_cls.y_pos + 104.0;
                    v1362 = v441;
                    v442 = (48 * v1380) + v3->rend_cls.x_pos;
                    v443 = v442;
                    v446 = v443;
                                     sub_46E2F0(v3, 803, v446, v1362, v1380, v1403, v1426, 3);
                    */
                }
                else
                {
                    float t[3];
                    t[0] = 0;
                    t[1] = 2;
                    t[2] = 4;
                    addbullet(this, NULL,803, 48*dir + x, y+104, dir, 1, t, 3);
                    /*v1637 = 0.0;
                    v1426 = &v1637;
                    v1638 = 2.0;
                    v1403 = 1;
                    v1639 = 4.0;
                    v1380 = v3->rend_cls.dir;
                    v444 = v3->rend_cls.y_pos + 104.0;
                    v1362 = v444;
                    v445 = (48 * v1380) + v3->rend_cls.x_pos;
                    v443 = v445;
                    v446 = v443;
                                     sub_46E2F0(v3, 803, v446, v1362, v1380, v1403, v1426, 3);
                    */
                }
            }

            if ( process() )
                set_seq(0);

            if ( get_subseq() == 6 && get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
                set_seq(9);
            else if ((get_subseq() == 1 && get_elaps_frames() > 4 && (not_charge_attack == 0 || get_elaps_frames() > 25)) ||
                     (get_subseq() == 4 && get_elaps_frames() > 12))
                next_subseq();
            else if (get_subseq() == 5 && get_frame_time() == 0 && get_frame() == 5 )
                v_force = 0.6;
        }
        break;
    case 416:
        if ( get_subseq() == 1 )
            sub10func(this);
        if ( get_subseq() == 0 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down(this) )
            {
                next_subseq();
                y = getlvl_height(this);
                reset_forces();
                break;
            }
        }

        if ( process() )
            set_seq(0);

        if (get_subseq() == 1 && get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            set_seq(9);
        else if ( get_subseq() == 0 && get_frame_time() == 0 &&  get_frame() == 5 )
        {
            play_sfx(2);
            h_inerc = -4.0;
            v_inerc = 8.0;
            v_force = 0.5;

            field_190 = 1;
            //sub_479FF0(v3, 200, 60);
            //add_card_energy(v3, 50);

            float t[3];
            t[0] = 60;
            t[1] = 0;
            t[2] = 0;
            addbullet(this, NULL, 801, x+dir*30, y+30, dir, 1,t,3);
        }
        break;
    case 418:
        sub10func(this);

        h_inerc -= 0.5;
        if ( h_inerc < 0.0 )
            h_inerc = 0.0;

        if ( process() )
            set_seq(0);

        if ( get_frame_time() == 0 )
        {
            if (get_frame() == 4)
            {
                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 0;
                addbullet(this, NULL, 848, x, y, dir, 1,t,3);
            }
            else if ( get_frame() == 5 )
            {
                scene_play_sfx(29);
                field_49A = 0;
            }
        }
        break;
    case 521:
    {

        uint32_t sq = get_subseq();

        if ( !sq || sq == 4 )
        {
            sub10func(this);
        }
        //field_18C = 1;
        if ( sq == 1 )
        {
            if ( get_elaps_frames() > 20 )
            {
                next_subseq();
            }
            /*if ( !(get_elaps_frames() % 3) )
            {
              v1802 = (MT_getnext() % 60) + 95.0 - 30.0;
              v512 = get_MT_range(0x64u) * 0.1000000014901161;
              v1803 = v512 + 10.0;
              v1804 = (MT_getnext() & 3);
              v513 = v3->rend_cls.horizontal_direction;
              v514 = v3->rend_cls.y_pos + 51.0;
              v515 = v514;
              v516 = (40 * v513) + v3->rend_cls.x_pos;
              sub_46E2F0(v3, 810, v516, v515, v513, 1, &v1802, 3);
              v1 = 0.0;
            }*/
        }

        sq = get_subseq();

        if ( sq > 0  && sq < 4 )
        {
            v_inerc -= 0.75;
            h_inerc -= 0.4;
            if ( h_inerc < 0)
                h_inerc = 0;
        }

        if ( sq == 3 && char_on_ground_down(this) )
        {
            next_subseq();
            y = getlvl_height(this);
            reset_forces();
        }

        if ( process() )
            set_seq(0);

        if (get_subseq() == 1 && get_frame_time()   == 0 &&
                get_frame()  == 0 && get_elaps_frames() == 0)
        {
            //v1661 = -85.0;
            //v1662 = 0.0;
            //v1663 = 1.0;
            //v519 = v3->rend_cls.y_pos + 232.0;
            //v520 = v519;
            //v521 = (61 * v3->rend_cls.horizontal_direction) + v3->rend_cls.x_pos;
            //sub_46E2F0(v3, 849, v521, v520, v3->rend_cls.horizontal_direction, 1, &v1661, 3);
            //sub_438170(v3, 127, v3->rend_cls.x_pos, v3->rend_cls.y_pos, v3->rend_cls.horizontal_direction, -1);
            play_sfx(5);
            //sub_479FF0(v3, 200, 120);
            //add_card_energy(v3, 50);
            h_inerc = 15.0;
            v_inerc = 25.0;
            v_force = 0.6;
        }

    }

    break;
    default:
        process();
    }
}


void char_marisa::func20()
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
    int32_t sq = get_seq();

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

            if (input->keyHit(INP_A))
            {
                if (char_on_ground_flag(this)) // On Ground
                {
                    if ( sq == 200 && input->gY() == 0 &&
                            input->gX(dir) > 0 &&
                            cprior <= get_prior(305) )  // 66A
                    {
                        angZ = 0;
                        set_seq(305);
                        input->zero_input();
                        return;
                    }

                    if ( (sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 )
                    {
                        if ( input->gY() < 0 )
                        {
                            if ( input->gX(dir) > 0 && cprior <= get_prior(304) ) // 3A
                            {
                                angZ = 0;
                                set_seq(304);
                                input->zero_input();
                                return;
                            }
                            else if (cprior <= get_prior(303) ) // 2A
                            {
                                angZ = 0;
                                set_seq(303);
                                input->zero_input();
                                return;
                            }
                        }
                        else if (input->gY() == 0)
                        {
                            if ( input->gX(dir) > 0 && cprior <= get_prior(302) ) // 6A
                            {
                                angZ = 0;
                                set_seq(302);
                                input->zero_input();
                                return;
                            }

                            float dst = fabs(x - enemy->x);

                            if ( dst > 90.0 && cprior <= get_prior(301)) //Far A
                            {
                                angZ = 0;
                                set_seq(301);
                                input->zero_input();
                                return;
                            }
                            else if(cprior <= get_prior(300)) //near A
                            {
                                angZ = 0;
                                set_seq(300);
                                input->zero_input();
                                return;
                            }
                        }
//                        if ( input->gY() <= 0)
//                        {
//                            if ( input->gX(dir) < 0)
//                            {
//                                if ( cprior <= get_prior(330) || sq == 330 )
//                                {
//                                    angZ = 0;
//                                    set_seq(330);
//                                    input->zero_input();
//                                    return;
//                                }
//                            }
//                        }
                    }
                    if ( field_190 != 0 && field_190 != 3 )
                    {
                        if ( sq == 321 ) // AAAA
                        {
                            angZ = 0;
                            set_seq(322);
                            input->zero_input();
                            return;
                        }
                        else if ( sq == 320 ) // AAA
                        {
                            angZ = 0;
                            set_seq(321);
                            input->zero_input();
                            return;
                        }
                        else if ( sq == 300 ) // AA
                        {
                            angZ = 0;
                            set_seq(320);
                            input->zero_input();
                            return;
                        }
                    }
                }
                else if (field_190 != 0 && field_190 != 3) // In Air (Melee)
                {

                    if ( input->gY() > 0 && input->gX(dir) == 0 && cprior <= get_prior(309) ) //j8A
                    {
                        angZ = 0;
                        set_seq(309);
                        input->zero_input();
                        return;
                    }
                    else if (input->gY() < 0 && input->gX(dir) >= 0 && cprior <= get_prior(308)) //j2A
                    {
                        angZ = 0;
                        set_seq(308);
                        input->zero_input();
                        return;
                    }
                    else if ( input->gY() == 0 && input->gX(dir) > 0 && cprior <= get_prior(307)) //j6A
                    {
                        angZ = 0;
                        set_seq(307);
                        input->zero_input();
                        return;
                    }
                    else if ( cprior <= get_prior(306) ) //j5A
                    {
                        angZ = 0;
                        set_seq(306);
                        input->zero_input();
                        return;
                    }
                }
            }

            if (input->keyHit(INP_B))
            {
                if (char_on_ground_flag(this)) // On Ground
                {
                    if ( sq == 200 && input->gY() == 0 &&  input->gX(dir) > 0 )  // 66B
                    {
                        angZ = 0;
                        set_seq(408);
                        input->zero_input();
                        return;
                    }

                    if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200)
                    {
                        if ( input->gY() < 0 /*&& input->gX(dir) > 0*/ && cprior <= get_prior(402) ) // 2B
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(421);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(402);
                                input->zero_input();
                                return;
                            }
                        }
                        else if ( input->gY() == 0  && input->gX(dir) > 0 && cprior <= get_prior(401) )
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(420);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(401);
                                input->zero_input();
                                return;
                            }

                        }
                        else if (cprior <= get_prior(400) )
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(420);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(400);
                                input->zero_input();
                                return;
                            }
                        }
                    }
                }
                else if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200 ) //In AIR
                {
                    if ( input->gY() >= 0 && cprior <= get_prior(404))
                    {
                        if ( field_892 > 0 && field_890 != 50 )
                        {
                            angZ = 0.0;
                            set_seq(422);
                            input->zero_input();
                            return;
                        }
                        else
                        {
                            angZ = 0.0;
                            set_seq(404);
                            input->zero_input();
                            return;
                        }
                    }
                    else if (cprior <= get_prior(406))
                    {
                        if ( field_892 > 0 && field_890 != 50 )
                        {
                            angZ = 0.0;
                            set_seq(422);
                            input->zero_input();
                            return;
                        }
                        else
                        {
                            angZ = 0.0;
                            set_seq(406);
                            input->zero_input();
                            return;
                        }

                    }
                }
            }
            if (input->keyHit(INP_C))
            {
                if (char_on_ground_flag(this)) // On Ground
                {
                    if ( sq == 200 && input->gY() == 0 &&  input->gX(dir) > 0 )  // 66B
                    {
                        angZ = 0;
                        set_seq(418);
                        input->zero_input();
                        return;
                    }
                    if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200)
                    {
                        if ( input->gY() < 0 /*&& input->gX(dir) > 0*/ && cprior <= get_prior(412) ) // 2C
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(431);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(412);
                                input->zero_input();
                                return;
                            }
                        }
                        else if ( input->gY() == 0  && input->gX(dir) > 0 && cprior <= get_prior(411) ) // 6C
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(430);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(411);
                                input->zero_input();
                                return;
                            }

                        }
                        else if (cprior <= get_prior(410) )
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(430);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(410);
                                input->zero_input();
                                return;
                            }
                        }
                    }
                }
                else
                {
                    if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200)
                    {
                        if (input->gY() >= 0 && input->gX(dir) > 0 && cprior <= get_prior(415))
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(432);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(415);
                                input->zero_input();
                                return;
                            }
                        }
                        else if (input->gY() < 0 && cprior <= get_prior(416))
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(432);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(416);
                                input->zero_input();
                                return;
                            }
                        }
                        else if (cprior <= get_prior(414))
                        {
                            if ( field_892 > 0 && field_890 != 50 )
                            {
                                angZ = 0.0;
                                set_seq(432);
                                input->zero_input();
                                return;
                            }
                            else
                            {
                                angZ = 0.0;
                                set_seq(414);
                                input->zero_input();
                                return;
                            }
                        }
                    }
                }
            }

            if (input->keyHit(INP_BC))
            {
                if (char_on_ground_flag(this))
                {

                }
            }
        }
    }
    /*
      v10 = v1->pressed_BC;
      if ( !v9 )
      {
        if ( (v10 && v10 < 3 || v1->is_pressed_BC_1) && sub_468660(v1, 0) && !v1->field_836 )
        {
          cprior = v147;
          if ( sub_489F10(v1, *&v147) )
            return;
          if ( *get_carduse_cost(&v1->field_5E8, 0) >= 100 )
          {
            if ( *get_carduse_cost(&v1->field_5E8, 0) <= 199 )
            {
              if ( v147 <= 50 )
              {
                if ( (v12 = v1->playing_seq, v12 > 299) && (v13 = v1->field_190, v13 != 3) && v13 || v12 < 300 )
                {
                  switch ( *get_carduse_cost(&v1->field_5E8, 0) )
                  {
                    case 100:
                      if ( !v1->field_800 )
                      {
                        ++v1->field_4C8;
                        v1->field_800 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v14);
                      sub_4873B0(v1, 500, v147);
                      break;
                    case 101:
                      if ( !v1->field_801 )
                      {
                        ++v1->field_4C8;
                        v1->field_801 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v15);
                      sub_4873B0(v1, 520, v147);
                      break;
                    case 102:
                      if ( !v1->field_802 )
                      {
                        ++v1->field_4C8;
                        v1->field_802 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v16);
                      sub_4873B0(v1, 540, v147);
                      break;
                    case 103:
                      if ( !v1->field_803 )
                      {
                        ++v1->field_4C8;
                        v1->field_803 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v17);
                      sub_4873B0(v1, 560, v147);
                      break;
                    case 104:
                      if ( !v1->field_800 )
                      {
                        ++v1->field_4C8;
                        v1->field_800 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v18);
                      sub_4873B0(v1, 505, v147);
                      break;
                    case 105:
                      if ( !v1->field_801 )
                      {
                        ++v1->field_4C8;
                        v1->field_801 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v19);
                      sub_4873B0(v1, 525, v147);
                      break;
                    case 106:
                      if ( !v1->field_802 )
                      {
                        ++v1->field_4C8;
                        v1->field_802 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v20);
                      sub_4873B0(v1, 545, v147);
                      break;
                    case 107:
                      if ( !v1->field_803 )
                      {
                        ++v1->field_4C8;
                        v1->field_803 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v21);
                      sub_4873B0(v1, 565, v147);
                      break;
                    case 108:
                      if ( !v1->field_800 )
                      {
                        ++v1->field_4C8;
                        v1->field_800 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v22);
                      sub_4873B0(v1, 510, v147);
                      break;
                    case 109:
                      if ( !v1->field_801 )
                      {
                        ++v1->field_4C8;
                        v1->field_801 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v23);
                      sub_4873B0(v1, 530, v147);
                      break;
                    case 110:
                      if ( !v1->field_802 )
                      {
                        ++v1->field_4C8;
                        v1->field_802 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v24);
                      sub_4873B0(v1, 550, v147);
                      break;
                    case 111:
                      if ( !v1->field_803 )
                      {
                        ++v1->field_4C8;
                        v1->field_803 = 1;
                      }
                      sub_4834F0(v1);
                      sub_488E70(v1, v25);
                      sub_4873B0(v1, 570, v147);
                      break;
                    default:
                      goto LABEL_77;
                  }
                  return;
                }
              }
            }
          }
    LABEL_77:
          if ( v147 <= 100 )
          {
            if ( *get_carduse_cost(&v1->field_5E8, 0) >= 200 )
            {
              if ( *get_carduse_cost(&v1->field_5E8, 0) <= 299 )
              {
                if ( !v1->pressed_x_axis )
                {
                  if ( (v26 = v1->playing_seq, v26 > 299) && (v27 = v1->field_190) != 0 && v27 != 3 || v26 < 300 )
                  {
                    switch ( *get_carduse_cost(&v1->field_5E8, 0) )
                    {
                      case 200:
                        sub_487370(v1, 600, v147);
                        break;
                      case 201:
                        sub_487370(v1, 601, v147);
                        break;
                      case 202:
                        sub_487370(v1, 602, v147);
                        break;
                      case 203:
                        sub_487370(v1, 603, v147);
                        break;
                      case 204:
                        sub_487370(v1, 604, v147);
                        break;
                      case 205:
                        sub_487370(v1, 605, v147);
                        break;
                      case 206:
                        sub_487370(v1, 606, v147);
                        break;
                      case 207:
                        sub_487370(v1, 607, v147);
                        break;
                      case 208:
                        sub_487370(v1, 608, v147);
                        break;
                      case 209:
                        sub_487370(v1, 609, v147);
                        break;
                      case 210:
                        sub_487370(v1, 610, v147);
                        break;
                      case 211:
                        sub_487370(v1, 611, v147);
                        break;
                      case 212:
                        sub_487370(v1, 612, v147);
                        break;
                      case 213:
                        sub_487370(v1, 613, v147);
                        break;
                      case 214:
                        sub_487370(v1, 614, v147);
                        break;
                      case 215:
                        if ( BYTE2(v1->field_8A6) )
                          goto LABEL_108;
                        sub_487370(v1, 615, v147);
                        break;
                      case 216:
                        sub_487370(v1, 616, v147);
                        break;
                      case 217:
                        sub_487370(v1, 617, v147);
                        break;
                      case 218:
                        sub_487370(v1, 618, v147);
                        break;
                      case 219:
                        sub_487370(v1, 619, v147);
                        break;
                      default:
                        goto LABEL_108;
                    }
                    return;
                  }
                }
              }
            }
          }
        }
        else
        {
          v11 = cprior;
        }
    LABEL_108:
        if ( sub_4870D0(v1) )
        {
          if ( v1->pressed_combination & 0x400 )
          {
            if ( SBYTE1(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 531) || (v28 = v1->playing_seq, v28 >= 500) && v28 <= 599 && !v1->field_801 )
              {
                if ( !v1->field_801 )
                {
                  ++v1->field_4C8;
                  v1->field_801 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 531, v11);
                return;
              }
            }
            if ( SBYTE1(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 526) || (v29 = v1->playing_seq, v29 >= 500) && v29 <= 599 && !v1->field_801 )
              {
                if ( !v1->field_801 )
                {
                  ++v1->field_4C8;
                  v1->field_801 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 526, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 521) || (v30 = v1->playing_seq, v30 >= 500) && v30 <= 599 && !v1->field_801 )
            {
              if ( !v1->field_801 )
              {
                ++v1->field_4C8;
                v1->field_801 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 521, v11);
              return;
            }
          }
          if ( v1->pressed_combination & 0x200 )
          {
            if ( SBYTE1(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 530) || (v31 = v1->playing_seq, v31 >= 500) && v31 <= 599 && !v1->field_801 )
              {
                if ( !v1->field_801 )
                {
                  ++v1->field_4C8;
                  v1->field_801 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 530, v11);
                return;
              }
            }
            if ( SBYTE1(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 525) || (v32 = v1->playing_seq, v32 >= 500) && v32 <= 599 && !v1->field_801 )
              {
                if ( !v1->field_801 )
                {
                  ++v1->field_4C8;
                  v1->field_801 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 525, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 520) || (v33 = v1->playing_seq, v33 >= 500) && v33 <= 599 && !v1->field_801 )
            {
              if ( !v1->field_801 )
              {
                ++v1->field_4C8;
                v1->field_801 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 520, v11);
              return;
            }
          }
          if ( v1->pressed_combination & 4 )
          {
            if ( SBYTE3(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 571) || (v34 = v1->playing_seq, v34 >= 500) && v34 <= 599 && !v1->field_803 )
              {
                if ( !v1->field_803 )
                {
                  ++v1->field_4C8;
                  v1->field_803 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 571, v11);
                return;
              }
            }
            if ( SBYTE3(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 566) || (v35 = v1->playing_seq, v35 >= 500) && v35 <= 599 && !v1->field_803 )
              {
                if ( !v1->field_803 )
                {
                  ++v1->field_4C8;
                  v1->field_803 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 566, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 561) || (v36 = v1->playing_seq, v36 >= 500) && v36 <= 599 && !v1->field_803 )
            {
              if ( !v1->field_803 )
              {
                ++v1->field_4C8;
                v1->field_803 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 561, v11);
              return;
            }
          }
          if ( v1->pressed_combination & 2 )
          {
            if ( SBYTE3(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 570) || (v37 = v1->playing_seq, v37 >= 500) && v37 <= 599 && !v1->field_803 )
              {
                if ( !v1->field_803 )
                {
                  ++v1->field_4C8;
                  v1->field_803 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 570, v11);
                return;
              }
            }
            if ( SBYTE3(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 565) || (v38 = v1->playing_seq, v38 >= 500) && v38 <= 599 && !v1->field_803 )
              {
                if ( !v1->field_803 )
                {
                  ++v1->field_4C8;
                  v1->field_803 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 565, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 560) || (v39 = v1->playing_seq, v39 >= 500) && v39 <= 599 && !v1->field_803 )
            {
              if ( !v1->field_803 )
              {
                ++v1->field_4C8;
                v1->field_803 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 560, v11);
              return;
            }
          }
          if ( v1->pressed_combination & 0x40 )
          {
            if ( SLOBYTE(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 511) || (v40 = v1->playing_seq, v40 >= 500) && v40 <= 599 && !v1->field_800 )
              {
                if ( !v1->field_800 )
                {
                  ++v1->field_4C8;
                  v1->field_800 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 511, v11);
                return;
              }
            }
            if ( SLOBYTE(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 506) || (v41 = v1->playing_seq, v41 >= 500) && v41 <= 599 && !v1->field_800 )
              {
                if ( !v1->field_800 )
                {
                  ++v1->field_4C8;
                  v1->field_800 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 506, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 500) )
              goto LABEL_247;
            v42 = v1->playing_seq;
            if ( v42 >= 500 && v42 <= 599 && !v1->field_800 )
              goto LABEL_248;
          }
          if ( v1->pressed_combination & 0x20 )
          {
            if ( SLOBYTE(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 510) || (v43 = v1->playing_seq, v43 >= 500) && v43 <= 599 && !v1->field_800 )
              {
                if ( !v1->field_800 )
                {
                  ++v1->field_4C8;
                  v1->field_800 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 510, v11);
                return;
              }
            }
            if ( SLOBYTE(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 505) || (v44 = v1->playing_seq, v44 >= 500) && v44 <= 599 && !v1->field_800 )
              {
                if ( !v1->field_800 )
                {
                  ++v1->field_4C8;
                  v1->field_800 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 505, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 500) || (v45 = v1->playing_seq, v45 >= 500) && v45 <= 599 && !v1->field_800 )
            {
    LABEL_247:
              if ( v1->field_800 )
              {
    LABEL_249:
                sub_4834F0(v1);
                sub_4873B0(v1, 500, v11);
                return;
              }
    LABEL_248:
              ++v1->field_4C8;
              v1->field_800 = 1;
              goto LABEL_249;
            }
          }
          if ( v1->pressed_combination & 0x40000000 )
          {
            if ( SBYTE2(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 551) || (v46 = v1->playing_seq, v46 >= 500) && v46 <= 599 && !v1->field_802 )
              {
                if ( !v1->field_802 )
                {
                  ++v1->field_4C8;
                  v1->field_802 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 551, v11);
                return;
              }
            }
            if ( SBYTE2(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 546) || (v47 = v1->playing_seq, v47 >= 500) && v47 <= 599 && !v1->field_802 )
              {
                if ( !v1->field_802 )
                {
                  ++v1->field_4C8;
                  v1->field_802 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 546, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 541) || (v48 = v1->playing_seq, v48 >= 500) && v48 <= 599 && !v1->field_802 )
            {
              if ( !v1->field_802 )
              {
                ++v1->field_4C8;
                v1->field_802 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 541, v11);
              return;
            }
          }
          if ( v1->pressed_combination & 0x20000000 )
          {
            if ( SBYTE2(v1->field_6AC) >= 1 )
            {
              if ( v11 <= get_prior(v1, 550) || (v49 = v1->playing_seq, v49 >= 500) && v49 <= 599 && !v1->field_802 )
              {
                if ( !v1->field_802 )
                {
                  ++v1->field_4C8;
                  v1->field_802 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 550, v11);
                return;
              }
            }
            if ( SBYTE2(v1->field_6A8) >= 1 )
            {
              if ( v11 <= get_prior(v1, 545) || (v50 = v1->playing_seq, v50 >= 500) && v50 <= 599 && !v1->field_802 )
              {
                if ( !v1->field_802 )
                {
                  ++v1->field_4C8;
                  v1->field_802 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 545, v11);
                return;
              }
            }
            if ( v11 <= get_prior(v1, 540) || (v51 = v1->playing_seq, v51 >= 500) && v51 <= 599 && !v1->field_802 )
            {
              if ( !v1->field_802 )
              {
                ++v1->field_4C8;
                v1->field_802 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 540, v11);
              return;
            }
          }
        }
        goto LABEL_503;
      }
      if ( (v10 && v10 < 3 || v1->is_pressed_BC_1) && sub_468660(v1, 0) && !v1->field_836 )
      {
        if ( *get_carduse_cost(&v1->field_5E8, 0) < 100 || *get_carduse_cost(&v1->field_5E8, 0) > 199 )
        {
          v11 = v147;
        }
        else
        {
          v11 = v147;
          if ( v147 <= 50 )
          {
            if ( (v52 = v1->playing_seq, v52 > 299) && (v53 = v1->field_190, v53 != 3) && v53 || v52 < 300 )
            {
              switch ( *get_carduse_cost(&v1->field_5E8, 0) )
              {
                case 100:
                  if ( !v1->field_800 )
                  {
                    ++v1->field_4C8;
                    v1->field_800 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v54);
                  sub_4873B0(v1, 500, v147);
                  break;
                case 102:
                  if ( !v1->field_802 )
                  {
                    ++v1->field_4C8;
                    v1->field_802 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v55);
                  sub_4873B0(v1, 542, v147);
                  break;
                case 103:
                  if ( !v1->field_803 )
                  {
                    ++v1->field_4C8;
                    v1->field_803 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v56);
                  sub_4873B0(v1, 562, v147);
                  break;
                case 104:
                  if ( !v1->field_800 )
                  {
                    ++v1->field_4C8;
                    v1->field_800 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v57);
                  sub_4873B0(v1, 505, v147);
                  break;
                case 106:
                  if ( SBYTE2(v1->field_6A8) < 1 )
                    goto LABEL_341;
                  if ( !v1->field_802 )
                  {
                    ++v1->field_4C8;
                    v1->field_802 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v58);
                  sub_4873B0(v1, 547, v147);
                  break;
                case 107:
                  if ( !v1->field_803 )
                  {
                    ++v1->field_4C8;
                    v1->field_803 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v59);
                  sub_4873B0(v1, 567, v147);
                  break;
                case 108:
                  if ( !v1->field_800 )
                  {
                    ++v1->field_4C8;
                    v1->field_800 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v60);
                  sub_4873B0(v1, 512, v147);
                  break;
                case 110:
                  if ( SBYTE2(v1->field_6AC) < 1 )
                    goto LABEL_341;
                  if ( !v1->field_802 )
                  {
                    ++v1->field_4C8;
                    v1->field_802 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v61);
                  sub_4873B0(v1, 552, v147);
                  break;
                case 111:
                  if ( !v1->field_803 )
                  {
                    ++v1->field_4C8;
                    v1->field_803 = 1;
                  }
                  sub_4834F0(v1);
                  sub_488E70(v1, v62);
                  sub_4873B0(v1, 572, v147);
                  break;
                default:
                  goto LABEL_341;
              }
              return;
            }
          }
        }
    LABEL_341:
        if ( v11 <= 100 )
        {
          if ( *get_carduse_cost(&v1->field_5E8, 0) >= 200 )
          {
            if ( *get_carduse_cost(&v1->field_5E8, 0) <= 299 )
            {
              if ( !v1->pressed_x_axis )
              {
                if ( (v63 = v1->playing_seq, v63 > 299) && (v64 = v1->field_190) != 0 && v64 != 3 || v63 < 300 )
                {
                  switch ( *get_carduse_cost(&v1->field_5E8, 0) )
                  {
                    case 203:
                      sub_487370(v1, 603, v11);
                      break;
                    case 205:
                      sub_487370(v1, 605, v11);
                      break;
                    case 207:
                      sub_487370(v1, 607, v11);
                      break;
                    case 208:
                      sub_487370(v1, 658, v11);
                      break;
                    case 211:
                      sub_487370(v1, 611, v11);
                      break;
                    default:
                      goto LABEL_356;
                  }
                  return;
                }
              }
            }
          }
        }
      }
      else
      {
        v11 = v147;
      }
    LABEL_356:
      if ( sub_4870D0(v1) )
      {
        if ( v1->pressed_combination & 4 )
        {
          if ( SBYTE3(v1->field_6AC) >= 1 )
          {
            if ( v11 <= get_prior(v1, 573) || (v65 = v1->playing_seq, v65 >= 500) && v65 <= 599 && !v1->field_803 )
            {
              if ( !v1->field_803 )
              {
                ++v1->field_4C8;
                v1->field_803 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 573, v11);
              return;
            }
          }
          if ( SBYTE3(v1->field_6A8) >= 1 )
          {
            if ( v11 <= get_prior(v1, 568) || (v66 = v1->playing_seq, v66 >= 500) && v66 <= 599 && !v1->field_803 )
            {
              if ( !v1->field_803 )
              {
                ++v1->field_4C8;
                v1->field_803 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 568, v11);
              return;
            }
          }
          if ( v11 <= get_prior(v1, 563) || (v67 = v1->playing_seq, v67 >= 500) && v67 <= 599 && !v1->field_803 )
          {
            if ( !v1->field_803 )
            {
              ++v1->field_4C8;
              v1->field_803 = 1;
            }
            sub_4834F0(v1);
            sub_4873B0(v1, 563, v11);
            return;
          }
        }
        if ( v1->pressed_combination & 2 )
        {
          if ( SBYTE3(v1->field_6AC) >= 1 )
          {
            if ( v11 <= get_prior(v1, 572) || (v68 = v1->playing_seq, v68 >= 500) && v68 <= 599 && !v1->field_803 )
            {
              if ( !v1->field_803 )
              {
                ++v1->field_4C8;
                v1->field_803 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 572, v11);
              return;
            }
          }
          if ( SBYTE3(v1->field_6A8) >= 1 )
          {
            if ( v11 <= get_prior(v1, 567) || (v69 = v1->playing_seq, v69 >= 500) && v69 <= 599 && !v1->field_803 )
            {
              if ( !v1->field_803 )
              {
                ++v1->field_4C8;
                v1->field_803 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 567, v11);
              return;
            }
          }
          if ( v11 <= get_prior(v1, 562) || (v70 = v1->playing_seq, v70 >= 500) && v70 <= 599 && !v1->field_803 )
          {
            if ( !v1->field_803 )
            {
              ++v1->field_4C8;
              v1->field_803 = 1;
            }
            sub_4834F0(v1);
            sub_4873B0(v1, 562, v11);
            return;
          }
        }
        if ( v1->pressed_combination & 0x40 )
        {
          if ( SLOBYTE(v1->field_6AC) >= 1 )
          {
            if ( v11 <= get_prior(v1, 513) || (v71 = v1->playing_seq, v71 >= 500) && v71 <= 599 && !v1->field_800 )
            {
              if ( !v1->field_800 )
              {
                ++v1->field_4C8;
                v1->field_800 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 513, v11);
              return;
            }
          }
          if ( SLOBYTE(v1->field_6A8) >= 1 )
          {
            if ( v11 <= get_prior(v1, 506) || (v72 = v1->playing_seq, v72 >= 500) && v72 <= 599 && !v1->field_800 )
            {
              if ( !v1->field_800 )
              {
                ++v1->field_4C8;
                v1->field_800 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 506, v11);
              return;
            }
          }
          if ( v11 <= get_prior(v1, 500) )
            goto LABEL_447;
          v73 = v1->playing_seq;
          if ( v73 >= 500 && v73 <= 599 && !v1->field_800 )
            goto LABEL_448;
        }
        if ( v1->pressed_combination & 0x20 )
        {
          if ( SLOBYTE(v1->field_6AC) >= 1 )
          {
            if ( v11 <= get_prior(v1, 512) || (v74 = v1->playing_seq, v74 >= 500) && v74 <= 599 && !v1->field_800 )
            {
              if ( !v1->field_800 )
              {
                ++v1->field_4C8;
                v1->field_800 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 512, v11);
              return;
            }
          }
          if ( SLOBYTE(v1->field_6A8) >= 1 )
          {
            if ( v11 <= get_prior(v1, 505) || (v75 = v1->playing_seq, v75 >= 500) && v75 <= 599 && !v1->field_800 )
            {
              if ( !v1->field_800 )
              {
                ++v1->field_4C8;
                v1->field_800 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 505, v11);
              return;
            }
          }
          if ( v11 <= get_prior(v1, 500) || (v76 = v1->playing_seq, v76 >= 500) && v76 <= 599 && !v1->field_800 )
          {
    LABEL_447:
            if ( v1->field_800 )
            {
    LABEL_449:
              sub_4834F0(v1);
              sub_4873B0(v1, 500, v11);
              return;
            }
    LABEL_448:
            ++v1->field_4C8;
            v1->field_800 = 1;
            goto LABEL_449;
          }
        }
        if ( v1->pressed_combination & 0x40000000 )
        {
          if ( SBYTE2(v1->field_6AC) >= 2 )
          {
            if ( v11 <= get_prior(v1, 553) || (v77 = v1->playing_seq, v77 >= 500) && v77 <= 599 && !v1->field_802 )
            {
              if ( !v1->field_802 )
              {
                ++v1->field_4C8;
                v1->field_802 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 553, v11);
              return;
            }
          }
          if ( SBYTE2(v1->field_6A8) >= 2 )
          {
            if ( v11 <= get_prior(v1, 548) || (v78 = v1->playing_seq, v78 >= 500) && v78 <= 599 && !v1->field_802 )
            {
              if ( !v1->field_802 )
              {
                ++v1->field_4C8;
                v1->field_802 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 548, v11);
              return;
            }
          }
          if ( !BYTE2(v1->field_6A8) )
          {
            if ( !BYTE2(v1->field_6AC) )
            {
              if ( v11 <= get_prior(v1, 543) || (v79 = v1->playing_seq, v79 >= 500) && v79 <= 599 && !v1->field_802 )
              {
                if ( !v1->field_802 )
                {
                  ++v1->field_4C8;
                  v1->field_802 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 543, v11);
                return;
              }
            }
          }
        }
        if ( v1->pressed_combination & 0x20000000 )
        {
          if ( SBYTE2(v1->field_6AC) >= 2 )
          {
            if ( v11 <= get_prior(v1, 552) || (v80 = v1->playing_seq, v80 >= 500) && v80 <= 599 && !v1->field_802 )
            {
              if ( !v1->field_802 )
              {
                ++v1->field_4C8;
                v1->field_802 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 552, v11);
              return;
            }
          }
          if ( SBYTE2(v1->field_6A8) >= 2 )
          {
            if ( v11 <= get_prior(v1, 547) || (v81 = v1->playing_seq, v81 >= 500) && v81 <= 599 && !v1->field_802 )
            {
              if ( !v1->field_802 )
              {
                ++v1->field_4C8;
                v1->field_802 = 1;
              }
              sub_4834F0(v1);
              sub_4873B0(v1, 547, v11);
              return;
            }
          }
          if ( !BYTE2(v1->field_6A8) )
          {
            if ( !BYTE2(v1->field_6AC) )
            {
              if ( v11 <= get_prior(v1, 542) || (v82 = v1->playing_seq, v82 >= 500) && v82 <= 599 && !v1->field_802 )
              {
                if ( !v1->field_802 )
                {
                  ++v1->field_4C8;
                  v1->field_802 = 1;
                }
                sub_4834F0(v1);
                sub_4873B0(v1, 542, v11);
                return;
              }
            }
          }
        }
      }
    LABEL_503:
      v8 = 200;
      goto LABEL_504;
    }
      }
    */

}

c_bullet *char_marisa::new_bullet()
{
    c_bullet *tmp = new marisa_bullets();
    return tmp;
}

void char_marisa::set_seq_params()
{

    switch(get_seq())
    {
    case 214:
        reset_ofs();
        field_7D6 = 0;
        v_inerc = 0.0;
        h_inerc = 0.0;
        v_force = 0.60000002;
        field_7DC = 12.0;
//        field_7EC = 0.0;
        x_off = 0;
        y_off = 95;
        break;
    case 302:
        if ( !field_49A )
            reset_forces();
        field_190 = 0;
        field_49A = 0;
        field_194 = 1;
        not_charge_attack = 1;
        break;
    case 304:
        field_49A = 0;
        field_194 = 1;
        field_190 = 0;
        reset_forces();
        not_charge_attack = 1;
        break;
    case 305:
        v_inerc = 0.0;
        field_49A = 0;
        field_190 = 0;
        h_inerc = 17.5;
        field_194 = 1;
        v_force = 0.0;
        break;
    case 306:
        field_7D0 = 0;
        field_190 = 0;
        field_194 = 1;
        break;
    case 307:
    case 308:
    case 309:
        field_194 = 1;
        field_190 = 0;
        not_charge_attack = 1;
        break;
    case 320:
        field_49A = 0;
        //field_190 = 0;
        field_194 = 1;
        break;
    case 400:
    case 401:
    case 402:
    case 411:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        not_charge_attack = 1;
        break;
    case 404:
    case 406:
    case 415:
        v_force = 0.0;
        field_190 = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        not_charge_attack = 1;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        return;
        break;
    case 408:
        h_inerc = 17.5;
        field_49A = 0;
        field_7D0 = 0;
        field_190 = 0;
        v_inerc = 0.0;
        field_194 = 1;
        break;
    case 410:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        not_charge_attack = 1;
        break;
    case 412:
        field_190 = 0;
        not_charge_attack = 1;
        reset_forces();
        field_7DC = 0.0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        break;
    case 414:
        v_force = 0.0;
        field_190 = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        not_charge_attack = 1;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 416:
        field_190 = 0;
        field_7D8 = 0;
        field_194 = 1;
        break;
    case 418:
        h_inerc = 17.5;
        if ( field_49A == 0)
            reset_forces();
        field_190 = 0;
        field_194 = 1;
        break;
    default:
        char_c::set_seq_params();
        break;
    }
}








