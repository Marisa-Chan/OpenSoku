#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "marisa_bullets.h"
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
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

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
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

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
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

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

            x = cos((-bul_parent->angZ) * 3.1415926/180.0) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin((-bul_parent->angZ) * 3.1415926/180.0) * bul_parent->field_37C * bul_parent->dir + bul_parent->y;

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
            set_real_size(field_37C,256);
        //   sub_438450(v1, v1->field_378, 0.0, v1->field_37C, 256.0);

        break;

    case 804:
        if ( get_subseq() == 0 )
        {
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];
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
                h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
                v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

                addition[1] -= 0.5;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;

                x += dir * h_inerc;
                y += v_inerc * 0.25;

                angZ += field_37C;
                scaleY = scaleX +=0.02;

                if ( get_elaps_frames() >= 0 )
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
    default:
        if (process())
            active = false;
    }
}

void marisa_bullets::set_seq_params()
{
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
            //sub_4B0780(v2, 989, COERCE_UNSIGNED_INT(15.0), 5, 1, 2);
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

        if ( get_subseq() == 0 )
        {
            /*sub_4B0780(v2, 989, COERCE_UNSIGNED_INT(20.0), 6, 2, 2);*/
        }
        else if ( get_subseq() == 1 )
        {
            /*sub_4B0780(v2, 989, COERCE_UNSIGNED_INT(20.0), 6, 2, 2);*/
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
            //sub_438450(v2, 0.0, 0.0, 0.0, 256.0);
            field_194 = 10;
            float t[3];
            t[0] = 0;
            t[1] = 0;
            t[2] = 3;
            addbullet(chrt,this,803,x,y,dir,1,t,3);
            t[2] = 5;
            addbullet(chrt,this,803,x,y,dir,1,t,3);
            set_real_size(0,0);
            //sub_438450(v2, 0.0, 0.0, 0.0, 256.0);
            field_380 = 35.0;
        }
        break;
    case 804:
        field_194 = 1;
        break;
    case 810:
        angZ = scene_rand_rng(360);
        set_subseq(addition[2]);
        scaleY = scaleX = scene_rand_rng(50) * 0.01 + 0.5;
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
        return;
    case 825:
        field_18C = 3;
        field_194 = 1;
        set_subseq(addition[2]);
        //if ( addition[2] <= 3 )
        //sub_4B0780(v2, addition[2] + 991, COERCE_UNSIGNED_INT(20.0), 6, 2, 2);
        field_36C = 0;
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
    case 998:
        angZ = 0;
        angY = 60;
        break;
    }
}




