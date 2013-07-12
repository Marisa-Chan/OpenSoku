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
    char_id = CHAR_ID_MARISA;
    pgp->load_dat("marisa",pal);
    char_loadsfx("marisa");
    cards_load_cards(&chr_cards,"marisa");
    load_face("marisa");
    load_spells("marisa");
    stand_gfx->init(this,"marisa");
}

void char_marisa::init_vars()
{
    field_898 = 0.0;
    field_890 = 0;
    field_89C = 0.0;
    field_892 = 0;
    field_8A0 = 0.0;
    field_894 = 0;
    field_8A4 = 0.0;
    field_8A8 = 0;
    field_138 = -6.0;
    char_c::init_vars();
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

        if ( field_890 != 50 && (char_is_shock() || field_894 <= 0))
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
        char_h_move( -5.0);
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
            v_inerc = 16.0;
            v_force = 0.75;
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
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move( 5.0);
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
            v_inerc = 16.0;
            v_force = 0.75;
            char_h_move( -4.0);
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
    case 197:
        if ( (get_seq() == 0 && get_frame() <= 4) || get_subseq() == 2 )
            sub10func();
        if ( get_subseq() < 2 )
            v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 2 )
        {
            y = getlvl_height();
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
            sub10func();
        if ( get_subseq() < 2 )
            v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 2 )
        {
            y = getlvl_height();
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
        sub10func();
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
        sub10func();
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
            char_h_move( 15.0);
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
            sub10func();

        if ( get_subseq() == 3 )
        {
            h_inerc += 2.0;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( !char_on_ground_flag() )
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
            if ( char_on_ground_down() )
            {
                v_inerc = 0.0;
                v_force = 0.0;
                y = getlvl_height();
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
            char_h_move( -14.0);
            v_inerc = 4.0;
            v_force = 0.5;
            scene_add_effect(this, 125, x, y+80, -dir,1);
            scene_add_effect(this, 126, x, y+80, -dir,1);
            scene_play_sfx(31);
        }
        break;
    case 202:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
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
                char_h_move( 11.0);
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
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
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
                char_h_move( -11.0);
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
        sub10func();
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
            sub10func();

        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
        }
        else
        {
            if ( char_on_ground_flag() || v_inerc > 0.0 )
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
                    //char_h_move( 0);
                    v_inerc = 22.5;
                    v_force = 0.85;
                }
                else if (sq == 209 || sq == 221)
                {
                    char_h_move( 10.0);
                    v_inerc = 18.0;
                    v_force = 0.85;
                }
                else if (sq == 210 || sq == 222)
                {
                    char_h_move( -10.0);
                    v_inerc = 18.0;
                    v_force = 0.85;
                }
                else if (sq == 211)
                {
                    char_h_move( 3.0);
                    v_inerc = 22.5;
                    v_force = 0.85;
                }
                else if (sq == 212)
                {
                    char_h_move( 10.0);
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
                        if ( weather_id != WEATHER_SUNNY )
                            dash_angle += 0.5;
                        else
                            dash_angle += 1.5;
                    }
                    else if ( field_7D4 < 0 )
                    {
                        if ( weather_id != WEATHER_SUNNY )
                            dash_angle -= 0.5;
                        else
                            dash_angle -= 1.5;
                    }

                    h_inerc = cos_deg(dash_angle) * field_7DC;
                    v_inerc = sin_deg(dash_angle) * field_7DC;

                    if ( y > 680.0 )
                        if ( v_inerc > 0.0 )
                            v_inerc = 0.0;

                    field_7DC += 0.3;
                    if ( field_7DC > 12.0 )
                        field_7DC = 12.0;

                    spell_energy_spend( weather_id != WEATHER_SUNNY ? 10 : 5, 1);
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
                        float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
                        float xx = cos_deg(dash_angle) * 100.0 * dir + x;
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
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
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
        sub10func();
        stopping(0.75);
        if ( process())
            set_seq(0);
        break;
    case 217:
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

            field_7D2 = atan2_deg(enemy->y + 100.0 - y, enemy->x - x * dir);
            if (get_subseq() == 5 || get_subseq() == 6)
                v_inerc -= v_force;
            if (get_subseq() > 0 && get_subseq() < 5)
            {
                field_7D6++;
                field_7D4 = field_7D2 - dash_angle;
                if (field_7D4 > 180)
                    field_7D4 -= 360;
                else if (field_7D4 < -180)
                    field_7D4 += 360;

                if ( field_7D4 > 0 )
                {
                    if ( weather_id != WEATHER_SUNNY )
                        dash_angle += 0.25;
                    else
                        dash_angle += 0.75;
                }
                else if ( field_7D4 < 0 )
                {
                    if ( weather_id != WEATHER_SUNNY )
                        dash_angle -= 0.25;
                    else
                        dash_angle -= 0.75;
                }

                h_inerc = cos_deg(dash_angle) * field_7DC;
                v_inerc = sin_deg(dash_angle) * field_7DC;

                if ( y > 680.0 )
                    if ( v_inerc > 0.0 )
                        v_inerc = 0.0;

                field_7DC += 0.3;
                if ( field_7DC > 12.0 )
                    field_7DC = 12.0;

                if (weather_id == WEATHER_SUNNY)
                    spell_energy_spend(10, 1);
                else
                    spell_energy_spend(15, 60);

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
                    float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
                    float xx = cos_deg(dash_angle) * 100.0 * dir + x;
                    scene_add_effect(this, 125, xx, yy, dir, 1);
                }

                if ( (keyDown(INP_D) == 0 && field_7D6 > 20) || spell_energy <= 0 )
                {
                    reset_ofs();

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
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
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
    case 220:
        if ( get_subseq() == 0 )
            sub10func();

        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
        }
        else
        {
            if ( char_on_ground_flag() || v_inerc > 0.0 )
                field_522 = 2;
            if ( get_subseq() > 0 )
            {
                v_inerc -= v_force;
                if (v_inerc < -20.0)
                    v_inerc = -20.0;
            }

            if ( get_subseq() == 1 && v_inerc < 4.0 )
                set_subseq(2);

            process();

            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
            {
                char_h_move(0.0);
                v_inerc = 22.5;
                v_force = 0.85;
                field_49A = 0;

                scene_add_effect(this, 63, x, y, dir, 1);
            }
        }
        break;
    case 223:
        sub10func();
        field_49A = 1;
        process();
        if (get_subseq() == 1)
        {
            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && field_7D0 == 0)
            {
                char_h_move(7.5);
                scene_add_effect(this, 125, x + 80.0 * dir, y + 80.0, dir, 1);
                scene_add_effect(this, 126, x, y + 80.0, dir, 1);
                scene_play_sfx(31);
            }

            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), y + scene_rand_rngf(200), dir, 1);
            field_7D0++;

            if ( (gX(dir) <= 0 && field_7D0 > 15) || field_7D0 > 45)
                set_seq(204);
        }
        break;
    case 224:
        if ( get_subseq() == 0 || get_subseq() == 3 )
            sub10func();

        if ( get_subseq() == 3 )
        {
            h_inerc += 2.0;
            if (h_inerc > 0.0)
                h_inerc = 0.0;
        }
        if (!char_on_ground_flag() && get_elaps_frames() % 5 == 0)
            scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), y + scene_rand_rngf(200), dir, 1);

        if ( get_subseq() < 3 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                v_inerc = 0.0;
                v_force = 0.0;
                y = getlvl_height();
                set_subseq(3);
                break;
            }
        }
        if ( process() )
        {
            set_seq(0);
            h_inerc = 0.0;
            v_force = 0.0;
        }
        else
        {
            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
                if (field_7D0 == 0)
                {
                    field_7D0 = 1;
                    char_h_move(-14.0);
                    v_inerc = 4.0;
                    v_force = 0.5;

                    scene_add_effect(this, 125, x, y + 80.0, dir, 1);
                    scene_add_effect(this, 126, x, y + 80.0, dir, 1);
                    scene_play_sfx(31);
                }
        }
        break;
    case 225:
        if ( get_subseq() >= 1 )
            v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
            set_seq(10);
        }
        else
        {
            if (get_subseq() >= 2 && get_elaps_frames() % 5 == 0)
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), y + scene_rand_rngf(200), dir, 1);

            if ( process() )
                set_seq(9);

            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
            {
                char_h_move(-11.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x, y + 120.0, dir, 1);
                scene_add_effect(this, 126, x, y + 120.0, dir, 1);
                scene_play_sfx(31);
            }
        }
        break;
    case 226:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
            set_seq(10);
        }
        else
        {
            if ( get_subseq() == 1 && get_elaps_frames() % 5 == 0)
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), y + scene_rand_rngf(200), dir, 1);

            if ( process() )
                set_seq(9);

            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            {
                if (get_subseq() == 1)
                {
                    field_7D0 = 0;
                    char_h_move(11.0);
                    v_inerc = 4.0;
                    v_force = 0.5;

                    scene_add_effect(this, 125, x + 80.0 * dir, y + 110.0, dir, 1);
                    scene_add_effect(this, 126, x, y + 110.0, dir, 1);
                    scene_play_sfx(31);
                }
                else if (get_subseq() == 2)
                    flip_with_force();
            }
        }
        break;
    case 300: //near A-attack
    case 330:
        sub10func();
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
        sub10func();
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
            sub10func();

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
            if ( char_on_ground_down() )
            {
                play_sfx(18);
                if ( ssq == 2 )
                    set_subseq(4);
                else
                    set_subseq(5);

                y = getlvl_height();
                v_inerc = 0.0;
                h_inerc = 5.0;
            }
        }
        else if ( ssq == 4 || ssq == 5 )
            stopping_posit(0.5);
    }
    break;

    case 303:
        sub10func();
        stopping_posit(0.6);
        if ( process() )
            set_seq(2);
        if ( get_frame_time() == 0 )
            if ( get_frame() == 3 )
                scene_play_sfx(27);
        break;

    case 304:
        sub10func();
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
        sub10func();

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
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
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

        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
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

        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
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

        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
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
    case 310:
        if (get_subseq() == 2 )
        {
            h_inerc -= 1.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;

            sub10func();
        }
        else
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                set_subseq(2);
                y = getlvl_height();
                v_inerc = 0.0;
                v_force = 0.0;
                field_190 = 1;
            }
        }
        if ( process() )
        {
            if (gY() >= 0 )
                set_seq(3);
            else
                set_seq(2);
        }
        else if (get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 7)
            scene_play_sfx(29);
        break;
    case 320:
        sub10func();
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
        sub10func();
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
        sub10func();

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
        sub10func();

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
                    add_card_energy( 10);
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
                    add_card_energy( 10);
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
            spell_energy_spend( 200, 45);
        }
        break;

    case 401:
        sub10func();

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
                    add_card_energy( 10);
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
                    add_card_energy( 10);
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
            spell_energy_spend( 200, 45);
        }
        break;

    case 402:
        sub10func();
        if ( input->keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( field_7D0 >= 0)
        {

            field_7D0--;

            if (field_7D0 == 0 && get_subseq() < 4)
            {
                field_190 = 1;
                play_sfx(0);
                add_card_energy( 5);
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
            spell_energy_spend( 200, 45);
            scene_add_effect(this, 62, 90*dir + x, y+70, dir, 1);
        }
        break;

    case 404:
        if ( get_subseq() == 3 )
            sub10func();
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 3 )
        {
            set_subseq(3);
            air_dash_cnt = 0;
            y = getlvl_height();
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
                        add_card_energy( 10);
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
                        add_card_energy( 10);
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
                spell_energy_spend( 200, 45);
            }

            if ( get_subseq() == 3  && get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 )
                set_seq(9);
        }
        break;

    case 406:
        if ( get_subseq() == 3 )
            sub10func();
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 3 )
        {
            set_subseq(3);
            air_dash_cnt = 0;
            y = getlvl_height();
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
                        add_card_energy( 10);
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
                        add_card_energy( 10);
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
                spell_energy_spend( 200, 45);
            }
            if ( get_subseq() == 3  && get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 )
                set_seq(9);
        }
        break;
    case 408:
        sub10func();
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

        if ( char_on_ground_down() )
        {
            set_seq(10);
            reset_forces();
            y = getlvl_height();
        }
        else if ( process() )
            set_seq(9);

        break;
    case 410:
        sub10func();

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
            spell_energy_spend(200, 60);
            field_190 = 1;
            add_card_energy( 50);
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
        sub10func();

        if ( get_subseq() < 2 )
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy( 50);
            field_7D4 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);
            if ( field_7D4 < -10 )
                field_7D4 = -10;
            else if ( field_7D4 > 10 )
                field_7D4 = 10;

            play_sfx(4);
            field_190 = 1;
            spell_energy_spend( 200, 60);

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
        sub10func();

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
            spell_energy_spend( 200, 60);
            add_card_energy( 50);
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
            sub10func();

        v_inerc -= v_force;

        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
        }
        else
        {
            if ( input->keyDown(INP_C) == 0)
                not_charge_attack = 0;

            if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
            {
                spell_energy_spend( 200, 60);
                field_190 = 1;
                add_card_energy( 50);
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
            sub10func();

        v_inerc -= v_force;

        if ( char_on_ground_down() && get_subseq() < 6 )
        {
            set_subseq(6);
            air_dash_cnt = 0;
            y = getlvl_height();
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
                spell_energy_spend( 200, 60);
                add_card_energy( 50);
                if ( field_7D8 == 1 )
                {
                    float t[3];
                    t[0] = 0;
                    t[1] = 2;
                    t[2] = 4;
                    addbullet(this, NULL,803, 48*dir + x, y+104, dir, 1, t, 3);
                }
                else
                {
                    float t[3];
                    t[0] = 0;
                    t[1] = 2;
                    t[2] = 4;
                    addbullet(this, NULL,803, 48*dir + x, y+104, dir, 1, t, 3);
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
            sub10func();
        if ( get_subseq() == 0 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                next_subseq();
                y = getlvl_height();
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
            spell_energy_spend( 200, 60);
            add_card_energy( 50);

            float t[3];
            t[0] = 60;
            t[1] = 0;
            t[2] = 0;
            addbullet(this, NULL, 801, x+dir*30, y+30, dir, 1,t,3);
        }
        break;
    case 418:
        sub10func();

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
    case 420:
        sub10func();
        if ( process() )
            set_seq(0);

        if ( get_subseq() == 1 && get_elaps_frames() >= 2 )
            next_subseq();
        else if (get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2)
        {
            field_190 = 1;
            field_894 = 40;
            field_890 = 1;
            field_7D0 = 1;
            spell_energy_spend(200, 45);
        }
        break;
    case 421:
        sub10func();
        if ( process() )
            set_seq(2);
        else if (get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2)
        {
            field_190 = 1;
            field_894 = 40;
            field_890 = 1;
            field_7D0 = 1;
            spell_energy_spend(200, 45);
        }
        break;
    case 422:
        if ( get_subseq() == 3 )
            sub10func();

        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 3 )
        {
            set_subseq(3);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
        }
        else
        {
            if ( process() )
                set_seq(0);

            if ( get_subseq() == 1 && get_elaps_frames() >= 2 )
                next_subseq();
            else
            {
                if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
                {
                    field_190 = 1;
                    h_inerc = -6.0;
                    v_inerc = 6.0;
                    v_force = 0.5;
                    field_894 = 40;
                    field_890 = 1;
                    field_7D0 = 1;
                    spell_energy_spend(200, 45);
                }
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3)
                    set_seq(9);
            }
        }
        break;
    case 430:
        sub10func();
        if ( get_subseq() < 2  && keyDown(INP_C) == 0 )
            not_charge_attack = 0;

        if ( get_subseq() == 2  && get_frame() == 2 && get_frame_time() == 0)
        {
            spell_energy_spend(200, 60);
            field_894 = 60;
            field_890 = 8;
            field_190 = 1;
            add_card_energy(50);
        }

        if ( process() )
            set_seq(0);

        if ( (get_subseq() == 1 || get_subseq() == 3) && get_elaps_frames() > 10 )
            next_subseq();
        break;
    case 431:
        sub10func();
        if ( process() )
            set_seq(2);
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2)
        {
            field_190 = 1;
            field_894 = 60;
            field_890 = 8;
            field_7D0 = 1;
            spell_energy_spend(200,60);
        }
        if ( get_subseq() == 3 && get_elaps_frames() > 10)
            next_subseq();

        break;
    case 432:
        if ( get_subseq() == 5 )
            sub10func();

        v_inerc -= v_force;
        if (char_on_ground_down() && get_subseq() < 5)
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
        }
        else
        {
            if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2)
            {
                spell_energy_spend(200, 60);
                field_190 = 1;
                field_894 = 60;
                field_890 = 8;
                add_card_energy(50);
            }
            if ( process() )
                set_seq(0);
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5)
                set_seq(9);
            else
            {
                v_inerc -= 0.01;

                if ((get_subseq() == 1 && get_elaps_frames() > 10) || (get_subseq() == 3 && get_elaps_frames() > 20) )
                    next_subseq();
                else if (get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5)
                    v_force = 0.6;
            }
        }
        break;
    case 500:
        if ( get_subseq() == 5 )
            sub10func();

        field_18C = 0;
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() > 20 )
            {
                set_seq(504);
                break;
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rng(60) + 180 - 30;
                tmp[1] = 15;
                tmp[2] = scene_rand() & 3;
                addbullet(this, NULL, 810,x - dir*95, y+100, dir, 1, tmp, 3);
            }

            if ( field_190 != 0 && field_190 != 1 && field_190 != 3 )
            {
                next_subseq();
                h_inerc = -5.0;
                v_inerc = 10.0;
                v_force = 0.35;
                break;
            }
        }
        else if (get_subseq() >= 2 && get_subseq() <= 4)
        {
            v_inerc -= v_force;
            h_inerc += 0.1;
            if ( h_inerc > -1.0 )
                h_inerc = -1.0;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(5);
            }
        }

        if ( process() )
            set_seq(0);
        if (get_subseq() == 0 && get_frame_time() == 0 && skills_1[0] >= 2 && get_frame() == 8)
            next_subseq();
        if (get_elaps_frames() == 0 && get_frame() == 0 && get_frame_time() == 0)
        {
            if (get_subseq() == 1)
            {
                float tmp[3];
                tmp[0] = 0;
                tmp[1] = 0;
                tmp[2] = 0;
                addbullet(this,NULL, 849, x + 109*dir, y + 84, dir, 1, tmp, 3);
                if ( getlvl_height() == y )
                    scene_add_effect(this, 128, x + dir * 200, y, dir, -1);

                h_inerc = 20.0;
                spell_energy_spend( 200, 120);
                add_card_energy( 50);
                play_sfx(6);
            }
            else if (get_subseq() == 3)
            {
                if ( skills_1[0] >= 1 )
                    next_subseq();
            }
        }
        break;
    case 504:
        if ( get_subseq() == 3 )
            sub10func();

        field_18C = 0;
        if ( get_subseq() >= 0 && get_subseq() <= 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(3);
            }
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_subseq() == 1)
            if (skills_1[0] >= 1)
                next_subseq();
        break;
    case 505:
        if ( get_subseq() == 3 )
            sub10func();
        field_18C = 4;

        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(3);
            }
        }
        if ( process() )
            set_seq(0);

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            add_card_energy(50);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 27.5;
            if (skills_1[4] >= 3)
                tmp[1] = 35.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 811, x + 109.0 * dir, y + 84.0, dir, 1, tmp, 3);

            scene_add_effect(this, 127, x + 200.0 * dir, y, dir, -1);

            h_inerc = -7.5;
            v_inerc = 10.0;
            v_force = 0.55;
            spell_energy_spend(200, 120);
            play_sfx(26);
        }
        break;
    case 506:
        if ( get_subseq() == 3 )
            sub10func();
        field_18C = 4;
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(3);
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            add_card_energy(50);

            float t[3];
            t[0] = -20.0;
            if ( getlvl_height() < y )
                t[0] = 30.0;
            t[1] = 27.5;
            if (skills_1[4] >= 3)
                t[1] = 35;
            t[2] = 0.0;

            addbullet(this, NULL,811, x + 109.0 * dir, y + 84.0, dir, 1, t, 3);
            scene_add_effect(this, 127, x + 200.0*dir, y, dir, -1);

            h_inerc = -7.5;
            v_inerc = 10.0;
            v_force = 0.55;
            spell_energy_spend(200,120);
            play_sfx(26);
        }
        break;
    case 510:
    case 512:
        if ( get_subseq() == 4 )
            sub10func();
        field_18C = 8;
        if ( get_subseq() == 1 || get_subseq() == 2 || get_subseq() == 3 )
        {
            h_inerc -= 0.75;
            if (h_inerc < 2.0)
                h_inerc = 2.0;

            v_inerc -= v_force;

            if (get_subseq() == 1 && v_inerc <= -1.0)
                v_inerc = -1.0;

            if (char_on_ground_down())
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(4);
                angZ = 0.0;
            }
            if (get_subseq() == 1)
            {
                field_7DC += 2.0;
                angZ -= 25.0;
                if (angZ < -1080.0)
                {
                    next_subseq();
                    angZ = 0.0;
                    break;
                }
            }
            if (get_subseq() == 3 && get_elaps_frames() >= 24)
            {
                set_seq(9);
                break;
            }
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
        {
            float t[3];
            t[0] = 75.0;
            t[1] = 0.0;
            t[2] = 4.0;
            if (skills_1[8] >= 4)
                t[2] = 6.0;
            addbullet(this, NULL, 812, x, y + 135.0, dir, 1, t, 3);
            h_inerc = 17.5;
            v_inerc = 11.0;
            v_force = 0.45;
            spell_energy_spend(200,120);
            add_card_energy(50);
            play_sfx(6);
            setOrigin(0, 135);
        }
        break;
    case 511:
    case 513:
        if ( get_subseq() == 1 || get_subseq() == 2 || get_subseq() == 3 )
        {
            h_inerc -= 0.75;
            if ( h_inerc < 2.0 )
                h_inerc = 2.0;

            v_inerc -= v_force;
            if ( get_subseq() == 1 && v_inerc <= -1.0 )
                v_inerc = -1.0;

            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(4);
                angZ = 0.0;
            }
            if ( get_subseq() == 1 )
            {
                field_7DC += 2.0;
                angZ -= 25.0;
                if ( angZ < -1080.0 )
                {
                    next_subseq();
                    angZ = 0.0;
                    break;
                }
            }
            if ( get_subseq() == 3 && get_elaps_frames() >= 24 )
            {
                set_seq(9);
                break;
            }
        }
        if ( process() )
            set_seq(0);

        if (get_elaps_frames() == 0 && get_frame() == 0 && get_frame_time() == 0 && get_subseq() == 1)
        {
            float t[3];
            t[0] = 75.0;
            t[1] = 0.0;
            t[2] = 4.0;
            if ( skills_1[8] >= 4 )
                t[2] = 6.0;
            addbullet(this, NULL, 812, x, y + 135.0, dir, 1, t ,3);

            h_inerc = 25.0;
            v_inerc = 12.5;
            v_force = 0.45;
            spell_energy_spend(200, 120);
            add_card_energy(50);
            play_sfx(6);
            setOrigin(0, 135.0);
        }
        break;
    case 520:
    {
        uint32_t sq = get_subseq();

        if ( sq == 0 || sq == 4 )
            sub10func();

        field_18C = 1;

        if ( sq == 0 && skills_1[1] >= 1 )
            field_51C = 2;

        if ( sq == 1 )
        {
            if ( get_elaps_frames() > 20 )
                next_subseq();
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
            h_inerc -= 0.5;
            if ( h_inerc < 0)
                h_inerc = 0;
        }

        if ( get_subseq() == 3 && char_on_ground_down() )
        {
            next_subseq();
            y = getlvl_height();
            reset_forces();
        }

        if ( process() )
            set_seq(0);

        if (get_subseq() == 1 && get_frame_time()   == 0 &&
                get_frame()  == 0 && get_elaps_frames() == 0)
        {
            float tmp[3];
            tmp[0] = -85;
            tmp[1] = 0;
            tmp[2] = 1;
            addbullet(this,NULL,849, x + dir*61, y + 232, dir,1,tmp,3);
            scene_add_effect(this, 127, x, y, dir, -1);
            play_sfx(5);
            spell_energy_spend( 200, 120);
            add_card_energy( 50);
            h_inerc = 12.5;
            v_inerc = 17.5;
            v_force = 0.6;
            field_51C = 0;
        }
    }
    return;
    case 521:
    {
        uint32_t sq = get_subseq();

        if ( sq == 0 || sq == 4 )
        {
            sub10func();
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

        if ( get_subseq() == 3 && char_on_ground_down() )
        {
            next_subseq();
            y = getlvl_height();
            reset_forces();
        }

        if ( process() )
            set_seq(0);

        if (get_subseq() == 1 && get_frame_time()   == 0 &&
                get_frame()  == 0 && get_elaps_frames() == 0)
        {
            float tmp[3];
            tmp[0] = -85;
            tmp[1] = 0;
            tmp[2] = 1;
            addbullet(this,NULL,849, x + dir*61, y + 232, dir,1,tmp,3);
            scene_add_effect(this, 127, x, y, dir, -1);
            play_sfx(5);
            spell_energy_spend( 200, 120);
            add_card_energy( 50);
            h_inerc = 15.0;
            v_inerc = 25.0;
            v_force = 0.6;
        }

    }
    break;
    case 525:
        if ( get_subseq() == 0 || get_subseq() == 4 )
            sub10func();

        field_18C = 5;
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() > 20 )
            {
                next_subseq();
                v_inerc *= 0.5;
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float t[3];
                t[0] = scene_rand_rng(60) + 95.0 - 30.0;
                t[1] = scene_rand_rngf(50)* 0.1 + 5.0;
                t[2] = 3.0;

                addbullet(this, NULL, 810, x + 40.0 * dir, y + 51.0, dir, 1, t, 3);
            }
        }
        if ( get_subseq() > 0 && get_subseq() < 4 )
        {
            v_inerc -= 0.55;
            h_inerc -= 0.5;
            if (h_inerc < 0.0)
                h_inerc = 0;
        }
        if ( get_subseq() == 3 && char_on_ground_down() )
        {
            next_subseq();
            y = getlvl_height();
            reset_forces();
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
        {
            float t[3];
            t[0] = -85.0;
            t[1] = 0.0;
            if (skills_1[5] >= 4)
                t[2] = 5.0;
            if (skills_1[5] <= 3)
                t[2] = 4.0;
            if (skills_1[5] <= 1)
                t[2] = 3.0;

            addbullet(this, NULL, 849, x + 61.0 * dir, y + 232.0, dir, 1, t, 3);
            scene_add_effect(this, 127, x, y, dir, -1);
            play_sfx(28);
            spell_energy_spend(200,120);
            add_card_energy(50);
            h_inerc = 7.0;
            v_inerc = 17.5;
            v_force = 0.5;
            field_190 = 1;
        }
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3)
            field_190 = 1;
        break;
    case 526:
        if ( get_subseq() == 0 || get_subseq() == 4 )
            sub10func();

        field_18C = 5;
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() > 30 )
            {
                next_subseq();
                v_inerc *= 0.5;
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float t[3];
                t[0] = scene_rand_rng(60) + 95.0 - 30.0;
                t[1] = scene_rand_rngf(50)* 0.1 + 5.0;
                t[2] = 3.0;

                addbullet(this, NULL, 810, x + 40.0 * dir, y + 51.0, dir, 1, t, 3);
            }
        }
        if ( get_subseq() > 0 && get_subseq() < 4 )
        {
            v_inerc -= 0.55;
            h_inerc -= 0.5;
            if (h_inerc < 0.0)
                h_inerc = 0;
        }
        if ( get_subseq() == 3 && char_on_ground_down() )
        {
            next_subseq();
            y = getlvl_height();
            reset_forces();
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
        {
            if ( get_subseq() == 1 )
            {
                float t[3];
                t[0] = -85.0;
                t[1] = 0.0;
                if ( skills_1[5] <= 4 )
                    t[2] = 4.0;
                if ( skills_1[5] <= 2 )
                    t[2] = 3.0;

                addbullet(this, NULL, 849, x + 61.0 * dir, y + 232.0, dir, 1, t, 3);
                scene_add_effect(this, 127, x, y, dir, -1);
                play_sfx(28);
                spell_energy_spend(200,120);
                add_card_energy(50);

                h_inerc = 25.0;
                v_inerc = 20.0;
                v_force = 0.5;
                field_190 = 1;
            }
        }
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3)
            field_190 = 1;
        break;
    case 530:
        sub10func();
        field_18C = 9;
        if ( process() )
            set_seq(0);
        if (get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 5)
        {
            float t[3];
            t[0] = -70.0;
            t[1] = 30.0;
            t[2] = 0.0;
            addbullet(this, NULL, 817, x + 18.0 * dir, y + 164.0, dir, 1, t, 3);
            scene_add_effect(this, 127, x, y, dir, -1);
            play_sfx(30);
            spell_energy_spend(200, 120);
            add_card_energy(50);
            field_190 = 1;
        }
        break;
    case 531:
        sub10func();
        field_18C = 9;
        if ( process() )
            set_seq(0);
        if (get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 5)
        {
            float t[3];
            t[0] = -40.0;
            t[1] = 50.0;
            t[2] = 0.0;
            addbullet(this, NULL, 817, x + 74.0 * dir, y + 164.0, dir, 1, t, 3);
            scene_add_effect(this, 127, x, y, dir, -1);
            play_sfx(30);
            spell_energy_spend(200, 120);
            add_card_energy(50);
            field_190 = 1;
        }
        break;
    case 540:
        sub10func();
        field_18C = 2;
        if ( !keyDown(INP_B))
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 2 && get_frame_time() == 0  && get_frame() == 1 )
        {
            add_card_energy( 50);
            spell_energy_spend( 200, 120);
            field_190 = 1;
            float tmp[3];
            tmp[0] = 4;
            tmp[1] = field_7DC / 40;
            tmp[2] = 0;
            addbullet(this,NULL, 820, x + 70*dir, y + 165, dir, 1, tmp, 3);
            play_sfx(7);
        }
        if (get_subseq() == 1)
        {
            if (not_charge_attack != 0 && get_elaps_frames() < 60)
                field_7DC++;
            else
                next_subseq();
        }
        break;
    case 541:
        sub10func();
        field_18C = 2;
        if ( !keyDown(INP_C))
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 2 && get_frame_time() == 0  && get_frame() == 1 )
        {
            add_card_energy( 50);
            spell_energy_spend( 200, 120);
            field_190 = 1;
            float tmp[3];
            tmp[0] = 4;
            tmp[1] = field_7DC / 40;
            tmp[2] = 0;
            addbullet(this,NULL, 820, x + 70*dir, y + 165, dir, 1, tmp, 3);
            play_sfx(7);
        }
        if (get_subseq() == 1)
        {
            if (not_charge_attack != 0 && get_elaps_frames() < 60)
                field_7DC += 2;
            else
                next_subseq();
        }
        break;
    case 542:
        if ( get_subseq() == 3 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq(3);
                break;
            }
        }
        field_18C = 2;
        if ( !keyDown(INP_B) )
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() ==0 && get_subseq() == 3)
            set_seq(9);
        else
        {
            if ( get_subseq() == 2 && get_frame_time() == 0 )
            {
                if (get_frame() == 1)
                {
                    add_card_energy( 50);
                    spell_energy_spend( 200, 120);
                    field_190 = 1;
                    float tmp[3];
                    tmp[0] = 4;
                    tmp[1] = field_7DC / 40;
                    tmp[2] = 0;
                    addbullet(this,NULL, 820, x + 70*dir, y + 165, dir, 1, tmp, 3);
                    play_sfx(7);
                }
                if (get_frame() == 4)
                    v_force = 0.5;
            }

            if (get_subseq() == 1)
            {
                if (not_charge_attack != 0 && get_elaps_frames() < 60)
                    field_7DC++;
                else
                    next_subseq();
            }
        }
        break;
    case 543:
        if ( get_subseq() == 3 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq(3);
                break;
            }
        }
        field_18C = 2;
        if ( !keyDown(INP_C) )
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() ==0 && get_subseq() == 3)
            set_seq(9);
        else
        {
            if ( get_subseq() == 2 && get_frame_time() == 0 )
            {
                if (get_frame() == 1)
                {
                    add_card_energy( 50);
                    spell_energy_spend( 200, 120);
                    field_190 = 1;
                    float tmp[3];
                    tmp[0] = 4;
                    tmp[1] = field_7DC / 40;
                    tmp[2] = 0;
                    addbullet(this,NULL, 820, x + 70*dir, y + 165, dir, 1, tmp, 3);
                    play_sfx(7);
                }
                if (get_frame() == 4)
                    v_force = 0.5;
            }

            if (get_subseq() == 1)
            {
                if (not_charge_attack != 0 && get_elaps_frames() < 60)
                    field_7DC += 2;
                else
                    next_subseq();
            }
        }
        break;
    case 545:
        sub10func();
        field_18C = 6;
        if ( process() )
            set_seq(0);
        if (get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2)
        {
            add_card_energy(50);
            spell_energy_spend(200, 120);
            field_190 = 1;

            float t[3];
            t[0] = 0.0;
            t[1] = 6.0;
            t[2] = 4.5;

            addbullet(this, NULL, 821, x + 96.0 * dir, y + 114.0, dir, 1, t, 3);
            play_sfx(7);
        }
        break;
    case 546:
        sub10func();
        field_18C = 6;
        if ( process() )
            set_seq(0);
        if (get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2)
        {
            add_card_energy(50);
            spell_energy_spend(200, 120);
            field_190 = 1;

            float t[3];
            t[0] = 0.0;
            t[1] = 16.0;
            t[2] = 4.5;

            addbullet(this, NULL, 821, x + 96.0 * dir, y + 114.0, dir, 1, t, 3);
            play_sfx(7);
        }
        break;
    case 547:
        if ( get_subseq() == 1 )
            sub10func();
        field_18C = 6;
        if ( get_subseq() < 1 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                set_subseq(1);
                y = getlvl_height();
                break;
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            set_seq(9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6)
        {
            play_sfx(7);
            h_inerc = -4.0;
            v_inerc = 8.0;
            v_force = 0.5;
            field_190 = 1;

            float t[3];
            t[0] = 0.0;
            t[1] = 3.0;
            t[2] = -20.0;
            addbullet(this, NULL, 821, x + dir * 30.0, y + 62.0, dir, 1, t, 3);
            spell_energy_spend( 200, 120);
            add_card_energy( 50);
        }
        break;
    case 548:
        if ( get_subseq() == 1 )
            sub10func();
        field_18C = 6;
        if ( get_subseq() < 1 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                set_subseq(1);
                y = getlvl_height();
                break;
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            set_seq(9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6)
        {
            play_sfx(7);
            h_inerc = -4.0;
            v_inerc = 8.0;
            v_force = 0.5;
            field_190 = 1;

            float t[3];
            t[0] = 0.0;
            t[1] = 13.0;
            t[2] = -20.0;
            addbullet( this, NULL, 821, x + dir * 30.0, y + 62.0 , dir, 1, t, 3);
            spell_energy_spend(200, 120);
            add_card_energy(50);
        }
        break;
    case 550:
        sub10func();
        field_18C = 10;
        if ( !keyDown(INP_B) )
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 3)
        {
            add_card_energy(50);
            spell_energy_spend(200, 120);
            field_190 = 1;
            char_frame *frm = get_pframe();

            float t[3];
            t[0] = 3.0;
            t[1] = 6.0;
            t[2] = 0.0;
            addbullet(this, NULL, 822, x + frm->extra1[4] * dir, y - frm->extra1[5], dir, 1, t, 3);
            play_sfx(36);
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= 4 )
            next_subseq();
        break;
    case 551:
        sub10func();
        field_18C = 10;
        if ( !keyDown(INP_B) )
            not_charge_attack = 0;
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 3)
        {
            add_card_energy(50);
            spell_energy_spend(200, 120);
            field_190 = 1;
            char_frame *frm = get_pframe();

            float t[3];
            t[0] = 7.0;
            t[1] = 8.0;
            t[2] = 0.0;
            addbullet(this, NULL, 822, x + frm->extra1[4] * dir, y - frm->extra1[5], dir, 1, t, 3);
            play_sfx(36);
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= 10 )
            next_subseq();
        break;
    case 552:
        if ( get_subseq() == 1 )
            sub10func();
        field_18C = 10;
        if ( get_subseq() < 1 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                set_subseq(1);
                y = getlvl_height();
                break;
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            set_seq(9);
        else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
        {
            h_inerc = -4.0;
            v_inerc = 8.0;
            v_force = 0.5;
            field_190 = 1;
            char_frame *frm = get_pframe();

            float t[3];
            t[0] = 7.0;
            t[1] = -8.0;
            t[2] = 0.0;

            addbullet(this, NULL, 822, x + frm->extra1[4] * dir, y - frm->extra1[5], dir, 1, t, 3);
            play_sfx(36);
            spell_energy_spend(200, 120);
            add_card_energy(50);
        }
        break;
    case 553:
        if ( get_subseq() == 1 )
            sub10func();
        field_18C = 10;
        if ( get_subseq() < 1 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                set_subseq(1);
                y = getlvl_height();
                break;
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            set_seq(9);
        else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
        {
            h_inerc = -4.0;
            v_inerc = 8.0;
            v_force = 0.5;
            field_190 = 1;
            char_frame *frm = get_pframe();

            float t[3];
            t[0] = 14.0;
            t[1] = -8.0;
            t[2] = 0.0;

            addbullet(this, NULL, 822, x + frm->extra1[4] * dir, y - frm->extra1[5], dir, 1, t, 3);
            spell_energy_spend(200, 120);
            add_card_energy(50);
            play_sfx(36);
        }
        break;
    case 560:
        sub10func();

        field_18C = 3;
        if ( !get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 9) )
            if (!keyDown(INP_B))
                not_charge_attack = 0;

        if ( field_7D0 > 0  && (get_subseq() >= 2  && get_subseq() <= 4))
        {
            if (field_7D0 % 4 == 1)
            {
                field_190 = 1;
                if ( (not_charge_attack == 1 && field_7D2 < 9) || field_7D2 < 5)
                {
                    float tmp[3];
                    tmp[0] = sin_deg(field_7DC) * 20.0 + field_7F0;
                    tmp[1] = 15;
                    tmp[2] = scene_rand_rng(4);
                    addbullet(this,NULL, 825, x + dir*44, y + 85, dir, 1 , tmp, 3);
                    play_sfx(9);
                    scene_add_effect(this, 129, x , y, dir, -1);
                }
                if (field_7DC < 0)
                    field_7DC = -(-30 + field_7DC);
                else
                    field_7DC = -(30 + field_7DC);
                field_7D2++;
            }
            field_7D0++;
        }

        if ( process() )
            set_seq(0);
        if ( get_subseq() == 1 )
        {
            uint32_t frms = 4;
            if ( skills_1[3] >= 1 )
                frms = 2;
            if ( get_elaps_frames() >= frms && get_elaps_frames() <= 10 )
            {
                if ( not_charge_attack == 0 )
                {
                    next_subseq();
                    break;
                }
                if ( get_elaps_frames() == 10 )
                    scene_add_effect(this, 62, x -23*dir, y+ 95, dir, 1);
            }
            if ( get_elaps_frames() >= 25 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0;
            tmp[1] = 0;
            tmp[2] = 4;
            addbullet(this, NULL, 825, x - 24*dir, y+95, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            field_7D0 = 1;
            spell_energy_spend( 200, 120);
            add_card_energy( 50);
            sub_486FD0(10.0, -10.0);
        }
        if ( get_subseq() == 3 )
        {
            uint32_t frms = 10;
            if ( skills_1[3] >= 1 )
                frms = 7;
            if ( skills_1[3] >= 4 )
                frms = 4;

            if ( (get_elaps_frames() > frms && not_charge_attack == 0) || get_elaps_frames() > frms + 10)
                next_subseq();
        }
        break;
    case 561:
        sub10func();

        field_18C = 3;
        if ( !get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 9) )
            if (!keyDown(INP_C))
                not_charge_attack = 0;

        if ( field_7D0 > 0  && (get_subseq() >= 2  && get_subseq() <= 4))
        {
            if (field_7D0 % 4 == 1)
            {
                field_190 = 1;
                if ( (not_charge_attack == 1 && field_7D2 < 9) || field_7D2 < 5)
                {
                    float tmp[3];
                    tmp[0] = sin_deg(field_7DC) * 30.0 + field_7F0;
                    tmp[1] = 15;
                    tmp[2] = scene_rand_rng(4);
                    addbullet(this,NULL, 825, x + dir*44, y + 85, dir, 1 , tmp, 3);
                    play_sfx(9);
                    scene_add_effect(this, 129, x , y, dir, -1);
                }
                if (field_7DC < 0)
                    field_7DC = -(-30 + field_7DC);
                else
                    field_7DC = -(30 + field_7DC);
                field_7D2++;
            }
            field_7D0++;
        }
        if (process())
            set_seq(0);
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() >= 2 && get_elaps_frames() <= 10 )
            {
                if ( not_charge_attack == 0 )
                {
                    next_subseq();
                    break;
                }
                if ( get_elaps_frames() == 10 )
                    scene_add_effect(this, 62, x -23*dir, y+ 95, dir, 1);
            }
            if ( get_elaps_frames() >= 25 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0;
            tmp[1] = 0;
            tmp[2] = 4;
            addbullet(this, NULL, 825, x - 24*dir, y+95, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            field_7D0 = 1;
            spell_energy_spend( 200, 120);
            add_card_energy( 50);
            sub_486FD0(10.0, -10.0);
        }
        if ( get_subseq() == 3 )
        {
            uint32_t frms = 10;
            if ( skills_1[3] >= 1 )
                frms = 7;
            if ( skills_1[3] >= 4 )
                frms = 4;

            if ( (get_elaps_frames() > frms && not_charge_attack == 0) || get_elaps_frames() > frms + 10)
                next_subseq();
        }
        break;
    case 562:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 3;
        v_inerc -= v_force;

        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 9) )
        {
            if ( !keyDown(INP_B))
                not_charge_attack = 0;
        }

        if ( field_7D0 > 0  && (get_subseq() >= 2  && get_subseq() <= 4))
        {
            if (field_7D0 % 4 == 1)
            {
                field_190 = 1;
                if ( (not_charge_attack == 1 && field_7D2 < 9) || field_7D2 < 5)
                {
                    float tmp[3];
                    tmp[0] = sin_deg(field_7DC) * 20.0 + field_7F0;
                    tmp[1] = 15;
                    tmp[2] = scene_rand_rng(4);
                    addbullet(this,NULL, 825, x + dir*44, y + 85, dir, 1 , tmp, 3);
                    play_sfx(9);
                }
                if (field_7DC < 0)
                    field_7DC = -(-30 + field_7DC);
                else
                    field_7DC = -(30 + field_7DC);
                field_7D2++;
            }
            field_7D0++;
        }
        if (process())
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5)
            set_seq(9);
        else
        {
            if ( get_subseq() == 1 )
            {
                if ( get_elaps_frames() >= 4 && get_elaps_frames() <= 10 )
                {
                    if ( not_charge_attack == 0 )
                    {
                        next_subseq();
                        break;
                    }
                    if ( get_elaps_frames() == 10 )
                        scene_add_effect(this, 62, x -23*dir, y+ 107, dir, 1);
                }
                if ( get_elaps_frames() >= 25 )
                {
                    next_subseq();
                    break;
                }
            }
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                float tmp[3];
                tmp[0] = 0;
                tmp[1] = 0;
                tmp[2] = 4;
                addbullet(this, NULL, 825, x - 23*dir, y+107, dir, 1, tmp, 3);
            }
            if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
            {
                field_7D0 = 1;
                spell_energy_spend( 200, 120);
                add_card_energy( 50);
                sub_486FD0(10.0, -10.0);
            }
            if ( get_subseq() == 3 )
            {
                uint32_t frms = 10;
                if ( skills_1[3] >= 1 )
                    frms = 7;
                if ( skills_1[3] >= 4 )
                    frms = 4;

                if ( (get_elaps_frames() > frms && not_charge_attack == 0) || get_elaps_frames() > frms + 10)
                    next_subseq();
            }
            else if ( get_subseq() == 4  && get_frame() == 5 && get_frame_time() == 0)
                v_force = 0.6;
        }
        break;
    case 563:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 3;
        v_inerc -= v_force;

        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() == 0 || (get_subseq() == 1 && get_elaps_frames() <= 9) )
        {
            if ( !keyDown(INP_C))
                not_charge_attack = 0;
        }
        if ( field_7D0 > 0  && (get_subseq() >= 2  && get_subseq() <= 4))
        {
            if (field_7D0 % 4 == 1)
            {
                field_190 = 1;
                if ( (not_charge_attack == 1 && field_7D2 < 9) || field_7D2 < 5)
                {
                    float tmp[3];
                    tmp[0] = sin_deg(field_7DC) * 30.0 + field_7F0;
                    tmp[1] = 15;
                    tmp[2] = scene_rand_rng(4);
                    addbullet(this,NULL, 825, x + dir*44, y + 85, dir, 1 , tmp, 3);
                    play_sfx(9);
                }
                if (field_7DC < 0)
                    field_7DC = -(-30 + field_7DC);
                else
                    field_7DC = -(30 + field_7DC);
                field_7D2++;
            }
            field_7D0++;
        }
        if (process())
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5)
            set_seq(9);
        else
        {
            if ( get_subseq() == 1 )
            {
                if ( get_elaps_frames() >= 4 && get_elaps_frames() <= 10 )
                {
                    if ( not_charge_attack == 0 )
                    {
                        next_subseq();
                        break;
                    }
                    if ( get_elaps_frames() == 10 )
                        scene_add_effect(this, 62, x -23*dir, y+ 107, dir, 1);
                }
                if ( get_elaps_frames() >= 25 )
                {
                    next_subseq();
                    break;
                }
            }
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                float tmp[3];
                tmp[0] = 0;
                tmp[1] = 0;
                tmp[2] = 4;
                addbullet(this, NULL, 825, x - 23*dir, y+107, dir, 1, tmp, 3);
            }
            if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
            {
                field_7D0 = 1;
                spell_energy_spend( 200, 120);
                add_card_energy( 50);
                sub_486FD0(10.0, -10.0);
            }
            if ( get_subseq() == 3 )
            {
                uint32_t frms = 10;
                if ( skills_1[3] >= 1 )
                    frms = 7;
                if ( skills_1[3] >= 4 )
                    frms = 4;

                if ( (get_elaps_frames() > frms && not_charge_attack == 0) || get_elaps_frames() > frms + 10)
                    next_subseq();
            }
            else if ( get_subseq() == 4  && get_frame() == 5 && get_frame_time() == 0)
                v_force = 0.6;
        }
        break;
    case 565:
        sub10func();
        field_18C = 7;
        if ( get_subseq() < 2 && !keyDown(INP_B) )
            not_charge_attack = 0;
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0)
        {
            add_card_energy(50);
            field_190 = 1;
            play_sfx(29);
            field_7D4 = -atan2_deg(enemy->y - y, (enemy->x - x)* dir);
            if ( field_7D4 < -10 )
                field_7D4 = -10;
            if ( field_7D4 > 10 )
                field_7D4 = 10;
            play_sfx(4);
            spell_energy_spend(200, 120);

            float t[3];
            t[0] = 1.75;
            t[1] = skills_1[7] * 10.0 + 25.0;
            t[2] = 10.0;
            if (skills_1[7] <= 3)
                t[0] = 1.5;
            addbullet(this, NULL, 826, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;

            addbullet(this, NULL, 826, x - 24.0 * dir, y + 95.0, dir, 1, t, 3);
        }

        if (get_subseq() == 1 && get_elaps_frames() >=8 && ( not_charge_attack == 0 || get_elaps_frames() > 25 ))
            next_subseq();
        if ( get_subseq() == 3 && get_elaps_frames() > 40)
            next_subseq();
        break;
    case 566:
        sub10func();
        field_18C = 7;
        if ( get_subseq() < 2 && !keyDown(INP_C) )
            not_charge_attack = 0;
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0)
        {
            add_card_energy(50);
            field_190 = 1;
            play_sfx(29);
            field_7D4 = -atan2_deg(enemy->y - y, (enemy->x - x)* dir);
            if ( field_7D4 < -10 )
                field_7D4 = -10;
            if ( field_7D4 > 10 )
                field_7D4 = 10;
            play_sfx(4);
            spell_energy_spend(200, 120);

            float t[3];
            t[0] = 1.75;
            t[1] = skills_1[7] * 10.0 + 25.0;
            t[2] = 10.0;
            if (skills_1[7] <= 3)
                t[0] = 1.5;
            addbullet(this, NULL, 826, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;

            addbullet(this, NULL, 826, x - 24.0 * dir, y + 95.0, dir, 1, t, 3);
        }

        if (get_subseq() == 1 && get_elaps_frames() >=8 && ( not_charge_attack == 0 || get_elaps_frames() > 25 ))
            next_subseq();
        if ( get_subseq() == 3 && get_elaps_frames() > 40)
            next_subseq();
        break;
    case 567:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 7;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() < 2  && !keyDown(INP_B) )
            not_charge_attack = 0;
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy(50);
            field_190 = 1;
            play_sfx(29);
            field_7D4 = -atan2_deg(enemy->y - y, (enemy->x - x)*dir);
            if ( field_7D4 < -10 )
                field_7D4 = -10;
            if ( field_7D4 > 10 )
                field_7D4 = 10;
            play_sfx(4);
            spell_energy_spend(200, 120);
            float t[3];
            t[0] = 1.75;
            t[1] = skills_1[7] * 5.0 + 25.0;
            t[2] = 10.0;
            if ( skills_1[7] <= 3 )
                t[0] = 1.5;

            addbullet(this, NULL, 826, x + 44.0*dir, y + 104.0, dir, 1, t, 3);
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;

            addbullet(this, NULL, 826, x - 48.0 * dir, y + 104.0, dir, 1, t, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq(9);
            break;
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= 8 && (!not_charge_attack || get_elaps_frames() > 25) )
            next_subseq();
        if ( get_subseq() == 3 && get_elaps_frames() > 40)
            next_subseq();
        if (get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5)
            v_force = 0.6;
        break;
    case 568:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 7;
        v_inerc = v_inerc - v_force;

        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }

        if ( get_subseq() < 2  && !keyDown(INP_C) )
            not_charge_attack = 0;

        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy(50);
            field_190 = 1;
            play_sfx(29);
            field_7D4 = -atan2_deg(enemy->y - y, (enemy->x - x)*dir);
            if ( field_7D4 < -10 )
                field_7D4 = -10;
            if ( field_7D4 > 10 )
                field_7D4 = 10;
            play_sfx(4);
            spell_energy_spend(200, 120);

            float t[3];
            t[0] = 1.75;
            t[1] = skills_1[7] * 5.0 + 25.0;
            t[2] = 10.0;
            if ( skills_1[7] <= 3 )
                t[0] = 1.5;

            addbullet(this, NULL, 826, x + 44.0*dir, y + 104.0, dir, 1, t, 3);
        }
        if ( process() )
            set_seq(0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;

            addbullet(this, NULL, 826, x - 48.0 * dir, y + 104.0, dir, 1, t, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq(9);
            break;
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= 8 && (!not_charge_attack || get_elaps_frames() > 25) )
            next_subseq();
        if ( get_subseq() == 3 && get_elaps_frames() > 40)
            next_subseq();
        if (get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5)
            v_force = 0.6;
        break;
    case 570:
        sub10func();
        field_18C = 11;
        if ( get_subseq() < 2  && !keyDown(INP_C) )
            not_charge_attack = 0;
        if ( get_subseq() == 2  && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy(50);
            field_190 = 1;
            play_sfx(34);
            spell_energy_spend(200, 120);

            float t[3];
            t[0] = 30.0;
            t[1] = 0.0;
            t[2] = 4.0;

            if ( field_7D8 == 1 ) //HACK? WHAT DIFF?
            {
                addbullet(this,NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for (int8_t i = 0; i < 3; i++)
                {
                    t[1] = i * 5.0 + 10.0;
                    if (skills_1[11] > 3)
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this,NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
                for (int8_t i = 0; i < 3; i++)
                {
                    t[1] = -i * 5.0 - 10.0;
                    if (skills_1[11] > 3)
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this,NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
            }
            else
            {
                addbullet(this,NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for (int8_t i = 0; i < 3; i++)
                {
                    t[1] = i * 5.0 + 10.0;
                    if (skills_1[11] > 3)
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this,NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
                for (int8_t i = 0; i < 3; i++)
                {
                    t[1] = -i * 5.0 - 10.0;
                    if (skills_1[11] > 3)
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this,NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 1 && get_elaps_frames() > 2)
            next_subseq();
        if (get_subseq() == 3 && get_elaps_frames() > 10 )
            next_subseq();
        break;
    case 571:
        sub10func();
        field_18C = 11;
        if ( get_subseq() < 2  && !keyDown(INP_C) )
            not_charge_attack = 0;
        if ( get_subseq() == 2  && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy(50);
            field_190 = 1;
            play_sfx( 34);
            spell_energy_spend(200, 120);

            float t[3];
            t[0] = 45.0;
            t[1] = 0.0;
            t[2] = 4.0;

            if ( field_7D8 == 1 ) //HACK? WHAT DIFF?
            {
                addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = i * 5.0 + 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = -i * 5.0 - 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
            }
            else
            {
                addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = i * 5.0 + 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = -i * 5.0 - 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                }
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 1 && get_elaps_frames() > 2 )
            next_subseq();
        if ( get_subseq() == 3 && get_elaps_frames() > 20)
            next_subseq();
        break;
    case 572:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 11;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() < 2 && !keyDown(INP_C))
            not_charge_attack = 0;
        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy( 50);
            field_190 = 1;
            play_sfx( 34);
            spell_energy_spend( 200, 120);
            float t[3];
            t[0] = 30.0;
            t[1] = 0.0;
            t[2] = 4.0;

            if ( field_7D8 == 1 ) //HACK? WHAT DIFF?
            {
                addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = i * 5.0 + 10.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = -i * 5.0 - 10.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
            }
            else
            {
                addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = i * 5.0 + 10.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = -i * 5.0 - 10.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
            }
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5)
        {
            set_seq(9);
            break;
        }

        if ( get_subseq() == 1 && get_elaps_frames() > 2 )
            next_subseq();
        if (get_subseq() == 3 && get_elaps_frames() > 10)
            next_subseq();
        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5 )
            v_force = 0.6;
        break;
    case 573:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 11;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq(5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() < 2  && !keyDown(INP_C) )
            not_charge_attack = 0;

        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            add_card_energy( 50);
            field_190 = 1;
            play_sfx( 34);
            spell_energy_spend( 200, 120);
            float t[3];
            t[0] = 45.0;
            t[1] = 0.0;
            t[2] = 4.0;

            if ( field_7D8 == 1 ) //HACK? WHAT DIFF?
            {
                addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = i * 5.0 + 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = -i * 5.0 - 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
            }
            else
            {
                addbullet(this, NULL, 827, x + 44.0 * dir, y + 85.0, dir, 1, t, 3);
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = i * 5.0 + 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
                for(int8_t i=0; i<3; i++)
                {
                    t[1] = -i * 5.0 - 20.0;
                    if ( skills_1[11] > 3 )
                        t[2] = 6.0;
                    else
                        t[2] = 0.0;
                    addbullet(this, NULL, 827, x + 48.0 * dir, y + 104.0, dir, 1, t, 3);
                }
            }
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5)
        {
            set_seq(9);
            break;
        }
        if ( get_subseq() == 1 && get_elaps_frames() > 2 )
            next_subseq();
        if (get_subseq() == 3 && get_elaps_frames() > 20)
            next_subseq();
        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5 )
            v_force = 0.6;
        break;
    case 599:
        if ( field_7D0 > 0 && field_7D0 < 12 && get_frame() < 7 )
        {
            field_7D4 = scene_rand_rng(35);
            float t[3];
            t[0] = -20 - field_7D4;
            t[1] = scene_rand() % 5 + 10;
            t[2] = 0.0;

            addbullet(this,NULL, 807, x + (field_7D0 + 1)*dir*20.0, y, dir, 1, t, 3);
            t[0] = scene_rand() % 360;
            t[1] = 0.0;
            t[2] = 1.0;
            addbullet(this,NULL, 801, x + (field_7D0 + 1)*dir*20.0, y, dir, 1, t, 3);
            if ( field_7D0 == 1 )
            {
                play_sfx(0);
                spell_energy_spend( 200, 120);
            }
            field_7D0++;
        }
        if ( process() )
            set_seq(0);
        if ( get_frame_time() == 0 && get_frame() == 5)
            field_7D0 = 1;
        break;
    case 611:
        if ( get_subseq() == 3 )
            sub10func();

        sub_46AB50(5, 2);
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            v_inerc -= v_force;
            h_inerc += 0.75;
            if ( h_inerc > -1.0 ) //HACK? LOL WHAT?
                h_inerc = -1.0;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq(3);
            }
        }
        if ( process() )
            set_seq(0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 9)
        {
            sub_4834E0(40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x - 23*dir, y + 94.0, dir, 1);
            sub_469450(0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            play_sfx(20);
            sub_486FD0(20.0, -20.0);

            h_inerc = -25.0;
            v_inerc = 10.0;
            v_force = 0.5;

            float tmp[4];
            tmp[0] = field_7F0;
            tmp[1] = 25.0;
            tmp[2] = 0.0;
            tmp[3] = 0.0;

            addbullet(this, NULL, 861, x + dir * 73.0, y + 95.0,dir,1, tmp, 4);
            scene_add_effect(this, 127, x + 200.0 * dir, y, dir, -1);
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

    if ( !check_AB_pressed() )
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
            if (field_524 == 0)
            {
                if (input->keyHit(INP_BC) && sub_468660(0) && field_836 == 0)
                {
                    if (char_on_ground_flag())
                    {
                        if ( !sub_489F10(cprior) && seq299_300_field190_0_3()) //HACK
                        {
                            int32_t crd_id = cards_active[0]->id;

                            if (cprior <= 50 && crd_id >= 100 && crd_id <= 199)
                            {
                                switch(crd_id)
                                {
                                case 100:
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(500, cprior);
                                    return;
                                case 101:
                                    if ( field_801 == 0 )
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(520, cprior);
                                    return;
                                case 102:
                                    if ( field_802 == 0 )
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(540, cprior);
                                    return;
                                case 103:
                                    if ( field_803 == 0 )
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(560, cprior);
                                    return;
                                case 104:
                                    if ( field_800 == 0 )
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(505, cprior);
                                    return;
                                case 105:
                                    if ( field_801 == 0 )
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(525, cprior);
                                    return;
                                case 106:
                                    if ( field_802 == 0 )
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(545, cprior);
                                    return;
                                case 107:
                                    if ( field_803 == 0 )
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(565, cprior);
                                    return;
                                case 108:
                                    if ( field_800 == 0 )
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(510, cprior);
                                    return;
                                case 109:
                                    if ( field_801 == 0 )
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(530, cprior);
                                    return;
                                case 110:
                                    if ( field_802 == 0 )
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(550, cprior);
                                    return;
                                case 111:
                                    if ( field_803 == 0 )
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(570, cprior);
                                    return;
                                default:
                                    break;
                                }
                            }
                            else if (cprior <= 100 && crd_id >= 200 && crd_id <= 299 && gX(1) == 0)
                            {
                                switch(crd_id)
                                {
                                case 200:
                                    sub_487370(600, cprior);
                                    return;
                                case 201:
                                    sub_487370(601, cprior);
                                    return;
                                case 202:
                                    sub_487370(602, cprior);
                                    return;
                                case 203:
                                    sub_487370(603, cprior);
                                    return;
                                case 204:
                                    sub_487370(604, cprior);
                                    return;
                                case 205:
                                    sub_487370(605, cprior);
                                    return;
                                case 206:
                                    sub_487370(606, cprior);
                                    return;
                                case 207:
                                    sub_487370(607, cprior);
                                    return;
                                case 208:
                                    sub_487370(608, cprior);
                                    return;
                                case 209:
                                    sub_487370(609, cprior);
                                    return;
                                case 210:
                                    sub_487370(610, cprior);
                                    return;
                                case 211:
                                    sub_487370(611, cprior);
                                    return;
                                case 212:
                                    sub_487370(612, cprior);
                                    return;
                                case 213:
                                    sub_487370(613, cprior);
                                    return;
                                case 214:
                                    sub_487370(614, cprior);
                                    return;
                                case 215:
                                    if ( field_8A8 == 0 )
                                    {
                                        sub_487370(615, cprior);
                                        return;
                                    }
                                    break;
                                case 216:
                                    sub_487370(616, cprior);
                                    return;
                                case 217:
                                    sub_487370(617, cprior);
                                    return;
                                case 218:
                                    sub_487370(618, cprior);
                                    return;
                                case 219:
                                    sub_487370(619, cprior);
                                    return;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (seq299_300_field190_0_3()) //HACK
                        {
                            int32_t crd_id = cards_active[0]->id;

                            if (cprior <= 50 && crd_id >= 100 && crd_id <= 199)
                            {
                                switch(crd_id)
                                {
                                case 100:
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(500, cprior);
                                    return;
                                case 102:
                                    if ( field_802 == 0 )
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(542, cprior);
                                    return;
                                case 103:
                                    if ( field_803 == 0 )
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(562, cprior);
                                    return;
                                case 104:
                                    if ( field_800 == 0 )
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(505, cprior);
                                    return;
                                case 106:
                                    if ( field_802 == 0 )
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(547, cprior);
                                    return;
                                case 107:
                                    if ( field_803 == 0 )
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(567, cprior);
                                    return;
                                case 108:
                                    if ( field_800 == 0 )
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(512, cprior);
                                    return;
                                case 110:
                                    if ( field_802 == 0 )
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(552, cprior);
                                    return;
                                case 111:
                                    if ( field_803 == 0 )
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(572, cprior);
                                    return;
                                default:
                                    break;
                                }
                            }
                            else if (cprior <= 100 && crd_id >= 200 && crd_id <= 299 && gX(1) == 0)
                            {
                                switch(crd_id)
                                {
                                case 203:
                                    sub_487370(603, cprior);
                                    return;
                                case 205:
                                    sub_487370(605, cprior);
                                    return;
                                case 207:
                                    sub_487370(607, cprior);
                                    return;
                                case 208:
                                    sub_487370(608, cprior);
                                    return;
                                case 211:
                                    sub_487370(611, cprior);
                                    return;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                }

                if (pres_comb && spell200_seq299_300_field190_0_3() )
                {
                    if (char_on_ground_flag())
                    {
                        if ( pres_comb & PCOMB_623C )
                        {
                            if ( skills_1[9] >= 1 )
                            {
                                if ( cprior <= get_prior(531) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0 )
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 531, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[5] >= 1 )
                            {
                                if ( cprior <= get_prior(526) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 526, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 521, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_623B )
                        {
                            if ( skills_1[9] >= 1 )
                            {
                                if ( cprior <= get_prior(530) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 530, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[5] >= 1 )
                            {
                                if ( cprior <= get_prior(525) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 525, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 520, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236C )
                        {
                            if ( skills_1[11] >= 1 )
                            {
                                if ( cprior <= get_prior(571) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 571, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[7] >= 1 )
                            {
                                if ( cprior <= get_prior(566) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 566, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 561, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236B )
                        {
                            if ( skills_1[11] >= 1 )
                            {
                                if ( cprior <= get_prior(570) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 570, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[7] >= 1 )
                            {
                                if ( cprior <= get_prior(565) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 565, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 560, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214C )
                        {
                            if ( skills_1[8] >= 1 )
                            {
                                if ( cprior <= get_prior(511) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 511, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[4] >= 1 )
                            {
                                if ( cprior <= get_prior(506) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 506, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 500, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214B )
                        {
                            if ( skills_1[8] >= 1 )
                            {
                                if ( cprior <= get_prior(510) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 510, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[4] >= 1 )
                            {
                                if ( cprior <= get_prior(505) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 505, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 500, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_2N2C )
                        {
                            if ( skills_1[10] >= 1 )
                            {
                                if ( cprior <= get_prior(551) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 551, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[6] >= 1 )
                            {
                                if ( cprior <= get_prior(546) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 546, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 541, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_2N2B )
                        {
                            if ( skills_1[10] >= 1 )
                            {
                                if ( cprior <= get_prior(550) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 550, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[6] >= 1 )
                            {
                                if ( cprior <= get_prior(545) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 545, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 540, cprior);
                                return;
                            }
                        }
                    }
                    else // Air specials
                    {
                        if ( pres_comb & PCOMB_236C )
                        {
                            if ( skills_1[11] >= 1 )
                            {
                                if ( cprior <= get_prior(573) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 573, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[7] >= 1 )
                            {
                                if ( cprior <= get_prior(568) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 568, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 563, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236B )
                        {
                            if ( skills_1[11] >= 1 )
                            {
                                if ( cprior <= get_prior(572) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 572, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[7] >= 1 )
                            {
                                if ( cprior <= get_prior(567) || (sq >= 500 && sq <= 599 && field_803 == 0))
                                {
                                    if ( field_803 == 0)
                                    {
                                        field_4C8++;
                                        field_803 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 567, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 562, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214C )
                        {
                            if ( skills_1[8] >= 1 )
                            {
                                if ( cprior <= get_prior(513) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 513, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[4] >= 1 )
                            {
                                if ( cprior <= get_prior(506) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 506, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 500, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_214B )
                        {
                            if ( skills_1[8] >= 1 )
                            {
                                if ( cprior <= get_prior(512) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 512, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[4] >= 1 )
                            {
                                if ( cprior <= get_prior(505) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 505, cprior);
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
                                sub_4834F0();
                                sub_4873B0( 500, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_2N2C )
                        {
                            if ( skills_1[10] >= 2 )
                            {
                                if ( cprior <= get_prior(553) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 553, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[6] >= 2 )
                            {
                                if ( cprior <= get_prior(548) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 548, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[10] == 0 && skills_1[6] == 0)
                            {
                                if ( cprior <= get_prior(543) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 543, cprior);
                                    return;
                                }
                            }
                        }
                        if ( pres_comb & PCOMB_2N2B )
                        {
                            if ( skills_1[10] >= 2 )
                            {
                                if ( cprior <= get_prior(552) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 552, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[6] >= 2 )
                            {
                                if ( cprior <= get_prior(547) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 547, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[10] == 0 && skills_1[6] == 0)
                            {
                                if ( cprior <= get_prior(542) || (sq >= 500 && sq <= 599 && field_802 == 0))
                                {
                                    if ( field_802 == 0)
                                    {
                                        field_4C8++;
                                        field_802 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 542, cprior);
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            if (input->keyHit(INP_A))
            {
                if (char_on_ground_flag()) // On Ground
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
//                        if ( input->gY() <= 0) //HACK
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
                if (char_on_ground_flag()) // On Ground
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
                        if ( input->gY() < 0 /*&& input->gX(dir) > 0*/ && cprior <= get_prior(402) ) // 2B //HACK?
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
                if (char_on_ground_flag()) // On Ground
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
                        if ( input->gY() < 0 /*&& input->gX(dir) > 0*/ && cprior <= get_prior(412) ) // 2C //HACK?
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
    case 500:
        field_18C = 0;
        reset_forces();
        field_190 = 0;
        v_force = 0.55;
        field_49A = 0;
        field_7D0 = 0;
        field_194 = 1;
        break;
    case 504:
        field_18C = 0;
        reset_forces();
        h_inerc = 10.0;
        v_inerc = 10.0;
        field_49A = 0;
        v_force = 0.55;
        field_7D0 = 0;
        field_194 = 1;
        if (skills_1[0] > 1)
            field_190 = 1;
        else
            field_190 = 0;
        break;
    case 520:
        field_18C = 1;
        reset_forces();
        field_194 = 99;
        field_190 = 0;
        field_49A = 0;
        field_7D0 = 0;
        if ( skills_1[1] > 1 )
            field_51C = 2;
        break;
    case 521:
        field_18C = 1;
        reset_forces();
        field_194 = 99;
        field_190 = 0;
        field_49A = 0;
        field_7D0 = 0;
        break;
    case 525:
    case 526:
        field_18C = 5;
        reset_forces();
        field_194 = 0;
        field_190 = 0;
        field_49A = 0;
        field_7D0 = 0;
        break;
    case 530:
    case 531:
        field_18C = 9;
        reset_forces();
        field_194 = 0;
        field_190 = 0;
        field_49A = 0;
        field_7D0 = 0;
        break;
    case 540:
    case 541:
        field_18C = 2;
        field_190 = 0;
        reset_forces();
        field_7DC = 0.0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        not_charge_attack = 1;
        break;
    case 542:
    case 543:
    {
        h_inerc *= 0.1;
        v_inerc *= 0.1;
        v_force = 0.025;
        field_18C = 2;
        field_190 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        field_7DC = 0.0;
        not_charge_attack = 1;
        float tmp[3];
        tmp[0] = 0;
        tmp[1] = 0;
        tmp[2] = 11;
        addbullet(this, NULL, 820, x, y, dir, -1, tmp, 3);
    }
    break;
    case 560:
    case 561:
        field_18C = 3;
        field_190 = 0;
        reset_forces();
        field_7DC = 0.0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        not_charge_attack = 1;
        break;
    case 562:
    case 563:
        field_7DC = 0.0;
        field_190 = 0;
        v_force = 0.0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_18C = 3;
        not_charge_attack = 1;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 606:
        reset_forces();
        field_194 = 99;
        field_190 = 0;
        field_49A = 0;
        field_7D0 = 0;
        break;
    case 611:
        field_7D0 = 0;
        field_7D2 = 0;
        field_190 = 1;
        reset_forces();
        break;
    default:
        char_c::set_seq_params();
        break;
    }
}








