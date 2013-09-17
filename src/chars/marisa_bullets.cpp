#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "marisa_bullets.h"
#include "marisa.h"
#include <math.h>


void marisa_bullets::func10()
{
    switch(get_seq())
    {
    case 800:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 0 )
        {
            field_194 = 1;
            field_36C = 0;
        }

        field_36C++;
        h_inerc = cos_deg(addition[0]) * (addition[1] + field_36C * 0.2);
        v_inerc = -sin_deg(addition[0]) * (addition[1] + field_36C * 0.2);

        if (x > 1380 || x < -100 || y > 1000 || y < -100)
        {
            active = false;
            break;
        }

        if (get_subseq() == 0 || get_subseq() == 1)
        {
            if (sub_48C6A0(0, 0, 4))
            {
                active = false;
                break;
            }

            angZ = addition[0];

            sub_48C4B0(0.0, addition[3], 100.0);

            if ( get_frame_time() > 180 || field_190 != 0 || getlvl_height() >= y )
            {
                chrt->play_sfx(41);
                active = false;

                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 0;

                for(int32_t i=0; i<6; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 7;
                    addbullet(chrt,NULL,800,x,y,dir,1,t,3);
                }

                t[2] = 8;
                addbullet(chrt,NULL,800,x,y,dir,1,t,3);

            }
        }
        else if (get_subseq() >= 2 && get_subseq() <= 5)
        {
            if ( sub_48C6A0(0, 0, 3) )
            {
                active = false;
                break;
            }
            angZ += 30;

            if ( get_elaps_frames() == 10 )
            {
                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 8;
                addbullet(chrt,NULL,800,x,y,dir,1,t,3);

                for(int32_t i=0; i<4; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 7;
                    addbullet(chrt,NULL, 800, x,y,dir,1,t,3);
                }
                active = false;
                break;
            }
        }
        else if (get_subseq() == 6 )
        {
            if ( get_elaps_frames() <= 20 )
            {
                scaleY = scaleX = (get_elaps_frames() % 2) * 0.1 + 2.0;
            }
            else
            {
                scaleY *= 0.85;
                scaleX *= 0.85;

                if ( c_A < 0xAu )
                {
                    active = false;
                    break;
                }
                if ( get_elaps_frames() > 10 )
                    c_A -= 10;
            }
        }
        else if (get_subseq() == 7 )
        {
            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0]) * addition[1];

            addition[1] -= 0.4;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;

            x += dir * h_inerc;
            y += v_inerc;
            scaleY = scaleX *= 0.97;

            if (c_A < 5)
            {
                active = false;
                break;
            }
            c_A -= 5;
            c_R -= 5;
            c_G -= 5;
        }
        else if (get_subseq() == 8 )
        {
            scaleX += 0.3;
            scaleY += 0.3;

            if (c_A < 20)
            {
                active = false;
                break;
            }
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
        }
        x += dir * h_inerc;
        y += v_inerc;
        if ( process() )
            active = false;
        break;

        break;
    case 801:
        if (get_subseq() == 0)
        {
            if ( field_190 == 5 || sub_48C6A0(0, 3, 5) )
            {
                active = false;
                break;
            }
            addition[1] += 0.5;
            sub_48C4B0(0.0, 0.25, 100.0);

            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0] ) * addition[1];

            angZ += 10.0;

            scaleX = scaleY = sin_deg(get_elaps_frames() * 10) * 0.5 + 1.0;

            if ( (get_elaps_frames() % 7) == 0 )
            {
                float t[3];
                t[0] = addition[0];
                t[1] = 0;
                t[2] = 2;
                addbullet(chrt, NULL, 801, x,y,dir,1,t,3);
            }

            if (x > 1380 || x < -100 || y > 1000 || y < -100)
            {
                active = false;
                break;
            }

            sub_48C5F0( 0);
            if ( get_elaps_frames() > 180 || field_190 != 0 || getlvl_height() >= y )
            {
                chrt->play_sfx(3);
                active = false;

                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 3;
                addbullet(chrt, NULL, 801, x,y,dir,1,t,3);

                for (int32_t i=0; i<12; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[1] = scene_rand_rng(10) + 5.0;
                    t[2] = 5.0;
                    addbullet(chrt, NULL, 801, x,y,dir,1,t,3);
                }

                t[2] = 6.0;
                addbullet(chrt, NULL, 801, x,y,dir,1,t,3);
            }
            x += h_inerc*dir;
            y += v_inerc;
        }
        else if (get_subseq() == 1)
        {
            if ( field_190 == 5 || sub_48C6A0(0, 3, 5) )
            {
                active = false;
                break;
            }
            addition[1] += 0.5;
            sub_48C4B0(0.0, 0.25, 100.0);

            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0] ) * addition[1];

            angZ += 10.0;

            scaleX = scaleY = sin_deg(get_elaps_frames() * 10) * 0.5 + 1.0;

            if ( (get_elaps_frames() % 3) == 0 )
            {
                float t[3];
                t[0] = addition[0];
                t[1] = 0;
                t[2] = 2;
                addbullet(chrt, NULL, 801, x,y,dir,1,t,3);
            }

            if (x > 1380 || x < -100 || y > 1000 || y < -100)
            {
                active = false;
                break;
            }

            sub_48C5F0( 0);
            if ( get_elaps_frames() > 180 || field_190 != 0 || getlvl_height() >= y )
            {
                chrt->play_sfx(3);
                active = false;

                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 4;
                addbullet(chrt, NULL, 801, x,y,dir,1,t,3);

                for (int32_t i=0; i<12; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[1] = scene_rand_rng(15) + 5.0;
                    t[2] = 5.0;
                    addbullet(chrt, NULL, 801, x,y,dir,1,t,3);
                }

                t[2] = 7.0;
                addbullet(chrt, NULL, 801, x,y,dir,1,t,3);
            }

            x += h_inerc*dir;
            y += v_inerc;
        }
        else if (get_subseq() == 2) //tail
        {
            scaleX += 0.1;
            scaleY += 0.1;

            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            c_R -= 20;
            c_B -= 20;
        }
        else if (get_subseq() == 3)
        {
            if ( get_frame() == 1 )
            {
                scaleX *= 0.85;
                scaleY *= 0.85;

                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;

                if ( c_G >= 20 )
                {
                    c_R -= 20;
                    c_G -= 20;
                }
            }
            else
            {
                sub_48C5F0( 0);

                if ( field_190 != 0 )
                {
                    if ( field_190 == 4 )
                        field_194 = 0;

                    field_370++;
                    if ( field_370 > 5 )
                    {
                        field_370 = 0;
                        field_190 = 0;
                    }
                }
                scaleY = scaleX = (get_elaps_frames() % 2) * 0.1 + 1.0;

                if ( field_194 == 0 )
                    next_frame();

            }
        }
        else if (get_subseq() == 4)
        {
            if ( get_frame() == 1 )
            {
                scaleX *= 0.85;
                scaleY *= 0.85;

                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;

                if ( c_G >= 20 )
                {
                    c_R -= 20;
                    c_G -= 20;
                }
            }
            else
            {
                sub_48C5F0( 0);

                if ( field_190 != 0 )
                {
                    if ( field_190 == 4 )
                        field_194 = 0;

                    field_370++;
                    if ( field_370 > 10 )
                    {
                        field_370 = 0;
                        field_190 = 0;
                    }
                }

                scaleY = scaleX = (get_elaps_frames() % 2) * 0.1 + 1.0;

                if ( field_194 == 0 )
                    set_frame(1);
            }
        }
        else if (get_subseq() == 5)
        {
            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0] ) * addition[1];

            addition[1] -= 0.4;
            if (addition[1] < 0.5)
                addition[1] = 0.5;

            x += h_inerc * dir;
            y += v_inerc;

            scaleY = scaleX *= 0.97;

            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            c_R -= 5;
            c_G -= 5;
        }
        else if (get_subseq() == 6 || get_subseq() == 7)
        {
            scaleX += 0.3;
            scaleY += 0.3;

            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( process() )
            active = false;
        break;
    case 802:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }

        if ( get_subseq() == 0 )
        {
            if ( sub_48C6A0(0, 4, 5) || x > 1380 || x < -100)
            {
                active = false;
                break;
            }
            angZ += 12.0;
            v_inerc -= 0.85;

            if ( field_190 != 0 || getlvl_height() >= y )
            {
                active = false;

                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 1.0;
                chrt->play_sfx(3);

                addbullet(chrt, NULL, 802, x,y,dir, 1,t,3);

                for(int32_t i =0; i<8; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 2;
                    addbullet(chrt,NULL,802,x,y,dir,1,t,3);
                }

                for(int32_t i =0; i<8; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 3;
                    addbullet(chrt,NULL,802,x,y,dir,1,t,3);
                }
                t[2] = 4;
                addbullet(chrt,NULL,802,x,y,dir,1,t,3);
            }
        }
        else if (get_subseq() == 1)
        {
            if ( get_frame() == 0 )
            {
                if ( field_190 == 6 )
                {
                    field_190 = 0;
                    field_194++;
                }
                if ( field_190 != 0)
                {
                    field_370++;
                    if ( field_370 > 5 )
                    {
                        field_370 = 0;
                        field_190 = 0;
                    }
                }

                scaleY = scaleX = (get_elaps_frames() % 2) * 0.1 + 1.0;

                if ( field_194 == 0)
                    set_frame(1);
            }
            else
            {
                scaleX *= 0.85;
                scaleY *= 0.85;

                if (c_A < 10)
                {
                    active = false;
                    break;
                }
                if ( get_elaps_frames() > 10 )
                    c_A -= 10;
            }
        }
        else if (get_subseq() == 2)
        {
            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0]) * addition[1];

            addition[1] -= 0.75;
            if ( addition[1] < 0.25 )
                addition[1] = 0.25;

            field_378 *= 0.995;
            angZ += field_378;
            scaleY = scaleX *= 1.005;

            if (c_A < 5)
            {
                active = false;
                break;
            }

            c_A -= 5;

            if (c_R >= 10)
            {
                c_R -= 10;
                c_G -= 10;
            }
        }
        else if (get_subseq() == 3)
        {
            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0]) * addition[1];

            addition[1] -= 0.25;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;

            field_378 *= 0.995;
            angZ += field_378;
            scaleY = scaleX *= 0.97;

            if (c_A < 5)
            {
                active = false;
                break;
            }

            c_A -= 5;

            if (c_R >= 10)
            {
                c_R -= 10;
                c_G -= 10;
            }

        }
        else if (get_subseq() == 4)
        {
            scaleX += 0.5;
            scaleY += 0.5;

            if (c_A < 25)
            {
                active = false;
                break;
            }
            c_A -= 25;
        }

        x += h_inerc*dir;
        y += v_inerc;

        if ( process() )
        {
            active = false;
            break;
        }
        break;
    case 803: //6C Beam

        if (get_subseq() <= 1)
        {
            if ( field_36C % 3 == 0 )
                field_190 = 0;

            if ( chrt->char_is_shock())
            {
                for (int32_t i = 0; i< 40; i++)
                {
                    scene_add_effect(chrt,201,scene_rand_rng(15)+30*i*dir+x, y,dir,1);
                }
                active = false;
                break;
            }

            if (chrt->get_subseq() < 5 && chrt->get_seq() == 411)
            {

                x = chrt->getX() + dir*44;
                y = chrt->getY() + 85;
            }
            else if (chrt->get_subseq() < 5 && chrt->get_seq() == 415)
            {
                x = chrt->getX() + dir*48;
                y = chrt->getY() + 104;
            }
            else
                set_subseq(2);

            field_36C++;
        }
        if ( get_subseq() == 2 )
        {
            field_194 = 0;
            scaleY *= 0.8;
            scaleX += 0.1;

            if ( get_elaps_frames() == 40 )
            {
                active = false;
                break;
            }
        }
        if (get_subseq() == 5)
        {
            if ( bul_parent == NULL )
            {
                active = false;
                break;
            }
            angZ = scene_rand_rng(360);

            x = cos_deg(-bul_parent->angZ) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin_deg(-bul_parent->angZ) * bul_parent->field_37C * bul_parent->dir + bul_parent->y;

            if ( bul_parent->field_36C != 0 )
            {
                scaleX = scaleY *= 0.8;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
        }
        else if (get_subseq() == 4)
        {
            field_378 -= 20;
            field_37C += field_380;
            if ( field_36C != 0 )
            {
                field_380 *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;

                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                field_380 += 3.0;
                set_custom_box(0, scaleY * 35, field_37C, scaleY * (-35), addition[0],0,0);
                sub_48C5F0( 0);
                if ( field_190 != 0)
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_190 = 0;
                        field_36E = 0;
                    }
                }
                if ( sub_48C640(2) )
                {
                    field_194 = 0;
                    field_36C = 1;
                    break;
                }
                else
                {
                    if ( field_194 > 0 )
                    {
                        if ( chrt->get_seq() == 411 && chrt->get_subseq() < 5)
                        {
                            x = dir * 44 + chrt->getX();
                            y = chrt->getY() + 85;
                        }
                        else if ( chrt->get_seq() == 415 && chrt->get_subseq() < 5)
                        {
                            x = dir * 48 + chrt->getX();
                            y = chrt->getY() + 104;
                        }
                        else
                        {
                            field_36C = 1;
                            break;
                        }

                        if ( chrt->char_is_shock())
                        {
                            for (int32_t i = 0; i< 40; i++)
                            {
                                scene_add_effect(chrt,201,scene_rand_rng(15)+30*i*dir+x, y,dir,1);
                            }
                            active = false;
                            break;
                        }
                    }
                    else
                        field_36C = 1;
                }
            }
        }
        else if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rng(360);
            if ( !sub_48C6A0(0, 0, 0) )
            {
                if ( bul_parent != NULL )
                {
                    x = bul_parent->getX();
                    y = bul_parent->getY();
                    if ( bul_parent->field_36C != 0)
                    {
                        scaleY = scaleX *= 0.85;
                        if ( scaleX < 0.01 )
                        {
                            active = false;
                            return;
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
        }
        if ( process() )
            active=false;

        if ( get_subseq() == 4 )
            sub_438450(field_378, 0.0, field_37C, 256.0);

        break;

    case 804:
        if ( get_subseq() == 0 )
        {
            h_inerc = cos_deg(addition[0]) * addition[1];
            v_inerc = -sin_deg(addition[0]) * addition[1];
            x += dir * h_inerc;
            y += v_inerc;
            scaleY = scaleX = scene_rand_rng(60) * 0.01 + 0.7;

            if ( field_190 == 6 )
            {
                field_190 = 0;
                field_194 ++;
            }
            if ( field_190 != 0 || getlvl_height() >= y + v_inerc )
            {
                next_subseq();
                scaleX = 2.0;
                scaleY = 2.0;
                break;
            }
        }
        else if (get_subseq() == 1)
        {
            field_36C++;
            scaleX *= 0.85;
            scaleY *= 0.85;
            if ( c_A >= 10 )
                c_A -=10;
        }
        if (c_A < 10 || x > 1380 || x < -100 || y > 1000 || y < -100 || process())
            active = false;
        break;
    case 810:
        set_vec_speed(addition[0],addition[1]);

        addition[1] -= 0.5;
        if ( addition[1] < 0.0 )
            addition[1] = 0.0;

        angZ += 8.0;
        if ( c_A <= 10 || x > 1380 || x < -100 || y > 1000 || y < -100)
            active = false;
        else
        {
            c_A -= 10;
            x += h_inerc * dir;
            y += v_inerc;
            if (process())
                active = false;
        }
        break;
    case 811:
        switch ( get_subseq() )
        {
        case 0:
            if ( field_190 == 5 || sub_48C6A0(1, 3, 7) )
            {
                active=false;
                break;
            }
            sub_48C5F0(0);
            if ( chrt->skills_1[4] >= 4 )
                sub_48C640( 1);

            if ( get_elaps_frames() > 0 && get_elaps_frames() % 5 == 0 && get_elaps_frames() <= 10 )
            {
                for (int8_t i=0; i < 6; i++)
                {
                    float t[3];
                    t[0] = scene_rand_rngf(360) - 180.0;
                    t[1] = scene_rand_rngf(50) * 0.1 + 15.0;
                    t[2] = 5.0;

                    if ( t[0] >= 0.0 )
                        field_36C = -1;
                    else
                        field_36C = 1;

                    float xx = 20 * get_elaps_frames() * dir + x;

                    addbullet(chrt, NULL, 811, xx, y, dir, field_36C, t,3);
                }
            }
            if ( get_elaps_frames() > 120 || field_194 <= 0 )
            {
                next_subseq();
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            set_vec_speed( addition[0], addition[1] * 0.9);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 2:
            scaleY = scaleX += field_378;
            field_378 -= 0.2;
            if ( field_378 <= 0.1 )
                field_378 = 0.1;
            if ( get_elaps_frames() > 10 )
            {
                if ( c_A <= 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
                c_R -= 8;
                c_G -= 8;
            }
            break;
        case 3:
            set_vec_speed( addition[0], addition[1]);
            addition[1] -= 0.5;
            if ( addition[1] < 0.0 )
                addition[1] = 0.0;
            scaleY = scaleX *= 0.95;
            if ( get_elaps_frames() > addition[3] )
            {
                if ( c_A <= 15 )
                {
                    active = false;
                    break;
                }
                c_A -= 15;
                c_R -= 15;
                c_G -= 15;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 4:
            scaleY = scaleX += field_378;
            field_378 -= 0.2;
            if ( field_378 <= 0.1 )
                field_378 = 0.1;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
            break;
        case 5:
            set_vec_speed( addition[0], addition[1]);
            addition[1] -= 0.5;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            x += dir * h_inerc;
            y += v_inerc * 0.25;
            scaleX += 0.01;
            scaleY += 0.01;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            if ( c_G >= 20 )
            {
                c_G -= 20;
                c_R -= 20;
            }
            break;
        default:
            break;
        }
        if ( process() )
            active=false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
            active=false;
        break;
    case 812:
        switch ( get_subseq() )
        {
        case 0:
        case 2:
            if ( chrt->get_seq() != 510 && chrt->get_seq() != 511 && chrt->get_seq() != 512 && chrt->get_seq() != 513 )
            {
                active = false;
                break;
            }
            x = cos_deg(-chrt->angZ - 30.0) * 58.0 * dir + chrt->x;
            y = sin_deg(-chrt->angZ - 30.0) * 58.0 + chrt->y + 100.0;
            angZ = chrt->angZ;
            if ( get_elaps_frames() % 8 == 0 )
            {
                float t[3];
                t[0] = scene_rand_rngf(20) + angZ - 10.0;
                t[1] = scene_rand_rngf(150) * 0.1 + 20.0;
                t[2] = 3.0;
                addbullet(chrt, NULL, 812, x, y, dir, 1, t, 3);
            }
            sub_48C5F0(0);
            if ( field_190 )
            {
                chrt->field_190 = field_190;
                field_36C++;
                if ( field_36C >= 10 )
                {
                    field_190 = 0;
                    field_36C = 0;
                }
            }
            if ( chrt->get_subseq() != 1 )
                active=false;
            break;
        case 1:
            if ( chrt->get_seq() != 510 && chrt->get_seq() != 511 && chrt->get_seq() != 512 && chrt->get_seq() != 513 )
            {
                active = false;
                break;
            }
            x = cos_deg(-chrt->angZ - 30.0) * 58.0 * dir + chrt->x;
            y = sin_deg(-chrt->angZ - 30.0) * 58.0 + chrt->y;
            angZ = chrt->angZ;
            if ( chrt->get_subseq() != 1 )
                active=false;
            break;
        case 3:
            angZ += field_378;
            scaleY = scaleX += 0.01;
            if ( c_A < 7 )
            {
                active = false;
                break;
            }
            c_A -= 7;
            c_G -= 7;
            c_R -= 7;
            addition[1] *= 0.9;
            set_vec_speed( addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            if ( field_36E != 0)
            {
                angZ -= 25.0;
                if ( c_A < 30 )
                {
                    active = false;
                    break;
                }
                c_A -= 30;
                c_G -= 30;
                c_R -= 20;
            }
            else
            {
                if ( chrt->get_seq() != 510 && chrt->get_seq() != 511 && chrt->get_seq() != 512 && chrt->get_seq() != 513 )
                {
                    active = false;
                    break;
                }
                x = chrt->x;
                y = chrt->y + 135.0;
                angZ = chrt->angZ + 75.0;
                sub_48C5F0( 0);
                if ( field_190 )
                {
                    chrt->field_190 = field_190;
                    field_36C++;
                    if ( field_36C >= 10 )
                    {
                        field_190 = 0;
                        field_36C = 0;
                    }
                }
                if ( chrt->get_subseq() != 1 )
                {
                    field_36E = 2;
                    field_194 = 0;
                }
            }
            break;
        default:
            break;
        }
        if ( process() )
            active=false;
        break;
    case 817:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0(0, 3, 7) )
            {
                active = false;
                break;
            }
            sub_48C5F0( 0);
            if ( get_elaps_frames() % 3 == 0 )
            {
                float t[3];
                t[0] = scene_rand_rngf(30) - 15.0 + addition[0] + 180.0;
                t[1] = scene_rand_rngf(15) + 15.0;
                t[2] = 5.0;
                addbullet(chrt, NULL, 817, x, y, dir, 1, t, 3);
            }
            if ( get_elaps_frames() < 15 )
            {
                addition[1] *= 0.9;
                set_vec_speed( addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
                break;
            }
            chrt->play_sfx(31);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            if ( chrt->skills_1[9] < 3 )
                tmp[2] = 1.0;
            else
                tmp[2] = 6.0;
            addbullet(chrt, NULL, 817, x, y, dir, 1, tmp, 3);

            tmp[2] = 2.0;
            addbullet(chrt, NULL, 817, x, y, dir, 1, tmp, 3);

            for (int8_t i=0; i < 6; i++)
            {
                float t[3];
                t[0] = scene_rand_rngf(360) - 180.0;
                t[1] = scene_rand_rngf(50) * 0.1 + 15.0;
                t[2] = 5.0;
                if ( t[0] >= 0.0 )
                    field_36C = -1;
                else
                    field_36C = 1;
                addbullet(chrt, NULL, 820, x, y, dir, field_36C, tmp, 3);
            }
            active=false;
            break;
        case 1:
        case 6:
            if ( field_36E == 0)
            {
                c_R = c_G = 220 + cos_deg(get_elaps_frames() * 12.0) * 35.0;
                if ( sub_48C6A0(1, 4, 5) )
                    field_36E = 1;

                if ( chrt->get_seq() >= 530 && chrt->get_seq() <= 534 && chrt->get_subseq() == 0 )
                    field_36E = 1;

                if ( field_194 <= 0 || (get_elaps_frames() > 20 * ((chrt->skills_1[9] >= 4) + 3) ))
                {
                    field_36E = 1;
                    c_G = 255;
                    c_R = 255;
                }
                else
                {
                    sub_48C5F0( 0);
                    if ( field_190 != 0 )
                    {
                        if ( field_190 == 4 )
                            field_194 = 0;
                        field_36C++;
                        if ( field_36C >= 5 )
                        {
                            field_36C = 0;
                            field_190 = 0;
                        }
                    }
                }
            }
            else
            {
                field_194 = 0;
                scaleY = scaleX += 0.02;

                if ( c_A <= 10 )
                    active = false;
                else
                {
                    c_A -= 10;
                    if (c_G >= 20)
                    {
                        c_G -= 20;
                        c_R -= 20;
                    }
                }
            }
            break;
        case 2:
            scaleY = scaleX += 0.25;
            if ( c_A <= 20 )
                active = false;
            else
            {
                c_A -= 20;
                c_R -= 20;
                c_G -= 20;
            }
            break;
        case 5:
            set_vec_speed( addition[0], addition[1]);
            addition[1] -= 0.5;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            x += cos_deg(-addition[0]) * dir * h_inerc;
            y += sin_deg(-addition[0]) * v_inerc * 0.25;
            scaleX += 0.01;
            scaleY += 0.01;

            if ( c_A < 10 )
                active = false;
            else
            {
                c_A -= 10;
                if (c_G >= 20)
                {
                    c_G -= 20;
                    c_R -= 20;
                }
            }
            break;
        default:
            break;
        }
        if ( process() )
            active=false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
            active = false;
        break;
    case 820:
        if ( field_190 == 5 )
            active = false;
        else
        {
            uint32_t ssq = get_subseq();
            switch ( ssq )
            {
            case 0:
            case 1:
                if ( chrt->char_is_shock() && ssq == 0)
                {
                    for (int8_t i=0; i<10; i++)
                        scene_add_effect(this,201,x,y,dir,1);
                    for (int8_t i=0; i<5; i++)
                        scene_add_effect(this,200,x,y,dir,1);
                    active = false;
                    break;
                }
                angZ += 8;
                if ( get_subseq() == 0 )
                    v_inerc -= 0.75;
                if ( x > 1380 || x < -100 )
                {
                    active = false;
                    break;
                }
                if (get_elaps_frames() % 3 == 0)
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rng(360);
                    tmp[1] = 5;
                    tmp[2] = scene_rand() & 3;
                    addbullet(chrt, NULL, 810, x, y,dir,1 , tmp, 3);
                }
                if ( getlvl_height() < y )
                {
                    x += dir * h_inerc;
                    y += v_inerc;
                }
                else
                {
                    h_inerc = 0;
                    v_inerc = 0;

                    scene_add_effect(this, 127,x,y,dir,-1);
                    scene_add_effect(this, 127,x,y,-dir,-1);

                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 8;
                    if (chrt->skills_1[2] >= 1)
                        tmp[2] = 9;
                    if (chrt->skills_1[2] >= 3)
                        tmp[2] = 10;

                    addbullet(chrt,NULL, 820,x,y,dir,1,tmp,3);
                    tmp[2] = 6;
                    addbullet(chrt,NULL, 820,x,y,dir,1,tmp,3);
                    chrt->play_sfx(8);

                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x, y, dir, pos, tmp, 3);
                    }

                    active = false;
                }
                break;
            case 2:
                if ( get_elaps_frames() == 5 && chrt->skills_1[2] >= 1 )
                {
                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 4;
                    addbullet(chrt, NULL, 820, x -100, y, dir, 1, tmp, 3);
                    tmp[2] = 6;
                    addbullet(chrt, NULL, 820, x -100, y, dir, 1, tmp, 3);
                    chrt->play_sfx(8);

                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, pos, tmp, 3);
                    }

                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 4;
                    addbullet(chrt, NULL, 820, x + 100, y, dir, 1, tmp, 3);
                    tmp[2] = 6;
                    addbullet(chrt, NULL, 820, x + 100, y, dir, 1, tmp, 3);

                    chrt->play_sfx(8);

                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, pos, tmp, 3);
                    }
                }
                else if( get_elaps_frames() == 10 && chrt->skills_1[2] >= 4 )
                {
                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 4;
                    addbullet(chrt, NULL, 820, x -200, y, dir, 1, tmp, 3);
                    tmp[2] = 6;
                    addbullet(chrt, NULL, 820, x -200, y, dir, 1, tmp, 3);
                    chrt->play_sfx(8);

                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, pos, tmp, 3);
                    }

                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 4;
                    addbullet(chrt, NULL, 820, x +200, y, dir, 1, tmp, 3);
                    tmp[2] = 6;
                    addbullet(chrt, NULL, 820, x +200, y, dir, 1, tmp, 3);
                    chrt->play_sfx(8);

                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, pos, tmp, 3);
                    }
                }
                else
                    active = false;
                break;
            case 3:
                if ( get_elaps_frames() > 0 && (get_elaps_frames() % 5 == 0) && get_elaps_frames() <= 60 )
                {
                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 4;
                    addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, 1, tmp, 3);
                    tmp[2] = 6;
                    addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, 1, tmp, 3);

                    chrt->play_sfx(8);
                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, pos, tmp, 3);
                    }


                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 4;
                    addbullet(chrt, NULL, 820, x - get_elaps_frames() * 20 * dir, y, dir, 1, tmp, 3);
                    tmp[2] = 6;
                    addbullet(chrt, NULL, 820, x - get_elaps_frames() * 20 * dir, y, dir, 1, tmp, 3);

                    chrt->play_sfx(8);
                    for (int8_t i=0; i< 12; i++)
                    {
                        tmp[0] = scene_rand_rng(30) + i * 30;
                        tmp[1] = scene_rand_rng(50) * 0.1 + 15;
                        tmp[2] = 5.0;
                        int8_t pos = sin_deg(-tmp[0]) > 0 ? -1 : 1;
                        addbullet(chrt, NULL, 820, x + get_elaps_frames() * 20 * dir, y, dir, pos, tmp, 3);
                    }
                }
                break;
            case 4:
                if ( get_frame() < 2 )
                {
                    if ( field_190 == 6 )
                    {
                        field_190 = 0;
                        field_194++;
                    }
                    if ( field_190 != 0)
                    {
                        field_370++;
                        if ( field_370 > 10 )
                        {
                            field_370 = 0;
                            field_190 = 0;
                        }
                    }
                    scaleY = scaleX = (get_elaps_frames() % 2) * 0.1 + 1.0;
                }
                else
                {
                    scaleX *= 0.9;
                    scaleY *= 0.9;

                    if (c_A < 10 )
                        active = false;
                    else if (get_frame_time() > 10)
                    {
                        c_A -= 10;
                        if ( c_G > 20)
                        {
                            c_G -= 20;
                            c_R -= 20;
                        }
                    }
                }
                break;
            case 5:
                set_vec_speed(addition[0], addition[1]);
                addition[1] *= 0.95;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;

                x += dir * h_inerc;
                y += v_inerc * 0.25;
                scaleX += 0.01;
                scaleY += 0.01;

                if (c_A < 4)
                    active = false;
                else
                {
                    c_A -= 4;
                    if (c_G >= 4)
                    {
                        c_G -= 4;
                        c_R -= 4;
                    }
                }
                break;
            case 6:
                scaleX += 0.4;
                scaleY += 0.4;

                if (c_A < 30)
                    active = false;
                else
                {
                    c_A -= 30;
                    c_G -= 30;
                    c_R -= 30;
                }
                break;
            case 7:
                if (bul_parent)
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if (bul_parent->get_subseq() >= 2)
                        active = false;
                }
                else
                    active = false;
                break;
            case 8:
            case 9:
            case 10:
                if ( get_frame() < 2 )
                {
                    sub_48C5F0( 0);
                    sub_48C640(10);
                }
                break;
            case 11:
                angZ += 2;
                if ( field_36C != 0 )
                {
                    if ( c_A < 15 )
                        active = false;
                    else
                        c_A -= 15;
                }
                else
                {
                    if ( c_A > 235 )
                        c_A = 255;
                    else
                        c_A += 20;

                    if ((chrt->get_seq() == 542 || chrt->get_seq() == 543) && (chrt->get_subseq()  <= 1 || (chrt->get_subseq() == 2 && chrt->get_frame() <= 3) ))
                    {
                        x = chrt->x;
                        y = chrt->y;
                    }
                    else
                        field_36C = 1;
                }
                break;
            default:
                active = false;
                break;
            }
            if (active)
            {
                if (process())
                    active = false;

                if (get_subseq() > 0 && get_subseq() < 7 && get_frame_time() == 0)
                    active = false;

                if ((get_subseq() == 9 || get_subseq() == 10 ) && get_elaps_frames() == 0)
                    active = false;
                else if (get_subseq() == 11 && get_elaps_frames() == 0 && get_frame() == 0 && get_frame_time() == 0)
                    active = false;
            }
        }
        break;
    case 821:
        if ( get_subseq() == 0 )
        {
            if ( sub_48C6A0(0, 3, 7) )
            {
                active = false;
                break;
            }
            v_inerc -= 1.0;
            if ( getlvl_height() >= v_inerc + y )
            {
                set_subseq(3);
                v_inerc = 0.0;
                h_inerc = 0.0;
                y = 0.0;
                break;
            }
            angZ += 8.0;
            y += v_inerc;
            x += dir * h_inerc;
        }
        if ( get_subseq() == 3 )
        {
            int32_t tmp = 2;
            if ( chrt->skills_1[6] >= 2 )
                tmp = 3;
            if ( chrt->skills_1[6] >= 4 )
                tmp++;
            if ( get_elaps_frames() % 6 == 0 && field_36C <= tmp )
            {
                chrt->play_sfx(27);
                float t[2];
                t[0] = 5.0;
                t[1] = 9.0;
                if ( chrt->skills_1[6] >= 2 )
                    t[1] = 11.0;
                if ( chrt->skills_1[6] >= 3 )
                    t[1] = 13.0;
                if ( chrt->skills_1[6] >= 4 )
                    t[1] = 18.0;
                addbullet(chrt, NULL, 821, x + dir * get_elaps_frames() * 20.0, y, dir, 1, t, 2);
                field_36C++;
            }
            if ( field_36C > tmp )
            {
                active = false;
                break;
            }
        }
        if ( get_subseq() == 5 )
        {
            v_inerc -= 0.15;
            if ( get_frame() == 1 )
                v_inerc *= 0.95;
            if ( v_inerc <= 0.5 )
                v_inerc = 0.5;
            scaleY = scaleX = 0.9 - 0.1 * (get_elaps_frames() % 3);
            sub_48C5F0( 0);
            if ( get_elaps_frames() >= 15 )
            {
                v_inerc -= 0.2;
                if ( v_inerc <= 0.5 )
                    v_inerc = 0.5;
                field_194 = 0;

                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
                c_R -= 10;
                c_G -= 10;
            }
            if ( get_elaps_frames() % 3 == 0 && get_elaps_frames() < 20 )
            {
                float t = 6.0;
                addbullet(chrt, NULL, 821, scene_rand_rngf(60) + x - 30.0, scene_rand_rngf(60) + y - 30.0, dir, 1, &t, 1);
            }
            y += v_inerc;
        }
        if ( get_subseq() == 6 )
        {
            scaleY = scaleX *= 0.98;;

            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            c_R -= 10;
            c_G -= 10;
            v_inerc += 0.05;
            y += v_inerc;
        }
        if ( get_subseq() == 7 )
        {
            scaleX += 0.1;
            scaleY += 0.1;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            c_R -= 10;
            c_G -= 10;
        }
        if ( get_subseq() == 8 )
        {
            scaleY = scaleX += 0.05;
            if ( c_A <= 8 )
            {
                active=false;
                break;
            }
            c_A -= 8;
            c_R -= 8;
            c_G -= 8;
        }
        if ( process() )
            active=false;
        break;
    case 822:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0(0, 4, 5) )
            {
                active = false;
                break;
            }
            if ( field_374 )
            {
                field_374--;
                if ( field_374 < 0 )
                    field_374 = 0;
            }
            else
            {
                char_frame *frm = chrt->get_pframe();
                if ( frm->unk22[0] == 1)
                {
                    float xx = frm->extra1[0] * chrt->dir + chrt->x - x;
                    float yy = chrt->y - frm->extra1[1] - y;

                    if ( fabs(xx) <= 100.0  && fabs(yy) <= 100)
                    {
                        field_374 = 20;
                        h_inerc = 3 * dir * chrt->dir;
                        v_inerc = 6.0;
                        scene_play_sfx(1);
                        scene_add_effect(this, 1, x, y, dir, 1);
                    }
                }
                if ( frm->unk22[0] == 2 )
                {
                    float xx = frm->extra1[0] * chrt->dir + chrt->x - x;
                    float yy = chrt->y - frm->extra1[1] - y;

                    if ( fabs(xx) <= 100.0  && fabs(yy) <= 100)
                    {
                        field_374 = 20;
                        h_inerc = 5 * dir * chrt->dir;
                        v_inerc = 9.0;
                        scene_play_sfx(2);
                        scene_add_effect(this, 2, x, y, dir, 1);
                    }
                }
                if ( frm->unk22[0] == 3 )
                {
                    float xx = frm->extra1[0] * chrt->dir + chrt->x - x;
                    float yy = chrt->y - frm->extra1[1] - y;

                    if ( fabs(xx) <= 100.0  && fabs(yy) <= 100)
                    {
                        field_374 = 20;
                        h_inerc = 8 * dir * chrt->dir;
                        v_inerc = 12.0;
                        scene_play_sfx(3);
                        scene_add_effect(this, 3, x, y, dir, 1);
                    }
                }
            }
            angZ += 8.0;
            if ( getlvl_height() < y )
                v_inerc -= 0.35;
            else
            {
                if ( h_inerc > 0.0 )
                {
                    h_inerc -= 0.1;
                    if ( h_inerc < 0.0 )
                        h_inerc = 0.0;
                }
                if ( h_inerc < 0.0 )
                {
                    h_inerc += 0.1;
                    if ( h_inerc > 0.0 )
                        h_inerc = 0.0;
                }
            }
            if ( v_inerc < 0  && getlvl_height() > y )
            {
                if ( v_inerc <= -2.0 )
                {
                    chrt->play_sfx(37);
                    h_inerc *= 0.85;
                    v_inerc *= -0.8;
                }
                else
                {
                    chrt->play_sfx(37);
                    v_inerc = 0.0;
                }
            }
            if ( dir > 0 && (( x > 1280.0 && 0.0 < h_inerc ) || ( 0.0 > x && 0.0 > h_inerc )))
            {
                chrt->play_sfx(37);
                h_inerc *= -0.8;
            }
            if ( dir < 0 && (( x > 1280.0 && 0.0 > h_inerc ) || ( 0.0 > x && 0.0 < h_inerc )) )
            {
                chrt->play_sfx(37);
                h_inerc *= -0.8;
            }
            if ( get_elaps_frames() >= 120 )
            {
                if ( shader_type == 0)
                    shader_type = 3;
                shader_cG = shader_cB = shader_cR = 4 * (get_elaps_frames() - 120);
            }
            if ( get_elaps_frames() < 180 )
            {
                x += h_inerc * dir;
                y += v_inerc;
            }
            else
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 4.0;

                scene_add_effect(this, 127, x, y, dir, -1);
                scene_add_effect(this, 127, x, y, -dir, -1);

                t[2] = 1.0;
                addbullet(chrt, NULL, 822, x, y, dir, 1, t, 3);

                t[2] = 3.0;
                addbullet(chrt, NULL, 822, x, y, dir, 1, t, 3);

                chrt->play_sfx(8);
                t[2] = 2.0;
                for(int8_t i=0; i< 6; i++)
                {
                    t[0] = scene_rand_rngf(360) - 180.0;
                    t[1] = scene_rand_rngf(50) * 0.1 + 25.0;

                    if ( t[0] >= 0.0 )
                        field_36C = -1;
                    else
                        field_36C = 1;

                    addbullet(chrt, NULL, 822, x, y, dir, field_36C, t, 3);
                }
                active=false;
            }
            break;
        case 1:
            if ( get_elaps_frames() >= 20 )
            {
                field_194 = 0;
                scaleX *= 0.92;
                scaleY *= 0.92;
                if ( c_A < 10 )
                    active = false;
                else if ( get_elaps_frames() >= 30 )
                {
                    c_A -= 10;
                    if ( c_G >= 20 )
                    {
                        c_G -= 20;
                        c_R -= 20;
                    }
                }
            }
            break;
        case 2:
            set_vec_speed( addition[0], addition[1]);
            addition[1] -= 0.5;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            x += dir * h_inerc;
            y += v_inerc * 0.25;
            scaleX += 0.01;
            scaleY += 0.01;

            if ( c_A < 10 )
                active=false;
            else
            {
                c_A -= 10;
                if ( c_G >= 20 )
                {
                    c_G -= 20;
                    c_R -= 20;
                }
            }
            break;
        case 3:
            scaleX += 0.4;
            scaleY += 0.4;
            if ( c_A < 30 )
                active = false;
            else
            {
                c_A -= 30;
                c_R -= 30;
                c_G -= 30;
            }
            break;
        default:
            break;
        }
        if (active && process())
            active = false;
        break;
    case 825:
    {
        switch(get_subseq())
        {
        case 0:
        case 1:
        case 2:
        case 3:
            if ( field_190 == 5 )
                active = false;
            else
            {

                if ( chrt->char_is_shock())
                {
                    for (int8_t i=0; i<4; i++)
                        scene_add_effect(this, 201, x, y,dir,1);
                    active = false;
                }
                else
                {
                    angZ += 8;
                    set_vec_speed(addition[0],addition[1]);
                    addition[0] *= 0.98;
                    addition[1] += 0.75;
                    if ( x > 1380.0 || x < -100 || y > 1000 || y < -400 )
                        active = false;
                    else
                    {
                        if ( get_frame_time() <= 45 && field_190 == 0 )
                        {
                            x += dir * h_inerc;
                            y += v_inerc;
                            if ( process() )
                                active = false;
                        }
                        else
                        {
                            float tmp[3];
                            tmp[0] = 0;
                            tmp[1] = 0;
                            tmp[2] = 7;
                            addbullet(chrt,NULL,825,x,y,dir,1,tmp,3);
                            set_subseq(6);
                        }
                    }
                }
            }
            break;
        case 4:
        {
            if (get_elaps_frames() % 8 == 0)
            {
                float tmp[3];
                tmp[0] = 0;
                tmp[1] = 0;
                tmp[2] = 5;
                addbullet(chrt,this, 810,x,y,dir,1,tmp,3);
            }
            if (chrt->get_seq() > 559 && chrt->get_seq() < 564)
            {
                if (chrt->get_seq() == 560 || chrt->get_seq() == 561)
                {

                    if ( chrt->get_subseq() >= 4 )
                    {
                        active = false;
                        break;
                    }
                    else if (chrt->get_subseq() == 1)
                    {
                        x = chrt->getX() - 24 * dir;
                        y = chrt->getY() + 95;
                    }
                    else if (chrt->get_subseq() == 2)
                    {
                        if ( chrt->get_frame() == 0 )
                        {
                            x = chrt->getX() - 12 * dir;
                            y = chrt->getY() + 80;
                        }
                        else if ( chrt->get_frame() == 1 )
                        {
                            x = chrt->getX() + 18 * dir;
                            y = chrt->getY() + 80;
                        }
                        else if ( chrt->get_frame() == 2 )
                        {
                            x = chrt->getX() + 36 * dir;
                            y = chrt->getY() + 85;
                        }
                        else if ( chrt->get_frame() == 3 )
                        {
                            x = chrt->getX() + 38 * dir;
                            y = chrt->getY() + 85;
                        }
                    }
                    else if ( chrt->get_subseq() == 3 )
                    {
                        x = chrt->getX() + 38 * dir;
                        y = chrt->getY() + 85;
                    }
                }
                else if (chrt->get_seq() == 562 || chrt->get_seq() == 563)
                {
                    if ( chrt->get_subseq() >= 4 )
                    {
                        active = false;
                        break;
                    }
                    else if (chrt->get_subseq() == 1)
                    {
                        x = chrt->getX() - 23 * dir;
                        y = chrt->getY() + 107;
                    }
                    else if (chrt->get_subseq() == 2)
                    {
                        if ( chrt->get_frame() == 0 )
                        {
                            x = chrt->getX() - 21 * dir;
                            y = chrt->getY() + 96;
                        }
                        else if ( chrt->get_frame() == 1 )
                        {
                            x = chrt->getX() + 15 * dir;
                            y = chrt->getY() + 95;
                        }
                        else if ( chrt->get_frame() == 2 )
                        {
                            x = chrt->getX() + 45 * dir;
                            y = chrt->getY() + 105;
                        }
                        else if ( chrt->get_frame() == 3 )
                        {
                            x = chrt->getX() + 47 * dir;
                            y = chrt->getY() + 103;
                        }
                    }
                    else if ( chrt->get_subseq() == 3 )
                    {
                        x = chrt->getX() + 47 * dir;
                        y = chrt->getY() + 103;
                    }
                }
                scaleX = scaleY = (get_elaps_frames() % 2) * 0.2 + 0.9;
            }
            else
                active = false;
        }
        break;
        case 5:
            if ( bul_parent)
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            scaleY = scaleX += 0.4;;
            if (c_A >= 30)
            {
                c_A -= 30;
                if (process())
                    active = false;
            }
            else
                active = false;
            break;
        case 6:
            scaleY = scaleX *= 0.8;
            if (get_elaps_frames() >= 30 || process())
                active = false;
            break;
        case 7:
            scaleY = scaleX += 0.4;;
            if (c_A >= 30)
            {
                c_A -= 30;
                if (process())
                    active = false;
            }
            else
                active = false;
            break;
        default:
            if (process())
                active = false;
        }
    }
    break;
    case 826:
        if ( get_subseq() == 0 || get_subseq() == 1 || get_subseq() == 6 || get_subseq() == 7 )
        {
            if ( field_36C % 3 == 0 )
                field_190 = 0;
            if ( field_36C % 6 == 0 )
            {
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 3.0;
                addbullet(chrt, this, 826, x, y, dir, 1, t, 3);
            }
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            {
                for (int8_t i=0; i< 40; i++)
                {
                    float xx = scene_rand_rngf(15) + 30.0 * i * dir + x;
                    scene_add_effect(this, 201, xx, y, dir, 1);
                }
                active=false;
                break;
            }
            if ( (chrt->get_seq() != 565 && chrt->get_seq() != 566) || chrt->get_subseq() >= 4 )
            {
                if ( (chrt->get_seq() != 567 && chrt->get_seq()) != 568 || chrt->get_subseq() >= 4 )
                {
                    if ( get_subseq() >= 2 )
                        set_subseq(8);
                    else
                        set_subseq(2);
                    break;
                }
                x = 48.0 * dir + chrt->x;
                y = chrt->y + 104.0;
            }
            else
            {
                x = 44.0 * dir + chrt->x;
                y = chrt->y + 85.0;
            }
            field_36C++;
        }

        if ( get_subseq() == 2 || get_subseq() == 8 )
        {
            field_194 = 0;
            scaleY *= 0.8;
            scaleX += 0.1;
            if ( get_elaps_frames() == 40 )
            {
                active=false;
                break;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            scaleY = scaleX += 0.3;
            if ( c_A < 20 )
            {
                active=false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 4 )
        {
            if ( get_elaps_frames() % 2 == 0 )
            {
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 5.0;
                addbullet(chrt, this, 826, x, y, dir, 1, t, 3);
            }
            if ( chrt->get_seq() <= 564 || chrt->get_seq() >= 569 )
            {
                active=false;
                break;
            }
            if ( chrt->get_seq() == 565 || chrt->get_seq() == 566 )
            {
                if ( chrt->get_subseq() >= 3 )
                {
                    active=false;
                    break;
                }
                if ( chrt->get_subseq() == 1 )
                {
                    x = chrt->x - 24.0 * dir;
                    y = chrt->y + 95.0;
                }
                if ( chrt->get_subseq() == 2 )
                {
                    if ( chrt->get_frame() == 0 )
                    {
                        x = chrt->x - 12.0 * dir;
                        y = chrt->y + 80.0;
                    }
                    else if ( chrt->get_frame() == 1 )
                    {
                        x = 18.0 * dir + chrt->x;
                        y = chrt->y + 80.0;
                    }
                    else if ( chrt->get_frame() == 2 )
                    {
                        x = 86.0 * dir + chrt->x;
                        y = chrt->y + 85.0;
                    }
                    else if ( chrt->get_frame() >= 3 )
                    {
                        x = 88.0 * dir + chrt->x;
                        y = chrt->y + 85.0;
                    }
                }
                if ( chrt->get_subseq() == 3 )
                {
                    x = 88.0 * dir + chrt->x;
                    y = 85.0 + chrt->y;
                }
            }
            if ( chrt->get_seq() == 567 || chrt->get_seq() == 568 )
            {
                if ( chrt->get_subseq() >= 3 )
                {
                    active=false;
                    break;
                }
                if ( chrt->get_subseq() == 1 )
                {
                    x = chrt->x - 23.0 * dir;
                    y = chrt->y + 107.0;
                }
                if ( chrt->get_subseq() == 2 )
                {
                    if ( chrt->get_frame() == 0 )
                    {
                        x = chrt->x - 21.0 * dir;
                        y = chrt->y + 96.0;
                    }
                    else if ( chrt->get_frame() == 1 )
                    {
                        x = 15.0 * dir + chrt->x;
                        y = 95.0 + chrt->y;
                    }
                    else if ( chrt->get_frame() == 2 )
                    {
                        x = 95.0 * dir + chrt->x;
                        y = chrt->y + 105.0;
                    }
                    else if ( chrt->get_frame() >= 3 )
                    {
                        x = 97.0 * dir + chrt->x;
                        y = chrt->y + 103.0;
                    }
                }
                if ( chrt->get_subseq() == 3 )
                {
                    x = 97.0 * dir + chrt->x;
                    y = 103.0 + chrt->y;
                }
            }
            scaleY = scaleX = (get_elaps_frames() % 2) * 0.2 + 0.9;
        }
        if ( get_subseq() == 5 )
        {
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            scaleY = scaleX += 0.4;
            if ( c_A < 30 )
            {
                active = false;
                break;
            }
            c_A -= 30;
        }
        if ( get_subseq() == 9 )
        {
            angZ = scene_rand_rngf(360);
            if ( sub_48C6A0(0, 0, 0) )
            {
                active = false;
                break;
            }
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                if ( bul_parent->field_36C )
                {
                    scaleY = scaleX *= 0.85;
                    if ( scaleX < 0.01 )
                    {
                        active=false;
                        break;
                    }
                }
                else  if ( get_elaps_frames() % 6 == 0 )
                {
                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 3.0;
                    addbullet(chrt, this, 826, x, y, dir, 1, t, 3);
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
        else  if ( get_subseq() == 11 )
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
                if ( scaleY <= 0.01 )
                {
                    active=false;
                    break;
                }
            }
        }
        else if (get_subseq() == 10)
        {
            field_378 -= 20.0;
            field_37C += addition[1];
            if ( field_36C )
            {
                addition[1] *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active=false;
                    break;
                }
            }
            else
            {
                addition[1] += 3.0;
                set_custom_box(-50, scaleY * 35.0, field_37C, scaleY * -35.0, addition[0], 0, 0);
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
                if ( sub_48C640( 2) )
                {
                    field_194 = 0;
                    field_36C = 1;
                    break;
                }
                if ( field_194 <= 0 )
                {
                    field_36C = 1;
                    break;
                }
                if ( (chrt->get_seq() == 565 || chrt->get_seq() == 566) && chrt->get_subseq() < 4 )
                {
                    x = chrt->x + 94.0 * dir;
                    y = chrt->y + 85.0;
                    if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                    {
                        for (int8_t i=0; i< 40; i++)
                        {
                            float xx = scene_rand_rngf(15) + 30.0 * i * dir;
                            scene_add_effect(this, 201, xx, y, dir, 1);
                            if (30 * i < scaleX * 256.0)
                                break;
                        }
                        active=false;
                        break;
                    }
                }
                else if ( (chrt->get_seq() == 567 || chrt->get_seq() == 568) && chrt->get_subseq() < 4 )
                {
                    x = chrt->x + 98.0 * dir;
                    y = chrt->y + 104.0;
                    if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                    {
                        for (int8_t i=0; i< 40; i++)
                        {
                            float xx = scene_rand_rngf(15) + 30.0 * i * dir;
                            scene_add_effect(this, 201, xx, y, dir, 1);
                            if (30 * i < scaleX * 256.0)
                                break;
                        }
                        active=false;
                        break;
                    }
                }
                else
                {
                    field_36C = 1;
                    break;
                }
            }
        }
        if (active && process())
            active = false;
        if ( get_subseq() == 10 )
            sub_438450(field_378, 0.0, field_37C, 256.0);
        break;
    case 827:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( get_elaps_frames() == 0 )
                tail_add(989, 5.0, 30, 1, gr_add);
            addition[0] -= 1.5;
            h_inerc = addition[0];
            v_inerc = cos_deg(field_378) * addition[1];
            field_378 += 10.0;
            if ( field_378 <= 180.0 )
            {
                if ( sub_48C6A0(0, 0, 4) )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                c_A = 0;
                if ( field_37C < 20.0 )
                {
                    active = false;
                    break;
                }
                tail_alpha(field_37C);
                field_37C -= 20.0;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            if ( scaleX < 1.0 )
            {
                scaleX += 0.2;
                if ( scaleX < 1.0 )
                    scaleY = scaleX;
                else
                {
                    scaleX = 1.0;
                    field_194 = 4;
                    scaleY = scaleX;
                }
            }
            else
            {
                sub_48C5F0(0);
                if ( field_190 )
                {
                    if ( field_190 == 4 )
                        field_194 = 0;
                    if ( field_36C >= 3 )
                    {
                        field_36C = 0;
                        field_190 = 0;
                    }
                    else
                        field_36C ++;
                }
                if ( get_elaps_frames() < 45 && field_194 > 0 )
                {
                    float t[3];
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(250) * 0.01 + 10.0;
                    t[2] = 5.0;
                    addbullet(chrt, NULL, 827, x, y, dir, 1, t, 3);
                }
                else
                {
                    field_194 = 0;
                    if ( c_A < 10 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 10;
                }
            }
            break;
        case 2:
        case 3:
            scaleX += 0.3;
            scaleY += 0.3;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            break;
        case 4:
            field_378 += 10.0;
            if ( field_378 >= 180.0 )
            {
                chrt->play_sfx(35);
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 1.0;
                addbullet(chrt, NULL, 827, x, y, dir,1, t, 3);
                t[2] = 2.0;
                addbullet(chrt, NULL, 827, x, y, dir,1, t, 3);
                t[2] = 3.0;
                addbullet(chrt, NULL, 827, x, getlvl_height(), dir,1, t, 3);

                for(int8_t i=0; i<8; i++)
                {
                    t[0] = i * 45.0;
                    t[1] = 8.0;
                    t[2] = 7.0;
                    addbullet(chrt, NULL, 827, x, y, dir,1, t, 3);
                }
                active = false;
                break;
            }
            if ( chrt->char_is_shock() )
            {
                active = false;
                break;
            }
            addition[0] -= 1.5;
            h_inerc = addition[0];
            x += h_inerc * dir;
            y += v_inerc;
            break;
        case 5:
            scaleY = scaleX *= 0.99;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            addition[1] *= 0.9;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            set_vec_speed( addition[0], addition[1]);
            x += h_inerc * dir;
            y += v_inerc;
            break;
        case 6:
            //if ( get_elaps_frames() == 0 )                                //HACK
            //tail_add(a1, 989, COERCE_UNSIGNED_INT(5.0), 30, 1, 2);
            addition[0] -= 1.5;
            h_inerc = addition[0];
            v_inerc = cos_deg(field_378) * addition[1];
            field_378 += 10.0;
            if ( field_378 <= 180.0 )
            {
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    for(int8_t i=0; i<4; i++)
                        scene_add_effect(this, 201, x, y, dir, 1);
                    active=false;
                    break;
                }
            }
            else
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                c_A = 0;
                if ( field_37C < 20.0 )
                {
                    active = false;
                    break;
                }
                tail_alpha(field_37C);
                field_37C -= 20.0;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 7:
            angZ += field_378;
            field_378 -= 0.5;
            if ( field_378 <= 2.0 )
                field_378 = 2.0;
            if ( field_36C )
            {
                addition[1] *= 0.92;
                scaleY = scaleX *= 0.95;
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
                c_B -= 10;
                c_R -= 10;
            }
            else
            {
                if ( sub_48C6A0(0, 0, 4) )
                {
                    active = false;
                    break;
                }
                addition[1] *= 0.98;
                sub_48C5F0( 5);
                if ( get_elaps_frames() > 10 )
                {
                    if ( field_194 <= 0 || (int32_t)get_elaps_frames() >= field_36E )
                    {
                        field_194 = 0;
                        field_36C = 1;
                        break;
                    }
                }
                else if ( get_elaps_frames() == 10 )
                    field_194 = 1;
            }
            set_vec_speed( addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        default:
            break;
        }
        if ( process() )
            active=false;
        break;
    case 848:
        if ( get_subseq() != 0 )
        {
            if ( get_subseq() == 1 )
            {
                if ( addition[1] == 0 && chrt->get_seq() == 307 && chrt->get_frame() > 4 )
                {
                    x = chrt->getX() + dir * 67;
                    y = chrt->getY() +  110;
                }
                else if (addition[1] == 1 && chrt->get_seq() == 308 && chrt->get_frame() > 4 )
                {
                    x = chrt->getX() + dir * 30;
                    y = chrt->getY() + 30;
                }
                else if (addition[1] == 2 && chrt->get_seq() == 408 && chrt->get_subseq() > 0)
                {
                    x = chrt->getX() + dir*106;
                    y = chrt->getY() + 103;
                }
            }
            else if (get_subseq() == 2)
            {
                h_inerc = cos_deg(addition[0]) * addition[1];
                v_inerc = -sin_deg(addition[0]) * addition[1];

                addition[1] -= 0.5;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;

                x += dir * h_inerc;
                y += v_inerc * 0.25;

                angZ += field_37C;
                scaleY = scaleX +=0.02;

                /*if ( get_elaps_frames() >= 0 )*/ //SIGN HACK
                {
                    if ( c_A <= 5 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 5;
                }
                x += dir * h_inerc;
                y += v_inerc * 0.25;
            }
        }
        else
        {
            x = chrt->getX();
            y = chrt->getY();
            if ( chrt->get_seq() != 322 && chrt->get_seq() != 418 && chrt->get_seq() != 696 )
            {
                active = false;
                break;
            }
        }
        if ( chrt->hit_stop == 0)
        {
            if ( process() )
                active = false;

            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 &&
                    (get_subseq() == 2 || get_subseq() == 1))
                active = false;

            if ( get_subseq() == 1  && get_frame_time() == 0 && get_frame() == 3) //make smoke
            {
                float t[3];
                t[0] = scene_rand_rng(360);
                t[1] = scene_rand_rng(10) * 0.1;
                t[2] = 2;
                addbullet(chrt,NULL,848,x,y,dir,1,t,3);
            }
        }
        break;
    case 849:
        if ( get_subseq() == 0 )
        {
            x = chrt->getX() + dir * 109;
            y = chrt->getY() + 84;
            if ( chrt->get_seq() != 500 || chrt->get_subseq() != 1)
            {
                active = false;
                break;
            }
        }
        else if ( get_subseq() == 1 )
        {
            x = chrt->getX() + dir * 61;
            y = chrt->getY() + 232;
            if ( (chrt->get_seq() != 520 && chrt->get_seq() != 521) || chrt->get_subseq() != 1)
            {
                active = false;
                break;
            }
        }
        else if (get_subseq() == 2)
        {
            x = chrt->getX() + dir * 61;
            y = chrt->getY() + 232;
            if  (chrt->get_seq() != 606 || chrt->get_subseq() != 1)
            {
                active = false;
                break;
            }
        }
        else if (get_subseq() == 3 || get_subseq() == 4 || get_subseq() == 5)
        {
            field_18C = 5;
            if (field_190 == 6)
            {
                field_194++;
                field_190 = 0;
            }
            else if (field_190 > 0)
            {
                field_36C++;
                if (field_36C > 5)
                {
                    field_190 = 0;
                    field_36C = 0;
                }
            }

            bul_follow_char(this, 38, 54);
            if  ((chrt->get_seq() != 525 && chrt->get_seq() != 526) || chrt->get_subseq() != 1)
            {
                active = false;
                break;
            }
        }
        if (chrt->hit_stop == 0)
            if (process())
                active = false;
        break;
    case 850:
        switch ( get_subseq() )
        {
        case 0:
            sub_48C5F0(0);
            if ( get_elaps_frames() % 3 == 0 )
            {
                field_194 = 1;
                field_190 = 0;
            }
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 87.0;
            if ( chrt->get_seq() != 600 || chrt->get_subseq() != 1 )
                next_subseq();
            if ( get_elaps_frames() > 60 )
                next_subseq();
            scaleY -= 0.01;
            break;
        case 1:
            scaleY *= 0.8;
            scaleX += 0.2;
            if ( get_elaps_frames() == 40 )
            {
                active = false;
                break;
            }
            x += 30.0 * dir;
            break;
        case 2:
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 87.0;
            if ( chrt->get_seq() != 600 || chrt->get_subseq() != 1 )
                next_subseq();
            if ( get_elaps_frames() > 40 )
                next_subseq();
            break;
        case 3:
            scaleY -= 0.01;
            scaleX -= 0.01;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            break;
        case 4:
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 87.0;
            scaleY += 0.1;
            scaleX += 0.05;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            break;
        default:
            break;
        }
        if ( active && process() )
            active=false;
        break;
    case 851:
        switch ( get_subseq() )
        {
        case 0:
            sub_48C5F0(0);
            scaleY = sin_deg(field_378);
            angZ += addition[1];
            addition[1] *= 0.9;
            if ( addition[1] > -0.3 && addition[1] < 0.0)
                addition[1] = -0.3;
            if ( addition[1] < 0.3  && addition[1] > 0.0)
                addition[1] = 0.3;
            if ( field_378 >= 90.0 )
            {
                if ( get_elaps_frames() % 3 == 0 )
                {
                    field_194 = 1;
                    field_190 = 0;
                }
                x = chrt->x + 25.0 * dir;
                y = chrt->y + 87.0;
                if ( chrt->get_seq() != 601 || chrt->get_subseq() != 1 )
                    next_subseq();
                if ( get_elaps_frames() >= 90 )
                    next_subseq();
                scaleY -= 0.01;
            }
            else
                field_378 += 9.0;
            break;
        case 1:
            angZ += addition[1];
            addition[1] *= 0.9;
            if ( addition[1] > -0.3 && addition[1] < 0.0)
                addition[1] = -0.3;
            if ( addition[1] < 0.3 && addition[1] > 0.0)
                addition[1] = 0.3;
            scaleY *= 0.8;
            scaleX += 0.2;
            if ( get_elaps_frames() == 40 )
            {
                active = false;
                break;
            }
            set_vec_speed( angZ, 30.0);
            break;
        case 802:
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 87.0;
            if ( chrt->get_seq() != 601 || chrt->get_subseq() != 1 )
                next_subseq();
            if ( get_elaps_frames() >= 90 )
                next_subseq();
            break;
        case 803:
            scaleY -= 0.01;
            scaleX -= 0.01;
            if (c_A < 10)
            {
                active = false;
                break;
            }
            c_A -= 10;
            break;
        default:
            break;
        }
        if (active && process())
            active = false;
        break;
    case 852:
        if ( get_subseq() == 0 )
        {
            sub_48C5F0(0);
            if ( scaleY >= 1.5 )
            {
                if ( get_elaps_frames() % 3 == 0 )
                {
                    field_194 = 1;
                    field_190 = 0;
                }
            }
            else
                scaleY += 0.25;
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 150.0;
            if ( chrt->get_seq() != 602 || chrt->get_subseq() != 1 )
                next_subseq();
            if ( get_elaps_frames() > 90 )
                next_subseq();
            scaleY += 0.001;
        }
        if ( get_subseq() == 1 )
        {
            scaleY *= 0.75;
            scaleX += 0.2;
            if ( get_elaps_frames() == 40 )
            {
                active = false;
                break;
            }
            set_vec_speed( -30.0, 10.0);
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 150.0;
            if ( chrt->get_seq() != 602 || chrt->get_subseq() != 1 )
                next_subseq();
            if ( get_elaps_frames() > 70 )
                next_subseq();
        }
        if ( get_subseq() == 3 )
        {
            scaleY -= 0.01;
            scaleX -= 0.01;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
        }
        if ( get_subseq() == 4 )
        {
            x = chrt->x + 25.0 * dir;
            y = chrt->y + 150.0;
            scaleY += 0.15;
            scaleX += 0.15;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            set_vec_speed( -30.0, 60.0);
            x += dir * h_inerc;
            y += v_inerc;
            angZ += 30.0;
            scaleY += 0.4;
            scaleX += 0.4;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if (active && process())
            active = false;
        break;
    case 853:
        if ( get_subseq() == 0 )
        {
            sub_48C5F0(0);
            if ( scaleY >= 1.5 )
            {
                if ( get_elaps_frames() % 3 == 0 )
                {
                    field_194 = 1;
                    field_190 = 0;
                }
            }
            else
                scaleY += 0.25;
            x = chrt->x + (chrt->h_inerc + 30.0) * dir;
            y = chrt->y + 54.0 + chrt->v_inerc;
            if ( chrt->get_seq() != 603 || (chrt->get_subseq() != 3 && chrt->get_subseq() != 2) )
                next_subseq();
            if ( get_elaps_frames() > 90 )
                next_subseq();
            angZ = chrt->field_7DC;
        }
        if ( get_subseq() == 1 )
        {
            scaleY *= 0.75;
            scaleX += 0.2;
            if ( get_elaps_frames() == 40 )
            {
                active = false;
                break;
            }
            set_vec_speed( angZ, 10.0);
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            x = chrt->x + (chrt->h_inerc + 30.0) * dir;
            y = chrt->y + 54.0 + chrt->v_inerc;
            if ( chrt->get_seq() != 603 || (chrt->get_subseq() != 3 && chrt->get_subseq() != 2 ))
                next_subseq();
            if ( get_elaps_frames() > 70 )
                next_subseq();
            angZ = chrt->field_7DC;
        }
        if ( get_subseq() == 3 )
        {
            scaleY -= 0.01;
            scaleX -= 0.01;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
        }
        if ( get_subseq() == 4 )
        {
            x = chrt->x + (chrt->h_inerc + 30.0) * dir;
            y = chrt->y + 54.0 + chrt->v_inerc;
            scaleY += 0.15;
            scaleX += 0.15;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            angZ += 30.0;
            scaleY += 0.4;
            scaleX += 0.4;
            if ( c_A <= 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 10 )
        {
            angZ += 2.0;
            if ( chrt->get_seq() != 603 )
            {
                active = false;
                break;
            }
            if ( chrt->get_subseq() )
            {
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
                c_G -= 5;
                c_R -= 5;
            }
            else
            {
                scaleY = scaleX = 1.0 - field_378;
                field_378 *= 0.8;
                float t[3];
                t[0] = angZ;
                t[1] = scaleX;
                t[2] = 11.0;
                addbullet(chrt, NULL, 853, x ,y, dir, -1, t, 3);
            }
        }
        if ( get_subseq() == 11 )
        {
            scaleY = scaleX += 0.05;
            if ( c_A <= 50 )
            {
                active = false;
                break;
            }
            c_A -= 50;
            c_G -= 50;
            c_R -= 50;
        }
        if ( process() )
            active = false;
        break;
    case 854:
        switch ( get_subseq() )
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            if ( field_36C )
            {
                v_inerc -= 0.15;
                if ( c_A < 6 )
                {
                    active = false;
                    break;
                }
                c_A -= 6;
                y += v_inerc;
            }
            else
            {
                if ( get_elaps_frames() % 30 == 0 )
                {
                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 5.0;
                    addbullet(chrt, this, 854, x, y, dir, 1, t, 3);
                }
                addition[0] += field_37C;
                field_37C -= 0.1;
                if ( field_37C < 3.0 )
                    field_37C = 3.0;
                addition[1] += field_378;
                field_378 -= 0.5;
                if ( field_378 <= 0.25 )
                    field_378 = 0.25;
                if ( chrt->get_seq() == 604)
                {
                    char_frame *frm = get_pframe();
                    x = cos_deg(-addition[0]) * addition[1] * 0.5 + frm->extra1[4] * chrt->dir + chrt->x;
                    y = sin_deg(-addition[0]) * addition[1] - frm->extra1[5] + chrt->y;
                    if (chrt->get_subseq() == 4)
                        field_36C = 1;
                }
                else
                    field_36C = 1;

                if ( cos_deg(-addition[0]) <= 0.0 )
                    order = 1;
                else
                    order = -1;
            }
            break;
        case 5:
            scaleY = scaleX += 0.025;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            c_G -= 5;
            c_R -= 5;
            if (!bul_parent)
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            break;
        case 6:
            angZ = scene_rand_rngf(360);
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            if (bul_parent->field_36C)
            {
                scaleY = scaleX *= 0.85;
                if (scaleX < 0.01)
                {
                    active = false;
                    break;
                }
            }
            break;
        case 7:
            field_378 -= 20.0;
            field_37C += field_380;
            if ( field_36C )
            {
                field_380 *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            order = bul_parent->order;
            addition[0] = sin_deg(bul_parent->addition[0]) * chrt->field_7DC;
            angZ = addition[0];
            x = cos_deg(-addition[0]) * 50.0 * dir + bul_parent->x;
            y = sin_deg(-addition[0]) * 50.0 + bul_parent->y;
            scaleY = 1.0 - cos_deg(-bul_parent->addition[0]) * 0.25;
            if ( bul_parent->field_36C == 1 )
                field_36C = 1;
            field_380 += 3.0;
            set_custom_box(0, scaleY * 35.0, field_37C, scaleY * -35.0, addition[0], 0, 0);
            sub_48C5F0( 0);
            if ( field_190 )
            {
                field_36E++;
                if ( field_36E >= 19 )
                {
                    field_194 = 1;
                    field_190 = 0;
                    field_36E = 0;
                }
            }
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            if ( bul_parent->field_36C == 1 )
                field_36C = 1;
            break;
        case 8:
            angZ = scene_rand_rngf(360);
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            order = bul_parent->order;
            x = cos_deg(-bul_parent->angZ) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin_deg(-bul_parent->angZ) * bul_parent->field_37C + bul_parent->y;
            if ( bul_parent->field_36C)
            {
                scaleX = scaleY *= 0.8;
                if (scaleY <= 0.01)
                {
                    active = false;
                    break;
                }
            }
            break;
        case 9:
            field_378 -= 20.0;
            field_37C += field_380;
            if ( field_36C )
            {
                field_380 *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                if ( !bul_parent )
                {
                    active = false;
                    break;
                }
                order = bul_parent->order;
                angZ = addition[0] = sin_deg(bul_parent->addition[0]) * chrt->field_7DC;
                x = cos_deg(-addition[0]) * 50.0 * dir + bul_parent->x;
                y = sin_deg(-addition[0]) * 50.0 + bul_parent->y;
                scaleY = 0.25 - cos_deg(-bul_parent->addition[0]) * 0.1;
                if ( bul_parent->field_36C == 1 )
                    field_36C = 1;
                field_380 += 3.0;
                if ( !bul_parent )
                {
                    active=false;
                    break;
                }
                if ( bul_parent->field_36C == 1 )
                    field_36C = 1;
            }
            break;
        default:
            break;
        }
        if (active && process() )
            active=false;
        if ( get_subseq() == 7 || get_subseq() == 9)
            sub_438450(field_378, 0.0, field_37C, 256.0);
        break;
    case 855:
        if ( get_subseq() == 0 )
        {
            x = chrt->x;
            y = chrt->y;
            if (chrt->get_seq() != 605 || get_subseq() != 1)
            {
                active = false;
                break;
            }
        }
        if (get_subseq() == 1)
        {
            x = chrt->x + 61.0 * dir;
            y = chrt->y + 232.0;
            if (chrt->get_seq() != 605 || get_subseq() != 1)
            {
                active = false;
                break;
            }
        }
        if ( !chrt->hit_stop && process() )
            active = false;
        break;
    case 856:
        if ( get_subseq() > 5 )
        {
            if ( get_frame() == 0 )
            {
                field_378 += addition[1];
                addition[1] -= 0.5;
                if ( addition[1] < 0.3 )
                    addition[1] = 0.3;
                if ( addition[3] <= get_elaps_frames() )
                {
                    next_frame();
                    float t[4];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 6.0;
                    t[3] = 0.0;
                    addbullet(chrt,this, 856, x, y, chrt->dir, 1, t,4);
                }
            }
            if ( get_frame() == 1 )
            {
                scaleY = scaleX = (get_frame_time() % 3) * 0.1 + 1.0;
                if ( get_frame_time() % 5 == 0 )
                {
                    float t[4];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 8.0;
                    t[3] = 0.0;
                    addbullet(chrt,this, 856, x, y, chrt->dir, 1, t,4);
                }
                if ( get_frame_time() == 60 )
                    next_frame();
            }
            if ( get_frame() == 2 )
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX <= 0.05 )
                {
                    active = false;
                    break;
                }
            }
            x = cos_deg((3 * get_elaps_frames()) + addition[0]) * field_378 * dir + chrt->x;
            y = sin_deg((3 * get_elaps_frames()) + addition[0]) * field_378 + chrt->y;
        }
        if ( get_subseq() == 6 || get_subseq() == 7 )
        {
            if ( bul_parent && bul_parent->get_frame() <= 1 )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            if ( get_subseq() == 7 && get_elaps_frames() > 5 )
            {
                field_194 = 0;
                field_190 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.05 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( get_subseq() == 8 )
        {
            if ( bul_parent && bul_parent->get_frame() <= 1 )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            scaleY = scaleX += 0.3;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if (active && process())
            active = false;
        break;
    case 857:
        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            h_inerc = -30.0;
            v_inerc = 9.99;
            //HACK FOR TASOFRO BUG!
            if ( x> 1380.0 || x < -100.0 || y > 1060.0 || y > -100.0)
            {
                active = false;
                break;
            }
            //END OF HACK
        }
        if ( get_subseq() == 3 )
        {
            h_inerc = 80.0;
            v_inerc = 0.0;
            if ( y <= 150.0 )
                scene_add_effect(this, 127, x, 0.0, dir, 1);

            if ( get_elaps_frames() == 0 )
            {
                float t[3];
                t[0] = scene_rand() % 80 - 40.0;
                t[1] = scene_rand() % 15 + 10.0;
                t[2] = 5.0;
                addbullet(chrt, NULL, 857, x - 83.0 * dir, y + 77.0, -dir, 1, t, 3);
            }
            if ( dir > 0 )
                if ( x > chrt->x )
                    if ( chrt->get_subseq() == 2 && chrt->get_seq() == 607)
                        chrt->h_inerc = 80.0;

            if ( dir < 0 )
                if ( x < chrt->x )
                    if ( chrt->get_subseq() == 2 && chrt->get_seq() == 607)
                        chrt->h_inerc = 80.0;

            if ( x > 2000.0 || x < -720.0 )
            {
                active = false;
                chrt->field_7D0 = 1;
                break;
            }
        }
        if ( get_subseq() == 4 )
        {
            h_inerc = 80.0;
            v_inerc = 0;
            if ( chrt->get_subseq() != 2 )
            {
                active = false;
                break;
            }
        }
        if ( get_subseq() == 5 )
        {
            addition[1] -= 0.5;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            set_vec_speed(addition[0],addition[1]);
            angZ += 12.0;
            scaleY = scaleX += 0.01;

            if (c_A <= 10)
            {
                active = false;
                break;
            }

            c_A -= 10;

            if ( x> 1380.0 || x < -100.0 || y > 1060.0 || y > -100.0)
            {
                active = false;
                break;
            }
        }
        x += h_inerc * dir;
        y += v_inerc;
        if(process())
            active = false;
        break;
    case 858:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( get_frame() == 0 && get_subseq() < 4 )
        {
            angZ += field_378;
            addition[1] += 1.0;
            set_vec_speed( addition[0], addition[1]);
            sub_48C4B0(0.0, 0.2, 100.0);
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -100.0 )
            {
                active = false;
                break;
            }
            if ( get_frame_time() % 2 == 0 )
            {
                float t[4];
                t[0] = angZ;
                t[1] = 0.0;
                t[2] = get_subseq();
                t[3] = 1.0;
                addbullet(chrt,NULL, 858, x, y, dir, 1, t, 4);
            }
            if ( field_190 == 6 )
            {
                field_190 = 0;
                field_194++;
            }
            if ( get_frame_time() > 240 || field_190 )
            {
                active=false;
                float t[4];
                t[0] = angZ;
                t[1] = 0.0;
                t[2] = get_subseq();
                t[3] = 1.0;
                addbullet(chrt, NULL, 858, x, y, dir, 1, t, 4);
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_frame() == 1 && get_subseq() < 4)
        {
            if ( c_A <= 30 )
            {
                active = false;
                break;
            }
            scaleX -= 0.05;
            scaleY -= 0.05;
            c_A -= 30;
        }
        if ( get_subseq() == 4 )
        {
            if ( c_A <= 40 )
            {
                active = false;
                break;
            }
            scaleX += 0.1;
            scaleY += 0.1;
            c_A -= 40;
        }
        if (active && process())
            active = false;
        break;
    case 859:
        if ( field_190 != 5 )
        {
            switch ( get_subseq() )
            {
            case 1:
                sub_48C5F0(0);
                sub_48C640( 0);
                break;
            case 2:
                set_vec_speed( addition[0], addition[1]);
                addition[1] -= 0.5;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;
                x += dir * h_inerc;
                y += v_inerc * 0.25;
                scaleX += 0.01;
                scaleY += 0.01;
                if ( c_A < 3 )
                {
                    active = false;
                    break;
                }
                c_A -= 3;
                break;
            case 3:
                scaleX += 0.5;
                scaleY += 0.5;
                if ( c_A < 15 )
                {
                    active = false;
                    break;
                }
                c_A -= 15;
                c_R -= 15;
                c_G -= 15;
                break;
            case 5:
                sub_48C5F0(0);
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float t[3];
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(10) + 10.0;
                    t[2] = 9.0;
                    addbullet(chrt, NULL, 859, x,y, dir, 1, t, 3);
                }
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 2 )
                    {
                        field_194 = 1;
                        field_190 = 0;
                        field_36E = 0;
                    }
                }
                if ( y > 1280.0 )
                {
                    y = 960.0;
                    x = enemy->x;
                    next_subseq();
                    addition[0] = 90.0;
                    angZ = 90.0;
                    set_vec_speed( addition[0], addition[1]);
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 6:
                sub_48C5F0(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 2 )
                    {
                        field_194 = 1;
                        field_190 = 0;
                        field_36E = 0;
                    }
                }
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float t[3];
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(10) + 10.0;
                    t[2] = 9.0;
                    addbullet(chrt, NULL, 859, x,y, dir, 1, t, 3);
                }
                if ( getlvl_height() >= y )
                {
                    scene_add_effect(this, 127, x, y, dir, -1);
                    scene_add_effect(this, 127, x, y, -dir, -1);

                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 1.0;
                    addbullet(chrt, NULL, 859, x, y, dir, 1, t, 3);
                    t[2] = 3.0;
                    addbullet(chrt, NULL, 859, x, y, dir, 1, t, 3);
                    //shake_camera(20.0); // HACK
                    chrt->play_sfx(40);
                    t[2] = 2.0;

                    for (int8_t i=0; i<20; i++)
                    {
                        t[0] = scene_rand_rngf(30) + i * 18.0;
                        t[1] = scene_rand_rngf(100) * 0.1 + 15.0;
                        int8_t ord = 1 - (sin_deg(-t[0]) > 0.0) * 2;
                        addbullet(chrt, NULL, 859, x, y, dir, ord, t, 3);
                    }
                    active=false;
                    break;
                }
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 8:
                set_vec_speed( addition[0], addition[1]);
                addition[1] *= 0.95;
                if ( addition[1] < 1.0 )
                    addition[1] = 1.0;
                v_inerc *= 0.2;
                angZ += field_37C;
                scaleX += 0.01;
                scaleY += 0.01;
                if ( c_A < 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 9:
                set_vec_speed( addition[0], addition[1]);
                addition[1] *= 0.95;
                if ( addition[1] < 1.0 )
                    addition[1] = 1.0;
                angZ += field_37C;
                scaleX += 0.01;
                scaleY += 0.01;
                if ( c_A < 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
                x += dir * h_inerc;
                y += v_inerc;
                break;
            default:
                break;
            }
        }
        else
            active = false;

        if (active && process())
            active = false;

        if (get_elaps_frames() == 0 && get_frame_time() ==0  && get_frame() == 0 && (get_subseq() == 2 || get_subseq() == 5))
            active = false;

        if ( active && get_subseq() == 1 && get_frame_time() == 0  && get_frame() == 13 )
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;
            addbullet(chrt, NULL, 859, x, y, dir, -1, t, 3);
        }
        break;
    case 861:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( get_subseq() == 0 )
        {
            angZ += field_378;
            field_378 += 0.1;
            set_vec_speed(addition[0],addition[1]);
            if ( x > 1380.0 || x < -100.0 || y > 1060.0 || y < -100.0)
            {
                active = false;
                break;
            }
            if ( get_elaps_frames() % 10 == 0 )
            {
                float tmp[4];

                tmp[0] = addition[0];
                tmp[1] = 0.0;
                tmp[2] = 1.0;
                tmp[3] = 0.0;

                addbullet(chrt, this, 861, x, y, dir, 1, tmp, 4);
            }
            sub_48C5F0(0);
            if ( field_190 != 0 )
            {
                if ( field_194 <= 0 )
                {
                    active = false;
                    chrt->play_sfx(21);

                    for(int32_t i=0; i<12; i++)
                    {
                        float tmp[4];

                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = 2.0;
                        tmp[3] = 0.0;

                        addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 4);
                    }
                    break;
                }
                if ( field_190 == 4 )
                    field_194 = 0;
                field_190 = 0;
            }
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 1 )
        {
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                hit_stop = bul_parent->hit_stop;

                if (c_A < 20)
                {
                    active = false;
                    break;
                }

                c_A -= 20;
                scaleX += 0.1;
                scaleY += 0.1;
            }
            else
            {
                if (c_A <= 30)
                {
                    active = false;
                    break;
                }

                c_A -= 30;
                scaleX += 0.25;
                scaleY += 0.25;
            }
        }
        if ( get_subseq() == 2 )
        {
            addition[1] -= 0.5;
            if (addition[1] < 0.0)
                addition[1] = 0.0;

            set_vec_speed(addition[0], addition[1]);
            angZ += field_378;
            if (c_A <= 10)
            {
                active = false;
                break;
            }
            scaleX += 0.005;
            scaleY += 0.005;
            c_A -= 10;
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 3 )
        {
            if (c_A <= 8)
            {
                active = false;
                break;
            }
            scaleY = scaleX += cos_deg(3 * get_elaps_frames()) * 0.25;
            c_A -= 8;
        }
        if ( get_subseq() == 4 )
        {
            if ( bul_parent == NULL )
            {
                active = false;
                break;
            }
            hit_stop = bul_parent->hit_stop;
            angZ -= field_378;
            field_378 += 0.1;
            if (c_A <= 128)
                c_A = 128;
            else
                c_A -= 20;
            x = bul_parent->x;
            y = bul_parent->y;
            scaleY = scaleX = cos_deg(20 * get_elaps_frames()) * 0.1 + 1.2;
        }
        if (process())
            active = false;
        break;
    case 862:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            angZ += field_378;
            v_inerc -= 0.75;
            if ( y > getlvl_height() )
            {
                if ( x > 1380.0 || x < -100.0 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                float t[3];
                t[0] = scene_rand_rngf(15) + 10.0;
                t[1] = 0.0;
                t[2] = 1.0;
                addbullet(chrt, NULL, 862, x, y, dir, 1, t, 3);
                chrt->play_sfx(38);
                active=false;
            }
            break;
        case 1:
        case 2:
            sub_48C5F0(0);
            sub_48C640(2);
            if ( get_subseq() != 2 || get_elaps_frames() < 2 )
                break;
            field_194 = 0;
            scaleX *= 0.95;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            c_G -= 15;
            c_R -= 15;
            break;
        case 3:
            scaleY = scaleX += addition[1];
            addition[1] *= 0.92;
            if ( addition[1] < 0.05 )
                addition[1] = 0.05;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            c_G -= 15;
            c_R -= 15;
            break;
        case 4:
            set_vec_speed( addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            field_378 += 0.05;
            v_inerc *= 0.2;
            v_inerc += field_378;
            angZ += field_37C;
            scaleX += 0.01;
            scaleY += 0.01;
            if ( c_A < 8 )
            {
                active = false;
                break;
            }
            c_A -= 8;
            c_R -= 8;
            c_G -= 8;
            break;
        default:
            break;
        }
        x += h_inerc * dir;
        y += v_inerc;
        if (process())
            active = false;
        break;
    case 864:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( chrt->health <= 0 || enemy->health <= 0 )
                field_36C = 1;
            angZ += 8.0;
            if ( field_374 )
            {
                field_374--;
                if ( field_374 < 0 )
                    field_374 = 0;
            }
            else
            {
                char_frame *frm = chrt->get_pframe();
                if ( frm->unk22[0] == 1)
                {
                    float xx = frm->extra1[0] * chrt->dir + chrt->x - x;
                    float yy = chrt->y - frm->extra1[1] - y;

                    if ( fabs(xx) <= 100.0  && fabs(yy) <= 100)
                    {
                        field_374 = 20;
                        h_inerc = 3 * dir * chrt->dir;
                        v_inerc = 6.0;
                        scene_play_sfx(1);
                        scene_add_effect(this, 1, x, y, dir, 1);
                    }
                }
                if ( frm->unk22[0] == 2 )
                {
                    float xx = frm->extra1[0] * chrt->dir + chrt->x - x;
                    float yy = chrt->y - frm->extra1[1] - y;

                    if ( fabs(xx) <= 100.0  && fabs(yy) <= 100)
                    {
                        field_374 = 20;
                        h_inerc = 5 * dir * chrt->dir;
                        v_inerc = 9.0;
                        scene_play_sfx(2);
                        scene_add_effect(this, 2, x, y, dir, 1);
                    }
                }
                if ( frm->unk22[0] == 3 )
                {
                    float xx = frm->extra1[0] * chrt->dir + chrt->x - x;
                    float yy = chrt->y - frm->extra1[1] - y;

                    if ( fabs(xx) <= 100.0  && fabs(yy) <= 100)
                    {
                        field_374 = 20;
                        h_inerc = 8 * dir * chrt->dir;
                        v_inerc = 12.0;
                        scene_play_sfx(3);
                        scene_add_effect(this, 3, x, y, dir, 1);
                    }
                }
            }
            if ( getlvl_height() < y )
                v_inerc -= 0.35;
            else
            {
                if ( h_inerc > 0.0 )
                {
                    h_inerc -= 0.1;
                    if ( h_inerc < 0.0 )
                        h_inerc = 0.0;
                }
                if ( h_inerc < 0.0 )
                {
                    h_inerc += 0.1;
                    if ( h_inerc > 0.0 )
                        h_inerc = 0.0;
                }
            }
            if ( v_inerc < 0  && getlvl_height() > y )
            {
                if ( v_inerc <= -2.0 )
                {
                    chrt->play_sfx(37);
                    h_inerc *= 0.85;
                    v_inerc *= -0.8;
                }
                else
                {
                    chrt->play_sfx(37);
                    v_inerc = 0.0;
                }
            }
            if ( dir > 0 && (( x > 1280.0 && 0.0 < h_inerc ) || ( 0.0 > x && 0.0 > h_inerc )))
            {
                chrt->play_sfx(37);
                h_inerc *= -0.8;
            }
            if ( dir < 0 && (( x > 1280.0 && 0.0 > h_inerc ) || ( 0.0 > x && 0.0 < h_inerc )) )
            {
                chrt->play_sfx(37);
                h_inerc *= -0.8;
            }
            if ( get_elaps_frames() >= 120 )
            {
                if ( shader_type == 0)
                    shader_type = 3;
                shader_cR = 4 * (get_elaps_frames() - 120);
                if ( get_elaps_frames() >= 184 )
                    shader_cR = 255;
                shader_cG = shader_cB = shader_cR ;
            }
            if ( get_elaps_frames() < 180 || getlvl_height() < y )
            {
                x += h_inerc * dir;
                y += v_inerc;
            }
            else
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 4.0;

                scene_add_effect(this, 127, x, y, dir, -1);
                scene_add_effect(this, 127, x, y, -dir, -1);

                t[2] = 1.0;
                addbullet(chrt, NULL, 864, x, y, dir, 1, t, 3);

                t[2] = 3.0;
                addbullet(chrt, NULL, 864, x, y, dir, 1, t, 3);

                chrt->play_sfx(40);
                //shake_camera(20.0);
                t[2] = 2.0;
                for(int8_t i=0; i< 20; i++)
                {
                    t[0] = scene_rand_rngf(30) + i * 18.0;
                    t[1] = scene_rand_rngf(100) * 0.1 + 15.0;
                    int8_t ord = 1 - (sin_deg(-t[0]) > 0.0) * 2;
                    addbullet(chrt, NULL, 864, x, y, dir, ord, t, 3);
                }
                active=false;
            }
            break;
        case 1:
            sub_48C5F0(0);
            sub_48C640( 0);
            break;
        case 2:
            set_vec_speed( addition[0], addition[1]);
            addition[1] -= 0.5;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            x += dir * h_inerc;
            y += v_inerc * 0.25;
            scaleX += 0.01;
            scaleY += 0.01;
            if ( c_A < 3 )
            {
                active = false;
                break;
            }
            c_A -= 3;
            break;
        case 3:
            scaleX += 0.5;
            scaleY += 0.5;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            break;
        default:
            break;
        }
        if ( active && process())
            active = false;

        if (get_elaps_frames() == 0 && get_frame() == 0 && get_frame_time() == 0 && (get_subseq() == 2 || get_subseq() == 5))
            active = false;

        if ( active && get_subseq() == 1 && get_frame_time() == 0 && get_frame() == 13 )
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;
            addbullet(chrt, NULL, 864, x, y, dir, -1, t, 3);
        }
        break;
    case 865:
        if (chrt->char_id == CHAR_ID_MARISA)
        {
            char_marisa *marisa = (char_marisa *)chrt;
            switch ( get_subseq() )
            {
            default:
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                if ( marisa->field_890 == 0 )
                {
                    field_36C = 0;
                    field_36E = 0;
                    field_370 = 0;
                    field_194 = 0;
                    field_190 = 0;
                }
                if ( chrt->health <= 0 || enemy->health <= 0 || marisa->field_892 <= 0 )
                {
                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 6.0;
                    addbullet(chrt, NULL, 865, x, y, chrt->dir, 1, t, 3);
                    t[2] = 7.0;
                    addbullet(chrt, NULL, 865, x, y, chrt->dir, 1, t, 3);
                    active=false;
                    break;
                }
                if ( marisa->field_890 == (int32_t)get_subseq() + 2 )
                {
                    marisa->field_890 = 1;
                    chrt->play_sfx(0);
                    float t[3];
                    t[0] = -atan2_deg(enemy->y - chrt->y, (enemy->x - chrt->x) * chrt->dir);
                    if ( t[0] > 30.0 )
                        t[0] = 30.0;
                    if ( t[0] < -30.0 )
                        t[0] = -30.0;
                    t[1] = 15.0;
                    t[2] = 8.0;
                    addbullet(chrt, NULL, 865, x, y, chrt->dir, 1, t, 3);
                    t[2] = 9.0;
                    addbullet(chrt, NULL, 865, x, y, chrt->dir, 1, t, 3);
                    t[2] = 10.0;
                    addbullet(chrt, NULL, 865, x, y, chrt->dir, 1, t, 3);
                }
                if ( marisa->field_890 == 8 &&  field_36C == 0)
                {
                    field_36C = 1;
                    if ( get_subseq() == 0 )
                        chrt->play_sfx(4);
                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 19.0;
                    addbullet(chrt, this, 865, x, y, chrt->dir, 1, t, 3);
                    t[2] = 21.0;
                    addbullet(chrt, this, 865, x, y, chrt->dir, 1, t, 3);
                }
                if ( marisa->field_890 == 50 )
                {
                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 23.0;
                    addbullet(chrt, NULL, 865, x, y, chrt->dir, -1, t, 3);
                    if ( scene_rand_rng(100) >= 90)
                    {
                        float t[3];
                        t[0] = 0.0;
                        t[1] = 0.0;
                        t[2] = 24.0;
                        float yy = scene_rand_rngf(50) + y - 25.0;
                        float xx = scene_rand_rngf(50) + x - 25.0;

                        addbullet(chrt, NULL, 865, xx, yy, dir, 1, t, 3);
                    }
                    if ( field_36E == 0 )
                    {
                        field_190 = 0;
                        field_194 = 1;
                        field_36E = 1;
                    }
                    if ( field_190 != 0 )
                    {
                        field_370++;
                        if ( field_370 >= 11 )
                        {
                            field_370 = 0;
                            field_190 = 0;
                            field_194 = 1;
                        }
                    }
                }
                if ( marisa->field_890 != 50 )
                {
                    if ( addition[1] > 120.0 )
                    {
                        addition[1] -= 0.5;
                        if ( addition[1] < 120.0 )
                            addition[1] = 120.0;
                    }
                    else
                    {
                        addition[1] += 5.0;
                        if ( addition[1] > 120.0 )
                            addition[1] = 120.0;
                    }
                    x = cos_deg(-addition[0] - marisa->field_898) * addition[1] * dir + chrt->x;
                    y = sin_deg(-addition[0] - marisa->field_898) * addition[1] + chrt->y + 100.0;
                }
                else
                {
                    addition[1] += 0.25;
                    if ( addition[1] > 180.0 )
                        addition[1] = 180.0;
                    x = cos_deg(-addition[0] - marisa->field_898) * addition[1] * dir + marisa->field_8A0;
                    y = sin_deg(-addition[0] - marisa->field_898) * addition[1] + marisa->field_8A4;
                }
                break;
            case 6:
            case 9:
                scaleY = scaleX *= 0.9;
                if ( c_A <= 10 )
                    active = false;
                else
                {
                    c_A -= 10;
                    c_R -= 10;
                    c_G -= 10;
                }
                break;
            case 7:
            case 10:
                scaleY = scaleX += 0.2;
                if ( c_A <= 10 )
                    active = false;
                else
                {
                    c_A -= 10;
                    c_R -= 10;
                    c_G -= 10;
                }
                break;
            case 8:
                sub_48C5F0(5);
                if ( sub_48C6A0(0, 0, 3) )
                {
                    active = false;
                    break;
                }
                if ( field_194 <= 0 )
                {
                    float t[3];
                    t[0] = 0.0;
                    t[1] = 0.0;
                    t[2] = 9.0;
                    addbullet(chrt, NULL, 865, x, y, dir, 1, t, 3);
                    t[2] = 10.0;
                    addbullet(chrt, NULL, 865, x, y, dir, 1, t, 3);
                    active=false;
                    break;
                }
                addition[1] += 0.1;
                set_vec_speed( addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
                if ( x > 1380.0 || x < -100.0 || y > 1060.0 || y < -100.0)
                {
                    active=false;
                    break;
                }
                break;
            case 19:
            case 20:
                if ( marisa->field_890 == 50 )
                    field_36C = 1;
                if ( bul_parent )
                {
                    x = 50 * dir + bul_parent->x;
                    y = bul_parent->y;
                    angZ = sin_deg(-bul_parent->addition[0] - marisa->field_898) * -4.0;
                }
                else
                {
                    field_36C = 1;
                    field_194 = 0;
                }
                if ( field_36C )
                {
                    field_194 = 0;
                    scaleY *= 0.9;
                    if ( c_A <= 10 )
                    {
                        active = false;
                        break;
                    }
                    else
                    {
                        c_A -= 10;
                        c_R -= 10;
                        c_G -= 10;
                    }
                }
                else
                {
                    if ( marisa->field_894 <= 0 )
                    {
                        field_36C = 1;
                        field_194 = 0;
                        break;
                    }
                    scaleY += 0.1;
                    if ( scaleY > 1.0 )
                        scaleY = 1.0;
                    sub_48C5F0( 0);
                    if ( field_190 )
                    {
                        field_36E++;
                        if ( field_36E >= 5 )
                        {
                            field_36E = 0;
                            field_194 = 1;
                            field_190 = 0;
                        }
                    }
                }
                break;
            case 21:
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                }
                else
                    field_36C = 1;

                if ( field_36C )
                {
                    scaleY *= 0.98;
                    if ( c_A <= 10 )
                    {
                        active = false;
                        break;
                    }
                    else
                    {
                        c_A -= 10;
                        c_R -= 10;
                        c_G -= 10;
                    }
                }
                else
                {
                    scaleY = scaleX = sin_deg(get_elaps_frames() * 3.0) * 0.2 + 1.0;
                    if ( c_A > 245 )
                        c_A = 255;
                    else
                        c_A += 10;
                    if ( marisa->field_894 <= 0 )
                    {
                        field_36C = 1;
                        field_194 = 0;
                        break;
                    }
                }
                break;
            case 22:
                marisa->field_8A8 = 1;
                if ( chrt->health <= 0 || enemy->health <= 0 || marisa->field_892 <= 0 )
                {
                    marisa->field_8A8 = 0;
                    active = false;
                    break;
                }
                if ( field_36C )
                {
                    addition[1] += 0.2;
                    addition[0] = -atan2_deg(chrt->y + 100.0 - y, (chrt->x - x) * dir);
                    float yy = chrt->y + 100.0 - y;
                    float xx = chrt->x - x;
                    if ( xx * xx + yy * yy <= addition[1] * addition[1] )
                    {
                        marisa->field_8A8 = 0;
                        marisa->field_890 = 0;
                        active=false;
                        break;
                    }
                }
                else
                {
                    addition[1] -= 0.15;
                    if ( addition[1] <= 0.0 )
                    {
                        addition[1] = 0.0;
                        field_36E++;
                        if ( field_36E >= 45 )
                            field_36C = 1;
                    }
                }
                set_vec_speed( addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
                marisa->field_8A0 = x;
                marisa->field_8A4 = y;
                break;
            case 23:
                scaleY = scaleX *= 0.98;
                if ( c_A < 25 )
                {
                    active = false;
                    break;
                }
                c_A -= 25;
                c_R -= 25;
                c_G -= 25;
                break;
            case 24:
                scaleY = scaleX *= 0.99;
                if ( c_A < 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
                c_R -= 5;
                c_G -= 5;
                v_inerc -= 0.1;
                y+= v_inerc;
                break;
            }
            if (active && process() )
                active=false;
        }
        break;
    case 869:
        switch ( get_subseq() )
        {
        default:
            break;
        case 1:
        case 3:
        case 5:
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            else
                field_36C = 2;

            if ( field_36C == 0 )
            {
                if ( chrt->get_seq() != 619 || chrt->get_subseq() >= 5 )
                {
                    field_36C = 2;
                    break;
                }
                sub_48C5F0(0);
                sub_48C640(0);
                if ( field_190 )
                {
                    ++field_36E;
                    if ( field_36E >= 5 )
                    {
                        field_36E = 0;
                        field_194 = 1;
                        field_190 = 0;
                    }
                }
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.99;
                scaleX += 0.2;
                if ( c_A <= 5u )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            break;
        case 2:
        case 4:
        case 6:
            scaleY += 0.2;
            scaleX += 0.05;
            if ( c_A <= 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            break;
        case 7:
            if ( field_36C )
            {
                if (c_A < 10)
                    active = false;
                else
                    c_A -= 10;
            }
            else
            {
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float t[3];
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(70) * 0.1 + 10.0;
                    t[2] = 12.0;
                    addbullet(chrt, NULL, 869, x, y, dir, 1, t, 3);
                }
                if ( chrt->get_seq() == 619 )
                {
                    x = 100 * dir + chrt->x;
                    y = chrt->y + 105.0;
                    if (get_subseq() >= 5)
                        field_36C = 1;
                }
                else
                    field_36C = 1;
            }
            break;
        case 9:
            if ( field_36C == 0 )
            {
                field_378 += addition[1];
                addition[1] *= 0.95;
                scaleY = scaleX += addition[3];
                addition[3] *= 0.8;
                if ( chrt->get_seq() == 619 )
                {
                    if ( chrt->get_subseq() == 4 )
                    {
                        addition[3] = 0.75;
                        addition[1] = 7.0;
                        field_36C = 1;
                    }
                }
                if ( chrt->get_seq() != 619 )
                {
                    field_36C = 2;
                    break;
                }
            }
            if ( field_36C == 1 )
            {
                field_378 += addition[1];
                addition[1] *= 0.9;
                scaleY = scaleX += addition[3];
                addition[3] *= 0.95;
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            if ( field_36C == 2 )
            {
                if ( c_A <= 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            if ( !bul_parent )
            {
                field_36C = 2;
                break;
            }
            else
            {
                x = cos_deg(-addition[0]) * field_378 * dir + bul_parent->x;
                y = sin_deg(-addition[0]) * field_378 + bul_parent->y;
            }
            break;
        case 10:
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            if ( field_36C == 0)
            {
                if ( chrt->get_seq() != 619 )
                {
                    field_36C = 2;
                    break;
                }
                if ( scaleY >= 0.1 )
                {
                    scaleY = 0.1;
                    field_194 = 1;
                    field_36C = 1;
                }
                else
                    scaleY += 0.005;
            }
            if ( field_36C == 1 )
            {
                if ( chrt->get_seq() != 619 )
                {
                    field_36C = 2;
                    break;
                }
                if ( chrt->get_subseq() == 4 )
                {
                    set_subseq(5);
                    float t[3];
                    t[0] = angZ;
                    t[1] = 0.0;
                    t[2] = 6.0;
                    scaleX = 4.0;
                    scaleY = 2.0;
                    field_36C = 0;
                    field_36E = 0;
                    addbullet(chrt, NULL, 869, x, y, dir, 1, t, 3);
                    chrt->play_sfx(11);
                    field_194 = 1;
                    field_190 = 0;
                    break;
                }
                sub_48C5F0(0);
                sub_48C640(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 5 )
                    {
                        field_36E = 0;
                        field_194 = 1;
                        field_190 = 0;
                    }
                }
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.99;
                scaleX += 0.2;
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            break;
        case 11:
            if ( field_36C )
            {
                {
                    active = false;
                    break;
                }
                c_A -= 10;
            }
            else
            {
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float t[3];
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(30) * 0.1 + 2.0;
                    t[2] = 12.0;
                    addbullet(chrt, NULL, 869, x, y, dir, 1, t, 3);
                }
                if ( chrt->get_seq() == 619 )
                {
                    x = chrt->x + 100.0 *dir;
                    y = chrt->y + 105.0;
                    if (chrt->get_subseq() == 4)
                    {
                        set_subseq(7);
                        break;
                    }
                }
                else
                    field_36C = 1;
            }
            break;
        case 12:
            set_vec_speed( addition[0], addition[1]);
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            if ( get_elaps_frames() >= 10 )
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
        }
        if (active && process())
            break;
        break;
    case 900:
        switch ( get_subseq() )
        {
        case 0:
        case 1:
        case 2:
        case 3:
            if ( chrt->char_is_shock() )
            {
                active = false;
                break;
            }
            else
            {
                sub_48C5F0( 20);
                angZ += field_380;
                if ( !field_36C )
                {
                    if ( chrt->get_seq() == 710 )
                    {
                        if ( chrt->get_subseq() <= 2 )
                        {
                            addition[0] += addition[3];
                            addition[1] += 1.0;
                            char_frame *frm = chrt->get_pframe();
                            x = (cos_deg(-addition[0]) * addition[1] + frm->extra1[4]) * dir + chrt->x;
                            y = sin_deg(-addition[0]) * addition[1] + chrt->y - frm->extra1[5];
                        }
                        if ( chrt->get_subseq() == 3 )
                        {
                            field_194 = 1;
                            field_190 = 0;
                            field_36C = 1;
                            addition[1] *= tan_deg(addition[3]);
                            addition[0] += 90.0;
                        }
                    }
                    if ( field_190 == 6 )
                    {
                        float t[3];
                        t[0] = 0.0;
                        t[1] = 0.0;
                        t[2] = 12.0;
                        addbullet(chrt, NULL, 900, x, y, dir, 1, t, 3);
                        active=false;
                        break;
                    }
                }
                else
                {
                    if ( field_190 )
                    {

                        float t[3];
                        t[0] = 0.0;
                        t[1] = 0.0;
                        t[2] = 12.0;
                        addbullet(chrt, NULL, 900, x, y, dir, 1, t, 3);
                        active=false;
                        break;
                    }
                    set_vec_speed( addition[0], addition[1]);
                    if ( get_elaps_frames() % 20 == 0 )
                    {
                        float t[3];
                        t[0] = scene_rand_rngf(60) + addition[0] + 150.0;
                        t[1] = scene_rand_rngf(9) + 6.0;
                        t[2] = get_subseq() + 14.0;
                        addbullet(chrt, NULL, 900, x, y, dir, 1, t, 3);
                    }
                    x += dir * h_inerc;
                    y += v_inerc;
                    if ( x > 1380.0 || x < -100.0 || y > 1060.0 || y < -100.0)
                    {
                        active = false;
                        break;
                    }
                }
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            scaleY = scaleX *= 0.9;
            if ( c_A <= 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            scaleY = scaleX += 0.05;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            break;
        case 12:
            scaleY = scaleX *= 0.98;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
            break;
        case 13:
            scaleY = scaleX += 0.2;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            break;
        case 14:
        case 15:
        case 16:
        case 17:
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            set_vec_speed( addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 18:
            if ( chrt->health <= 0 || field_194 <= 0 )
            {
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 4.0;
                addbullet(chrt, this, 900, x, y, dir, 1, t, 3);
                active=false;
                break;
            }
            if ( get_elaps_frames() % 20 == 0 )
            {
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 10.0;
                addbullet(chrt, this, 900, x, y, dir, 1, t, 3);
            }
            angZ += 2.0;
            set_vec_speed( addition[0], addition[1]);
            if ( x > 1380.0 || x < -100.0 || y > 1060.0 || y < -100.0)
            {
                active = false;
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        default:
            break;
        }
        if (active && process())
            active = false;
        break;
    case 910:
        switch ( get_subseq() )
        {
        case 0:
            if ( chrt->char_is_shock() )
            {
                active = false;
                break;
            }
            sub_48C5F0( 20);
            if ( field_190 )
            {
                float t[3];
                t[0] = 0.0;
                t[1] = 0.5;
                t[2] = 3.0;
                addbullet(chrt, NULL, 910, x, y, dir, 1, t, 3);
                t[2] = 9.0;
                addbullet(chrt, NULL, 910, x, y, dir, 1, t, 3);

                for (int8_t i=0; i<5; i++)
                {
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(10) + 10.0;
                    t[2] = 1.0;
                    addbullet(chrt, NULL, 910, x, y, dir, 1, t, 3);
                }
                active=false;
                break;
            }
            if ( get_elaps_frames() % 5 == 0 )
            {
                float t[3];
                t[0] = scene_rand_rngf(60) + 150.0 - atan2_deg(v_inerc, h_inerc);
                t[1] = scene_rand_rngf(12) + 8.0;
                t[2] = 1.0;
                addbullet(chrt, NULL, 910, x, y, dir, 1, t, 3);
            }
            int32_t v700, v701;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                v700 = 4;
                v701 = 1;
                break;
            case GAME_DIFF_HARD:
                v700 = 3;
                v701 = 1;
                break;
            case GAME_DIFF_NORMAL:
                v700 = 2;
                v701 = 1;
                break;
            case GAME_DIFF_EASY:
                v700 = 1;
                v701 = 0;
                break;
            default:
                v700 = 0; //v844
                v701 = 0; //v844
                break;
            }
            if ( field_36C < v700 )
            {
                if ( dir * h_inerc > 0.0 )
                    if ( x > 1280.0 )
                    {
                        h_inerc = -h_inerc;
                        field_36C++;
                    }
                if ( dir * h_inerc < 0.0 )
                    if ( x < 0.0 )
                    {
                        h_inerc = -h_inerc;
                        field_36C++;
                    }
                if ( v_inerc > 0.0 )
                    if ( y > 900.0 )
                    {
                        v_inerc = -v_inerc;
                        field_36C++;
                    }
            }
            if ( v_inerc < 0.0 && getlvl_height() > y )
            {
                if ( field_36C < v701 )
                    if ( field_36C < v700 )
                    {
                        v_inerc = -v_inerc;
                        field_36C++;
                    }
                angZ = -atan2_deg(v_inerc, h_inerc);
                if ( x > 1580.0 || x < -300.0 || y > 1300.0 || y < -500.0)
                    active = false;
                x += dir * h_inerc;
                y += v_inerc;
            }
            else
            {
                chrt->play_sfx(13);
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 5.0;
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_LUNA:
                    t[2] = 7.0;
                    break;
                case GAME_DIFF_EASY:
                case GAME_DIFF_NORMAL:
                    t[2] = 5.0;
                    break;
                case GAME_DIFF_HARD:
                    t[2] = 6.0;
                    break;
                default:
                    break;
                }
                //shake_camera(10.0); //HACK
                addbullet(chrt, NULL, 910, x, getlvl_height(), dir, 1, t, 3);
                t[1] = 0.5;
                t[2] = 4.0;
                addbullet(chrt, NULL, 910, x, getlvl_height(), dir, 1, t, 3);
                for (int8_t i=0; i<7; i++)
                {
                    t[0] = scene_rand_rngf(360);
                    t[1] = scene_rand_rngf(10) + 15.0;
                    t[2] = 2.0;

                    addbullet(chrt, NULL, 910, x, y, dir, 1, t, 3);
                }
                active=false;
            }
            break;
        case 1:
            set_vec_speed( addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            field_378 += 0.05;
            v_inerc += field_378;
            angZ += field_37C;
            scaleX += 0.01;
            scaleY += 0.01;
            if ( c_A < 8 )
            {
                active = false;
                break;
            }
            c_A -= 8;
            c_R -= 8;
            c_G -= 8;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 2:
            set_vec_speed( addition[0], addition[1]);
            addition[1] *= 0.95;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            field_378 += 0.05;
            v_inerc *= 0.2;
            v_inerc += field_378;
            angZ += field_37C;
            scaleX += 0.01;
            scaleY += 0.01;
            if ( c_A < 8 )
            {
                active = false;
                break;
            }
            c_A -= 8;
            c_R -= 8;
            c_G -= 8;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 3:
        case 4:
            scaleY = scaleX += addition[1];
            addition[1] *= 0.92;
            if ( addition[1] < 0.05 )
                addition[1] = 0.05;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            c_G -= 15;
            c_R -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 5:
            sub_48C5F0(0);
            sub_48C640( 0);
            if ( chrt->char_is_shock() )
                field_194 = 0;
            if ( get_elaps_frames() >= 16 ||  field_194 == 0)
            {
                field_194 = 0;
                scaleY = scaleX *= 0.95;
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
                c_R -= 10;
                c_G -= 10;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 9:
            scaleY = scaleX *= 0.95;
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            c_R -= 10;
            c_G -= 10;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 6:
            sub_48C5F0(0);
            sub_48C640( 0);
            if (chrt->char_is_shock() )
                field_194 = 0;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 7:
            sub_48C5F0(0);
            sub_48C640( 0);
            if ( chrt->char_is_shock() )
            {
                field_194 = 0;
                next_subseq();
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 8:
            field_194 = 0;
            scaleX *= 0.92;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        default:
            x += dir * h_inerc;
            y += v_inerc;
            break;
        }
        if (active && process() )
            active=false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 7 )
            active=false;
        break;
    case 920:
        switch ( get_subseq() )
        {
        case 1:
            angZ += 2.0;
            scaleY = scaleX *= 0.92;
            if ( c_A < 15 )
            {
                active = false;
                break;
            }
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            set_vec_speed( addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 2:
            angZ += 2.0;
            if ( field_36C )
            {
                scaleY = scaleX *= 0.92;
                if ( c_A < 20 )
                {
                    active = false;
                    break;
                }
                c_A -= 20;
                c_R -= 20;
                c_G -= 20;
            }
            else
            {
                if ( field_190
                        || get_elaps_frames() >= addition[3]
                        || chrt->char_is_shock() )
                {
                    field_36C = 1;
                    field_194 = 0;
                    break;
                }
                addition[1] *= 0.98;
                if ( addition[1] < 1.0 )
                    addition[1] = 1.0;
            }
            set_vec_speed( addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 3:
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                angZ = bul_parent->angZ;
            }
            scaleY = scaleX += 0.3;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
            break;
        case 4:
            if ( get_elaps_frames() % 2 == 0 )
            {
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 5.0;
                addbullet(chrt, this, 920, x, y, dir, 1, t, 3);
            }
            if ( chrt->get_seq() > 730 || chrt->get_seq() < 732 )
            {
                active = false;
                break;
            }
            if ( chrt->get_seq() == 730 || chrt->get_seq() == 731 )
            {
                if ( chrt->get_subseq() >= 4 )
                {
                    active = false;
                    break;
                }
                char_frame *frm = chrt->get_pframe();
                x = frm->extra1[4] * chrt->dir + chrt->x;
                y = -frm->extra1[5] + chrt->y;
            }
            scaleY = scaleX = (get_elaps_frames() % 2) * 0.2 + 0.9;
            break;
        case 5:
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            scaleY = scaleX += 0.4;
            if ( c_A < 30 )
            {
                active = false;
                break;
            }
            c_A -= 30;
            break;
        case 6:
            if ( field_36C )
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                c_A -= 10;
                c_B -= 10;
                c_R -= 10;
            }
            else
            {
                if ( c_A > 205 )
                {
                    c_A = -1;
                    field_36C = 1;
                }
                else
                {
                    c_A += 50;
                }
            }
            scaleY = scaleX += 0.02;
            break;
        case 9:
            angZ = scene_rand_rngf(360);
            if ( chrt->char_is_shock() )
            {
                active = false;
                break;
            }
            if ( bul_parent )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                if ( !bul_parent->field_36C )
                {
                    if ( get_elaps_frames() % 6 == 0 )
                    {
                        float t[3];
                        t[0] = 0.0;
                        t[1] = 0.0;
                        t[2] = 3.0;
                        addbullet(chrt, this, 920, x, y, dir, 1, t, 3);
                    }
                    break;
                }
            }
            scaleY = scaleX *= 0.85;
            if ( scaleX < 0.01 )
                active=false;
            break;
        case 10:
            field_378 -= 20.0;
            field_37C += addition[1];
            if ( field_37C > 1380.0 )
                field_37C = 1380.0;
            if ( field_36C )
            {
                addition[1] *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active=false;
                    break;
                }
                break;
            }
            addition[1] += 3.0;
            set_custom_box(0, scaleY * 35.0, field_37C, scaleY * -35.0, addition[0], 0, 0);
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
            sub_48C640( 0);
            sub_48C5F0( 0);
            float t[4];
            int32_t frames;
            frames = 1;
            t[3] = 0.0;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                frames = 2;
                t[3] = 120.0;
                break;
            case GAME_DIFF_HARD:
                frames = 3;
                t[3] = 60.0;
                break;
            case GAME_DIFF_NORMAL:
                frames = 6;
                t[3] = 30.0;
                break;
            case GAME_DIFF_EASY:
                frames = 0;
                break;
            default:
                break;
            }
            if (frames != 0)
            {
                if ( get_elaps_frames() % frames == 0 )
                {
                    t[0] = scene_rand_rngf(40) - 20.0;
                    t[1] = scene_rand_rngf(9) + 6.0;
                    t[2] = 2.0;
                    float xx = scene_rand_rngf(field_37C) * dir + x;
                    float yy = y + 10.0 - scene_rand_rngf(20);

                    addbullet(chrt, NULL, 920, xx, yy, dir,1, t, 4);
                }
                break;
            }
            if ( chrt->get_seq() < 730 || chrt->get_seq() > 732 )
            {
                active = false;
                break;
            }
            if ( chrt->get_seq() == 730 || chrt->get_seq() == 731 )
            {
                if ( chrt->get_subseq() >= 4 )
                {
                    field_36C = 1;
                }
                else
                {
                    char_frame *frm = chrt->get_pframe();
                    x = frm->extra1[4] * dir + chrt->x;
                    y = chrt->y - frm->extra1[5];
                }
            }
            if ( chrt->char_is_shock() )
            {
                active=false;
                break;
            }
            break;
        case 11:
            angZ = scene_rand_rngf(360);
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            x = cos_deg(-bul_parent->angZ) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin_deg(-bul_parent->angZ) * bul_parent->field_37C + bul_parent->y;
            if ( !bul_parent->field_36C )
            {
                active = false;
                break;
            }
            scaleY = scaleX *= 0.8;
            if (scaleY < 0.01)
            {
                active = false;
                break;
            }
            break;
        case 12:
            field_378 -= 20.0;
            field_37C += addition[1];
            if ( field_36C )
            {
                addition[1] *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active=false;
                    break;
                }
            }
            else
            {
                addition[0] = chrt->angZ;
                angZ = chrt->angZ;
                float v774 = tan_deg(90.0 - addition[0]) * y;
                field_380 = sqrt(y * y + v774 * v774);
                if ( field_37C > field_380 )
                    field_37C = field_380;

                addition[1] += 3.0;
                set_custom_box(0, scaleY * 35.0, field_37C, scaleY * -35.0, addition[0], 0, 0);
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
                sub_48C640( 0);
                sub_48C5F0( 0);

                if ( get_elaps_frames() % 2 == 0 )
                {
                    float t[3];
                    t[0] = scene_rand_rngf(120) - 60.0 + addition[0];
                    t[1] = scene_rand_rngf(5) + 10.0;
                    t[2] = 1.0;
                    addbullet(chrt, NULL, 920, x, y, dir, 1, t, 3);
                }
                int32_t frames = 0;
                float t[4];
                t[3] = 0.0;
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_LUNA:
                    frames = 2;
                    t[3] = 300.0;
                    break;
                case GAME_DIFF_HARD:
                    frames = 3;
                    t[3] = 240.0;
                    break;
                case GAME_DIFF_NORMAL:
                    frames = 6;
                    t[3] = 180.0;
                    break;
                case GAME_DIFF_EASY:
                    frames = 0;
                    t[3] = 0.0;
                    break;
                default:
                    break;
                }
                float xx = cos_deg(-addition[0]) * field_37C * dir + x;
                float yy = sin_deg(-addition[0]) * field_37C + y;
                if (xx < 1380 && xx > -100 && y <= 20.0)
                {
                    if ( frames && get_elaps_frames() % frames == 0 )
                    {
                        t[0] = -scene_rand_rngf(80) - 40.0;
                        t[1] = scene_rand_rngf(22) + 3.0;
                        t[2] = 2.0;
                        addbullet(chrt, NULL, 920, xx, yy, dir, 1, t, 4 );
                    }
                    if ( get_elaps_frames() % 3 == 0 )
                    {
                        t[0] = 0.0;
                        t[1] = 0.0;
                        t[2] = 6.0;
                        addbullet(chrt, NULL, 920, xx, yy, dir, -1, t, 3);
                    }
                }
                if ( chrt->get_seq() != 733 )
                {
                    active = false;
                    break;
                }
                if ( chrt->get_subseq() < 6 )
                {
                    char_frame *frm = chrt->get_pframe();
                    x = (cos_deg(-addition[0]) * 200.0 + frm->extra1[4]) * dir + chrt->x;
                    y = sin_deg(-addition[0]) * 200.0 - frm->extra1[5] + chrt->y;
                }
                else
                    field_36C = 1;

                if ( chrt->char_is_shock() )
                {
                    active=false;
                    break;
                }
            }
            break;
        default:
            break;
        }
        if (active && process() )
            active=false;

        if (get_subseq() == 12)
            sub_438450(field_378, 0.0, field_37C, 256.0);
        break;
    case 970:
        if ( get_subseq() <= 7 )
        {
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( chrt->char_is_shock() )
                field_36C = 2;
            if ( !field_36C )
            {
                if ( c_A > 240 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 15;
                x = cos_deg(-addition[0]) * addition[1] * dir + field_37C;
                y = sin_deg(-addition[0]) * addition[1] + field_380;
            }
            if ( field_36C == 1 )
            {
                field_36E++;
                x = cos_deg(-addition[0]) * addition[1] * dir + field_37C;
                y = sin_deg(-addition[0]) * addition[1] + field_380;
                field_36C = 2;
            }
            if ( field_36C == 2 )
            {
                x = cos_deg(-addition[0]) * addition[1] * dir + field_37C;
                y = sin_deg(-addition[0]) * addition[1] + field_380;
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
        }
        if (active && process() )
            active=false;
        break;
    case 980:
        //sub_48C190(a1); //HACK
        if (active && process() )
            active=false;
        break;
    case 989:
        if ( chrt->get_seq() < 300 )
        {
            active = false;
            break;
        }
        if ( chrt->hit_stop > 0 )
            break;
        if ( get_subseq() == 0 )
        {
            x = dir * addition[0] + chrt->x;
            y = chrt->y + addition[1];
            scaleX += 0.001;
            scaleY += 0.001;
            if ( c_B >= 250 )
            {
                c_B = 255;
                c_G += 4;
            }
            else
                c_B += 5;

            if ( get_elaps_frames() >= 120 )
            {
                set_subseq(2);
                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 3.0;
                addbullet(chrt,this, 989, x, y, dir, 1, t, 3);
                c_B = 255;
                c_G = 255;
                c_R = 255;
                break;
            }
        }
        if ( get_subseq() == 1 )
        {
            if (c_A >= 250)
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
        if (active && process() )
            active=false;
        break;
    case 990:
        x = chrt->x - 82 * dir;
        y = chrt->y + 132.0;
        if ( (chrt->get_seq() == 600 && chrt->get_subseq() == 1)
                || (chrt->get_seq() == 601 && chrt->get_subseq() == 1)
                || (chrt->get_seq() == 602 && chrt->get_subseq() == 1)
                || (chrt->get_seq() == 619 && (chrt->get_subseq() == 4 || chrt->get_subseq() == 5))
                || (chrt->get_seq() == 731 && (chrt->get_subseq() == 1 || chrt->get_subseq() == 2))
                || (chrt->get_seq() == 733 && (chrt->get_subseq() == 1 || chrt->get_subseq() == 2)) )
        {
            if (process() )
                active=false;
        }
        else
            active = false;
        break;
    case 998:
        angZ += 5.0;
        if ( get_subseq() == 0)
        {
            if (chrt->get_seq() >= 150 && chrt->get_seq() < 154)
            {
                x = chrt->x + 57 * chrt->dir;
                y = chrt->y + 94;
                dir = chrt->dir;
            }
            else if (chrt->get_seq() >= 154 && chrt->get_seq() < 158)
            {
                x = chrt->x + 57 * chrt->dir;
                y = chrt->y + 60;
                dir = chrt->dir;
            }
            else if (chrt->get_seq() == 158)
            {
                x = chrt->x + 57 * chrt->dir;
                y = chrt->y + 100;
                dir = chrt->dir;
            }
            else
            {
                next_subseq();
                chrt->bbarrier_show = false;
            }
        }
        else if ( get_subseq() == 1)
        {
            if (c_A >= 10)
                c_A -= 10;
            else
                active = false;

        }

        if (active && process())
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
            active=false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = 15.0;
            v_inerc = 15.0;
            v_force = 0.2;
        }
        break;
    default:
        if (process())
            active = false;
    }
}

void marisa_bullets::set_seq_params()
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
        scaleY = scaleX = 2.0;
        field_194 = 1;
        angZ = addition[0];

        set_subseq(addition[2]);

        if ( get_subseq() == 0 )
        {
            //if ( addition[3] != 0 )
            //tail_add(v2, 989, COERCE_UNSIGNED_INT(15.0), 5, 1, 2); //HACK
        }

        if ( get_subseq() > 1 && get_subseq() < 6)
            scaleY = scaleX = 1.0;

        if ( get_subseq() == 7 )
        {
            scaleY = scaleX = scene_rand_rng(200) * 0.01 + 2.0;
            angZ = scene_rand_rng(360);
            addition[1] = scene_rand_rng(15) * 0.1 + 10.0;
        }
        break;
    case 801:
        field_194 = 1;
        set_subseq(addition[2]);

        if ( get_subseq() == 0 || get_subseq() == 1)
        {
            tail_add(989, 20.0, 6, 2, gr_add);
        }
        else if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rng(80) + addition[0] - 40.0;
        }
        else if ( get_subseq() == 3 )
            field_194 = 3;
        else if ( get_subseq() == 4 )
            field_194 = 5;
        else if ( get_subseq() == 5 )
        {
            scaleY = scaleX = scene_rand_rng(200) * 0.01 + 2.0;
            angZ = scene_rand_rng(360);
            addition[1] = scene_rand_rng(15) * 0.1 + 10.0;
            addition[0] = scene_rand_rng(360);
        }
        break;
    case 802:

        field_194 = 1;
        set_subseq(addition[2]);

        if ( get_subseq() == 0 )
        {
            h_inerc = addition[1] * 6.0 + 6.0;
            v_inerc = addition[1] * 6.0 + 12.5;
        }
        else if ( get_subseq() == 2 ||  get_subseq() == 3 )
        {
            field_378 = scene_rand_rng(10) - 5.0;
            scaleY = scaleX = scene_rand_rng(200) * 0.01 + 1.0;
            angZ = scene_rand_rng(360);
            addition[1] = scene_rand_rng(15) * 0.1 + 15.0;
            addition[0] = scene_rand_rng(360);
        }
        break;
    case 803:
        field_194 = 10;
        set_subseq(addition[2]);
        if ( get_subseq() <= 2 )
            x_off = -40.0;
        else if ( get_subseq() == 4 )
        {
            sub_438450(0.0, 0.0, 0.0, 256.0);
            field_194 = 10;
            float t[3];
            t[0] = 0;
            t[1] = 0;
            t[2] = 3;
            addbullet(chrt,this,803,x,y,dir,1,t,3);
            t[2] = 5;
            addbullet(chrt,this,803,x,y,dir,1,t,3);
            set_real_size(0,0);
            sub_438450(0.0, 0.0, 0.0, 256.0);
            field_380 = 35.0;
        }
        break;
    case 804:
        field_194 = 1;
        break;
    case 809:
        scaleY = scaleX = addition[1];
        c_A = 128;
        set_subseq(addition[2]);
        angZ = addition[0];
        break;
    case 810:
        angZ = scene_rand_rng(360);
        set_subseq(addition[2]);
        scaleY = scaleX = scene_rand_rng(50) * 0.01 + 0.5;
        break;
    case 811:
        field_18C = 4;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_378 = 5.0;
            field_194 = 1;
            for (int8_t i=0; i < 16; i++)
            {
                float t[4];
                t[0] = 80.0 - scene_rand_rngf(160);
                t[1] = scene_rand_rngf(250) * 0.1 + 10.0;
                t[2] = 3.0;
                t[3] = scene_rand_rngf(45);
                addbullet(chrt, NULL, 811, x, y, dir, 1, t, 4);
            }
            float t[4];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;
            t[3] = 0.0;
            addbullet(chrt, NULL, 811, x, y, dir, 1, t, 4);
            set_vec_speed(addition[0], addition[1]);
            angZ = addition[0];
        }
        if ( get_subseq()== 2 )
            field_378 = 1.0;
        if ( get_subseq()== 3 )
        {
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(100) * 0.04 + 1.0;
            field_378 = scene_rand_rngf(20) - 10.0;
            field_37C = scene_rand_rngf(20) + 5.0;
        }
        if ( get_subseq()== 4 )
            field_378 = 1.0;
        if ( get_subseq()== 5 )
        {
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 812:
        field_18C = 8;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq()== 2 )
            field_194 = 4;
        if ( get_subseq()== 3 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(11) - 5.0;
            scaleY = scaleX = scene_rand_rngf(10) * 0.1 + 0.5;;
        }
        if ( get_subseq() == 4 || get_subseq()== 6 )
        {
            field_194 = 4;
            angZ = addition[0];
        }
        break;
    case 817:
        field_18C = 9;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            set_vec_speed(addition[0], addition[1]);
        if ( get_subseq()== 1 || get_subseq()== 6 )
            field_194 = 6;
        if ( get_subseq()== 5 )
        {
            scaleY =scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 820:
        field_18C = 2;
        field_194 = 1;
        set_subseq(addition[2]);
        if (addition[2] == 0 )
        {
            h_inerc = addition[1] * 6 + 3;
            v_inerc = addition[1] * 6 + 6;
            field_138 = -6;
            has_shadow = 1;
            float tmp[3];
            tmp[0] = 0;
            tmp[1] = 0;
            tmp[2] = 7;
            addbullet(chrt, this, 820,x,y,dir,-1,tmp,3);
            field_138 = -6;
            has_shadow = 1;
        }
        else if (addition[2] == 1 )
        {
            h_inerc = 5;
            v_inerc = -25;
            has_shadow = 1;
            field_138 = -6;
            float tmp[3];
            tmp[0] = 0;
            tmp[1] = 0;
            tmp[2] = 7;
            addbullet(chrt, this, 820,x,y,dir,-1,tmp,3);
        }
        else if (addition[2] == 5)
        {
            scaleX = scaleY = scene_rand_rng(100) * 0.01 + 1;
            angZ = scene_rand_rng(360);
        }
        else if ( addition[2] == 11 )
        {
            angX = 80;
            c_A = 0;
        }
        break;
    case 821:
        field_18C = 6;
        field_194 = 1;
        set_subseq(addition[0]);
        if ( get_subseq()<= 2 )
        {
            h_inerc = 6.0;
            v_inerc = 4.5;
            h_inerc = addition[1];
            has_shadow = 1;
            v_inerc = addition[2];
            field_138 = -6.0;
        }
        if ( get_subseq()== 5 )
        {
            v_inerc = addition[1];
            float t = 7.0;
            addbullet(chrt, NULL, 821, x, y, dir, 1, &t, 1);
            t = 8.0;
            addbullet(chrt, NULL, 821, x, y, dir, -1, &t, 1);
        }
        if ( get_subseq() == 6 )
            v_inerc = 0.0;
        break;
    case 822:
        field_18C = 10;
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
        {
            h_inerc = addition[0];
            has_shadow = 1;
            v_inerc = addition[1];
            field_138 = -6.0;
        }
        if ( get_subseq()== 1 )
            field_194 = 1;
        if ( get_subseq()== 2 )
        {
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 825:
        field_18C = 3;
        field_194 = 1;
        set_subseq(addition[2]);
        //if ( addition[2] <= 3 )
        //tail_add(v2, addition[2] + 991, COERCE_UNSIGNED_INT(20.0), 6, 2, 2); //HACK
        field_36C = 0;
        break;
    case 826:
        field_18C = 7;
        field_194 = 10;
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
        {
            setOrigin(-60.0, 0.0);
            scaleY = 1.2;
        }
        if ( get_subseq()== 6 )
        {
            setOrigin(-60.0, 0.0);
            scaleY = 1.8;
        }

        if ( get_subseq()== 10 )
        {
            sub_438450(0.0, 0.0, 0.0, 256.0);
            scaleX = 1.0;
            scaleY = addition[0];
            field_194 = 10;
            float t[3];
            t[0] = addition[0];
            t[1] = 0.0;
            t[2] = 9.0;
            addbullet(chrt, this, 826, x, y, dir, 1, t, 3);
            t[2] = 11.0;
            addbullet(chrt, this, 826, x, y, dir, 1, t, 3);
            sub_438450(0.0, 0.0, 0.0, 256.0);
        }
        if ( get_subseq()== 9 || get_subseq()== 11 )
            scaleY = scaleX = addition[0];
        break;
    case 827:
        field_37C = 255.0;
        field_18C = 11;
        set_subseq(addition[2]);
        field_190 = 0;
        if ( get_subseq()== 1 )
        {
            scaleX = 0.0;
            scaleY = 0.0;
        }
        if ( get_subseq()== 5 )
        {
            scaleY = scaleX = scene_rand_rngf(150) * 0.01 + 1.0;
        }
        if ( get_subseq() == 7 )
        {
            field_378 = 20.0;
            field_36E = 10 * (chrt->skills_1[11] + 1);
            set_vec_speed(addition[0], addition[1]);
        }
        break;
    case 848:
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 2 )
        {
            if ( scene_rand_rng(100) >= 50 )
                field_37C = -1.0;
            else
                field_37C = 1.0;
        }
        break;
    case 849:
        angZ = addition[0];
        set_subseq(addition[2]);

        if (get_subseq() == 2)
            scaleY = scaleX = 2.0;
        else if (get_subseq() == 3 || get_subseq() == 4 || get_subseq() == 5)
        {
            field_18C = 5;
            field_194 = 5;
        }

        break;
    case 850:
        field_194 = 1;
        scaleX = 3.0;
        scaleY = 1.5;
        set_subseq(addition[2]);
        if ( get_subseq() == 2 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
        }
        break;
    case 851:
        scaleX = 10.0;
        scaleY = 0;
        set_subseq(addition[2]);
        if ( get_subseq() == 2 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
        }
        break;
    case 852:
        scaleX = 4.0;
        scaleY = 0.0;
        angZ = -30.0;
        set_subseq(addition[2]);
        if ( get_subseq()== 2 )
        {
            scaleX = 3.0;
            scaleY = 3.0;
        }
        if ( get_subseq() == 5 )
        {
            scaleX = 1.0;
            scaleY = 1.0;
            angX = scene_rand_rngf(20) - 50.0;
            angY = scene_rand_rngf(20) + 50.0;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 853:
        scaleX = 4.0;
        scaleY = 0.0;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq()== 4 )
        {
            /*sub_465E50(&meta, 995);
            field_154->field_F8 = 22.0;
            field_154->field_FC = 22.0;
            *(float *)&field_154->field_E8 = 640.0;
            *(float *)&field_154->field_EC = 0.0;
            LOBYTE(field_154->field_104) = dir;*/
        }
        if ( get_subseq()== 2 )
        {
            scaleX = 3.0;
            scaleY = 3.0;
        }
        if ( get_subseq()== 5 )
        {
            scaleX = 1.0;
            scaleY = 1.0;
            angX = dir * addition[0];
            angY = scene_rand_rngf(20) + 50.0;
            angZ = scene_rand_rngf(360);
        }
        if ( get_subseq()== 10 )
        {
            field_360 = 1;
            field_378 = 1.0;
            scaleX = 0.0;
            scaleY = 0.0;
            angX = 75.0;
        }
        if ( get_subseq()== 11 )
        {
            field_360 = 1;
            scaleY = scaleX = addition[1];
            angX = 75.0;
        }
        break;
    case 854:
        set_subseq(addition[2]);
        if ( get_subseq() <= 4 )
        {
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 7.0;

            addbullet(chrt, this, 854, x + dir * 50.0, y, dir, 1, t, 3);
            t[2] = 9.0;
            addbullet(chrt, this, 854, x + dir * 50.0, y, dir, 1, t, 3);
            field_378 = 10.0;
            field_37C = 7.5;
        }
        if ( get_subseq() == 5 )
        {
            angX = scene_rand_rngf(100) - 50.0;
            angY = scene_rand_rngf(100) - 50.0;
        }
        if ( get_subseq() == 7 )
        {
            sub_438450(0.0, 0.0, 0.0, 256.0);
            scaleX = 1.0;
            field_194 = 1;
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 6.0;
            addbullet(chrt, this, 854, x, y, dir, 1, t, 3);
            t[2] = 8.0;
            addbullet(chrt, this, 854, x, y, dir, 1, t, 3);
            field_380 = 15.0;
        }
        if ( get_subseq() == 9 )
        {
            sub_438450(0.0, 0.0, 0.0, 256.0);
            scaleX = 1.0;
            scaleY = 0.2;
            field_380 = 15.0;
        }
        break;
    case 855:
        angZ = addition[0];
        set_subseq(addition[2]);
        break;
    case 856:
        set_subseq(addition[2]);
        if ( get_subseq() == 6 )
        {
            field_190 = 0;
            field_194 = 1;
        }
        break;
    case 857:
        field_360 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 4 )
        {
            field_194 = 1;
            field_190 = 0;
        }
        if ( get_subseq() == 5 )
            angZ = scene_rand_rng(360);
        break;
    case 858:
        if ( scene_rand_rngf(100) > 50 )
            field_378 = -8.0;
        else
            field_378 = 8.0;
        set_subseq(addition[2]);
        set_frame(addition[3]);
        if ( get_subseq() < 4 )
        {
            if ( get_frame() == 0 )
            {
                angZ = scene_rand_rngf(360);
                float t[4];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 4.0;
                t[3] = get_subseq();
                field_194 = 1;
                field_190 = 0;
                addbullet(chrt,NULL, 858, x, y, dir, 1, t, 4);
            }
            if ( get_frame() == 1 )
                angZ = addition[0];
        }
        break;
    case 859:
        set_subseq(addition[2]);
        if ( get_subseq() == 1 )
            field_194 = 1;
        if ( get_subseq() == 2 )
        {
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
        }
        if ( get_subseq() == 5 )
        {
            set_vec_speed(addition[0], addition[1]);
            angZ = addition[0];
            field_194 = 1;
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 7.0;
            addbullet(chrt, NULL, 859, x, y, dir, 1, t, 3);
            scaleX = scaleY = 1.5;
        }
        if (  get_subseq() == 8 )
        {
            field_37C = scene_rand_rngf(9) - 4.0;
            scaleX = scaleY = scene_rand_rngf(50) * 0.01 + 0.75;
            angZ = scene_rand_rngf(360);
        }
        if (  get_subseq() == 9 )
        {
            field_37C = scene_rand_rngf(9) - 4.0;
            scaleX = scaleY = scene_rand_rngf(50) * 0.01 + 0.75;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 861:
        set_subseq(addition[2]);
        set_frame(addition[3]);
        if ( get_subseq() == 0 )
        {
            field_378 = 5.0;
            field_194 = 6;

            float tmp[4];
            tmp[0] = addition[0];
            tmp[1] = 0.0;
            tmp[2] = 3.0;
            tmp[3] = 0.0;

            addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 4);

            tmp[2] = 4.0;
            tmp[3] = 0.0;

            addbullet(chrt, this, 861, x ,y ,dir, 1, tmp, 4);
        }
        else if ( get_subseq() == 1 )
            angZ = addition[0];
        else if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rng(360);
            scaleY = scaleX = scene_rand_rng(100) * 0.01 + 0.5;
            addition[0] = scene_rand_rng(360);
            addition[1] = scene_rand_rng(30) + 10;
            field_378 = scene_rand_rng(20) - 10.0;
            field_37C = scene_rand_rng(20) + 5.0;
        }
        else if (get_subseq() == 3)
            angZ = addition[0];
        else if (get_subseq() == 4)
            field_378 = 5.0;
        break;
    case 862:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(20) * 0.1 + 4.0;
            h_inerc = addition[0];
            has_shadow = 1;
            v_inerc = addition[1];
            field_138 = -6.0;
        }
        if ( get_subseq() == 1 )
        {
            field_194 = 1;
            angZ = addition[0];
            float t[3];
            for (int8_t i=0; i < 8; i++)
            {
                t[0] = scene_rand_rngf(20) + i * 45.0;
                t[1] = scene_rand_rngf(5) + 20.0;
                t[2] = 4.0;
                int8_t ord = 1 - 2 * (sin_deg(-t[0]) > 0 );
                addbullet(chrt, NULL, 862 ,x ,y, dir, ord, t, 3);
            }
            t[1] = 0.75;
            t[2] = 3.0;

            addbullet(chrt,NULL, 862, x, y, dir, -1, t, 3);
        }
        if ( get_subseq()== 3 )
            angX = 80.0;
        if ( get_subseq()== 4 )
        {
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
            field_37C = scene_rand_rngf(10) - 5.0;
        }
        break;
    case 864:
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
        {
            h_inerc = addition[0];
            has_shadow = 1;
            v_inerc = addition[1];
            field_138 = -6.0;
        }
        if ( get_subseq()== 1 )
            field_194 = 1;
        if ( get_subseq()== 2 )
        {
            scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 865:
        set_subseq(addition[2]);
        if ( get_subseq()== 8 )
        {
            field_194 = 1;
            angZ = addition[0];
        }
        if ( get_subseq() == 19 )
        {
            scaleX = 2.0;
            field_194 = 1;
            if ( bul_parent )
            {
                char_marisa *marisa = (char_marisa *)chrt;
                angZ = sin_deg(-bul_parent->addition[0] - marisa->field_898) * -4.0;
            }
            scaleY = 0.1;
        }
        if ( get_subseq() == 24 )
        {
            angZ = scene_rand_rngf(360);
            scaleY = scaleX += scene_rand_rngf(10) * 0.1;
        }
        break;
    case 869:
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq()== 1 || get_subseq()== 3 || get_subseq()== 5 )
            scaleX = 10.0;
        if ( get_subseq()== 2 )
            scaleX = 10.0;
        if ( get_subseq()== 4 )
            scaleX = 6.0;
        if ( get_subseq()== 6 )
            scaleX = 4.0;
        if ( get_subseq()== 10 )
        {
            scaleX = 10.0;
            scaleY = 0.0;
        }
        if ( get_subseq()== 11 )
        {
            float t[4];
            t[0] = addition[0];
            t[1] = 0.0;
            t[2] = 10.0;
            addbullet(chrt, this, 869, x, y, dir, 1, t, 3);

            t[1] = 5.0;
            t[2] = 9.0;
            t[3] = 0.2;
            addbullet(chrt, this, 869, x, y, dir, 1, t, 4);

            t[1] = 15.0;
            t[3] = 0.4;
            addbullet(chrt, this, 869, x, y, dir, 1, t, 4);
        }
        if ( get_subseq() == 12 )
        {
            scaleY = scaleX = scene_rand_rngf(5) * 0.1 + 0.5;
        }
        break;
    case 900:
        set_subseq(addition[2]);
        if ( get_subseq() <= 3 )
        {
            angZ = scene_rand_rngf(360);
            float t[3];
            t[0] = 0.0;
            t[1] = 0.0;
            t[2] = 4.0;
            addbullet(chrt, NULL, 900, x, y, dir, 1, t, 3);
            field_194 = 1;
            scaleY = scaleX = scene_rand_rngf(30) * 0.01 + 0.8;
            field_380 = scene_rand_rngf(5) + 2.0;
        }
        if ( get_subseq()== 12 )
        {
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_36E = 240;
                break;
            case GAME_DIFF_HARD:
                field_36E = 180;
                break;
            case GAME_DIFF_EASY:
            case GAME_DIFF_NORMAL:
                field_36E = 120;
                break;
            default:
                break;
            }
        }
        if ( get_subseq()== 13 )
        {
            field_194 = 0;
            scaleX = 0.1;
            scaleY = 0.1;
        }
        if ( get_subseq()>= 14 && get_subseq()<= 17 )
        {
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        }
        if ( get_subseq() == 18 )
            field_194 = 1;
        break;
    case 910:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            angZ = addition[0];
            field_194 = 1;
            //tail_add(v2, 993, COERCE_UNSIGNED_INT(40.0), 60, 1, 2); //HACK
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 1 )
        {
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.5;
            angZ = scene_rand_rngf(360);
            field_37C = scene_rand_rngf(10) - 5.0;
        }
        if ( get_subseq() == 2 )
        {
            scaleY = scaleX = scene_rand_rngf(75) * 0.01 + 1.0;
            angZ = scene_rand_rngf(360);
            field_37C = scene_rand_rngf(10) - 5.0;
        }
        if ( get_subseq()>= 5 && get_subseq()<= 7 )
            field_194 = 1;
        break;
    case 920:
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
        {
            setOrigin(-60.0, 0.0);
            scaleY = 1.2;
        }
        if ( get_subseq()== 1 )
        {
            scaleY = scaleX = scene_rand_rngf(75) * 0.01 + 0.75;
            angZ = scene_rand_rngf(360);
        }
        if ( get_subseq() == 2 )
        {
            field_194 = 1;
            scaleY = scaleX = scene_rand_rngf(75) * 0.01 + 0.75;
            angZ = scene_rand_rngf(360);
        }
        if ( get_subseq()== 6 )
            c_A = 0;
        if ( get_subseq()== 10 )
        {
            sub_438450(0.0, 0.0, 0.0, 256.0);
            scaleX = 1.0;
            scaleY = addition[3];
            field_194 = 99;
            float t[4];
            t[0] = addition[0];
            t[1] = 0.0;
            t[2] = 9.0;
            t[3] = addition[3];
            addbullet(chrt, this, 920, x, y, dir, 1, t, 4);

            t[2] = 11.0;
            addbullet(chrt, this, 920, x, y, dir, 1, t, 4);

            sub_438450(0.0, 0.0, 0.0, 256.0);
        }
        if ( get_subseq()== 9 || get_subseq()== 11 )
        {
            scaleY = scaleX = addition[3];
        }
        if ( get_subseq()== 12 )
        {
            /*sub_465E50(&meta, 995); //HACK
            field_154->field_F8 = 25.0;
            field_154->field_FC = 10.0;
            *(float *)&field_154->field_E8 = 640.0;
            *(float *)&field_154->field_EC = 0.0;
            LOBYTE(field_154->field_104) = dir;*/
            angZ = addition[0];
            sub_438450(0.0, 0.0, 0.0, 256.0);
            scaleX = 1.0;
            field_194 = 99;
            scaleY = addition[3];
            float t[4];
            t[0] = addition[0];
            t[1] = 0.0;
            t[2] = 9.0;
            t[3] = addition[3];
            addbullet(chrt, this, 920, x, y, dir, 1, t, 4);

            t[2] = 11.0;
            addbullet(chrt, this, 920, x, y, dir, 1, t, 4);
            sub_438450(0.0, 0.0, 0.0, 256.0);
        }
        break;
    case 921:
        angZ = scene_rand_rngf(360);
        set_subseq(addition[2]);
        field_194 = 1;
        set_vec_speed(addition[0], addition[1]);
        scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        break;
    case 970:
        set_subseq(addition[2]);
        if ( get_subseq() <= 7 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
            char_frame *frm = chrt->get_pframe();
            field_37C = frm->extra1[4] * dir + chrt->x;
            field_380 = chrt->y - frm->extra1[5];
        }
        break;
    case 980:
        //sub_48C360(); //HACK
        break;
    case 990:
//      field_134 = 0; //HACK
        break;
    case 998:
        angZ = 0;
        angY = 60;
        break;
    case 999:
        set_subseq(addition[2]);
        if ( get_subseq() == 4 )
        {
            h_inerc = addition[0];
            v_inerc = addition[1];
        }
        break;
    }
}





