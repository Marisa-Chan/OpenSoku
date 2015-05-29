#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "cirno.h"
#include "cirno_bullets.h"
#include <math.h>


void cirno_bullets::func10()
{
    switch(get_seq())
    {
    case 800:
        if ( field_190 == 5 || x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
        case 7:
            if ( sub_48C6A0( 0, 0, 3) )
            {
                active = false;
                break;
            }
            set_vec_speed(addition[0], addition[1]);
            addition[1] += 0.25;
            if ( get_frame_time() <= 180 && field_190 == 0 && getlvl_height() < y )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                active = false;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 4.0;
                for (int32_t i=0; i<2; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 800, x, y, dir, 1, tmp,3);
                }

                tmp[2] = 5.0;
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 800, x, y, dir, 1, tmp,3);
                }

                tmp[2] = 6.0;
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 800, x, y, dir, 1, tmp,3);
                }
            }
            break;
        case 1:
            scaleY = scaleX *= 0.85;
            if ( c_A < 25 )
            {
                active = false;
                return;
            }
            c_A -= 25;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.05;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;

            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.98;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            field_37C -= 0.1;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
        case 5:
            angZ += field_378;
            v_inerc -= 0.5;
            if ( v_inerc < 0.0 )
            {
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            }
            if ( (int32_t)get_elaps_frames() >= field_36C )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.98;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.9;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 801:
        if ( field_190 == 5 || x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0( 0, 2, 2) )
            {
                active = false;
                break;
            }
            set_vec_speed(addition[0], addition[1]);
            addition[1] += 0.75;
            if ( addition[1] >= 22.5 )
                addition[1] = 22.5;
            sub_48C5F0( 0);
            if ( field_190 == 4 )
                field_194 = 0;
            if ( field_190 != 0 && field_190 != 4 )
                addition[1] = 3.0;
            if ( field_190 != 0 )
                if ( field_194 > 0 )
                {
                    field_36C++;
                    if ( field_36C >= 2 )
                    {
                        field_36C = 0;
                        field_190 = 0;
                    }
                }
            if ( get_elaps_frames() % 4 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(8) + 10.0;
                tmp[2] = 3.0;
                addbullet( chrt,NULL, 801, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 5 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = 6 * get_elaps_frames();
                tmp[2] = 1.0;
                addbullet( chrt,NULL, 801, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(8);
                tmp[2] = 2.0;
                addbullet( chrt,NULL, 801, x, y, dir, 1, tmp,3);
            }
            if ( get_frame_time() <= 180 && field_194 > 0 && getlvl_height() < y )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                active = false;

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 4.0;
                for (int32_t i=0; i<2; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 801, x, y, dir, 1, tmp,3);
                }

                tmp[2] = 5.0;
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 801, x, y, dir, 1, tmp,3);
                }

                tmp[2] = 6.0;
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 801, x, y, dir, 1, tmp,3);
                }
            }
            break;
        case 1:
            scaleY = scaleX += 0.1;
            angZ += 8.0;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.05;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.98;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            field_37C -= 0.1;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
        case 5:
            angZ += field_378;
            v_inerc -= 0.5;
            if ( v_inerc < 0.0 )
            {
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            }
            if ( (int32_t) get_elaps_frames() >= field_36C )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.98;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.9;

            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 802:
        if ( field_190 == 5 || x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0( 0, 0, 3) )
            {
                active = false;
                break;
            }
            set_vec_speed(addition[0], addition[1]);
            addition[1] += 0.25;
            if ( get_frame_time() <= 180 && field_190 == 0 )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                active = false;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 4.0;
                for (int32_t i=0; i<2; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 802, x, y, dir, 1, tmp,3);
                }

                tmp[2] = 5.0;
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 802, x, y, dir, 1, tmp,3);
                }

                tmp[2] = 6.0;
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(10);
                    addbullet( chrt,NULL, 802, x, y, dir, 1, tmp,3);
                }
            }
            break;
        case 1:
            scaleY = scaleX *= 0.85;
            if ( c_A < 25 )
            {
                active = false;
                break;
            }
            c_A -= 25;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            v_inerc *= 0.25;
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.05;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.98;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            field_37C -= 0.1;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
        case 5:
            angZ += field_378;
            v_inerc -= 0.5;
            if ( v_inerc < 0.0 )
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            if ( (int32_t)get_elaps_frames() >= field_36C )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.98;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.9;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 7:
            if ( sub_48C6A0( 0, 2, 3) )
            {
                active = false;
                break;
            }
            if ( getlvl_height() < y )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;
                addbullet( chrt, NULL, 802, x, y, dir, 1, tmp,3);
                for (int32_t i=0; i<5; i++)
                {
                    tmp[0] = scene_rand_rngf(8) + 20.0 - addition[0] - i * 10.0 - 4.0;
                    tmp[1] = scene_rand_rngf(6) + 17.5;
                    tmp[2] = 0.0;
                    addbullet( chrt, NULL, 802, x, y, dir, 1, tmp,3);
                }
                for (int32_t i=0; i<12; i++)
                {
                    tmp[0] = scene_rand_rngf(8) + i * 30.0 - 4.0;
                    tmp[1] = 25.5;
                    tmp[2] = 2.0;
                    if (sin_deg(-tmp[0]) < 0.0)
                        field_36C = 1;
                    else
                        field_36C = -1;
                    addbullet( chrt, NULL, 802, x, y, field_36C, 1, tmp,3);
                }
                for (int32_t i=0; i<5; i++)
                {
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(15) + 10.0;
                    tmp[2] = 3.0;
                    addbullet( chrt, NULL, 802, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 805:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_190 == 5 || sub_48C6A0( 0, 1, 4) )
            {
                active = false;
                break;
            }
            addition[1] *= 0.92;
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;

                if ( scene_rand_rngf(100) <= 50 )
                    tmp[2] = 2.0;
                addbullet( chrt, NULL, 805, scene_rand_rngf(60) + x - 30.0, scene_rand_rngf(60) + y - 30.0, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 4 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(50) * 0.1 + 5.0;
                tmp[2] = 4.0;
                addbullet( chrt, NULL, 805, x, y, dir, 1, tmp,3);
            }
            if ( sub_48C5F0( 10) )
            {
                active = false;
                break;
            }
            if ( field_190 != 0)
            {
                if ( field_190 == 4 )
                    field_194 = 0;
                else
                {
                    field_36C++;
                    if ( field_36C >= 10 )
                    {
                        field_190 = 0;
                        field_36C = 0;
                    }
                }
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 ||
                    get_elaps_frames() > 45 || field_194 <= 0 || addition[1] <= 3.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 2:
            if ( get_elaps_frames() < 40 )
            {
                scaleX += 0.2;
                if ( field_37C <= scaleX )
                    scaleX = field_37C;
                scaleY = scaleX;
            }
            else
            {
                v_inerc -= 0.3;
                angZ += field_378;
                if ( c_A < 16 )
                {
                    active = false;
                    break;
                }
                c_A -= 16;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            scaleY = scaleX *= 0.65;
            if ( c_A < 40 )
            {
                active = false;
                break;
            }
            c_A -= 40;
            if ( process() )
                active = false;
            break;
        case 4:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( process() )
                active = false;
            break;
        }
        break;
    case 806:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_190 == 5 || sub_48C6A0( 0, 2, 5) )
            {
                active = false;
                break;
            }
            sub_48C4B0( 0.0, 1.0, 100.0);
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;
                if ( scene_rand_rngf(100) <= 50 )
                    tmp[2] = 2.0;
                addbullet( chrt, NULL, 806, scene_rand_rngf(60) + x - 30.0, scene_rand_rngf(60) + y - 30.0, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(100) * 0.1 + 10.0;
                tmp[2] = 4.0;
                addbullet( chrt, NULL, 806, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet( chrt, NULL, 806, x, y, dir, 1, tmp,3);
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 2:
            if ( get_elaps_frames() >= 40 || sub_48C6A0( 0, 0, 0) )
            {
                chrt->play_sfx( 1);
                active = false;
                for (int32_t i=0; i<2; i++)
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(3) + 3.0;
                    tmp[2] = 6.0;
                    addbullet( chrt, NULL, 806, x, y, dir, 1, tmp,3);
                }
                for (int32_t i=0; i<2; i++)
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(4) + 4.0;
                    tmp[2] = 7.0;
                    addbullet( chrt, NULL, 806, x, y, dir, 1, tmp,3);
                }
            }
            else
            {
                scaleX += 0.2;
                if ( field_37C <= scaleX )
                    scaleX = field_37C;
                scaleY = scaleX;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            scaleY = scaleX += 0.1;
            if ( get_elaps_frames() >= 2 )
                field_194 = 0;
            if ( c_A < 40 )
            {
                active = false;
                break;
            }
            c_A -= 40;
            if ( process() )
                active = false;
            break;
        case 4:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( sub_48C6A0( 0, 0, 0) )
            {
                active = false;
                break;
            }
            if ( get_elaps_frames() < 40 )
            {
                if ( process() )
                    active = false;
            }
            else
            {
                active = false;
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = 0.0;
                tmp[2] = 3.0;
                addbullet( chrt, NULL, 806, x, y, dir, 1, tmp,3);
                for (int32_t i=0; i<3; i++)
                {
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(4) + 6.0;
                    tmp[2] = 4.0;
                    addbullet( chrt,NULL, 806, x, y, dir, 1, tmp,3);
                }
            }
            break;
        case 6:
        case 7:
            angZ += field_378;
            v_inerc -= 0.2;
            if ( v_inerc < 0.0 )
            {
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            }
            if ( (int32_t)get_elaps_frames() >= 0 )
            {
                if ( c_A < 15 )
                {
                    active = false;
                    break;
                }
                c_A -= 15;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( process() )
                active = false;
            break;
        }
        break;
    case 807:
        switch ( get_subseq() )
        {
        case 0:
        {
            if ( chrt->get_seq() != 412 )
            {
                active = false;
                break;
            }
            scaleX += 0.05;
            scaleY += 0.05;
            CharFrameData *frm = chrt->get_pframe();
            x = frm->extra1[4] * dir + chrt->x;
            y = chrt->y - frm->extra1[5];
            if ( chrt->get_subseq() == 0 && chrt->get_frame() == 4 )
            {
                next_subseq();
                chrt->play_sfx( 3);
                h_inerc = 5.0;
                v_inerc = 17.5;
                break;
            }
            if ( chrt->get_subseq() == 4 && chrt->get_frame() == 2 )
            {
                set_subseq( 2);
                chrt->play_sfx( 3);
                h_inerc = 2.5;
                v_inerc = 35.0;
                break;
            }
            if ( process() )
                active = false;
        }
        break;
        case 1:
        case 2:
            if ( field_190 == 5 || sub_48C6A0( 0, 2, 5) )
            {
                active = false;
                break;
            }
            angZ -= 12.0;
            sub_48C5F0( 0);
            set_custom_box( scaleX * -20.0, scaleX * 20.0, scaleX * 20.0, scaleX * -20.0, addition[0], 0, 0);
            if ( getlvl_height() > y || field_194 <= 0 || health <= -1000 )
            {
                chrt->play_sfx( 4);

                for (int32_t i=0; i<4; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(6) + 8.0;
                    tmp[2] = 6.0;
                    float xx = cos_deg(-tmp[0]) * tmp[1] * 3.0 * dir + x;
                    float yy = cos_deg(-tmp[0]) * tmp[1] * 3.0 + y;
                    addbullet(chrt,NULL, 807, xx, yy, dir, 1, tmp, 3);

                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(6) + 8.0;
                    tmp[2] = 7.0;
                    xx = cos_deg(-tmp[0]) * tmp[1] * 3.0 * dir + x;
                    yy = cos_deg(-tmp[0]) * tmp[1] * 3.0 + y;
                    addbullet(chrt,NULL, 807, xx, yy, dir, 1, tmp, 3);
                    //shake_camera(3.0); //HACK
                }
                active = false;
                break;
            }
            if ( get_elaps_frames() % 4 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) * 0.1 + 2.0;
                tmp[2] = 4.0;
                addbullet(chrt,NULL, 807, x, y, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 5 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(100) * 0.1 + 10.0;
                tmp[2] = 3.0;
                addbullet(chrt,NULL, 807, x, y, dir, 1, tmp, 3);
            }
            if ( x > 1380.0  || x < -100 || y < -100.0)
            {
                active = false;
                break;
            }
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.95;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.05;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
        case 7:
            angZ += field_378;
            v_inerc -= 0.2;
            if ( v_inerc < 0.0 )
            {
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            }
            if ( (int32_t)get_elaps_frames() >= 0 )
            {
                if ( c_A < 15 )
                {
                    active = false;
                    break;
                }
                c_A -= 15;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( process() )
                active = false;
            break;
        }
        break;
    case 808:
        switch ( get_subseq() )
        {
        case 0:
        {
            CharFrameData *frm = chrt->get_pframe();

            if ( get_elaps_frames() % 6 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = 2.0;
                tmp[2] = 4.0;
                addbullet(chrt,NULL, 808, x, y - get_pframe()->extra1[5] * scaleY, dir, 1, tmp, 3);
            }
            if ( (chrt->get_seq() != 416 && chrt->get_seq() != 412) || chrt->get_subseq() == 3 )
            {
                active = false;
                break;
            }
            scaleX += 0.05;
            scaleY += 0.05;
            x = frm->extra1[4] * dir + chrt->x;
            y = chrt->y - frm->extra1[5];
            if ( chrt->get_subseq() == 2 && chrt->get_frame() == 1 )
            {
                chrt->play_sfx( 3);
                next_subseq();
                h_inerc = chrt->h_inerc + 7.5;
                v_inerc = chrt->v_inerc + 10.0;
                break;
            }
            if ( process() )
                active = false;
        }
        break;
        case 1:
        case 2:
            if ( field_190 == 5 || sub_48C6A0( 0, 2, 5) )
            {
                active = false;
                break;
            }
            sub_48C5F0( 0);
            set_custom_box( scaleX * -25.0, scaleY * -50.0, scaleX * 25.0, 0, addition[0], 0,0);
            if ( getlvl_height() > y || field_194 <= 0 || health <= -1000 )
            {
                chrt->play_sfx( 4);
                for (int32_t i=0; i<4; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(6) + 8.0;
                    tmp[2] = 6.0;
                    float xx = cos_deg(-tmp[0]) * tmp[1] * 3.0 * dir + x;
                    float yy = cos_deg(-tmp[0]) * tmp[1] * 3.0 + y + scaleY * 24.0;
                    addbullet(chrt,NULL, 808, xx, yy, dir, 1, tmp, 3);

                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(6) + 8.0;
                    tmp[2] = 7.0;
                    xx = cos_deg(-tmp[0]) * tmp[1] * 3.0 * dir + x;
                    yy = cos_deg(-tmp[0]) * tmp[1] * 3.0 + y + scaleY * 24.0;
                    addbullet(chrt,NULL, 808, xx, yy, dir, 1, tmp, 3);
                    //shake_camera(3.0); //HACK
                }
                active = false;
                break;
            }
            if ( get_elaps_frames() % 4 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) * 0.1 + 2.0;
                tmp[2] = 4.0;
                addbullet( chrt, NULL, 808, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 5 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(100) * 0.1 + 10.0;
                tmp[2] = 3.0;
                addbullet(chrt,NULL, 807, x, y, dir, 1, tmp, 3);
            }
            if ( x > 1380.0  || x < -100 || y < -100.0)
            {
                active = false;
                break;
            }
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 0.95;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.05;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
        case 7:
            angZ += field_378;
            v_inerc -= 0.2;
            if ( v_inerc < 0.0 )
            {
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            }
            if ( (int32_t) get_elaps_frames() >= 0 )
            {
                if ( c_A < 15 )
                {
                    active = false;
                    break;
                }
                c_A -= 15;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
        default:
            if ( process() )
                active = false;
            break;
        }
        break;
    case 810:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C == 0 )
            {
                if ( chrt->get_seq() < 500 || chrt->get_seq() > 503 || chrt->get_subseq() > 1 )
                {
                    field_36C = 1;
                }
                else
                {
                    x = chrt->x;
                    y = chrt->y + 220.0;
                    scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                    field_378 += 0.01;
                    if ( get_elaps_frames() % (17 - chrt->field_7D0) == 0 )
                    {
                        float tmp[3];
                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = 1.0;
                        addbullet( chrt,NULL, 810, x + 50.0 - scene_rand_rngf(100), y + 50.0 - scene_rand_rngf(100), dir, 1, tmp,3);
                    }
                }
            }
            else
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 || sub_48C6A0( 0, 0, 4) )
            {
                active = false;
                break;
            }
            if ( field_190 != 0)
            {
                chrt->play_sfx( 1);
                for (int32_t i = 0; i < 4; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 )
            {
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
            angZ += addition[0];
            addition[0] *= 0.95;
            addition[1] *= 0.85;
            if ( addition[1] <= 0.025 )
                addition[1] = 0.025;
            scaleY = scaleX += addition[1];
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 811:
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0( 0, 3, 5) )
            {
                active = false;
                break;
            }
            if ( field_36C == 0)
            {
                if ( chrt->get_seq() < 505 || chrt->get_seq() > 508 )
                {
                    active = false;
                    break;
                }
                x = chrt->x;
                y = chrt->y + 300.0;
                scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                field_378 += 0.01;
                if ( chrt->get_subseq() == 2 )
                    field_36C = 1;

                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                set_vec_speed(addition[0], addition[1]);
                if ( getlvl_height() > y )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 10.0;
                    addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp,3);
                    tmp[2] = 4.0;
                    addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp,3);

                    for(int32_t i=0; i< 8; i++)
                    {
                        tmp[0] = scene_rand_rngf(30) + i * 45.0;
                        tmp[1] = 15.0;
                        tmp[2] = 2.0;

                        addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp,3);
                    }
                    for(int32_t i=0; i< 15; i++)
                    {
                        tmp[0] = scene_rand_rngf(180);
                        tmp[1] = scene_rand_rngf(15) + 5.0;
                        tmp[2] = 3.0;

                        addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp,3);
                    }
                    active = false;
                }
                else
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                }
            }
            break;
        case 1:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            scaleY = scaleX += 0.2;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( scaleX * 100.0 < field_378 )
            {
                field_194 = 0;
            }
            else
            {
                field_378 += 20.0;
                x += cos_deg(-addition[0]) * 20.0 * dir;
                y += sin_deg(-addition[0]) * 20.0;
            }
            if ( addition[1] <= get_elaps_frames() )
            {
                scaleY = scaleX *= 0.99;
                if ( c_A < 7 )
                {
                    active = false;
                    break;
                }
                c_A -= 7;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( scaleX * 230.0 < field_378 )
            {
                field_194 = 0;
            }
            else
            {
                field_378 += 50.0;
                x += cos_deg(-addition[0]) * 50.0 * dir;
                y += sin_deg(-addition[0]) * 50.0;
            }
            if ( addition[1] <= get_elaps_frames() )
            {
                scaleY = scaleX *= 0.98;
                if ( c_A < 7 )
                {
                    active = false;
                    break;
                }
                c_A -= 7;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
            if ( sub_48C6A0( 0, 0, 0) || enemy->health <= 0
                    || get_elaps_frames() >= addition[3] + 60 * (chrt->skills_1[4] + 4)
                    || ((chrt->get_seq() == 505 || chrt->get_seq() == 506) && chrt->get_subseq() == 0) )
            {
                active = false;
                break;
            }
            if ( get_elaps_frames() % 6 == 0 )
            {
                float tmp[3];
                tmp[0] = get_elaps_frames() * 4.0;
                tmp[1] = 3.0;
                tmp[2] = 2.0;
                if ( sin_deg(4.0 * get_elaps_frames()) > 0.0 )
                {
                    addbullet( chrt,NULL, 811, cos_deg(-tmp[0]) * 150.0 * dir + x, sin_deg(-tmp[0]) * 25.0 + y, dir, -1, tmp,3);

                    tmp[0] += 180.0; //HACK!?
                    addbullet( chrt,NULL, 811, cos_deg(-tmp[0]) * 150.0 * dir + x, sin_deg(-tmp[0]) * 25.0 + y, dir, -1, tmp,3);
                }
                else
                {
                    addbullet( chrt,NULL, 811, cos_deg(-tmp[0]) * 150.0 * dir + x, sin_deg(-tmp[0]) * 25.0 + y, dir, 1, tmp,3);

                    tmp[0] += 180.0; //HACK!?
                    addbullet( chrt,NULL, 811, cos_deg(-tmp[0]) * 150.0 * dir + x, sin_deg(-tmp[0]) * 25.0 + y, dir, 1, tmp,3);
                }
            }
            if ( !enemy->sub_469730() && !enemy->sub_469710()
                    && fabs(enemy->x - x) < 150.0
                    && fabs(enemy->y - y) < 100.0 )
            {
                chrt->play_sfx( 7);
                float tmp[3];
                tmp[1] = 30.0;
                tmp[2] = 5.0;

                for(int32_t i=0; i<6; i++)
                {
                    tmp[0] = -85.0 - scene_rand_rngf(10);
                    float ps = scene_rand_rngf(40) - 20.0;
                    addbullet( chrt, NULL, 811, scene_rand_rngf(100) + x - 175.0 + i * 50.0, ps + y - 120.0, dir, (1 - 2 * (ps > 0.0)), tmp,3);
                }

                tmp[2] = 6.0;
                for(int32_t i=0; i<3; i++)
                {
                    tmp[0] = -85.0 - scene_rand_rngf(10);
                    float ps = scene_rand_rngf(20) - 10.0;
                    addbullet( chrt, NULL, 811, scene_rand_rngf(60) + x - 130.0 + i * 100.0, ps + y - 240.0, dir, (1 - 2 * (ps > 0.0)), tmp,3);
                }
                tmp[2] = 11.0;
                addbullet( chrt, NULL, 811, x, y, dir, 1, tmp,3);
                active = false;
            }
            else
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 11:
            if ( get_elaps_frames() >= 10 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 812:
        if (get_subseq() == 0)
        {
            if ( x > 1600.0 || x < -320.0 || y < -480.0 || y > 1280.0 )
            {
                active = false;
                break;
            }
            if ( field_374 == 0 )
                if ( chrt->get_seq() < 510 || chrt->get_seq() > 514 || chrt->get_subseq() >= 5 )
                {
                    field_378 = field_37C;
                    field_374 = 1;
                }
            field_37C += 15.0;
            if ( field_378 <= field_37C )
            {
                field_37C = field_378;
                set_vec_speed(addition[0], addition[1]);
            }
            if ( field_36C )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.05 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                set_custom_box(0, (scaleY * 20.0), field_37C, (scaleY * -20.0), addition[0], 0,0);
                sub_48C5F0( 0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_190 = 0;
                        field_36E = 0;
                    }
                }
                if ( field_194 <= 0 )
                {
                    field_36C = 1;
                    break;
                }
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    break;
                }
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        else if ( get_subseq() == 1 )
        {
            angZ = scene_rand_rngf(360);
            if ( sub_48C6A0( 0, 0, 2) )
            {
                active = false;
                break;
            }
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                if ( bul_parent->field_36C )
                    scaleY = scaleX *= 0.85;
                if ( scaleX < 0.05 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.01 )
                {
                    active = false;
                    break;
                }
            }
        }
        else if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            if ( sub_48C6A0( 0, 1, 4) || !bul_parent )
            {
                active = false;
                break;
            }
            x = cos_deg(-bul_parent->angZ) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin_deg(-bul_parent->angZ) * bul_parent->field_37C + bul_parent->y;
            if ( bul_parent->field_36C )
                scaleX = scaleY *= 0.8;
            if ( scaleY <= 0.05 )
            {
                active = false;
                break;
            }
        }
        if ( process() )
            active = false;
        if ( get_subseq() == 0 )
            sub_438450( 0.0, 0.0, field_37C, 256.0);
        break;
    case 815:
        switch ( get_subseq() )
        {
        case 0:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            scaleY = scaleX = bul_parent->scaleX;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
        case 6:
            if ( chrt->hit_stop <= 0 )
                angZ = chrt->h_inerc / (scaleX * 310.0) * 360.0 + angZ;
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }

            if ( chrt->get_seq() == 520 || chrt->get_seq() == 521 )
            {
                if ( chrt->get_subseq() == 1 )
                {
                    if ( field_36C == 0 )
                    {
                        field_36C = 1;
                        field_194 = 99;
                        float tmp[3];
                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = 0.0;

                        addbullet(chrt, this, 815, x, y, dir, -1, tmp,3);
                    }
                }
                if ( chrt->get_subseq() == 3 )
                {
                    field_194 = 1;
                    field_190 = 0;
                    set_subseq( 7);
                    h_inerc = chrt->h_inerc + 2.0;
                    break;
                }
                if ( chrt->h_inerc > 0.0 )
                    if ( chrt->hit_stop <= 0 )
                        scaleX += 0.02;
            }

            scaleY = scaleX;
            set_custom_box( (scaleX * -50.0), (scaleX * 50.0), (scaleX * 50.0), (scaleX * -50.0), addition[0], 0, 0);
            x = (scaleX * 50.0 + 40.0) * dir + chrt->x;
            y = chrt->y + scaleY * 50.0;

            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = -scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5) + 5.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 815, cos_deg(-tmp[0]) * 50.0 * dir + x, sin_deg(-tmp[0]) * 50.0 + y, dir, 1, tmp, 3);
            }
            if ( field_190 )
                if ( field_194 > 0 )
                {
                    field_36E++;
                    if ( field_36E > 15 )
                    {
                        field_36E = 0;
                        field_190 = 0;
                    }
                    chrt->field_190 = field_190;
                }
            if ( health > 0 )
                if ( getlvl_height() <= y - 49.9 * scaleY ) //HACK float rounding
                    if ( (x <= 1280.0 && x >= 0.0) || chrt->get_elaps_frames() < 30 || chrt->get_subseq() != 1 )
                        if ( chrt->get_seq() == 520 || chrt->get_seq() == 521 )
                        {
                            x += dir * h_inerc;
                            y += v_inerc;
                            if ( process() )
                                active = false;
                            break;
                        }

            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = -scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(7) + 3.0;
                tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y;
                addbullet( chrt,NULL, 815, xx, yy, dir, 1, tmp,3);
            }
            for (int32_t i=0; i<8; i++)
            {
                tmp[0] = i * 45.0 - scene_rand_rngf(30);
                tmp[1] = scene_rand_rngf(2) + 8.0;
                tmp[2] = 2.0;

                float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                float yy = sin_deg(-tmp[0]) * 50.0 + y;
                addbullet( chrt,NULL, 815, xx, yy, dir, 1, tmp,3);
            }
            if ( chrt->get_seq() == 520 || chrt->get_seq() == 521 )
                chrt->field_7D0 = 1;
            chrt->play_sfx( 10);
            active = false;
            break;
        case 7:
            angZ = h_inerc / (scaleX * 310.0) * 360.0 + angZ;
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            set_custom_box( (scaleX * -50.0), (scaleX * 50.0), (scaleX * 50.0), (scaleX * -50.0), addition[0], 0, 0);
            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = -scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5) + 5.0;
                tmp[2] = 2.0;

                float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                float yy = sin_deg(-tmp[0]) * 50.0 + y;

                addbullet( chrt,NULL, 815, xx, yy, dir, 1, tmp,3);
            }
            if ( getlvl_height() < y - scaleY * 50.0 )
                v_inerc -= 0.5;
            if ( getlvl_height() >= y - scaleY * 50.0 )
                if ( getlvl_height() <= y - scaleY * 50.0 + 5.0 )
                {
                    y = getlvl_height() + scaleY * 50.0;
                    v_inerc = 0.0;
                }
            sub_48C5F0( 0);
            if ( health > 0
                    && getlvl_height() <= y - scaleY * 50.0 + 5.0
                    && field_190 == 0 )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                float tmp[3];
                for (int32_t i=0; i<12; i++)
                {
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 3.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y;
                    addbullet( chrt,NULL, 815, xx, yy, dir, 1, tmp,3);
                }
                for (int32_t i=0; i<8; i++)
                {
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 8.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 50.0 + y;
                    addbullet( chrt,NULL, 815, xx, yy, dir, 1, tmp,3);
                }
                chrt->play_sfx( 10);
                active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 816:
        switch ( get_subseq() )
        {
        case 0:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            scaleY = scaleX = bul_parent->scaleX;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
        case 6:
            if ( chrt->get_seq() < 525 || chrt->get_seq() > 528 )
            {
                for(int32_t i=0; i<12; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 8.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet(chrt, NULL, 816, cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x, sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0, dir, 1, tmp, 3);
                }
                for (int32_t i=0; i<8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 13.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 50.0 + y + 100.0;
                    addbullet( chrt,NULL, 816, xx, yy, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( chrt->get_subseq() != 1 )
                {
                    for(int32_t i=0; i<12; i++)
                    {
                        float tmp[3];
                        tmp[0] = -scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(7) + 8.0;
                        tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                        addbullet(chrt, NULL, 816, cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x, sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0, dir, 1, tmp, 3);
                    }
                    for (int32_t i=0; i<8; i++)
                    {
                        float tmp[3];
                        tmp[0] = i * 45.0 - scene_rand_rngf(30);
                        tmp[1] = scene_rand_rngf(2) + 13.0;
                        tmp[2] = 2.0;

                        float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                        float yy = sin_deg(-tmp[0]) * 50.0 + y + 100.0;
                        addbullet( chrt,NULL, 816, xx, yy, dir, 1, tmp,3);
                    }
                    active = false;
                }
                else
                {
                    x = chrt->x;
                    y = chrt->y;
                    if ( get_elaps_frames() % 2 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = 2.0;

                        float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                        float yy = sin_deg(-tmp[0]) * 50.0 + y;
                        addbullet( chrt,NULL, 816, xx, yy, dir, 1, tmp,3);
                    }
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                }
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 817:
        switch ( get_subseq() )
        {
        case 0:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            scaleY = scaleX = bul_parent->scaleX;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
        case 6:
            if ( chrt->get_seq() < 525 || chrt->get_seq() > 528 )
            {
                for (int32_t i=0; i< 12; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 8.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0;

                    addbullet(chrt, NULL, 817, xx, yy, dir, 1, tmp, 3);
                }
                for (int32_t i=0; i< 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 13.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 50.0 + y + 100.0;

                    addbullet(chrt, NULL, 817, xx, yy, dir, 1, tmp, 3);
                }
                active = false;
                break;
            }
            if ( chrt->get_subseq() != 1 )
            {
                for (int32_t i=0; i< 12; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 8.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0;

                    addbullet(chrt, NULL, 817, xx, yy, dir, 1, tmp, 3);
                }
                for (int32_t i=0; i< 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 13.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 50.0 + y + 100.0;

                    addbullet(chrt, NULL, 817, xx, yy, dir, 1, tmp, 3);
                }
                active = false;
                break;
            }
            x = chrt->x;
            y = chrt->y;

            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = -scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5) + 5.0;
                tmp[2] = 2.0;

                float xx = cos_deg(-tmp[0]) * tmp[1] * 50.0 * dir + x;
                float yy = sin_deg(-tmp[0]) * tmp[1] * 50.0 + y;

                addbullet(chrt, NULL, 817, xx, yy, dir, 1, tmp, 3);
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 820:
        switch ( get_subseq() )
        {
        case 0:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            scaleY = scaleX = bul_parent->scaleX;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_36C )
            {
                if ( field_190 == 5 || sub_48C6A0( 0, 4, 3) )
                {
                    active = false;
                    break;
                }
                sub_48C5F0( 0);
                sub_48C640( 2);
                v_inerc -= 0.5;
                if ( getlvl_height() < y && !field_190 )
                {
                    if ( get_elaps_frames() % 2 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = -scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = 2.0;

                        float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                        float yy = sin_deg(-tmp[0]) * 50.0 + y;

                        addbullet(chrt, NULL, 820, xx, yy, dir, 1, tmp, 3);
                    }
                    x += dir * h_inerc;
                    y += v_inerc;
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                    break;
                }
                //shake_camera(5.0); //HACK
                chrt->play_sfx( 10);
                if ( getlvl_height() >= y )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.35;
                    tmp[2] = 10.0;

                    addbullet(chrt, NULL, 820, x, getlvl_height(), dir, 1, tmp, 3);
                }
                for (int32_t i=0; i<8; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 8.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0;
                    addbullet( chrt,NULL, 820, xx, yy, dir, 1, tmp,3);
                }
                for (int32_t i=0; i<6; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 13.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 50.0 + y + 100.0;
                    addbullet( chrt,NULL, 820, xx, yy, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                scaleX += 0.08;
                if ( scaleX > 1.0 )
                    scaleX = 1.0;
                scaleY = scaleX;
                if ( chrt->get_seq() >= 540 && chrt->get_seq() <= 544 )
                {
                    CharFrameData *frm = chrt->get_pframe();
                    x = frm->extra1[4] * dir + chrt->x;
                    y = chrt->y - frm->extra1[5];
                    if ( chrt->get_subseq() == 2 && chrt->get_frame() == 1 )
                    {
                        field_36C = 1;
                        h_inerc = frm->extra2[1];
                        v_inerc = frm->extra2[2];
                        field_194 = 1;
                        break;
                    }
                    if ( get_elaps_frames() % 2 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = -scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = 2.0;

                        float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                        float yy = sin_deg(-tmp[0]) * 50.0 + y;

                        addbullet(chrt, NULL, 820, xx, yy, dir, 1, tmp, 3);
                    }
                    x += dir * h_inerc;
                    y += v_inerc;
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                    break;
                }
                for (int32_t i=0; i< 12; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 8.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0;

                    addbullet(chrt, NULL, 820, xx, yy, dir, 1, tmp, 3);
                }
                for (int32_t i=0; i< 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 13.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 50.0 + y + 100.0;

                    addbullet(chrt, NULL, 820, xx, yy, dir, 1, tmp, 3);
                }
                active = false;
            }
            break;
        case 6:
            v_inerc -= 0.35;
            if ( field_190 || ( getlvl_height() >= y && v_inerc < 0.0 ) )
            {
                chrt->play_sfx( 4);
                for (int32_t i=0; i< 3; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 3.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y;

                    addbullet(chrt, NULL, 820, xx, yy, dir, 1, tmp, 3);
                }
                for (int32_t i=0; i< 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 3.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 50.0 + y;

                    addbullet(chrt, NULL, 820, xx, yy, dir, 1, tmp, 3);
                }
                active = false;
            }
            else
            {
                x += dir * h_inerc;
                y += v_inerc;
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 )
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
            if ( get_elaps_frames() % 5 == 0 )
            {
                int32_t tm = -1;
                if ( chrt->skills_1[2] >= 1 )
                    tm = 1;
                if ( chrt->skills_1[2] >= 3 )
                    tm = 2;
                if ( chrt->skills_1[2] >= 4 )
                    tm = 3;
                if ( field_36C <= tm )
                {
                    field_36C++;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 25.0;
                    tmp[2] = 11.0;
                    float xx = (scene_rand_rngf(10) + 25.0 + field_36C * 70.0) * dir + x;
                    addbullet(chrt,NULL, 820, xx, y - 150.0, dir, 1, tmp, 3);
                    xx = x - (scene_rand_rngf(10) + 25.0 + field_36C * 70.0) * dir;
                    addbullet(chrt,NULL, 820, xx, y - 150.0, dir, 1, tmp, 3);
                }
            }
            scaleX += addition[1];
            addition[1] *= 0.9;
            scaleY = scaleX;
            if ( get_elaps_frames() >= 20 )
            {
                if ( c_A < 15 )
                {
                    active = false;
                    break;
                }
                c_A -= 15;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 11:
            y += addition[1];
            addition[1] *= 0.9;
            if ( getlvl_height() <= y )
                y = getlvl_height();
            if ( get_elaps_frames() < 15 )
                if ( field_190 != 8 && field_190 != 4 && field_190 != 6 )
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                    break;
                }
            field_194 = 0;
            scaleX -= 0.001;
            scaleY -= 0.005;

            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;

            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
        {
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        }
        break;
    case 821:
        switch ( get_subseq() )
        {
        case 0:
        {
            angZ = scene_rand_rngf(360);
            if ( sub_48C6A0( 0, 3, 2) )
            {
                active = false;
                break;
            }
            if ( get_elaps_frames() % 10 == 0 )
            {
                float tmp[3];
                tmp[0] = -scene_rand_rngf(360);
                tmp[1] = 0.0;
                tmp[2] = 6.0;

                float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                float yy = sin_deg(-tmp[0]) * 50.0 + y;

                addbullet(chrt, NULL, 821, xx, yy, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(50) * 0.01 + 0.75;
                tmp[2] = 2.0;

                addbullet(chrt, this, 821, x, y, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 15 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = 0.0;
                tmp[2] = 1.0;

                addbullet(chrt, this, 821, x, y, dir, 1, tmp, 3);
            }

            float yy = y - enemy->y - 100.0;
            yy *= yy;
            float xx = x - enemy->x;
            xx *= xx;
            if ( yy + xx >= 32400.0 || get_elaps_frames() < 20 )
            {
                if ( (int32_t)get_elaps_frames() >= 15 * (chrt->skills_1[6] + 7) )
                {
                    active = false;
                    break;
                }
                addition[1] *= 0.98;
                if ( addition[1] <= 1.0 )
                    addition[1] = 1.0;
                set_vec_speed(addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 15);
                int32_t tm = 12;
                if ( chrt->skills_1[6] >= 2 )
                    tm = 14;
                if ( chrt->skills_1[6] >= 3 )
                    tm = 15;
                if ( chrt->skills_1[6] >= 4 )
                    tm = 16;

                for(int32_t i=0; i < tm; i++)
                {
                    float tmp[3];
                    tmp[0] = i * (360.0 / (float)tm) + (180.0 / (float)tm);
                    tmp[1] = 25.0;
                    tmp[2] = 3.0;

                    addbullet( chrt,NULL, 821, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
        }
        break;
        case 1:
            if ( bul_parent )
            {
                x = bul_parent->h_inerc * dir + bul_parent->x;
                y = bul_parent->v_inerc + bul_parent->y;
            }
            scaleY = scaleX += 0.15;
            if ( c_A < 13 )
            {
                active = false;
                break;
            }
            c_A -= 13;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->h_inerc * dir + bul_parent->x;
            y = bul_parent->v_inerc + bul_parent->y;
            if ( !field_36C )
            {
                scaleX += 0.1;
                if ( scaleX > addition[1] )
                {
                    scaleX = addition[1];
                    field_36C = 1;
                }
                scaleY = scaleX;
            }
            else
            {
                scaleX += 0.005;
                scaleY *= 0.99;
                if ( c_A < 13 )
                {
                    active = false;
                    break;
                }
                c_A -= 13;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            if ( field_190 == 5 || sub_48C6A0( 0, 0, 2) )
            {
                active = false;
                break;
            }
            if ( !field_190 && (int32_t)get_elaps_frames() < 2 * chrt->skills_1[6] + 10 )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                for (int32_t i=0; i< 4; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 4.0;

                    addbullet(chrt, NULL, 821, x, y, dir, 1, tmp, 3);
                }
                active = false;
            }
            break;
        case 4:
        case 5:
            v_inerc -= 0.5;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 822:
        switch ( get_subseq() )
        {
        case 0:
        {
            if ( chrt->get_seq() != 550 && chrt->get_seq() != 551 )
            {
                active = false;
                break;
            }
            sub_48C5F0( 0);
            if ( field_190 == 1 && chrt->get_subseq() == 0 )
                chrt->field_7D0 = 1;

            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(3);
            tmp[2] = 2.0;
            addbullet( chrt, NULL, 822, x, y, dir, 1, tmp,3);
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(6);
            tmp[2] = 3.0;

            float xx = scene_rand_rngf(100) + x - 50.0;
            float yy = scene_rand_rngf(100) + y - 50.0;
            addbullet( chrt, NULL, 822, xx, yy, dir, 1, tmp,3);
            int32_t tm = 10;
            if ( chrt->skills_1[10] >= 2 )
                tm = 11;
            if ( chrt->skills_1[10] >= 3 )
                tm = 13;

            if ( (int32_t)get_elaps_frames() >= tm )
                active = false;
            else
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
        }
        break;
        case 1:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            scaleX += 0.1;
            if ( scaleX > 1.5 )
                scaleX = 1.5;
            scaleY = scaleX;
            if ( field_36C == 0)
            {
                enemy->x = x;
                enemy->y = y + 20.0;
                if ( getlvl_height() < y )
                {
                    v_inerc -= 0.5;
                    if ( getlvl_height() >= v_inerc + y )
                    {
                        y = getlvl_height();
                        v_inerc = 0.0;
                    }
                }
                if ( chrt->get_subseq() == 2 && chrt->get_frame() == 6 )
                {
                    CharFrameData *frm = chrt->get_pframe();
                    scene_add_effect(chrt, 4, frm->extra1[4] * chrt->dir + chrt->x, chrt->y - frm->extra1[5], dir, 1);
                    scene_play_sfx(3);
                    field_36C = 2;
                }

                if ( chrt->get_seq() != 550 && chrt->get_seq() != 551 )
                {
                    for (int32_t i=0; i<12; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(6) + 5.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 8.0;

                        float xx = x + 50.0 - scene_rand_rngf(100);
                        float yy = y + scene_rand_rngf(250);

                        addbullet(chrt, NULL, 822, xx, yy, dir, 1, tmp, 3);
                    }
                    for (int32_t i=0; i<6; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(4) + 3.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 8.0;

                        float xx = x + 30.0 - scene_rand_rngf(60);
                        float yy = y + scene_rand_rngf(200);

                        addbullet(chrt, NULL, 822, xx, yy, dir, 1, tmp, 3);
                    }
                    enemy->field_1A4 = 5.0;
                    enemy->field_1A8 = 12.5;
                    chrt->play_sfx( 10);
                    enemy->set_seq(71);
                    enemy->field_4BA = 6000;
                    active = false;
                }
                else
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                }
            }
            else
            {
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(3);
                    tmp[2] = 2.0;

                    addbullet(chrt, NULL, 822, x, y, dir, 1, tmp, 3);

                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(6);
                    tmp[2] = 3.0;

                    float xx = x - 50.0 + scene_rand_rngf(100);
                    float yy = y - 50.0 + scene_rand_rngf(100);

                    addbullet(chrt, NULL, 822, xx, yy, dir, 1, tmp, 3);
                }
                enemy->x = x;
                enemy->y = y + 20.0;
                h_inerc = -25.0;
                if ( getlvl_height() < y )
                {
                    v_inerc -= 0.5;
                    if ( getlvl_height() >= v_inerc + y )
                    {
                        y = getlvl_height();
                        v_inerc = 0.0;
                    }
                }
                if ( get_border_near() == 0 && getlvl_height() <= y )
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                    break;
                }
                else
                {
                    for (int32_t i=0; i<12; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(6) + 5.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 8.0;

                        float xx = x + 50.0 - scene_rand_rngf(100);
                        float yy = y + scene_rand_rngf(250);

                        addbullet(chrt, NULL, 822, xx, yy, dir, 1, tmp, 3);
                    }
                    for (int32_t i=0; i<6; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(4) + 3.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 8.0;

                        float xx = x + 30.0 - scene_rand_rngf(60);
                        float yy = y + scene_rand_rngf(200);

                        addbullet(chrt, NULL, 822, xx, yy, dir, 1, tmp, 3);
                    }
                    enemy->field_1A4 = -3.0;
                    enemy->field_1A8 = 17.5;
                    enemy->damage_limit = 100;
                    enemy->set_seq(77);
                    //shake_camera(8.0); //HACK
                    chrt->play_sfx( 10);
                    scene_add_effect(chrt, 4, x, y + 125.0, dir, 1);
                    if ( chrt->weather_id == WEATHER_HAIL )
                        sub_464110( (chrt->skills_1[10] * 0.1 + 1.0) * 1250.0, 750, 1, 1);
                    else
                        sub_464110( (chrt->skills_1[10] * 0.1 + 1.0) * 1000.0, 750, 1, 1);
                    active = false;
                }
            }
            break;
        case 6:
            v_inerc -= 0.35;
            if ( field_190 == 0 && (getlvl_height() < y || v_inerc >= 0.0) )
            {
                x += dir * h_inerc;
                y += v_inerc;
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                for(int32_t i=0; i<3; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 3.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y;

                    addbullet(chrt, NULL, 820, xx ,yy ,dir,1, tmp,3);
                }

                for(int32_t i=0; i<2; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 3.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * tmp[1] * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 50.0 + y;

                    addbullet(chrt, NULL, 820, xx ,yy ,dir,1, tmp,3);
                }
                active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 825:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_190 == 5 || sub_48C6A0( 0, 0, 5) )
            {
                active = false;
                break;
            }
            addition[1] *= 0.9;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;
                if ( scene_rand_rng(100) <= 50 )
                    tmp[2] = 2.0;

                float yy = scene_rand_rngf(100) + y - 50.0;
                float xx = scene_rand_rngf(100) + x - 50.0;

                addbullet(chrt, NULL, 825, xx, yy, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 2 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(50) * 0.1 + 5.0;
                tmp[2] = 4.0;
                addbullet( chrt, NULL, 825, x, y, dir, 1, tmp,3);
            }
            sub_48C5F0( 0);
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 || get_elaps_frames() > 13 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 2:
            if ( get_elaps_frames() < 40 )
            {
                scaleX += 0.2;
                if ( field_37C <= scaleX )
                    scaleX = field_37C;
                scaleY = scaleX;
            }
            else
            {
                v_inerc -= 0.3;
                angZ += field_378;
                if ( c_A < 16 )
                {
                    active = false;
                    break;
                }
                c_A -= 16;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            scaleY = scaleX *= 0.85;
            if ( c_A < 40 )
            {
                active = false;
                break;
            }
            c_A -= 40;
            if ( process() )
                active = false;
            break;
        case 4:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( process() )
                active = false;
            break;
        }
        break;
    case 826:
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0( 0, 3, 5) )
            {
                active = false;
                break;
            }
            if ( field_36C == 0)
            {
                if ( chrt->get_seq() < 505 || chrt->get_seq() > 508 )
                {
                    active = false;
                    break;
                }
                x = chrt->x;
                y = chrt->y + 300.0;
                scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                field_378 += 0.01;
                if ( chrt->get_subseq() == 2 )
                    field_36C = 1;

                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                set_vec_speed(addition[0], addition[1]);
                if ( getlvl_height() <= y )
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                }
                else
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 10.0;

                    addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);

                    tmp[2] = 4.0;
                    addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);

                    for(int32_t i=0; i<8; i++)
                    {
                        tmp[0] = scene_rand_rngf(30) + i * 45.0;
                        tmp[1] = 15.0;
                        tmp[2] = 2.0;

                        addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);
                    }
                    for(int32_t i=0; i<15; i++)
                    {
                        tmp[0] = scene_rand_rngf(180);
                        tmp[1] = scene_rand_rngf(15) + 5.0;
                        tmp[2] = 3.0;

                        addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);
                    }
                    active = false;
                }
            }
            break;
        case 1:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            scaleY = scaleX += 0.2;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( scaleX * 100.0 < field_378 )
                field_194 = 0;
            else
            {
                field_378 += 20.0;
                x += cos_deg(-addition[0]) * 20.0 * dir;
                y += sin_deg(-addition[0]) * 20.0;
            }
            if ( addition[1] <= get_elaps_frames() )
            {
                scaleY = scaleX *= 0.99;
                if ( c_A < 7 )
                {
                    active = false;
                    break;
                }
                c_A -= 7;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( field_36C == 0)
            {
                if ( scaleX * 115.0 < field_378 )
                {
                    if ( field_370 == 0)
                    {
                        field_194 = 1;
                        field_370 = 1;
                    }
                }
                else
                {
                    field_378 += 25.0;
                    x += cos_deg(-addition[0]) * 25.0 * dir;
                    y += sin_deg(-addition[0]) * 25.0;
                }
                if ( sub_48C6A0( 0, 1, 2) )
                {
                    active = false;
                    break;
                }
                if ( chrt->get_seq() < 565 || chrt->get_seq() > 569 )
                {
                    for (int32_t i=0; i<8; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 8.0;

                        float yy = sin_deg(-addition[0]) * i * 20.0 + y;
                        float xx = cos_deg(-addition[0]) * i * 20.0 * dir + x;
                        addbullet(chrt, NULL, 826, xx, yy, dir, 1, tmp, 3);
                    }
                }
                else if ( chrt->get_subseq() == 2 && chrt->get_frame() == 4 )
                {
                    field_36C = 1;
                    field_194 = 1;
                    field_190 = 0;
                    addition[1] = scene_rand_rngf(25) + 35.0;
                    break;
                }
            }
            if ( field_36C == 1 )
            {
                set_vec_speed(addition[0], addition[1]);
                sub_48C5F0( 0);
                if ( get_elaps_frames() % 5 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = 3.0;
                    addbullet( chrt, NULL, 826, x, y, dir, 1, tmp,3);
                }
                if ( field_190 != 0 && field_190 != 1 )
                {
                    for (int32_t i=0; i<8; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 8.0;

                        float yy = sin_deg(-addition[0]) * i * 20.0 + y;
                        float xx = cos_deg(-addition[0]) * i * 20.0 * dir + x;
                        addbullet(chrt, NULL, 826, xx, yy, dir, 1, tmp, 3);
                    }
                    active = false;
                    break;
                }
                if ( y >= 1480.0 )
                {
                    active = false;
                    break;
                }
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
            if ( sub_48C6A0( 0, 0, 0)
                    || enemy->health <= 0
                    || get_elaps_frames() >= 300
                    || ((chrt->get_seq() == 505 || chrt->get_seq() == 506) && chrt->get_subseq() == 0) )
            {
                active = false;
                break;
            }
            if ( get_elaps_frames() % 6 == 0 )
            {
                float tmp[3];
                tmp[0] = get_elaps_frames() * 4.0;
                tmp[1] = 3.0;
                tmp[2] = 2.0;
                if ( sin_deg(4.0 * get_elaps_frames()) > 0.0 )
                {
                    float xx = cos_deg(-tmp[0]) * 150.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 25.0 + y;
                    addbullet(chrt, NULL, 811, xx, yy, dir, -1, tmp, 3);

                    tmp[0] += 180.0;
                    xx = cos_deg(-tmp[0]) * 150.0 * dir + x;
                    yy = sin_deg(-tmp[0]) * 25.0 + y;
                    addbullet(chrt, NULL, 811, xx, yy, dir, -1, tmp, 3);
                }
                else
                {
                    float xx = cos_deg(-tmp[0]) * 150.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 25.0 + y;
                    addbullet(chrt, NULL, 811, xx, yy, dir, 1, tmp, 3);

                    tmp[0] += 180.0;
                    xx = cos_deg(-tmp[0]) * 150.0 * dir + x;
                    yy = sin_deg(-tmp[0]) * 25.0 + y;
                    addbullet(chrt, NULL, 811, xx, yy, dir, 1, tmp, 3);
                }
            }

            if ( fabs(enemy->x - x) >= 150.0 || fabs(enemy->y - y) >= 100.0 )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                float tmp[3];
                tmp[1] = 30.0;
                tmp[2] = 5.0;
                for (int32_t i=0; i<6; i++)
                {
                    tmp[0] = -85.0 - scene_rand_rngf(10);

                    float tm = scene_rand_rngf(40) - 20.0;
                    int32_t ord = 1 - 2 * (tm > 0.0);

                    float yy = tm + y - 120.0;
                    float xx = scene_rand_rngf(100) + x - 175.0 + i * 50.0;

                    addbullet(chrt, NULL, 811, xx, yy, dir, ord, tmp, 3);
                }
                tmp[2] = 6.0;
                for (int32_t i=0; i<6; i++)
                {
                    tmp[0] = -85.0 - scene_rand_rngf(10);

                    float tm = scene_rand_rngf(20) - 10.0;
                    int32_t ord = 1 - 2 * (tm > 0.0);

                    float yy = tm + y - 240.0;
                    float xx = scene_rand_rngf(60) + x - 130.0 + i * 100.0;

                    addbullet(chrt, NULL, 811, xx, yy, dir, ord, tmp, 3);
                }
                tmp[2] = 11.0;
                addbullet( chrt, NULL, 811, x, y, dir, 1, tmp,3);
                active = false;
            }
            break;
        case 11:
            if ( get_elaps_frames() < 10 )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 827:
        switch ( get_subseq() )
        {
        case 0:
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
            {
                if ( process() )
                    active = false;
                if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 1 )
                {
                    for (int32_t i=0; i< 16; i++)
                    {
                        float tmp[3];
                        tmp[0] = -scene_rand_rngf(160) - 10.0;
                        tmp[1] = scene_rand_rngf(4) + 10.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 1.0;

                        addbullet(chrt, NULL, 858, (cos_deg(-tmp[0])*135.0 + 200.0)* dir + x, y, dir, 1, tmp, 3 );
                    }

                    float tmp[3];
                    tmp[2] = 4.0;

                    for (int32_t i=0; i< 8; i++)
                    {
                        tmp[0] = i * 45.0 + 22.5;
                        tmp[1] = scene_rand_rngf(4) + 16.0;

                        int32_t ord = 1 - 2 * (-sin_deg(-tmp[0]) >= 0.0);
                        float xx = (cos_deg(-tmp[0]) * 80.0 + 200.0) * dir + x;
                        float yy = sin_deg(-tmp[0]) * 15.0 + y;

                        addbullet(chrt, NULL, 858, xx, yy, dir, ord, tmp, 3 );
                    }

                    tmp[2] = 5.0;

                    addbullet( chrt, NULL, 858, (200 * dir) + x, y, dir, -1, tmp,3);
                }
            }
            break;
        case 1:
        case 2:
            scaleY = scaleX -= 0.001;
            angZ += field_378;
            v_inerc -= 0.5;
            if ( c_A < 4 )
            {
                active = false;
                break;
            }
            c_A -= 4;
            if ( x > 1380.0 || x < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 3:
            scaleY = scaleX *= 0.995;
            angZ += field_378;
            field_378 *= 0.99;
            field_37C -= 0.1;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            if ( addition[1] == 1 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            v_inerc += field_37C;
            x += dir * h_inerc;
            y += v_inerc;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 4:
            scaleY = scaleX += 0.001;
            angZ += field_378;
            field_378 *= 0.95;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            if ( addition[1] == 1.0 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            x += dir * h_inerc;
            y += v_inerc * 0.15;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 5:
            scaleY = scaleX += 0.3;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 6:
            scaleY = scaleX *= 0.9;
            if ( c_A < 30 )
            {
                active = false;
                break;
            }
            c_A -= 30;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 7:
        case 8:
        case 10:
        case 11:
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || (chrt->get_subseq() > 1 && chrt->get_subseq() != 3) )
            {
                active = false;
                break;
            }
            x = chrt->x;
            y = chrt->y;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 9:
        case 12:
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 )
            {
                active = false;
                break;
            }
            x = chrt->x;
            y = chrt->y;
            if ( chrt->get_frame() >= 5 )
                active = false;
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 13:
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
            {
                if ( process() )
                    active = false;

                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 13 )
                    active = false;
            }
            break;
        default:
            if ( chrt->get_seq() < 570 || chrt->get_seq() > 574 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        }
        break;
    case 848:
        switch ( get_subseq() )
        {
        case 0:
            x = chrt->x;
            y = chrt->y;
            if ( chrt->get_seq() == 322 || chrt->get_seq() == 418 || chrt->get_seq() == 696 )
            {
                if ( chrt->hit_stop == 0 )
                    if ( process() )
                        active = false;
            }
            else
                active = false;
            break;
        case 1:
            if ( chrt->get_seq() != 408 )
            {
                active = false;
                break;
            }
            x = (cos_deg(-addition[0]) * field_378 + 58.0) * dir + chrt->x;
            y = sin_deg(-addition[0]) * field_378 + chrt->y + 107.0;
            if ( chrt->hit_stop <= 0 )
            {
                field_36C++;
                field_378 += addition[1];
                addition[1] *= 0.9;
                scaleY *= 0.9;
                if ( get_elaps_frames() % 6 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(6);
                    tmp[2] = 3.0;
                    float xx = scene_rand_rngf(40) + y - 20.0;
                    float yy = scene_rand_rngf(40) + x - 20.0;
                    addbullet(chrt, NULL, 848, xx, yy, dir, 1, tmp, 3);
                }
                if ( field_36C < 10 )
                {
                    if ( process() )
                        active = false;
                    if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
                        active = false;
                }
                else
                    active = false;
            }
            break;
        case 2:
            scaleY = scaleX *= 0.8;
            if ( scaleX <= 0.5 )
            {
                if ( c_A < 40 )
                {
                    active = false;
                    break;
                }
                c_A -= 40;
            }
            if ( chrt->hit_stop == 0 )
            {
                if ( process() )
                    active = false;
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
                    active = false;
            }
            break;
        case 3:
            angZ += field_378;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.9;
            field_37C -= 0.1;
            v_inerc += field_37C;
            scaleY = scaleX *= 0.97;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            if ( chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 4:
            if ( (chrt->get_seq() != 301 && chrt->get_seq() != 321) || (chrt->get_subseq() == 0 && chrt->get_frame() ==0 ))
            {
                active = false;
                break;
            }
            if ( chrt->get_frame() > 9 )
            {
                scaleY = scaleX *= 0.98;
            }
            else
            {
                dir = chrt->dir;
                CharFrameData *frm = chrt->get_pframe();
                x = (frm->extra1[4] * chrt->dir) + chrt->x;
                y = chrt->y - frm->extra1[5];
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(8) + 8.0;
                    tmp[2] = 3.0;
                    addbullet( chrt, NULL, 848, x, y, dir, 1, tmp,3);

                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(4) + 4.0;
                    tmp[2] = 5.0;
                    addbullet( chrt, NULL, 848, x, y, dir, 1, tmp,3);
                }
            }
            if ( process() )
                active = false;
            break;
        case 5:
            angZ += field_378;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.9;
            field_37C -= 0.1;
            v_inerc += field_37C;
            scaleY = scaleX *= 0.97;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( chrt->hit_stop == 0 )
                if ( process() )
                    active = false;
            break;
        case 6:
            scaleY = scaleX *= 0.9;
            if ( get_elaps_frames() < 4 )
            {
                if ( process() )
                    active = false;
            }
            else
                active = false;
            break;
        case 7:
            if ( (chrt->get_seq() != 304 && chrt->get_seq() != 418) || (chrt->get_frame() == 0 && chrt->get_subseq() == 0) )
            {
                active = false;
                break;
            }
            if ( chrt->get_seq() == 304 )
            {
                if ( chrt->get_frame() <= 11 )
                {
                    dir = chrt->dir;
                    CharFrameData *frm = chrt->get_pframe();
                    x = (frm->extra1[4] * chrt->dir) + chrt->x;
                    y = chrt->y - frm->extra1[5];
                    if ( get_elaps_frames() % 2 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(3) + 2.0;
                        tmp[2] = 5.0;
                        addbullet( chrt, NULL, 848, x, y, dir, 1, tmp,3);
                    }
                }

                if ( chrt->get_frame() < 9 )
                {
                    scaleX += 0.2;
                    if ( scaleX > 1.0 )
                        scaleX = 1.0;
                    scaleY = scaleX;
                }
                else
                {
                    scaleY = scaleX *= 0.98;
                    if ( c_A < 10 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 10;
                }
            }
            if ( chrt->get_seq() == 418 )
            {
                if ( chrt->get_frame() <= 7 )
                {
                    dir = chrt->dir;
                    CharFrameData *frm = chrt->get_pframe();
                    x = (frm->extra1[4] * chrt->dir) + chrt->x;
                    y = chrt->y - frm->extra1[5];
                    if ( get_elaps_frames() % 2 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(3) + 2.0;
                        tmp[2] = 5.0;
                        addbullet( chrt, NULL, 848, x, y, dir, 1, tmp,3);
                    }
                }
                if ( chrt->get_frame() < 5 )
                {
                    scaleX += 0.2;
                    if ( scaleX <= 1.0 )
                        scaleY = scaleX;
                    else
                        scaleY = scaleX = 1.0;
                }
                else
                {
                    scaleY = scaleX *= 0.98;
                    if ( c_A < 10 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 10;
                }
            }
            if (chrt->hit_stop == 0)
                if ( process() )
                    active = false;
            break;
        default:
            if (chrt->hit_stop == 0)
                if ( process() )
                    active = false;
            break;
        }
        break;
    case 849:
        if ( get_subseq() == 0 )
        {
            x = (109 * dir) + chrt->x;
            y = chrt->y + 84.0;
            if ( chrt->get_seq() != 500 || chrt->get_subseq() != 1 )
            {
                active = false;
                break;
            }
        }
        if ( get_subseq() == 1 )
        {
            x = (61 * dir) + chrt->x;
            y = chrt->y + 232.0;
            if ( (chrt->get_seq() != 520 && chrt->get_seq() != 521) || chrt->get_subseq() != 1 )
            {
                active = false;
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            x = (61 * dir) + chrt->x;
            y = chrt->y + 232.0;
            if ( chrt->get_seq() != 606 || chrt->get_subseq() != 1 )
            {
                active = false;
                break;
            }
        }
        if ( get_subseq() == 3 || get_subseq() == 4 || get_subseq() == 5 )
        {
            field_18C = 5;
            if ( field_190 == 6 )
            {
                field_194++;
                field_190 = 0;
            }
            if ( field_190 )
            {
                field_36C++;
                if ( field_36C > 5 )
                {
                    field_190 = 0;
                    field_36C = 0;
                }
            }
            bul_follow_char(this, 38, 54);

            if ( ( chrt->get_seq() != 525 && chrt->get_seq() != 526 )|| chrt->get_subseq() != 1 )
            {
                active = false;
                break;
            }
        }
        if ( chrt->hit_stop == 0 )
            if ( process() )
                active = false;
        break;
    case 850:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C == 0 )
            {
                if ( (chrt->get_seq() != 600 && chrt->get_seq() != 650) || chrt->get_subseq() > 1 )
                {
                    field_36C = 1;
                }
                else
                {
                    CharFrameData *frm = chrt->get_pframe();
                    x = (frm->extra1[4] * chrt->dir) + chrt->x;
                    y = chrt->y - frm->extra1[5];
                    scaleY = scaleX = sin_deg(get_elaps_frames()*2) * 0.25 + field_378;
                    field_378 += 0.01;
                    if ( get_elaps_frames() % 10 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = 1.0;

                        float xx = x + 50.0 - scene_rand_rngf(100);
                        float yy = y + 50.0 - scene_rand_rngf(100);
                        addbullet( chrt, NULL, 850, xx, yy, dir, 1, tmp, 3);
                    }
                }
            }
            else
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 || sub_48C6A0( 0, 0, 4) )
            {
                active = false;
                break;
            }
            if ( field_190 == 0)
            {
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                for(int32_t i=0; i<4; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 850, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 851:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C )
            {
                set_vec_speed(addition[0], addition[1]);
                if ( getlvl_height() <= y )
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                }
                else
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 10.0;

                    addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);

                    tmp[2] = 4.0;
                    addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);

                    for (int32_t i=0; i<8.0; i++)
                    {
                        tmp[0] = scene_rand_rngf(30) + i * 45.0;
                        tmp[1] = 15.0;
                        tmp[2] = 2.0;

                        addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);
                    }

                    for (int32_t i=0; i<15.0; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(180);
                        tmp[1] = scene_rand_rngf(15) + 5.0;
                        tmp[2] = 3.0;

                        addbullet(chrt, NULL, 811, x, getlvl_height(), dir, 1, tmp, 3);
                    }
                    active = false;
                }
            }
            else
            {
                if ( chrt->get_seq() < 505 || chrt->get_seq() > 508 )
                {
                    active = false;
                    break;
                }
                x = chrt->x;
                y = chrt->y + 300.0;
                scaleX = scaleY = sin_deg(get_elaps_frames()*2) * 0.25 + field_378;
                field_378 += 0.01;
                if ( chrt->get_subseq() == 2 )
                    field_36C = 1;

                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 1:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            scaleY = scaleX += 0.2;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( scaleX * 100.0 < field_378 )
            {
                field_194 = 0;
            }
            else
            {
                field_378 += 20.0;
                x += cos_deg(-addition[0]) * 20.0 * dir;
                y += sin_deg(-addition[0]) * 20.0;
            }
            if ( addition[1] > get_elaps_frames() )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                for (int32_t i=0; i<8; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(10) + 10.0;
                    tmp[2] = (scene_rand_rng(100) < 50) + 8.0;

                    float yy = scene_rand_rngf(100) + y;
                    float xx = x + 20.0 - scene_rand_rngf(40);
                    addbullet(chrt, NULL, 851, xx, yy, dir, 1, tmp, 3);
                }
                active = false;
            }
            break;
        case 6:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( scaleX * 230.0 < field_378 )
            {
                field_194 = 0;
            }
            else
            {
                field_378 += 50.0;
                x += cos_deg(-addition[0]) * 50.0 * dir;
                y += sin_deg(-addition[0]) * 50.0;
            }
            if ( addition[1] > get_elaps_frames() )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                for (int32_t i=0; i<8; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(10) + 10.0;
                    tmp[2] = (scene_rand_rng(100) < 50) + 8.0;

                    float yy = scene_rand_rngf(150) + y;
                    float xx = x + 20.0 - scene_rand_rngf(40);
                    addbullet(chrt, NULL, 851, xx, yy, dir, 1, tmp, 3);
                }
                active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.5;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
            x += (30 * dir);
            y = getlvl_height();
            if ( x >= 1380.0 || x < -100.0 )
            {
                active = false;
                break;
            }
            if ( get_elaps_frames() % 4 == 0 )
            {
                float tmp[3];
                tmp[0] = get_elaps_frames() * 4.0;
                tmp[1] = 3.0;
                tmp[2] = 2.0;
                if ( sin_deg(4.0 * get_elaps_frames() > 0.0 ) )
                {
                    float yy = sin_deg(-tmp[0]) * 25.0 + y;
                    float xx = cos_deg(-tmp[0]) * 150.0 * dir + x;

                    addbullet(chrt, NULL, 851, xx, yy, dir, -1, tmp, 3);

                    tmp[0] += 180.0;
                    yy = sin_deg(-tmp[0]) * 25.0 + y;
                    xx = cos_deg(-tmp[0]) * 150.0 * dir + x;
                    addbullet(chrt, NULL, 851, xx, yy, dir, -1, tmp, 3);
                }
                else
                {
                    float yy = sin_deg(-tmp[0]) * 25.0 + y;
                    float xx = cos_deg(-tmp[0]) * 150.0 * dir + x;

                    addbullet(chrt, NULL, 851, xx, yy, dir, 1, tmp, 3);

                    tmp[0] += 180.0;
                    yy = sin_deg(-tmp[0]) * 25.0 + y;
                    xx = cos_deg(-tmp[0]) * 150.0 * dir + x;
                    addbullet(chrt, NULL, 851, xx, yy, dir, 1, tmp, 3);
                }
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = -85.0 - scene_rand_rngf(10);
                tmp[1] = 30.0;
                tmp[2] = 5.0;

                float tm = scene_rand_rngf(40) - 20.0;
                int32_t ord = 1 - 2 * (tm > 0.0);

                float yy = tm + y - 120.0;
                float xx = scene_rand_rngf(150) + x - 75.0;

                addbullet(chrt,NULL, 851, xx, yy, dir, ord, tmp, 3);

                tmp[0] = -85.0 - scene_rand_rngf(10);
                tmp[2] = 6.0;

                tm = scene_rand_rngf(20) - 10.0;
                ord = 1 - 2 * (tm > 0.0);

                yy = tm + y - 240.0;
                xx = scene_rand_rngf(100) + x - 50.0;

                addbullet(chrt,NULL, 851, xx, yy, dir, ord, tmp, 3);

                tmp[1] = scene_rand_rngf(5) * 0.1 + 1.0;
                tmp[2] = scene_rand_rngf(4) + 11.0;

                yy = scene_rand_rngf(10) - 5.0 + y;
                xx = scene_rand_rngf(100) + x - 50.0;

                addbullet(chrt,NULL, 851, xx, yy, dir, 1, tmp, 3);
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            if ( get_elaps_frames() < 60 )
            {
                scaleX += 0.1;
                if ( scaleX > addition[1] )
                    scaleX = addition[1];
                scaleY = scaleX;
            }
            else
            {
                scaleY = scaleX -= 0.005;
                if ( c_A <= 6 )
                {
                    active = false;
                    break;
                }
                c_A -= 6;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 852:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C == 0 )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    scaleY = scaleX = sin_deg(get_elaps_frames()) * 0.3 + 1.0;
                }
                else
                {
                    field_36C = 1;
                }
            }
            else
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() % 6 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(3) + 1.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 852, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 12 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 8.0;
                tmp[2] = (scene_rand_rng(10) > 4) + 10.0;
                addbullet( chrt, NULL, 852, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 15 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 7.0;
                addbullet( chrt, this, 852, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 3 == 0 && field_378 <= 56.0 && get_elaps_frames() >= 15 )
            {
                float tmp[3];
                tmp[0] = field_378 * 20.0;
                tmp[1] = 10.0;
                tmp[2] = 5.0;

                float yy = sin_deg(-tmp[0]) * 20.0 + y;
                float xx = cos_deg(-tmp[0]) * 80.0 * dir + x;

                addbullet(chrt,NULL, 852, xx, yy, dir, 1, tmp, 3 );

                tmp[2] = 4.0;
                yy = sin_deg(-tmp[0]) * 20.0 + y;
                xx = cos_deg(-tmp[0]) * 80.0 * dir + x;
                addbullet(chrt,NULL, 852, xx, yy, dir, 1, tmp, 3 );

                field_378 += 1.0;
            }
            if ( get_elaps_frames() == 180 )
            {
                chrt->play_sfx( 15);
                for(int32_t i=0; i<18; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 20.0;
                    tmp[1] = 10.0;
                    tmp[2] = 5.0;

                    float yy = sin_deg(-tmp[0]) * 20.0 + y;
                    float xx = cos_deg(-tmp[0]) * 80.0 * dir + x;

                    addbullet(chrt,NULL, 852, xx, yy, dir, 1, tmp, 3 );

                    tmp[2] = 4.0;
                    yy = sin_deg(-tmp[0]) * 20.0 + y;
                    xx = cos_deg(-tmp[0]) * 80.0 * dir + x;
                    addbullet(chrt,NULL, 852, xx, yy, dir, 1, tmp, 3 );
                }
                active = false;
            }
            else
            {
                if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
        case 6:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( field_190 )
            {
                chrt->play_sfx( 1);
                for(int32_t i=0; i<3; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 852, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( get_elaps_frames() >= 30 )
                {
                    field_194 = 0;
                    scaleY = scaleX *= 0.98;
                    if ( c_A <= 15 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 15;
                }
                if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 7:
            scaleY = scaleX += 0.05;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
        case 11:
            v_inerc -= 0.2;
            angZ += field_378;
            field_378 *= 0.98;
            if ( c_A <= 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 854:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C )
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            else
            {
                if ( chrt->get_seq() == 604 || chrt->get_seq() == 654 )
                {
                    if ( chrt->get_subseq() >= 1 )
                    {
                        field_360 = 0;
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = 25.0;
                        tmp[2] = 4.0;
                        addbullet( chrt, NULL, 854, x, y, dir, 1, tmp,3);
                        if ( get_elaps_frames() % 10 == 0 )
                        {
                            tmp[0] = 0.0;
                            tmp[1] = 0.0;
                            tmp[2] = 1.0;
                            addbullet( chrt, NULL, 854, x, y, dir, 1, tmp,3);
                        }
                        if ( get_elaps_frames() % 6 == 0 )
                        {
                            chrt->play_sfx( 102);
                            tmp[0] = scene_rand_rngf(360);
                            tmp[1] = scene_rand_rngf(4) + 4.0;
                            tmp[2] = 2.0;
                            addbullet( chrt, NULL, 854, x, y, dir, 1, tmp,3);
                        }
                        if ( get_elaps_frames() % 12 == 0 )
                        {
                            tmp[0] = scene_rand_rngf(360);
                            tmp[1] = scene_rand_rngf(10) + 8.0;
                            tmp[2] = 3.0;
                            addbullet( chrt, NULL, 854, x, y, dir, 1, tmp,3);
                        }
                    }
                    if ( chrt->get_subseq() < 2 || chrt->get_frame() < 9 )
                    {
                        CharFrameData *frm = chrt->get_pframe();
                        x = (frm->extra1[4] * dir) + chrt->x;
                        y = chrt->y - frm->extra1[5];
                        scaleX += 0.1;
                        if ( scaleX > 1.0 )
                            scaleX = 1.0;
                        scaleY = scaleX;
                    }
                    else
                    {
                        field_36C = 1;
                    }
                }
                else
                    field_36C = 1;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
            scaleY = scaleX += 0.3;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.98;
            if ( addition[1] <= 3.0 )
                addition[1] = 3.0;
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( field_190 == 4 || field_190 == 6 )
            {
                angX = scene_rand_rngf(60) - 30.0;
                angY = scene_rand_rngf(60) - 30.0;
                set_subseq(7);
                break;
            }
            if ( x > 1380.0 || x < -100.0 || y < -300.0 || y > 800.0 )
            {
                active = false;
                break;
            }

            if ( chrt->get_seq() != 604 && chrt->get_seq() != 654 )
            {
                field_36C = 1;
            }
            else  if ( field_36C == 0 && chrt->get_subseq() == 2 && chrt->field_7D0 == 1 )
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                addition[1] = 0.0;
                set_subseq( 5);
                break;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( get_elaps_frames() < 90 )
            {
                if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                set_subseq(6);
                addition[0] = scene_rand_rngf(360);
                field_190 = 0;
                field_194 = 1;
            }
            break;
        case 6:
            set_vec_speed(addition[0], addition[1]);
            addition[1] += 0.1;

            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( field_190 != 0 )
            {
                angX = scene_rand_rngf(60) - 30.0;
                angY = scene_rand_rngf(60) - 30.0;
                set_subseq(7);
                break;
            }
            if ( x > 1380.0 || x < -100.0 || y < -300.0 || y > 800.0 )
            {
                active = false;
                break;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 7:
            scaleY = scaleX += field_378;
            field_378 *= 0.92;
            h_inerc = 0.0;
            v_inerc = 0.0;
            if ( get_elaps_frames() >= 15 )
            {
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
        case 11:
            v_inerc -= 0.2;
            angZ += field_378;
            field_378 *= 0.98;
            if ( c_A <= 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 12:
            scaleY = scaleX *= 0.99;
            if ( get_elaps_frames() >= 5 )
            {
                field_194 = 0;
                if ( c_A <= 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 13:
            scaleY = scaleX += 0.6;

            for (int32_t i=0; i<3; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = 0.0;
                tmp[2] = (scene_rand_rngf(10) > 5) + 8.0;
                float tm = scaleX * 60.0 - scene_rand_rngf(50);
                float xx = cos_deg(-tmp[0]) * tm * dir + x;
                float yy = sin_deg(-tmp[0]) * tm + y;

                addbullet(chrt, NULL, 854, xx, yy, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() >= 20 )
            {
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 14:
            scaleY = scaleX += addition[1];
            addition[1] *= 0.92;
            if ( get_elaps_frames() >= 10 )
            {
                if ( c_A <= 4 )
                {
                    active = false;
                    break;
                }
                c_A -= 4;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 15:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            if ( bul_parent->get_subseq() != 4 )
            {
                active = false;
                break;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 855:
        switch ( get_subseq() )
        {
        case 0:
            if ( !field_36C )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    scaleY = scaleX = sin_deg(get_elaps_frames()) * 0.3 + 1.0;
                }
                else
                {
                    field_36C = 1;
                }
            }
            else
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() % 6 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(3) + 1.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 855, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 12 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 8.0;
                tmp[2] = (scene_rand_rng(10) > 4) + 10.0;
                addbullet( chrt, NULL, 855, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 15 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 7.0;
                addbullet( chrt, this, 852, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 3 == 0 )
                if ( field_378 <= 36.0 )
                {
                    float tmp[3];
                    tmp[0] = field_378 * 20.0;
                    tmp[1] = 10.0;
                    tmp[2] = 5.0;

                    float xx = cos_deg(-tmp[0]) * 80.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 20.0 + y;

                    addbullet( chrt, NULL, 855, xx, yy, dir, 1, tmp,3);

                    tmp[2] = 4.0;

                    addbullet( chrt, NULL, 855, xx, yy, dir, 1, tmp,3);
                    field_378 += 1.0;
                }
            if ( get_elaps_frames() == 120 )
            {
                for(int32_t i=0; i<18; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 20.0;
                    tmp[1] = 10.0;
                    tmp[2] = 5.0;

                    float xx = cos_deg(-tmp[0]) * 80.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 20.0 + y;

                    addbullet( chrt, NULL, 855, xx, yy, dir, 1, tmp,3);

                    tmp[2] = 4.0;
                    addbullet( chrt, NULL, 855, xx, yy, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
        case 6:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( field_190 )
            {
                for(int32_t i=0; i<3; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 855, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( get_elaps_frames() >= 12 )
                {
                    field_194 = 0;
                    scaleY = scaleX *= 0.98;
                    if ( c_A <= 15 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 15;
                }
                if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 7:
            scaleY = scaleX += 0.05;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 )
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
        case 11:
            v_inerc -= 0.2;
            angZ += field_378;
            field_378 *= 0.98;
            if ( c_A <= 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 856:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C == 0 )
            {
                x = chrt->x;
                y = chrt->y + 115.0;
                if ( chrt->get_seq() == 606      && chrt->get_subseq() != 0
                        && (chrt->get_subseq() != 4 || chrt->get_elaps_frames() < 120) )
                {
                    scaleX += 0.1;
                    if ( scaleX >= 10.0 )
                        scaleX = 10.0;
                    scaleY = scaleX * 0.3;
                    set_custom_box((-80.0 * scaleX), (scaleY * 80.0), (scaleX * 80.0), (scaleY * -80.0), 0, 0,0);
                    sub_48C5F0( 0);
                    sub_48C640( 0);
                    if ( field_190 )
                    {
                        field_36E++;
                        if ( field_36E >= 8 )
                        {
                            field_36E = 0;
                            field_190 = 0;
                            field_194 = 1;
                        }
                    }
                    if ( get_elaps_frames() % 2 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(75) + 25.0;
                        tmp[2] = 1.0;
                        addbullet( chrt, this, 856, x, y, dir, 1 - 2 *(sin_deg(tmp[0])>=0), tmp,3);
                    }
                    if ( get_elaps_frames() % 18 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = 4.0;

                        float xx = (scene_rand_rngf(200) - 100.0) * scaleX + x;
                        float yy = (scene_rand_rngf(200) - 100.0) * scaleY + x;
                        addbullet( chrt, this, 856, xx, yy, dir, 1 - 2 *(sin_deg(tmp[0])>=0), tmp,3);
                    }

                    if ( get_elaps_frames() % 12 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(75) + 25.0;
                        tmp[2] = (scene_rand_rng(100) >= 50) + 10.0;

                        addbullet( chrt, this, 856, x, y, dir, 1 - 2 *(sin_deg(tmp[0])>=0), tmp,3);
                    }
                    if ( get_elaps_frames() % 8 == 0 )
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(50) + 50.0;
                        tmp[2] = 7.0;

                        addbullet( chrt, this, 856, x, y, dir, 1 - 2 *(scene_rand_rng(100)>=50), tmp,3);
                    }
                }
                else
                {
                    field_36C = 1;
                }
            }
            else
            {
                scaleX *= 1.005;
                scaleY *= 1.005;
                if ( c_A <= 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            addition[0] += field_378;
            x = cos_deg(-addition[0]) * bul_parent->scaleX * addition[1] * dir + bul_parent->x;
            y = sin_deg(-addition[0]) * bul_parent->scaleY * addition[1] + bul_parent->y;
            order = 1 - 2 * (sin_deg(addition[0]) >= 0.0);
            scaleX = (1.0 - sin_deg(-addition[0]) * 0.3) * field_37C * (fabs(sin_deg(-addition[0])) + 1.0);
            scaleY = (1.0 - sin_deg(-addition[0]) * 0.3) * field_37C;
            field_37C *= 0.95;
            if ( c_A < 9 )
            {
                active = false;
                break;
            }
            c_A -= 9;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            scaleY = scaleX *= 0.8;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            if ( field_190 )
            {
                for (int32_t i=0; i<3; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 852, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( get_elaps_frames() >= 30 )
                {
                    field_194 = 0;
                    scaleY = scaleX *= 0.98;
                    if ( c_A <= 15 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 15;
                }
                if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            break;
        case 6:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 7:
            angZ += 12.0;
            scaleY = scaleX += 0.01;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 )
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
        case 11:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            angZ += field_380;
            addition[0] += field_378;
            x = cos_deg(-addition[0]) * bul_parent->scaleX * addition[1] * dir + bul_parent->x;
            y = sin_deg(-addition[0]) * bul_parent->scaleY * addition[1] + bul_parent->y;
            order = 1 - 2 * (sin_deg(addition[0]) >= 0.0);

            field_37C *= 0.999;
            if ( c_A < 9 )
            {
                active = false;
                break;
            }
            c_A -= 9;
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1580.0 || x < -300.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 857:
        switch ( get_subseq() )
        {
        case 0:
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
            {
                if ( process() )
                    active = false;
                if (get_frame_time() == 0 && get_frame() == 1 )
                {
                    for (int32_t i=0; i< 16; i++)
                    {
                        float tmp[3];
                        tmp[0] = -scene_rand_rngf(160) - 10.0;
                        tmp[1] = scene_rand_rngf(4) + 10.0;
                        tmp[2] = (scene_rand_rng(100) > 50) + 1.0;

                        addbullet(chrt, NULL, 858, (cos_deg(-tmp[0])*135.0 + 200.0)* dir + x, y, dir, 1, tmp, 3 );
                    }
                    float tmp[3];
                    tmp[2] = 4.0;

                    for (int32_t i=0; i< 8; i++)
                    {
                        tmp[0] = i * 45.0 + 22.5;
                        tmp[1] = scene_rand_rngf(4) + 16.0;

                        int32_t ord = 1 - 2 * (-sin_deg(-tmp[0]) >= 0.0);
                        float xx = (cos_deg(-tmp[0]) * 80.0 + 200.0) * dir + x;
                        float yy = sin_deg(-tmp[0]) * 15.0 + y;

                        addbullet(chrt, NULL, 858, xx, yy, dir, ord, tmp, 3 );
                    }

                    tmp[2] = 5.0;

                    addbullet( chrt, NULL, 858, (200 * dir) + x, y, dir, -1, tmp,3);
                }
            }
            break;
        case 1:
        case 2:
            scaleY = scaleX -= 0.001;
            angZ += field_378;
            v_inerc -= 0.5;
            if ( c_A < 4)
            {
                active = false;
                break;
            }
            c_A -= 4;
            if (x > 1380.0 || x < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 3:
            scaleY = scaleX *= 0.995;
            angZ += field_378;
            field_378 *= 0.99;
            field_37C -= 0.1;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            if ( addition[1] == 1.0 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            v_inerc += field_37C;
            x += dir * h_inerc;
            y += v_inerc;
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 4:
            scaleY = scaleX += 0.001;
            angZ += field_378;
            field_378 *= 0.95;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            if ( addition[1] == 1.0 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            v_inerc += field_37C;
            x += dir * h_inerc;
            y += v_inerc * 0.15;
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 5:
            scaleY = scaleX += 0.3;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 6:
            scaleY = scaleX *= 0.9;
            if ( c_A < 30 )
            {
                active = false;
                break;
            }
            c_A -= 30;
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 7:
        case 8:
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 1 )
            {
                active = false;
                break;
            }
            x = chrt->x;
            y = chrt->y;
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        case 9:
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 )
            {
                active = false;
                break;
            }
            x = chrt->x;
            y = chrt->y;
            if ( chrt->get_frame() >= 11 )
            {
                active = false;
                break;
            }
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        default:
            if ( chrt->get_seq() != 607 || chrt->get_subseq() != 2 || chrt->hit_stop <= 0 )
                if ( process() )
                    active = false;
            break;
        }
        break;
    case 858:
        switch ( get_subseq() )
        {
        case 0:
            if ( !field_36C )
            {
                if ( chrt->get_seq() != 608 )
                {
                    active = false;
                    break;
                }
                x = chrt->x;
                y = chrt->y;
                if ( chrt->get_frame() == 10 )
                    field_36C = 1;
            }
            else
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }

            if ( process() )
                active = false;
            if ( get_frame_time() == 0 && get_frame() == 1 )
            {
                for (int32_t i=0; i< 16; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(160) - 10.0;
                    tmp[1] = scene_rand_rngf(4) + 10.0;
                    tmp[2] = (scene_rand_rng(100) > 50) + 1.0;

                    addbullet(chrt, NULL, 858, (cos_deg(-tmp[0])*135.0 + 200.0)* dir + x, y, dir, 1, tmp, 3 );
                }
                float tmp[3];
                tmp[2] = 4.0;

                for (int32_t i=0; i< 8; i++)
                {
                    tmp[0] = i * 45.0 + 22.5;
                    tmp[1] = scene_rand_rngf(4) + 16.0;

                    int32_t ord = 1 - 2 * (-sin_deg(-tmp[0]) >= 0.0);
                    float xx = (cos_deg(-tmp[0]) * 80.0 + 200.0) * dir + x;
                    float yy = sin_deg(-tmp[0]) * 15.0 + y;

                    addbullet(chrt, NULL, 858, xx, yy, dir, ord, tmp, 3 );
                }

                tmp[2] = 5.0;

                addbullet( chrt, NULL, 858, (200 * dir) + x, y, dir, -1, tmp,3);
            }
            break;
        case 1:
        case 2:
            scaleY = scaleX -= 0.001;
            angZ += field_378;
            v_inerc -= 0.5;
            if ( c_A < 4)
            {
                active = false;
                break;
            }
            c_A -= 4;
            if (x > 1380.0 || x < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            scaleY = scaleX *= 0.995;
            angZ += field_378;
            field_378 *= 0.99;
            field_37C -= 0.1;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            if ( addition[1] == 1.0 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            v_inerc += field_37C;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 4:
            scaleY = scaleX += 0.001;
            angZ += field_378;
            field_378 *= 0.95;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            if ( addition[1] == 1.0 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            v_inerc += field_37C;
            x += dir * h_inerc;
            y += v_inerc * 0.15;
            if ( process() )
                active = false;
            break;
        case 5:
            scaleY = scaleX += 0.3;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            if ( process() )
                active = false;
            break;
        case 6:
            scaleY = scaleX *= 0.9;
            if ( c_A < 30 )
            {
                active = false;
                break;
            }
            c_A -= 30;
            if ( process() )
                active = false;
            break;
        default:
            if ( process() )
                active = false;
            break;
        }
        break;
    case 860:
        switch ( get_subseq() )
        {
        case 0:
            x = chrt->x;
            y = chrt->y + 110.0;
            scaleX += 0.05;
            if ( scaleX > 2.0 )
                scaleX = 2.0;
            scaleY = scaleX;
            if ( !field_36C )
            {
                if ( c_A > 245 )
                    c_A = 255;
                else
                    c_A += 10;
                if ( ((char_cirno *)chrt)->field_890 <= 0 )
                    field_36C = 1;
                if ( get_elaps_frames() % 8 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(5);
                    tmp[2] = 2.0;
                    addbullet( chrt, NULL, 860, x, y, dir, -1, tmp,3);
                }
                if ( get_elaps_frames() % 8 == 0 && chrt->get_seq() != 610 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 6.0;
                    addbullet( chrt, NULL, 860, x, y, dir, -1, tmp,3);
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                    break;
                }
            }
            else
            {
                scaleY = scaleX *= 0.98;
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 6:
            if ( get_elaps_frames() % 15 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5);
                tmp[2] = 2.0;
                addbullet( chrt, this, 860, x, y, dir, -1, tmp,3);
            }
            if ( get_elaps_frames() < 60 )
            {
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 4.0;
                addbullet( chrt, NULL, 860, x, y, dir, 1, tmp,3);
                for(int32_t i=0; i<12; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 8.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    float xx = cos_deg(-tmp[0]) * tmp[1] * 5.0 * scaleX * dir + x;
                    float yy = sin_deg(-tmp[0]) * tmp[1] * 5.0 * scaleY + y + 100.0;
                    addbullet(chrt, NULL, 860, xx, yy, dir, 1, tmp, 3);
                }
                for (int32_t i=0; i<6; i++)
                {
                    tmp[0] = i * 60.0 - scene_rand_rngf(30);
                    tmp[1] = scene_rand_rngf(2) + 13.0;
                    tmp[2] = 2.0;

                    float xx = cos_deg(-tmp[0]) * 50.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 50.0 + y + 100.0;
                    addbullet( chrt,NULL, 860, xx, yy, dir, 1, tmp,3);
                }
                active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 && getlvl_height() >= y )
            {
                v_inerc *= -0.75;
                h_inerc *= 0.5;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 863:
        if (get_subseq() == 0)
        {
            field_37C += 35.0;
            if ( chrt->get_seq() == 613 || chrt->get_seq() == 663 )
                if ( chrt->get_subseq() >= 4 )
                    field_374 = 1;
            if ( chrt->get_seq() != 613 && chrt->get_seq() != 663 )
                field_374 = 1;

            if ( field_374 )
                set_vec_speed(addition[0], addition[1]);
            else
            {
                CharFrameData *frm = chrt->get_pframe();
                x = (frm->extra1[4] * dir) + chrt->x;
                y = chrt->y - frm->extra1[5];
            }
            if ( field_36C )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.05 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                if ( addition[0] > 0.0 )
                {
                    if ( chrt->dX(dir)> 0 )
                        if ( addition[0] >= 15.0 )
                        {
                            addition[0] -= 1.0;
                            if ( addition[0] < 15.0 )
                                addition[0] = 15.0;
                        }
                    if ( chrt->dX(dir)< 0 )
                        if ( addition[0] <= 75.0 )
                        {
                            addition[0] += 1.0;
                            if ( addition[0] >= 75.0 )
                                addition[0] = 75.0;
                        }
                }
                if ( addition[0] < 0.0 )
                {
                    if ( chrt->dX(dir) > 0 )
                        if ( addition[0] <= -15.0 )
                        {
                            addition[0] += 1.0;
                            if ( addition[0] >= -15.0 )
                                addition[0] = -15.0;
                        }
                    if ( chrt->dX(dir) < 0 )
                        if ( addition[0] >= -75.0 )
                        {
                            addition[0] -= 1.0;
                            if ( addition[0] <= -75.0 )
                                addition[0] = -75.0;
                        }
                }
                angZ = addition[0];
                set_custom_box( 0, (scaleY * 20.0), field_37C, (scaleY * -20.0), addition[0], 0,0);
                sub_48C5F0( 0);
                if ( field_190 )
                {
                    if ( field_190 == 4 )
                        field_194 = 0;
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_190 = 0;
                        field_36E = 0;
                    }
                }
                if ( field_194 <= 0 || get_elaps_frames() >= 300 )
                {
                    field_36C = 1;
                    break;
                }
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        else if ( get_subseq() == 1 )
        {
            angZ = scene_rand_rng(360);
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                if ( bul_parent->field_36C )
                {
                    scaleY = scaleX *= 0.85;
                    if ( scaleX < 0.05 )
                    {
                        active = false;
                        break;
                    }
                }
            }
            else
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.01 )
                {
                    active = false;
                    break;
                }
            }
        }
        else if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = cos_deg(-bul_parent->angZ) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin_deg(-bul_parent->angZ) * bul_parent->field_37C + bul_parent->y;
            if ( bul_parent->field_36C )
            {
                scaleX = scaleY *= 0.8;
                if ( scaleY <= 0.05 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( process() )
            active = false;
        if ( get_subseq() == 0 )
            sub_438450( 0.0, 0.0, field_37C, 256.0);
        break;
    case 900:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C )
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            else
            {
                if ( chrt->get_seq() < 710 || chrt->get_seq() > 714 || chrt->get_subseq() > 2 )
                {
                    field_36C = 1;
                }
                else
                {
                    x = chrt->x;
                    y = chrt->y + 220.0;
                    scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                    field_378 += 0.01;
                }
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
        case 7:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            v_inerc -= 0.35;
            angZ = -atan2_deg(v_inerc, h_inerc);
            if ( !field_190 && !chrt->char_is_shock() && getlvl_height() < y )
            {
                if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                for(int32_t i=0; i<2; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 900, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            break;
        case 6:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            v_inerc -= 0.1;
            angZ = -atan2_deg(v_inerc, h_inerc);
            if ( !field_190 && !chrt->char_is_shock() && getlvl_height() < y )
            {
                if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
            }
            else
            {
                chrt->play_sfx( 1);
                for(int32_t i=0; i<2; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 900, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            break;
        case 8:
        case 9:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 )
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
        case 11:
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( field_36C == 0)
            {
                if ( c_A > 240 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 15;

                if ( chrt->get_seq() < 710 || chrt->get_seq() > 714 || chrt->get_subseq() != 1 )
                {
                    field_36C = 2;
                }
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 220.0;
                    if ( field_36E >= 20 )
                    {
                        field_36C = 2;
                    }
                }
            }
            if ( field_36C == 1 )
            {
                field_36E++;
                if ( chrt->get_seq() < 710 || chrt->get_seq() > 714 || chrt->get_subseq() != 1)
                    field_36C = 2;
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 220.0;
                    if (field_36E >= 20)
                        field_36C = 2;
                }
            }
            if ( field_36C == 2 )
            {
                if ( chrt->get_seq() >= 710 && chrt->get_seq() <= 714 && chrt->get_subseq() == 1 )
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 220.0;
                }
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 12:
        case 13:
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( field_36C == 0)
            {
                if ( c_A > 240 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 15;

                if ( chrt->get_seq() != 712 || chrt->get_subseq() > 1 )
                {
                    field_36C = 2;
                }
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 100.0;
                    if ( field_36E >= 20 )
                    {
                        field_36C = 2;
                    }
                }
            }
            if ( field_36C == 1 )
            {
                field_36E++;
                if ( chrt->get_seq() != 712 || chrt->get_subseq() != 1)
                    field_36C = 2;
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 100.0;
                    if (field_36E >= 20)
                        field_36C = 2;
                }
            }
            if ( field_36C == 2 )
            {
                if ( chrt->get_seq() == 712 && chrt->get_subseq() <= 1 )
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 100.0;
                }
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 14:
            if ( field_36C )
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            else
            {
                if ( chrt->get_seq() != 712 || chrt->get_subseq() > 3 )
                {
                    field_36C = 1;
                }
                else
                {
                    x = chrt->x;
                    y = chrt->y + 100.0;
                    scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                    field_378 += 0.005;
                }
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 910:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_36C )
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            else
            {
                if ( chrt->get_seq() < 720 || chrt->get_seq() > 724 || chrt->get_subseq() > 1 )
                {
                    field_36C = 1;
                }
                else
                {
                    x = chrt->x;
                    y = chrt->y + 100.0;
                    scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                    field_378 += 0.01;
                }
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.85;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 2:
            angZ += field_378;
            field_378 *= 0.95;
            scaleY = scaleX *= 1.005;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            v_inerc += field_37C;
            field_37C -= 0.1;
            if ( field_37C <= -5.0 )
                field_37C = -5.0;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 3:
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 5:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            v_inerc -= 0.05;
            angZ = -atan2_deg(v_inerc, h_inerc);
            if ( field_190 == 0 && !chrt->char_is_shock() && getlvl_height() < y )
            {
                if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
                {
                    active = false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                if ( process() )
                    active = false;
                break;
            }
            else
            {
                for(int32_t i=0; i<2; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 8.0;
                    addbullet( chrt, NULL, 900, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            break;
        case 6:
            if ( field_190 == 5 )
            {
                active = false;
                break;
            }
            angZ = addition[0];
            addition[1] -= 0.5;
            if ( addition[1] <= 1.0 )
                addition[1] = 1.0;
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() % 15 == 0 )
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5) + 2.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
            }
            if ( chrt->char_is_shock() || health < 0 )
            {
                chrt->play_sfx( 1);
                for(int32_t i=0; i<4; i++)
                {
                    float tmp[3];
                    tmp[0] = -scene_rand_rngf(180);
                    tmp[1] = scene_rand_rngf(5) + 5.0;
                    tmp[2] = (scene_rand_rng(10) > 5) + 16.0;
                    addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                }
                active = false;
            }
            else
            {
                if ( get_elaps_frames() < 180 )
                {
                    if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
                    {
                        active = false;
                        break;
                    }
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( process() )
                        active = false;
                }
                else
                {
                    chrt->play_sfx( 1);
                    for(int32_t i=0; i<4; i++)
                    {
                        float tmp[3];
                        tmp[0] = -scene_rand_rngf(180);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = (scene_rand_rng(10) > 5) + 16.0;
                        addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                    }

                    int32_t pr1,pr2,pr3;
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        pr1 = 3;
                        pr2 = 3;
                        pr3 = 3;
                        break;
                    case GAME_DIFF_HARD:
                        pr1 = 2;
                        pr2 = 3;
                        pr3 = 2;
                        break;
                    case GAME_DIFF_NORMAL:
                        pr2 = 4;
                        pr1 = 2;
                        pr3 = 1;
                        break;
                    case GAME_DIFF_EASY:
                        pr2 = 3;
                        pr1 = 1;
                        pr3 = 0;
                        break;
                    default:
                        pr2 = 0;
                        pr1 = 0;
                        pr3 = 0;
                        break;
                    }
                    float tmp[3];
                    for(int32_t i=0; i<4; i++)
                    {
                        tmp[0] = -scene_rand_rngf(180);
                        tmp[1] = scene_rand_rngf(5) + 5.0;
                        tmp[2] = (scene_rand_rng(10) > 5) + 16.0;
                        addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                    }
                    for (int32_t i=0; i<pr2; i++)
                    {
                        tmp[0] = scene_rand_rngf(30) + addition[0] - 15.0;
                        tmp[1] = scene_rand_rngf(30) * 0.1 + 10.0;
                        tmp[2] = 5.0;
                        addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                    }
                    for (int32_t i=0; i<pr1; i++)
                    {
                        tmp[0] = scene_rand_rngf(40) + addition[0] - 20.0;
                        tmp[1] = scene_rand_rngf(30) * 0.1 + 6.5;
                        tmp[2] = 5.0;
                        addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                    }
                    for (int32_t i=0; i<pr3; i++)
                    {
                        tmp[0] = scene_rand_rngf(50) + addition[0] - 25.0;
                        tmp[1] = scene_rand_rngf(30) * 0.1 + 3.0;
                        tmp[2] = 5.0;
                        addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                    }

                    tmp[1] = 0.3;
                    tmp[2] = 15.0;
                    addbullet( chrt, NULL, 910, x, y, dir, 1, tmp,3);
                    active = false;
                }
            }
            break;
        case 8:
        case 9:
        case 16:
        case 17:
            v_inerc -= 0.2;
            angZ += field_378;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( v_inerc < 0.0 )
                if ( getlvl_height() >= y )
                {
                    v_inerc *= -0.75;
                    h_inerc *= 0.5;
                }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 10:
        case 11:
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( field_36C == 0)
            {
                if ( c_A > 240 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                {
                    c_A += 15;
                }
                if ( chrt->get_seq() < 710 || chrt->get_seq() > 714 || chrt->get_subseq() != 1 )
                {
                    field_36C = 2;
                }
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 220.0;
                    if ( field_36E >= 20 )
                    {
                        field_36C = 2;
                    }
                }
            }
            if ( field_36C == 1 )
            {
                field_36E++;
                if ( chrt->get_seq() < 710 || chrt->get_seq() > 714 || chrt->get_subseq() != 1)
                    field_36C = 2;
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 220.0;
                    if (field_36E >= 20)
                        field_36C = 2;
                }
            }
            if ( field_36C == 2 )
            {
                if ( chrt->get_seq() >= 710 && chrt->get_seq() <= 714 && chrt->get_subseq() == 1 )
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 220.0;
                }
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 12:
        case 13:
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( field_36C == 0)
            {
                if ( c_A > 240 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 15;

                if ( chrt->get_seq() != 712 || chrt->get_subseq() > 1 )
                {
                    field_36C = 2;
                }
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 100.0;
                    if ( field_36E >= 20 )
                    {
                        field_36C = 2;
                    }
                }
            }
            if ( field_36C == 1 )
            {
                field_36E++;
                if ( chrt->get_seq() != 712 || chrt->get_subseq() > 1)
                    field_36C = 2;
                else
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 100.0;
                    if (field_36E >= 20)
                        field_36C = 2;
                }
            }
            if ( field_36C == 2 )
            {
                if ( chrt->get_seq() == 712 && chrt->get_subseq() <= 1 )
                {
                    x = cos_deg(-addition[0]) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] + chrt->y + 100.0;
                }
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 14:
            if ( field_36C )
            {
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            else
            {
                if ( chrt->get_seq() != 712 || chrt->get_subseq() > 3 )
                {
                    field_36C = 1;
                }
                else
                {
                    x = chrt->x;
                    y = chrt->y + 100.0;
                    scaleY = scaleX = sin_deg(get_elaps_frames() * 2) * 0.25 + field_378;
                    field_378 += 0.005;
                }
            }
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        case 15:
            scaleY = scaleX += addition[1];
            addition[1] *= 0.92;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        default:
            if ( x > 1380.0 || x < -100.0 || y > 900.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( process() )
                active = false;
            break;
        }
        break;
    case 980:
        //sub_48C190(this); //HACK
        if ( process() )
            active = false;
        break;
    case 989:
        if ( chrt->get_seq() < 300 )
        {
            active = false;
            break;
        }
        if ( chrt->hit_stop <= 0 )
        {
            if ( get_subseq() == 0 )
            {
                x = dir * addition[0] + chrt->x;
                y = addition[1] + chrt->y;
                scaleX += 0.001;
                scaleY += 0.001;
                if ( c_B >= 250 )
                {
                    c_B = 255;
                    c_G += 4;
                }
                else
                {
                    c_B += 5;
                }
                if ( get_elaps_frames() >= 120 )
                {
                    set_subseq(2);
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 3.0;
                    addbullet( chrt, this, 989, x, y, dir, 1, tmp,3);
                    c_B = 255;
                    c_G = 255;
                    c_R = 255;
                    break;
                }
            }
            if ( get_subseq() == 1 )
            {
                if ( c_A >= 250 )
                    c_A = 255;
                else
                    c_A += 5;
                scaleX -= 0.002;
                scaleY -= 0.002;
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->get_subseq() == 2 )
                    {
                        active = false;
                        break;
                    }
                }
            }
            if ( get_subseq() == 2 )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                scaleY = scaleX *= 0.9;
                c_A -= 10;
                c_G -= 10;
                c_R -= 10;
            }
            if ( get_subseq() == 3 )
            {
                if ( c_A < 5 )
                {
                    active = false;
                    break;
                }
                scaleX += 0.1;
                scaleY += 0.1;
                c_A -= 5;
                c_G -= 5;
                c_R -= 5;
            }
            if ( process() )
                active = false;
        }
        break;
    case 990:
        if ( get_subseq() == 0 )
        {
            switch ( chrt->get_seq() )
            {
            case 302:
                if ( (chrt->get_subseq() == 0 && chrt->get_frame() <= 9) || (chrt->get_subseq() == 1 && chrt->get_frame() <= 11) )
                {
                    dir = chrt->dir;
                    CharFrameData *frm = chrt->get_pframe();
                    x = frm->extra1[4] * dir + chrt->x;
                    y = chrt->y - frm->extra1[5];
                }
                else if ( get_frame() <= 6 )
                {
                    set_frame(7);
                    return;
                }
                break;
            case 307:
                if ( chrt->get_frame() <= 13 )
                {
                    dir = chrt->dir;
                    CharFrameData *frm = chrt->get_pframe();
                    x = frm->extra1[4] * dir + chrt->x;
                    y = chrt->y - frm->extra1[5];
                }
                else if ( get_frame() <= 6 )
                {
                    set_frame(7);
                    return;
                }
                break;
            case 322:
                if ( chrt->get_frame() <= 8 )
                {
                    dir = chrt->dir;
                    CharFrameData *frm = chrt->get_pframe();
                    x = frm->extra1[4] * dir + chrt->x;
                    y = chrt->y - frm->extra1[5];
                }
                else if ( get_frame() <= 6 )
                {
                    set_frame(7);
                    return;
                }
                break;
            case 696:
                if (chrt->get_frame() <= 13 )
                {
                    dir = chrt->dir;
                    CharFrameData *frm = chrt->get_pframe();
                    x = frm->extra1[4] * dir + chrt->x;
                    y = chrt->y - frm->extra1[5];
                }
                else if ( get_frame() <= 6 )
                {
                    set_frame(7);
                    return;
                }
                break;
            default:
                if ( get_frame() <= 6 )
                {
                    set_frame(7);
                    return;
                }
                break;
            }
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            active = false;
        break;
    case 998:
        if ( get_subseq() == 0 )
        {

            if ( chrt->get_seq() > 153 && chrt->get_seq() < 158 )
            {
                x = (57 * dir) + chrt->x;
                y = chrt->y + 60.0;
            }
            if ( chrt->get_seq() > 149 && chrt->get_seq() < 154 )
            {
                x = (57 * dir) + chrt->x;
                y = chrt->y + 94.0;
            }
            if ( chrt->get_seq() == 158 )
            {
                x = (57 * dir) + chrt->x;
                y = chrt->y + 100.0;
            }
            if ( chrt->get_seq() < 150 || chrt->get_seq() > 158 )
            {
                next_subseq();
                chrt->bbarrier_show = 0;
            }
        }
        if ( get_subseq() == 1 )
        {
            v_inerc -= 0.2;
            scaleX *= 0.99;
            scaleY *= 0.99;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            y += v_inerc;
        }
        if ( process() )
            active = false;
        break;
    case 999:
        if ( get_subseq() <= 1 )
        {
            chrt->x = x;
            if ( x > 1480.0 || x < -200.0 )
            {
                active = false;
                break;
            }
            if ( get_subseq() == 1 )
                v_inerc -= v_force;
        }
        x += dir * h_inerc;
        y += v_inerc;
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = 15.0;
            v_inerc = 15.0;
            v_force = 0.2;
        }
        break;
    default:
        c_bullet::func10();
        break;
    }
}

void cirno_bullets::set_seq_params()
{
    h_inerc = 0.0;
    v_inerc = 0.0;
    field_378 = 0.0;
    field_37C = 0.0;
    field_380 = 0.0;
    field_384 = 0.0;
    field_394 = 0;
    field_388 = 0.0;
    field_396 = 0;
    field_194 = 0;
    field_198 = 1.0;
    field_36C = 0;
    field_36E = 0;
    field_370 = 0;
    field_372 = 0;
    field_374 = 0;
    field_1A2 = 0;
    switch(get_seq())
    {
    case 800:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 7 )
        {
            field_194 = 1;
            scaleY = scaleX = scene_rand_rngf(20) * 0.01 + 0.9;
            angZ = addition[0];
        }
        if ( get_subseq() == 1 )
        {
            angZ = scene_rand_rngf(360);

            for (int32_t i =0; i<6; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(5) + 2.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 800, x, y, dir, 1, tmp,3);
            }

            for (int32_t i =0; i<6; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(12) + 2.0;
                tmp[2] = 6.0;
                addbullet( chrt, NULL, 800, x, y, dir, 1, tmp,3);
            }
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 4 || get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        break;
    case 801:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 6;
            angZ = addition[0];
        }
        if ( get_subseq() == 1 )
        {
            scaleX = 0.1;
            scaleY = 0.1;
            angX = addition[0];
            angY = 70.0;
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 4 || get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        break;
    case 802:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 1;
            scaleY = scaleX = scene_rand_rngf(20) * 0.01 + 0.9;
            angZ = addition[0];
        }
        if ( get_subseq() == 1 )
            angZ = scene_rand_rngf(360);
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 4 || get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rng(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 7 )
            set_vec_speed(addition[0], addition[1]);
        break;
    case 803:
        x_off = -40.0;
        field_194 = 10;
        break;
    case 804:
        field_194 = 1;
        break;
    case 805:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 3;
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            scaleX = 0.0;
            scaleY = 0.0;
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(4) - 2.0;
            field_37C = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        break;
    case 806:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            set_vec_speed(addition[0], addition[1]);
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            scaleX = 0.0;
            scaleY = 0.0;
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(4) - 2.0;
            field_37C = scene_rand_rngf(15) * 0.1 + 1.0;
        }
        if ( get_subseq() == 3 )
        {
            field_194 = 1;
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rng(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 6 || get_subseq() == 7 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        break;
    case 807:
    case 808:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_194 = 1;
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            scaleX = 0.0;
            scaleY = 0.0;
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(4) - 2.0;
            field_37C = scene_rand_rngf(15) * 0.1 + 1.0;
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if (  get_subseq() == 6 ||  get_subseq() == 7 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        break;
    case 809:
        scaleX = addition[1];
        c_A = 128;
        scaleY = addition[1];
        set_subseq(addition[2]);
        angZ = addition[0];
        break;
    case 810:
        field_18C = 0;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            for(int32_t i=0; i<3; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            angZ = addition[0];
            set_vec_speed(addition[0], addition[1]);
            field_194 = 1;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        break;
    case 811:
        field_18C = 4;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            for(int32_t i=0; i<3; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 811, x ,y ,dir,1, tmp,3);
            }
            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet(chrt, NULL, 811, x ,y ,dir,1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 811, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            field_194 = 0;
            /*sub_465E50(&meta, 995); //HACK
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            field_154->field_EC = y + 120.0;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0] + 90.0;
            scaleY = scaleX = scene_rand_rng(20) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 0;
            /*sub_465E50(&meta, 995); //HACK
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            field_154->field_EC = y + 240.0;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0] + 90.0;
            scaleY = scaleX = scene_rand_rng(20) * 0.01 + 0.8;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 11 )
            field_194 = 1;
        break;
    case 812:
        field_18C = 8;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_378 = 300.0;
            if ( chrt->skills_1[8] >= 2 )
                field_378 = 450.0;
            if ( chrt->skills_1[8] >= 4 )
                field_378 = 600.0;
            sub_438450( 0.0, 0.0, 0.0, 256.0);

            scaleX = 1.0;
            scaleY = 1.0;
            field_194 = 1;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;

            addbullet(chrt, this, 812,x, y, dir, 1, tmp, 3);

            tmp[2] = 2.0;
            addbullet(chrt, this, 812,x, y, dir, 1, tmp, 3);
        }
        break;
    case 815:
        field_18C = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 || get_subseq() == 6 )
        {
            field_194 = 0;
            health = 800;
            if ( chrt->skills_1[1] >= 1 )
                health = 1300;
            if ( chrt->skills_1[1] >= 2 )
                health = 1450;
            if ( chrt->skills_1[1] >= 3 )
                health = 1600;
            if ( chrt->skills_1[1] >= 4 )
                health = 1800;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        }
        break;
    case 816:
    case 817:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            for(int32_t i=0; i<3; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }

            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 || get_subseq() == 6 )
            field_194 = 0;
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        }
        break;
    case 820:
        field_18C = 2;
        field_194 = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            for(int32_t i=0; i<3; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }

            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            if ( chrt->skills_1[2] >= 2 )
                set_frame( 1);
            if ( chrt->skills_1[2] >= 4 )
                set_frame( 2);
            field_194 = 0;
            scaleX = 0.25;
            scaleY = 0.25;
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 1;
            angZ = scene_rand_rngf(360);
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleX = scaleY = scene_rand_rng(125) * 0.01 + 0.25;
        }
        if ( get_subseq() == 11 )
        {
            field_194 = 1;
            /*sub_465E50(&meta, 995);
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            field_154->field_EC = getlvl_height();
            LOBYTE(field_154->field_104) = dir;*/
            scaleY = scaleX = scene_rand_rng(20) * 0.01 + 0.8;
        }
        break;
    case 821:
        field_18C = 6;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
            set_vec_speed(addition[0], addition[1]);
        if ( get_subseq() == 1 )
            angZ = addition[0];
        if ( get_subseq() == 2 )
        {
            scaleX = 0.1;
            scaleY = 0.1;
            angZ = addition[0];
        }
        if ( get_subseq() == 3 )
        {
            angZ = addition[0];
            set_vec_speed(addition[0], addition[1]);
            field_194 = 1;
        }
        if ( get_subseq() == 4 || get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(20) - 10.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        break;
    case 822:
        field_18C = 10;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 1;
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 5 )
        {
            v_inerc = 4.0;
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
            enemy->set_seq(102);
            enemy->reset_forces();
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 1;
            angZ = scene_rand_rngf(360);
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(125) * 0.01 + 0.25;
        }
        break;
    case 825:
        field_18C = 3;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
            field_194 = 1;
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            scaleX = 0.0;
            scaleY = 0.0;
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(4) - 2.0;
            field_37C = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(10) - 5.0;
            scaleY = scaleX = scene_rand_rngf(40) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        break;
    case 826:
        field_18C = 7;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<3; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            field_194 = 0;
            /*sub_465E50(&meta, 995); //HACK
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            v225 = y + 120.0;
            field_154->field_EC = v225;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0] + 90.0;
            scaleY = scaleX = scene_rand_rngf(20) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 0;
            /*sub_465E50(&meta, 995); // HACK
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            v227 = y + 120.0;
            field_154->field_EC = v227;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0];
            scaleX = scene_rand_rngf(20) * 0.01 + 0.8;
            scaleY = scaleX * 0.5;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 11 )
            field_194 = 1;
        break;
    case 827:
        field_18C = 11;
        set_subseq(addition[2]);
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            field_378 = scene_rand_rngf(11) - 5.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(6) * 0.1 + 0.8;
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 3 )
        {
            field_378 = scene_rand_rngf(5) - 2.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        if ( get_subseq() == 4 )
        {
            field_378 = scene_rand_rngf(11) - 5.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(3) * 0.1 + 0.8;
        }
        break;
    case 848:
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 1 )
        {
            field_378 = scene_rand_rngf(40) + 10.0;
            x = (cos_deg(-addition[0]) * field_378 + 58.0) * dir + chrt->x;
            y = sin_deg(-addition[0]) * field_378 + chrt->y + 107.0;
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 2.0;
            addbullet(chrt, NULL, 848, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(4) - 2.0;
        }
        if ( get_subseq() == 5 )
        {
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(20) * 0.1 - 1.0;
        }
        if ( get_subseq() == 6 )
        {
            scaleY = scaleX = scene_rand_rng(100) * 0.01 + 0.5;
            for (int32_t i=0; i<4; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(8) + 8.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 848, x, y, dir, 1, tmp, 3);
            }
            for (int32_t i=0; i<2; i++)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(4) + 4.0;
                tmp[2] = 5.0;
                addbullet(chrt, NULL, 848, x, y, dir, 1, tmp, 3);
            }
        }
        if ( get_subseq() == 7 )
        {
            scaleX = 0.1;
            scaleY = 0.1;
        }
        break;
    case 849:
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 2 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
        }
        if ( get_subseq() == 3 || get_subseq() == 4 || get_subseq() == 5 )
        {
            field_18C = 5;
            field_194 = 5;
        }
        break;
    case 850:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_360 = 1;
            field_378 = 0.5;
        }
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<3; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 850, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 850, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            field_360 = 1;
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 850, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            angZ = addition[0];
            set_vec_speed(addition[0], addition[1]);
            field_194 = 1;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        break;
    case 851:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 810, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            field_194 = 0;
            /*sub_465E50(&meta, 995); //HACK
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            v295 = y + 120.0;
            field_154->field_EC = v295;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0] + 90.0;
            scaleX = scaleY = scene_rand_rngf(20) * 0.01 + 0.8;
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 0;
            /*sub_465E50(&meta, 995);
            field_154->field_F8 = 10.0;
            field_154->field_FC = 10.0;
            field_154->field_E8 = x;
            v297 = y + 240.0;
            field_154->field_EC = v297;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0] + 90.0;
            scaleX = scaleY = scene_rand_rngf(20) * 0.01 + 0.8;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleX = scaleY = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 10 )
            field_194 = 1;
        if ( get_subseq() >= 11 && get_subseq() <= 14 )
        {
            scaleX = 0.1;
            scaleY = 0.1;
        }
        break;
    case 852:
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
            c_A = 128;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for(int32_t i=0; i<3; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 852, x ,y ,dir,1, tmp,3);
            }

            tmp[2] = 0.0;
            addbullet(chrt, this, 852, x ,y ,dir,-1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 852, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            v_inerc *= 0.5;
            angZ = -atan2_deg(v_inerc, h_inerc);
            float tm = cos_deg(-addition[0]);
            if ( cos_deg(-addition[0]) < 0.0 )
                tm *= -1;
            field_194 = 1;
            scaleY = scaleX = (tm) * 0.5 + 0.5;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 10 || get_subseq() == 11 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        break;
    case 854:
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            field_360 = 1;
            scaleX = 0.0;
            scaleY = 0.0;
        }
        if ( get_subseq() == 1 )
            angZ = scene_rand_rngf(360);
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            angZ = addition[0];
            field_194 = 1;
            field_378 = 0.2;
            scaleY = scaleX = scene_rand_rngf(5) * 0.1 + 0.8;

            float tmp[3];
            tmp[0] = addition[0];
            tmp[1] = 0.0;
            tmp[2] = 15.0;
            addbullet(chrt, this, 854, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 10 || get_subseq() == 11 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 12 )
            field_194 = 1;
        if ( get_subseq() == 14 )
            y_to_down = true;
        if ( get_subseq() == 15 )
        {
            angZ = addition[0];
            field_378 = 0.2;
            scaleY = scaleX = scene_rand_rngf(5) * 0.1 + 1.0;
            sub_48BF60(scene_rand_rngf(360));
        }
        break;
    case 855:
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
            c_A = 128;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for(int32_t i=0; i<3; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 855, x ,y ,dir,1, tmp,3);
            }

            tmp[2] = 0.0;
            addbullet(chrt, this, 855, x ,y ,dir,-1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 855, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            v_inerc *= 0.5;
            angZ = -atan2_deg(v_inerc, h_inerc);
            float tm = cos_deg(-addition[0]);
            if ( cos_deg(-addition[0]) < 0.0 )
                tm *= -1;
            field_194 = 1;
            scaleY = scaleX = (tm) * 0.5 + 0.5;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 10 || get_subseq() == 11 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        break;
    case 856:
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
        {
            field_194 = 1;
            scaleX = 1.0;
            scaleY = 0.25;
        }
        if ( get_subseq() == 1 )
        {
            if ( bul_parent )
            {
                x = cos_deg(-addition[0]) * bul_parent->scaleX * addition[1] * dir + bul_parent->x;
                y = sin_deg(-addition[0]) * bul_parent->scaleY * addition[1] + bul_parent->y;
            }
            field_378 = scene_rand_rngf(50) * 0.1 + 6.0;
            field_37C = scene_rand_rngf(10) * 0.1 + 0.5;
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rng(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 852, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 7 )
        {
            angZ = scene_rand_rngf(360);
            angY = scene_rand_rngf(20) - 10.0;
            angX = scene_rand_rngf(20) + 65.0;
            if ( bul_parent )
            {
                scaleY = scaleX = (scene_rand_rngf(25) * 0.01 + 1.0) * bul_parent->scaleX;
            }
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 10 || get_subseq() == 11 )
        {
            if ( bul_parent )
            {
                x = cos_deg(-addition[0]) * bul_parent->scaleX * addition[1] * dir + bul_parent->x;
                y = sin_deg(-addition[0]) * bul_parent->scaleY * addition[1] + bul_parent->y;
            }
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(30) * 0.1 + 5.0;
            field_37C = scene_rand_rngf(10) * 0.1 + 0.5;
            field_380 = 6.0 - scene_rand_rngf(13);
        }
        break;
    case 857:
        set_subseq(addition[2]);
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            field_378 = scene_rand_rngf(11) - 5.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(6)* 0.1 + 0.8;
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 3 )
        {
            field_378 = scene_rand_rngf(5) - 2.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        if ( get_subseq() == 4 )
        {
            field_378 = scene_rand_rngf(11) - 5.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(3) * 0.1 + 0.9;
        }
        break;
    case 858:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_194 = 1;
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            field_378 = scene_rand_rngf(11) - 5.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(6) * 0.1 + 0.8;
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 3 )
        {
            field_378 = scene_rand_rngf(5) - 2.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        if ( get_subseq() == 4 )
        {
            field_378 = scene_rand_rngf(11) - 5.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(3) * 0.1 + 0.9;
        }
        break;
    case 860:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            c_A = 0;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 810, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
            field_194 = 1;
        if ( get_subseq() == 5 || get_subseq() == 6 )
            field_194 = 0;
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        }
        break;
    case 863:
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            sub_438450( 0.0, 0.0, 0.0, 256.0);
            scaleX = 1.0;
            scaleY = 1.5;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;
            field_194 = 15;
            addbullet(chrt, this, 863, x, y, dir, 1, tmp, 3);

            tmp[2] = 2.0;
            addbullet(chrt, this, 863, x, y, dir, 1, tmp, 3);
        }
        break;
    case 900:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 14 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 900, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 900, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 900, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 || get_subseq() == 6 || get_subseq() == 7 )
        {
            angZ = addition[0];
            set_vec_speed(addition[0], addition[1]);
            field_194 = 1;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() >= 10 && get_subseq() <= 13 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        break;
    case 910:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 14 )
            field_378 = 0.5;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            for (int32_t i=0; i<12; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;

                addbullet( chrt,NULL, 910, x, y, dir, 1, tmp,3);
            }
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(5) + 4.0;
            tmp[2] = 2.0;
            addbullet( chrt,NULL, 910, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(6) - 3.0;
            scaleY = scaleX = scene_rand_rngf(60) * 0.01 + 0.7;
        }
        if ( get_subseq() == 3 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() == 4 )
        {
            for(int32_t i=0; i<360; i+=60)
            {
                float tmp[3];
                tmp[0] = scene_rand_rngf(40) + i;
                tmp[1] = scene_rand_rngf(10) + 5.0;
                tmp[2] = 3.0;
                addbullet(chrt, NULL, 910, x ,y ,dir,1, tmp,3);
            }
        }
        if ( get_subseq() == 5 || get_subseq() == 6 || get_subseq() == 7 )
        {
            angZ = addition[0];
            set_vec_speed(addition[0], addition[1]);
            field_194 = 1;
        }
        if ( get_subseq() == 8 || get_subseq() == 9 || get_subseq() == 16 || get_subseq() == 17 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            field_36C = scene_rand_rngf(10);
            scaleY = scaleX = scene_rand_rngf(80) * 0.01 + 0.8;
        }
        if ( get_subseq() >= 10 && get_subseq() <= 13 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
        }
        if ( get_subseq() == 15 )
            angZ = scene_rand_rngf(360);
        break;
    case 920:
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 1 || get_subseq() == 3 || get_subseq() == 5 )
            scaleX = 10.0;
        if ( get_subseq() == 2 )
            scaleX = 10.0;
        if ( get_subseq() == 4 )
            scaleX = 6.0;
        if ( get_subseq() == 6 )
            scaleX = 4.0;
        if ( get_subseq() == 10 )
        {
            scaleX = 10.0;
            scaleY = 0.0;
        }
        if ( get_subseq() == 11 )
        {
            float tmp[4];
            tmp[0] = addition[0];
            tmp[1] = 0.0;
            tmp[2] = 10.0;

            addbullet(chrt, this, 920,x ,y ,dir, 1, tmp, 3);

            tmp[1] = 5.0;
            tmp[2] = 9.0;
            tmp[3] = 0.2;

            addbullet(chrt,this, 920, x ,y ,dir, 1, tmp, 4);

            tmp[1] = 15.0;
            tmp[3] = 0.4;
            addbullet(chrt,this, 920, x ,y ,dir, 1, tmp, 4);
        }
        if ( get_subseq() == 12 )
        {
            scaleY = scaleX = scene_rand_rngf(5) * 0.1 + 0.5;
        }
        break;
    case 921:
        angZ = scene_rand_rngf(360);
        set_subseq( addition[2]);
        field_194 = 1;
        set_vec_speed(addition[0], addition[1]);
        scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        break;
    case 980:
        //sub_48C360(); //HACK
        break;
    case 989:
        field_194 = 1;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;

            addbullet(chrt, this, 989,x ,y ,dir, 1, tmp, 3);

            c_R = 0;
            c_G = 0;
            c_B = 0;
        }
        if ( get_subseq() == 1 )
            c_A = 0;
        break;
    case 990:
        set_subseq(addition[2]);
        break;
    case 999:
        set_subseq(addition[2]);
        if ( get_subseq() == 4 )
        {
            h_inerc = addition[0];
            v_inerc = addition[1];
        }
        break;
    default:
        c_bullet::set_seq_params();
        break;
    }
}




