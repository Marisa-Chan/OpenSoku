#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "marisa.h"
#include <math.h>

char_marisa::char_marisa(inp_ab *func):
    char_c::char_c(func)
{
    viz.load_dat("marisa",0);
    char_loadsfx(this,"marisa");
};

char_marisa::char_marisa(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    viz.load_dat("marisa",pal);
    char_loadsfx(this,"marisa");
};


void char_marisa::stopping(float p)
{
    if (field_49A)
    {
        if (h_inerc > 0)
        {
            h_inerc -= p;
            if (h_inerc < 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
        if ( h_inerc < 0)
        {
            h_inerc += p;
            if (h_inerc > 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
    }
    else
        reset_forces();
}

void char_marisa::stopping_posit(float p)
{
    if (field_49A)
    {
        h_inerc -= p;
        if (h_inerc < 0)
        {
            reset_forces();
            field_49A = 0;
        }
    }
    else
        reset_forces();
}

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
        viz.process();
        break;
    case 1:
        sub10func(this);
        stopping(0.5);
        if (viz.process() && viz.get_frame() == 0)
            set_seq(2);
        break;
    case 2:
        sub10func(this);
        stopping(0.5);
        viz.process();
        break;
    case 3:
        sub10func(this);
        stopping(0.5);
        if (viz.process() && viz.get_frame() == 0)
            set_seq(0);
        break;
    case 4:
        sub10func(this);
        char_h_move(this,6.0);
        viz.process();
        break;
    case 5:
        sub10func(this);
        char_h_move(this,-5.0);
        viz.process();
        break;
    case 6:
        if (viz.get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (viz.get_subseq()>0)
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

        if (viz.get_subseq()       == 1 &&
                viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
        {
            v_inerc = 16.0;
            v_force = 0.75;
        }
        break;

    case 7:
        if (viz.get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (viz.get_subseq()>0)
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

        if (viz.get_subseq()       == 1 &&
                viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
        {
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move(this, 5.0);
        }
        break;
    case 8:
        if (viz.get_subseq() == 0)
        {
            sub10func(this);
            if (field_49A == 0)
                reset_forces();
        }

        if (viz.get_subseq()>0)
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

        if (viz.get_subseq()       == 1 &&
                viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
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

        viz.process();
        break;
    case 10:
        sub10func(this);
        if (viz.process() && viz.get_frame() == 0)
            set_seq(0);
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

        viz.process();

        if ( viz.get_subseq() == 0 && viz.get_frame() == 3 && viz.get_frame_time() == 0 )
        {
            char_h_move(this, 15.0);
            scene_add_effect(this, 125, 80*dir+x, y+80, dir,1);
            scene_add_effect(this, 126, x, y+80, dir,1);
            scene_play_sfx(31);
        }
        else if (viz.get_subseq() == 1)
        {
            if ( (viz.get_elaps_frames() % 5) == 0 )
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
        if ( viz.get_subseq() == 0 || viz.get_subseq() == 3 )
            sub10func(this);

        if ( viz.get_subseq() == 3 )
        {
            h_inerc += 2.0;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( !char_on_ground_flag(this) )
        {
            if ( (viz.get_elaps_frames() % 5) == 0)
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,-dir,1);
            }
        }
        if ( viz.get_subseq() < 3 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down(this) )
            {
                v_inerc = 0.0;
                v_force = 0.0;
                y = getlvl_height(this);
                viz.set_subseq(3);
                break;
            }
        }
        if ( viz.process() )
        {
            set_seq(0);
            reset_forces();
        }
        else if ( viz.get_elaps_frames() ==0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_subseq() == 1 )
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
            if ( (viz.get_subseq() == 1 || viz.get_subseq() == 2 ) &&  (viz.get_elaps_frames() % 5) == 0 )
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,dir,1);
            }

            viz.process();

            if ( viz.get_subseq() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 2 )
            {
                field_7D0 = 0;
                char_h_move(this, 11.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x+80*dir, y+110, dir,1);
                scene_add_effect(this, 126, x, y+110, dir,1);
                scene_play_sfx(31);
            }
            else if (viz.get_subseq() == 2 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_elaps_frames() == 0)
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
            if ( viz.get_subseq() < 3 && (viz.get_elaps_frames() % 5) == 0 )
            {
                float yy = (scene_rand() % 200) + y;
                float xx = x - (scene_rand() % 100) + 50;
                scene_add_effect(this, 124,xx,yy,-dir,1);
            }

            viz.process();

            if ( viz.get_subseq() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 3 )
            {
                field_7D0 = 0;
                char_h_move(this, -11.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x, y+120, -dir,1);
                scene_add_effect(this, 126, x, y+120, -dir,1);
                scene_play_sfx(31);
            }
            else if (viz.get_subseq() == 2 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_elaps_frames() == 0)
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
        if ( viz.process() )
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
        if ( viz.get_subseq() == 0 )
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
            if ( viz.get_subseq() > 0 )
            {
                v_inerc -= v_force;
                if ( v_inerc < -20.0 )
                    v_inerc = -20.0;

                if ( viz.get_subseq() == 1 && v_inerc < 4.0 )
                    viz.set_subseq(2);
            }

            viz.process();

            if ( viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_subseq() == 1)
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
        if ( viz.process())
            set_seq(9);
        else
        {

            if ( viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_subseq() == 1)
                scene_play_sfx(31);

            if (viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_subseq() == 6)
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

                if ( viz.get_subseq() == 5 || viz.get_subseq() == 6 )
                    v_inerc -= v_force;
                if ( viz.get_subseq() > 0 && viz.get_subseq() < 5 )
                {
                    field_7D6 ++;
                    field_7D4 = field_7D2 - dash_angle;
                    if ( field_7D4 > 180 )
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
                        angZ = 180.0 - dash_angle;

                    if ( h_inerc < 0.0 )
                        if ( viz.get_subseq() == 1 )
                            viz.set_subseq(3);

                    if ( h_inerc >= 0 )
                        if ( viz.get_subseq() == 3 )
                            viz.set_subseq(1);

                    if ( h_inerc < 0.0 )
                        if ( viz.get_subseq() == 2 )
                            viz.set_subseq(4);

                    if ( h_inerc >= 0)
                        if ( viz.get_subseq() == 4 )
                            viz.set_subseq(2);

                    if ( viz.get_elaps_frames() % 5 == 1 )
                    {
                        float yy = sin(dash_angle * 3.1415/180.0) * 100.0 + y + 100.0;
                        float xx = cos(dash_angle * 3.1415/180.0) * 100.0 * dir + x;
                        scene_add_effect(this, 125, xx, yy, dir, 1);
                    }
                    if ( (input->keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
                    {
                        //initclass_rendercharclass(&v3->rend_cls);
                        angZ = 0;

                        if ( viz.get_subseq() != 0 || viz.get_subseq() == 2 )
                        {
                            if ( dir == 1 )
                            {
                                if ( enemy->x >= x )
                                    viz.set_subseq(5);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    viz.set_subseq(6);
                                }
                            }
                            else
                            {
                                if ( enemy->x <= x )
                                    viz.set_subseq(5);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    viz.set_subseq(6);
                                }
                            }
                        }
                        else if ( viz.get_subseq() == 3 || viz.get_subseq() == 4 )
                        {
                            if ( dir == 1 )
                            {
                                if ( enemy->x >= x )
                                    viz.set_subseq(6);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    viz.set_subseq(5);
                                }
                            }
                            else
                            {
                                if ( enemy->x <= x )
                                    viz.set_subseq(6);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    viz.set_subseq(5);
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
                if ( viz.get_subseq() < 5 )
                {
                    //initclass_rendercharclass(&v3->rend_cls);
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
        if ( viz.process())
            set_seq(0);
        break;
    case 300: //near A-attack
        sub10func(this);
        stopping_posit(0.5);

        if ( viz.process())
            set_seq(0);
        if ( viz.get_frame_time() == 0 && viz.get_frame() == 4 )
        {
            scene_play_sfx(27);
            field_49A = 0;
        }
        break;
    case 301: //far A-attack
        sub10func(this);
        stopping_posit(0.5);
        if (viz.get_frame() > 4 )
            stopping_posit(1.5);

        if ( viz.process() )
            set_seq(0);
        if ( viz.get_frame_time() == 0 )
        {
            if ( viz.get_frame() == 3 )
                h_inerc = 30.0;
            if ( viz.get_frame() == 4 )
            {
                h_inerc = 10.0;
                scene_play_sfx(27);
                field_49A = 0;
            }
        }
        if ( viz.get_frame() > 3 )
            stopping_posit(0.5);
        break;

    case 302: //6A(A)
    {
        uint32_t ssq = viz.get_subseq();
        if ( ssq == 0 || ssq == 1 || ssq == 4 )
            sub10func(this);

        if ( viz.get_frame() < 2 )
            if ( !input->keyDown(INP_A))
                not_charge_attack = 0;  // yeah, CHARGE

        if ( ssq == 0 )
            if ( h_inerc > 0)
                stopping_posit(0.75);

        if (viz.get_frame_time()   == 0 &&
                viz.get_frame()        == 0 &&
                viz.get_elaps_frames() == 0)
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

        if ( viz.process() )
            set_seq(0);

        ssq = viz.get_subseq();
        uint32_t tf = viz.get_elaps_frames();

        if (viz.get_frame_time() == 0 &&
                viz.get_frame()      == 0 &&
                tf  == 0 &&
                ssq == 5)
            set_seq(0);

        if (ssq == 1)
        {
            if ( not_charge_attack == 0 && tf < 2 )
                next_subseq();
            else if ( tf > 12 )
                viz.set_subseq(3);
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
                    viz.set_subseq(4);
                else
                    viz.set_subseq(5);

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
        if ( viz.process() )
            set_seq(2);
        if ( viz.get_frame_time() == 0 )
            if ( viz.get_frame() == 3 )
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

        if ( viz.process() )
            set_seq(0);

        if ( viz.get_elaps_frames() == 0 &&
                viz.get_frame_time() == 0 &&
                viz.get_frame() == 0 &&
                viz.get_subseq() == 1 )
        {
            set_seq(0);
        }
        else if ( viz.get_subseq() != 0 || viz.get_frame_time() != 0 || viz.get_frame() != 4 )
        {
            if ( viz.get_subseq() == 1 && viz.get_frame_time() == 0 )
            {
                if ( viz.get_frame() == 1 )
                {
                    h_inerc = 25.0;
                    scene_play_sfx(28);
                }
                else if ( viz.get_frame() == 4 )
                    h_inerc = 0.0;
            }
        }
        else if ( not_charge_attack == 1 )
        {
            viz.next_subseq();
            scene_add_effect(this, 62,x+dir*75,y+98,dir,1);
        }
        else if (not_charge_attack == 0)
        {
            h_inerc = 15.0;
            scene_play_sfx(28);

            if ( viz.get_subseq() == 1 && viz.get_frame_time() == 0 )
            {
                if ( viz.get_frame() == 1 )
                {
                    h_inerc = 25.0;
                    scene_play_sfx(28);
                }
                else if ( viz.get_frame() == 4 )
                    h_inerc = 0.0;
            }
        }
        break;

    case 305:
        sub10func(this);

        if ( viz.get_frame() > 4 )
        {
            h_inerc --;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( viz.process() )
            set_seq(0);
        if ( viz.get_frame_time() == 0 )
            if ( viz.get_frame() == 4 )
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
            if ( viz.get_subseq() == 1 &&
                    viz.get_elaps_frames() > 12 )
                next_subseq();

            if ( viz.process() )
                set_seq(9);
            if ( viz.get_subseq() == 0 &&
                    viz.get_frame()  == 1 &&
                    viz.get_frame_time() ==0 )
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

            if ( viz.process() )
                set_seq(9);

            if ( viz.get_elaps_frames() == 0 &&
                    viz.get_frame_time() == 0 &&
                    viz.get_frame() == 0 &&
                    viz.get_subseq() == 1 )
            {
                set_seq(9);
            }
            else
            {
                if ( viz.get_frame() == 3 && not_charge_attack == 1 &&
                        viz.get_subseq() == 0 && viz.get_frame_time() == 0)
                {
                    next_subseq();
                }
                else
                {
                    if ( viz.get_subseq() == 0 && viz.get_frame_time() == 0 )
                    {
                        if (viz.get_frame() == 5 )
                        {
                            play_sfx(1);
                            h_inerc = -8.0;
                            v_inerc = 7.0;
                            v_force = 0.5;
                            /*v1793 = 0.0;
                            v1794 = 0.0;
                            v1795 = 1.0;
                            v252 = v3->rend_cls.y_pos + 110.0;
                            v253 = v252;
                            v254 = (67 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                            sub_46E2F0(v3, 848, v254, v253, v3->rend_cls.dir, 1, &v1793, 3);*/
                        }
                    }
                    if ( viz.get_subseq() == 1 )
                    {
                        if ( viz.get_frame() == 0 )
                        {
                            if ( not_charge_attack == 0 &&  viz.get_elaps_frames() < 5 )
                            {
                                viz.set_subseq(0);
                                set_frame(3);
                                return;
                            }

                            if ( viz.get_elaps_frames() == 5 )
                                scene_add_effect(this, 62, x-70*dir , y+180 , dir,1);

                        }
                        if ( viz.get_frame_time() == 0 && viz.get_frame() == 3 )
                        {

                            play_sfx(1);
                            h_inerc = -8.0;
                            v_force = 0.5;
                            v_inerc = 7.0;

                            /* v1444 = 3;

                             v1419 = &v1868;
                             v1396 = 1;

                             v1868 = 0.0;
                             v1869 = 20.0;
                             v1373 = v3->rend_cls.dir;
                             v260 = v3->rend_cls.y_pos + 110.0;
                             v1356 = v260;
                             v261 = (67 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                             v262 = v261;
                             v263 = v262;
                             sub_46E2F0(v3, 804, v263, v1356, v1373, v1396, v1419, v1444);*/
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
            if ( viz.process() )
                set_seq(9);


            if ( viz.get_elaps_frames() == 0 &&
                    viz.get_frame_time() == 0 &&
                    viz.get_frame() == 0 &&
                    viz.get_subseq() == 1 )
            {
                set_seq(9);
            }
            else
            {
                if ( viz.get_frame() == 3 && not_charge_attack == 1 &&
                        viz.get_subseq() == 0 && viz.get_frame_time() == 0)
                {
                    next_subseq();
                }
                else
                {
                    if ( viz.get_subseq() == 0 && viz.get_frame_time() == 0 )
                    {
                        if (viz.get_frame() == 5 )
                        {
                            play_sfx(1);
                            h_inerc = -4.0;
                            v_inerc = 8.0;
                            v_force = 0.5;
                            /*v1799 = 60.0;
                            v1800 = 1.0;
                            v1801 = 1.0;
                            v265 = v3->rend_cls.dir;
                            v266 = v3->rend_cls.y_pos + 30.0;
                            v267 = v266;
                            v268 = (30 * v265) + v3->rend_cls.x_pos;
                            sub_46E2F0(v3, 848, v268, v267, v265, v251, &v1799, 3);*/
                        }
                    }

                    if ( viz.get_subseq() == 1 )
                    {
                        if ( viz.get_frame() == 0 )
                        {
                            if ( not_charge_attack == 0 &&  viz.get_elaps_frames() < 5 )
                            {
                                viz.set_subseq(0);
                                set_frame(3);
                                return;
                            }

                            if ( viz.get_elaps_frames() == 5 )
                                scene_add_effect(this, 62, x-70*dir , y+180 , dir,1);

                        }

                        if ( viz.get_frame_time() == 0 && viz.get_frame() == 3 )
                        {

                            play_sfx(1);
                            h_inerc = -4.0;
                            v_force = 0.5;
                            v_inerc = 8.0;

                            /*
                                      v1444 = 3;
                                      v1419 = &v1870;
                                      v1396 = v251;
                                      v1870 = 60.0;
                                      v1871 = 20.0;
                                      v1373 = v3->rend_cls.dir;
                                      v274 = v3->rend_cls.y_pos + 30.0;
                                      v1356 = v274;
                                      v275 = (30 * v1373) + v3->rend_cls.x_pos;
                                      v262 = v275;
                                      v263 = v262;
                                      sub_46E2F0(v3, 804, v263, v1356, v1373, v1396, v1419, v1444);*/

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
            if (viz.process())
                set_seq(9);

            if ( viz.get_subseq() == 0 && viz.get_frame() == 3 )
            {
                if (viz.get_frame_time() == 0)
                {
                    scene_play_sfx(29);
                    h_inerc = 10.0;
                    v_inerc = 15.0;
                    v_force = 0.85;
                }
            }
            if (viz.get_frame_time() == 0 && viz.get_frame() == 4)
            {
                field_194 = 1;
                field_190 = 0;
            }
        }
        break;

    case 320:
        sub10func(this);
        if ( viz.get_frame() > 1 )
        {
            h_inerc -= 2.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( viz.process() )
            set_seq(0);
        if ( viz.get_frame_time() == 0 &&
                viz.get_frame() == 2 )
        {
            scene_play_sfx(28);
            field_49A = 0;
        }
        break;
    case 321:
        sub10func(this);
        if ( viz.get_frame() > 1 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( viz.process() )
            set_seq(0);
        if ( viz.get_frame_time() == 0 &&
                viz.get_frame() == 3 )
        {
            scene_play_sfx(28);
            field_49A = 0;
            h_inerc = 7.5;
        }
        break;

    case 322:
        sub10func(this);

        if ( viz.get_frame() > 5 )
        {
            h_inerc -= 3.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( viz.process() )
            set_seq(0);
        if ( viz.get_frame_time() == 0 )
        {
            if ( viz.get_frame() == 4 )
            {
                h_inerc = 15.0;
                /*v1445 = 3;
                v1420 = &v1805;
                v1805 = 0.0;
                v1397 = 1;
                v1806 = 0.0;
                v1807 = 0.0;
                v1374 = v3->rend_cls.dir;
                sub_46E2F0(v3, 848, v3->rend_cls.x_pos, v3->rend_cls.y_pos, v1374, v1397, v1420, v1445);*/
            }

            if ( viz.get_frame_time() == 0  &&
                    viz.get_frame() == 5 )
            {
                scene_play_sfx(29);
                field_49A = 0;
            }
        }
        break;
    case 400:
        sub10func(this);

        if ( viz.get_subseq() == 0 || (viz.get_subseq() == 1 && viz.get_elaps_frames() <= 4))
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
                    /*v1446 = 4;
                    v1421 = &v1820;
                    v1398 = 1;
                    v1820 = (-10 * v3->field_7D2) + v3->field_7F0;
                    v1821 = 10.0;
                    v1822 = 0.0;
                    v1823 = 0.5;
                    v1375 = v3->rend_cls.dir;
                    v291 = v3->rend_cls.y_pos + 102.0;
                    v1357 = v291;
                    v292 = (94 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                    v290 = v292;
                    v293 = v290;
                    sub_46E2F0(v3, 800, v293, v1357, v1375, 1, v1421, v1446);*/
                    play_sfx(0);
                    field_7D2++;
                }
            }
            else
            {
                if ( (field_7D0 % 3) == 1 && field_7D2 < 3 )
                {
                    field_190 = 1;
                    /*add_card_energy(v3, 10);
                    v1446 = 4;
                    v1421 = &v1852;
                    v1398 = 1;
                    v1852 = (-10 * v3->field_7D2) + v3->field_7F0;
                    v1853 = 7.0;
                    v1854 = 0.0;
                    v1855 = 0.0;
                    v1375 = v3->rend_cls.dir;
                    v288 = v3->rend_cls.y_pos + 102.0;
                    v1357 = v288;
                    v289 = (94 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                    v290 = v292;
                    v293 = v290;
                    sub_46E2F0(v3, 800, v293, v1357, v1375, v1398, v1421, v1446);*/
                    play_sfx(0);
                    field_7D2++;
                }
            }
        }

        if ( viz.process() )
            set_seq(0);
        if ( viz.get_subseq() == 1 )
        {
            if ( (not_charge_attack == 0 && viz.get_elaps_frames() >= 2 && viz.get_elaps_frames() < 5)
                    || viz.get_elaps_frames() > 15)
            {
                next_subseq();
                break;
            }

            if ( viz.get_elaps_frames() == 5 )
                scene_add_effect(this, 62, x - 12*dir, y+100, dir, 1);
        }
        if ( viz.get_subseq() == 2 && viz.get_frame_time() == 0 && viz.get_frame() == 2 )
        {
            //sub_486FD0(v3, 25.0, -25.0);
            field_7D0 = 1;
            //sub_479FF0(v3, 200, 45);
        }
        break;

    case 401:
        sub10func(this);

        if ( viz.get_subseq() == 0 || (viz.get_subseq() == 1 && viz.get_elaps_frames() <= 4))
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
                    /*v1448 = 4;
                    v1422 = &v1828;
                    v1399 = 1;
                    v1828 = (-10 * v3->field_7D2) + v3->field_7F0;
                    v1829 = 10.0;
                    v1830 = 0.0;
                    v1831 = 0.5;
                    v1376 = v3->rend_cls.dir;
                    v309 = v3->rend_cls.y_pos + 130.0;
                    v1358 = v309;
                    v310 = (96 * v1376) + v3->rend_cls.x_pos;
                    v308 = v310;
                    v311 = v308;
                    sub_46E2F0(v3, 800, v311, v1358, v1376, v1399, v1422, v1448);*/
                    play_sfx(0);
                    field_7D2++;
                }
            }
            else
            {
                if ( (field_7D0 % 3) == 1 && field_7D2 < 3 )
                {
                    field_190 = 1;
                    /*add_card_energy(v3, 10);
                    v1448 = 4;
                    v1422 = &v1844;
                    v1399 = 1;
                    v1844 = (-10 * v3->field_7D2) + v3->field_7F0;
                    v1845 = 7.0;
                    v1846 = 0.0;
                    v1847 = 0.0;
                    v1376 = v3->rend_cls.dir;
                    v306 = v3->rend_cls.y_pos + 130.0;
                    v1358 = v306;
                    v307 = (96 * v1376) + v3->rend_cls.x_pos;
                    v308 = v307;
                    v311 = v308;
                    sub_46E2F0(v3, 800, v311, v1358, v1376, v1399, v1422, v1448);*/
                    play_sfx(0);
                    field_7D2++;
                }
            }
        }

        if ( viz.process() )
            set_seq(0);
        if ( viz.get_subseq() == 1 )
        {
            if ( (not_charge_attack == 0 && viz.get_elaps_frames() >= 2 && viz.get_elaps_frames() < 5)
                    || viz.get_elaps_frames() > 15)
            {
                next_subseq();
                break;
            }
            if ( viz.get_elaps_frames() == 5 )
                scene_add_effect(this, 62, x - 12*dir, y+100, dir, 1);
        }

        if ( viz.get_subseq() == 2 && viz.get_frame_time() == 0 && viz.get_frame() == 2 )
        {
            /*v318 = v3->enemy;
            v319 = (v318->rend_cls.x_pos - v3->rend_cls.x_pos) * v3->rend_cls.dir;
            v320 = v319;
            v321 = v318->rend_cls.y_pos - v3->rend_cls.y_pos;
            v322 = -sub_4092A0(v321, v320);

            v3->field_7D4 = v322;
            if ( v322 < -40 )
              v3->field_7D4 = -40;
            if ( v3->field_7D4 > -20 )
              v3->field_7D4 = -20;

            sub_486FD0(v3, -20.0, -55.0);*/
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

            if (field_7D0 == 0 && viz.get_subseq() < 4)
            {
                field_190 = 1;
                play_sfx(0);
                /*add_card_energy(v3, 5);
                v1742 = (MT_getnext() % 0x1E) - 15.0;
                v1743 = (2 * v3->field_7D2 + 15);
                v1744 = (MT_getnext() & 3) + 2.0;
                v326 = v3->rend_cls.y_pos + 67.0;
                v327 = v326;
                v328 = (87 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                sub_46E2F0(v3, 800, v328, v327, v3->rend_cls.dir, 1, &v1742, 3);*/
                field_7D0 = 4;
                field_7D2++;
            }
        }
        if ( viz.process() )
            set_seq(2);
        if ( viz.get_subseq() == 3 && (not_charge_attack == 0 || viz.get_elaps_frames() >= 30) )
        {
            next_subseq();
            break;
        }
        if ( viz.get_subseq() == 2 && viz.get_frame_time() == 0  && viz.get_frame() == 2 )
        {
            field_7D0 = 1;
            //sub_479FF0(v3, 200, 45);
            scene_add_effect(this, 62, 90*dir + x, y+70, dir, 1);
        }
        break;

    case 404:
        if ( viz.get_subseq() == 3 )
            sub10func(this);
        v_inerc -= v_force;
        if ( char_on_ground_down(this) && viz.get_subseq() < 3 )
        {
            viz.set_subseq(3);
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
                        /*add_card_energy(v3, 10);
                        v1450 = 4;
                        v1423 = &v1836;
                        v1400 = 1;
                        v1836 = (-10 * v3->field_7D2) + v3->field_7F0;
                        v1837 = 10.0;
                        v1838 = 0.0;
                        v1839 = 0.5;
                        v1377 = v3->rend_cls.dir;
                        v340 = v3->rend_cls.y_pos + 115.0;
                        v1359 = v340;
                        v341 = (80 * v1377) + v3->rend_cls.x_pos;
                        v339 = v341;
                        v342 = v339;
                        sub_46E2F0(v3, 800, v342, v1359, v1377, v1400, v1423, v1450);*/
                        play_sfx(0);
                        field_7D2++;
                    }
                }
                else
                {
                    if ( (field_7D0 %3) == 1 && field_7D2 < 3 )
                    {
                        field_190 = 1;
                        /*add_card_energy(v3, 10);
                        v1450 = 4;
                        v1423 = &v1860;
                        v1400 = 1;
                        v1860 = (-10 * v3->field_7D2) + v3->field_7F0;
                        v1861 = 7.0;
                        v1862 = 0.0;
                        v1863 = 0.0;
                        v1377 = v3->rend_cls.dir;
                        v337 = v3->rend_cls.y_pos + 115.0;
                        v1359 = v337;
                        v338 = (80 * v1377) + v3->rend_cls.x_pos;
                        v339 = v338;
                        v342 = v339;
                        sub_46E2F0(v3, 800, v342, v1359, v1377, v1400, v1423, v1450);*/
                        play_sfx(0);
                        field_7D2++;
                    }
                }
            }
            if ( viz.process() )
                set_seq(0);

            if ( viz.get_subseq() == 0 || (viz.get_subseq() == 1 && viz.get_elaps_frames() <= 4))
                if ( input->keyDown(INP_B) == 0 )
                    not_charge_attack = 0;

            if ( viz.get_subseq() == 1 )
            {

                if ( (not_charge_attack == 0 && viz.get_elaps_frames() >= 2 && viz.get_elaps_frames() < 5)
                        || viz.get_elaps_frames() > 15)
                {
                    next_subseq();
                    break;
                }

                if ( viz.get_elaps_frames() == 5 )
                    scene_add_effect(this, 62, x - 25*dir, y+125, dir, 1);
            }
            if ( viz.get_subseq() == 2  && viz.get_frame_time() == 0 && viz.get_frame() == 2 )
            {
                //v350 = v3->enemy;
                h_inerc = -6.0;
                v_inerc = 6.0;
                v_force = 0.5;
                /*v351 = (v350->rend_cls.x_pos - v3->rend_cls.x_pos) * v3->rend_cls.dir;
                v352 = v351;
                v353 = v350->rend_cls.y_pos - v3->rend_cls.y_pos;
                v354 = -sub_4092A0(v353, v352);
                v3->field_7D4 = v354;
                if ( v354 < -10 )
                  v3->field_7D4 = -10;
                if ( v3->field_7D4 > 10 )
                  v3->field_7D4 = 10;*/
                //sub_486FD0(v3, 25.0, 25.0);
                field_7D0 = 1;
                //sub_479FF0(v3, 200, 45);
            }

            if ( viz.get_subseq() == 3  && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_elaps_frames() == 0 )
                set_seq(9);
        }
        break;

    case 406:
        if ( viz.get_subseq() == 3 )
            sub10func(this);
        v_inerc -= v_force;
        if ( char_on_ground_down(this) && viz.get_subseq() < 3 )
        {
            viz.set_subseq(3);
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
                        /*add_card_energy(v3, 10);
                        v1451 = 4;
                        v1424 = &v1816;
                        v1401 = 1;
                        v1816 = (10 * v3->field_7D2) + v3->field_7F0;
                        v1817 = 10.0;
                        v1818 = 0.0;
                        v1819 = 0.5;
                        v1378 = v3->rend_cls.dir;
                        v362 = v3->rend_cls.y_pos + 87.0;
                        v1360 = v362;
                        v363 = (69 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                        v361 = v363;
                        v364 = v361;
                        sub_46E2F0(v3, 800, v364, v1360, v1378, v1401, v1424, v1451);*/
                        play_sfx(0);
                        field_7D2++;
                    }
                }
                else
                {
                    if ( (field_7D0 %3) == 1 && field_7D2 < 3 )
                    {
                        field_190 = 1;
                        /*add_card_energy(v3, 10);
                        v1451 = 4;
                        v1424 = &v1812;
                        v1401 = 1;
                        v1812 = (10 * v3->field_7D2) + v3->field_7F0;
                        v1813 = 7.0;
                        v1814 = 0.0;
                        v1815 = 0.0;
                        v1378 = v3->rend_cls.dir;
                        v359 = v3->rend_cls.y_pos + 87.0;
                        v1360 = v359;
                        v360 = (69 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                        v361 = v360;
                        v364 = v361;
                        sub_46E2F0(v3, 800, v364, v1360, v1378, v1401, v1424, v1451);*/
                        play_sfx(0);
                        field_7D2++;
                    }
                }
            }
            if ( viz.process() )
                set_seq(0);

            if ( viz.get_subseq() == 0 || (viz.get_subseq() == 1 && viz.get_elaps_frames() <= 4))
                if ( input->keyDown(INP_B) == 0 )
                    not_charge_attack = 0;

            if ( viz.get_subseq() == 1 )
            {
                if ( (not_charge_attack == 0 && viz.get_elaps_frames() >= 2 && viz.get_elaps_frames() < 5)
                        || viz.get_elaps_frames() > 15)
                {
                    next_subseq();
                    break;
                }
                if ( viz.get_elaps_frames() == 5 && not_charge_attack == 1 )
                    scene_add_effect(this, 62, x - 25*dir, y+125, dir, 1);
            }
            if ( viz.get_subseq() == 2 && viz.get_frame_time() == 0 && viz.get_frame() == 2 )
            {
                //v373 = v3->enemy;
                h_inerc = -6.0;
                v_inerc = 6.0;
                v_force = 0.5;
                /*v374 = (v373->rend_cls.x_pos - v3->rend_cls.x_pos) * v3->rend_cls.dir;
                v375 = v374;
                v376 = v373->rend_cls.y_pos - v3->rend_cls.y_pos;
                v377 = -sub_4092A0(v376, v375);
                v3->field_7D4 = v377;
                if ( v377 < 20 )
                    v3->field_7D4 = 20;
                if ( v3->field_7D4 > 40 )
                    v3->field_7D4 = 40;
                sub_486FD0(v3, 60.0, 20.0);*/
                field_7D0 = 1;
                //sub_479FF0(v3, 200, 45);
            }
            if ( viz.get_subseq() == 3  && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_elaps_frames() == 0 )
                set_seq(9);
        }
        break;
    case 408:
        sub10func(this);
        h_inerc -= 0.75;
        if ( h_inerc < 0.0 )
            h_inerc = 0.0;

        if ( viz.process() )
            set_seq(0);
        if ( viz.get_subseq() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 6 )
        {
            play_sfx(1);
            /*   v1736 = 0.0;
               v1737 = 2.0;
               v1738 = 1.0;
               v379 = v3->rend_cls.y_pos + 103.0;
               v380 = v379;
               v381 = (106 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
               sub_46E2F0(v3, 848, v381, v380, v3->rend_cls.dir, 1, &v1736, 3);*/
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
        else if ( viz.process() )
            set_seq(9);

        break;
    case 410:
        sub10func(this);

        if ( input->keyDown(INP_C) == 0)
            not_charge_attack = 0;
        if ( viz.get_subseq() == 2 && viz.get_frame() == 2 && viz.get_frame_time() == 0 )
        {
            /*v385 = v3->enemy;
            v386 = (v385->rend_cls.x_pos - v3->rend_cls.x_pos) * v3->rend_cls.dir;
            v387 = v386;
            v388 = v385->rend_cls.y_pos - v3->rend_cls.y_pos;
            v389 = -sub_4092A0(v388, v387);
            v3->field_7D4 = v389;
            if ( v389 < -20 )
                v3->field_7D4 = -20;
            if ( v3->field_7D4 > 20 )
                v3->field_7D4 = 20;*/
            play_sfx(2);
            //sub_479FF0(v3, 200, 60);
            field_190 = 1;
            //add_card_energy(v3, 50);
            if ( field_7D8 )
            {
                /*v1619 = v3->field_7D4;
                v1620 = 5.0;
                v1621 = 1.0;
                v391 = v3->rend_cls.y_pos + 85.0;
                v392 = v391;
                v393 = (44 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                sub_46E2F0(v3, 801, v393, v392, v3->rend_cls.dir, 1, &v1619, 3);*/
            }
            else
            {
                /*v1787 = v3->field_7D4;
                v1788 = 5.0;
                v1789 = 0.0;
                v394 = v3->rend_cls.y_pos + 85.0;
                v395 = v394;
                v396 = (44 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
                sub_46E2F0(v3, 801, v396, v395, v3->rend_cls.dir, 1, &v1787, 3);*/
            }
        }
        if ( viz.process() )
            set_seq(0);
        if ( viz.get_subseq() == 1 && viz.get_elaps_frames() > 0)
        {
            if ( (not_charge_attack == 0 && viz.get_elaps_frames() <= 9) || viz.get_elaps_frames() >= 30 )
            {
                next_subseq();
                break;
            }
            if ( viz.get_elaps_frames() == 10 )
            {
                scene_add_effect(this, 62, x - 23*dir, y + 93, dir, 1);
                field_7D8 = 1;
            }
        }

        if ( viz.get_subseq() == 3 && viz.get_elaps_frames() > 20 )
            next_subseq();
        break;
    case 411:
        sub10func(this);

        if ( viz.get_subseq() < 2 )
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

        if ( viz.get_subseq() == 2 && viz.get_frame() == 2 && viz.get_frame_time() == 0 )
        {
            /*add_card_energy(v3, 50);
            v407 = v3->enemy;
            v408 = (v407->rend_cls.x_pos - v3->rend_cls.x_pos) * v3->rend_cls.dir;
            v409 = v408;
            v410 = v407->rend_cls.y_pos - v3->rend_cls.y_pos;
            v411 = -sub_4092A0(v410, v409);
            v3->field_7D4 = v411;
            if ( v411 < -10 )
              v3->field_7D4 = -10;
            if ( v3->field_7D4 > 10 )
              v3->field_7D4 = 10;*/
            play_sfx(4);
            field_190 = 1;
            //sub_479FF0(v3, 200, 60);
            /*v1591 = 0.0;
            v1592 = 0.0;
            v1593 = 4.0;
            v412 = v3->rend_cls.dir;
            v413 = v3->rend_cls.y_pos + 85.0;
            v414 = v413;
            v415 = (44 * v412) + v3->rend_cls.x_pos;
            sub_46E2F0(v3, 803, v415, v414, v412, 1, &v1591, 3);*/
        }

        if ( viz.process() )
            set_seq(0);

        if ( (viz.get_subseq() == 1 && viz.get_elaps_frames() > 4 && (not_charge_attack == 0  || viz.get_elaps_frames() > 25))
                || (viz.get_subseq() == 4 && viz.get_elaps_frames() > 12 ))
            next_subseq();

        break;
    case 412:
        sub10func(this);

        if ( viz.get_subseq() < 2 )
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

        if ( viz.get_subseq() == 2 && viz.get_frame() == 1 && viz.get_frame_time() == 0 )
        {
            play_sfx(7);
            /*v1625 = 0.0;
            v1626 = v3->field_7DC / 40.0;
            v1627 = 0.0;
            v3->field_190 = 1;
            sub_479FF0(v3, 200, 60);
            add_card_energy(v3, 50);
            v419 = v3->rend_cls.y_pos + 162.0;
            v420 = v419;
            v421 = (70 * v3->rend_cls.dir) + v3->rend_cls.x_pos;
            sub_46E2F0(v3, 802, v421, v420, v3->rend_cls.dir, 1, &v1625, 3);*/
        }

        if ( viz.process() )
            set_seq(0);

        if ( viz.get_subseq() == 1 && viz.get_elaps_frames() > 4)
        {
            field_7DC++;
            if (viz.get_elaps_frames() > 40 || not_charge_attack == 0)
                next_subseq();
        }
        break;
    case 414:
        if ( viz.get_subseq() == 5 )
            sub10func(this);

        v_inerc -= v_force;

        if ( char_on_ground_down(this) && viz.get_subseq() < 5 )
        {
            viz.set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

            if ( viz.get_subseq() == 2 && viz.get_frame() == 2 && viz.get_frame_time() == 0 )
            {
                //sub_479FF0(v3, 200, 60);
                field_190 = 1;
                /*add_card_energy(v3, 50);
                v422 = v3->enemy;
                v423 = (v422->rend_cls.x_pos - v3->rend_cls.x_pos) * v3->rend_cls.dir;
                v424 = v423;
                v425 = v422->rend_cls.y_pos - v3->rend_cls.y_pos;
                v426 = -sub_4092A0(v425, v424);
                v3->field_7D4 = v426;
                if ( v426 < -40 )
                  v3->field_7D4 = -40;
                if ( v3->field_7D4 > 40 )
                  v3->field_7D4 = 40;*/
                play_sfx(2);
                if ( field_7D8 )
                {
                    /*v1425 = &v1781;
                    v1402 = 1;
                    v1781 = v3->field_7D4;
                    v1782 = 0.0;
                    v1783 = 1.0;
                    v1379 = v3->rend_cls.dir;
                    v427 = v3->rend_cls.y_pos + 104.0;
                    v1361 = v427;
                    v428 = (48 * v1379) + v3->rend_cls.x_pos;
                    v429 = v428;
                    v432 = v429;
                                  sub_46E2F0(v3, 801, v432, v1361, v1379, v1402, v1425, 3);*/
                }
                else
                {
                    /*v1425 = &v1631;
                    v1402 = 1;
                    v1631 = v3->field_7D4;
                    v1632 = 0.0;
                    v1633 = 0.0;
                    v1379 = v3->rend_cls.dir;
                    v430 = v3->rend_cls.y_pos + 104.0;
                    v1361 = v430;
                    v431 = (48 * v1379) + v3->rend_cls.x_pos;
                    v429 = v431;
                    v432 = v429;
                                  sub_46E2F0(v3, 801, v432, v1361, v1379, v1402, v1425, 3);*/
                }
            }

            if ( viz.process() )
                set_seq(0);

            if ( viz.get_subseq() == 5 && viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 )
                set_seq(9);
            else if ( viz.get_subseq() == 1 )
            {

                v_inerc -= 0.01;
                if ( (not_charge_attack == 0 && viz.get_elaps_frames() <= 9) || viz.get_elaps_frames() > 30 )
                {
                    next_subseq();
                    break;
                }
                if ( viz.get_elaps_frames() == 10 )
                {
                    field_7D8 = 1;
                    scene_add_effect(this, 62, x -23*dir , y + 107, dir, 1);
                }
            }
            else if ( viz.get_subseq() == 3 && viz.get_elaps_frames() > 20 )
                next_subseq();
            else if ( viz.get_subseq() == 4 && viz.get_frame_time() == 0 && viz.get_frame() == 5 )
                v_force = 0.6;
        }
        break;
    case 415:
        if ( viz.get_subseq() == 6 )
            sub10func(this);

        v_inerc -= v_force;

        if ( char_on_ground_down(this) && viz.get_subseq() < 6 )
        {
            viz.set_subseq(6);
            air_dash_cnt = 0;
            y = getlvl_height(this);
            reset_forces();
        }
        else
        {
            if ( viz.get_subseq() < 2 )
                if ( input->keyDown(INP_C) == 0)
                    not_charge_attack = 0;

            if ( viz.get_subseq() == 2 && viz.get_frame() == 2 && viz.get_frame_time() == 0 )
            {
                play_sfx(4);
                field_190 = 1;
                //sub_479FF0(v3, 200, 60);
                //add_card_energy(v3, 50);
                if ( field_7D8 == 1 )
                {
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

            if ( viz.process() )
                set_seq(0);

            if ( viz.get_subseq() == 5 && viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 )
                set_seq(9);
            else if ((viz.get_subseq() == 1 && viz.get_elaps_frames() > 4 && (not_charge_attack == 0 || viz.get_elaps_frames() > 25)) ||
                     (viz.get_subseq() == 4 && viz.get_elaps_frames() > 12))
                next_subseq();
            else if (viz.get_subseq() == 5 && viz.get_frame_time() == 0 && viz.get_frame() == 5 )
                v_force = 0.6;
        }
        break;
        case 416:
          if ( viz.get_subseq() == 1 )
            sub10func(this);
          if ( viz.get_subseq() == 0 )
          {
            v_inerc -= v_force;
            if ( char_on_ground_down(this) )
            {
              viz.next_subseq();
              y = getlvl_height(this);
              reset_forces();
              break;
            }
          }

          if ( viz.process() )
            set_seq(0);

          if (viz.get_subseq() == 1 && viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0)
            set_seq(9);
          else if ( viz.get_subseq() == 0 && viz.get_frame_time() == 0 &&  viz.get_frame() == 5 )
              {
                play_sfx(2);
                h_inerc = -4.0;
                v_inerc = 8.0;
                v_force = 0.5;
                /*v1748 = 60.0;
                v1749 = 0.0;
                v1750 = 0.0;
                v3->field_190 = 1;
                sub_479FF0(v3, 200, 60);
                add_card_energy(v3, 50);
                v449 = v3->rend_cls.dir;
                v450 = v3->rend_cls.y_pos + 30.0;
                v451 = v450;
                v452 = (30 * v449) + v3->rend_cls.x_pos;
                sub_46E2F0(v3, 801, v452, v451, v449, 1, &v1748, 3);*/
              }
          break;
        case 418:
          sub10func(this);

          h_inerc -= 0.5;
          if ( h_inerc < 0.0 )
            h_inerc = 0.0;

          if ( viz.process() )
            set_seq(0);

          if ( viz.get_frame_time() == 0 )
          {
            if (viz.get_frame() == 4)
            {
              /*v1643 = 0.0;
              v1644 = 0.0;
              v1645 = 0.0;
              sub_46E2F0(v3, 848, v3->rend_cls.x_pos, v3->rend_cls.y_pos, v3->rend_cls.dir, 1, &v1643, 3);*/
            }
            else if ( viz.get_frame() == 5 )
              {
                scene_play_sfx(29);
                field_49A = 0;
              }
          }
          break;
    case 521:
    {

        uint32_t sq = viz.get_subseq();

        if ( !sq || sq == 4 )
        {
            sub10func(this);
        }
        //field_18C = 1;
        if ( sq == 1 )
        {
            if ( viz.get_elaps_frames() > 20 )
            {
                viz.next_subseq();
            }
            /*if ( !(viz.get_elaps_frames() % 3) )
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

        sq = viz.get_subseq();

        if ( sq > 0  && sq < 4 )
        {
            v_inerc -= 0.75;
            h_inerc -= 0.4;
            if ( h_inerc < 0)
                h_inerc = 0;
        }

        if ( sq == 3 && char_on_ground_down(this) )
        {
            viz.next_subseq();
            y = getlvl_height(this);
            reset_forces();
        }

        if ( viz.process() )
            set_seq(0);

        if (viz.get_subseq() == 1 && viz.get_frame_time()   == 0 &&
                viz.get_frame()  == 0 && viz.get_elaps_frames() == 0)
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
        viz.process();
    }
}


bool sub_487110(char_c *chr)
{
    if ( chr->gY() > 0)
    {
        if ( chr->gX(chr->dir) > 0 )
        {
            chr->angZ = 0.0;
            chr->set_seq(209);
            return true;
        }
        else if ( chr->gX(chr->dir) < 0 )
        {
            chr->angZ = 0.0;
            chr->set_seq(210);
            return true;
        }
        else
        {
            chr->angZ = 0.0;
            chr->set_seq(208);
            return true;
        }
    }

    return false;
}

bool sub_4871A0(char_c *chr)
{
    if ( chr->pres_move & 0x20  && chr->field_80E == 0)
        if (  chr->get_seq() >= 150  && chr->get_seq() <= 157 && (chr->max_spell_energy >= 200 || chr->weather_var == 0) )
        {
            if ( chr->gY() <= 0 )
            {
                chr->angZ = 0.0;
                if ( chr->gX(chr->dir) <= 0 )
                    chr->set_seq(224);
                else
                    chr->set_seq(223);
                //if ( v1->weather_var? )
                // sub_463160(v1, 1);
                return true;
            }
            else
            {
                chr->angZ = 0.0;
                if ( chr->gX(chr->dir) >= 0 )
                    chr->set_seq(220);
                else
                    chr->set_seq(222);
                //if ( chr->weather_var )
                // sub_463160(v1, 1);
                return true;
            }
        }
    return false;
}

bool sub_4896A0(char_c *chr, uint16_t cprior, uint32_t flag_200000)
{
    if ( (chr->pres_move & 4) || (chr->gY() > 0 && chr->gX(chr->dir)==0 && (chr->keyDown(INP_D) || cprior >= 40)) )
        if ( cprior <= chr->get_prior(208) || flag_200000 )
            if ( chr->field_sq_check() )
            {
                chr->angZ = 0.0;
                chr->set_seq(208);
                return true;
            }
    if ( chr->pres_move & 0x10 || (chr->gY() > 0 && chr->gX(chr->dir) > 0 && (chr->keyDown(INP_D) || cprior >= 40)))
        if ( cprior <= chr->get_prior(209) || flag_200000 )

            if ( chr->field_sq_check())
            {
                chr->angZ = 0.0;
                chr->set_seq(209);
                return true;
            }


    if ( chr->pres_move & 0x8 || (chr->gY() > 0 && chr->gX(chr->dir) < 0 && (chr->keyDown(INP_D) || cprior >= 40)))
        if ( cprior <= chr->get_prior(210) || flag_200000)
            if ( chr->field_sq_check())
            {
                chr->angZ = 0.0;
                chr->set_seq(210);
                return true;
            }
    return false;
}

bool sub_489A30(char_c *chr, uint16_t cprior, uint32_t flag_200000)
{
    if ( ((chr->pres_move & 1 && chr->dir == 1)
            || (chr->pres_move & 2 && chr->dir == -1)
            || (chr->keyDown(INP_D) && chr->gY() == 0 && chr->gX(chr->dir) > 0))
            && chr->get_seq() != 204
            && cprior <= chr->get_prior(200)
            && chr->field_sq_check())
    {
        chr->angZ = 0.0;
        chr->set_seq(200);
        return true;
    }
    else if (((chr->pres_move & 2 && chr->dir == 1)
              || (chr->pres_move & 1 && chr->dir == -1)
              || (chr->keyDown(INP_D) && chr->gY() == 0 && chr->gX(chr->dir) < 0))
             && cprior <= chr->get_prior(201)
             && chr->field_sq_check())
    {
        chr->angZ = 0.0;
        chr->set_seq(201);
        return true;
    }
    return false;
}


bool sub_4872C0(char_c *chr)
{
    if ( (chr->pres_move & 0x20) != 0  && chr->field_80E == 0 && chr->get_seq() == 158 &&
            (chr->max_spell_energy >= 200 || chr->weather_var==0 ))
    {
        chr->angZ = 0.0;
        if ( chr->gX(chr->dir) > 0 )
        {
            chr->set_seq(226);
            //if ( chr->weather_var == 0 )
            //sub_463160(v1, 1);
            return 1;
        }
        else
        {
            chr->set_seq(225);
            //if ( v1->weather_var? )
            //sub_463160(v1, 1);
            return true;
        }
    }
    return false;
}

bool sub_489B90(char_c *chr, uint16_t cprior, uint32_t flag_200000, int8_t max_dash, uint16_t subse)
{
    if ( (chr->air_dash_cnt < max_dash
            && (chr->get_seq() != 202 || chr->get_subseq() >= subse)
            && (chr->pres_move & 1) != 0 && chr->dir == 1)
            ||
            ((chr->pres_move & 2) != 0 && chr->dir == -1
             && (cprior <= chr->get_prior(202) || flag_200000)
             && (chr->v_inerc <= 0.0 || chr->y > 100.0)
             && chr->field_sq_check()))
    {
        chr->angZ = 0.0;
        chr->set_seq(202);
        chr->air_dash_cnt++;
        return true;
    }
    return false;
}

bool sub_489C80(char_c *chr, uint16_t cprior, uint32_t flag_200000, int8_t max_dash, uint16_t subse)
{
    if ( (chr->air_dash_cnt < max_dash
            && (chr->get_seq() != 202 || chr->get_subseq() >= subse)
            && (chr->pres_move & 1) != 0 && chr->dir == 1)
            ||
            ((chr->pres_move & 2) != 0 && chr->dir == -1
             && (cprior <= chr->get_prior(202) || flag_200000)
             && (chr->v_inerc <= 0.0 || chr->y > 100.0)
             && chr->field_sq_check()))
    {
        chr->angZ = 0.0;
        chr->set_seq(203);
        chr->air_dash_cnt++;
        return true;
    }
    return false;
}

bool sub_489D70(char_c *chr, uint16_t cprior, uint32_t flag_200000, int8_t max_dash)
{
    if ( chr->air_dash_cnt < max_dash
            && chr->keyDown(INP_D)
            && (chr->gX(chr->dir) != 0 || chr->gY() != 0)
            && (chr->v_inerc <= 0.0 || chr->y > 100.0)
            && (cprior <= chr->get_prior(214) || flag_200000)
            && chr->field_sq_check() )
    {
        if ( chr->gY() < 0 )
        {
            if (chr->gX(chr->dir) > 0)
                chr->dash_angle = -45.0;
            else if( chr->gX(chr->dir) < 0 )
                chr->dash_angle = -135.0;
            else
                chr->dash_angle = -90.0;
        }
        else if ( chr->gY() > 0 )
        {
            if (chr->gX(chr->dir) > 0)
                chr->dash_angle = 45.0;
            else if( chr->gX(chr->dir) < 0 )
                chr->dash_angle = 135.0;
            else
                chr->dash_angle = 90.0;
        }
        else
        {
            if (chr->gX(chr->dir) > 0)
                chr->dash_angle = 0.0;
            else if( chr->gX(chr->dir) < 0 )
                chr->dash_angle = 180.0;
            else
                chr->dash_angle = 0.0;
        }
        chr->angZ = 0;
        chr->air_dash_cnt++;
        chr->set_seq(214);
        return true;
    }

    return false;
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

    uint16_t cprior = viz.get_cprior();
    uint32_t fflags = viz.get_pframe()->fflags;

    bool cc = (fflags & FF_CANCELLEABLE) != 0;
    bool cu = (fflags & FF_UNK200000) != 0;
    int32_t sq = viz.get_seq_id();

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

            if (input->keyHit(INP_A))
            {
                if (char_on_ground_flag(this)) // On Ground
                {
                    if ( sq == 200 && input->gY() == 0 &&
                            input->gX(dir) > 0 &&
                            cprior <= viz.get_prior(305) )  // 66A
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
                            if ( input->gX(dir) > 0 && cprior <= viz.get_prior(304) ) // 3A
                            {
                                angZ = 0;
                                set_seq(304);
                                input->zero_input();
                                return;
                            }
                            else if (cprior <= viz.get_prior(303) ) // 2A
                            {
                                angZ = 0;
                                set_seq(303);
                                input->zero_input();
                                return;
                            }
                        }
                        else if (input->gY() == 0)
                        {
                            if ( input->gX(dir) > 0 && cprior <= viz.get_prior(302) ) // 6A
                            {
                                angZ = 0;
                                set_seq(302);
                                input->zero_input();
                                return;
                            }

                            float dst = fabs(x - enemy->x);

                            if ( dst > 90.0 && cprior <= viz.get_prior(301)) //Far A
                            {
                                angZ = 0;
                                set_seq(301);
                                input->zero_input();
                                return;
                            }
                            else if(cprior <= viz.get_prior(300)) //near A
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
//                                if ( cprior <= viz.get_prior(330) || sq == 330 )
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

                    if ( input->gY() > 0 && input->gX(dir) == 0 && cprior <= viz.get_prior(309) ) //j8A
                    {
                        angZ = 0;
                        set_seq(309);
                        input->zero_input();
                        return;
                    }
                    else if (input->gY() < 0 && input->gX(dir) >= 0 && cprior <= viz.get_prior(308)) //j2A
                    {
                        angZ = 0;
                        set_seq(308);
                        input->zero_input();
                        return;
                    }
                    else if ( input->gY() == 0 && input->gX(dir) > 0 && cprior <= viz.get_prior(307)) //j6A
                    {
                        angZ = 0;
                        set_seq(307);
                        input->zero_input();
                        return;
                    }
                    else if ( cprior <= viz.get_prior(306) ) //j5A
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
                        if ( input->gY() < 0 /*&& input->gX(dir) > 0*/ && cprior <= viz.get_prior(402) ) // 2B
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
                        else if ( input->gY() == 0  && input->gX(dir) > 0 && cprior <= viz.get_prior(401) )
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
                        else if (cprior <= viz.get_prior(400) )
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
                    if ( input->gY() < 0 && cprior <= viz.get_prior(404))
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
                    else if (cprior <= viz.get_prior(406))
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
                        if ( input->gY() < 0 /*&& input->gX(dir) > 0*/ && cprior <= viz.get_prior(412) ) // 2C
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
                        else if ( input->gY() == 0  && input->gX(dir) > 0 && cprior <= viz.get_prior(411) ) // 5C
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
                        else if (cprior <= viz.get_prior(410) )
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
                        if (input->gY() >= 0 && input->gX(dir) > 0 && cprior <= viz.get_prior(415))
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
                        else if (input->gY() < 0 && cprior <= viz.get_prior(416))
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
                        else if (cprior <= viz.get_prior(414))
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
 
}


void char_marisa::set_seq_params()
{
    switch(viz.get_seq_id())
    {
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








