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

    if ( controlling_type == CONTROL_PC_STORY )
    {
        if ( cards_added >= 1 )
        {
            switch ( cards_active[0]->id )
            {
            case 0:
            case 1:
            case 2:
            case 3:
                field_4AA = 2;
                field_534 = 0.25;
                field_55C = 2.0;
                field_538 = 0.0;
                field_86A = 1;
                if ( get_pframe()->extra1[4] == 1 )
                {
                    field_86A = 3;
                    field_55C = 3.5;
                }
                if ( get_pframe()->extra1[4] == 2 )
                {
                    field_86A = 3;
                    field_55C = 5.0;
                }
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                field_4AA = 2;
                field_534 = 0.25;
                field_55C = 1.0;
                field_538 = 0.0;
                field_86A = 1;
                if ( get_pframe()->extra1[4] == 1 )
                {
                    field_86A = 3;
                    field_55C = 6.0;
                }
                if ( get_pframe()->extra1[4] == 2 )
                {
                    field_86A = 3;
                    field_55C = 6.0;
                }
                break;
            default:
                break;
            }
        }
        if ( field_882 == 1 )
        {
            if ( field_188 >= max_health && field_574 == 0 )
            {
                field_86A = 2;
                field_882 = 2;
                flip_with_force();
                set_seq( 149);
                scene_add_effect(this, 53, x, y + 100.0, dir, 1);
                if ( cards_added >= 1 && cards_active[0]->id <= 7 )
                {
                    field_884 = 300;
                    field_886 = 300;
                }
            }
            if ( health <= 0 )
                field_882 = 2;
        }
        if ( field_884 > 0 )
        {
            if ( damage_limit > 0 && damage_limit < 100 )
                damage_limit = 0;
            if ( field_884 == 1 || health <= 0 )
            {
                field_4AA = 0;
                field_884 = 0;
                field_4BA = 0;
                field_188 = 0;
                field_820 = 0;
                field_81E = 1;
                field_81A = 0;
                field_81C = 0;
                field_818 = 0;
                field_882 = 1;
            }
            else
            {
                field_86A = 2;
                field_4AA = 2;
                field_538 = 1.0;
                field_534 = 1.0;
                field_884--;
                field_4BA = 6000;
            }
        }
        if ( health <= 0 )
            field_86A = 0;
    }

    if ( field_890 > 0 )
    {
        field_890--;
        field_54C = 0.0;

        if ( get_seq() >= 600 && get_seq() <= 689 && get_seq() != 610 && get_seq() != 660 )
            field_890 = 0;

        if ( (get_seq() == 610 || get_seq() == 660) && get_subseq() == 0 && get_frame() == 0 )
            field_890 = 0;

        if ( health <= 0 || enemy->health <= 0 )
            field_890 = 0;
    }

    if ( get_seq() > 149 && get_seq() < 159 )
    {
        if ( !bbarrier_show )
        {
            bbarrier_show = 1;

            if ( get_seq() > 149 && get_seq() < 154 )
                addbullet(this, NULL, 998, x + (57 * dir), y + 94.0, dir, 1, 0, 0);

            if ( get_seq() > 153 && get_seq() < 158 )
                addbullet(this, NULL, 998, x + (57 * dir), y + 60.0, dir, 1, 0, 0);

            if ( get_seq() == 158 )
                addbullet(this, NULL, 998, x + (57 * dir), y + 100.0, dir, 1, 0, 0);
        }
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
        char_h_move( 6.5);
        process();
        break;
    case 5:
        sub10func();
        char_h_move( -6.5);
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
            sub_6E28C0();
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
            char_h_move(0);
            v_inerc = 16.0;
            v_force = 0.75;
            field_49A = 0;
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
            sub_6E28C0();
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
            sub_6E28C0();
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
            char_h_move( -5.0);
            field_49A = 0;
        }
        break;
    case 9:
    case 11:
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
            if (dY() > 0)
                set_seq(2);
            else
                set_seq(0);
        }
        break;
    case 197:
        if ( get_subseq() != 0 && get_subseq() != 3 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                set_subseq(3);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }
        else
            sub10func();

        if ( process() )
        {
            if ( controlling_type == CONTROL_PC_STORY )
            {
                set_seq(700);
                field_51C = 3;
                field_520 = 3;
                break;
            }
            if ( dY() > 0 )
                set_seq( 1);
            else
                set_seq( 0);
        }
        if ( get_subseq() == 3 && get_frame() == 2 && get_frame_time() == 0 )
        {
            if ( enemy->x < x )
                dir = -1;
            if ( enemy->x > x )
                dir = 1;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = 15.5;
            v_inerc = 6.0;
            v_force = 0.4;
        }
        break;
    case 198:
        if ( get_subseq() != 0 && get_subseq() != 3 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                set_subseq(3);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }
        else
            sub10func();

        if ( process() )
        {
            if ( controlling_type == CONTROL_PC_STORY )
            {
                set_seq(700);
                field_51C = 3;
                field_520 = 3;
                break;
            }
            if ( dY() > 0 )
                set_seq( 1);
            else
                set_seq( 0);
        }
        if ( get_subseq() == 3 && get_frame() == 2 && get_frame_time() == 0 )
        {
            if ( enemy->x < x )
                dir = -1;
            if ( enemy->x > x )
                dir = 1;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = -15.5;
            v_inerc = 6.0;
            v_force = 0.4;
        }
        break;
    case 199:
        sub10func();
        if ( process() )
        {

            if ( controlling_type == CONTROL_PC_STORY )
            {
                set_seq( 700);
                field_51C = 3;
                field_520 = 3;
                break;
            }
            set_seq(0);
            if ( dY() > 0 )
                set_seq( 1);
        }
        if ( get_subseq() == 0 && get_frame() == 8 && get_frame_time() == 0 )
        {
            if ( enemy->x < x )
                dir = -1;
            if ( enemy->x > x )
                dir = 1;
        }
        break;
    case 200:
        sub10func();
        field_49A = 1;
        process();
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rng(100), y + scene_rand_rng(200), dir, 1);

            if ( dY() >= 0 )
            {
                field_7D0++;
                if ( (dX(dir) > 0 || field_7D0 <= 5) && field_7D0 <= 60 )
                {
                    if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
                    {
                        char_h_move( 11.5);
                        scene_add_effect(this, 125, (80 * dir) + x,  y + 80.0, dir, 1);
                        scene_add_effect(this,126, x, y + 80.0, dir, 1);
                        scene_play_sfx(31);
                    }
                }
                else
                    set_seq( 204);
            }
            else
            {
                if ( dX(dir) <= 0 )
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
            h_inerc += 0.75;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( !char_on_ground_flag() && get_elaps_frames() % 5 == 0 )
            scene_add_effect(this, 124, x + 50.0 - scene_rand_rng(100), y + scene_rand_rng(200), -dir, 1);

        if ( get_subseq() == 2 && get_elaps_frames() >= 12 )
        {
            next_subseq();
            break;
        }
        if ( process() )
        {
            set_seq( 0);
            reset_forces();
        }
        else
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                char_h_move( -11.5);
                scene_add_effect(this, 125, x, y + 80.0, -dir, 1);
                scene_add_effect(this, 126, x, y + 80.0, -dir, 1);
                scene_play_sfx(31);
            }
        }
        break;
    case 202:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
            set_seq( 10);
            break;
        }
        if ( get_subseq() == 1 || get_subseq() == 2 )
            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rng(100), y + scene_rand_rng(200), dir, 1);

        process();
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 &&  get_frame() == 0 && get_subseq() == 1 )
        {
            char_h_move( 11.5);
            v_inerc = 4.0;
            v_force = 0.5;
            scene_add_effect(this, 125, 80.0 * dir + x, y + 110.0, dir, 1);
            scene_add_effect(this, 126, x, y + 110.0, dir, 1);
            scene_play_sfx(31);
        }
        if ( get_subseq() == 2 )
            flip_with_force();
        break;
    case 203:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
            set_seq( 10);
            break;
        }
        if ( get_subseq() < 3 && get_elaps_frames() % 5 == 0 )
            scene_add_effect(this, 124, x + 50.0 - scene_rand_rng(100), y + scene_rand_rng(200), -dir, 1);
        process();
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
            {
                char_h_move( -11.5);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x, y + 120.0, -dir, 1);
                scene_add_effect(this, 126, x, y + 120.0, -dir, 1);
            }
            if ( get_subseq() == 2 )
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
            set_seq( 0);
            field_49A = 0;
        }
        break;
    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
    case 220:
    case 221:
    case 222:
        if ( get_subseq() == 0 )
            sub10func();
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( char_on_ground_flag() || v_inerc > 0.0 )
            field_522 = 2;
        if ( get_subseq() > 0 )
        {
            sub_6E28C0();
            v_inerc -= v_force;
            if ( v_inerc < -20.0 )
                v_inerc = -20.0;
        }
        if ( get_subseq() == 1 )
        {
            if ( v_inerc < 4.0 )
                set_subseq( 2);
        }
        process();
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            int32_t sq = get_seq();
            if (sq == 208 || sq == 220)
            {
                char_h_move( 0);
                v_inerc = 22.5;
                v_force = 0.85;
            }
            else if (sq == 209 || sq == 221)
            {
                char_h_move( 10);
                v_inerc = 18.0;
                v_force = 0.85;
            }
            else if (sq == 210 || sq == 222)
            {
                char_h_move( -10);
                v_inerc = 18.0;
                v_force = 0.85;
            }
            else if (sq == 211)
            {
                char_h_move( 3);
                v_inerc = 22.5;
                v_force = 0.85;
            }
            else if (sq == 212)
            {
                char_h_move( 10);
                v_inerc = 16.0;
                v_force = 0.7;
            }

            field_49A = 0;
            scene_add_effect(this, 63, x, y, dir, 1);
        }
        break;
    case 214:
        if ( process() )
        {
            set_seq( 9);
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
                scene_play_sfx(31);
            if (get_subseq() == 6 )
            {
                set_seq( 9);
                break;
            }
        }

        if ( dY() < 0)
        {
            field_7D2 = 90 - dX(dir) * 45;
        }
        else if (dY() == 0)
        {
            if (dX(dir) > 0 )
                field_7D2 = 0;
            else if (dX(dir) < 0 )
                field_7D2 = 180;
        }
        else if (dY() > 0)
        {
            field_7D2 = -90 - dX(dir) * 45;
        }

        if ( get_subseq() == 5 || get_subseq() == 6 )
            v_inerc -= v_force;

        if ( get_subseq() <= 0 || get_subseq() >= 5 )
        {
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                v_force = 0.0;
                v_inerc = 0.0;
                if ( get_subseq() >= 5 )
                {
                    set_seq( 10);
                    reset_forces();
                }
                else
                {
                    reset_ofs();
                    set_seq( 215);
                }
            }
            break;
        }
        field_7D6++;
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
            angZ = 180.0 - dash_angle;
        //angZ = 180 -angZ;

        if ( h_inerc < 0.0 )
        {
            if ( get_subseq() == 1 )
                set_subseq(3);
            else if ( get_subseq() == 2 )
                set_subseq(4);
        }
        else
        {
            if ( get_subseq() == 3 )
                set_subseq(1);
            else if ( get_subseq() == 4 )
                set_subseq(2);
        }

        if ( get_elaps_frames() % 5 == 1 )
        {
            float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
            float xx = cos_deg(dash_angle) * 100.0 * dir + x;
            scene_add_effect(this, 125, xx, yy, dir, 1);
        }

        if ( (keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
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
        }
        break;
    case 215:
        sub10func();
        if ( h_inerc > 0.0 )
        {
            h_inerc -= 0.75;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        else if ( h_inerc < 0.0 )
        {
            h_inerc += 0.75;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( process() )
            set_seq( 0);
        break;
    case 217:
        if ( process() )
        {
            set_seq( 9);
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
                scene_play_sfx(31);
            if (get_subseq() == 6 )
            {
                set_seq( 9);
                break;
            }
        }

        field_7D2 = atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);

        if ( get_subseq() == 5 || get_subseq() == 6 )
            v_inerc -= v_force;

        if ( get_subseq() <= 0 || get_subseq() >= 5 )
        {
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                v_force = 0.0;
                v_inerc = 0.0;
                if ( get_subseq() >= 5 )
                {
                    set_seq( 10);
                    reset_forces();
                }
                else
                {
                    reset_ofs();
                    set_seq( 215);
                }
            }
            break;
        }
        field_7D6++;
        field_7D4 = field_7D2 - dash_angle;
        if ( field_7D4 >180 )
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
            angZ = 180.0 - dash_angle;
//            angZ = 180 -angZ;

        if ( h_inerc < 0.0 )
        {
            if ( get_subseq() == 1 )
                set_subseq(3);
            else if ( get_subseq() == 2 )
                set_subseq(4);
        }

        if ( h_inerc >= 0 )
        {
            if ( get_subseq() == 3 )
                set_subseq(1);
            else if ( get_subseq() == 4 )
                set_subseq(2);
        }

        if ( get_elaps_frames() % 5 == 1 )
        {
            float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
            float xx = cos_deg(dash_angle) * 100.0 * dir + x;
            scene_add_effect(this, 125, xx, yy, dir, 1);
        }

        if ( (keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
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
        }
        break;
    case 223:
        sub10func();
        field_49A = 1;
        process();
        if ( get_subseq() == 1 )
        {
            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
                if ( !field_7D0 )
                {
                    char_h_move( 7.5);
                    scene_add_effect(this, 125, (80 * dir) + x, y + 80.0, dir, 1);
                    scene_add_effect(this, 126, x, y + 80.0, dir, 1);
                    scene_play_sfx(31);
                }

            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), scene_rand_rngf(200) + y, dir, 1);

            field_7D0++;

            if ( (dX(dir) <= 0 && field_7D0 > 15 ) || field_7D0 > 45 )
                set_seq( 204);
        }
        break;
    case 224:
        if ( get_subseq() == 0 || get_subseq() == 3 )
            sub10func();

        if ( get_subseq() == 3 )
        {
            h_inerc += 2.0;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( !char_on_ground_flag() &&
                get_elaps_frames() % 5 == 0 )
            scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), scene_rand_rngf(200) + y, -dir, 1);

        if ( get_subseq() < 3)
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                v_inerc = 0.0;
                v_force = 0.0;
                y = getlvl_height();
                set_subseq( 3);
                break;
            }
        }
        if ( process() )
        {
            set_seq( 0);
            h_inerc = 0.0;
            v_force = 0.0;
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            if ( !field_7D0 )
            {
                field_7D0 = 1;
                char_h_move( -14.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, x, y + 80.0, -dir, 1);
                scene_add_effect(this, 126, x, y + 80.0, -dir, 1);
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
            set_seq( 10);
            break;
        }
        if ( get_subseq() >= 2 )
            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), scene_rand_rngf(200) + y, -dir, 1);

        if ( process() )
            set_seq( 9);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            char_h_move( -11.0);
            v_inerc = 4.0;
            v_force = 0.5;
            scene_add_effect(this, 125, x, y + 120.0, -dir, 1);
            scene_add_effect(this, 126, x, y + 120.0, -dir, 1);
            scene_play_sfx(31);
        }
        break;
    case 226:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            reset_forces();
            y = getlvl_height();
            set_seq( 10);
            break;
        }

        if ( get_subseq() == 1 )
            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), scene_rand_rngf(200) + y, dir, 1);

        if ( process() )
            set_seq( 9);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
            {
                field_7D0 = 0;
                char_h_move( 11.0);
                v_inerc = 4.0;
                v_force = 0.5;
                scene_add_effect(this, 125, (80 * dir) + x, y + 110.0, dir, 1);
                scene_add_effect(this, 126, x, y + 110.0, dir, 1);
                scene_play_sfx(31);
            }
            if ( get_subseq() == 2 )
                flip_with_force();
        }
        break;
    case 300:
    case 330:
        sub10func();
        /*if ( !get_true(0) )*/
        {
            if ( field_49A )
            {
                h_inerc -= 0.5;
                if ( h_inerc < 0.0 )
                {
                    h_inerc = 0.0;
                    field_49A = 0;
                }
            }
            if ( process() )
                set_seq( 0);
            if ( get_frame_time() == 0 && get_frame() == 3 )
            {
                scene_play_sfx(27);
                field_49A = 0;
            }
        }
        break;
    case 301:
        sub10func();
        /*if ( get_true(0) )
          break;*/
        if ( field_49A )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
            {
                h_inerc = 0.0;
                field_49A = 0;
            }
        }

        if ( get_frame() > 3 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
            {
                h_inerc = 0.0;
                field_49A = 0;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_frame_time() == 0 )
        {
            if (get_frame() == 3)
            {
                h_inerc = 5.0;
                play_sfx( 51);
            }
            if (get_frame() == 5)
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 4.0;

                CharFrameData *frm = get_pframe();
                addbullet(this, NULL, 848, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
            }
            if ( get_frame() == 6 )
                field_190 = 0;
            if ( get_frame() == 7 )
                field_190 = 0;
        }

        break;
    case 302:
        sub10func();
        /*if ( get_true(1) )
          break;*/
        if ( keyDown(INP_A) == 0 )
            not_charge_attack = 0;
        if ( h_inerc > 0.0 )
        {
            h_inerc -= 0.75;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( process() ||
                (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1) )
        {
            set_seq( 0);
            break;
        }
        if (get_subseq() == 1 && get_frame_time() == 0 && get_frame() == 7)
        {
            h_inerc = 15.0;
            play_sfx( 52);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            CharFrameData *frm = get_pframe();
            addbullet(this, NULL, 990, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
        }
        if (get_subseq() == 0 && get_frame_time() == 0)
        {
            if (get_frame() == 4 && not_charge_attack)
            {
                scene_add_effect(this, 62, x, y + 205.0, dir, 1);
                next_subseq();
                break;
            }
            if (get_frame() == 6)
            {
                h_inerc = 12.5;
                play_sfx( 52);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                CharFrameData *frm = get_pframe();
                addbullet(this, NULL, 990, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
            }
        }
        break;
    case 303:
        sub10func();
        /*if ( !get_true(0) )*/
        {
            if ( field_49A > 0 )
            {
                h_inerc -= 0.6;
                if ( h_inerc < 0.0 )
                {
                    h_inerc = 0.0;
                    field_49A = 0;
                }
            }
            if ( process() )
                set_seq( 2);
            if ( get_frame_time() == 0 && get_frame() == 2 )
                scene_play_sfx(27);
        }
        break;
    case 304:
        sub10func();
        /*if ( !get_true(1) )*/
        {
            if ( get_frame() >= 9 && h_inerc > 0.0 )
            {
                h_inerc -= 1.0;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            if ( keyDown(INP_A) == 0)
                not_charge_attack = 0;
            if ( process() )
                set_seq( 0);
            if ( get_subseq() == 0 && get_frame_time() == 0 )
            {
                if ( get_frame() == 3 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 7.0;

                    CharFrameData *frm = get_pframe();
                    addbullet(this, NULL, 848, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
                }
                if ( get_frame() == 5 )
                {
                    h_inerc = 13.0;
                    scene_play_sfx(29);
                }
            }
        }
        break;
    case 305:
        sub10func();
        /*if ( !get_true(1) )*/
        {
            if ( get_frame() >= 4 )
            {
                h_inerc -= 1.0;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            if ( process() )
                set_seq( 0);
            if ( get_frame_time() == 0 && get_frame() == 4 )
                scene_play_sfx(28);
        }
        break;
    case 306:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 9);
        if ( get_frame_time() == 0 && get_frame() == 3 )
            scene_play_sfx(28);
        break;
    case 307:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 9);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            set_seq( 9);
            break;
        }
        if ( get_frame_time() == 0)
        {
            if ( get_frame() == 6 )
            {
                play_sfx( 52);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                CharFrameData *frm = get_pframe();
                addbullet(this, NULL, 990, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
            }
            if (get_frame() == 13)
                v_force = 0.5;
        }
        break;
    case 308:
        if ( keyDown(INP_A) == 0 )
            not_charge_attack = 0;

        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 9);
        if ( get_subseq() == 1 )
        {
            if ( get_frame_time() == 0 && get_frame() == 0 )
            {
                h_inerc *= 0.2;
                v_inerc *= 0.2;
                v_force = 0.1;
                play_sfx( 50);
            }
            if ( field_190 )
            {
                field_7D0++;
                if ( field_7D0 >= 3 && field_194 > 0 )
                {
                    field_7D0 = 0;
                    field_190 = 0;
                }
            }
            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 6.0;

                addbullet(this, NULL, 848, (90.0 - scene_rand_rngf(100)) * dir + x,    scene_rand_rngf(100) + y + 20.0 , dir, 1, tmp, 3);
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 0 )
            v_force = 0.5;
        break;
    case 309:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 9);
        if ( get_frame_time() == 0 && get_frame() == 0 )
        {
            if (get_subseq() == 1)
            {
                scene_play_sfx(29);
                h_inerc = 7.0;
                v_inerc = 18.5;
                v_force = 0.1;
            }
            if ( get_subseq() == 2 )
            {
                h_inerc = h_inerc * 0.5;
                v_inerc = v_inerc * 0.25;
                v_force = 0.5;
            }
        }
        break;
    case 310:
        if ( get_subseq() == 2 )
        {
            h_inerc -= 1.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            sub10func();
        }
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                set_subseq( 2);
                y = getlvl_height();
                v_inerc = 0.0;
                v_force = 0.0;
                field_190 = 1;
            }
        }
        if ( process() )
        {
            if ( dY() >= 0 )
                set_seq(3);
            else
                set_seq(2);
        }
        else
        {
            if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 7 )
                scene_play_sfx(29);
        }
        break;
    case 320:
        sub10func();
        /*if ( !get_true(0) )*/
        {
            if ( get_frame() > 1 )
            {
                h_inerc -= 2.0;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            if ( process() )
                set_seq( 0);
            if ( get_frame_time() == 0 && get_frame() == 2 )
            {
                scene_play_sfx(28);
                field_49A = 0;
            }
        }
        break;
    case 321:
        sub10func();
        /*if ( !get_true(0) )*/
        {
            if ( get_frame() > 3 )
            {
                h_inerc -= 0.5;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            if ( process() )
                set_seq( 0);
            if ( get_frame_time() == 0 )
            {
                if ( get_frame() == 3 )
                {
                    play_sfx( 51);
                    h_inerc = 7.5;
                    field_49A = 0;
                }
                if ( get_frame() == 5 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 4.0;

                    CharFrameData *frm = get_pframe();
                    addbullet(this, NULL, 848, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
                }
                if ( get_frame() == 6 )
                    field_190 = 0;

                if ( get_frame() == 7 )
                    field_190 = 0;
            }
        }
        break;
    case 322:
        sub10func();
        /*if ( !get_true(1) )*/
        {
            if ( get_frame() > 5 )
            {
                h_inerc -= 3.0;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            if ( process() )
                set_seq( 0);
            if ( get_frame_time() == 0 && get_frame() == 4 )
            {
                h_inerc = 15.0;
                play_sfx( 52);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                CharFrameData *frm = get_pframe();
                addbullet(this, NULL, 990, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
            }
        }
        break;
    case 400:
        sub10func();
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 1 )
        {
            if ( get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 )
            {
                if ( !not_charge_attack )
                {
                    next_subseq();
                    break;
                }
                scene_add_effect(this, 62, 7 * dir + x , y + 110.0, dir, 1);
            }
            field_7D0++;
            if ( !not_charge_attack && get_elaps_frames() >= 15 )
            {
                next_subseq();
                return;
            }
            if ( get_elaps_frames() >= 75 )
            {
                next_subseq();
                return;
            }
        }
        if ( get_subseq() == 2 &&  get_frame_time() == 0 && get_frame() == 1 )
        {
            play_sfx( 0);
            add_card_energy( 30);
            spell_energy_spend(200, 45);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;

            addbullet(this, NULL, 800, 71.0 * dir + x , y + 107.0, dir, 1, tmp, 3);
            sub_486FD0( 15.0, -15.0);
            field_190 = 1;

            if (field_7D0 >= 60)
            {
                for (int32_t i = 0; i< 5; i++)
                {
                    float tmp[3];
                    tmp[0] = field_7F0 + scene_rand_rngf(20) * 0.1 + i * 4.0 - 11.0;
                    tmp[1] = scene_rand_rng(50) * 0.1 + 12.5;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }

                for (int32_t i = 0; i< 4; i++)
                {
                    float tmp[3];
                    tmp[0] = field_7F0 + scene_rand_rngf(30) * 0.1 + i * 5.0 - 9.0;
                    tmp[1] = scene_rand_rng(50) * 0.1 + 10.0;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }
                break;
            }
            if (field_7D0 >= 15)
            {
                for (int32_t i = 0; i< 6; i++)
                {
                    float tmp[3];
                    tmp[0] = field_7F0 + scene_rand_rngf(20) * 0.1 + i * 4.0 - 11.0;
                    tmp[1] = scene_rand_rng(50) * 0.1 + 12.5;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }
                break;
            }

            if ( field_7D0 == 0 )
            {
                for (int32_t i = 0; i< 4; i++)
                {
                    float tmp[3];
                    tmp[0] = field_7F0 + scene_rand_rngf(30) * 0.1 + i * 5.0 - 9.0;
                    tmp[1] = scene_rand_rng(50) * 0.1 + 10.0;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }
            }
        }
        break;
    case 401:
        sub10func();
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 1 )
        {
            if ( get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 && !not_charge_attack )
            {
                next_subseq();
                break;
            }
            field_7D0++;
            if ( (!not_charge_attack && get_elaps_frames() >= 15) || get_elaps_frames() >= 60 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 1 )
        {
            play_sfx( 0);
            add_card_energy( 30);
            spell_energy_spend(200, 45);
            field_190 = 1;
            if ( field_7D0 == 0)
            {
                sub_486FD0( 10.0, -10.0);
                float tmp[3];
                tmp[0] = field_7F0;
                tmp[1] = 20.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 801, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
            }
            if ( field_7D0 >= 15 )
            {
                sub_486FD0( 10.0, -10.0);
                float tmp[3];
                tmp[0] = field_7F0;
                tmp[1] = 20.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 801, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
            }
        }
        break;
    case 402:
        sub10func();
        if ( process() )
            set_seq( 2);
        if ( get_frame_time() == 0 && get_frame() == 5 )
        {
            add_card_energy( 30);
            spell_energy_spend(200, 45);
            field_190 = 1;
            play_sfx( 0);

            float tmp[3];
            tmp[0] = 60;
            tmp[1] = 27.5;
            tmp[2] = 7.0;

            addbullet(this, NULL, 802, (51 * dir) + x, y + 36.0, dir, 1, tmp, 3);
        }
        break;
    case 404:
        if ( get_subseq() == 3 )
            sub10func();
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 3 )
        {
            set_subseq( 3);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
            set_seq( 9);

        if ( get_subseq() == 1 )
        {
            if ( get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 )
            {
                if ( !not_charge_attack )
                {
                    next_subseq();
                    break;
                }
                scene_add_effect(this, 62, (7 * dir) + x, y + 110.0, dir, 1);
            }
            field_7D0++;
            if ( (!not_charge_attack && get_elaps_frames() >= 15)
                    || get_elaps_frames() >= 75 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 2  && get_frame_time() == 0)
        {
            if ( get_frame() == 6 )
            {
                v_force = 0.5;
                break;
            }

            if (get_frame() == 1)
            {
                play_sfx( 0);
                add_card_energy( 30);
                spell_energy_spend(200, 45);
                field_190 = 1;

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;

                addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                sub_486FD0( 15.0, -15.0);

                if ( field_7D0 >= 60 )
                {
                    for (int32_t i = 0; i< 5; i++)
                    {
                        tmp[0] = field_7F0 + scene_rand_rngf(20) * 0.1 + i * 4.0 - 11.0;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 12.5;
                        tmp[2] = 0.0;

                        addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                    }
                    for (int32_t i = 0; i< 4; i++)
                    {
                        tmp[0] = field_7F0 + scene_rand_rngf(30) * 0.1 + i * 5.0 - 9.0;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 10.0;
                        tmp[2] = 0.0;

                        addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                    }
                    break;
                }
                if (field_7D0 >= 15)
                {
                    for (int32_t i = 0; i< 6; i++)
                    {
                        tmp[0] = field_7F0 + scene_rand_rngf(20) * 0.1 + i * 4.0 - 11.0;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 12.5;
                        tmp[2] = 0.0;

                        addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                    }
                    break;
                }

                if ( field_7D0 == 0 )
                {
                    for (int32_t i = 0; i< 4; i++)
                    {
                        tmp[0] = field_7F0 + scene_rand_rngf(30) * 0.1 + i * 5.0 - 9.0;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 10.0;
                        tmp[2] = 0.0;

                        addbullet(this, NULL, 800, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                    }
                }
            }
        }
        break;
    case 405:
        if ( get_subseq() == 3 )
            sub10func();
        if ( keyDown(INP_B) == 0)
            not_charge_attack = 0;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 3 )
        {
            set_subseq( 3);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
            set_seq( 9);

        if ( get_subseq() == 1 )
        {
            if ( get_frame_time() == 0 && get_frame() == 0 && get_elaps_frames() == 0 && !not_charge_attack )
            {
                next_subseq();
                break;
            }
            field_7D0++;
            if ( (!not_charge_attack && get_elaps_frames() >= 15)
                    || get_elaps_frames() >= 60 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 )
        {
            if ( get_frame() == 6 )
            {
                v_force = 0.5;
                break;
            }

            if ( get_frame() == 1 )
            {
                play_sfx( 0);
                add_card_energy( 30);
                spell_energy_spend(200, 45);
                field_190 = 1;
                if ( field_7D0 == 0)
                {
                    sub_486FD0( 10.0, -10.0);
                    float tmp[3];
                    tmp[0] = field_7F0;
                    tmp[1] = 20.0;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 801, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }
                if ( field_7D0 >= 15 )
                {
                    sub_486FD0( 10.0, -10.0);
                    float tmp[3];
                    tmp[0] = field_7F0;
                    tmp[1] = 20.0;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 801, (71 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }
            }
        }
        break;
    case 406:
        if ( get_subseq() == 1 )
            sub10func();
        if ( keyDown(INP_B) == 0)
            not_charge_attack = 0;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 1 )
        {
            set_subseq( 1);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            set_seq( 9);

        if ( get_subseq() == 0 && get_frame_time() == 0 )
        {
            if (get_frame() == 5)
            {
                add_card_energy( 30);
                spell_energy_spend(200, 45);
                field_190 = 1;
                play_sfx( 0);
                float tmp[3];
                tmp[0] = 60.0;
                tmp[1] = 27.5;
                tmp[2] = 7.0;
                addbullet(this, NULL, 802, (43 * dir) + x, y + 96.0, dir, 1, tmp, 3);
            }
            if ( get_frame() == 7 )
                v_force = 0.5;
        }
        break;
    case 408:
        sub10func();
        if ( get_subseq() >= 1 )
        {
            h_inerc -= 0.35;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            if ( get_subseq() == 1 )
            {
                if ( get_elaps_frames() % 3 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(90) - 45.0;
                    tmp[1] = scene_rand_rngf(5) + 20.0;
                    tmp[2] = 1.0;
                    addbullet(this, NULL, 848, (58 * dir) + x, y + 107.0, dir, 1, tmp, 3);
                }
                if ( get_elaps_frames() % 6 == 0 )
                    play_sfx( 53);
                if ( field_190 )
                {
                    field_7D0++;
                    if ( field_7D0 >= 5 && field_194 > 0 )
                    {
                        field_7D0 = 0;
                        field_190 = 0;
                    }
                }
            }
        }
        if ( process() )
            set_seq( 0);
        break;
    case 409:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq( 10);
            reset_forces();
            y = getlvl_height();
            break;
        }
        if ( process() )
            set_seq( 9);
        break;
    case 410:
        sub10func();
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            set_seq( 0);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 &&  get_frame() == 3 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 27.5;
            tmp[2] = 0.0;

            addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

            tmp[0] = 40.0;
            addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

            tmp[0] = -40.0;
            addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

            play_sfx( 2);
            spell_energy_spend(200, 60);
            field_190 = 1;
            add_card_energy( 50);

            for (int32_t i=0; i < 12; i++)
            {
                tmp[0] = i * 30.0;
                tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                tmp[2] = 4.0;
                addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);
            }
        }
        break;
    case 411:
        sub10func();
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            set_seq( 0);

        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 40.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 806, (68.0 * dir) + x, y + 108.0, dir, 1, tmp, 3);

            play_sfx( 2);
            spell_energy_spend(200, 60);
            field_190 = 1;
            add_card_energy( 50);

            for (int32_t i=0; i < 12; i++)
            {
                tmp[0] = i * 30.0;
                tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                tmp[2] = 4.0;
                addbullet(this, NULL, 806, (68.0 * dir) + x, y + 108.0, dir, 1, tmp, 3);
            }
        }
        break;
    case 412:
        sub10func();
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            CharFrameData *frm = get_pframe();
            addbullet(this, NULL, 808, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
        }

        if ( get_subseq() == 1 && (!not_charge_attack || get_elaps_frames() >= 40) )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 1 )
        {
            field_190 = 1;
            spell_energy_spend(200, 60);
            add_card_energy( 50);
        }
        break;
    case 414:
        if ( get_subseq() == 2 )
            sub10func();
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 2 )
        {
            set_subseq( 2);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0  && ( get_subseq() == 1 || get_subseq() == 2))
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0)
        {
            if ( get_frame() == 3 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 27.5;
                tmp[2] = 0.0;

                addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

                tmp[0] = 40.0;
                addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

                tmp[0] = -40.0;
                addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

                play_sfx( 2);
                spell_energy_spend(200, 60);
                field_190 = 1;
                add_card_energy( 50);

                for (int32_t i=0; i < 12; i++)
                {
                    tmp[0] = i * 30.0;
                    tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                    tmp[2] = 4.0;
                    addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);
                }
            }
            if ( get_frame() == 12 )
                v_force = 0.5;
        }
        break;
    case 415:
        if ( get_subseq() == 2 )
            sub10func();
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 2 )
        {
            set_subseq( 2);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0  && ( get_subseq() == 1 || get_subseq() == 2))
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0)
        {
            if ( get_frame() == 3 )
            {
                add_card_energy( 50);
                play_sfx( 2);
                field_190 = 1;
                spell_energy_spend(200, 60);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 40.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 806, (68.0 * dir) + x, y + 108.0, dir, 1, tmp, 3);

                for (int32_t i=0; i < 12; i++)
                {
                    tmp[0] = i * 30.0;
                    tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                    tmp[2] = 4.0;
                    addbullet(this, NULL, 806, (68.0 * dir) + x, y + 108.0, dir, 1, tmp, 3);
                }
            }
            if ( get_frame() == 13 )
                v_force = 0.5;
        }
        break;
    case 416:
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( get_subseq() == 3 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                set_subseq(3);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            CharFrameData *frm = get_pframe();
            addbullet(this, NULL, 808, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
        }
        if ( get_subseq() == 1 && (!not_charge_attack || get_elaps_frames() >= 40) )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 )
        {
            if ( get_frame() == 1 )
            {
                field_190 = 1;
                spell_energy_spend(200, 60);
                add_card_energy( 50);
            }
            if ( get_frame() == 6 )
                v_force = 0.5;
        }
        break;
    case 418:
        sub10func();
        if ( get_frame() >= 2 )
            h_inerc -= 0.5;
        if ( h_inerc < 0.0 )
            h_inerc = 0.0;
        if ( process() )
            set_seq( 0);
        if ( get_frame_time() == 0 )
        {
            if ( get_frame() == 1 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 7.0;

                CharFrameData *frm = get_pframe();
                addbullet(this, NULL, 848, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
            }
            if ( get_frame() == 2 )
            {
                scene_play_sfx(29);
                field_49A = 0;
            }
        }
        break;
    case 500:
        sub10func();
        field_18C = 0;
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
            set_seq( 0);

        if ( get_subseq() == 1)
        {
            if ( !not_charge_attack || get_elaps_frames() > 180)
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() == 0)
            {
                play_sfx( 18);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;
                addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
            }
            int32_t delim = 15;
            if ( skills_1[0] >= 1 )
                delim = 12;
            if ( skills_1[0] >= 2 )
                delim = 11;
            if ( skills_1[0] >= 3 )
                delim = 10;
            if ( skills_1[0] >= 4 )
                delim = 8;
            field_7D2++;
            if ( field_7D2 % delim == 0 )
            {
                field_7D0++;
                if ( field_7D0 == 10 )
                {
                    float tmp[3];
                    tmp[0] = 7.0;
                    tmp[1] = 0.4;
                    tmp[2] = 10.0;
                    addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
                    play_sfx( 15);
                }
            }
            if ( field_7D0 > 10 )
                field_7D0 = 10;
            if ( skills_1[0] >= 1 && keyDown(INP_C) >= 1 )
            {
                spell_energy_spend(200, 120);
                add_card_energy( 20);
                set_subseq( 5);
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            field_7D4 = 1;
        }
        if ( get_subseq() == 3 && field_7D0 == 0 )
        {
            next_subseq();
            break;
        }
        if ( field_7D4 == 1 && field_7D0 > 0 )
        {
            if ( field_7D6 % 5 == 0 )
            {
                play_sfx( 5);
                field_7D0--;
                sub_486FD0( 10.0, -10.0);

                float tmp[3];
                tmp[0] = field_7F0;
                tmp[1] = 35.0;
                tmp[2] = 5.0;

                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                tmp[2] = 4.0;
                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
            }
            field_7D6 ++;
        }
        break;
    case 501:
        sub10func();
        field_18C = 0;
        if ( !keyDown(INP_C) )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
            set_seq( 0);

        if ( get_subseq() == 1 )
        {
            if ( (!not_charge_attack && get_elaps_frames() > 10)
                    || get_elaps_frames() > 180 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() == 0)
            {
                play_sfx( 18);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;
                addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
            }
            int32_t delim = 15;
            if ( skills_1[0] >= 1 )
                delim = 12;
            if ( skills_1[0] >= 2 )
                delim = 11;
            if ( skills_1[0] >= 3 )
                delim = 10;
            if ( skills_1[0] >= 4 )
                delim = 8;
            field_7D2++;
            if ( field_7D2 % delim == 0 )
            {
                field_7D0++;
                if ( field_7D0 == 15 )
                {
                    float tmp[3];
                    tmp[0] = 7.0;
                    tmp[1] = 0.4;
                    tmp[2] = 10.0;
                    addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
                    play_sfx( 15);
                }
            }
            if ( field_7D0 > 15 )
                field_7D0 = 15;
            if ( skills_1[0] >= 1 && keyDown(INP_B) >= 1 )
            {
                spell_energy_spend(200, 120);
                add_card_energy( 20);
                set_subseq( 5);
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            field_7D4 = 1;
        }
        if ( get_subseq() == 3 && field_7D0 == 0 )
        {
            next_subseq();
            break;
        }
        if ( field_7D4 == 1 && field_7D0 > 0 )
        {
            if ( field_7D6 % 5 == 0 )
            {
                play_sfx( 5);
                field_7D0--;
                sub_486FD0( 10.0, -10.0);

                float tmp[3];
                tmp[0] = field_7F0;
                tmp[1] = 35.0;
                tmp[2] = 5.0;

                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                tmp[2] = 4.0;
                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
            }
            field_7D6 ++;
        }
        break;
    case 502:
        if ( get_subseq() == 6 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                set_subseq( 6);
                reset_forces();
                break;
            }
        }
        field_18C = 0;
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 5 || get_subseq() == 6 )
                set_seq( 9);
        }
        if ( get_subseq() == 1 )
        {
            if ( (!not_charge_attack && get_elaps_frames() > 10)
                    || get_elaps_frames() > 180 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() == 0)
            {
                play_sfx( 18);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;
                addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
            }
            int32_t delim = 15;
            if ( skills_1[0] >= 1 )
                delim = 12;
            if ( skills_1[0] >= 2 )
                delim = 11;
            if ( skills_1[0] >= 3 )
                delim = 10;
            if ( skills_1[0] >= 4 )
                delim = 8;
            field_7D2++;
            if ( field_7D2 % delim == 0 )
            {
                field_7D0++;
                if ( field_7D0 == 10 )
                {
                    float tmp[3];
                    tmp[0] = 7.0;
                    tmp[1] = 0.4;
                    tmp[2] = 10.0;
                    addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
                    play_sfx( 15);
                }
            }
            if ( field_7D0 > 10 )
                field_7D0 = 10;
            if ( skills_1[0] >= 1 && keyDown(INP_C) >= 1 )
            {
                spell_energy_spend(200, 120);
                add_card_energy( 20);
                v_force = 0.5;
                set_subseq( 5);
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            field_7D4 = 1;
        }
        if ( get_subseq() == 3 && field_7D0 == 0 )
        {
            next_subseq();
            break;
        }

        if ( field_7D4 == 1 && (get_subseq() == 2 || get_subseq() == 3 || get_subseq() == 4) && field_7D0 > 0 ) //sic //MAY BE HACK
        {
            if ( field_7D6 % 5 == 0 )
            {
                play_sfx( 5);
                field_7D0--;
                sub_486FD0( 10.0, -10.0);

                float tmp[3];
                tmp[0] = field_7F0;
                tmp[1] = 35.0;
                tmp[2] = 5.0;

                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                tmp[2] = 4.0;
                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
            }
            field_7D6 ++;
        }
        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 3 )
            v_force = 0.5;
        break;
    case 503:
        if ( get_subseq() == 6 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                set_subseq( 6);
                reset_forces();
                break;
            }
        }
        field_18C = 0;
        if ( keyDown(INP_C) == 0)
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 5 || get_subseq() == 6 )
                set_seq( 9);
        }
        if ( get_subseq() == 1 )
        {
            if ( (!not_charge_attack && get_elaps_frames() > 10)
                    || get_elaps_frames() > 180 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() == 0)
            {
                play_sfx( 18);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;
                addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
            }
            int32_t delim = 15;
            if ( skills_1[0] >= 1 )
                delim = 12;
            if ( skills_1[0] >= 2 )
                delim = 11;
            if ( skills_1[0] >= 3 )
                delim = 10;
            if ( skills_1[0] >= 4 )
                delim = 8;
            field_7D2++;
            if ( field_7D2 % delim == 0 )
            {
                field_7D0++;
                if ( field_7D0 == 15 )
                {
                    float tmp[3];
                    tmp[0] = 7.0;
                    tmp[1] = 0.4;
                    tmp[2] = 10.0;
                    addbullet(this, NULL, 810, x, y + 220.0, dir, 1, tmp, 3);
                    play_sfx( 15);
                }
            }
            if ( field_7D0 > 15 )
                field_7D0 = 15;
            if ( skills_1[0] >= 1 && keyDown(INP_B) >= 1 )
            {
                spell_energy_spend(200, 120);
                add_card_energy( 20);
                v_force = 0.5;
                set_subseq( 5);
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            field_7D4 = 1;
        }
        if ( get_subseq() == 3 && field_7D0 == 0 )
        {
            next_subseq();
            break;
        }
        if ( field_7D4 == 1
                && (get_subseq() == 2 || get_subseq() == 3 || get_subseq() == 4)
                && field_7D0 > 0 )
        {
            if ( field_7D6 % 5 == 0 )
            {
                play_sfx( 5);
                field_7D0--;
                sub_486FD0( 10.0, -10.0);

                float tmp[3];
                tmp[0] = field_7F0;
                tmp[1] = 35.0;
                tmp[2] = 5.0;

                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                tmp[2] = 4.0;
                addbullet(this, NULL, 810, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
            }
            field_7D6 ++;
        }
        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 3 )
            v_force = 0.5;
        break;
    case 505:
        sub10func();
        field_18C = 4;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 1 && get_elaps_frames() >= 12 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            play_sfx( 6);

            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            tmp[3] = 0.0;

            float yy = getlvl_height((150 * dir) + x);
            addbullet(this, NULL, 811, (150 * dir) + x, yy, dir, 1, tmp, 4);

            tmp[2] = 4.0;
            addbullet(this, NULL, 811, (150 * dir) + x, yy, dir, 1, tmp, 4);
        }
        break;
    case 506:
        sub10func();
        field_18C = 4;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 1 && get_elaps_frames() >= 32 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            play_sfx( 6);

            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            tmp[3] = 120.0;

            float yy = getlvl_height((150 * dir) + x);
            addbullet(this, NULL, 811, (150 * dir) + x, yy, dir, 1, tmp, 4);

            tmp[2] = 4.0;
            addbullet(this, NULL, 811, (150 * dir) + x, yy, dir, 1, tmp, 4);
        }
        break;
    case 510:
        sub10func();
        field_18C = 8;
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            play_sfx( 8);
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 15.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 812, (86 * dir) + x, y + 117.0, dir, 1, tmp, 3);

            tmp[0] = -30.0;
            addbullet(this, NULL, 812, (86 * dir) + x, y + 117.0, dir, 1, tmp, 3);

            tmp[0] = 30.0;
            addbullet(this, NULL, 812, (86 * dir) + x, y + 117.0, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 3 && get_elaps_frames() >= 8 )
        {
            next_subseq();
            break;
        }
        break;
    case 512:
        if ( get_subseq() == 5 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                set_subseq( 5);
                y = getlvl_height();
                break;
            }
        }
        field_18C = 8;
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            play_sfx( 8);
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 15.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 812, (86 * dir) + x, y + 117.0, dir, 1, tmp, 3);

            tmp[0] = -30.0;
            addbullet(this, NULL, 812, (86 * dir) + x, y + 117.0, dir, 1, tmp, 3);

            tmp[0] = 30.0;
            addbullet(this, NULL, 812, (86 * dir) + x, y + 117.0, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 3 && get_elaps_frames() >= 8 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 2 )
            v_force = 0.5;
        break;
    case 520:
        sub10func();
        field_18C = 1;
        if ( keyDown(INP_B) == 0)
            not_charge_attack = 0;
        if ( get_subseq() == 1 )
        {
            h_inerc += 0.2;
            if ( h_inerc > 12.5 )
                h_inerc = 12.5;
            if ( field_7D0 == 1 )
            {
                h_inerc *= -0.5;
                next_subseq();
                //shake_camera(5.0); //HACK
                break;
            }
            if ( get_elaps_frames() >= 120 || (!not_charge_attack && get_elaps_frames() >= 30) )
            {
                set_subseq( 3);
                break;
            }
        }

        if ( get_subseq() == 2 )
        {
            h_inerc += 0.25;
            if ( skills_1[1] >= 3 )
                h_inerc += 0.1;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }

        if ( get_subseq() == 3 )
        {
            h_inerc -= 0.25;
            if ( h_inerc < 0 )
                h_inerc = 0;
        }
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame() == 6 )
        {
            if (get_frame_time() == 0)
            {
                spell_energy_spend(200, 120);
                add_card_energy( 50);
                play_sfx( 9);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet(this, NULL, 815, (90 * dir) + x, y + 50.0, dir, -1, tmp, 3);

                tmp[2] = 4.0;
                addbullet(this, NULL, 815, (90 * dir) + x, y + 50.0, dir, -1, tmp, 3);
            }
            if ( skills_1[1] >= 1 && get_frame_time() >= 2 )
            {
                next_frame();
                break;
            }
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
        {
            if ( get_subseq() == 1 )
                h_inerc = 3.0;
            if ( get_subseq() == 3)
                set_seq( 0);
        }
        break;
    case 521:
        sub10func();
        field_18C = 1;
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( get_subseq() == 1 )
        {
            h_inerc += 0.05;
            if ( h_inerc > 12.5 )
                h_inerc = 12.5;
            if ( field_7D0 == 1 )
            {
                h_inerc *= -0.5;
                next_subseq();
                //shake_camera(5.0); //HACK
                break;
            }
            if ( get_elaps_frames() >= 120 || (!not_charge_attack && get_elaps_frames() >= 30) )
            {
                set_subseq( 3);
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            h_inerc += 0.25;
            if ( skills_1[1] >= 3 )
                h_inerc += 0.1;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }

        if ( get_subseq() == 3 )
        {
            h_inerc -= 0.25;
            if ( h_inerc < 0 )
                h_inerc = 0;
        }
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame() == 6 )
        {
            if (get_frame_time() == 0)
            {
                spell_energy_spend(200, 120);
                add_card_energy( 50);
                play_sfx( 9);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 6.0;
                addbullet(this, NULL, 815, (90 * dir) + x, y + 50.0, dir, -1, tmp, 3);

                tmp[2] = 4.0;
                addbullet(this, NULL, 815, (90 * dir) + x, y + 50.0, dir, -1, tmp, 3);
            }

            if ( (skills_1[1] >= 1 && get_frame_time() >= 15) ||
                    (skills_1[1] >= 4 && get_frame_time() >= 11) )
            {
                next_frame();
                break;
            }
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
        {
            if ( get_subseq() == 1 )
                h_inerc = 3.0;
            if ( get_subseq() == 3)
                set_seq( 0);
        }
        break;
    case 525:
    case 526:
        field_18C = 5;
        if ( get_subseq() == 1 )
        {
            if ( field_190 )
            {
                play_sfx( 4);
                set_subseq( 2);
                h_inerc = -8.0;
                break;
            }
            if ( get_elaps_frames() >= 20 )
            {
                set_subseq( 3);
                h_inerc = 10.0;
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            h_inerc += 0.5;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( get_subseq() == 3 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0 )
                h_inerc = 0;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 &&  get_frame_time() == 0 &&  get_frame() == 0  &&  get_subseq() == 1 )
        {
            play_sfx( 11);
            scene_add_effect(this, 127, x, y, dir, -1);
            spell_energy_spend(200, 120);
            add_card_energy( 50);

            if (sq == 525)
                h_inerc = 15.0;
            else if (sq == 526)
                h_inerc = 25.0;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;

            addbullet(this, NULL, 816, x, y, dir, 1, tmp, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3)
            set_seq( 0);
        break;
    case 527:
    case 528:
        field_18C = 5;
        if ( get_subseq() == 4 )
            sub10func();
        if ( get_subseq() == 1 )
        {
            if ( field_190 )
            {
                play_sfx( 4);
                set_subseq( 2);
                h_inerc = -5.0;
                v_inerc = 7.0;
                v_force = 0.5;
                break;
            }
            if ( (sq == 527 && get_elaps_frames() >= 20) ||
                    (sq == 528 && get_elaps_frames() >= 30))
            {
                set_subseq( 3);
                h_inerc = 6.0;
                v_force = 0.35;
                break;
            }
        }
        if ( get_subseq() == 2 || get_subseq() == 3)
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 4);
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            play_sfx( 11);
            scene_add_effect(this, 127, x, y, dir, -1);
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            if (sq == 527)
                h_inerc = 15.0;
            else if (sq == 528)
                h_inerc = 25.0;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;

            addbullet(this, NULL, 816, x, y, dir, 1, tmp, 3);
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && ( get_subseq() == 3 || get_subseq() == 4 ))
            set_seq( 9);
        break;
    case 530:
    case 531:
        if ( get_subseq() != 0 && get_subseq() != 4 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 4);
                break;
            }
        }
        else
            sub10func();

        field_18C = 9;
        if ( get_subseq() <= 3 )
        {
            if (field_7D0 % 2 == 0)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(2) + 2.0;
                tmp[2] = 2.0;
                addbullet(this,NULL, 817, x, y + 100.0, dir, 1, tmp, 3);
            }
            if ( get_subseq() == 3 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5) + 5.0;
                tmp[2] = 3.0;

                addbullet(this,NULL, 817, x, y + 100.0, dir, 1, tmp, 3);

                if ( field_190 )
                {
                    field_7D2++;
                    if ( field_7D2 >= 2 )
                    {
                        field_7D2 = 0;
                        field_190 = 0;
                    }
                }
            }
        }
        field_7D0++;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            play_sfx( 20);
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            h_inerc = 0.0;
            if (sq == 530)
            {
                v_inerc = 13.5;
                v_force = 0.5;
            }
            else if (sq == 531)
            {
                v_inerc = 17.5;
                v_force = 0.4;
            }
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            play_sfx( 12);
            field_194 = 4;
            if ( skills_1[9] >= 2 )
                field_194 = 5;
            if ( skills_1[9] >= 4 )
                field_194 = 6;
            field_190 = 0;
            h_inerc = 20.0;
            v_inerc = -20.0;
        }
        break;
    case 532:
    case 533:
        if ( get_subseq() != 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 2);
                break;
            }
        }
        else
            sub10func();

        field_18C = 9;
        if (field_7D0 % 2 == 0)
        {
            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(2) + 2.0;
            tmp[2] = 2.0;
            addbullet(this,NULL, 817, x, y + 100.0, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 1 || (get_subseq() == 0 && get_frame() >= 4) )
        {
            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 5.0;
            tmp[2] = 3.0;

            addbullet(this,NULL, 817, x, y + 100.0, dir, 1, tmp, 3);

            if ( field_190 )
            {
                field_7D2++;
                if ( field_7D2 >= 2 )
                {
                    field_7D2 = 0;
                    field_190 = 0;
                }
            }
        }
        field_7D0++;
        if ( process() )
            set_seq( 0);
        if ( get_frame_time() == 0 && get_frame() == 4 && get_subseq() == 0 )
        {
            play_sfx( 12);
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            if (sq == 532)
            {
                field_194 = 3;
                if ( skills_1[9] >= 2 )
                    field_194 = 4;
                if ( skills_1[9] >= 4 )
                    field_194 = 5;
            }
            else if (sq == 533)
            {
                field_194 = 4;
                if ( skills_1[9] >= 2 )
                    field_194 = 5;
                if ( skills_1[9] >= 4 )
                    field_194 = 6;
            }
            field_190 = 0;
            h_inerc = 20.0;
            v_inerc = -20.0;
        }
        if (sq == 532 && get_subseq() == 2 && get_frame_time() == 0)
        {
            if (get_frame() == 2)
                if (field_7D4 <= 8)
                    set_frame(4);
            if (get_frame() == 3)
                if (field_7D4 <= 16)
                    set_frame(4);
        }
        break;
    case 540:
    case 541:
        sub10func();
        field_18C = 2;
        if ((sq == 540 && keyDown(INP_B) == 0) ||
                (sq == 541 && keyDown(INP_C) == 0))
            not_charge_attack = 0;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
        {
            play_sfx( 18);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;

            CharFrameData *frm = get_pframe();
            addbullet(this, NULL, 820, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
        }
        if ( get_subseq() == 1)
        {
            if (get_frame_time() == 0 && get_frame() == 0 && (!not_charge_attack || get_elaps_frames() >= 60) )
            {
                next_subseq();
                break;
            }
            if (!not_charge_attack && get_elaps_frames() >= 7)
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 1 )
        {
            play_sfx( 13);
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            field_190 = 1;
        }
        break;
    case 542:
        if ( get_subseq() == 2 )
            sub10func();
        field_18C = 2;
        if ( get_subseq() < 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                set_subseq( 2);
                y = getlvl_height();
                break;
            }
        }
        if ( get_subseq() <= 1 && keyDown(INP_B) == 0 )
            not_charge_attack = 0;

        if ( process() )
            set_seq( 9);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
        {
            play_sfx( 7);
            h_inerc = -4.0;
            v_inerc = 8.0;
            v_force = 0.5;
            field_190 = 1;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;
            addbullet(this, NULL, 820, (30.0 * dir) + x, y + 62.0, dir, 1, tmp, 3);

            spell_energy_spend(200, 120);
            add_card_energy( 50);
        }
        break;
    case 545:
    case 546:
        sub10func();
        field_18C = 6;
        if ( get_subseq() <= 1 && (
                    (sq == 545 && keyDown(INP_B) == 0 ) ||
                    (sq == 546 && keyDown(INP_C) == 0 ) ))
            not_charge_attack = 0;

        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            set_seq( 0);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            play_sfx( 14);
            float tmp[3];
            if (sq == 545)
                tmp[0] = 0.0;
            else if (sq == 546)
                tmp[0] = -45.0;
            tmp[1] = 6.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 821, (30.0 * dir) + x, y + 120.0, dir, 1, tmp, 3);
            spell_energy_spend(200, 120);
            field_190 = 1;
            add_card_energy( 50);

            for (int32_t i =0; i < 12 ; i++)
            {
                tmp[0] = i * 30;
                tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                tmp[2] = 4.0;
                addbullet(this, NULL, 805, (30.0 * dir) + x, y + 120.0, dir, 1, tmp, 3);
            }
        }
        break;
    case 547:
    case 548:
        if ( get_subseq() == 2 )
            sub10func();
        field_18C = 6;
        if ( get_subseq() <= 1 )
        {
            if ( keyDown(INP_B) == 0)
                not_charge_attack = 0;
        }
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 2 )
        {
            set_subseq( 2);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            if (get_subseq() == 1 && get_subseq() == 2)
            {
                set_seq( 9);
                break;
            }

        if ( get_subseq() == 0 && get_frame_time() == 0)
        {
            if ( get_frame() == 3 )
            {
                play_sfx( 14);
                float tmp[3];
                if (sq == 547)
                    tmp[0] = 0.0;
                else if (sq == 548)
                    tmp[0] = 45.0;
                tmp[1] = 6.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 821, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

                spell_energy_spend(200, 120);
                field_190 = 1;
                add_card_energy( 50);

                for (int32_t i = 0 ; i< 12 ; i++)
                {
                    tmp[0] = i * 30.0;
                    tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                    tmp[2] = 4.0;

                    addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);
                }
            }
            if ( get_frame() == 12 )
                v_force = 0.5;
        }
        break;
    case 550:
        sub10func();
        field_18C = 10;
        if ( process() ||
                (get_elaps_frames() == 0 && get_frame_time() == 0  && get_frame() == 0 && get_subseq() == 1 ))
        {
            set_seq( 3);
            break;
        }
        if ( get_subseq() == 0 )
        {
            if ( get_frame() == 3 && get_frame_time() >= 15 && chrt->skills_1[10] >= 4 )
            {
                next_frame();
                break;
            }
            if ( field_7D0 == 1 )
            {
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet(this, NULL, 822, enemy->x, enemy->y, -dir, 1, tmp, 3);
                play_sfx( 19);
                break;
            }
            if ( get_frame_time() == 0 && get_frame() == 5 )
            {
                play_sfx( 16);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 15.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 822, (30.0 * dir) + x, y + 55.0, dir, 1, tmp, 3);

                tmp[0] = -45.0;
                addbullet(this, NULL, 822, (30.0 * dir) + x, y + 55.0, dir, 1, tmp, 3);

                tmp[0] = 45.0;
                addbullet(this, NULL, 822, (30.0 * dir) + x, y + 55.0, dir, 1, tmp, 3);

                spell_energy_spend(200, 120);
                add_card_energy( 50);
            }
        }
        if ( get_subseq() == 2 )
        {
            if ( get_frame_time() == 0 && get_frame() == 6 )
                h_inerc = 20.0;

            if ( get_frame() > 6 )
            {
                h_inerc -= 0.75;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
        }
        break;
    case 551:
        sub10func();
        field_18C = 10;
        if ( process() )
            set_seq( 9);
        if ( get_frame_time() == 0 && get_frame() == 5 )
        {
            float tmp[3];
            tmp[0] = 180.0;
            tmp[1] = 20.0;
            tmp[2] = scene_rand_rngf(6);

            addbullet(this, NULL, 822, (53 * dir) + x, y + 124.0, dir, 1, tmp, 3);
        }
        break;
    case 560:
        sub10func();
        field_18C = 3;
        if ( get_subseq() == 1 && get_elaps_frames() >= 40 )
        {
            next_subseq();
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 )
        {
            if ( get_frame() <= 2 )
            {
                CharFrameData *frm = get_pframe();

                if ( skills_1[3] >= 4 )
                    if ( (int32_t)get_frame_time() >= frm->duration - 2 )
                        next_frame();
                if ( skills_1[3] >= 2 )
                    if ( (int32_t)get_frame_time() >= frm->duration - 1 )
                        next_frame();
            }
            if ( get_frame_time() == 0 && get_frame() == 3 )
            {
                spell_energy_spend(200, 120);
                add_card_energy( 50);
                play_sfx( 17);
                field_190 = 1;

                float tmp[3];

                for (int32_t i =0; i< 8; i++)
                {

                    tmp[0] = i * 45.0 + 22.5;
                    tmp[1] = 18.0;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 825, cos_deg(-tmp[0]) * 75.0 * dir + x, sin_deg(-tmp[0]) * 75.0 + y + 100.0, dir, 1, tmp, 3);
                }
                tmp[2] = 3.0;

                addbullet(this, NULL, 825, x, y + 100.0, dir, 1, tmp, 3);
            }
        }
        break;
    case 561:
        sub10func();
        field_18C = 3;
        if ( get_subseq() == 1 && get_elaps_frames() >= 48 )
        {
            next_subseq();
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 )
        {
            if ( get_frame() <= 2 )
            {
                CharFrameData *frm = get_pframe();

                if ( skills_1[3] >= 4 )
                    if ( (int32_t)get_frame_time() >= frm->duration - 2 )
                        next_frame();
                if ( skills_1[3] >= 2 )
                    if ( (int32_t)get_frame_time() >= frm->duration - 1 )
                        next_frame();
            }
            if ( get_frame_time() == 0 && get_frame() == 3 )
            {
                spell_energy_spend(200, 120);
                add_card_energy( 50);
                play_sfx( 17);
                field_190 = 1;

                float tmp[3];

                for (int32_t i =0; i< 8; i++)
                {

                    tmp[0] = i * 45.0 + 22.5;
                    tmp[1] = 25.0;
                    tmp[2] = 0.0;

                    addbullet(this, NULL, 825, cos_deg(-tmp[0]) * 75.0 * dir + x, sin_deg(-tmp[0]) * 75.0 + y + 100.0, dir, 1, tmp, 3);
                }
                tmp[2] = 3.0;

                addbullet(this, NULL, 825, x, y + 100.0, dir, 1, tmp, 3);
            }
        }
        break;
    case 562:
        if ( get_subseq() == 3 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( get_subseq() != 1 && char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq( 3);
                break;
            }
        }
        field_18C = 3;
        if ( get_subseq() == 1 && get_elaps_frames() >= 40 )
        {
            next_subseq();
            v_force = 0.5;
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
            set_seq( 9);

        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            field_190 = 1;
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            play_sfx( 17);

            float tmp[3];

            for (int32_t i =0; i< 8; i++)
            {

                tmp[0] = i * 45.0 + 22.5;
                tmp[1] = 18.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 825, cos_deg(-tmp[0]) * 75.0 * dir + x, sin_deg(-tmp[0]) * 75.0 + y + 100.0, dir, 1, tmp, 3);
            }
            tmp[2] = 3.0;

            addbullet(this, NULL, 825, x, y + 100.0, dir, 1, tmp, 3);
        }
        break;
    case 563:
        if ( get_subseq() == 3 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( get_subseq() != 1 && char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq( 3);
                break;
            }
        }
        field_18C = 3;
        if ( get_subseq() == 1 && get_elaps_frames() >= 48 )
        {
            next_subseq();
            v_force = 0.5;
            break;
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
            set_seq( 9);

        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            field_190 = 1;
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            play_sfx( 17);

            float tmp[3];

            for (int32_t i =0; i< 8; i++)
            {

                tmp[0] = i * 45.0 + 22.5;
                tmp[1] = 25.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 825, cos_deg(-tmp[0]) * 75.0 * dir + x, sin_deg(-tmp[0]) * 75.0 + y + 100.0, dir, 1, tmp, 3);
            }
            tmp[2] = 3.0;

            addbullet(this, NULL, 825, x, y + 100.0, dir, 1, tmp, 3);
        }
        break;
    case 565:
        sub10func();
        field_18C = 7;
        if ( keyDown(INP_B) == 0 )
            not_charge_attack = 0;
        if ( get_subseq() == 1 )
        {
            if ( (get_elaps_frames() >= 15 && !not_charge_attack) || get_elaps_frames() >= 60 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() % 6 == 0 )
                if ( field_7D0 < skills_1[7] + 5 )
                {
                    float tmp[3];
                    tmp[0] = -60.0 - sin_deg(get_elaps_frames() * 17.0) * 15.0;
                    tmp[1] = 20.0;
                    tmp[2] = 6.0;

                    float xx = sin_deg(get_elaps_frames() * 47.0) * 20.0 + 20.0 * field_7D0;
                    float yy = sin_deg(get_elaps_frames() * 23.0) * 15.0;
                    addbullet(this, NULL, 826, xx * dir + x, yy + y - 120.0, dir, (1 - 2 * (yy >= 0 )), tmp, 3);
                    play_sfx( 0);
                    field_7D0++;
                }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(this, NULL, 826, x ,y, dir, -1 ,tmp, 3);
            field_190 = 1;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 4 )
            play_sfx( 6);
        break;
    case 566:
        sub10func();
        field_18C = 7;
        if ( keyDown(INP_C) == 0 )
            not_charge_attack = 0;
        if ( get_subseq() == 1 )
        {
            if ( (get_elaps_frames() >= 15 && !not_charge_attack) || get_elaps_frames() >= 60 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() % 4 == 0 )
                if ( field_7D0 < 2 * skills_1[7] + 7 )
                {
                    float tmp[3];
                    tmp[0] = -60.0 - sin_deg(get_elaps_frames() * 17.0) * 15.0;
                    tmp[1] = 20.0;
                    tmp[2] = 6.0;

                    float xx = sin_deg(get_elaps_frames() * 47.0) * 10.0 + 60.0 * field_7D0;
                    float yy = sin_deg(get_elaps_frames() * 23.0) * 15.0;
                    addbullet(this, NULL, 826, xx * dir + x, yy + y - 120.0, dir, (1 - 2 * (yy >= 0 )), tmp, 3);
                    play_sfx( 0);
                    field_7D0++;
                }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(this, NULL, 826, x ,y, dir, -1 ,tmp, 3);
            field_190 = 1;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 4 )
            play_sfx( 6);
        break;
    case 567:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 7;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq( 5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() < 2 )
        {
            if ( keyDown(INP_B) == 0 )
                not_charge_attack = 0;
        }

        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            field_7D4 = -atan2_deg(enemy->y - y, (enemy->x - x) * dir);

            if ( field_7D4 < -10 )
                field_7D4 = -10;
            if ( field_7D4 > 10 )
                field_7D4 = 10;

            play_sfx( 29);
            field_190 = 1;
            spell_energy_spend(200, 60);
            add_card_energy( 50);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            if ( skills_1[7] > 3 )
                tmp[2] = 6.0;
            addbullet(this, NULL, 826, (48 * dir) + x, y + 104.0, dir, 1, tmp, 3);
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(this, NULL, 826, x - (48 * dir), y + 104.0, dir, 1, tmp, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 1 && get_elaps_frames() > 10 )
            if ( !not_charge_attack || get_elaps_frames() > 25 )
                next_subseq();

        if ( get_subseq() == 3 && get_elaps_frames() > 40 )
            next_subseq();

        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5 )
            v_force = 0.6;
        break;
    case 568:
        if ( get_subseq() == 5 )
            sub10func();
        field_18C = 7;
        v_inerc -= v_force;
        if ( char_on_ground_down() && get_subseq() < 5 )
        {
            set_subseq( 5);
            air_dash_cnt = 0;
            y = getlvl_height();
            reset_forces();
            break;
        }
        if ( get_subseq() < 2 )
        {
            if ( keyDown(INP_C) == 0 )
                not_charge_attack = 0;
        }

        if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
        {
            field_7D4 = -atan2_deg(enemy->y - y, (enemy->x - x) * dir);

            if ( field_7D4 < -10 )
                field_7D4 = -10;
            if ( field_7D4 > 10 )
                field_7D4 = 10;

            play_sfx( 29);
            field_190 = 1;
            spell_energy_spend(200, 60);
            add_card_energy( 50);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            if ( skills_1[7] > 3 )
                tmp[2] = 6.0;
            addbullet(this, NULL, 826, (48 * dir) + x, y + 104.0, dir, 1, tmp, 3);
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0
                && get_frame_time() == 0
                && get_frame() == 0
                && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(this, NULL, 826, x - (48 * dir), y + 104.0, dir, 1, tmp, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 1 && get_elaps_frames() > 10 )
            if ( !not_charge_attack || get_elaps_frames() > 25 )
                next_subseq();

        if ( get_subseq() == 3 && get_elaps_frames() > 40 )
            next_subseq();

        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 5 )
            v_force = 0.6;
        break;
    case 570:
    case 572:
        field_18C = 11;
        if ( get_subseq() == 2 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( field_190 )
            {
                field_7D0++;
                if ( field_7D0 >= 10 )
                {
                    field_7D0 = 0;
                    field_190 = 0;
                    field_194 = 1;
                }
            }
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq( 2);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;

                if ( skills_1[11] <= 3 )
                    tmp[2] = 9.0;
                else
                    tmp[2] = 12.0;

                addbullet( this, NULL, 827, x, y , dir, 1, tmp, 3);
                field_190 = 0;
                field_194 = 1;
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            set_seq( 0);
            break;
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            h_inerc = 17.5;
            v_inerc = 10.0;
            v_force = 0.75;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;

            if ( skills_1[11] < 3 )
            {
                tmp[2] = 7.0;
                addbullet(this, NULL, 827, x, y, dir, 1, tmp, 3);
            }
            else
            {
                tmp[2] = 10.0;
                addbullet(this, NULL, 827, x, y, dir, 1, tmp, 3);
                set_subseq(3);
            }
        }

        if ( get_subseq() == 1 || get_subseq() == 3 )
            if ( get_elaps_frames() % 10 == 0 )
                play_sfx( 105);

        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 1 )
        {
            play_sfx( 106);
            field_190 = 0;
            field_194 = 1;
        }
        break;
    case 571:
    case 573:
        field_18C = 11;
        if ( get_subseq() == 2 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( field_190 )
            {
                field_7D0++;
                if ( field_7D0 >= 10 )
                {
                    field_7D0 = 0;
                    field_190 = 0;
                    field_194 = 1;
                }
            }
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq( 2);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;

                if ( skills_1[11] <= 3 )
                    tmp[2] = 9.0;
                else
                    tmp[2] = 12.0;

                addbullet( this, NULL, 827, x, y , dir, 1, tmp, 3);
                field_190 = 0;
                field_194 = 1;
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            set_seq( 0);
            break;
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            h_inerc = 12.5;
            v_inerc = 25.0;
            v_force = 1.00;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;

            if ( skills_1[11] < 3 )
            {
                tmp[2] = 7.0;
                addbullet(this, NULL, 827, x, y, dir, 1, tmp, 3);
            }
            else
            {
                tmp[2] = 10.0;
                addbullet(this, NULL, 827, x, y, dir, 1, tmp, 3);
                set_subseq(3);
            }
        }

        if ( get_subseq() == 1 || get_subseq() == 3 )
            if ( get_elaps_frames() % 10 == 0 )
                play_sfx( 105);
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 1 )
        {
            play_sfx( 106);
            field_190 = 0;
            field_194 = 1;
        }
        break;
    case 599:
        if ( field_7D0 > 0 && field_7D0 < 12 && get_frame() < 7 )
        {

            field_7D4 = scene_rand_rng(35);

            float tmp[3];
            tmp[0] = (-20 - field_7D4);
            tmp[1] = (scene_rand_rngf(5) + 10);
            tmp[2] = 0.0;

            float xx = (20 * dir * (field_7D0 + 1));
            addbullet(this, NULL, 807, xx + x, y, dir, 1, tmp, 3);

            tmp[0] = scene_rand_rngf(360);
            tmp[1] = 0.0;
            tmp[2] = 1.0;

            addbullet(this, NULL, 801, xx + x, y, dir, 1, tmp, 3);

            if ( field_7D0 == 1 )
            {
                play_sfx( 0);
                spell_energy_spend(200, 120);
            }
            field_7D0++;
        }
        if ( process() )
            set_seq( 0);
        if ( get_frame_time() == 0 && get_frame() == 5 )
            field_7D0 = 1;
        break;
    case 600:
        sub10func();
        if ( get_subseq() <= 3 )
            sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 850, x, y + 220.0, dir, 1, tmp, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            field_4A6 = 40;
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 220.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 3 )
        {
            if ( get_elaps_frames() > 90 )
            {
                next_subseq();
                break;
            }
            if ( get_elaps_frames() < 60 )
                if ( get_elaps_frames() % 3 == 0 )
                {
                    play_sfx( 5);
                    float tmp[3];
                    tmp[0] = scene_rand_rng(30) - 15.0;
                    tmp[1] = 40.0;
                    tmp[2] = 5.0;

                    addbullet(this, NULL, 850, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                    tmp[2] = 4.0;
                    addbullet(this, NULL, 850, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
                }
        }
        break;
    case 601:
        sub10func();
        sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 195.0, dir, 1);

            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            play_sfx( 100);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            addbullet(this, NULL, 851, (100 * dir) + x, getlvl_height(), dir, 1, tmp, 3);
            addbullet(this, NULL, 851, (100 * dir) + x, getlvl_height(), -dir, 1, tmp, 3);
        }
        break;
    case 602:
        sub10func();
        sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_frame_time() == 0 )
        {
            if ( get_frame() == 3 )
            {
                sub_4834E0( 40);
                scene_play_sfx(23);
                scene_add_effect(this, 115, (20 * dir) + x, y + 100.0, dir, 1);
                sub_469450( 0, 0, 60);
                sub_483570();
                weather_forecast_next();
            }
            if ( get_frame() == 5 )
            {
                play_sfx( 101);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 4.5;
                tmp[2] = 1.0;

                addbullet(this, NULL, 852, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

                for (int32_t i=0; i< 12; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 30.0;
                    tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                    tmp[2] = 4.0;

                    addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);
                }
            }
        }
        break;
    case 603:
        sub_46AB50( 0, 2);
        if ( get_subseq() != 0 && get_subseq() != 4 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 4);
                break;
            }
        }
        else
            sub10func();

        if ( field_7D0 % 2 == 0 && get_subseq() <= 3 && time_stop == 0 )
        {
            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rng(2) + 6.0;
            tmp[2] = 2.0;
            addbullet(this, NULL, 817, x, y + 100.0, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 3 )
        {
            if ( time_stop == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rng(5) + 10.0;
                tmp[2] = 3.0;
                addbullet(this, NULL, 817, x, y + 100.0, dir, 1, tmp, 3);
            }
            if ( field_190 == 1 )
            {
                reset_forces();
                set_subseq( 5);
                break;
            }
            if ( field_190 )
            {
                h_inerc = -4.0;
                v_inerc = 7.0;
                v_force = 0.4;
                set_subseq(6);
                break;
            }
        }
        if ( get_subseq() == 5 )
        {
            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rng(4) + 10.0;
            tmp[2] = 2.0;
            addbullet(this, NULL, 817, (30 * dir) + x, y + 65.0, dir, 1, tmp, 3);

            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rng(5) + 15.0;
            tmp[2] = 3.0;
            addbullet(this, NULL, 817, (30 * dir) + x, y + 65.0, dir, 1, tmp, 3);

            if ( field_190 )
            {
                field_7D4 = 0;
                field_7D2 ++;
                if ( field_7D2 >= 4 )
                {
                    field_7D2 = 0;
                    field_190 = 0;
                    field_194 = 1;
                }
            }
            field_7D4 ++;
            if ( field_7D4 >= 5 || get_elaps_frames() >= 60 )
            {
                h_inerc = -4.0;
                v_inerc = 7.0;
                v_force = 0.4;
                set_subseq(6);
                break;
            }
        }
        field_7D0 ++;
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            spell_energy_spend(200, 120);
            add_card_energy( 50);
            h_inerc = 0.0;
            v_inerc = 18.5;
            v_force = 0.5;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 3 )
        {
            reset_forces();
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, (10 * dir) + x, y + 116.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            play_sfx( 12);
            field_194 = 1;
            field_190 = 0;
            h_inerc = 25.0;
            v_inerc = -25.0;
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
            set_seq( 0);
        break;
    case 604:
        sub10func();
        sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 4 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 300.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 854, x, y + 300.0, dir, 1, tmp, 3);
        }

        if ( get_subseq() == 1 && get_elaps_frames() >= 90 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 10 )
        {
            field_7D0 = 1;
            play_sfx( 100);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 12.0;

            addbullet(this, NULL, 854, x - (7 * dir), y + 115.0, dir, 1, tmp, 3);

            tmp[2] = 13.0;
            addbullet(this, NULL, 854, x - (7 * dir), y + 115.0, dir, 1, tmp, 3);

            tmp[1] = 0.075;
            tmp[2] = 14.0;
            addbullet(this, NULL, 854, 320.0, 480.0, 1, 1, tmp, 3);

            //shake_camera(8.0); //HACK
        }
        break;
    case 605:
        sub10func();
        if ( get_subseq() < 4 )
            sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 115.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 3 )
        {
            if ( get_elaps_frames() <= 40 )
            {
                if ( get_elaps_frames() % 17 == 0 )
                {
                    play_sfx( 103);
                    for (int32_t i=0; i< 12; i++)
                    {
                        float tmp[3];
                        tmp[0] = i * 30.0 + 15.0;
                        tmp[1] = 25.0;
                        tmp[2] = 5.0;

                        float xx = cos_deg(-tmp[0]) * 80.0 * dir + x;
                        float yy = sin_deg(-tmp[0]) * 20.0 + y + 100;

                        addbullet(this, NULL, 855, xx, yy, dir, 1, tmp, 3);

                        tmp[2] = 4.0;
                        addbullet(this, NULL, 855, xx, yy, dir, 1, tmp, 3);
                    }
                }
            }
            if ( get_elaps_frames() >= 44 )
                next_subseq();
        }
        break;
    case 606:
        sub10func();
        if ( get_subseq() < 5 )
            sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 115.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            play_sfx( 104);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 856, x, y + 115.0, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 4 && get_elaps_frames() >= 150 )
            next_subseq();
        break;
    case 607:
        if ( get_subseq() == 4 )
            sub10func();
        if ( get_subseq() < 3 )
            sub_46AB50( 0, 2);
        if ( get_subseq() == 1 )
        {
            dash_angle *= 0.92;
            if ( dash_angle < 1.0 )
                dash_angle = 1.0;
            set_vec_speed(field_7DC, dash_angle);
        }

        if ( get_subseq() == 3 || get_subseq() == 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 858, x, y, dir, 1, tmp, 3);
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x - (30 * dir), y + 130.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if (get_subseq() == 1)
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
            {
                field_7DC = -60.0;
                dash_angle = 30.0;
                set_vec_speed(field_7DC, 30.0);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 7.0;

                addbullet(this, NULL, 857, x, y, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 10 == 0 )
                play_sfx( 105);
            if ( field_190 )
            {
                field_7D0++;
                if ( field_7D0 >= 10 )
                {
                    field_7D0 = 0;
                    field_190 = 0;
                }
            }
            if ( get_elaps_frames() < 48 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 6.0;

                CharFrameData *frm = get_pframe();

                float xx = (frm->extra1[4] * dir) + x + 40.0 - scene_rand_rngf(80);
                float yy = y - frm->extra1[5] + 40.0 - scene_rand_rngf(80);

                addbullet(this, NULL, 857, xx , yy, dir, 1, tmp, 3);

                xx = (frm->extra1[4] * dir) + x + 40.0 - scene_rand_rngf(80);
                yy = y - frm->extra1[5] + 40.0 - scene_rand_rngf(80);
                tmp[2] = 3.0;
                addbullet(this, NULL, 857, xx , yy, dir, 1, tmp, 3);

                xx = (frm->extra1[4] * dir) + x + 20.0 - scene_rand_rngf(40);
                yy = y - frm->extra1[5] + 20.0 - scene_rand_rngf(40);
                tmp[2] = 4.0;
                addbullet(this, NULL, 857, xx , yy, dir, 1, tmp, 3);
            }
            else
            {
                next_subseq();
                h_inerc = 0.0;
                v_inerc = 0.0;
                v_force = 0.0;
                float tmp[3];

                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 9.0;

                addbullet(this, NULL, 857, x, y, dir, 1, tmp, 3);
                break;
            }
        }

        if ( get_subseq() == 2 && get_frame_time() == 0 )
        {
            if ( get_frame() == 1 )
            {
                play_sfx( 106);
                //shake_camera(10.0); //HACK
                field_190 = 0;
                field_194 = 1;
            }
            if ( get_frame() == 11 )
                v_force = 0.5;
        }
        break;
    case 608:
        if ( get_subseq() == 2 )
            sub10func();
        sub_46AB50( 0, 2);
        if ( get_subseq() == 1 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                next_subseq();

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                addbullet(this, NULL,  858, x, y, dir, 1, tmp, 3);
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x - (30 * dir), y + 130.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 1 )
        {
            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
            {
                h_inerc = 4.0;
                v_inerc = 40.0;
                v_force = 5.0;
            }

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;

            CharFrameData *frm = get_pframe();

            float xx = (frm->extra1[4] * dir) + x + 40.0 - scene_rand_rngf(80);
            float yy = y - frm->extra1[5] + 40.0 - scene_rand_rngf(80);

            addbullet(this, NULL, 858, xx , yy, dir, 1, tmp, 3);

            xx = (frm->extra1[4] * dir) + x + 40.0 - scene_rand_rngf(80);
            yy = y - frm->extra1[5] + 40.0 - scene_rand_rngf(80);
            tmp[2] = 3.0;
            addbullet(this, NULL, 858, xx , yy, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 1 )
        {
            play_sfx( 107);
            //shake_camera(10.0); //HACK
        }
        break;

    case 610:
        sub10func();
        sub_46AB50( 0, 2);
        if ( field_890 )
            field_890 = 180;
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 125.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            play_sfx( 108);
            field_890 = 180;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            addbullet(this, NULL, 860, x, y + 110.0, dir, -1, tmp, 3);
        }
        break;
    case 613:
        sub_46AB50( 0, 2);
        sub10func();
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 215.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            play_sfx( 109);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 35.0;
            tmp[2] = 0.0;

            CharFrameData *frm = get_pframe();
            addbullet(this, NULL, 863, frm->extra1[4] * dir + x, y - frm->extra1[5], dir, 1, tmp, 3);

            tmp[0] = -30.0;
            addbullet(this, NULL, 863, frm->extra1[4] * dir + x, y - frm->extra1[5], dir, 1, tmp, 3);

            tmp[0] = 30.0;
            addbullet(this, NULL, 863, frm->extra1[4] * dir + x, y - frm->extra1[5], dir, 1, tmp, 3);
        }
        if ( get_subseq() == 3 && get_elaps_frames() >= 60 )
            next_subseq();
        break;
    case 650:
        if ( get_subseq() == 5 )
            sub10func();
        if ( get_subseq() <= 3 )
            sub_46AB50( 0, 2);
        if ( get_subseq() == 4)
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 5);
                break;
            }
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 &&  get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq( 9);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            addbullet(this, NULL, 850, x, y+220.0, dir, 1, tmp, 3);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            field_4A6 = 40;
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 220.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 3 )
        {
            if ( get_elaps_frames() > 90 )
            {
                v_force = 0.5;
                next_subseq();
            }
            else if ( get_elaps_frames() < 60 )
            {
                if ( get_elaps_frames() % 3 == 0)
                {
                    play_sfx( 5);
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(30) - 15.0;
                    tmp[1] = 40.0;
                    tmp[2] = 5.0;
                    addbullet(this, NULL, 850, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
                    tmp[2] = 4.0;
                    addbullet(this, NULL, 850, (65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
                }
            }
        }
        break;
    case 652:
        if ( get_subseq() == 1 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 1);
                break;
            }
        }
        sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            set_seq( 9);
        if ( get_subseq() == 0 && get_frame_time() == 0 )
        {
            if ( get_frame() == 3 )
            {
                sub_4834E0( 40);
                scene_play_sfx(23);
                scene_add_effect(this, 115, (20 * dir) + x, y + 100.0, dir, 1);
                sub_469450( 0, 0, 60);
                sub_483570();
                weather_forecast_next();
            }
            if ( get_frame() == 5 )
            {
                play_sfx( 101);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 4.5;
                tmp[2] = 1.0;

                addbullet(this, NULL, 852, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);

                for (int32_t i=0; i< 12; i++)
                {
                    tmp[0] = i * 30.0;
                    tmp[1] = sin_deg(-tmp[0]) * 20.0 + 7.0;
                    tmp[2] = 4.0;

                    addbullet(this, NULL, 805, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);
                }
            }
            if ( get_frame() == 14 )
                v_force = 0.5;
        }
        break;
    case 654:
        if ( get_subseq() == 4 )
            sub10func();
        if ( get_subseq() == 3 || get_subseq() == 2 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                set_subseq( 4);
                reset_forces();
                break;
            }
        }
        if ( get_subseq() <= 2 )
            sub_46AB50( 0, 2);
        if ( process() )
            set_seq( 3);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 4 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 300.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            addbullet( this, NULL, 854, x, y+ 300.0, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= 90 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 2  && get_frame_time() == 0 && get_frame() == 10 )
        {
            field_7D0 = 1;
            play_sfx( 100);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 12.0;

            addbullet( this, NULL, 854, x - (7 * dir), y+ 115.0, dir, 1, tmp, 3);
            tmp[2] = 13.0;
            addbullet( this, NULL, 854, x - (7 * dir), y+ 115.0, dir, 1, tmp, 3);

            tmp[1] = 0.075;
            tmp[2] = 14.0;
            addbullet( this, NULL, 854, 320.0, 480.0, 1, 1, tmp, 3);

            //shake_camera(8.0); //HACK
        }
        if ( get_subseq() == 2  && get_frame_time() == 0 && get_frame() == 24 )
            v_force = 0.5;
        break;
    case 655:
        if ( get_subseq() == 5 )
            sub10func();
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 4);
                break;
            }
            if ( get_subseq() < 4 )
                sub_46AB50( 0, 2);
        }
        if ( process() )
            set_seq( 0);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            set_seq( 9);
            v_force = 0.5;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 115.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 3 )
        {
            if ( get_elaps_frames() <= 40 )
                if ( get_elaps_frames() % 17 == 0 )
                {
                    play_sfx( 103);
                    for (int32_t i = 0; i < 12; i++)
                    {
                        float tmp[3];
                        tmp[0] = i *30 +  15.0;
                        tmp[1] = 25.0;
                        tmp[2] = 5.0;

                        float xx = cos_deg(-tmp[0]) * 80.0 * dir + x;
                        float yy = sin_deg(-tmp[0]) * 20.0 + y + 100;

                        addbullet(this, NULL, 855, xx, yy, dir, 1, tmp, 3);

                        tmp[2] = 4.0;
                        addbullet(this, NULL, 855, xx, yy, dir, 1, tmp, 3);
                    }
                }
            if ( get_elaps_frames() >= 44 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 4 && get_frame_time() == 0 && get_frame() == 6 )
            v_force = 0.5;
        break;
    case 660:
        sub_46AB50( 0, 2);
        if ( field_890 )
            field_890 = 180;
        if ( process() )
        {
            set_seq( 9);
            v_force = 0.5;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 125.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            play_sfx( 108);
            field_890 = 180;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;
            addbullet(this, NULL, 860, x, y + 110.0, dir, -1, tmp, 3);
        }
        break;
    case 663:
        sub_46AB50( 0, 2);
        if ( process() )
        {
            set_seq( 9);
            v_force = 0.5;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            sub_4834E0( 40);
            scene_play_sfx(23);
            scene_add_effect(this, 115, x, y + 215.0, dir, 1);
            sub_469450( 0, 0, 60);
            sub_483570();
            weather_forecast_next();
        }
        if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
        {
            play_sfx( 109);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 35.0;
            tmp[2] = 0.0;

            CharFrameData *frm = get_pframe();
            addbullet(this, NULL, 863, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);

            tmp[0] = -30.0;
            addbullet(this, NULL, 863, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);

            tmp[0] = 30.0;
            addbullet(this, NULL, 863, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
        }
        if ( get_subseq() == 3 && get_elaps_frames() >= 60 )
            next_subseq();
        break;
    case 695:
        sub10func();
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            scene_play_sfx(55);
            scene_add_effect(this, 140, x, y + 100.0, dir, 1);
            scene_add_effect(this, 140, x, y + 100.0, dir, 1);
            scene_add_effect(this, 140, x, y + 100.0, dir, 1);
            scene_add_effect(this, 141, x, y + 100.0, dir, -1);
            scene_add_effect(this, 142, x, y, dir, -1);
        }
        break;
    case 696:
        sub10func();
        if ( get_frame() > 5 )
        {
            h_inerc -= 3.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( process() )
            set_seq( 0);
        if ( get_frame_time() == 0 )
        {
            if ( get_frame() == 4 )
                h_inerc = 15.0;
            if ( get_frame() == 5 )
            {
                scene_play_sfx(29);
                field_49A = 0;
            }
            if ( get_frame() == 6 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;
                CharFrameData *frm = get_pframe();
                addbullet(this, NULL, 990, (frm->extra1[4] * dir) + x, y - frm->extra1[5], dir, 1, tmp, 3);
            }
        }
        break;
    case 707:
        sub10func();
        if ( h_inerc > 12.0 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 12.0 )
                h_inerc = 12.0;
        }
        if ( process() )
        {
            set_seq( 700);
            break;
        }
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            h_inerc = 15.0;
            scene_add_effect(this, 125, (80 * dir) + x, y + 80.0, dir, 1);
            scene_add_effect(this, 126, x, y + 80.0, dir, 1);
            scene_play_sfx(31);
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), scene_rand_rngf(200) + y, dir, 1);
            if ( get_elaps_frames() > 30 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        break;
    case 708:
        if ( get_subseq() == 0 || get_subseq() == 2 )
            sub10func();

        if ( get_subseq() == 2 )
        {
            h_inerc += 2.0;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( !char_on_ground_flag() )
        {
            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 124, x + 50.0 - scene_rand_rngf(100), scene_rand_rngf(200) + y, dir, 1);
            v_inerc -= 0.5;
        }

        if (!char_on_ground_flag() && getlvl_height() >= v_inerc + y && v_inerc < 0.0 )
        {
            v_inerc = 0.0;
            y = getlvl_height();
            set_subseq( 2);
            break;
        }
        if ( process() )
        {
            set_seq( 700);
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = -14.0;
            v_inerc = 4.0;
            scene_add_effect(this, 125, x, y + 80.0, -dir, 1);
            scene_add_effect(this , 126, x, y + 80.0, -dir, 1);
            scene_play_sfx(31);
        }
        break;
    case 710:
        sub10func();
        if ( get_subseq() <= 1 )
        {
            h_inerc *= 0.98;
            v_inerc *= 0.98;
        }
        if ( get_subseq() == 1 )
        {
            if ( field_7D0 == 0)
            {
                int32_t delim;
                if ( (int32_t) get_elaps_frames() <= field_7D2 )
                {
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        delim = 2;
                        break;
                    case GAME_DIFF_HARD:
                        delim = 3;
                        break;
                    case GAME_DIFF_NORMAL:
                        delim = 4;
                        break;
                    case GAME_DIFF_EASY:
                        delim = 5;
                        break;
                    default:
                        delim = 1;
                        break;
                    }
                    if ( get_elaps_frames() % delim == 0 )
                    {
                        play_sfx( 5);
                        float tmp[3];
                        tmp[0] = -60.0 - scene_rand_rngf(60);
                        tmp[1] = scene_rand_rngf(25) * 0.1 + 17.5;
                        tmp[2] = 5.0;

                        addbullet(this, NULL, 900, x + 50.0 - scene_rand_rngf(100), y + 170.0 + scene_rand_rngf(100), dir, 1, tmp, 3);

                        tmp[2] = 4.0;
                        addbullet(this, NULL, 900, x, y + 220.0, dir, 1, tmp, 3);
                    }
                }
                if ( get_elaps_frames() >= 60 )
                {
                    set_subseq( 5);
                    break;
                }
            }
            if ( field_7D0 == 1 )
            {
                if ( get_elaps_frames() <= 60 )
                    if ( get_elaps_frames() % 4 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(400) + 200.0;
                        tmp[2] = (scene_rand_rng(100) >= 50) + 10.0;

                        addbullet(this, NULL, 900, cos_deg(-tmp[0]) * tmp[1] * dir + x, sin_deg(-tmp[0]) * tmp[1] + y + 220.0, dir, 1, tmp, 3);
                    }
                if ( get_elaps_frames() >= 120 )
                {
                    sub_486FD0( 45.0, -45.0);
                    flip_with_force();
                    next_subseq();
                    break;
                }

            }
        }

        if ( get_subseq() == 3 )
        {
            int32_t frm_cnt, delim;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                frm_cnt = 60;
                delim = 2;
                break;
            case GAME_DIFF_HARD:
                frm_cnt = 40;
                delim = 3;
                break;
            case GAME_DIFF_NORMAL:
                frm_cnt = 25;
                delim = 3;
                break;
            case GAME_DIFF_EASY:
                frm_cnt = 15;
                delim = 3;
                break;
            default:
                frm_cnt = 1;
                delim = 1;
                break;
            }
            if ( (int32_t) get_elaps_frames() <= frm_cnt )
                if ( get_elaps_frames() % delim == 0 )
                {
                    play_sfx( 5);
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(40) + field_7F0 - 20.0;
                    tmp[1] = scene_rand_rngf(30) + 5.0;
                    tmp[2] = 6.0;

                    addbullet(this, NULL, 900,(65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                    tmp[2] = 4.0;
                    addbullet(this, NULL, 900,(65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
                }
            if ( get_elaps_frames() >= 90 )
            {
                next_subseq();
                break;
            }
        }
        if ( process() )
            set_seq( 700);
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 900, x, y + 220.0, dir, 1, tmp, 3);
                field_7D0 = 0;
                if ( scene_rand_rngf(100) >= 50 )
                    field_7D0 = 1;
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_LUNA:
                    field_7D2 = 60;
                    break;
                case GAME_DIFF_HARD:
                    field_7D2 = 50;
                    break;
                case GAME_DIFF_NORMAL:
                    field_7D2 = 40;
                    break;
                case GAME_DIFF_EASY:
                    field_7D2 = 30;
                    break;
                default:
                    break;
                }
            }
            if ( get_subseq() == 5 )
            {
                if ( enemy->health <= 0 )
                    set_seq(9);
                else
                    set_seq(715);
            }
        }
        break;
    case 711:
        if ( get_subseq() <= 1 )
        {
            h_inerc *= 0.98;
            v_inerc *= 0.98;
        }
        if ( get_subseq() == 1 )
        {
            if ( field_7D0 == 0 )
            {
                int32_t delim;
                if ( (int32_t) get_elaps_frames() <= field_7D2 )
                {
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        delim = 2;
                        break;
                    case GAME_DIFF_HARD:
                        delim = 3;
                        break;
                    case GAME_DIFF_NORMAL:
                        delim = 4;
                        break;
                    case GAME_DIFF_EASY:
                        delim = 5;
                        break;
                    default:
                        delim = 1;
                        break;
                    }
                    if ( get_elaps_frames() % delim == 0 )
                        if ( get_elaps_frames() >= 30 )
                        {
                            play_sfx( 5);
                            float tmp[3];
                            tmp[0] = -60.0 - scene_rand_rngf(60);
                            tmp[1] = scene_rand_rngf(20) * 0.1 + 10.5;
                            tmp[2] = 5.0;

                            addbullet(this, NULL, 900, x + 50.0 - scene_rand_rngf(100), y + 170.0 + scene_rand_rngf(100), dir, 1, tmp, 3);

                            tmp[2] = 4.0;
                            addbullet(this, NULL, 900, x, y + 220.0, dir, 1, tmp, 3);
                        }
                }
                if ( get_elaps_frames() >= 90 )
                {
                    set_subseq( 5);
                    break;
                }
            }
            if ( field_7D0 == 1 )
            {
                if ( get_elaps_frames() <= 60 )
                    if ( get_elaps_frames() % 4 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(400) + 200.0;
                        tmp[2] = (scene_rand_rng(100) >= 50) + 10.0;

                        addbullet(this, NULL, 900, cos_deg(-tmp[0]) * tmp[1] * dir + x, sin_deg(-tmp[0]) * tmp[1] + y + 220.0, dir, 1, tmp, 3);
                    }
                if ( get_elaps_frames() >= 120 )
                {
                    sub_486FD0( 45.0, -45.0);
                    flip_with_force();
                    next_subseq();
                    break;
                }
            }
        }
        if ( get_subseq() == 3 )
        {
            int32_t frm_cnt, delim, rrng;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                frm_cnt = 60;
                delim = 2;
                rrng = 10;
                break;
            case GAME_DIFF_HARD:
                frm_cnt = 40;
                delim = 3;
                rrng = 7;
                break;
            case GAME_DIFF_NORMAL:
                frm_cnt = 25;
                delim = 3;
                rrng = 7;
                break;
            case GAME_DIFF_EASY:
                frm_cnt = 15;
                delim = 3;
                rrng = 0;
                break;
            default:
                frm_cnt = 1;
                delim = 1;
                rrng = 0;
                break;
            }
            if ( (int32_t) get_elaps_frames() <= frm_cnt )
                if ( get_elaps_frames() % delim == 0 )
                {
                    play_sfx( 5);
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(40) + field_7F0 - 20.0;
                    tmp[1] = scene_rand_rngf(rrng + 20) + 5.0;
                    tmp[2] = 6.0;

                    addbullet(this, NULL, 900,(65 * dir) + x, y + 117.0, dir, 1, tmp, 3);

                    tmp[2] = 4.0;
                    addbullet(this, NULL, 900,(65 * dir) + x, y + 117.0, dir, 1, tmp, 3);
                }
            if ( get_elaps_frames() >= 90 )
            {
                next_subseq();
                break;
            }
        }
        if ( process() )
        {
            if ( enemy->health > 0 )
                set_seq( 715);
            else
                set_seq( 9);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 900, x, y + 220.0, dir, 1, tmp, 3);

                field_7D0 = 0;
                if ( scene_rand_rng(100) >= 50 )
                    field_7D0 = 1;
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_LUNA:
                    field_7D2 = 60;
                    break;
                case GAME_DIFF_HARD:
                    field_7D2 = 50;
                    break;
                case GAME_DIFF_NORMAL:
                    field_7D2 = 40;
                    break;
                case GAME_DIFF_EASY:
                    field_7D2 = 30;
                    break;
                default:
                    break;
                }
            }
            if ( get_subseq() == 5 )
            {
                if ( enemy->health <= 0 )
                    set_seq(9);
                else
                    set_seq(715);
            }
        }
        break;
    case 712:
        if ( get_subseq() <= 1 )
        {
            h_inerc *= 0.98;
            v_inerc *= 0.98;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() % 2 == 0 )
            {
                if ( (int32_t) get_elaps_frames() <= field_7D2 - 60 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(400) + 200.0;
                    tmp[2] = (scene_rand_rng(100) >= 50) + 12.0;

                    addbullet(this, NULL, 900, cos_deg(-tmp[0]) * tmp[1] * dir + x, sin_deg(-tmp[0]) * tmp[1] + y + 100.0, dir, 1, tmp, 3);
                }
            }
            if ( (int32_t)get_elaps_frames() >= field_7D2 )
            {
                next_subseq();
                break;
            }
        }

        if ( get_subseq() == 3 )
        {
            int32_t rrng, delim;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                rrng = 60;
                delim = 2;
                break;
            case GAME_DIFF_HARD:
                rrng = 50;
                delim = 3;
                break;
            case GAME_DIFF_NORMAL:
                rrng = 30;
                delim = 3;
                break;
            case GAME_DIFF_EASY:
                rrng = 20;
                delim = 3;
                break;
            default:
                rrng = 1;
                delim = 1;
                break;
            }
            if ( get_elaps_frames() % delim == 0 )
                if ( (int32_t)get_elaps_frames() < field_7D2 )
                {
                    play_sfx( 5);
                    float tmp[3];
                    tmp[0] = scene_rand_rng(rrng) - 120.0;
                    tmp[1] = scene_rand_rng(75) * 0.1 + 12.5;
                    tmp[2] = 7.0;

                    addbullet(this, NULL, 900, x + 50.0 - scene_rand_rngf(100), y + 170.0 + scene_rand_rngf(100), dir, 1, tmp, 3);
                    addbullet(this, NULL, 900, x + 50.0 - scene_rand_rngf(100), y + 170.0 + scene_rand_rngf(100), -dir, 1, tmp, 3);

                    tmp[2] = 4.0;
                    addbullet(this, NULL, 900, x, y + 220.0, dir, 1, tmp, 3);
                }
            if ( get_elaps_frames() >= 150 )
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 4 && get_elaps_frames() >= 120 )
        {
            next_subseq();
            break;
        }
        if ( process() )
        {
            v_force = 0.5;
            set_seq(9);
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 1 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 14.0;
                addbullet(this, NULL, 900, x, y + 100.0, dir, 1, tmp, 3);
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_LUNA:
                    field_7D2 = 120;
                    break;
                case GAME_DIFF_HARD:
                    field_7D2 = 180;
                    break;
                case GAME_DIFF_NORMAL:
                    field_7D2 = 210;
                    break;
                case GAME_DIFF_EASY:
                    field_7D2 = 240;
                    break;
                default:
                    break;
                }
            }
            if ( get_subseq() == 3 )
            {
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_EASY:
                case GAME_DIFF_NORMAL:
                case GAME_DIFF_HARD:
                case GAME_DIFF_LUNA:
                    field_7D2 = 120;
                    break;
                default:
                    break;
                }
            }
        }
        break;
    case 715:
        if ( process() )
        {
            if ( field_7D0 == 1 )
            {
                if ( field_81C > 0 )
                    set_seq( 9);
                else
                {
                    field_81E = scene_rand_rng(3) + 1;
                    field_81C = 0;
                    set_seq( 712);
                }
            }
            else
            {
                if ( enemy->health > 0 )
                {
                    if ( field_81C < 600 )
                        set_seq( 711);
                    else
                    {
                        field_81E = scene_rand_rng(3) + 1;
                        field_81C = 0;
                        set_seq( 712);
                    }
                }
                else
                    set_seq( 9);
            }
            break;
        }
        if ( get_subseq() == 1)
        {
            h_inerc = (dash_angle - x) * dir * 0.05;
            v_inerc = 0.05 * (field_7DC - y);
            if (get_elaps_frames() >= 60)
            {
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            h_inerc *= 0.92;
            v_inerc *= 0.92;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            if ( getlvl_height() >= y )
            {
                field_7D0 = 0;
                field_7DC = scene_rand_rngf(100) + 150.0;
            }
            else if ( scene_rand_rng(100) > 50 )
            {
                field_7D0 = 0;
                field_7DC = scene_rand_rngf(250) + 50.0;
            }
            else
            {
                field_7D0 = 1;
                field_7DC = 0.0;
            }
            dash_angle = scene_rand_rngf(1080) + 100.0;
            if ( dash_angle >= x )
                dir = 1;
            else
                dir = -1;
        }
        break;
    case 720:
        sub10func();
        if ( get_subseq() <= 1 )
        {
            h_inerc *= 0.98;
            v_inerc *= 0.98;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() % field_7D0 == 0 )
                if ( field_7D2 > 0 )
                {
                    field_7D2--;
                    sub_486FD0( 360.0, -360.0);

                    for (int32_t i=0; i< dash_angle; i++)
                    {
                        if (field_7D4 > 0)
                            for (int32_t j=0; j<field_7D4; j++)
                            {
                                float tmp[3];
                                tmp[0] = j * (360 / field_7D4) + (i - (dash_angle - 1.0) * 0.5) * field_7DC + field_7F0;
                                tmp[1] = 10.0;
                                tmp[2] = 5.0;

                                float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                                float yy = sin_deg(-tmp[0]) * 50.0 + x + 100.0;

                                addbullet(this, NULL, 910, xx, yy, dir, 1, tmp, 3);

                                tmp[2] = 4.0;
                                addbullet(this, NULL, 910, xx, yy, dir, 1, tmp, 3);
                            }
                    }
                    if ( field_7D2 <= 0 )
                    {
                        next_subseq();
                        break;
                    }
                }
        }
        if ( get_subseq() == 2 && get_elaps_frames() >= 120 )
        {
            next_subseq();
            break;
        }
        if ( process() )
        {
            set_seq( 725);
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 910, x, y + 100.0, dir, 1, tmp, 3);

            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_7D0 = 60;
                field_7D2 = 3;
                field_7D4 = 4;
                dash_angle = 3.0;
                field_7DC = 15.0;
                break;
            case GAME_DIFF_HARD:
                field_7D0 = 75;
                field_7D2 = 3;
                field_7D4 = 3;
                dash_angle = 3.0;
                field_7DC = 15.0;
                break;
            case GAME_DIFF_NORMAL:
                field_7D0 = 75;
                field_7D2 = 2;
                field_7D4 = 3;
                dash_angle = 1.0;
                field_7DC = 0.0;
                break;
            case GAME_DIFF_EASY:
                field_7D0 = 90;
                field_7D2 = 2;
                field_7D4 = 3;
                dash_angle = 1.0;
                field_7DC = 0.0;
                break;
            default:
                break;
            }
        }
        break;
    case 721:
        if ( x <= 640.0 )
        {
            if ( dir == 1 )
                h_inerc += 0.03;
            else
                h_inerc -= 0.03;
        }
        else
        {
            if ( dir != 1 )
                h_inerc += 0.03;
            else
                h_inerc -= 0.03;
        }
        if ( h_inerc > 6.0 )
            h_inerc = 6.0;
        if ( h_inerc < -6.0 )
            h_inerc = -6.0;

        if ( y >= 150.0 )
            v_inerc -= 0.0125;
        else
            v_inerc += 0.0125;
        if ( v_inerc > 2.5 )
            v_inerc = 2.5;
        if ( v_inerc < -2.5 )
            v_inerc = -2.5;
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() % field_7D0 == 0 )
                if ( field_7D2 > 0 )
                {
                    field_7D2--;
                    sub_486FD0( 360.0, -360.0);

                    for (int32_t i=0; i< dash_angle; i++)
                    {
                        if (field_7D4 > 0)
                            for (int32_t j=0; j<field_7D4; j++)
                            {
                                float tmp[3];
                                tmp[0] = j * (360 / field_7D4) + (i - (dash_angle - 1.0) * 0.5) * field_7DC + field_7F0;
                                tmp[1] = 10.0;
                                tmp[2] = 6.0;

                                float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                                float yy = sin_deg(-tmp[0]) * 50.0 + x + 100.0;

                                addbullet(this, NULL, 910, xx, yy, dir, 1, tmp, 3);

                                tmp[2] = 4.0;
                                addbullet(this, NULL, 910, xx, yy, dir, 1, tmp, 3);
                            }
                    }
                    if ( field_7D2 <= 0 )
                    {
                        next_subseq();
                        return;
                    }
                }
        }
        if ( get_subseq() == 2 && get_elaps_frames() >= 120 )
        {
            next_subseq();
            break;
        }

        if ( process() )
        {
            set_seq( 725);
            field_81C = 120;
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 910, x, y + 100.0, dir, 1, tmp, 3);

            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_7D0 = 60;
                field_7D2 = 3;
                field_7D4 = 15;
                dash_angle = 1.0;
                field_7DC = 24.0;
                break;
            case GAME_DIFF_HARD:
                field_7D0 = 70;
                field_7D2 = 3;
                field_7D4 = 12;
                dash_angle = 1.0;
                field_7DC = 30.0;
                break;
            case GAME_DIFF_NORMAL:
                field_7D0 = 75;
                field_7D2 = 2;
                field_7D4 = 10;
                dash_angle = 1.0;
                field_7DC = 36.0;
                break;
            case GAME_DIFF_EASY:
                field_7D0 = 90;
                field_7D2 = 2;
                field_7D4 = 6;
                dash_angle = 1.0;
                field_7DC = 60.0;
                break;
            default:
                break;
            }
        }
        break;
    case 725:
        flip_with_force();
        if ( x <= 640.0 )
        {
            if ( dir == 1 )
                h_inerc += 0.03;
            else
                h_inerc -= 0.03;
        }
        else
        {
            if ( dir != 1 )
                h_inerc += 0.03;
            else
                h_inerc -= 0.03;
        }
        if ( h_inerc > 6.0 )
            h_inerc = 6.0;
        if ( h_inerc < -6.0 )
            h_inerc = -6.0;

        if ( y >= 150.0 )
            v_inerc -= 0.0125;
        else
            v_inerc += 0.0125;

        if ( v_inerc > 2.5 )
            v_inerc = 2.5;
        if ( v_inerc < -2.5 )
            v_inerc = -2.5;
        if ( process() )
            set_seq( 725);
        break;
    case 770:
        if ( process() )
            set_seq( 0);
        if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
        {
            field_6F5 = 1;
            sub_4685C0( -1);
            sub_46AB50( 0, -1);
            field_188 = 0;
            health_to_max();
            field_868 = 1;
            field_820 = 0;
            field_81E = 1;
            field_81A = 0;
            field_81C = 0;
            field_818 = 0;
            scene_play_sfx(23);
            field_882 = 1;
            field_86A = 1;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 0.0;

            addbullet(this, NULL, 1201, 180.0, 130.0, 1, 2, tmp, 3);

            tmp[2] = 1.0;
            addbullet(this, NULL, 1202, x, y + 100.0, dir, -1, tmp, 3);
        }
        break;
    case 780:
        field_7DC += 5.0;
        h_inerc = cos_deg(field_7DC) * 3.0;
        if ( h_inerc <= 0.0 )
        {
            dir = -1;
            h_inerc = -h_inerc;
        }
        else
            dir = 1;
        if ( process() )
            set_seq( 780);
        break;
    case 788:
        if ( get_subseq() == 15 )
        {
            v_inerc -= v_force;
            if (char_on_ground_down() )
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 16);
                //shake_camera(2.0); //HACK
                scene_play_sfx(22);
                break;
            }
        }

        if ( (get_subseq() == 17 || get_subseq() == 18))
        {
            v_inerc -= v_force;
            if (char_on_ground_down() )
            {
                y = getlvl_height();
                reset_forces();
                set_subseq( 19);
                break;
            }
        }

        if ( get_subseq() == 20 && get_elaps_frames() >= 60 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() >= 22 && get_subseq() <= 25 )
        {
            v_inerc = v_inerc - v_force;
            if (char_on_ground_down())
            {
                reset_forces();
                y = getlvl_height();
                set_seq( 10);
                break;
            }
        }

        if ( process() )
        {
            set_seq( 700);
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
        {
            if ( get_subseq() == 17 )
            {
                h_inerc = 0.0;
                v_inerc = 12.0;
                v_force = 2.0;
            }
            if ( get_subseq() == 22 )
            {
                set_subseq(6);
            }
            if ( get_subseq() == 23 )
            {
                v_inerc = 20.0;
                v_force = 0.75;
                scene_add_effect(this, 63, x, y, dir, 1);
            }
        }
        break;
    case 791:
        v_inerc -= v_force;
        if ( v_inerc < 0 )
            v_inerc = 0;
        if ( process() )
        {
            set_seq( 700);
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            scene_add_effect(this, 63, x, y , dir, 1);
            field_571 = 0;
            h_inerc = 10.0;
            v_inerc = 25.0;
            v_force = 0.2;
        }
        break;
    case 795:
        if ( get_subseq() == 0 )
        {
            v_inerc = v_inerc - 0.3;
            if (char_on_ground_down())
            {
                set_subseq( 1);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }
        if ( process() )
            set_seq( 700);
        break;
    case 797:
        if ( get_subseq() == 0 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                next_subseq();
                y = getlvl_height();
                v_inerc = 0.0;
                break;
            }
        }
        if ( get_subseq() == 1 )
        {
            h_inerc -= 1.0;
            if ( h_inerc < 0 )
                h_inerc = 0;
            if ( x > 480.0 )
                x = 480.0;
        }
        if ( process() )
            set_seq( 0);
        break;
    case 798:
        if ( get_subseq() == 0 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                next_subseq();
                y = getlvl_height();
                v_inerc = 0.0;
                break;
            }
        }
        if ( get_subseq() == 1 )
        {
            h_inerc -= 0.75;
            if ( h_inerc <= 0 )
            {
                h_inerc = 0;
                field_7D0++;
                if ( field_7D0 >= 2 )
                {
                    next_subseq();
                    h_inerc = -5.0;
                    v_inerc = 5.0;
                }
            }
        }
        if (get_subseq() == 2 || get_subseq() == 3)
        {
            v_inerc -= 0.25;
            if (char_on_ground_down())
            {
                reset_forces();
                y = getlvl_height();
                set_subseq( 4);
                scene_play_sfx(30);
                x = 800.0;
                break;
            }
        }
        if ( process() )
            set_seq( 700);
        break;
    default:
        char_c::func10();
        break;
    }
}


