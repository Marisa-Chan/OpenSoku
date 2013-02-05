#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "marisa.h"
#include <math.h>

char_marisa::char_marisa(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    pgp->load_dat("marisa",pal);
    char_loadsfx(this,"marisa");
};

void sub_4834F0(char_c *)
{
    // HACK
}

void sub_4873B0(char_c *chr, int32_t seq, int32_t smt)
{
    if ( smt >= 10 )
        chr->correction |= 8;

    chr->set_seq(seq);
    //input_push_pressed_to_buf(chr);
    chr->angZ = 0.0;
}


void char_marisa::func10()
{
    x_delta = 0;
    y_delta = 106;

    if ( field_892 <= 0 )
    {
        field_892 = 0;
        field_894 = 0;
        field_890 = 0;
        field_898 = 0.0;
        field_89C = 0.0;
    }
    else
    {
        if ( get_seq() >= 600 && get_seq() != 615)
        {
            field_892 = 0;
            field_894 = 0;
            field_890 = 0;
            field_898 = 0.0;
            field_89C = 0.0;
        }

        if ( get_seq() != 615 && field_890 != 50 )
        {
            field_892--;
            field_894--;
        }

        if ( health <= 0 || enemy->health <= 0 )
        {
            field_892 = 0;
            field_894 = 0;
            field_890 = 0;
        }

        if ( field_890 != 50 && (char_is_shock(this) || field_894 <= 0))
        {
            field_894 = 0;
            field_890 = 0;
        }

        if ( field_890 == 0 )
        {
            if ( field_89C > 3.0 )
            {
                field_89C -= 0.1;
                if ( field_89C < 3.0 )
                    field_89C = 3.0;
            }
            else if ( field_89C < 3.0 )
            {
                field_89C += 0.1;
                if ( field_89C > 3.0 )
                    field_89C = 3.0;
            }
        }
        else if ( field_890 >= 1 && field_890 <= 7 )
        {
            if ( field_89C > 12.0 )
            {
                field_89C -= 0.1;
                if ( field_89C < 12.0 )
                    field_89C = 12.0;
            }
            else if ( field_89C < 12.0 )
            {
                field_89C += 0.1;
                if ( field_89C > 12.0 )
                    field_89C = 12.0;
            }

            if (field_894 % 5 == 0 && field_890 == 1 && field_894 > 0)
                field_890 = scene_rand_rng(4) + 2;
        }
        else if ( field_890 == 8 )
        {
            if ( field_89C > 0.5 )
            {
                field_89C -= 0.1;
                if ( field_89C < 0.5 )
                    field_89C = 0.5;
            }
            else if ( field_89C < 0.5 )
            {
                field_89C += 0.1;
                if ( field_89C > 0.5 )
                    field_89C = 0.5;
            }
        }
        else if (field_890 == 50)
        {
            if ( field_89C > 12.0 ) //HACK MAY BE 3
            {
                field_89C -= 0.1;
                if ( field_89C < 3.0 )
                    field_89C = 12.0;
            }
            else if ( field_89C < 12.0 )
            {
                field_89C += 0.1;
                if ( field_89C > 3.0 )
                    field_89C = 12.0;
            }
        }
        field_898 -= field_89C;
    }

    if ( get_seq() >= 150 && get_seq() < 159 && bbarrier_show == false)
    {
        bbarrier_show = true;
        if ( get_seq() >= 150 && get_seq() < 154)
            addbullet(this,NULL,998, x + dir*57, y + 94, dir, 1, NULL, 0);
        else if ( get_seq() >= 154 && get_seq() < 158)
            addbullet(this,NULL,998, x + dir*57, y + 60, dir, 1, NULL, 0);
        else if ( get_seq() == 158)
            addbullet(this,NULL,998, x + dir*57, y + 100, dir, 1, NULL, 0);
    }

    if ( hit_stop != 0 || enemy->time_stop != 0 )
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
    case 197:
        if ( (get_seq() == 0 && get_frame() <= 4) || get_subseq() == 2 )
            sub10func(this);
        if ( get_subseq() < 2 )
            v_inerc -= v_force;
        if ( char_on_ground_down(this) && get_subseq() < 2 )
        {
            y = getlvl_height(this);
            reset_forces();
            set_subseq(2);
        }
        else
        {
            if (process())
            {
                if ( controlling_type == 2)
                {
                    set_seq(700);
                    field_51C = 3;
                    field_520 = 3;
                }
                else
                {
                    set_seq(0);
                    if ( gY() < 0 )
                        set_seq(1);
                }
            }
            else
            {
                if ( get_subseq() == 2 && get_frame() == 3 && get_frame_time() == 0)
                {
                    if ( enemy->x < x )
                        dir = -1;
                    if ( enemy->x > x )
                        dir = 1;
                }
                if ( get_subseq() == 0 && get_frame() == 5 && get_frame_time() == 0)
                {
                    v_inerc = 6.0;
                    h_inerc = 14.5;
                    v_force = 0.5;
                }
            }
        }
        break;

    case 198:
        if ( (get_subseq() == 0 && get_frame() <= 3) || get_subseq() == 2 )
            sub10func(this);
        if ( get_subseq() < 2 )
            v_inerc -= v_force;
        if ( char_on_ground_down(this) && get_subseq() < 2 )
        {
            y = getlvl_height(this);
            reset_forces();
            set_subseq(2);
        }
        else
        {
            if (process())
            {

                if ( controlling_type == 2)
                {
                    set_seq(700);
                    field_51C = 3;
                    field_520 = 3;
                }
                else
                {
                    set_seq(0);
                    if ( gY() < 0 )
                        set_seq(1);
                }
            }
            else
            {
                if ( get_subseq() == 2 && get_frame() == 3 && get_frame_time() == 0)
                {
                    if ( enemy->x < x )
                        dir = -1;
                    if ( enemy->x > x )
                        dir = 1;
                }
                if ( get_subseq() == 0 && get_frame() == 4 && get_frame_time() == 0)
                {
                    v_inerc = 6.0;
                    h_inerc = 14.5;
                    v_force = 0.5;
                }
            }
        }
        break;
    case 199:
        sub10func(this);
        if ( process() )
        {

            if ( controlling_type == 2 )
            {
                set_seq(700);

                field_51C = 3;
                field_520 = 3;
            }
            else
            {
                set_seq(0);
                if ( gY() < 0)
                    set_seq(1);
            }
        }
        else if ( get_frame_time() == 0  && get_frame() == 12)
        {
            if (enemy->x < x)
                dir = -1;
            else
                dir = 1;
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
            {
                set_seq(9);
                break;
            }
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
                        angZ = 180 -angZ;
                    //angZ = 180.0 + dash_angle;

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
        field_18C = 1;
        if ( sq == 1 )
        {
            if ( get_elaps_frames() > 20 )
            {
                next_subseq();
            }
            if ( !(get_elaps_frames() % 3) )
            {
              float tmp[3];
              tmp[0] = scene_rand_rng(60) + 95.0 - 30.0;
              tmp[1] = scene_rand_rng(100) * 0.1 + 10.0;
              tmp[2] = scene_rand() & 3;
              addbullet(this,NULL,810,40*dir + x, y+51, dir, 1, tmp, 3);
            }
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
        char_c::func10();
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
               //class->func2_set_seq(v1, LOWORD(pres_comb));
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
            if (field_524 == 0)
            {
                if (input->keyHit(INP_BC))
                {
                    if (char_on_ground_flag(this))
                    {

                    }
                    else
                    {

                    }
                }

                if (pres_comb && spell200_seq299_300_field190_0_3(this) )
                {
                    if (char_on_ground_flag(this))
                    {
                        if ( spell200_seq299_300_field190_0_3(this) )

                            if ( pres_comb & PCOMB_623C )
                            {
                                if ( field_6AD >= 1 )
                                {
                                    if ( cprior <= get_prior(531) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                    {
                                        if ( field_801 == 0 )
                                        {
                                            field_4C8++;
                                            field_801 = 1;
                                        }
                                        sub_4834F0(this);
                                        sub_4873B0(this, 531, cprior);
                                        return;
                                    }
                                }
                                if ( field_6A9 >= 1 )
                                {
                                    if ( cprior <= get_prior(526) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                    {
                                        if ( field_801 == 0)
                                        {
                                            field_4C8++;
                                            field_801 = 1;
                                        }
                                        sub_4834F0(this);
                                        sub_4873B0(this, 526, cprior);
                                        return;
                                    }
                                }
                                if ( cprior <= get_prior(521) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 521, cprior);
                                    return;
                                }
                            }
                        if ( pres_comb & PCOMB_623B )
                        {
                            if ( field_6AD >= 1 )
                            {
                                if ( cprior <= get_prior(530) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 530, cprior);
                                    return;
                                }
                            }
                            if ( field_6A9 >= 1 )
                            {
                                if ( cprior <= get_prior(525) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 525, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(520) || (sq >= 500 && sq <= 599 && field_801 == 0))
                            {
                                if ( field_801 == 0)
                                {
                                    field_4C8++;
                                    field_801 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 520, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236C )
                        {
                            if ( field_6AF >= 1 )
                            {
                                if ( cprior <= get_prior(571) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 571, cprior);
                                    return;
                                }
                            }
                            if ( field_6AB >= 1 )
                            {
                                if ( cprior <= get_prior(566) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 566, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(561) || (sq >= 500 && sq <= 599 && field_803 == 0))
                            {
                                if ( field_803 == 0)
                                {
                                    field_4C8++;
                                    field_803 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 561, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236B )
                        {
                            if ( field_6AF >= 1 )
                            {
                                if ( cprior <= get_prior(570) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 570, cprior);
                                    return;
                                }
                            }
                            if ( field_6AB >= 1 )
                            {
                                if ( cprior <= get_prior(565) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 565, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(560) || (sq >= 500 && sq <= 599 && field_803 == 0))
                            {
                                if ( field_803 == 0)
                                {
                                    field_4C8++;
                                    field_803 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 560, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214C )
                        {
                            if ( field_6AC >= 1 )
                            {
                                if ( cprior <= get_prior(511) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 511, cprior);
                                    return;
                                }
                            }
                            if ( field_6A8 >= 1 )
                            {
                                if ( cprior <= get_prior(506) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 506, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(500) || (sq >= 500 && sq <= 599 && field_800 == 0))
                            {
                                if ( field_800 == 0)
                                {
                                    field_4C8++;
                                    field_800 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 500, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214B )
                        {
                            if ( field_6AC >= 1 )
                            {
                                if ( cprior <= get_prior(510) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 510, cprior);
                                    return;
                                }
                            }
                            if ( field_6A8 >= 1 )
                            {
                                if ( cprior <= get_prior(505) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 505, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(500) || (sq >= 500 && sq <= 599 && field_800 == 0))
                            {
                                if ( field_800 == 0)
                                {
                                    field_4C8++;
                                    field_800 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 500, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_2N2C )
                        {
                            if ( field_6AE >= 1 )
                            {
                                if ( cprior <= get_prior(551) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 551, cprior);
                                    return;
                                }
                            }
                            if ( field_6AA >= 1 )
                            {
                                if ( cprior <= get_prior(546) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 546, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(541) || (sq >= 500 && sq <= 599 && field_802 == 0))
                            {
                                if ( field_802 == 0)
                                {
                                    field_4C8++;
                                    field_802 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 541, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_2N2B )
                        {
                            if ( field_6AE >= 1 )
                            {
                                if ( cprior <= get_prior(550) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 550, cprior);
                                    return;
                                }
                            }
                            if ( field_6AA >= 1 )
                            {
                                if ( cprior <= get_prior(545) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 545, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(540) || (sq >= 500 && sq <= 599 && field_802 == 0))
                            {
                                if ( field_802 == 0)
                                {
                                    field_4C8++;
                                    field_802 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 540, cprior);
                                return;
                            }
                        }
                    }
                    else // Air specials
                    {
                        if ( pres_comb & PCOMB_236C )
                        {
                            if ( field_6AF >= 1 )
                            {
                                if ( cprior <= get_prior(573) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 573, cprior);
                                    return;
                                }
                            }
                            if ( field_6AB >= 1 )
                            {
                                if ( cprior <= get_prior(568) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 568, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(563) || (sq >= 500 && sq <= 599 && field_803 == 0))
                            {
                                if ( field_803 == 0)
                                {
                                    field_4C8++;
                                    field_803 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 563, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236B )
                        {
                            if ( field_6AF >= 1 )
                            {
                                if ( cprior <= get_prior(572) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 572, cprior);
                                    return;
                                }
                            }
                            if ( field_6AB >= 1 )
                            {
                                if ( cprior <= get_prior(567) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 567, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(562) || (sq >= 500 && sq <= 599 && field_803 == 0))
                            {
                                if ( field_803 == 0)
                                {
                                    field_4C8++;
                                    field_803 = 1;
                                }
                                sub_4834F0(this);
                                sub_4873B0(this, 562, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214C )
                        {
                            if ( field_6AC >= 1 )
                            {
                                if ( cprior <= get_prior(513) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 513, cprior);
                                    return;
                                }
                            }
                            if ( field_6A8 >= 1 )
                            {
                                if ( cprior <= get_prior(506) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 506, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(500) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 500, cprior);
                                    return;
                                }
                        }
                        if ( pres_comb & PCOMB_214B )
                        {
                            if ( field_6AC >= 1 )
                            {
                                if ( cprior <= get_prior(512) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 512, cprior);
                                    return;
                                }
                            }
                            if ( field_6A8 >= 1 )
                            {
                                if ( cprior <= get_prior(505) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 505, cprior);
                                    return;
                                }
                            }
                            if ( cprior <= get_prior(500) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 500, cprior);
                                    return;
                                }
                        }
                        if ( pres_comb & PCOMB_2N2C )
                        {
                            if ( field_6AE >= 2 )
                            {
                                if ( cprior <= get_prior(553) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 553, cprior);
                                    return;
                                }
                            }
                            if ( field_6AA >= 2 )
                            {
                                if ( cprior <= get_prior(548) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 548, cprior);
                                    return;
                                }
                            }
                            if ( field_6AA == 0 && field_6AE == 0)
                                {
                                    if ( cprior <= get_prior(543) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                    {
                                        if ( field_802 == 0)
                                        {
                                            field_4C8++;
                                            field_802 = 1;
                                        }
                                        sub_4834F0(this);
                                        sub_4873B0(this, 543, cprior);
                                        return;
                                    }
                                }
                        }
                        if ( pres_comb & PCOMB_2N2B )
                        {
                            if ( field_6AE >= 2 )
                            {
                                if ( cprior <= get_prior(552) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 552, cprior);
                                    return;
                                }
                            }
                            if ( field_6AA >= 2 )
                            {
                                if ( cprior <= get_prior(547) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0(this);
                                    sub_4873B0(this, 547, cprior);
                                    return;
                                }
                            }
                            if ( field_6AA == 0 && field_6AE == 0)
                                {
                                    if ( cprior <= get_prior(542) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                    {
                                        if ( field_802 == 0)
                                        {
                                            field_4C8++;
                                            field_802 = 1;
                                        }
                                        sub_4834F0(this);
                                        sub_4873B0(this, 542, cprior);
                                        return;
                                    }
                                }
                        }
                    }
                }
            }

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
                else if ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) // In Air (Melee)
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


        }
    }
    /*
      v10 = pressed_BC;
      if ( !v9 )
      {
        if ( (v10 && v10 < 3 || is_pressed_BC_1) && sub_468660(v1, 0) && !field_836 )
        {
          cprior = v147;
          if ( sub_489F10(v1, *&v147) )
            return;
          if ( *get_carduse_cost(&field_5E8, 0) >= 100 )
          {
            if ( *get_carduse_cost(&field_5E8, 0) <= 199 )
            {
              if ( v147 <= 50 )
              {
                if ( (v12 = playing_seq, v12 > 299) && (v13 = field_190, v13 != 3) && v13 || v12 < 300 )
                {
                  switch ( *get_carduse_cost(&field_5E8, 0) )
                  {
                    case 100:
                      if ( !field_800 )
                      {
                        ++field_4C8;
                        field_800 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v14);
                      sub_4873B0(this, 500, v147);
                      break;
                    case 101:
                      if ( !field_801 )
                      {
                        ++field_4C8;
                        field_801 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v15);
                      sub_4873B0(this, 520, v147);
                      break;
                    case 102:
                      if ( !field_802 )
                      {
                        ++field_4C8;
                        field_802 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v16);
                      sub_4873B0(this, 540, v147);
                      break;
                    case 103:
                      if ( !field_803 )
                      {
                        ++field_4C8;
                        field_803 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v17);
                      sub_4873B0(this, 560, v147);
                      break;
                    case 104:
                      if ( !field_800 )
                      {
                        ++field_4C8;
                        field_800 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v18);
                      sub_4873B0(this, 505, v147);
                      break;
                    case 105:
                      if ( !field_801 )
                      {
                        ++field_4C8;
                        field_801 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v19);
                      sub_4873B0(this, 525, v147);
                      break;
                    case 106:
                      if ( !field_802 )
                      {
                        ++field_4C8;
                        field_802 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v20);
                      sub_4873B0(this, 545, v147);
                      break;
                    case 107:
                      if ( !field_803 )
                      {
                        ++field_4C8;
                        field_803 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v21);
                      sub_4873B0(this, 565, v147);
                      break;
                    case 108:
                      if ( !field_800 )
                      {
                        ++field_4C8;
                        field_800 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v22);
                      sub_4873B0(this, 510, v147);
                      break;
                    case 109:
                      if ( !field_801 )
                      {
                        ++field_4C8;
                        field_801 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v23);
                      sub_4873B0(this, 530, v147);
                      break;
                    case 110:
                      if ( !field_802 )
                      {
                        ++field_4C8;
                        field_802 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v24);
                      sub_4873B0(this, 550, v147);
                      break;
                    case 111:
                      if ( !field_803 )
                      {
                        ++field_4C8;
                        field_803 = 1;
                      }
                      sub_4834F0(this);
                      sub_488E70(v1, v25);
                      sub_4873B0(this, 570, v147);
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
            if ( *get_carduse_cost(&field_5E8, 0) >= 200 )
            {
              if ( *get_carduse_cost(&field_5E8, 0) <= 299 )
              {
                if ( !pressed_x_axis )
                {
                  if ( (v26 = playing_seq, v26 > 299) && (v27 = field_190) != 0 && v27 != 3 || v26 < 300 )
                  {
                    switch ( *get_carduse_cost(&field_5E8, 0) )
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
                        if ( BYTE2(field_8A6) )
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
          cprior = cprior;
        }
    LABEL_108:

        goto LABEL_503;
      }
      if ( (v10 && v10 < 3 || is_pressed_BC_1) && sub_468660(v1, 0) && !field_836 )
      {
        if ( *get_carduse_cost(&field_5E8, 0) < 100 || *get_carduse_cost(&field_5E8, 0) > 199 )
        {
          cprior = v147;
        }
        else
        {
          cprior = v147;
          if ( v147 <= 50 )
          {
            if ( (v52 = playing_seq, v52 > 299) && (v53 = field_190, v53 != 3) && v53 || v52 < 300 )
            {
              switch ( *get_carduse_cost(&field_5E8, 0) )
              {
                case 100:
                  if ( !field_800 )
                  {
                    ++field_4C8;
                    field_800 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v54);
                  sub_4873B0(this, 500, v147);
                  break;
                case 102:
                  if ( !field_802 )
                  {
                    ++field_4C8;
                    field_802 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v55);
                  sub_4873B0(this, 542, v147);
                  break;
                case 103:
                  if ( !field_803 )
                  {
                    ++field_4C8;
                    field_803 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v56);
                  sub_4873B0(this, 562, v147);
                  break;
                case 104:
                  if ( !field_800 )
                  {
                    ++field_4C8;
                    field_800 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v57);
                  sub_4873B0(this, 505, v147);
                  break;
                case 106:
                  if ( SBYTE2(field_6A8) < 1 )
                    goto LABEL_341;
                  if ( !field_802 )
                  {
                    ++field_4C8;
                    field_802 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v58);
                  sub_4873B0(this, 547, v147);
                  break;
                case 107:
                  if ( !field_803 )
                  {
                    ++field_4C8;
                    field_803 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v59);
                  sub_4873B0(this, 567, v147);
                  break;
                case 108:
                  if ( !field_800 )
                  {
                    ++field_4C8;
                    field_800 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v60);
                  sub_4873B0(this, 512, v147);
                  break;
                case 110:
                  if ( SBYTE2(field_6AC) < 1 )
                    goto LABEL_341;
                  if ( !field_802 )
                  {
                    ++field_4C8;
                    field_802 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v61);
                  sub_4873B0(this, 552, v147);
                  break;
                case 111:
                  if ( !field_803 )
                  {
                    ++field_4C8;
                    field_803 = 1;
                  }
                  sub_4834F0(this);
                  sub_488E70(v1, v62);
                  sub_4873B0(this, 572, v147);
                  break;
                default:
                  goto LABEL_341;
              }
              return;
            }
          }
        }
    LABEL_341:
        if ( cprior <= 100 )
        {
          if ( *get_carduse_cost(&field_5E8, 0) >= 200 )
          {
            if ( *get_carduse_cost(&field_5E8, 0) <= 299 )
            {
              if ( !pressed_x_axis )
              {
                if ( (v63 = playing_seq, v63 > 299) && (v64 = field_190) != 0 && v64 != 3 || v63 < 300 )
                {
                  switch ( *get_carduse_cost(&field_5E8, 0) )
                  {
                    case 203:
                      sub_487370(v1, 603, cprior);
                      break;
                    case 205:
                      sub_487370(v1, 605, cprior);
                      break;
                    case 207:
                      sub_487370(v1, 607, cprior);
                      break;
                    case 208:
                      sub_487370(v1, 658, cprior);
                      break;
                    case 211:
                      sub_487370(v1, 611, cprior);
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
        cprior = v147;
      }
    LABEL_356:
      if ( sub_4870D0(v1) )
      {

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
        v_force = 0.6;
        field_7DC = 12.0;
        field_7EC = 0.0;
        x_off = 0;
        y_off = 95;
        break;
    case 300:
    case 301:
    case 303:
    case 321:
    case 322:
    case 330:
        if ( field_49A == 0)
            reset_forces();
        field_190 = 0;
        field_194 = 1;
        break;
    case 302:
        if ( field_49A == 0)
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
        field_190 = 0;
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