void char_cirno::func20()
{
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
             if ( pres_comb >= 700 && pres_comb < 800 ) //HACK?
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
                if (((keyDown(INP_BC) && keyDown(INP_BC) < 3) || keyHit(INP_BC)) && sub_468660(0) && field_836 == 0)
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
                            else if (cprior <= 100 && crd_id >= 200 && crd_id <= 299 && keyDown(INP_X_AXIS) == 0)
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
                                    sub_487370(615, cprior);
                                    return;
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
                                    sub_4873B0(502, cprior);
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
                                case 105:
                                    if ( skills_1[5] >= 1 )
                                    {
                                        if ( !field_801 )
                                        {
                                            field_4C8++;
                                            field_801 = 1;
                                        }
                                        sub_4834F0();
                                        sub_488E70();
                                        sub_4873B0( 527, cprior);
                                        return;
                                    }
                                    break;
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
                                case 109:
                                    if ( field_801 == 0 )
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_488E70();
                                    sub_4873B0(532, cprior);
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
                            else if (cprior <= 100 && crd_id >= 200 && crd_id <= 299 && keyDown(INP_X_AXIS) == 0)
                            {
                                switch(crd_id)
                                {
                                case 200:
                                    sub_487370( 650, cprior);
                                    return;
                                case 202:
                                    sub_487370( 652, cprior);
                                    return;
                                case 203:
                                    sub_487370(603, cprior);
                                    return;
                                case 204:
                                    sub_487370( 654, cprior);
                                    return;
                                case 205:
                                    sub_487370( 655, cprior);
                                    return;
                                case 210:
                                    sub_487370( 660, cprior);
                                    return;
                                case 213:
                                    sub_487370( 663, cprior);
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
                        if ( pres_comb & PCOMB_623B )
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
                        if ( pres_comb & PCOMB_214B )
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
                            if ( cprior <= get_prior(501) || (sq >= 500 && sq <= 599 && field_800 == 0))
                            {
                                if ( field_800 == 0)
                                {
                                    field_4C8++;
                                    field_800 = 1;
                                }
                                sub_4834F0();
                                sub_4873B0( 501, cprior);
                                return;
                            }
                        }
                        if ( pres_comb & PCOMB_236B )
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
                        if ( pres_comb & PCOMB_623C )
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

                            if ( skills_1[7] == 0 && skills_1[11] ==0 )
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
                        if ( pres_comb & PCOMB_623B )
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
                            if ( skills_1[7] == 0 && skills_1[11] ==0 )
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
                        if ( pres_comb & PCOMB_236C )
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
                            if ( skills_1[4] == 0 && skills_1[8] == 0 )
                                if ( cprior <= get_prior(503) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 503, cprior);
                                    return;
                                }
                        }
                        if ( pres_comb & PCOMB_236B )
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
                            if ( skills_1[4] == 0 && skills_1[8] == 0 )
                                if ( cprior <= get_prior(502) || (sq >= 500 && sq <= 599 && field_800 == 0))
                                {
                                    if ( field_800 == 0)
                                    {
                                        field_4C8++;
                                        field_800 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 502, cprior);
                                    return;
                                }
                        }
                        if ( pres_comb & PCOMB_214C )
                        {
                            if ( skills_1[9] >= 1 )
                            {
                                if ( cprior <= get_prior(533) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 533, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[5] >= 2 )
                            {
                                if ( cprior <= get_prior(528) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 528, cprior);
                                    return;
                                }
                            }
                        }
                        if ( pres_comb & PCOMB_214B )
                        {
                            if ( skills_1[9] >= 1 )
                            {
                                if ( cprior <= get_prior(532) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 532, cprior);
                                    return;
                                }
                            }
                            if ( skills_1[5] >= 2 )
                            {
                                if ( cprior <= get_prior(527) || (sq >= 500 && sq <= 599 && field_801 == 0))
                                {
                                    if ( field_801 == 0)
                                    {
                                        field_4C8++;
                                        field_801 = 1;
                                    }
                                    sub_4834F0();
                                    sub_4873B0( 527, cprior);
                                    return;
                                }
                            }
                        }
                        if ( pres_comb & PCOMB_2N2C )
                        {
                            if ( skills_1[6] >= 1 )
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
                        }
                        if ( pres_comb & PCOMB_2N2B )
                        {
                            if ( skills_1[6] >= 1 )
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
                        }
                    }
                }
            }

            if ((keyUp(INP_A) && keyUp(INP_A) < 3) || keyDown(INP_A) == 2 || keyHit(INP_A))
            {
                if (char_on_ground_flag()) // On Ground
                {
                    if ( sq == 200 && dY() == 0 &&
                            dX(dir) > 0 &&
                            cprior <= get_prior(305) )  // 66A
                    {
                        angZ = 0;
                        set_seq(305);
                        input->zero_keyhit();
                        return;
                    }

                    if ( (sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 )
                    {
                        if ( dY() > 0 )
                        {
                            if ( ( dX(dir) > 0 || hX(dir) > 0 ) && cprior <= get_prior(304) ) // 3A
                            {
                                angZ = 0;
                                set_seq(304);
                                input->zero_keyhit();
                                return;
                            }
                            else if (cprior <= get_prior(303) ) // 2A
                            {
                                angZ = 0;
                                set_seq(303);
                                input->zero_keyhit();
                                return;
                            }
                        }
                        else if ( dY() >= 0 )
                        {
                            if ( dX(dir) < 0 || hX(dir) < 0 ) // 4a
                                if ( cprior <= get_prior(330) || sq == 330 )
                                {
                                    angZ = 0;
                                    set_seq(330);
                                    input->zero_keyhit();
                                    return;
                                }
                        }

                        if (dY() == 0)
                        {
                            if ( (dX(dir) > 0 || hX(dir) > 0) && cprior <= get_prior(302) ) // 6A
                            {
                                angZ = 0;
                                set_seq(302);
                                input->zero_keyhit();
                                return;
                            }

                            float dst = fabs(x - enemy->x);

                            if ( dst > 60.0 && cprior <= get_prior(301)) //Far A
                            {
                                angZ = 0;
                                set_seq(301);
                                input->zero_keyhit();
                                return;
                            }

                            if(cprior <= get_prior(300)) //near A
                            {
                                angZ = 0;
                                set_seq(300);
                                input->zero_keyhit();
                                return;
                            }
                        }
                    }
                    if ( field_190 != 0 && field_190 != 3 )
                    {
                        if ( sq == 321 ) // AAAA
                        {
                            angZ = 0;
                            set_seq(322);
                            input->zero_keyhit();
                            return;
                        }
                        else if ( sq == 320 ) // AAA
                        {
                            angZ = 0;
                            set_seq(321);
                            input->zero_keyhit();
                            return;
                        }
                        else if ( sq == 300 ) // AA
                        {
                            angZ = 0;
                            set_seq(320);
                            input->zero_keyhit();
                            return;
                        }
                    }
                }
                else if ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) // In Air (Melee)
                {

                    if ( (dY() < 0 || hY() < 0 ) && dX(dir) == 0 && cprior <= get_prior(309) ) //j8A
                    {
                        angZ = 0;
                        set_seq(309);
                        input->zero_keyhit();
                        return;
                    }
                    else if ((dY() > 0 || hY() > 0) /*&& gX(dir) >= 0*/ && cprior <= get_prior(308)) //j2A
                    {
                        angZ = 0;
                        set_seq(308);
                        input->zero_keyhit();
                        return;
                    }
                    else if ( dY() == 0 && (dX(dir) > 0 || hX(dir) > 0 ) && cprior <= get_prior(307)) //j6A
                    {
                        angZ = 0;
                        set_seq(307);
                        input->zero_keyhit();
                        return;
                    }
                    else if ( cprior <= get_prior(306) ) //j5A
                    {
                        angZ = 0;
                        set_seq(306);
                        input->zero_keyhit();
                        return;
                    }
                }
            }

            if ((keyUp(INP_B) && keyUp(INP_B) < 3) || keyDown(INP_B) == 2 || keyHit(INP_B))
            {
                if (char_on_ground_flag()) // On Ground
                {
                    if ( sq == 200 && dY() == 0 && (dX(dir) > 0 || hX(dir) > 0) )  // 66B
                    {
                        angZ = 0;
                        set_seq(408);
                        input->zero_keyhit();
                        return;
                    }

                    if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200)
                    {
                        if ( (dY() > 0 || hY() > 0)/*&& gX(dir) > 0*/ && cprior <= get_prior(402) ) // 2B //HACK?
                        {
                            angZ = 0.0;
                            set_seq(402);
                            input->zero_keyhit();
                            return;
                        }
                        else if ( dY() == 0  && (dX(dir) > 0 || hX(dir) > 0) && cprior <= get_prior(401) )
                        {
                            angZ = 0.0;
                            set_seq(401);
                            input->zero_keyhit();
                            return;
                        }
                        else if (cprior <= get_prior(400) )
                        {
                            angZ = 0.0;
                            set_seq(400);
                            input->zero_keyhit();
                            return;
                        }
                    }
                }
                else if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200 ) //In AIR
                {
                    if ( (dY() > 0 || hY() > 0) && cprior <= get_prior(406))
                    {
                        angZ = 0.0;
                        set_seq(406);
                        input->zero_keyhit();
                        return;
                    }
                    else if ( dY() == 0 && (dX(dir) > 0 || hX(dir) > 0) && cprior <= get_prior(405))
                    {
                        angZ = 0.0;
                        set_seq(405);
                        input->zero_keyhit();
                        return;
                    }
                    else if (cprior <= get_prior(404))
                    {
                        angZ = 0.0;
                        set_seq(404);
                        input->zero_keyhit();
                        return;
                    }
                }
            }
            if ((keyUp(INP_C) && keyUp(INP_C) < 3) || keyDown(INP_C) == 2 || keyHit(INP_C))
            {
                if (char_on_ground_flag()) // On Ground
                {
                    if ( sq == 200 && dY() == 0 && (dX(dir) > 0 || hX(dir) > 0) )  // 66B
                    {
                        angZ = 0;
                        set_seq(418);
                        input->zero_keyhit();
                        return;
                    }
                    if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200)
                    {
                        if ( (dY() > 0 || hY() > 0)/*&& gX(dir) > 0*/ && cprior <= get_prior(412) ) // 2C //HACK?
                        {
                            angZ = 0.0;
                            set_seq(412);
                            input->zero_keyhit();
                            return;
                        }
                        else if ( dY() == 0  && (dX(dir) > 0 || hX(dir) > 0) && cprior <= get_prior(411) ) // 6C
                        {
                            angZ = 0.0;
                            set_seq(411);
                            input->zero_keyhit();
                            return;
                        }
                        else if (cprior <= get_prior(410) )
                        {
                            angZ = 0.0;
                            set_seq(410);
                            input->zero_keyhit();
                            return;
                        }
                    }
                }
                else
                {
                    if ( ((sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300 ) && spell_energy >= 200)
                    {
                        if (dY() <= 0 && (dX(dir) > 0 || hX(dir) > 0) && cprior <= get_prior(415))
                        {
                            angZ = 0.0;
                            set_seq(415);
                            input->zero_keyhit();
                            return;
                        }
                        else if ((dY() > 0 || hY() > 0) && cprior <= get_prior(416))
                        {
                            angZ = 0.0;
                            set_seq(416);
                            input->zero_keyhit();
                            return;
                        }
                        else if (cprior <= get_prior(414))
                        {
                            angZ = 0.0;
                            set_seq(414);
                            input->zero_keyhit();
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
    case 4:
        h_inerc = 6.0;
        break;
    case 5:
        h_inerc = -5.0;
        break;
    case 10:
        reset_forces();
        break;
    case 214:
    case 217:
        reset_ofs();
        h_inerc = 0.0;
        field_7D6 = 0;
        v_inerc = 0.0;
        v_force = 0.6;
        x_off = 0.0;
        y_off = 95.0;
        field_7DC = 12.0;
        field_7EC = 0.0;
        break;
    case 300:
    case 303:
    case 322:
    case 330:
        if ( !field_49A )
            reset_forces();
        field_190 = 0;
        field_194 = 1;
        break;
    case 301:
    case 321:
        if ( !field_49A )
            reset_forces();
        field_190 = 0;
        field_194 = 3;
        break;
    case 302:
        if ( !field_49A )
            reset_forces();
        field_194 = 1;
        field_190 = 0;
        field_49A = 0;
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
        h_inerc = 12.5;
        v_force = 0.0;
        field_49A = 0;
        field_190 = 0;
        field_194 = 1;
        break;
    case 320:
        field_49A = 0;
        field_190 = 0;
        field_194 = 1;
        break;
    case 307:
        field_194 = 1;
        field_190 = 0;
        not_charge_attack = 1;
        v_force = 0.0;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 308:
        h_inerc *= 0.5;
        field_194 = 4;
        field_7D0 = 0;
        field_190 = 0;
        v_inerc *= 0.2;
        not_charge_attack = 1;
        v_force = 0.2;
        break;
    case 309:
        field_194 = 1;
        field_190 = 0;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        not_charge_attack = 1;
        v_force = 0.2;
        break;
    case 310:
        v_force = 0.5;
        field_7D0 = 0;
        field_190 = 0;
        field_194 = 1;
        break;
    case 306:
        field_7D0 = 0;
        field_190 = 0;
        field_194 = 1;
        break;
    case 400:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        not_charge_attack = 1;
        break;
    case 401:
    case 411:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        not_charge_attack = 1;
        break;
    case 402:
        field_190 = 0;
        reset_forces();
        break;
    case 404:
    case 405:
        v_force = 0.05;
        field_190 = 0;
        field_7D0 = 0;
        not_charge_attack = 1;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 406:
    case 415:
        field_190 = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        not_charge_attack = 1;
        v_force = 0.0;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 408:
        h_inerc = 12.0;
        field_49A = 0;
        field_7D0 = 0;
        field_190 = 0;
        v_inerc = 0.0;
        field_194 = 6;
        break;
    case 409:
        field_49A = 0;
        v_force = 0.35;
        field_7D0 = 0;
        field_190 = 0;
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
        not_charge_attack = 1;
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        break;
    case 414:
        field_190 = 0;
        v_force = 0.0;
        not_charge_attack = 1;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 416:
        field_190 = 0;
        v_force = 0.05;
        not_charge_attack = 1;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 418:
        h_inerc = 15.0;
        if ( !field_49A )
            reset_forces();
        field_190 = 0;
        field_194 = 1;
        break;

    case 420:
    case 421:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        break;
    case 422:
        field_190 = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        v_force = 0.0;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 430:
    case 431:
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        break;
    case 432:
        field_190 = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        v_force = 0.0;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 500:
    case 501:
        field_7D0 = 3;
        if ( skills_1[0] >= 1 )
            field_7D0 = 4;
        if ( skills_1[0] >= 3 )
            field_7D0 = 5;
        field_7D2 = 0;
        field_7D4 = 0;
        field_7D6 = 0;
        field_18C = 0;
        reset_forces();
        field_190 = 0;
        field_49A = 0;
        not_charge_attack = 1;
        break;
    case 502:
    case 503:
        field_7D0 = 3;
        if ( skills_1[0] >= 1 )
            field_7D0 = 4;
        if ( skills_1[0] >= 3 )
            field_7D0 = 5;
        v_force = 0.05;
        field_7D2 = 0;
        field_7D4 = 0;
        field_7D6 = 0;
        field_18C = 0;
        h_inerc *= 0.15;
        v_inerc *= 0.15;
        field_190 = 0;
        field_49A = 0;
        not_charge_attack = 1;
        break;
    case 505:
    case 506:
        field_18C = 4;
        field_7D0 = 3;
        field_7D2 = 0;
        field_7D4 = 0;
        field_7D6 = 0;
        reset_forces();
        field_190 = 0;
        field_49A = 0;
        not_charge_attack = 1;
        break;
    case 510:
    case 512:
        field_18C = 8;
        reset_forces();
        field_194 = 0;
        field_190 = 0;
        field_49A = 0;
        break;
    case 520:
    case 521:
        field_18C = 1;
        reset_forces();
        field_7D0 = 0;
        field_49A = 0;
        field_190 = 1;
        not_charge_attack = 1;
        break;
    case 525:
    case 526:
    case 527:
    case 528:
        field_18C = 5;
        reset_forces();
        field_190 = 0;
        field_49A = 0;
        field_194 = 1;
        break;
    case 530:
    case 531:
    case 532:
    case 533:
        field_18C = 9;
        reset_forces();
        field_194 = 1;
        field_190 = 0;
        field_49A = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D4 = 0;
        break;
    case 540:
    case 541:
        field_18C = 2;
        field_190 = 0;
        reset_forces();
        not_charge_attack = 1;
        break;
    case 542:
        field_190 = 0;
        not_charge_attack = 0;
        field_18C = 2;
        field_194 = 1;
        break;
    case 545:
    case 546:
        field_18C = 6;
        field_190 = 0;
        reset_forces();
        not_charge_attack = 1;
        break;
    case 547:
    case 548:
        field_18C = 6;
        field_190 = 0;
        not_charge_attack = 1;
        h_inerc *= 0.1;
        v_inerc *= 0.1;
        v_force = 0.0;
        break;
    case 550:
    case 551:
        field_18C = 10;
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        break;
    case 560:
    case 561:
        field_18C = 3;
        field_190 = 0;
        reset_forces();
        not_charge_attack = 1;
        break;
    case 562:
    case 563:
        field_18C = 3;
        v_force = 0.0;
        field_190 = 0;
        h_inerc *= 0.1;
        v_inerc *= 0.1;
        break;
    case 565:
    case 566:
        field_18C = 7;
        field_190 = 0;
        reset_forces();
        field_7D0 = 0;
        not_charge_attack = 1;
        break;
    case 567:
    case 568:
        field_18C = 7;
        field_190 = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        not_charge_attack = 1;
        v_force = 0.0;
        h_inerc *= 0.2;
        v_inerc *= 0.2;
        break;
    case 570:
    case 571:
    case 572:
    case 573:
        field_18C = 11;
        field_7D0 = 0;
        field_190 = 0;
        reset_forces();
        field_194 = 1;
        break;
    case 599:
        field_190 = 1;
        reset_forces();
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D6 = 0;
        field_7D8 = 0;
        break;
    case 600:
    case 650:
        field_7D0 = 3;
        field_7D2 = 0;
        field_7D4 = 0;
        field_7D6 = 0;
        reset_forces();
        field_190 = 0;
        field_49A = 0;
        break;
    case 601:
    case 602:
    case 652:
        field_190 = 0;
        reset_forces();
        field_49A = 0;
        break;
    case 603:
    case 653:
        field_190 = 0;
        reset_forces();
        field_194 = 99;
        field_49A = 0;
        field_7D0 = 0;
        field_7D2 = 0;
        field_7D4 = 0;
        break;
    case 604:
    case 654:
        field_7D0 = 0;
        field_49A = 0;
        field_190 = 0;
        reset_forces();
        break;
    case 707:
    case 720:
    case 722:
        reset_forces();
        break;
    case 605:
    case 606:
    case 655:
        field_49A = 0;
        field_190 = 0;
        reset_forces();
        break;
    case 607:
        reset_forces();
        field_49A = 0;
        field_190 = 0;
        field_7D0 = 0;
        field_194 = 4;
        break;
    case 608:
    case 610:
    case 613:
    case 658:
    case 660:
    case 663:
        field_190 = 0;
        reset_forces();
        break;
    case 708:
        reset_forces();
        field_7D0 = 0;
        break;
    case 721:
    case 725:
        break;
    case 710:
    case 712:
        reset_forces();
        flip_with_force();
        break;
    case 711:
        h_inerc *= 0.25;
        v_inerc *= 0.25;
        flip_with_force();
        break;
    case 730:
    case 732:
        field_7D0 = 0;
        field_7D2 = 0;
        reset_forces();
        break;
    case 731:
    case 733:
        field_7D0 = 0;
        field_7DC = 0.0;
        field_7D2 = 0;
        reset_forces();
        break;
    case 780:
        field_7D0 = 30;
        field_7DC = 0.0;
        break;
    case 798:
        field_7D0 = 0;
        play_sfx( 5);
        break;
    default:
        char_c::set_seq_params();
        break;
    }
}






void char_cirno::sub_6E28C0()
{
    if ( v_inerc > 0.0 || dY() <= 0 )
    {
        if ( v_inerc < -1.5 )
        {
            v_inerc = -1.5;

            if ( dX(dir) == 0 )
                h_inerc *= 0.95;
            else if ( dX(dir) > 0 )
            {
                if ( h_inerc < 7.0 )
                    h_inerc = 7.0;
            }
            else /*if ( dX(dir) < 0 )*/
            {
                if ( h_inerc > -7.0 )
                    h_inerc = -7.0;
            }
        }
    }
    else
        set_seq(11);
}
