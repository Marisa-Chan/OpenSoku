#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "../utils.h"
#include "alice_bullets.h"
#include "alice.h"
#include <math.h>


bool alice_bullets::sub_5269B0()
{
    field_380 = -atan2_deg(chrt->y + 100 - y, chrt->x - x);
    field_378 += 2;
    if (field_378 > 20)
        field_378 = 20.0;

    set_vec_speed(field_380, field_378);

    if (x - chrt->x > 0)
        dir = -1;
    else if (x - chrt->x < 0)
        dir = 1;

    if (fabs (x - chrt->x) >= 20 || fabs(chrt->y + 100 - y) >= 20.0)
        return false;

    active = false;
    return true;
}

bool alice_bullets::sub_526870(uint16_t subseq)
{
    c_meta * par = chrt;
    c_bullet * parb = bul_parent;

    x = par->x;
    y = par->y + 100;

    if ( bul_parent )
    {
        if (dir == 1)
            angZ = -atan2_deg(parb->y - (par->y + 100), parb->x - x);
        else
            angZ = atan2_deg(parb->y - (par->y + 100), parb->x - x) + 180;

        field_378 = (parb->x - x) * (parb->x - x);
        field_37C = (parb->y - y) * (parb->y - y);
        field_380 = sqrt(field_378 + field_37C);
        scaleX = field_380 * 0.0039;

        if (parb->get_subseq() == subseq)
        {
            active = false;
            return true;
        }
    }
    else
    {
        active = false;
        return true;
    }
    return false;
}




void alice_bullets::func10()
{
    switch(sprite.get_seq_id())
    {
    case 800:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( get_subseq() > 6 )
        {
            sub_48BF60(addition[3] + 4 * get_elaps_frames());
            scaleY = scaleX = scaleX + 0.02;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            else
            {
                c_A -= 10;
                if ( process() )
                {
                    active = false;
                    break;
                }
            }
            return;
        }
        if ( get_frame() == 0 )
        {
            sub_48BF60(addition[3] + 4 * get_elaps_frames());
            if ( sub_48C6A0( 0, 0, 4) )
            {
                active = false;
                break;
            }
            if ( field_190 )
            {
                if ( field_190 == 4 )
                    field_194 = 0;
                next_frame();
                float tmp[4];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 7.0;
                tmp[3] = get_elaps_frames() * 4.0 + addition[3];
                addbullet( chrt, NULL, 800, x, y, dir, 1, tmp, 4);
                break;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                break;
            }
            set_vec_speed(addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
        }
        if (get_frame() == 1)
        {
            scaleY = scaleX = scaleX * 0.85;
            if ( c_A > 20 )
            {
                c_A -= 20;

                if ( process() )
                {
                    active = false;
                }
            }
            else
                active = false;
        }
        else
        {
            if ( process() )
            {
                active = false;
                return;
            }
        }
        break;
    case 801:
        if ( get_subseq() <= 6 )
        {
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                if ( get_subseq() <= 5 )
                    set_subseq( 6);
            if ( chrt->get_seq() <= 399 || chrt->get_seq() >= 410 )
            {
                if ( get_subseq() <= 4 && ((chrt->get_seq() >= 400 && chrt->get_seq() <= 407 && chrt->get_subseq() == 0 && chrt->get_frame() == 0) || chrt->get_seq() <= 399 || chrt->get_seq() >= 408) )
                {
                    set_subseq( 5);
                    order = -1;
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                }
            }
            else
            {
                if ( ((chrt->get_seq() == 404 && chrt->get_subseq() == 8) || (chrt->get_seq() == 405 && chrt->get_subseq() == 8) || (chrt->get_seq() == 406 && chrt->get_subseq() == 8))
                        && get_subseq() <= 4 )
                {
                    set_subseq( 5);
                    order = -1;
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                }
            }
            switch ( get_subseq() )
            {
            case 0:
                field_378 += h_inerc;
                field_37C += v_inerc;
                h_inerc *= 0.75;
                v_inerc *= 0.75;
                if ( get_elaps_frames() >= 10 )
                    set_subseq(2);

                x = field_378 + addition[0] * dir + chrt->x;
                y = addition[1] + field_37C + chrt->y;
                break;
            case 2:
                x = field_378 + addition[0] * dir + chrt->x;
                y = addition[1] + field_37C + chrt->y;
                break;
            case 3:
                if ( get_elaps_frames() % 3 == 0 )
                {
                    if ( field_36C <= 6 )
                    {
                        chrt->play_sfx( 0);
                        field_36C++;
                        field_380 = -atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);
                        if ( addition[2] == 1.0)
                        {
                            if ( field_380 < 20.0 )
                                field_380 = 20.0;
                            if ( field_380 > 60.0 )
                                field_380 = 60.0;
                        }
                        else
                        {
                            if ( field_380 < -20.0 )
                                field_380 = -20.0;
                            if ( field_380 > 20.0 )
                                field_380 = 20.0;
                        }
                        float tmp[4];
                        tmp[0] = scene_rand_rngf(20) + field_380 - 10.0;
                        tmp[1] = 15.5;
                        tmp[2] = 0.0;
                        tmp[3] = field_36C * 35.0;
                        addbullet( chrt, NULL, 800, (20 * dir) + x, y + 5.0, dir, 1, tmp,4);
                        tmp[2] = 7.0;
                        addbullet( chrt, NULL, 800, (20 * dir) + x, y + 5.0, dir, 1, tmp,4);
                        chrt->play_sfx( 0);
                    }
                }
                if ( get_elaps_frames() >= 30 )
                    next_subseq();
                x = (field_378 + addition[0]) * dir + chrt->x;
                y = addition[1] + field_37C + chrt->y;
                break;
            case 5:
                if ( sub_5269B0() )
                    return;
                x += h_inerc;
                y += v_inerc;
                break;
            case 6:
                if ( h_inerc > 5.0 )
                    h_inerc = 5.0;
                if ( h_inerc < -5.0 )
                    h_inerc = -5.0;
                if ( v_inerc > 5.0 )
                    v_inerc = 5.0;
                if ( v_inerc < -5.0 )
                    v_inerc = -5.0;
                v_inerc -= 0.5;
                x += h_inerc;
                y += v_inerc;
                angZ += 15.0;

                if ( c_A < 20 )
                {
                    active = false;
                    return;
                }
                c_A -= 20;
                break;
            default:
                break;
            }
        }
        if ( get_subseq() >= 7 && get_subseq() <= 12)
        {
            if ( ((chrt->get_seq() > 49 && chrt->get_seq() < 150) || health <= -500) && get_subseq() <= 9 )
            {
                set_subseq(6);
                break;
            }
            else
            {
                if ( chrt->get_seq() != 402 && get_subseq() <= 9 )
                {
                    set_subseq(5);
                    order = -1;
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                }
                switch ( get_subseq() )
                {
                case 7:
                    if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 7 )
                    {
                        h_inerc = 27.5;
                        v_inerc = 0.0;
                    }
                    if ( get_elaps_frames() >= 4 )
                    {
                        next_subseq();
                        return;
                    }
                    x += dir * h_inerc;
                    break;
                case 8:
                case 9:
                    h_inerc -= 4.0;
                    if ( h_inerc < 4.0 )
                        h_inerc = 4.0;
                    if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 9 )
                    {
                        float tmp[3];
                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = 10.0;
                        addbullet(chrt, this, 801, (45 * dir) + x, y + 5.0, dir, 1, tmp, 3);
                    }
                    if ( get_subseq() == 9 && get_elaps_frames() >= 40 )
                    {
                        set_subseq(5);
                        order = -1;
                        if ( x - chrt->x > 0.0 )
                            dir = -1;
                        if ( x - chrt->x < 0.0 )
                            dir = 1;
                        field_378 = 0.0;
                    }
                    x += dir * h_inerc;
                    break;
                case 10:
                    if ( !bul_parent )
                    {
                        active = false;
                        return;
                    }
                    if ( bul_parent->get_subseq() == 9 )
                    {
                        if ( field_190 )
                        {
                            if ( field_36C < 7 )
                                field_36C++;
                            else
                            {
                                field_36C = 0;
                                field_190 = 0;
                            }
                        }
                        x = (45 * dir) + bul_parent->x;
                        y = bul_parent->y + 5.0;
                        break;
                    }
                    field_194 = 0;
                    scaleY = scaleX *= 0.85;
                    if ( scaleX <= 0.01 )
                    {
                        active = false;
                        return;
                    }
                    break;
                case 11:
                    angZ += 15.0;
                    if ( !bul_parent )
                    {
                        active = false;
                        return;
                    }
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->field_194 > 0 )
                    {
                        scaleY += 0.3;
                        if ( scaleY > 3.0 )
                            scaleY = 3.0;
                        break;
                    }
                    else
                    {
                        scaleY *= 0.65;
                        if ( scaleY <= 0.01 )
                        {
                            active = false;
                            return;
                        }
                    }
                    break;
                case 12:
                    if ( !bul_parent )
                    {
                        active = false;
                        return;
                    }
                    x = bul_parent->x;
                    y = bul_parent->y;
                    scaleY = scaleX = sin_deg(3 * get_elaps_frames()) * 6.0;
                    if (c_A < 9)
                    {
                        active = false;
                        return;
                    }
                    else
                        c_A -= 9;
                    break;
                default:
                    break;
                }
            }
        }

        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            order = -1;
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 802:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            if ( get_subseq() <= 5 )
                set_subseq(6);
        if ( chrt->get_seq() <= 399 || chrt->get_seq() >= 410 )
            if ( get_subseq() <= 4 )
            {
                set_subseq(5);
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                field_378 = 0.0;
            }
        if ( (chrt->get_seq() == 404 && chrt->get_subseq() == 8) || (chrt->get_seq() == 406 && chrt->get_subseq() == 8 ))
            if ( get_subseq() <= 4 )
            {
                set_subseq(5);
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                field_378 = 0.0;
            }
        switch ( get_subseq() )
        {
        case 0:
            field_378 += h_inerc;
            field_37C += v_inerc;
            h_inerc *= 0.75;
            v_inerc *= 0.75;
            if ( get_elaps_frames() >= 10 )
                set_subseq(1);
            x = (field_378 + addition[0]) * dir + chrt->x;
            y = addition[1] + field_37C + chrt->y;
            break;
        case 1:
            if ( chrt->get_subseq() >= 5 )
                next_subseq();
            x = (field_378 + addition[0]) * dir + chrt->x;
            y = addition[1] + field_37C + chrt->y;
            break;
        case 2:
            x = (field_378 + addition[0]) * dir + chrt->x;
            y = addition[1] + field_37C + chrt->y;
            break;
        case 3:
            if ( get_elaps_frames() % 3 == 0 )
            {
                if ( field_36C <= 12 )
                {
                    chrt->play_sfx( get_elaps_frames() % 3);
                    field_36C++;
                    field_380 = -atan2_deg(chrt->enemy->y + 100.0 - y, (chrt->enemy->x - x) * dir);
                    if ( field_380 < -20.0 )
                        field_380 = -20.0;
                    if ( field_380 > 20.0 )
                        field_380 = 20.0;
                    float tmp[4];
                    tmp[0] = scene_rand_rngf(20) + field_380 - 10.0;
                    tmp[1] = 17.5;
                    tmp[2] = 0.0;
                    tmp[3] = field_36C * 35.0;
                    addbullet( chrt, NULL, 800, (20 * dir) + x, y + 5.0, dir, 1, tmp,4);
                    tmp[2] = 7.0;
                    addbullet( chrt, NULL, 800, (20 * dir) + x, y + 5.0, dir, 1, tmp,4);
                    chrt->play_sfx( 0);
                }
            }
            if ( get_elaps_frames() >= 40 )
                next_subseq();
            x = (field_378 + addition[0]) * dir + chrt->x;
            y = addition[1] + field_37C + chrt->y;
            break;
        case 5:
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
            break;
        case 6:
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
            break;
        default:
            break;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            order = -1;
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 803:
    {
        if (chrt->char_is_shock())
            if (get_subseq() < 4)
                set_subseq(5);

        bool tr = (chrt->get_seq() > 399 && chrt->get_seq() < 410)  || get_subseq() > 3 ;

        if ( (tr && get_subseq() >= 8) || !tr)
        {
            set_subseq(4);
            order = -1;
            if (x - chrt->x > 0)
                dir = -1;
            else if ( x - chrt->x < 0)
                dir = 1;
        }

        switch ( get_subseq() )
        {
        case 0:
            if (get_elaps_frames() > 60 || fabs(enemy->x - x) < 300)
                field_36E++;
            if (field_36E > 0)
            {
                h_inerc -= 4.0;
                if (h_inerc < 0)
                {
                    h_inerc = 0;
                    next_subseq();
                    return;
                }
            }

            x += h_inerc * dir;
            y += v_inerc;
            break;
        case 2:
            if ( get_elaps_frames() % 3 == 0 && field_36C <= 7)
            {
                chrt->play_sfx(get_elaps_frames() % 3);

                field_36C++;
                if ( field_380 < -20.0 )
                    field_380 = -20.0;
                else if ( field_380 > 20.0 )
                    field_380 = 20.0;

                float tmp[4];
                tmp[0] = scene_rand_rngf(60) - 30.0;
                tmp[1] = 30;
                tmp[2] = 0;
                tmp[3] = field_36C * 35.0;

                addbullet(chrt,NULL, 804, x + dir * 20, y + 5,dir, 1, tmp, 4);

                tmp[2] = 7;
                addbullet(chrt,NULL, 800, x + dir * 20, y + 5,dir, 1, tmp, 4);

                chrt->play_sfx(0);
            }
            if (get_elaps_frames() >= 30)
                next_subseq();
            break;
        case 4:
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;

            break;
        case 5:
            if ( h_inerc > 5.0)
                h_inerc = 5.0;
            else if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            else if ( v_inerc < -5.0 )
                v_inerc = -5.0;

            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15;

            if (c_A < 20)
            {
                active = false;
                return;
            }
            c_A -= 20;
            break;
        case 6:
            if ( !sub_526870(5) )
                return;
            break;
        case 7:
            if ( get_elaps_frames() >= 6 || fabs(enemy->x - x) < 300 )
                field_36E++;
            if (field_36E > 0)
            {
                h_inerc -= 4.0;
                if (h_inerc < 0)
                {
                    h_inerc = 0;
                    next_subseq();
                    return;
                }
            }
            x += h_inerc * dir;
            y += v_inerc;
            break;
        default:
            break;
        }
        if (process())
            active = false;
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4)
        {
            order = -1;
            if (x - chrt->x > 0)
                dir = -1;
            else if (x - chrt->x < 0)
                dir = 1;

            field_378 = 0.0;
        }
    }
    break;
    case 804:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        if ( get_subseq() > 6 )
        {
            sub_48BF60(addition[3] + 8 * get_elaps_frames());
            addition[1] -= 2.0;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            set_vec_speed(addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            scaleY = scaleX *= 0.85;
            if ( c_A > field_36C )
                c_A -= field_36C;
            else
            {
                active = false;
                return;
            }
        }
        else
        {
            if (get_frame() == 0)
            {
                sub_48BF60(addition[3] + 8 * get_elaps_frames());
                addition[1] -= 2.0;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;
                if ( !sub_48C6A0( 0, 0, 3) )
                {
                    if ( get_elaps_frames() >= 30 )
                    {
                        next_frame();
                        return;
                    }
                    if ( field_190 )
                    {
                        next_frame();
                        addition[1] = 0.5;
                        for (int i=0; i < 4; i++)
                        {
                            float tmp[4];
                            tmp[0] = scene_rand_rngf(360);
                            tmp[1] = scene_rand_rngf(30) + 10.0;
                            tmp[2] = (get_subseq() + 7);
                            tmp[3] = get_elaps_frames() * 8.0 + addition[3];
                            addbullet( chrt, NULL, 804, x, y, dir, 1, tmp,4);
                        }
                        return;
                    }
                    if ( x <= 1380.0 && x >= -100.0 && y <= 1000.0 && y >= -160.0 )
                    {
                        set_vec_speed(addition[0], addition[1]);
                        x += dir * h_inerc;
                        y += v_inerc;
                    }
                    else
                    {
                        active = false;
                        return;
                    }
                }
                else
                {
                    active = false;
                    return;
                }
            }
            else if ( get_frame() == 1)
            {
                addition[1] -= 2.0;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;
                set_vec_speed(addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
                scaleY = scaleX *= 0.85;
                if ( c_A > 20 )
                    c_A -= 20;
                else
                {
                    active = false;
                    return;
                }
            }
            else
                return;
        }
        if ( process() )
            active = false;
        break;

    case 805:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            if ( get_subseq() <= 5 )
                set_subseq(6);
        if ( get_subseq() != 6 && get_subseq() != 7 )
            if ( health < -600 || chrt->health <= 0 )
                set_subseq(6);
        switch ( get_subseq() )
        {
        case 0:
            set_vec_speed(addition[0], addition[1]);
            addition[1] -= 2.0;
            if ( addition[1] < 0.0 )
            {
                addition[1] = 0.0;
                next_subseq();
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( y < getlvl_height() )
                y = getlvl_height();
            break;
        case 1:
            if ( get_elaps_frames() >= 60 )
            {
                next_subseq();
                return;
            }
            if ( chrt->get_seq() >= 410 && chrt->get_seq() <= 416 && chrt->get_subseq() == 1 )
            {
                next_subseq();
                field_36E = 1;
                return;
            }
            break;
        case 3:
            if ( field_36E == 1 )
            {
                if ( get_elaps_frames() == 0 )
                {
                    chrt->play_sfx( 1);
                    field_36C++;
                    field_380 = -atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);
                    if ( field_380 < -80.0 )
                        field_380 = -80.0;
                    if ( field_380 > 80.0 )
                        field_380 = 80.0;
                    float tmp[3];
                    tmp[0] = field_380;
                    tmp[1] = 0.0;
                    tmp[2] = 0.0;
                    addbullet(chrt, this, 807, (20 * dir) + x, y + 5.0, dir, 1, tmp, 3);
                }
                if ( get_elaps_frames() >= 90 )
                    next_subseq();
            }
            else
            {
                if ( get_elaps_frames() % 3 == 0 && field_36C <= 7 )
                    if ( x > -40.0 && x < 1320.0 )
                    {
                        chrt->play_sfx( 0);
                        field_36C++;
                        field_380 = -atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);
                        if ( field_380 < -80.0 )
                            field_380 = -80.0;
                        if ( field_380 > 80.0 )
                            field_380 = 80.0;
                        float tmp[4];
                        tmp[0] = field_380 + 18.0 - field_36C * 4.0;
                        tmp[1] = 12.5;
                        tmp[2] = 0.0;
                        tmp[3] = 0.0;
                        addbullet( chrt, NULL, 806, (20 * dir) + x, y + 5.0, dir, 1, tmp,4);
                        tmp[2] = 7.0;
                        addbullet( chrt, NULL, 806, (20 * dir) + x, y + 5.0, dir, 1, tmp,4);
                    }
                if ( get_elaps_frames() >= 30 )
                    next_subseq();
            }
            break;
        case 5:
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
            break;
        case 6:
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            c_A -= 10;
            break;
        case 7:
            if ( chrt->get_seq() == 609 || chrt->get_seq() == 659 )
                if ( chrt->get_subseq() == 1 )
                    if ( bul_parent )
                        if ( (bul_parent->get_seq() == 805 && bul_parent->get_subseq() == 8) ||
                                bul_parent->get_seq() == 859 )
                        {
                            scaleY = 5.0;
                            set_seq(859);
                            set_subseq(4);
                            field_194 = 1;
                            field_36C = 0;
                            return;
                        }
            if ( sub_526870(6) )
                return;
            break;
        case 8:
        {
            char_alice *alice = (char_alice *)chrt;
            if ( chrt->health <= 0 || enemy->health <= 0 )
            {
                alice->field_892--;
                alice->field_8BC[field_3AC + 1] = 0;
                set_subseq(6);
                return;
            }
            if ( alice->field_8BC[field_3AC + 1] )
            {
                next_subseq();
                alice->field_8BC[field_3AC + 1] = 0;
                return;
            }
            else
            {
                alice->field_89C[field_3AC] = x;
                alice->field_8AC[field_3AC] = y;

                if ( chrt->get_seq() == 560 && chrt->get_subseq() == 1 )
                {
                    alice->field_892--;
                    set_seq(825);
                    set_subseq(1);
                    //get_elaps_frames() = 0;
                    return;
                }
                if ( chrt->get_seq() == 609 || (chrt->get_seq() == 659 && chrt->get_subseq() == 1 ))
                {
                    alice->field_892--;
                    set_seq(859);
                    set_subseq(1);
                    //get_elaps_frames() = 0;
                    field_36C = 0;
                    field_194 = 1;
                    return;
                }
                if ( chrt->get_seq() == 566 || (chrt->get_seq() == 569 && alice->field_8BC[0] == 1) )
                {
                    alice->field_892--;
                    set_seq(834);
                    set_subseq(7);
                    if ( enemy->x < x )
                        dir = -1;
                    if ( enemy->x > x )
                        dir = 1;

                    //get_elaps_frames() = 0;
                    return;
                }
            }
        }
        break;
        case 10:
            if ( get_elaps_frames() >= 60 )
            {
                set_subseq(5);
                return;
            }
            break;
        default:
            break;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            int tmp = 1;
            if ( chrt->skills_1[3] == 2 || chrt->skills_1[11] == 2 )
                tmp = 2;
            if ( chrt->skills_1[3] == 3 || chrt->skills_1[11] == 3 )
                tmp = 2;
            if ( chrt->skills_1[3] == 4 || chrt->skills_1[11] == 4 )
                tmp = 3;

            char_alice *alice = (char_alice *)chrt;

            if ( alice->field_892 <= tmp )
            {
                field_3AC = alice->field_892;
                alice->field_892++;
                alice->field_89C[field_3AC] = x;
                alice->field_8AC[field_3AC] = y;
                set_subseq(8);
            }
        }
        break;
    case 806:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        if ( get_subseq() <= 6 )
        {
            if ( get_frame() == 0 )
            {
                sub_48BF60(4 * get_elaps_frames());
                if ( !sub_48C6A0( 0, 0, 4) )
                {
                    if ( field_190 || get_elaps_frames() > 60 )
                    {
                        next_frame();
                        float tmp[4];
                        tmp[0] = 0.0;
                        tmp[1] = 0.0;
                        tmp[2] = (get_subseq() + 7);
                        tmp[3] = get_elaps_frames() * 4.0;
                        addbullet( chrt, NULL, 806, x, y, dir, 1, tmp,4);
                        return;
                    }
                    if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                    {
                        active = false;
                        return;
                    }
                    set_vec_speed(addition[0], addition[1]);
                    x += dir * h_inerc;
                    y += v_inerc;

                }
                else
                {
                    active = false;
                    return;
                }

            }
            else if ( get_frame() == 1 )
            {
                scaleY = scaleX *= 0.85;
                if (c_A <= 20)
                {
                    active = false;
                    return;
                }
                else
                    c_A -= 20;
            }
            else
                return;
        }
        else
        {
            sub_48BF60(addition[3] + 4 * get_elaps_frames());
            scaleY = scaleX += 0.02;
            if (c_A <= 10)
            {
                active = false;
                return;
            }
            else
                c_A -= 10;
        }
        if ( process() )
            active = false;
        break;
    case 807:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_frame() <= 1 )
        {
            for(int8_t i = 0; i < 12; i++)
            {
                float xx = cos_deg(angZ) * (float)i * 130.0 * dir + x;
                float yy = sin_deg(angZ) * 130.0 + y;
                scene_add_effect(this,  201, xx, yy, dir,  1);
            }
            active = false;
            return;
        }
        if ( get_frame() <= 1 )
        {
            if ( bul_parent == NULL )
            {
                set_frame(2);
                return;
            }
            if ( bul_parent->get_subseq() == 6 )
            {
                set_frame( 2);
                return;
            }
        }
        if ( get_frame() == 0 && get_elaps_frames() >= 20 )
        {
            scaleY += 0.15;
            if ( scaleY >= 2.0 )
            {
                field_194 = 4;
                scaleY = 2.0;
                next_frame();
            }
        }
        if ( get_frame() == 1 )
        {
            sub_48C5F0( 0);
            if ( field_190 )
            {
                field_36C++;
                if ( field_36C >= 7 )
                {
                    field_36C = 0;
                    field_190 = 0;
                }
            }
        }
        if ( get_frame() == 2 )
        {
            field_194 = 0;
            scaleY *= 0.9;
            if ( get_frame_time() >= 60 )
            {
                active = false;
                return;
            }
        }
        if ( process() )
            active = false;
        break;
    case 810:
        if ( get_subseq() <= 2 )
            if ( sub_48C6A0( 0, 1, 3) || health <= -750 )
                set_subseq(3);
        if ( get_subseq() == 0)
        {
            if ( (chrt->get_seq() == 500 || chrt->get_seq() == 501) && chrt->get_frame() == 0 )
            {
                next_subseq();
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
            set_vec_speed(addition[0], addition[1]);
            addition[0] -= 2.0;
            addition[1] -= 1.0;
            if ( addition[1] < 0.0 )
            {
                addition[1] = 0.0;
                next_subseq();
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( y < 0.0 )
                y = 0.0;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet(chrt, this, 810, x, y, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 15 == 0 )
                chrt->play_sfx( 4);
            sub_48C5F0( 0);
            if ( field_188 > 0 )
            {
                set_subseq(3);
                return;
            }
            if ( field_190 )
            {
                field_36C++;
                if ( field_36C >= 4 )
                {
                    field_36C = 0;
                    field_190 = 0;
                }
            }
            uint16_t tmp = 80;
            if ( chrt->skills_1[0] >= 1 )
                tmp = 120;
            if ( chrt->skills_1[0] >= 3 )
                tmp = 180;
            if ( get_elaps_frames() >= tmp || field_194 <= 0 ||
                    ((chrt->get_seq() == 500 || chrt->get_seq() == 501) && chrt->get_frame() == 0))
            {
                next_subseq();
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
        }
        if ( get_subseq() == 2 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 3 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() != 4 || !sub_526870(3) )
        {
            if ( get_subseq() == 5 )
            {
                angZ += 25.0;
                if ( bul_parent == NULL )
                {
                    active = false;
                    return;
                }
                if ( bul_parent->get_subseq() == 1 )
                {
                    scaleX += 0.1;
                    if ( scaleX > 3.0 )
                        scaleX = 2.5;
                    scaleY = scaleX;
                    if ( c_A > 225 )
                        c_A = -1;
                    else
                        c_A += 30;
                }
                else
                {
                    if ( c_A < 20 )
                    {
                        active = false;
                        return;
                    }
                    scaleX += 0.1;
                    c_A -= 20;
                    c_R -= 20;
                    c_G -= 20;
                }
            }
            if ( process() )
                active = false;
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
            {
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                field_378 = 0.0;
            }
        }
        break;
    case 811:
        if ( get_subseq() == 0 )
        {
            if ( sub_48C6A0( 0, 1, 3) || health <= -500 )
                set_subseq(1);
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 3.0;
                addbullet(chrt, this, 811, x, y, dir, 1, tmp, 3);
            }
            sub_48C5F0( 0);
            if ( field_36C == 0)
            {
                addition[1] -= 0.5;
                if ( addition[1] < 0.0 )
                {
                    addition[1] = 0.0;
                    field_36C = 1;
                }
                set_vec_speed(addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
            }
            if ( field_36C == 1 )
            {
                field_36E++;
                if ( field_36E >= 30 )
                {
                    if ( chrt->skills_1[4] >= 3 )
                    {
                        field_194 = 1;
                        field_190 = 0;
                    }
                    field_36C = 2;
                }
            }
            if ( field_36C == 2 )
            {
                addition[0] = -atan2_deg(chrt->y + 100.0 - y, chrt->x - x);
                addition[1] += 0.5;
                if ( field_378 > 20.0 )
                    field_378 = 20.0;
                set_vec_speed(addition[0], addition[1]);
                x += h_inerc;
                y += v_inerc;
                if ( fabs(chrt->x - x) < 20.0 && fabs(chrt->y + 100.0 - y) < 20.0 )
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 1 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            c_A -= 10;
        }
        if ( get_subseq() == 2 && sub_526870(1) )
            return;
        if ( get_subseq() == 3 )
        {
            if ( bul_parent == NULL)
            {
                active = false;
                return;
            }
            if ( bul_parent->get_subseq() == 0)
            {
                x = bul_parent->x;
                y = bul_parent->y;
                scaleX += 0.1;
                if ( scaleX > 2.5 )
                    scaleX = 2.0;
                scaleY = scaleX;
                if ( c_A > 225 )
                    c_A = -1;
                else
                    c_A += 30;
            }
            else
            {
                if ( c_A < 20 )
                {
                    active = false;
                    return;
                }
                scaleX += 0.1;
                c_A -= 20;
                c_R -= 20;
                c_G -= 20;
            }

            angZ += 25.0;
        }
        if ( process() )
            active = false;
        break;
    case 812:
        field_18C = 8;
        if ( get_subseq() <= 2 || get_subseq() == 11 || get_subseq() == 12 )
        {
            if ( sub_48C6A0( 0, 1, 3) || health < 0 )
            {
                set_subseq(3);
                return;
            }
            if ( chrt->get_seq() >= 510 && chrt->get_seq() <= 513 && chrt->get_subseq() == 0 && chrt->get_frame() == 0)
            {
                set_subseq(6);
                return;
            }
        }
        if ( get_subseq() == 0 || get_subseq() == 1 )
        {
            if ( field_36C == 0)
            {
                if ( get_subseq() == 0 )
                {
                    angZ -= 20.0;
                    if ( field_380 >= 90.0 )
                    {
                        field_370++;
                        if ( field_370 >= 20 )
                        {
                            angZ = 0.0;
                            next_subseq();
                        }
                    }
                    addition[0] -= 3.0;
                }
                field_380 += 4.0;
                if ( field_380 >= 90.0 )
                    field_380 = 90.0;

                addition[1] = sin_deg(field_380) * field_388;
                x = cos_deg(-addition[0]) * addition[1] * dir + field_378;
                y = sin_deg(-addition[0]) * addition[1] + field_37C;
            }
        }
        if ( get_subseq() == 2 )
        {
            if ( (addition[3] == 0.0 && chrt->keyDown(INP_B) == 0)
                    || (addition[3] == 1.0 && chrt->keyDown(INP_C) == 0) )
            {
                set_subseq(11);
                field_36E = 0;
                return;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 4 )
        {
            if ( bul_parent == NULL )
            {
                active = false;
                return;
            }
            else
            {
                x = bul_parent->x;
                y = bul_parent->y;
                if (bul_parent->field_194 == 0 || bul_parent->get_subseq() != 2)
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleX += addition[1];
            addition[1] *= 0.92;
            scaleY = scaleX;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 6 )
        {
            if (sub_5269B0())
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if (get_subseq() == 7 && sub_526870(3))
            return;

        if ( get_subseq() == 9 )
        {
            if ( bul_parent == NULL || bul_parent->field_36C == 0 )
            {
                next_subseq();
                return;
            }
            x = bul_parent->x;
            y = bul_parent->y;
        }

        if ( get_subseq() == 11 )
        {
            angZ += 40.0;
            field_36E++;
            if (field_36E > 10)
            {
                addition[0] += 170.0;
                addition[1] = 20.0;
                angZ = addition[0];
                chrt->play_sfx(5);
                set_subseq(12);
                set_vec_speed(addition[0], addition[1]);
                order = 1;
                float tmp[3];
                tmp[0] = angZ;
                tmp[1] = 0.3;
                tmp[2] = 9.0;
                addbullet(chrt, this, 812, x, y, dir, 1, tmp, 3 );
                tmp[2] = 5.0;
                addbullet(chrt, NULL, 812, x, y, dir, 1, tmp, 3 );
            }
        }
        if ( get_subseq() == 12 )
        {
            sub_48C5F0(10);
            field_380 += 2.0;
            addition[1] *= 0.92;
            if ( addition[1] < 1.0 )
                addition[1] = 1.0;
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() >= 10 )
            {
                field_36C = 0;
                field_194 = 0;
            }
            if ( get_elaps_frames() >= 60 )
            {
                set_subseq(6);
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 11 )
            active = false;
        break;
    case 815:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0( 0, 1, 4) )
            {
                active = false;
                return;
            }
            if ( getlvl_height() >= v_inerc + y )
            {
                //shake_camera(5.0); //HACK
                next_subseq();

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 815, x, y, dir, 1, tmp,3);
                chrt->play_sfx( 6);
                y = getlvl_height();
                v_inerc = -v_inerc;
                h_inerc *= 0.2;
                shader_type = 1;
                return;
            }
            if ( health < 0 )
            {
                next_subseq();

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 815, x, y, dir, 1, tmp,3);
                v_inerc = -v_inerc;
                h_inerc = -h_inerc * 0.2;
                shader_type = 1;
                return;
            }
            if ( field_190 == 1 || field_190 == 7 )
            {
                field_378 = enemy->x - x;
                field_37C = enemy->y - y;
                set_subseq(6);
                h_inerc = 0.0;
                v_inerc = 0.0;
                return;
            }
            if ( x > 1380.0 || x < - 100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }

            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            shader_type = 1;
            angZ += 15.0;
            if ( c_A <= 5 )
            {
                active = false;
                return;
            }
            c_A -= 5;
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 2:
        case 5:
            sub_48C5F0( 0);
            scaleY = scaleX -= 0.01;
            if ( c_A <= 10)
            {
                active = false;
                return;
            }
            c_A -= 10;
            c_G -= 10;
            c_B -= 10;
            break;
        case 3:
            scaleY = scaleX += 0.02;
            if ( get_elaps_frames() > 0 )
            {
                if (c_B <= 20)
                {
                    c_B -= 20;
                    c_G -= 20;
                }
                else
                {
                    if (c_A <= 20)
                    {
                        active = false;
                        return;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 20;
                }
            }
            break;
        case 4:
            scaleY = scaleX += 0.1;
            if ( (int)get_elaps_frames() >= 0 )
            {
                if (c_B <= 30)
                {
                    c_B -= 30;
                    c_G -= 30;
                }
                else
                {
                    if (c_A <= 25)
                    {
                        active = false;
                        return;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 25;
                }
            }
            break;
        case 6:
            if ( sub_48C6A0( 0, 1, 4) )
            {
                active = false;
                return;
            }
            x = enemy->x - field_378;
            y = enemy->y - field_37C;
            if ( get_elaps_frames() >= 120 )
            {
                //shake_camera(5.0); //HACK
                set_subseq(1);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet( chrt, NULL, 815, x, y, dir, 1, tmp,3);
                chrt->play_sfx( 6);
                v_inerc = scene_rand_rngf(30) * 0.1 + 5.0;
                h_inerc = 5.0 - scene_rand_rngf(10);
            }
            break;
        default:
            break;
        }
        if ( process() )
            active = false;
        break;
    case 816:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        switch ( get_subseq() )
        {
        case 4:
            scaleY = scaleX += 0.1;
            if ( (int)get_elaps_frames() >= 0 )
            {
                if (c_B <= 30)
                {
                    c_B -= 30;
                    c_G -= 30;
                }
                else
                {
                    if (c_A <= 25)
                    {
                        active = false;
                        return;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 25;
                }
            }
            break;
        case 0:
            angZ += 15.0;
            if ( angZ >= 360.0 )
                angZ = 360.0;
            if ( sub_48C6A0( 0, 1, 4) )
            {
                active = false;
                return;
            }
            if ( (v_inerc < 0.0 && SQR(enemy->x - x) + SQR(enemy->y + 100.0 - y) <= 2500.0 )
                    || getlvl_height() >= v_inerc + y
                    || health < 0 )
            {
                //shake_camera(5.0); //HACK
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 816, x, y, dir, 1, tmp,3);
                chrt->play_sfx( 6);
                shader_type = 1;
                v_inerc = scene_rand_rngf(10) - v_inerc * 0.25;
                h_inerc *= 0.2;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            v_inerc -= 1.0;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            angZ += 15.0;
            if ( c_A <= 5 )
            {
                active = false;
                return;
            }
            c_A -= 5;
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 2:
            sub_48C5F0( 0);
            scaleY = scaleX -= 0.01;
            if ( c_A > 10 )
            {
                c_A -= 10;
                c_G -= 10;
                c_B -= 10;
            }
            else
            {
                active = false;
                return;
            }
            break;
        case 3:
            scaleY = scaleX += 0.04;
            if ( get_elaps_frames() > 0 )
            {
                if (c_B <= 20)
                {
                    c_B -= 20;
                    c_G -= 20;
                }
                else
                {
                    if (c_A <= 20)
                    {
                        active = false;
                        return;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 20;
                }
            }
            break;
        case 5:
            if ( get_elaps_frames() % 2 == 0 )
            {
                float yy = (50 * get_elaps_frames()) + y;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet( chrt, NULL, 816, x, yy, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() == 4 )
            {
                active = false;
                return;
            }
            break;
        default:
            break;
        }
        if ( process() )
            active = false;
        break;
    case 817:
        if ( field_190 != 5 )
        {
            switch ( get_subseq() )
            {
            case 3:
                scaleY = scaleX += 0.02;
                if ( get_elaps_frames() > 0 )
                {
                    if (c_B <= 20)
                    {
                        c_B -= 20;
                        c_G -= 20;
                    }
                    else
                    {
                        if (c_A <= 20)
                        {
                            active = false;
                            return;
                        }
                        c_G = 0;
                        c_B = 0;
                        c_A -= 20;
                    }
                }
                break;
            case 4:
                scaleY = scaleX += 0.1;
                if ( (int)get_elaps_frames() >= 0 )
                {
                    if (c_B <= 30)
                    {
                        c_B -= 30;
                        c_G -= 30;
                    }
                    else
                    {
                        if (c_A <= 25)
                        {
                            active = false;
                            return;
                        }
                        c_G = 0;
                        c_B = 0;
                        c_A -= 25;
                    }
                }
                break;
            case 2:
                sub_48C5F0( 0);
                scaleY = scaleX -= 0.01;
                if ( c_A > 10 )
                {
                    c_A -= 10;
                    c_G -= 10;
                    c_B -= 10;
                }
                else
                {
                    active = false;
                    return;
                }
                break;
            case 0:
                if ( (chrt->get_seq() == 530 || chrt->get_seq() == 531) && chrt->get_subseq() == 0 && chrt->get_frame() == 0 )
                {
                    set_subseq(6);
                    h_inerc = 0.0;
                    v_inerc = 7.5;
                    return;
                }
                if ( sub_48C6A0( 0, 3, 5) )
                {
                    active = false;
                    return;
                }
                if ( getlvl_height() >= v_inerc + y )
                {
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    next_subseq();
                    y = getlvl_height();
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                v_inerc -= 0.5;
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 1:
                if ( (chrt->get_seq() == 530 || chrt->get_seq() == 531) && chrt->get_subseq() == 0 && chrt->get_frame() == 0 )
                {
                    set_subseq(6);
                    h_inerc = 0.0;
                    v_inerc = 7.5;
                    return;
                }
                if ( sub_48C6A0( 0, 3, 5) )
                {
                    active = false;
                    return;
                }
                h_inerc = 2.0;
                v_inerc = 0.0;
                if ( getlvl_height() < y )
                {
                    set_subseq(0);
                    return;
                }
                if ( chrt->skills_1[9] >= 2 && field_36C == 0 )
                {
                    float xx = (enemy->x - x) * dir;
                    if ( xx <= 200.0 && xx >= 0.0 && y < enemy->y )
                    {
                        field_36C = 1;
                        set_subseq(7);
                        h_inerc = 4.0;
                        v_inerc = (chrt->skills_1[9] - 2.0) * 4.0 + 7.0;
                        return;
                    }
                }
                if ( (SQR(x - enemy->x) <= 2500.0 && SQR(y - enemy->y) <= 10000.0 )
                        || getlvl_height() > y
                        || health < 0 )
                {
                    //shake_camera(10.0); //HACK
                    set_subseq(6);
                    shader_type = 1;
                    has_shadow = 0;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet( chrt, NULL, 817, x, y, dir, 1, tmp,3);
                    chrt->play_sfx( 6);
                    y = getlvl_height();
                    v_inerc = 12.0;
                    h_inerc = -10.0;
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 5:
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float yy = (50 * get_elaps_frames()) + y;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet( chrt, NULL, 817, x, yy, dir, 1, tmp,3);
                }
                if ( get_elaps_frames() != 4 )
                {
                    active = false;
                    return;
                }
                break;
            case 6:
                angZ += 15.0;
                if ( c_A <= 5 )
                {
                    active = false;
                    return;
                }
                c_A -= 5;
                v_inerc -= 0.5;
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 7:
                if ( (chrt->get_seq() == 530 || chrt->get_seq() == 531) && chrt->get_subseq() == 0 && chrt->get_frame() == 0 )
                {
                    set_subseq(6);
                    h_inerc = 0.0;
                    v_inerc = 7.5;
                    return;
                }
                if ( sub_48C6A0( 0, 3, 5) )
                {
                    active = false;
                    return;
                }
                v_inerc -= 0.5;
                if ( getlvl_height() >= v_inerc + y )
                {
                    set_subseq(1);
                    y = getlvl_height();
                    v_inerc = 0.0;
                    return;
                }
                if ( (SQR(x - enemy->x) <= 10000.0 && SQR(y - enemy->y) <= 10000.0)
                        || health < 0 )
                {
                    //shake_camera(10.0); //HACK
                    set_subseq(6);
                    shader_type = 1;
                    has_shadow = 0;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet( chrt, NULL, 817, x, y, dir, 1, tmp,3);
                    chrt->play_sfx( 6);
                    v_inerc = 12.0;
                    h_inerc = -10.0;
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 8:
                if ( sub_48C6A0( 0, 3, 5) )
                {
                    active = false;
                    return;
                }
                v_inerc -= 0.5;
                if ( getlvl_height() >= v_inerc + y
                        || (SQR(x - enemy->x) <= 2500.0 && SQR(y - enemy->y) <= 10000.0)
                        || getlvl_height() > y
                        || health < 0 )
                {
                    //shake_camera(10.0); //HACK
                    set_subseq(6);
                    shader_type = 1;
                    has_shadow = 0;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet( chrt, NULL, 817, x, y, dir, 1, tmp,3);
                    chrt->play_sfx( 6);
                    v_inerc = 12.0;
                    h_inerc = -10.0;
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 9:
                if ( (chrt->get_seq() == 530 || chrt->get_seq() == 531) && chrt->get_subseq() == 0 && chrt->get_frame() == 0 )
                {
                    set_subseq(6);
                    h_inerc = 0.0;
                    v_inerc = 7.5;
                    return;
                }
                if ( sub_48C6A0( 0, 3, 5) )
                {
                    active = false;
                    return;
                }
                if ( getlvl_height() >= v_inerc + y )
                {
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    next_subseq();
                    y = getlvl_height();
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                v_inerc -= 0.5;
                x += dir * h_inerc;
                y += v_inerc;
                break;
            case 10:
                if ( (chrt->get_seq() == 530 || chrt->get_seq() == 531) && chrt->get_subseq() == 0 && chrt->get_frame() == 0 )
                {
                    set_subseq(6);
                    h_inerc = 0.0;
                    v_inerc = 7.5;
                    return;
                }
                if ( sub_48C6A0( 0, 3, 5) )
                {
                    active = false;
                    return;
                }
                h_inerc = chrt->skills_1[9] + 3.0;
                v_inerc = 0.0;
                if ( getlvl_height() < y )
                {
                    set_subseq(0);
                    return;
                }
                if ( chrt->skills_1[9] >= 2 )
                {
                    float xx = (enemy->x - x) * dir;
                    if ( xx <= 200.0 && xx >= 0.0 && y < enemy->y )
                    {
                        set_subseq(8);
                        scene_add_effect(this,  1, x, y, dir,  1);
                        scene_play_sfx(1);
                        h_inerc += 3.0;
                        v_inerc = 4.0;
                        return;
                    }
                }
                if ( (SQR(x - enemy->x) <= 2500.0 && SQR(y - enemy->y) <= 10000.0 )
                        || getlvl_height() > y
                        || health < 0 )
                {
                    //shake_camera(10.0); //HACK
                    set_subseq(6);
                    shader_type = 1;
                    has_shadow = 0;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet( chrt, NULL, 817, x, y, dir, 1, tmp,3);
                    chrt->play_sfx( 6);
                    y = getlvl_height();
                    v_inerc = 12.0;
                    h_inerc = -10.0;
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                x += dir * h_inerc;
                y += v_inerc;
                break;
            default:
                break;
            }
        }
        if (process())
            active = false;
        break;
    case 820:
        field_18C = 2;
        if ( get_subseq() <= 4 )
        {
            int16_t tmp = 200;
            if ( chrt->skills_1[2] >= 1 )
                tmp = 500;
            if ( chrt->skills_1[2] >= 2 )
                tmp = 650;
            if ( chrt->skills_1[2] >= 3 )
                tmp = 800;
            if ( chrt->skills_1[2] >= 4 )
                tmp = 950;
            if ( sub_48C6A0( 0, 1, 3) || health <= -tmp )
                set_subseq(5);
        }
        if ( get_subseq() == 0 )
        {
            angZ += 20.0;
            if ( get_elaps_frames() == 18 )
            {
                v_inerc = 0.0;
                h_inerc = 0.0;
                angZ = 0.0;
                next_subseq();
                order = 1;
                return;
            }
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            if ( y < 0.0 )
                y = 0.0;
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= addition[3] + 20 * (chrt->skills_1[2] == 0) )
        {
            next_subseq();
            return;
        }
        if ( get_subseq() == 2 )
        {
            angZ += 40.0;
            if ( get_elaps_frames() >= 9 )
            {
                angZ = 0.0;
                next_subseq();
                return;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( get_elaps_frames() == 0 )
            {
                chrt->play_sfx( 7);
                addition[0] = 45.0;
                addition[1] = 55.0;
            }
            addition[1] -= 5.0;
            if ( addition[1] < -0.5 )
            {
                addition[1] = -0.5;
                field_194 = 0;
            }
            set_vec_speed(addition[0], addition[1]);
            sub_48C5F0( 0);
            if ( field_188 > 0 )
            {
                set_subseq(4);
                return;
            }
            if ( field_36C >= 90 )
            {
                next_subseq();
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
            if ( field_190 && chrt->skills_1[2] >= 3 )
            {
                field_194 = 2;
                set_subseq(7);
                return;
            }
            field_36C += 1;
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 4 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 5 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 6 && sub_526870(5) )
            return;
        if ( get_subseq() == 7 )
        {
            addition[1] -= 5.0;
            if ( addition[1] < -0.5 )
            {
                addition[1] = -0.5;
                field_194 = 0;
            }
            set_vec_speed(addition[0], addition[1]);
            sub_48C5F0( 0);
            if ( field_190 )
            {
                field_36E++;
                if ( field_36E >= 5 )
                {
                    field_36E = 0;
                    field_190 = 0;
                }
            }
            if ( field_188 > 0 )
            {
                set_subseq(4);
                return;
            }
            if ( field_36C >= 90 )
            {
                set_subseq(4);
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
            field_36C += 1;
            x += dir * h_inerc;
            y += v_inerc;
        }
        if (process())
            active = false;
        break;
    case 821:
        field_18C = 6;
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 1 )
            set_subseq( 3);

        if ( get_subseq() == 0 )
        {
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() >= 1 && get_subseq() <= 2 )
        {
            h_inerc -= 2.0;
            if ( field_190 )
                if ( chrt->get_seq() >= 545 && chrt->get_seq() <= 549 )
                    chrt->field_190 = field_190;
            if ( h_inerc < -0.5 )
                h_inerc = -0.5;
            if ( h_inerc <= 0.0 && get_subseq() == 1 )
            {
                field_194 = 0;
                set_subseq(2);
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            c_A -= 10;
        }
        if ( get_subseq() == 3 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 4 )
        {
            scaleX += 0.05;
            scaleY *= 0.8;
            if ( scaleY <= 0.01 )
            {
                active = false;
                return;
            }
            h_inerc = 10.0;
            x += dir * 10.0;
        }
        if ( get_subseq() == 5 )
        {
            scaleY = scaleX += 0.05;
            if ( c_A < 30 )
            {
                active = false;
                return;
            }
            c_A -= 30;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = 25.0;
            chrt->play_sfx(12);
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;
            float yy = y + 4.0;
            float xx = (130 * dir) + x;
            addbullet(chrt, NULL, 821, xx, yy, dir, order, tmp,3);
        }
        break;
    case 822:
        field_18C = 10;
        if ( get_subseq() <= 4 )
        {
            int8_t a1,a2;
            if ( get_subseq() > 2 )
            {
                a1 = 0;
                a2 = 0;
            }
            else
            {
                a1 = 3;
                a2 = 1;
            }
            if ( sub_48C6A0( 0, a2, a1) )
            {
                set_subseq(5);
                return;
            }
        }
        if ( get_subseq() == 0)
        {
            angZ += 20.0;
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.98;
            if ( get_elaps_frames() == 10 )
            {
                v_inerc = 0.0;
                h_inerc = 0.0;
                angZ = -scene_rand_rng(15);
                next_subseq();
                order = 1;
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
        }


        if ( get_subseq() == 1 || get_subseq() == 2 )
        {
            if ( chrt->get_seq() != 550 && chrt->get_seq() != 551 )
            {
                set_subseq(4);
                return;
            }
            if ( chrt->get_subseq() == 1 )
                field_36C = 1;
            if ( field_36C == 1 )
            {
                field_36E++;
                if ( field_36E >= addition[3] )
                {
                    chrt->play_sfx( 14);
                    float yy = y + 15.0;
                    float xx = (30 * dir) + x;
                    float tmp[3];
                    tmp[0] = angZ - scene_rand_rngf(10);
                    tmp[1] = scene_rand_rngf(10) + 15.0 + addition[4];
                    tmp[2] = 6.0;
                    addbullet( chrt, NULL, 822, xx, yy, dir, 1, tmp,3);
                    set_subseq(3);
                    return;
                }
            }
        }
        if ( get_subseq() == 3 && get_elaps_frames() >= 30 )
        {
            angZ = 0.0;
            next_subseq();
            return;
        }
        if ( get_subseq() == 4 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 5 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 6 )
        {
            if ( get_frame() == 0 )
            {
                if ( field_36C )
                {
                    angZ -= 30.0;
                    if ( c_A < 10 )
                    {
                        active = false;
                        return;
                    }
                    c_A -= 10;
                    v_inerc -= 0.25;
                }
                else
                {
                    if ( sub_48C6A0( 0, 0, 4) )
                    {
                        active = false;
                        return;
                    }
                    sub_48C640( 10);
                    if ( field_190 == 6 || field_190 == 2 || field_190 == 4 || field_190 == 8 )
                    {
                        field_36C = 1;
                        h_inerc = -4.0 - scene_rand_rngf(20) * 0.1;
                        v_inerc = scene_rand_rngf(30) * 0.1 + 12.0;
                        sub_4B0750();
                        return;
                    }
                    if ( field_190 == 1 || field_190 == 7 )
                    {
                        field_37C = enemy->x - x;
                        field_380 = enemy->y - y;
                        h_inerc = 0.0;
                        v_inerc = 0.0;
                        set_frame(1);
                        sub_4B0750();
                        return;
                    }
                    v_inerc -= 0.35;
                    h_inerc -= 0.1;
                    if ( h_inerc < 2.0 )
                        h_inerc = 2.0;
                    angZ = -atan2_deg(v_inerc, h_inerc);
                }
            }
            if ( get_frame() == 1 )
            {
                x = enemy->x - field_37C;
                y = enemy->y - field_380;
                if ( get_elaps_frames() >= 10 )
                {
                    if ( c_A < 15 )
                    {
                        active = false;
                        return;
                    }
                    c_A -= 15;
                }
            }
        }
        if ( x > 1780.0 || x < -500.0 || y > 1280.0 || y < -200.0 )
        {
            active = false;
            return;
        }
        x += dir * h_inerc;
        y += v_inerc;
        if ( get_subseq() == 7 && sub_526870(5) )
            return;
        if ( process() )
            active = false;
        break;
    case 825:
        field_18C = 3;
        if ( get_subseq() <= 2 && ( sub_48C6A0( 0, 1, 3) || health <= -750 ) )
            set_subseq(3);
        if ( get_subseq() == 0 )
        {
            set_vec_speed(addition[0], addition[1]);
            addition[0] -= 2.0;
            addition[1] -= 1.0;
            if ( addition[1] < 0.0 )
            {
                addition[1] = 0.0;
                next_subseq();
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            if ( y < 0.0 )
                y = 0.0;
        }
        if ( get_subseq() == 1 )
        {
            field_380 = -atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);
            set_vec_speed(field_380, 2.0);
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet(chrt, this, 825, x, y, dir, 1, tmp,3);
            }
            if ( get_elaps_frames() % 15 == 0 )
                chrt->play_sfx( 4);
            sub_48C5F0(0);
            if ( field_188 > 0 )
            {
                set_subseq(3);
                return;
            }
            if ( field_190 )
            {
                field_36C++;
                if ( field_36C >= 4 )
                {
                    field_36C = 0;
                    field_190 = 0;
                }
            }
            if ( (int32_t)get_elaps_frames() >= 5 * (chrt->skills_1[3] + 18) || field_194 <= 0 )
            {
                next_subseq();
                order = -1;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 3 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc = v_inerc - 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 4 && sub_526870(3) )
            break;
        if ( get_subseq() == 5 )
        {
            angZ += 25.0;
            if ( bul_parent == NULL)
            {
                active = false;
                return;
            }
            if ( bul_parent->get_subseq() == 1 )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                scaleX += 0.1;
                if ( scaleX > 3.0 )
                    scaleX = 2.5;
                scaleY = scaleX;
                if ( c_A > 225 )
                    c_A = 255;
                else
                    c_A += 30;
            }
            else
            {
                if ( c_A < 20 )
                {
                    active = false;
                    return;
                }
                scaleX += 0.1;
                c_A -= 20;
                c_R -= 20;
                c_G -= 20;
            }
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
        {
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 827:
        switch ( get_subseq() )
        {
        case 0:
        case 3:
        {
            sub_48C5F0( 2 * chrt->skills_1[11] + 1);
            if ( field_36C )
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                scaleY = scaleX *= 0.95;
                if ( c_A < 15 )
                {
                    active = false;
                    return;
                }
                c_A -= 15;
            }
            else
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;
                addbullet( chrt, NULL, 827, x, y, dir, 1, tmp,3);

                if ( field_190 == 6 || field_190 == 4 || field_190 == 8 )
                {
                    field_36C = 1;
                    field_194 = 0;
                    return;
                }
                else
                {
                    if ( sub_48C6A0(0, 3, 5) )
                    {
                        active = false;
                        return;
                    }
                    char_alice *alice = (char_alice *)chrt;

                    int32_t doll = alice->field_892;
                    if ( doll > 0 )
                    {
                        if ( SQR(y - alice->field_8AC[doll - 1]) + SQR(x - alice->field_89C[doll - 1]) <= SQR(35) )
                        {
                            x = alice->field_89C[doll - 1];
                            y = alice->field_8AC[doll - 1];
                            alice->field_8BC[doll] = 1;
                            if ( doll == 1 )
                            {
                                addition[1] = -atan2_deg(enemy->y - y + 100.0, (enemy->x - x) * dir);
                            }
                            else
                            {
                                addition[1] = -atan2_deg(alice->field_8AC[doll - 2] - y, (alice->field_89C[doll - 2] - x) * dir);
                            }
                            alice->field_892--;
                            field_190 = 0;
                            field_194 = 1;
                            float tmp[3];
                            tmp[0] = 0.0;
                            tmp[1] = 0.0;
                            tmp[2] = 2.0;
                            addbullet(chrt, NULL, 827, x, y, dir, 1, tmp,3);
                            chrt->play_sfx( 13);
                        }
                    }
                    set_vec_speed(addition[0], addition[1]);
                }
            }
            x += dir * h_inerc;
            y += v_inerc;
            char_alice *alice = (char_alice *)chrt;
            if ( alice->field_892 == 0 )
                break;
            if ( x < -100.0 || x > 1380.0 || y > 1060.0 || y < -260.0 )
            {
                active = false;
                return;
            }
        }
        break;
        case 1:
        case 4:
            scaleY = scaleX *= 0.98;
            if ( c_A <= 5 )
            {
                active = false;
                return;
            }
            c_A -= 5;
            c_G -= 5;
            c_B -= 5;
            break;
        case 2:
            scaleY = scaleX += field_378;
            field_378 -= 0.2;
            if ( field_378 < 0.05 )
                field_378 = 0.05;
            if ( c_A <= 10 )
            {
                active = false;
                return;
            }
            c_A -= 10;
            c_G -= 10;
            c_B -= 10;
            break;
        case 5:
        case 6:
        {
            if ( sub_48C6A0( 0, 3, 5) )
            {
                active = false;
                return;
            }
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;
            addbullet(chrt, NULL, 827, x, y, dir, 1, tmp,3);
            sub_48C5F0( 0);
            char_alice *alice = (char_alice *)chrt;
            int32_t doll = alice->field_892;
            if ( doll > 0 )
            {
                if ( SQR(x - alice->field_89C[doll - 1]) + SQR(y - alice->field_8AC[doll - 1]) <= SQR(15) )
                {
                    x = alice->field_89C[doll - 1];
                    y = alice->field_8AC[doll - 1];
                    alice->field_8BC[doll] = 1;

                    if ( doll == 1 )
                    {
                        addition[1] = -atan2_deg(enemy->y - y + 100.0, (enemy->x - x) * dir);
                    }
                    else
                    {
                        addition[1] = -atan2_deg(alice->field_8AC[doll - 2] - y, (alice->field_89C[doll - 2] - x) * dir);
                    }
                    alice->field_892--;
                    field_190 = 0;
                    field_194 = 1;
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet(chrt, NULL, 827, x, y, dir, 1, tmp,3);
                    chrt->play_sfx( 13);
                }
            }
            set_vec_speed(addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            if ( alice->field_892 == 0 )
                break;
            if ( x < -100.0 || x > 1380.0 || y > 1060.0 || y < -260.0 )
            {
                active = false;
                return;
            }
        }
        break;
        default:
            break;
        }
        if (process())
            active = false;
        break;
    case 830:
        if ( get_subseq() == 0 )
        {
            field_378 += field_37C;
            field_37C -= 1.5;
            if ( field_37C < 0.0 )
                field_37C = 0.0;
            dir = chrt->dir;
            char_alice *alice = (char_alice *)chrt;
            float angl = (4 * alice->field_898) + addition[2] * 120.0;
            x = cos_deg(angl) * field_378 + chrt->x;
            y = sin_deg(angl) * field_378 * 0.25 + chrt->y + 100.0;
            order = 2 * ((int32_t)angl % 360 > 180) - 1;
            if ( chrt->health <= 0 )
            {
                next_subseq();
                h_inerc = 0.0;
                v_inerc = 0.0;
                return;
            }
            if ( (chrt->get_seq() == 565 || chrt->get_seq() == 567)
                    && alice->field_8BC[0] == 1
                    && addition[2] == alice->field_890[0])
            {
                alice->field_890[0]--;
                alice->field_8BC[0] = 0;
                set_seq(831);
                set_subseq(0);
                //get_elaps_frames() = 0; //HACK
                return;
            }
            if ( (chrt->get_seq() == 566 || chrt->get_seq() == 569) && alice->field_8BC[0] == 1 )
            {
                alice->field_890[0]--;
                set_seq(834);
                set_subseq(0);
                //get_elaps_frames() = 0; //HACK
                return;
            }
        }
        if ( get_subseq() == 1 )
        {
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if (process() )
            active = false;
        break;
    case 831:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 3 )
        {
            set_subseq(4);
            h_inerc = 0.0;
            v_inerc = 0.0;
            return;
        }
        if ( get_subseq() == 0)
        {
            field_378 = SQR((50 * chrt->dir) + chrt->x - x);
            field_37C = SQR(chrt->y + 115.0 - y);
            field_380 = sqrt(field_37C + field_378);
            addition[0] = -atan2_deg(chrt->y + 115.0 - y, (50 * chrt->dir) + chrt->x - x);
            addition[1] = field_380 * 0.2;
            if ( addition[1] > 50.0 )
                addition[1] = 50.0;
            set_vec_speed(addition[0], addition[1]);
            if ( h_inerc >= 0.0 )
                dir = 1;
            else
                dir = -1;
            if ( get_elaps_frames() >= 16 )
            {
                next_subseq();
                dir = chrt->dir;
                x = (50 * chrt->dir) + chrt->x;
                y = chrt->y + 115.0;
                return;
            }
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;

                float xx = (60.0 * dir) + x;
                float yy = y + 5.0;
                addbullet(chrt, this, 831, xx, yy, dir, 1, tmp, 3);
                chrt->play_sfx( 9);
            }

            x = (50 * dir) + chrt->x;
            y = chrt->y + 115.0;

            uint16_t frames = 15;
            if ( chrt->skills_1[7] >= 2 )
                frames = 20;
            if ( chrt->skills_1[7] >= 3 )
                frames = 25;
            if ( chrt->skills_1[7] >= 4 )
                frames = 30;
            if ( get_elaps_frames() >= frames
                    || (chrt->get_seq() != 565 && chrt->get_seq() != 567)
                    || chrt->get_subseq() >= 3 )
            {
                field_378 = 0.0;
                field_37C = 0.0;
                field_380 = 0.0;
                next_subseq();
                return;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }

        if ( get_subseq() == 4 )
        {
            if ( 5.0 < h_inerc )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( 5.0 < v_inerc )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            if ( field_36C == 0 )
            {
                if ( get_elaps_frames() >= 40 )
                {
                    field_36C = 1;
                }
                else
                {
                    if ( bul_parent )
                    {
                        x = (60 * dir) + bul_parent->x;
                        y = bul_parent->y + 5.0;
                    }
                    scaleX = scaleY = (get_elaps_frames() & 2) * 0.2 + 1.0;
                }
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    return;
                }
                uint16_t frames = 15;
                if ( chrt->skills_1[7] >= 2 )
                    frames = 20;
                if ( chrt->skills_1[7] >= 3 )
                    frames = 25;
                if ( chrt->skills_1[7] >= 4 )
                    frames = 30;
                if ( get_elaps_frames() >= frames || (chrt->get_seq() != 565 && chrt->get_seq() != 567) || chrt->get_subseq() >= 3 )
                    field_36C = 1;
            }
            if ( field_36C == 1 )
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.02 )
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 6 )
        {
            if ( chrt->get_seq() <= 49 || chrt->get_seq() >= 150 )
            {
                if ( field_36C <= 1 )
                {
                    uint16_t frames = 15;
                    if ( chrt->skills_1[7] >= 2 )
                        frames = 20;
                    if ( chrt->skills_1[7] >= 3 )
                        frames = 25;
                    if ( chrt->skills_1[7] >= 4 )
                        frames = 30;
                    if ( get_elaps_frames() >= frames
                            || (chrt->get_seq() != 565 && chrt->get_seq() != 567)
                            || chrt->get_subseq() >= 3 )
                        field_36C = 2;
                }
            }
            else
            {
                if ( field_36C <= 1 )
                {
                    for (int8_t i = 0; i < 30; i++)
                    {
                        float xx = scene_rand_rngf(20) + (40 * i * dir) + x;
                        float yy = y + 10.0 - scene_rand_rng(20);
                        scene_add_effect(this,  201, xx, yy, dir,  1);
                    }
                    active = false;
                    return;
                }
            }
            if ( field_36C == 0 )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                }
                scaleY += 0.1;
                if ( scaleY > 0.7 )
                {
                    scaleY = 0.7;
                    field_36C = 1;
                    field_194 = 10;
                    return;
                }
            }
            if ( field_36C == 1 )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->field_36C == 1 )
                        field_36C = 2;
                }
                sub_48C5F0(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_36E = 0;
                        field_190 = 0;
                    }
                }
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    return;
                }
            }
        }
        if (process())
            active = false;
        break;
    case 834:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            if ( get_subseq() <= 3 || get_subseq() >= 7 )
            {
                set_subseq(4);
                h_inerc = 0.0;
                v_inerc = 0.0;
                return;
            }
        if ( get_subseq() == 0 )
        {
            char_alice *alice = (char_alice *)chrt;
            float angl = 3 * alice->field_898 + addition[2] * 120.0;
            float tx = cos_deg(angl) * 20.0 + (75 * chrt->dir) + chrt->x;
            float ty = sin_deg(angl) * 80.0 + chrt->y + 100.0;
            field_378 = SQR(tx - x);
            field_37C = SQR(ty - y);
            field_380 = sqrt(field_378 + field_37C);
            addition[0] = -atan2_deg(ty - y, tx - x);
            addition[1] = field_380 * 0.2;
            if ( addition[1] > 50.0 )
                addition[1] = 50.0;
            set_vec_speed(addition[0], addition[1]);
            if ( h_inerc >= 0.0 )
                dir = 1;
            else
                dir = -1;
            if ( get_elaps_frames() >= 16 )
            {
                next_subseq();
                dir = chrt->dir;
                x = tx;
                y = ty;
                return;
            }
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;

                float xx = (60.0 * dir) + x;
                float yy = y + 5.0;
                addbullet(chrt, this, 834, xx, yy, dir, 1, tmp, 3);
                chrt->play_sfx( 9);
            }
            char_alice *alice = (char_alice *)chrt;
            float angl = 3 * alice->field_898 + addition[2] * 120.0;
            float tx = cos_deg(angl) * 20.0 + (75 * chrt->dir) + chrt->x;
            float ty = sin_deg(angl) * 80.0 + chrt->y + 100.0;
            x = tx;
            y = ty;

            if ( (chrt->get_seq() != 566 && chrt->get_seq() != 569)
                    || chrt->get_subseq() >= 3 )
            {

                field_378 = 0.0;
                field_37C = 0.0;
                field_380 = 0.0;
                next_subseq();
                return;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }

        if ( get_subseq() == 4 )
        {
            if ( 5.0 < h_inerc )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( 5.0 < v_inerc )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            if ( field_36C == 0)
            {
                if ( get_elaps_frames() >= 40 )
                {
                    field_36C = 1;
                }
                else
                {
                    if ( bul_parent )
                    {
                        x = (60 * dir) + bul_parent->x;
                        y = bul_parent->y + 5.0;
                    }
                    scaleY = scaleX = (get_elaps_frames() & 2) * 0.2 + 1.0;
                }
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    return;
                }
                if ( (chrt->get_seq() != 566 && chrt->get_seq() != 569) || chrt->get_subseq() >= 3 )
                    field_36C = 1;
            }
            if ( field_36C == 1 )
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.02 )
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 6 )
        {
            if ( chrt->get_seq() <= 49 || chrt->get_seq() >= 150 )
            {
                if ( field_36C <= 1 )
                    if ( (chrt->get_seq() != 566 && chrt->get_seq() != 569) || chrt->get_subseq() >= 3 )
                        field_36C = 2;
            }
            else
            {
                if ( field_36C <= 1 )
                {
                    for (int8_t i = 0; i < 20; i++)
                    {
                        float xx = scene_rand_rngf(30) + (60 * i * dir) + x;
                        float yy = y + 10.0 - scene_rand_rng(20);
                        scene_add_effect(this,  201, xx, yy, dir,  1);
                    }
                    active = false;
                    return;
                }
            }
            if ( field_36C == 0 )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                }
                scaleY += 0.1;
                if ( scaleY > 0.7 )
                {
                    scaleY = 0.7;
                    field_36C = 1;
                    field_194 = 10;
                    return;
                }
            }
            if ( field_36C == 1 )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->field_36C == 1 )
                        field_36C = 2;
                }
                sub_48C5F0(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_36E = 0;
                        field_190 = 0;
                    }
                }
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 7 && get_elaps_frames() >= 16 )
        {
            next_subseq();
            return;
        }
        if ( get_subseq() == 8 )
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                float xx = (60 * dir) + x;
                float yy = y + 5.0;
                addbullet(chrt, this, 834, xx, yy, dir, 1, tmp, 3);
                chrt->play_sfx( 9);
            }
            if ( (chrt->get_seq() != 566 && chrt->get_seq() != 569)
                    || chrt->get_subseq() >= 3 )
            {
                set_subseq(2);
                return;
            }
        }
        if (process())
            active = false;
        break;
    case 849:
        switch ( get_subseq() )
        {
        case 1:
        case 2:
        case 3:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 3 )
            {
                set_subseq(4);
                return;
            }
            if ( chrt->get_seq() == 301 || get_subseq() > 2 )
            {
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
                {
                    h_inerc = 30.0;
                    v_inerc = 5.0;
                }
                if ( get_subseq() <= 2 )
                {
                    h_inerc -= 3.0;
                    if ( h_inerc <= 1.0 )
                        h_inerc = 1.0;
                    v_inerc -= 0.5;
                    if ( v_inerc < 0.5 )
                        v_inerc = 0.5;
                    field_378 += h_inerc * dir;
                    field_37C += v_inerc;
                    x = (30 * dir) + chrt->x + field_378;
                    y = chrt->y + 100.0 + field_37C;
                    chrt->field_190 = field_190;
                    if ( get_subseq() == 2 && get_elaps_frames() % 2 == 0 && get_frame() >= 1 )
                    {
                        field_380 = scene_rand_rngf(90) - 45.0;
                        float tmp[3];
                        tmp[0] = field_380;
                        tmp[1] = 0.0;
                        tmp[2] = 5.0;
                        float xx = cos_deg(-field_380) * 100.0 * dir + x;
                        float yy = sin_deg(-field_380) * 100.0 + y;
                        addbullet(chrt, NULL, 849, xx, yy, dir, 1, tmp ,3);
                    }
                }
                if ( get_subseq() == 3 )
                {
                    if ( sub_5269B0() )
                        return;
                    x += h_inerc;
                    y += v_inerc;
                }
            }
            else
            {
                set_subseq(3);
                field_378 = 0.0;
                return;
            }
            break;
        case 4:
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
            break;
        case 5:
            scaleX += 0.01;
            scaleY *= 0.8;
            if ( scaleY <= 0.05 )
            {
                active = false;
                return;
            }
            set_vec_speed(addition[0], 15.0);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 6:
        case 7:
        case 8:
        case 26:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 7 )
            {
                set_subseq(4);
                field_378 = 0.0;
                return;
            }
            if ( chrt->get_seq() != 302 && get_subseq() <= 7 )
            {
                set_subseq(3);
                field_378 = 0.0;
                field_37C = 0.0;
                return;
            }
            if ( get_subseq() == 6 )
            {
                if ( bul_parent )
                {
                    x = dir * field_378 + bul_parent->x;
                    y = bul_parent->y + field_37C;
                    field_378 += cos_deg(addition[0]) * addition[3] * 5.0;
                    field_37C += sin_deg(addition[0]) * addition[3] * 15.0;
                }
                else
                {
                    set_subseq(3);
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }

            if ( get_subseq() == 7 )
            {
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 9.0;

                    float yy = sin_deg(addition[0]) * 15.0 + y + 3.0;
                    float xx = (cos_deg(addition[0]) * 5.0 + 135.0) * dir + x;
                    addbullet(chrt, NULL, 849, xx, yy, dir, 1, tmp, 3);
                }
                if ( bul_parent )
                {
                    x = field_378 * dir + bul_parent->x;
                    y = bul_parent->y + field_37C;
                }
                else
                {
                    set_subseq(3);
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            if ( get_subseq() == 8 || get_subseq() == 26 )
            {
                if ( ((chrt->get_seq() > 49 && chrt->get_seq() < 150) || chrt->get_seq() != 302) && get_frame() <= 1 )
                {
                    set_frame(2);
                    return;
                }
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 8 )
                {
                    field_194 = 1;
                    field_190 = 0;
                    h_inerc = 30.0;
                    v_inerc = 0.0;
                }
                h_inerc -= 3.0;
                if ( h_inerc <= 0.5 )
                    h_inerc = 0.5;
                field_378 += h_inerc * dir;
                field_37C += v_inerc;
                x = (110 * dir) + chrt->x + field_378;
                y = chrt->y + 105.0 + field_37C;
                if ( get_frame() == 1 )
                    chrt->field_190 = field_190;
                if ( get_frame() == 2 && get_frame_time() == 10 )
                {
                    active = false;
                    return;
                }
            }
            break;
        case 9:
            scaleX += 0.05;
            scaleY *= 0.85;
            if ( c_A < 15 )
            {
                active = false;
                return;
            }
            c_A -= 15;
            h_inerc = 10.0;
            x += dir * 10.0;
            break;
        case 10:
            if ( sub_526870(4) )
                return;
            break;
        case 11:
        case 12:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            {
                set_subseq( 4);
                angZ = 0.0;
                field_378 = 0.0;
                return;
            }
            if ( chrt->get_seq() != 304 )
            {
                set_subseq( 3);
                angZ = 0.0;
                field_378 = 0.0;
                field_37C = 0.0;
                return;
            }
            set_vec_speed(addition[0], addition[1]);
            addition[1] -= 4.0;
            if ( addition[1] <= 1.0 )
                addition[1] = 1.0;
            field_378 += h_inerc * dir;
            field_37C += v_inerc;
            x = (30 * dir) + chrt->x + field_378;
            y = chrt->y + 100.0 + field_37C;
            if ( field_190 )
                chrt->field_190 = field_190;
            if ( get_subseq() == 12 )
            {
                if ( get_elaps_frames() >= 3 )
                    field_194 = 0;
                if ( get_elaps_frames() >= 10 )
                {
                    set_subseq(3);
                    angZ = 0.0;
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            break;
        case 13:
            scaleX += 0.05;
            scaleY *= 0.85;
            if ( c_A < 15 )
            {
                active = false;
                return;
            }
            c_A -= 15;
            set_vec_speed(addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 14:
        case 15:
        case 16:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 15 )
            {
                set_subseq(4);
                field_378 = 0.0;
                return;
            }
            if ( (chrt->get_seq() != 307 || chrt->get_subseq() == 1) && get_subseq() <= 15 )
            {
                set_subseq(3);
                field_378 = 0.0;
                field_37C = 0.0;
                return;
            }
            if ( get_subseq() == 14 )
            {
                if ( bul_parent )
                {
                    x = dir * field_378 + bul_parent->x;
                    y = bul_parent->y + field_37C;
                    field_378 = cos_deg(addition[0]) * 5.0 + field_378;
                    field_37C = sin_deg(addition[0]) * 10.0 + field_37C;
                }
                else
                {
                    set_subseq(3);
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            if ( get_subseq() == 15 )
            {
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 9.0;

                    float xx = (cos_deg(addition[0]) * 5.0 + 135.0) * dir + x;
                    float yy = sin_deg(addition[0]) * 15.0 + y + 3.0;
                    addbullet(chrt, NULL, 849, xx, yy, dir, 1, tmp, 3);
                }
                if ( bul_parent )
                {
                    x = field_378 * dir + bul_parent->x;
                    y = bul_parent->y + field_37C;
                }
                else
                {
                    set_subseq(3);
                    if ( x - chrt->x > 0.0 )
                        dir = -1;
                    if ( x - chrt->x < 0.0 )
                        dir = 1;
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            if ( get_subseq() == 16 )
            {
                if ( ((chrt->get_seq() > 49 && chrt->get_seq() < 150) || chrt->get_seq() != 307 || chrt->get_subseq() == 1)
                        && get_frame() <= 1 )
                {
                    set_frame(2);
                    return;
                }
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
                {
                    field_194 = 1;
                    field_190 = 0;
                    h_inerc = 30.0;
                    v_inerc = 0.0;
                }
                h_inerc -= 3.0;
                if ( h_inerc <= 0.5 )
                    h_inerc = 0.5;
                field_378 += h_inerc * dir;
                field_37C += v_inerc;
                x = (50 * dir) + chrt->x + field_378;
                y = chrt->y + 140.0 + field_37C;
                if ( chrt->get_seq() == 307 && chrt->get_subseq() == 0)
                    chrt->field_190 = field_190;
                if ( get_frame() == 2 && get_frame_time() == 10 )
                {
                    active = false;
                    return;
                }
            }
            break;
        case 17:
        case 18:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 18 )
            {
                set_subseq(4);
                field_378 = 0.0;
                return;
            }
            if ( chrt->get_seq() != 308 && get_subseq() <= 18 )
            {
                set_subseq(3);
                field_378 = 0.0;
                field_37C = 0.0;
                return;
            }
            if ( get_subseq() == 17 )
            {
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
                {
                    field_194 = 0;
                    field_190 = 0;
                }
                x = (field_378 + 25.0) * dir + chrt->x;
                y = chrt->y + 95.0 + field_37C;
                set_vec_speed(addition[0], addition[1]);
                field_378 += h_inerc;
                field_37C += v_inerc;
            }
            if ( get_subseq() == 18 )
            {
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
                {
                    float tmp[3];
                    tmp[0] = 45.0;
                    tmp[1] = 2.0;
                    tmp[2] = 13.0;
                    addbullet(chrt, NULL, 849, x, y, dir, 1, tmp,3);
                    addition[0] = 45.0;
                    addition[1] = 30.0;
                }
                x = (field_378 + 25.0) * dir + chrt->x;
                y = chrt->y + 95.0 + field_37C;
                set_vec_speed(addition[0], addition[1]);
                addition[1] -= 3.0;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;
                if ( get_elaps_frames() >= 8 )
                    field_194 = 0;
                field_378 += h_inerc;
                field_37C += v_inerc;
                if ( get_elaps_frames() >= 26 )
                {
                    set_subseq(3);
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            break;
        case 19:
        case 20:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            {
                set_subseq(4);
                return;
            }
            if ( chrt->get_seq() != 408 && get_subseq() <= 20 )
            {
                set_subseq(3);
                field_378 = 0.0;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 19 )
            {
                h_inerc = 30.0;
                v_inerc = 5.0;
            }
            if ( get_subseq() <= 20 )
            {
                h_inerc -= 3.0;
                if ( h_inerc <= 1.0 )
                    h_inerc = 1.0;
                v_inerc -= 0.5;
                if ( v_inerc < 0.5 )
                    v_inerc = 0.5;
                field_378 += h_inerc * dir;
                field_37C += v_inerc;
                x = (30 * dir) + chrt->x + field_378;
                y = chrt->y + 100.0 + field_37C;
                chrt->field_190 = field_190;
                if ( get_subseq() == 20 )
                {
                    if ( (get_elaps_frames() % 2) == 0 && get_frame() >= 1 )
                    {
                        field_380 = scene_rand_rngf(90) - 45.0;
                        float tmp[3];
                        tmp[0] = field_380;
                        tmp[1] = 0.0;
                        tmp[2] = 5.0;

                        float xx = cos_deg(-field_380) * 100.0 * dir + x;
                        float yy = sin_deg(-field_380) * 100.0 + y;
                        addbullet(chrt, NULL, 849, xx, yy, dir, 1, tmp ,3);
                    }
                }
            }
            break;
        case 21:
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 22.0;
                addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
            }
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            {
                set_subseq(4);
                return;
            }
            if ( chrt->get_seq() != 418 )
            {
                set_subseq(3);
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                field_378 = 0.0;
                return;
            }
            x = (cos_deg(10 * (18 - get_elaps_frames())) * 150.0 + 150.0) * dir + chrt->x;
            y = sin_deg(10 * (18 - get_elaps_frames())) * 50.0 + chrt->y + 50.0;
            scaleX = scaleY = sin_deg(10 * (get_elaps_frames() - 18)) * 0.15 + 1.0;
            if ( get_elaps_frames() >= 18 )
                order = 1;
            if ( get_elaps_frames() == 17 )
            {
                field_194 = 1;
                field_190 = 0;
            }
            if ( get_elaps_frames() == 19 )
                field_194 = 0;
            if ( field_190 )
                chrt->field_190 = field_190;
            if ( get_elaps_frames() >= 35 )
            {
                active = false;
                return;
            }
            break;
        case 22:
            if ( !bul_parent )
            {
                if ( c_A < 30 )
                {
                    active = false;
                    return;
                }
                scaleX += 0.1;
                c_A -= 30;
                c_R -= 30;
                c_G -= 30;
                angZ += 25.0;
            }
            else
            {
                order = bul_parent->order;
                if ( bul_parent->get_subseq() == 21 || bul_parent->get_subseq() == 23 )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    scaleY = scaleX = bul_parent->scaleX * 2;
                    if ( c_A > 225 )
                        c_A = 255;
                    else
                        c_A += 30;
                    angZ +=25.0;
                }
                else
                {
                    active = false;
                    return;
                }
            }
            break;
        case 23:
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 22.0;
                addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
            }
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            {
                set_subseq(4);
                return;
            }
            if ( chrt->get_seq() != 418 )
            {
                set_subseq(3);
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                field_378 = 0.0;
                return;
            }
            x = (cos_deg(10 * (18 + get_elaps_frames())) * 150.0 + 150.0) * dir + chrt->x;
            y = sin_deg(10 * (18 + get_elaps_frames())) * 50.0 + chrt->y + 50.0;
            scaleX = scaleY = sin_deg(10 * (-get_elaps_frames() - 18)) * 0.15 + 1.0;
            if ( get_elaps_frames() >= 18 )
                order = -1;
            if ( get_elaps_frames() == 17 )
            {
                field_194 = 1;
                field_190 = 0;
            }
            if ( get_elaps_frames() == 19 )
                field_194 = 0;
            if ( field_190 )
                chrt->field_190 = field_190;
            if ( get_elaps_frames() >= 35 )
            {
                active = false;
                return;
            }
            break;
        case 24:
        case 25:
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 24 )
            {
                set_subseq(4);
                field_378 = 0.0;
                return;
            }
            if ( chrt->get_seq() == 309 && chrt->get_subseq() != 4 )
            {
                if ( get_subseq() == 24 )
                {
                    if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
                    {
                        field_194 = 0;
                        field_190 = 0;
                    }
                    x = (field_378 + 25.0) * dir + chrt->x;
                    y = chrt->y + 95.0 + field_37C;
                    set_vec_speed(addition[0], addition[1]);
                    field_378 += h_inerc;
                    field_37C += v_inerc;
                }
            }
            else
            {
                if ( get_subseq() <= 24 )
                {
                    set_subseq(3);
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            if ( get_subseq() == 25 )
            {
                if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
                {
                    float tmp[3];
                    tmp[0] = -45.0;
                    tmp[1] = 2.0;
                    tmp[2] = 13.0;
                    addbullet(chrt, NULL, 849, x, y, dir, 1, tmp,3);
                    addition[0] = -45.0;
                    addition[1] = 30.0;
                }
                x = (field_378 + 30.0) * dir + chrt->x;
                y = chrt->y + 120.0 + field_37C;
                set_vec_speed(addition[0], addition[1]);
                addition[1] -= 3.0;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;
                if ( get_elaps_frames() >= 8 )
                    field_194 = 0;
                field_378 += h_inerc;
                field_37C += v_inerc;
                if ( get_elaps_frames() >= 18 )
                {
                    set_subseq(3);
                    field_378 = 0.0;
                    field_37C = 0.0;
                    return;
                }
            }
            break;
        default:
            break;
        }
        if ( process() )
        {
            active = false;
            return;
        }

        if ( get_subseq() == 2 || get_subseq() == 20)
            if ( get_frame() >= 1 &&  get_frame_time() == 0)
            {
                scene_play_sfx(27);
                field_194 = 1;
                field_190 = 0;
            }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
        {
            if ( get_subseq() == 21 )
                set_subseq(3);
            if ( get_subseq() == 3 )
            {
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                field_378 = 0.0;
            }
            if ( get_subseq() == 12 )
            {
                scene_play_sfx(27);
                float tmp[3];
                tmp[0] = addition[0];
                tmp[1] = 3.0;
                tmp[2] = 13.0;
                addbullet(chrt, NULL, 849, x, y, dir, 1, tmp,3);
            }
        }
        break;
    case 850:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( get_subseq() == 0 )
        {
            if ( !chrt->time_stop )
                field_360 = 0;
            angZ += 30.0;
            if ( getlvl_height() >= v_inerc + y )
            {
                shader_type = 1;
                //shake_camera(10.0); // HACK
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;

                y = getlvl_height();
                addbullet(chrt, NULL, 850, x, y, dir, 1, tmp, 3);
                chrt->play_sfx(21);
                v_inerc *= -0.5;
                h_inerc *= 0.2;
                break;
            }
            v_inerc -= 1.0;
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 1 )
        {
            angZ += 15.0;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            sub_48C5F0(0);
            scaleY = scaleX -= 0.005;
            if ( c_A <= 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
            c_G -= 5;
            c_B -= 5;
        }
        if ( get_subseq() == 3 )
        {
            scaleX = scaleY += 0.2;
            if (get_elaps_frames() > 0)
            {
                if ( c_B > 25 )
                {
                    if ( c_A <= 25 )
                    {
                        active = false;
                        break;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 25;
                }
                else
                {
                    c_G -= 25;
                    c_B -= 25;
                }
            }
        }
        if ( get_subseq() == 4 )
        {
            scaleY = scaleX += 0.01;
            if (get_elaps_frames() > 0)
            {
                if ( c_B < 25 )
                {
                    c_G = 0;
                    c_B = 0;
                }
                else
                {
                    c_G -= 25;
                    c_B -= 25;
                }
                if ( c_A < 25 )
                {
                    active = false;
                    break;
                }
                else
                    c_A -= 25;
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleY = scaleX += 0.01;
            set_vec_speed(addition[0], addition[1]);
            addition[1] -= 1.5;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;
            x += dir * h_inerc;
            y += v_inerc * 0.2 ;
            if ( c_A < 5 )
            {
                active = false;
                break;
            }
            c_A -= 5;
        }
        if ( process() )
        {
            active = false;
            break;
        }
        break;
    case 851:
        if ( get_subseq() <= 1 )
        {
            field_378 += field_380 * dir;
            field_380 -= 1.5;
            if ( field_380 < 1.0 )
                field_380 = 1.0;
            field_374 += 3;
            field_372 += 4 * dir;
            if ( field_374 >= 90 )
                field_374 = 90;
            if ( get_subseq() == 1 )
                field_384 += 3.0;
            x = sin_deg(field_374) * field_384 * cos_deg(addition[3] + field_372) + field_378;
            y = sin_deg(field_374) * field_384 * sin_deg(addition[3] + field_372) + field_37C;
        }
        if (get_subseq() == 0 && field_380 == 1.0)
        {
            chrt->play_sfx(39);
            next_subseq();
            order = 1;
            field_194 = 1;
            break;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0 )
            {
                float tmp[4];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                tmp[3] = 0.0;
                addbullet(chrt, this, 851, x, y, dir, 1, tmp, 4);
            }
            sub_48C5F0(0);
            if ( field_190 )
            {
                field_370++;
                if ( field_370 >= 30 )
                {
                    field_370 = 0;
                    field_190 = 0;
                    field_194 = 1;
                }
            }
            if ( get_elaps_frames() >= 120 )
            {
                field_194 = 0;
                next_subseq();
                order = -1;
                field_378 = 0.0;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 3 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if (get_subseq() == 4 && sub_526870(3))
            return;
        if ( get_subseq() == 5 )
        {
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            if ( bul_parent->get_subseq() == 1 )
            {
                if ( c_A > 225 )
                    c_A = 255;
                else
                    c_A += 30;
                x = bul_parent->x;
                y = bul_parent->y;
            }
            else
            {
                if ( c_A < 30 )
                {
                    active = false;
                    break;
                }
                scaleY = scaleX += 0.15;
                c_A -= 30;
            }
            angZ += 25.0;
        }
        if ( process() )
        {
            active = false;
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
        {
            order = -1;
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 852:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 3 )
        {
            set_subseq(4);
            h_inerc = 0.0;
            v_inerc = 0.0;
            break;
        }
        if ( get_subseq() == 0 )
        {
            float xx = (50 * chrt->dir) + chrt->x - x;
            float yy = chrt->y + 115.0 - y;
            field_378 = SQR(xx);
            field_37C = SQR(yy);
            field_380 = sqrt(field_37C + field_378);
            addition[0] = -atan2_deg(yy, xx);
            addition[1] = field_380 * 0.2;
            if ( addition[1] > 50.0 )
                addition[1] = 50.0;
            set_vec_speed(addition[0], addition[1]);
            if ( h_inerc >= 0.0 )
                dir = 1;
            else
                dir = -1;
            if ( get_elaps_frames() >= 16 )
            {
                next_subseq();
                dir = chrt->dir;
                x = (50 * chrt->dir) + chrt->x;
                y = chrt->y + 115.0;
                break;
            }
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 1)
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                float xx = (60 * dir) + x;
                float yy = y + 5.0;
                addbullet(chrt, this, 852, xx, yy, dir, 1, tmp, 3);
                chrt->play_sfx( 23);
            }
            x = (50 * dir) + chrt->x;
            y = chrt->y + 115.0;

            if ( (chrt->get_seq() != 602 && chrt->get_seq() != 652) || chrt->get_seq() >= 3 )
            {
                field_378 = 0.0;
                field_37C = 0.0;
                field_380 = 0.0;
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 4 )
        {
            if ( 5.0 < h_inerc )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( 5.0 < v_inerc )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            if ( field_36C == 0)
            {
                if ( get_elaps_frames() >= 60 )
                {
                    field_36C = 1;
                }
                else
                {
                    if ( bul_parent )
                    {
                        x = (60 * dir) + bul_parent->x;
                        y = bul_parent->y + 5.0;
                    }
                    scaleY = scaleX = (get_elaps_frames() & 2) * 0.2 + 1.0;
                }
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    break;
                }
                if ( (chrt->get_seq() != 602 && chrt->get_seq() != 652) || chrt->get_subseq() == 3 )
                    field_36C = 1;
            }
            else if ( field_36C == 1 )
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.02 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( get_subseq() == 6 )
        {
            if ( field_36C <= 1 )
            {
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    break;
                }
                else
                {
                    if ( (chrt->get_seq() != 602 && chrt->get_seq() != 652) || chrt->get_subseq() == 3 )
                        field_36C = 2;
                }
            }
            if ( field_36C == 0)
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                }
                scaleY += 0.15;
                if ( scaleY > 1.0 )
                {
                    scaleY = 1.0;
                    field_36C = 1;
                    field_194 = 20;
                    break;
                }
            }
            else if ( field_36C == 1 )
            {
                if ( (get_elaps_frames() % 2) == 0 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 7.0;
                    float xx = scene_rand_rngf(960) * dir + x;
                    addbullet(chrt, this, 852, xx, y, dir, 1, tmp, 3);
                }
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->field_36C == 1 )
                        field_36C = 2;
                }
                sub_48C5F0(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_36E = 0;
                        field_190 = 0;
                    }
                }
            }
            else if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( get_subseq() == 7 )
        {
            scaleY = scaleX += 0.05;
            angZ += 30.0;
            if ( bul_parent )
                y = bul_parent->y;
            if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
            {
                active = false;
                break;
            }
            if ( c_A < 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            c_G -= 10;
            c_B -= 10;
            x += (25 * dir);
            if ( x > 1380.0 || x < -100.0 )
            {
                active = false;
                break;
            }
        }
        if ( process() )
            active = false;
        break;
    case 853:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( get_subseq() == 0)
        {
            angZ += 30.0;
            if ( getlvl_height() >= v_inerc + y )
            {
                shader_type = 1;
                //shake_camera(10.0); // HACK
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                y = getlvl_height();
                addbullet(chrt, NULL, 853, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 25);
                v_inerc = 17.5;
                h_inerc *= 0.2;
                break;
            }
            else
            {
                v_inerc -= 2.0;
                x += dir * h_inerc;
                y += v_inerc;
            }
        }
        if ( get_subseq() == 1 )
        {
            angZ += 15.0;
            if ( c_A <= 10 )
            {
                active = false;
                break;
            }
            c_A -= 10;
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            sub_48C5F0(0);
            scaleY = scaleX -= 0.005;
        }
        if ( get_subseq() == 3 )
        {
            scaleY = scaleX += 0.3;
            if ( get_elaps_frames() > 0 )
            {
                if ( c_B > 25 )
                {
                    if ( c_A <= 25 )
                    {
                        active = false;
                        break;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 25;
                }
                else
                {
                    c_G -= 25;
                    c_B -= 25;
                }
            }
        }
        if ( get_subseq() == 4 )
        {
            scaleY = scaleX += 0.05;
            if ( (int)get_elaps_frames() >= 0 )
            {
                if ( c_B < 25 )
                {
                    c_G = 0;
                    c_B = 0;
                }
                else
                {
                    c_G -= 25;
                    c_B -= 25;
                }
                if ( c_A < 25 )
                {
                    active = false;
                    break;
                }
                c_A -= 25;
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleY = scaleX += 0.01;
            set_vec_speed(addition[0], addition[1]);
            addition[1] -= 1.5;
            if ( addition[1] < 0.5 )
            {
                addition[1] = 0.5;
                if ( c_A < 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
            x += dir * h_inerc;
            y += v_inerc * 0.2;
        }
        if ( process() )
        {
            active = false;
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
            active = false;
        break;
    case 854:
        if ( get_subseq() <= 1 )
        {
            field_380 -= 2.0;
            if ( addition[3] <= 359.0 )
            {
                if ( field_380 < 2.0 )
                    field_380 = 2.0;
                field_374 += 3;
                field_372 += 4 * dir;
                if ( field_374 >= 90 )
                    field_374 = 90;
                x = sin_deg(field_374) * 150.0 * cos_deg(addition[3] + field_372) + field_378;
                y = sin_deg(field_374) * 150.0 * sin_deg(addition[3] + field_372) + field_37C;
            }
            else
            {
                if ( field_380 < 2.0 )
                    field_380 = 2.0;
                field_374 += 3;
                field_372 += -4 * dir;
                if ( field_374 >= 90 )
                    field_374 = 90;
                x = sin_deg(field_374) * 250.0 * cos_deg(addition[3] + field_372) + field_378;
                y = sin_deg(field_374) * 250.0 * sin_deg(addition[3] + field_372) + field_37C;
            }
        }
        if ( get_subseq() == 0)
        {
            field_194 = 0;
            if ( field_380 <= 2.0)
            {
                next_subseq();
                order = 1;
                field_194 = 1;
                break;
            }
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0)
            {
                float tmp[4];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                if ( addition[3] >= 360.0 )
                {
                    tmp[2] = 6.0;
                    tmp[3] = 0.0;
                }
                else
                {
                    tmp[2] = 5.0;
                    tmp[3] = 0.0;
                }
                addbullet(chrt, this, 854, x, y, dir, 1, tmp, 4);
            }
            sub_48C5F0(0);
            if ( field_190 )
            {
                field_370++;
                if ( field_370 >= 30 )
                {
                    field_370 = 0;
                    field_190 = 0;
                    field_194 = 1;
                }
            }
            if ( get_elaps_frames() >= 120 )
            {
                field_194 = 0;
                next_subseq();
                order = -1;
                field_378 = 0.0;
                if ( x - chrt->x > 0.0 )
                    dir = -1;
                if ( x - chrt->x < 0.0 )
                    dir = 1;
                break;
            }
        }
        if ( get_subseq() == 2 )
        {
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 3 )
        {
            if ( 5.0 < h_inerc )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( 5.0 < v_inerc )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 4 && sub_526870(3) )
            return;
        if ( get_subseq() == 5 || get_subseq() == 6 )
        {
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            if ( bul_parent->get_subseq() == 1 )
            {
                if ( c_A > 225 )
                    c_A = 255;
                else
                    c_A += 30;
                x = bul_parent->x;
                y = bul_parent->y;
            }
            else
            {
                if ( c_A < 30 )
                {
                    active = false;
                    break;
                }
                scaleY = scaleX += 0.15;
                c_A -= 30;
            }
            angZ += 25.0;
        }
        if ( process() )
        {
            active = false;
            break;
        }
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2)
        {
            order = -1;
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 855:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 3 )
        {
            set_subseq(4);
            h_inerc = 0.0;
            v_inerc = 0.0;
            break;
        }
        if ( get_subseq() == 0)
        {
            char_alice *alice = (char_alice *)chrt;
            float angl = (4 * alice->field_898) + addition[3] * 60.0;
            float tx = cos_deg(angl) * (field_388 * 0.25 + 20.0) + (75 * alice->dir) + alice->x;
            float xx = tx - x;
            float ty = sin_deg(angl) * (field_388 + 80.0) + chrt->y + 100.0;
            float yy = ty - y;
            field_378 = SQR(xx);
            field_37C = SQR(yy);
            field_380 = sqrt(field_37C + field_378);
            addition[0] = -atan2_deg(yy, xx);
            addition[1] = field_380 * 0.2;
            if ( addition[1] > 50.0 )
                addition[1] = 50.0;
            set_vec_speed(addition[0], addition[1]);
            if ( h_inerc >= 0.0 )
                dir = 1;
            else
                dir = -1;
            if ( get_elaps_frames() >= 16 )
            {
                next_subseq();
                dir = chrt->dir;
                x = tx;
                y = ty;
                break;
            }
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                float yy = y + 5.0;
                float xx = (60 * dir) + x;
                addbullet(chrt, this, 855, xx, yy, dir, 1, tmp, 3);
                chrt->play_sfx( 27);
            }
            char_alice *alice = (char_alice *)chrt;
            float angl = (4 * alice->field_898) + addition[3] * 60.0;
            x = cos_deg(angl) * (field_388 * 0.25 + 20.0) + (75 * alice->dir) + alice->x;
            y = sin_deg(angl) * (field_388 + 80.0) + chrt->y + 100.0;
            field_388 += 2.0;
        }
        if ( get_subseq() == 1 )
        {
            if ( chrt->get_seq() != 605 || chrt->get_subseq() >= 3 )
            {
                field_378 = 0.0;
                field_37C = 0.0;
                field_380 = 0.0;
                next_subseq();
                break;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( sub_5269B0() )
                break;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 4 )
        {
            if ( 5.0 < h_inerc )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( 5.0 < v_inerc )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            if ( field_36C == 0)
            {
                if ( get_elaps_frames() >= 90 )
                {
                    field_36C = 1;
                }
                else
                {
                    if ( bul_parent )
                    {
                        x = (60 * dir) + bul_parent->x;
                        y = bul_parent->y + 5.0;
                    }
                    scaleY = scaleX = (get_elaps_frames() & 2) * 0.2 + 1.0;
                }
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    break;
                }
                if ( chrt->get_seq() != 605 || get_subseq() == 3 )
                    field_36C = 1;
            }
            if ( field_36C == 1 )
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.02 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( get_subseq() == 6 )
        {
            if ( field_36C <= 1 )
            {
                if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                {
                    active = false;
                    break;
                }
                else
                {
                    if ( chrt->get_seq() != 605 )
                        field_36C = 2;
                }
            }
            if ( field_36C == 0)
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                }
                scaleY += 0.1;
                if ( scaleY > 0.5 )
                {
                    scaleY = 0.5;
                    field_36C = 1;
                    field_194 = 10;
                    break;
                }
            }
            else if ( field_36C == 1 )
            {
                if ( bul_parent )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->field_36C == 1 )
                        field_36C = 2;
                }
                sub_48C5F0(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_36E = 0;
                        field_190 = 0;
                    }
                }
            }
            else if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( process() )
            active = false;
        break;
    case 856:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 5 )
        {
            set_subseq(4);
            h_inerc = 0.0;
            v_inerc = 0.0;
            break;
        }
        if ( get_subseq() == 0 )
        {
            set_vec_speed(addition[0], addition[1]);
            addition[1] -= 1.0;
            if ( addition[1] <= 0.0 )
            {
                addition[1] = 0.0;
                dir = -dir;
                next_subseq();
                break;
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 1 && get_elaps_frames() >= 10 )
        {
            next_subseq();
            break;
        }
        if ( get_subseq() == 3 )
        {
            if ( get_elaps_frames() == 0 )
            {
                chrt->play_sfx( 29);
                float tmp[4];
                tmp[0] = (-8 * (int)addition[3] % 4) + 60.0;
                tmp[1] = 0.0;
                tmp[2] = 8.0;
                tmp[3] = addition[3];
                float yy = y + 5.0;
                float xx = (20 * dir) + x;
                addbullet(chrt, this, 856, xx, yy, dir, 1, tmp, 4);
            }
            if ( get_elaps_frames() >= 120 )
                next_subseq();
        }
        if ( get_subseq() == 5 )
        {
            if ( sub_5269B0() )
                break;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 6 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 7 && sub_526870(6) )
            break;
        if ( get_subseq() == 8 )
        {
            angZ += field_378;
            field_378 *= 0.9;
            if ( field_190 == 5
                    || bul_parent == NULL
                    || bul_parent->get_subseq() == 6
                    || bul_parent->get_subseq() == 5 )
            {
                active = false;
                break;
            }
            if ( bul_parent->get_subseq() == 4 )
            {
                set_frame( 2);
                break;
            }
            if ( get_frame() == 0 && get_elaps_frames() >= 10 )
            {
                scaleY += 0.15;
                if ( scaleY >= 2.0 )
                {
                    field_194 = 4;
                    scaleY = 2.0;
                    next_frame();
                }
            }
            if ( get_frame() == 1 )
            {
                scaleY = (get_elaps_frames() & 2) * 0.2 + 2.0;
                sub_48C5F0( 0);
                if ( field_190 )
                {
                    field_36C++;
                    if ( field_36C >= 7 )
                    {
                        field_36C = 0;
                        field_190 = 0;
                    }
                }
            }
            if ( get_frame() == 2 )
            {
                scaleY *= 0.8;
                if ( get_frame_time() >= 20 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( get_subseq() == 9 )
        {
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            if ( field_36C == 0 )
            {
                scaleY = scaleX = (get_elaps_frames() % 2) * 0.2 + 1.0;
                if ( bul_parent->get_frame() == 2 )
                    field_36C = 1;
            }
            if ( field_36C == 1 )
            {
                scaleY *= 0.9;
                if ( get_frame_time() >= 60 )
                {
                    active = false;
                    break;
                }
            }
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            order = -1;
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 857:
        if ( get_subseq() <= 1)
        {
            if ( chrt->health <= 0 )
            {
                set_subseq(5);
                break;
            }
            if ( get_subseq() == 0 )
            {
                addition[1] -= 2.0;
                if ( addition[1] < 0.0 )
                {
                    addition[1] = 0.0;
                    next_subseq();
                    break;
                }
            }
            if ( get_subseq() == 1 )
            {
                if ( get_elaps_frames() == 10 )
                {
                    chrt->play_sfx( 30);
                    field_378 = -atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);
                    field_378 = addition[3];
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 3.0;
                    float yy = y + 5.0;
                    float xx = (40 * dir) + x;
                    addbullet(chrt, this, 857, xx, yy, dir, 1, tmp ,3);
                    tmp[0] = field_378;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    addbullet(chrt, this, 857, xx, yy, dir, -1, tmp ,3);
                }
                if ( get_elaps_frames() == 20 )
                {
                    chrt->play_sfx( 30);
                    float tmp[3];
                    tmp[0] = field_378 - 90.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    float yy = y + 5.0;
                    float xx = (40 * dir) + x;
                    addbullet(chrt, this, 857, xx, yy, dir, -1, tmp ,3);
                }
                if ( get_elaps_frames() == 30 )
                {
                    chrt->play_sfx( 30);
                    float tmp[3];
                    tmp[0] = field_378 - 180.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    float yy = y + 5.0;
                    float xx = (40 * dir) + x;
                    addbullet(chrt, this, 857, xx, yy, dir, -1, tmp ,3);
                }
                if ( get_elaps_frames() == 40 )
                {
                    chrt->play_sfx( 30);
                    float tmp[3];
                    tmp[0] = field_378 - 270.0;
                    tmp[1] = 0.0;
                    tmp[2] = 2.0;
                    float yy = y + 5.0;
                    float xx = (40 * dir) + x;
                    addbullet(chrt, this, 857, xx, yy, dir, -1, tmp ,3);
                }
                if ( get_elaps_frames() > 300 )
                {
                    set_subseq(8);
                    field_378 = 0.0;
                    break;
                }
                field_37C += field_380;
                field_380 += 0.01;
                if (get_elaps_frames() >= 300 || field_36C >= 95 )
                {
                    set_subseq(8);
                    field_378 = 0.0;
                    break;
                }
            }
            set_vec_speed(addition[0], addition[1]);
            x += dir * h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            angZ = addition[0] + bul_parent->field_37C;
            if ( field_36C == 0)
            {
                x = (40 * dir) + bul_parent->x;
                y = bul_parent->y + 5.0;
                if ( bul_parent->get_subseq() != 1 )
                    field_36C = 2;
                if ( field_36C == 0 )
                {
                    scaleY += 0.05;
                    if ( scaleY >= 1.0 )
                    {
                        scaleY = 1.0;
                        field_194 = 1;
                        field_36C = 1;
                    }
                    if ( !bul_parent || bul_parent->get_subseq() != 1 )
                        field_36C = 2;
                }
            }
            if ( field_36C == 1 )
            {
                if ( field_190 == 6 )
                {
                    if ( bul_parent )
                        bul_parent->field_36C++;
                }
                sub_48C5F0( 0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 5 )
                    {
                        field_190 = 0;
                        field_194 = 1;
                        field_36E = 0;
                        if ( bul_parent )
                            bul_parent->field_36C += 5;
                    }
                }
                if ( !bul_parent || bul_parent->get_subseq() != 1 )
                    field_36C = 2;
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( c_A < 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
                c_B -= 8;
                c_G -= 8;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( field_36C == 0 )
            {
                scaleY = scaleX = (1.0 - field_378) * 0.75 + 0.25;
                field_378 *= 0.95;
                if ( field_378 <= 0.75 )
                {
                    if ( !field_190 )
                        field_194 = 1;
                    if ( field_190 == 6 )
                    {
                        if ( bul_parent )
                            bul_parent->field_36C++;
                    }
                    sub_48C5F0( 0);
                    sub_48C640( 0);
                    if ( field_190 )
                    {
                        field_36E++;
                        if ( field_36E >= 5 )
                        {
                            field_190 = 0;
                            field_194 = 1;
                            field_36E = 0;
                            if ( bul_parent )
                                bul_parent->field_36C += 5;
                        }
                    }
                }
                if ( get_elaps_frames() % 15 == 0 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 4.0;
                    addbullet(chrt, this, 857, x, y, dir, 1, tmp, 3);
                }
                if ( bul_parent )
                {
                    x = (40 * dir) + bul_parent->x;
                    y = bul_parent->y + 5.0;
                    scaleY = scaleX = (get_elaps_frames() % 2) * 0.1 + 1.0;
                    if (bul_parent->get_subseq() == 5 ||
                            bul_parent->get_subseq() == 6 ||
                            bul_parent->get_subseq() == 8)
                        field_36C = 1;
                }
                else
                    field_36C = 1;
            }
            if ( field_36C != 1 )
            {
                scaleY = scaleX *= 0.97;
                if ( c_A < 8 )
                {
                    active = false;
                    break;
                }
                c_A -= 8;
                c_B -= 8;
                c_G -= 8;
            }
        }
        if ( get_subseq() == 4 )
        {
            if ( !bul_parent )
            {
                active = false;
                break;
            }
            else
            {
                x = bul_parent->x;
                y = bul_parent->y;
                scaleY = scaleX += 0.2;
                if (c_A < 8)
                {
                    active = false;
                    break;
                }
                c_A -= 8;
            }
        }
        if ( get_subseq() == 5 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                break;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 6 )
        {
            if ( sub_5269B0() )
                break;
            x += h_inerc;
            y += v_inerc;
        }
        if ( get_subseq() == 7 )
        {
            if ( sub_526870(5) )
                break;
        }
        if ( get_subseq() == 8 )
        {
            if ( chrt->health <= 0 )
            {
                set_subseq(5);
                break;
            }
            if ( get_elaps_frames() >= 30 )
            {
                set_subseq(6);
                break;
            }
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
        {
            order = -1;
            if ( x - chrt->x > 0.0 )
                dir = -1;
            if ( x - chrt->x < 0.0 )
                dir = 1;
            field_378 = 0.0;
        }
        break;
    case 858:
        if ( get_subseq() != 15 && get_subseq() <= 19 )
            if ( chrt->get_seq() >= 50 && chrt->get_seq() <= 149 )
            {
                set_subseq(15);
                h_inerc = 0.0;
                v_inerc = 0.0;
                return;
            }
        if ( get_subseq() != 15 && get_subseq() != 16 && get_subseq() <= 19 )
            if ( chrt->get_seq() != 608 || chrt->get_subseq() > 1 )
            {
                set_subseq(15);
                h_inerc = -10.0;
                v_inerc = 12.0;
                shader_type = 1;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 37.0;
                addbullet( chrt, NULL, 858, x, y, dir, 1, tmp,3);
                chrt->play_sfx( 6);
                //shake_camera(8.0);
                return;
            }
        switch ( get_subseq() )
        {
        case 0:
        case 1:
            field_372 = 0;
            if ( chrt->dX(1) > 0 )
            {
                if ( dir == -1 )
                {
                    dir = 1;
                    h_inerc = -h_inerc;
                }
            }
            else if ( chrt->dX(1) < 0 )
            {
                if ( dir == 1 )
                {
                    dir = -1;
                    h_inerc = -h_inerc;
                }
            }
            if ( chrt->dX(dir) <= 0 )
            {
                h_inerc -= 2.0;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            else
            {
                h_inerc += 2.0;
                if ( h_inerc > 10.0 )
                    h_inerc = 10.0;
            }
            if ( chrt->dY() < 0 )
            {
                v_inerc += 2.0;
                if (v_inerc > 10.0)
                    v_inerc = 10.0;
            }
            if ( chrt->dY() > 0 )
            {
                v_inerc -= 2.0;
                if (v_inerc < -10.0)
                    v_inerc = -10.0;
            }
            if ( chrt->dY() == 0 )
            {
                if ( v_inerc <= 0.0 )
                {
                    v_inerc += 2.0;
                    if ( v_inerc > 0.0 )
                        v_inerc = 0.0;
                }
                else
                {
                    v_inerc -= 2.0;
                    if ( v_inerc < 0.0 )
                        v_inerc = 0.0;
                }
            }
            if ( get_subseq() == 0 )

                if ( h_inerc > 5.0 )
                    set_subseq(1);
            if ( get_subseq() == 1 )
                if ( h_inerc < 5.0 )
                    set_subseq(0);
            if ( chrt->keyDown(INP_A) > 0 && chrt->keyDown(INP_A) < 4 )
            {
                if ( chrt->dX(1) == 0 && chrt->dY() == 0 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    set_subseq(2);
                    return;
                }
                if ( chrt->dX(dir) > 0 )
                {
                    if ( chrt->dY() == 0 )
                    {
                        field_36C = 0;
                        field_194 = 1;
                        set_subseq(3);
                        return;
                    }
                    if ( chrt->dY() > 0 )
                    {
                        field_36C = 0;
                        field_194 = 1;
                        set_subseq(6);
                        return;
                    }
                }
                if ( chrt->dX(dir) == 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    set_subseq(6);
                    return;
                }
                if ( chrt->dX(dir) == 0 && chrt->dY() < 0 )
                {
                    field_36C = 0;
                    field_388 = 0.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) > 0 && chrt->dY() < 0 )
                {
                    field_36C = 0;
                    field_388 = 1.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() < 0 )
                {
                    dir = -dir;
                    field_36C = 0;
                    field_388 = 1.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
            }

            if ( chrt->keyDown(INP_B) > 0 &&chrt->keyDown(INP_B) < 4 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(11);
                return;
            }
            if ( chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(13);
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 2:
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
            {
                field_190 = 0;
                field_36E = 0;
                h_inerc = 30.0;
                v_inerc = 2.0;
            }
            h_inerc -= 3.0;
            if ( h_inerc <= 1.0 )
                h_inerc = 1.0;
            v_inerc -= 0.5;
            if ( v_inerc < 0.5 )
                v_inerc = 0.5;
            if ( get_frame() >= 2 )
            {
                if ( field_190 )
                    field_36E = 1;
                if ( (get_elaps_frames() % 2) == 0 )
                    if ( get_frame() >= 1 && get_frame() <= 7 )
                    {
                        field_380 = scene_rand_rng(90) - 45.0;

                        float tmp[3];
                        tmp[0] = field_380;
                        tmp[1] = 0.0;
                        tmp[2] = 21.0;

                        float yy = sin_deg(-field_380) * 100.0 + y;
                        float xx = cos_deg(-field_380) * 100.0 * dir + x;
                        addbullet(chrt, NULL, 858, xx, yy, dir, 1, tmp, 3);
                    }
            }
            if ( chrt->keyDown(INP_A) > 0 && chrt->keyDown(INP_A) < 4 && field_36E == 1 )
            {
                if ( chrt->dX(dir) > 0 && chrt->dY() == 0 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    set_subseq(3);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() == 0 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    dir = -dir;
                    set_subseq(3);
                    return;
                }
                if ( chrt->dX(dir) >= 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    set_subseq(6);
                    return;
                }

                if ( chrt->dX(dir) < 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    dir = -dir;
                    set_subseq(6);
                    return;
                }

                if ( chrt->dX(dir) == 0 && chrt->dY() < 0 )
                {
                    field_36C = 0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) > 0 && chrt->dY() < 0 )
                {
                    field_36C = 0;
                    field_388 = 0.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() < 0 )
                {
                    dir = -dir;
                    field_36C = 0;
                    field_388 = 0.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
            }
            if ( chrt->keyDown(INP_B) > 0 && chrt->keyDown(INP_B) < 4 && field_36E == 1 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(11);
                return;
            }
            if ( chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 && field_36E == 1 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(13);
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 3:
        case 4:
        case 5:
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                field_190 = 0;
            }
            if ( get_subseq() == 4 && get_elaps_frames() >= 16 )
            {
                next_subseq();
                return;
            }
            if (get_subseq() >= 4)
            {
                h_inerc -= 3.0;
                if ( h_inerc <= 0.5 )
                    h_inerc = 0.5;
            }
            if ( chrt->keyDown(INP_A) > 0 && chrt->keyDown(INP_A) < 4 && field_190 != 0 && field_372 <= 1 )
            {
                if ( chrt->dX(dir) > 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_372++;
                    field_194 = 1;
                    set_subseq(6);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_372++;
                    field_194 = 1;
                    dir = -dir;
                    set_subseq(6);
                    return;
                }
                if ( chrt->dX(dir) == 0 )
                {
                    if ( chrt->dY() > 0 )
                    {
                        field_36C = 0;
                        field_372++;
                        field_194 = 1;
                        set_subseq(6);
                        return;
                    }
                    if ( chrt->dY() < 0 )
                    {
                        field_36C = 0;
                        field_372++;
                        field_194 = 4;
                        h_inerc = 0.0;
                        v_inerc = 0.0;
                        set_subseq(9);
                    }
                }
                if ( chrt->dX(dir) > 0 && chrt->dY() < 0 )
                {
                    field_36C = 0;
                    field_372++;
                    field_388 = 1.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() < 0 )
                {
                    dir = -dir;
                    field_36C = 0;
                    field_372++;
                    field_388 = 1.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
            }
            if ( chrt->keyDown(INP_B) > 0 && chrt->keyDown(INP_B) < 4 && field_190 != 0 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(11);
                return;
            }

            if ( chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 && field_190 != 0)
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(13);
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 6:
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6 )
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                field_190 = 0;
            }
            angZ += 40.0;
            h_inerc -= 1.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            if ( v_inerc <= 0.0 )
            {
                v_inerc += 1.0;
                if ( v_inerc > 0.0 )
                    v_inerc = 0.0;
            }
            else
            {
                v_inerc -= 1.0;
                if ( v_inerc < 0.0 )
                    v_inerc = 0.0;
            }
            if ( get_elaps_frames() >= 9 )
            {
                angZ = 0.0;
                next_subseq();
                chrt->play_sfx( 7);

                float tmp[3];
                tmp[0] = 45.0;
                tmp[1] = 25.0;
                tmp[2] = 22.0;

                float yy = y - 105.0;
                float xx = 105 * dir + x;
                addbullet(chrt, this, 858, xx, yy, dir, 1, tmp, 3);

                addition[0] = 45.0;
                addition[1] = 35.0;
                field_194 = 1;
                field_190 = 0;
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 7:
            addition[1] -= 2.0;
            if ( addition[1] < -0.5 )
            {
                addition[1] = -0.5;
                field_194 = 0;
            }
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() >= 20 )
            {
                next_subseq();
                return;
            }
            if ( chrt->keyDown(INP_A) > 0 && chrt->keyDown(INP_A) < 4 && field_190 != 0 && field_372 <= 1 )
            {
                if ( chrt->dX(dir) > 0 && chrt->dY() == 0 )
                {
                    field_36C = 0;
                    field_372++;
                    field_194 = 1;
                    set_subseq(3);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() == 0 )
                {
                    field_36C = 0;
                    field_372++;
                    dir = -dir;
                    field_194 = 1;
                    set_subseq(3);
                    return;
                }
                if ( chrt->dX(dir) == 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_372++;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) > 0 && chrt->dY() > 0 )
                {
                    field_36C = 0;
                    field_372++;
                    field_388 = 1.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() > 0 )
                {
                    dir = -dir;
                    field_36C = 0;
                    field_372++;
                    field_388 = 1.0;
                    field_194 = 4;
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                    set_subseq(9);
                    return;
                }
            }

            if ( chrt->keyDown(INP_B) > 0 && chrt->keyDown(INP_B) < 4 && field_190 != 0 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(11);
                return;
            }
            if (  chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 && field_190 != 0 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(13);
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 8:
            addition[1] -= 5.0;
            if ( addition[1] < -0.5 )
            {
                addition[1] = -0.5;
                field_194 = 0;
            }
            set_vec_speed(addition[0], addition[1]);
            if ( get_elaps_frames() >= 30 )
            {
                set_subseq(0);
                return;
            }
            if ( chrt->keyDown(INP_B) > 0 && chrt->keyDown(INP_B) < 4 && field_190 != 0 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(11);
                return;
            }
            if ( chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 && field_190 != 0 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(13);
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 9:
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 9 )
            {
                field_36E = 0;
                h_inerc = 0.0;
                v_inerc = 0.0;
                field_190 = 0;
            }
            h_inerc -= 1.0;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            if ( v_inerc <= 0.0 )
            {
                v_inerc += 1.0;
                if ( v_inerc > 0.0 )
                    v_inerc = 0.0;
            }
            else
            {
                v_inerc -= 1.0;
                if ( v_inerc < 0.0 )
                    v_inerc = 0.0;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 10:
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 23.0;

                addbullet(chrt, this, 858, x, y, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() % 15 == 0 )
            {
                chrt->play_sfx( 4);
            }
            if ( field_190 )
            {
                field_36E = 1;
                field_36C++;
                if ( field_36C >= 4 )
                {
                    field_36C = 0;
                    field_190 = 0;
                }
            }
            if ( get_elaps_frames() >= 45 )
            {
                set_subseq(0);
                if ( x - chrt->x > 0.0 )
                    dir = 1;
                if ( x - chrt->x < 0.0 )
                    dir = -1;
                return;
            }
            v_inerc *= 0.95;
            h_inerc *= 0.95;

            if ( chrt->keyDown(INP_A) > 0 && chrt->keyDown(INP_A) < 4 && field_36E == 1 && field_372 <= 1 )
            {
                if ( chrt->dX(dir) > 0 && chrt->dY() == 0 )
                {
                    field_372++;
                    field_36C = 0;
                    field_194 = 1;
                    set_subseq(3);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() == 0 )
                {
                    field_372++;
                    field_36C = 0;
                    field_194 = 1;
                    dir = -dir;
                    set_subseq(3);
                    return;
                }
                if ( chrt->dX(dir) >= 0  && chrt->dY() > 0 )
                {
                    field_372++;
                    field_36C = 0;
                    field_194 = 1;
                    set_subseq(6);
                    return;
                }
                if ( chrt->dX(dir) < 0 && chrt->dY() < 0 )
                {
                    field_372++;
                    field_36C = 0;
                    field_194 = 1;
                    dir = -dir;
                    set_subseq(6);
                    return;
                }
            }

            if ( chrt->keyDown(INP_B) > 0 && chrt->keyDown(INP_B) < 4 && field_36E == 1 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(11);
                return;
            }
            if ( chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 && field_36E == 1 )
            {
                field_36C = 0;
                field_194 = 0;
                set_subseq(13);
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 11:
            field_36C = 0;

            if (chrt->dX(dir) == 0)
            {
                h_inerc = 0.0;
            }
            else if (chrt->dX(dir) < 0)
            {
                h_inerc -= 1.0;
                if (h_inerc < -4.0)
                    h_inerc = -4.0;
            }
            else if (chrt->dX(dir) > 0)
            {
                h_inerc += 1.0;
                if (h_inerc > 4.0)
                    h_inerc = 4.0;
            }

            if (chrt->dY() == 0)
            {
                v_inerc = 0.0;
            }
            else if (chrt->dY() < 0)
            {
                v_inerc += 1.0;
                if (v_inerc > 4.0)
                    v_inerc = 4.0;
            }
            else if (chrt->dY() > 0)
            {
                v_inerc -= 1.0;
                if (v_inerc < -4.0)
                    v_inerc = -4.0;
            }

            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 12:
            if ( (get_elaps_frames() % 2) == 0 )
            {
                if ( field_36C <= 9 )
                {
                    chrt->play_sfx( 0);
                    field_36C++;
                    float e_x = (enemy->x - x) * dir;
                    float e_y = enemy->y + 100.0 - y;
                    field_380 = -atan2_deg(e_y, e_x);
                    if ( field_380 < -30.0 )
                        field_380 = -30.0;
                    if ( field_380 > 30.0 )
                        field_380 = 30.0;

                    float tmp[4];
                    tmp[0] = scene_rand_rng(20) + field_380 - 10.0;
                    tmp[1] = 20.0;
                    tmp[2] = 26.0;
                    tmp[3] = 0.0;
                    float yy = y + 5.0;
                    float xx = (20 * dir) + x;

                    addbullet( chrt, NULL, 858, xx, yy, dir, 1, tmp, 4);

                    tmp[2] = 7.0;

                    addbullet( chrt, NULL, 800, xx, yy, dir, 1, tmp, 4);

                    chrt->play_sfx( 0);
                }
            }
            if ( get_elaps_frames() >= 18 )
            {
                if ( chrt->keyDown(INP_C) > 0 && chrt->keyDown(INP_C) < 4 )
                {
                    x += h_inerc * dir;
                    y += v_inerc;

                    if (y <= 0.0)
                        y = 0.0;
                    if (x > 1260.0)
                        x = 1260.0;
                    if (x < 20.0)
                        x = 20.0;
                    break;
                }
            }
            if ( get_elaps_frames() >= 40 )
            {
                set_subseq(0);
            }
            if (chrt->dX(dir) == 0)
            {
                h_inerc = 0.0;
            }
            else if (chrt->dX(dir) < 0)
            {
                h_inerc -= 1.0;
                if (h_inerc < -4.0)
                    h_inerc = -4.0;
            }
            else if (chrt->dX(dir) > 0)
            {
                h_inerc += 1.0;
                if (h_inerc > 4.0)
                    h_inerc = 4.0;
            }

            if (chrt->dY() == 0)
            {
                v_inerc = 0.0;
            }
            else if (chrt->dY() < 0)
            {
                v_inerc += 1.0;
                if (v_inerc > 4.0)
                    v_inerc = 4.0;
            }
            else if (chrt->dY() > 0)
            {
                v_inerc -= 1.0;
                if (v_inerc < -4.0)
                    v_inerc = -4.0;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 13:
            field_36C = 0;

            if (chrt->dX(dir) == 0)
            {
                h_inerc = 0.0;
            }
            else if (chrt->dX(dir) < 0)
            {
                h_inerc -= 1.0;
                if (h_inerc < -2.0)
                    h_inerc = -2.0;
            }
            else if (chrt->dX(dir) > 0)
            {
                h_inerc += 1.0;
                if (h_inerc > 2.0)
                    h_inerc = 2.0;
            }

            if (chrt->dY() == 0)
            {
                v_inerc = 0.0;
            }
            else if (chrt->dY() < 0)
            {
                v_inerc += 1.0;
                if (v_inerc > 2.0)
                    v_inerc = 2.0;
            }
            else if (chrt->dY() > 0)
            {
                v_inerc -= 1.0;
                if (v_inerc < -2.0)
                    v_inerc = -2.0;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 14:
            if (chrt->dX(dir) == 0)
            {
                h_inerc = 0.0;
            }
            else if (chrt->dX(dir) < 0)
            {
                h_inerc -= 1.0;
                if (h_inerc < -2.0)
                    h_inerc = -2.0;
            }
            else if (chrt->dX(dir) > 0)
            {
                h_inerc += 1.0;
                if (h_inerc > 2.0)
                    h_inerc = 2.0;
            }

            if (chrt->dY() == 0)
            {
                v_inerc = 0.0;
            }
            else if (chrt->dY() < 0)
            {
                v_inerc += 1.0;
                if (v_inerc > 2.0)
                    v_inerc = 2.0;
            }
            else if (chrt->dY() > 0)
            {
                v_inerc -= 1.0;
                if (v_inerc < -2.0)
                    v_inerc = -2.0;
            }

            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 14 )
            {
                chrt->play_sfx( 9);
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 33.0;

                float yy = y + 5.0;
                float xx = (20 * dir) + x;

                addbullet(chrt, this, 858, xx, yy, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() >= 75 )
            {
                set_subseq(0);
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 15:
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            angZ += 15.0;

            if ( c_A >= 20 )
                c_A -= 20;
            else
            {
                active = false;
                return;
            }
            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 16:
            if ( sub_5269B0() )
                return;
            x += h_inerc;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 20:
            if ( sub_526870(15) )
                return;
            break;
        case 21:
            scaleX += 0.01;
            scaleY *= 0.8;
            if ( scaleY <= 0.05 )
            {
                active = false;
                return;
            }
            set_vec_speed(addition[0], 15.0);

            x += h_inerc * dir;
            y += v_inerc;

            if (y <= 0.0)
                y = 0.0;
            if (x > 1260.0)
                x = 1260.0;
            if (x < 20.0)
                x = 20.0;
            break;
        case 22:
            if ( field_36C == 0)
            {
                if ( bul_parent)
                {
                    if (bul_parent->get_subseq() == 4 || bul_parent->get_subseq() == 7)
                    {
                        dir = bul_parent->dir;
                        x = bul_parent->x;
                        y = bul_parent->y;
                    }
                    else
                    {
                        field_36C = 1;
                    }
                }
                else
                {
                    field_36C = 1;
                }
            }
            else
            {
                scaleY *= 0.95;
                if ( c_A >= 20 )
                    c_A -= 20;
                else
                {
                    active = false;
                    return;
                }
            }
            break;
        case 23:
            angZ += 25.0;
            if ( !bul_parent )
            {
                active = false;
                return;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            if ( bul_parent->get_subseq() == 10 )
            {
                scaleX += 0.1;
                if ( scaleX > 3.0 )
                    scaleX = 2.5;
                scaleY = scaleX;
                if ( c_A > 225 )
                    c_A = 255;
                else
                    c_A += 30;
            }
            else
            {
                if ( c_A >= 20 )
                {
                    scaleX += 0.1;
                    c_A -= 20;
                    c_R -= 20;
                    c_G -= 20;
                }
                else
                {
                    active = false;
                    break;
                }
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 24:
            if ( !bul_parent )
            {
                active = false;
                return;
            }
            x = bul_parent->x;
            y = bul_parent->y;
            if (bul_parent->get_subseq() == 15 || bul_parent->get_subseq() == 16)
            {
                active = false;
                return;
            }
            break;
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            if ( get_frame() == 0 )
            {
                sub_48BF60(addition[3] + 4 * get_elaps_frames());
                if ( sub_48C6A0( 0, 0, 4) )
                {
                    active = false;
                    return;
                }
                if ( field_190 != 0 )
                {
                    if ( field_190 == 4 )
                        field_194 = 0;
                    next_frame();
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 7.0;
                    tmp[3] = get_elaps_frames() * 4.0 + addition[3];
                    addbullet(chrt, NULL, 800, x, y, dir, 1, tmp, 4);
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                set_vec_speed(addition[0], addition[1]);
                x += dir * h_inerc;
                y += v_inerc;
            }
            if ( get_frame() == 1 )
            {
                scaleY = scaleX *= 0.85;
                if ( c_A > 20 )
                    c_A -= 20;
                else
                {
                    active = false;
                    return;
                }
            }
            break;
        case 33:
            if ( bul_parent )
            {
                if ( field_36C == 0)
                {
                    if ( bul_parent->get_subseq() != 14 )
                        field_36C = 1;
                    if ( get_elaps_frames() < 45 )
                    {
                        x = (60 * dir) + bul_parent->x;
                        y = bul_parent->y + 5.0;
                        scaleY = scaleX = (get_elaps_frames() & 2) * 0.2 + 1.0;
                    }
                    else
                    {
                        field_36C = 1;
                    }
                    if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 )
                    {
                        active = false;
                        return;
                    }
                }
            }
            else
            {
                field_36C = 1;
            }
            if ( field_36C == 1)
            {
                scaleY = scaleX *= 0.85;
                if (scaleX < 0.02)
                {
                    active = false;
                    return;
                }
            }
            break;
        case 34:
            if ( bul_parent )
            {
                if ( field_36C <= 1 )
                {
                    if ( bul_parent->field_36C == 1 )
                        field_36C = 2;
                }
                if ( field_36C == 0)
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    scaleY += 0.1;
                    if ( scaleY > 0.75 )
                    {
                        scaleY = 0.75;
                        field_36C = 1;
                        field_194 = 10;
                        return;
                    }
                }
                if ( field_36C == 1 )
                {
                    x = bul_parent->x;
                    y = bul_parent->y;
                    if ( bul_parent->field_36C == 1 )
                        field_36C = 2;
                    sub_48C5F0( 0);
                    if ( field_190 )
                    {
                        field_36E++;
                        if ( field_36E >= 3 )
                        {
                            field_36E = 0;
                            field_190 = 0;
                        }
                    }
                }
            }
            else
            {
                field_36C = 2;
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if (scaleY <= 0.01)
                {
                    active = false;
                    return;
                }
            }
            break;
        case 35:
            scaleY = scaleX += 0.02;
            if ( get_elaps_frames() > 0 )
            {
                if ( c_B <= 20 )
                {
                    c_G -= 20;
                    c_B -= 20;
                }
                else
                {
                    if ( c_A > 20 )
                    {
                        c_G = 0;
                        c_B = 0;
                        c_A -= 20;
                    }
                    else
                    {
                        active = false;
                        return;
                    }
                }
            }
            break;
        case 36:
            scaleY = scaleX += 0.1;
            /*if ( get_elaps_frames() >= 0 ) */ //HACK for avoid warning
            {
                if ( c_B < 30 )
                {
                    c_G = 0;
                    c_B = 0;
                }
                else
                {
                    c_G -= 30;
                    c_B -= 30;
                }
                if ( c_A >= 25 )
                    c_A -= 25;
                else
                {
                    active = false;
                    return;
                }
            }
            break;
        case 37:
            sub_48C5F0( 0);
            scaleY = scaleX -= 0.01;
            if ( c_A > 10 )
            {
                c_A -= 10;
                c_G -= 10;
                c_B -= 10;
            }
            else
            {
                active = false;
                return;
            }
            break;
        default:
            break;
        }
        process();
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
        {
            if (get_subseq() == 3 || get_subseq() == 6 || get_subseq() == 9 ||
                    get_subseq() == 11 || get_subseq() == 13 || get_subseq() == 15)
            {
                set_subseq(0);
                return;
            }
            if ( get_subseq() == 4 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 22.0;

                float xx = (40 * dir) + x;

                addbullet(chrt, this, 858, xx, y, dir, 1, tmp, 3);
                field_194 = 1;
                field_190 = 0;
                chrt->play_sfx( 7);
                h_inerc = 40.0;
                v_inerc = 0.0;
            }
            if ( get_subseq() == 10 )
            {
                v_inerc = 15.0;
                h_inerc = field_388 * 15.0;
                field_36C = 0;
            }
        }
        if ( get_subseq() == 2 && get_frame_time() == 0)
        {
            if ( get_frame() >= 2 && get_frame() <= 6 )
            {
                scene_play_sfx(28);
                field_194 = 1;
                if ( field_190 )
                    field_36C = 1;
                field_190 = 0;
            }
            if ( get_frame() == 8 )
            {
                if ( field_36C > 0 )
                    field_190 = 1;
            }
        }
        break;

    case 859:
        switch ( get_subseq() )
        {
        case 1:
        case 2:
            if ( (chrt->get_seq() != 609 && chrt->get_seq() != 659) || chrt->get_subseq() != 1 )
            {
                set_subseq(3);
                return;
            }
            if ( get_subseq() == 2 )
            {
                sub_48C5F0(0);
                sub_48C640(0);
                if ( field_190 )
                {
                    field_36C++;
                    if ( field_36C > 4 )
                    {
                        field_36C = 0;
                        field_194 = 1;
                        field_190 = 0;
                    }
                }
                if ( get_elaps_frames() % 3 == 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(15) + 5.0;
                    tmp[2] = 6.0;
                    addbullet(chrt, NULL, 859, x, y, dir, -1, tmp, 3);
                }
            }
            break;
        case 3:
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;

            v_inerc -= 0.5;

            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;

            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            else
                c_A -= 10;
            break;
        case 4:
            sub_48C5F0(0);
            sub_48C640(0);
            if ( (chrt->get_seq() != 609 && chrt->get_seq() != 659) || chrt->get_subseq() != 1 )
            {
                active = false;
                return;
            }
            set_custom_box(0, 40, (scaleX * 256.0), -40, angZ, 0, 0);
            if ( sub_526870(6) )
                return;
            if ( field_190 )
            {
                field_36C++;
                if ( field_36C > 4 )
                {
                    field_36C = 0;
                    field_194 = 1;
                    field_190 = 0;
                }
            }
            break;
        case 5:
            if ( field_36C )
            {
                scaleY = scaleX *= 0.98;
                if ( c_A < 6 )
                {
                    active = false;
                    return;
                }
                else
                {
                    c_A -= 6;
                    c_B -= 6;
                    c_G -= 6;
                }
            }
            else if ( bul_parent && bul_parent->get_subseq() == 2 )
            {
                x = bul_parent->x;
                y = bul_parent->y;
            }
            else
            {
                field_36C = 1;
            }
            break;
        case 6:
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.99;
            if ( c_A < 6 )
            {
                active = false;
                return;
            }
            else
            {
                c_A -= 6;
                c_B -= 6;
                c_G -= 6;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        default:
            break;
        }
        if (process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;
            addbullet(chrt, this, 859, x, y, dir, -1, tmp, 3);
        }
        break;

    case 860:
        if ( chrt->get_seq() > 49 && chrt->get_seq() < 150 && get_subseq() <= 1 )
            set_subseq(3);
        if ( get_subseq() == 0)
        {
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() >= 1 && get_subseq() <= 2 )
        {
            h_inerc -= 2.0;
            if ( h_inerc < -0.5 )
                h_inerc = -0.5;
            if ( h_inerc <= 0.0 && get_subseq() == 1 )
            {
                field_194 = 0;
                set_subseq( 2);
            }
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 2 )
        {
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            else
                c_A -= 10;
        }
        if ( get_subseq() == 3 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;

            v_inerc -= 0.5;

            x += h_inerc;
            y += v_inerc;

            angZ += 15.0;

            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            else
                c_A -= 20;
        }
        if ( get_subseq() == 4 )
        {
            scaleX += 0.05;
            scaleY *= 0.8;
            if ( scaleY <= 0.01 )
            {
                active = false;
                return;
            }
            h_inerc = 10.0;
            x += dir * 10.0;
        }
        if ( get_subseq() == 5 )
        {
            scaleY = scaleX += 0.05;
            if ( c_A < 30 )
            {
                active = false;
                return;
            }
            else
                c_A -= 30;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = 25.0;
            chrt->play_sfx(12);

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            float xx = (130 * dir) + x;
            float yy = y + 4.0;

            addbullet(chrt, NULL, 860, xx, yy, dir, order, tmp, 3);
        }
        break;
    case 861:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( getlvl_height() >= v_inerc + y )
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                next_subseq();
                y = getlvl_height();
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            if ( health < 0 )
            {
                set_subseq(6);
                h_inerc = 0.0;
                v_inerc = 7.5;
                return;
            }
            h_inerc = 2.0;
            v_inerc = 0.0;
            if ( getlvl_height() < y )
            {
                set_subseq( 0);
                return;
            }
            if ( (SQR(x - enemy->x) <= 2500.0 && SQR(y - enemy->y) <= 10000.0) ||
                    y < getlvl_height() ||
                    health < 0 )
            {
                //shake_camera(10.0);
                shader_type = 1;
                set_subseq( 6);
                has_shadow = 0;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 6);
                y = getlvl_height();
                v_inerc = 12.0;
                h_inerc = -10.0;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;

        case 2:
            sub_48C5F0( 0);
            scaleY = scaleX -= 0.01;
            if ( c_A > 10 )
            {
                c_A -= 10;
                c_G -= 10;
                c_B -= 10;
            }
            else
            {
                active = false;
                return;
            }
            break;
        case 3:
            scaleY = scaleX += 0.02;
            if ( get_elaps_frames() > 0 )
            {
                if ( c_B <= 20 )
                {
                    c_G -= 20;
                    c_B -= 20;
                }
                else
                {
                    if ( c_A <= 20 )
                    {
                        active = false;
                        return;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 20;
                }
            }
            break;
        case 4:
            scaleY = scaleX += 0.1;
            /* if ( get_elaps_frames() >= 0 ) */ //HACK Avoid warning
            {
                if ( c_B < 30 )
                {
                    c_G = 0;
                    c_B = 0;
                }
                else
                {
                    c_G -= 30;
                    c_B -= 30;
                }
                if ( c_A < 25 )
                {
                    active = false;
                    return;
                }
                else
                    c_A -= 25;
            }
            break;
        case 5:
            if ( get_elaps_frames() % 2 == 0 )
            {
                float yy = (50 * get_elaps_frames()) + y;

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;

                addbullet(chrt, NULL, 861, x, yy, dir, 1, tmp, 3);
            }
            if ( get_elaps_frames() == 4 )
            {
                active = false;
                return;
            }
            break;
        case 6:
            angZ += 15.0;
            if ( c_A <= 5 )
            {
                active = false;
                return;
            }
            else
                c_A -= 5;

            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 7:
            v_inerc -= 0.5;
            if ( getlvl_height() + field_380 >= v_inerc + y && v_inerc < 0.0 )
            {
                set_subseq( 10);
                y = getlvl_height() + field_380;
                v_inerc = 0.0;
                return;
            }
            if ( (SQR(x - enemy->x) <= 10000.0 && SQR(y - enemy->y) <= 10000.0) || health < 0 )
            {
                //shake_camera(10.0);
                shader_type = 1;
                set_subseq( 6);
                has_shadow = 0;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 6);
                v_inerc = 12.0;
                h_inerc = -10.0;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 8:
            v_inerc -= 0.5;
            if ( getlvl_height() + field_380 >= v_inerc + y ||
                    (SQR(x - enemy->x) <= 2500.0 && SQR(y - enemy->y) <= 10000.0) ||
                    getlvl_height() + field_380 > y ||
                    health < 0 )
            {
                //shake_camera(10.0);
                shader_type = 1;
                set_subseq( 6);
                has_shadow = 0;
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 6);
                v_inerc = 12.0;
                h_inerc = -10.0;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 9:
            if ( health < 0 )
            {
                set_subseq(6);
                h_inerc = 0.0;
                v_inerc = 7.5;
                return;
            }
            if ( getlvl_height() + field_380 >= v_inerc + y )
            {
                h_inerc = 0.0;
                v_inerc = 0.0;
                next_subseq();
                y = getlvl_height() + field_380;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 10:
            if ( health < 0 )
            {
                set_subseq(6);
                h_inerc = 0.0;
                v_inerc = 7.5;
                return;
            }
            h_inerc = field_378;
            v_inerc = 0.0;

            if ( getlvl_height() + field_380 < y )
            {
                set_subseq(9);
                return;
            }
            if ( field_36E == 1 )
            {
                float e_x = (enemy->x - x) * dir;
                if ( e_x <= 200.0 && e_x >= 0.0 && y >= enemy->y )
                {
                    set_subseq( 8);
                    scene_add_effect(this,  1, x, y, dir,  1);
                    scene_play_sfx(1);
                    h_inerc += 3.0;
                    v_inerc = 8.0;
                    return;
                }
            }
            if ( field_36E == 2 )
            {
                float e_x = (enemy->x - x) * dir;
                if ( e_x <= 200.0 && e_x >= 0.0 && y < enemy->y )
                {
                    field_36C = 1;
                    set_subseq( 7);
                    h_inerc = 4.0;
                    v_inerc = 15.0;
                    return;
                }
            }
            if ( (SQR(x - enemy->x) <= 2500.0 && SQR(y - enemy->y) <= 10000.0) ||
                    getlvl_height() + field_380 > y ||
                    health < 0 )
            {
                //shake_camera(10.0);
                set_subseq( 6);
                shader_type = 1;
                has_shadow = 0;

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 6);
                y = getlvl_height() + field_380;
                v_inerc = 12.0;
                h_inerc = -10.0;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        default:
            break;
        }
        if (process())
            active = false;
        break;
    case 900:
        if ( get_subseq() <= 4 && (chrt->char_is_shock() || health < 0) )
        {
            set_subseq(5);
            h_inerc *= 0.25;
            v_inerc *= 0.25;
            return;
        }
        if ( get_subseq() == 0 )
        {
            angZ += 20.0;
            addition[1] *= 0.97;
            set_vec_speed(addition[0], addition[1]);
            if ( addition[1] <= 1.0 )
            {
                v_inerc = 0.0;
                h_inerc = 0.0;
                angZ = 0.0;
                next_subseq();
                order = 1;
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
        }
        if (get_subseq() == 1 /*&& get_elaps_frames() >= 0*/) //HACK SILENCE WARNING
        {
            next_subseq();
            if ( x >= enemy->x )
                dir = -1;
            else
                dir = 1;
            return;
        }
        if ( get_subseq() == 3 )
        {
            int32_t v1060, v1061, v1063;
            uint32_t v1062;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                v1060 = 6;
                v1061 = 2;
                v1062 = 80;
                v1063 = 1;
                break;
            case GAME_DIFF_HARD:
                v1060 = 5;
                v1061 = 2;
                v1062 = 100;
                v1063 = 1;
                break;
            case GAME_DIFF_NORMAL:
                v1060 = 4;
                v1061 = 1;
                v1062 = 120;
                v1063 = 0;
                break;
            case GAME_DIFF_EASY:
                v1061 = 0;
                v1060 = 4;
                v1062 = 150;
                v1063 = 0;
                break;
            default:
                v1060 = 0;
                v1061 = 0;
                v1062 = 0;
                v1063 = 0;
                break;
            }
            if ( get_elaps_frames() % 4 == 0 && v1060 > field_372 )
            {
                field_380 = -atan2_deg(enemy->y + 100.0 - y,  (enemy->x - x) * dir);
                if ( field_380 > 90.0 )
                    field_380 = 90.0;
                if ( field_380 < -90.0 )
                    field_380 = -90.0;
                float tmp[3];
                tmp[0] = scene_rand_rng(20) + field_380 - 10.0;
                tmp[1] = 15.0;
                tmp[2] = field_37C;
                float yy = y + 5.0;
                float xx = (20 * dir) + x;
                addbullet(chrt, NULL, 901, xx, yy, dir, 1, tmp, 3);

                tmp[2] = (field_36C % 7) + 7.0;
                addbullet(chrt, NULL, 901, xx, yy, dir, 1, tmp, 3);
                chrt->play_sfx( 0);
                field_372++;
            }
            if ( get_elaps_frames() >= v1062 )
            {
                if ( field_374 >= v1061 )
                {
                    if ( v1063 == 0 )
                    {
                        set_subseq(5);
                        return;
                    }
                    if ( x >= enemy->x )
                        dir = -1;
                    else
                        dir = 1;
                    set_subseq( 4);
                    sub_48C4B0(0.0, 180.0, 100.0);
                    angZ = addition[0];
                    return;
                }
                else
                {
                    set_subseq(2);
                    field_372 = 0;
                    field_374++;
                    if ( x >= enemy->x )
                        dir = -1;
                    else
                        dir = 1;
                    return;
                }
            }
        }

        if ( get_subseq() == 4 )
        {
            sub_48C4B0(0.0, 2.0, 100.0);
            addition[1] += 0.75;
            set_vec_speed(addition[0], addition[1]);
            angZ = addition[0];
            if ( x > 1480.0 || x < -100.0 || y > 1000.0 )
            {
                active = false;
                return;
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 6.0;
                addbullet(chrt, NULL, 902, x, y, dir, -1, tmp ,3);
            }
            if ( getlvl_height() >= y || (SQR(enemy->x - x) + SQR(enemy->y + 100.0 - y) <= 5625.0) )
            {
                //shake_camera(5.0); //HACK NOT IMPLEMENTED YET
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 902, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 6);
                return;
            }

            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 5 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 6 && sub_526870(5) )
            return;
        if ( get_subseq() == 7 )
        {
            addition[1] -= 5.0;
            if ( addition[1] < -0.5 )
            {
                addition[1] = -0.5;
                field_194 = 0;
            }
            set_vec_speed(addition[0], addition[1]);
            sub_48C5F0(0);
            if ( field_190 )
            {
                field_36E++;
                if ( field_36E >= 5 )
                {
                    field_36E = 0;
                    field_190 = 0;
                }
            }
            if ( field_188 > 0 )
            {
                set_subseq( 4);
                return;
            }
            if ( field_36C >= 90 )
            {
                set_subseq( 4);

                order = -1;

                if ( x - chrt->x > 0.0 )
                    dir = -1;
                else if ( x - chrt->x < 0.0 )
                    dir = 1;
                return;
            }
            field_36C += 1;
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
        {
            field_37C = scene_rand_rngf(7);
        }
        break;

    case 901:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        if ( get_subseq() > 6 )
        {
            scaleY = scaleX *= 0.9;

            if ( c_A <= 10 )
            {
                active = false;
                return;
            }
            else
                c_A -= 10;
        }
        else
        {
            if ( get_frame() == 0 )
            {
                if ( field_190 || get_elaps_frames() >= 20 || chrt->char_is_shock() )
                {
                    next_frame();
                    return;
                }
                if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
                {
                    active = false;
                    return;
                }
                set_vec_speed(addition[0], addition[1]);

                x += dir * h_inerc;
                y += v_inerc;
            }
            if ( get_frame() == 1 )
            {

            }
            scaleY = scaleX *= 0.85;
            if ( c_A <= 20 )
            {
                active = false;
                return;
            }
            else
                c_A -= 20;
        }
        if ( process() )
            active = false;
        break;

    case 902:
        if ( field_190 == 5 )
        {
            active = false;
            return;
        }
        switch ( get_subseq() )
        {
        case 0:
            if ( sub_48C6A0( 0, 1, 4) )
            {
                active = false;
                return;
            }
            if ( getlvl_height() >= v_inerc + y || health < 0 )
            {
                // shake_camera(5.0); HACK
                next_subseq();
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 815, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 6);
                y = getlvl_height();
                v_inerc = -v_inerc;
                h_inerc *= 0.2;
                return;
            }
            if ( field_190 == 1 || field_190 == 7 )
            {
                field_378 = enemy->x - x;
                field_37C = enemy->y - y;
                set_subseq(6);
                h_inerc = 0.0;
                v_inerc = 0.0;
                return;
            }
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -160.0 )
            {
                active = false;
                return;
            }
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            shader_type = 1;
            angZ += 15.0;
            if ( c_A <= 5 )
            {
                active = false;
                return;
            }
            c_A -= 5;
            v_inerc -= 0.5;
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 2:
            sub_48C5F0( 0);
            scaleY = scaleX -= 0.01;
            if ( c_A <= 10 )
            {
                active = false;
                return;
            }

            c_A -= 10;
            c_G -= 10;
            c_B -= 10;
            break;
        case 3:
            scaleY = scaleX += 0.02;

            if ( get_elaps_frames() > 0 )
            {
                if ( c_B <= 20 ) //Looks like bug
                {
                    c_G -= 20;
                    c_B -= 20;
                }
                else
                {
                    if ( c_A <= 20 )
                    {
                        active = false;
                        return;
                    }
                    c_G = 0;
                    c_B = 0;
                    c_A -= 20;
                }
            }
            break;
        case 4:
            scaleY = scaleX += 0.1;
            /*if ( get_elaps_frames() >= 0 )*/ //HACK SILENCE WARNING
            {
                if ( c_B < 30 )
                {
                    c_G = 0;
                    c_B = 0;
                }
                else
                {
                    c_G -= 30;
                    c_B -= 30;
                }
                if ( c_A < 25 )
                {
                    active = false;
                    return;
                }
                c_A -= 25;
            }
            break;
        case 6:
            scaleY = scaleX *= 0.98;
            if ( c_A < 8 )
            {
                active = false;
                return;
            }
            c_A -= 8;
            c_B -= 8;
            c_G -= 8;
            break;
        default:
            break;
        }
        if (process())
            active = false;
        break;

    case 910:
    {
        char_alice *alice = (char_alice *)chrt;
        if ( get_subseq() <= 4 && (chrt->char_is_shock() || health < 0) )
        {
            alice->field_89A--;
            set_subseq( 5);
            return;
        }
        if ( get_subseq() == 0 )
        {
            if ( !bul_parent )
            {
                set_subseq( 5);
                alice->field_89A--;
                return;
            }
            dir = bul_parent->dir;
            x = cos_deg(-addition[0]) * addition[1] + bul_parent->x;
            y = sin_deg(-addition[0]) * addition[1] + bul_parent->y;
            angZ += 20.0;
            addition[0] += field_37C;
            field_37C -= 0.5;
            if ( field_37C <= 1.0 )
                field_37C = 1.0;
            addition[1] += field_378;
            field_378 -= 1.0;
            if ( field_378 < 0.0 )
                field_378 = 0.0;
            if ( get_elaps_frames() == 60 )
            {
                angZ = 0.0;
                set_subseq( 4);
                order = 1;
                return;
            }
        }
        if ( get_subseq() == 1 )
        {
            if ( !bul_parent )
            {
                set_subseq( 5);
                alice->field_89A--;
                return;
            }
            dir = bul_parent->dir;
            x = cos_deg(-addition[0]) * addition[1] + bul_parent->x;
            y = sin_deg(-addition[0]) * addition[1] + bul_parent->y;
            if ( bul_parent->field_36C == 2 )
            {
                next_subseq();
                return;
            }
            addition[0] += 1.0;
        }
        if ( get_subseq() == 2 )
        {
            if ( !bul_parent )
            {
                set_subseq( 5);
                alice->field_89A--;
                return;
            }
            dir = bul_parent->dir;
            x = cos_deg(-addition[0]) * addition[1] + bul_parent->x;
            y = sin_deg(-addition[0]) * addition[1] + bul_parent->y;
            if ( bul_parent->field_36E == 2 )
            {
                next_subseq();
                angZ = addition[0];
                field_194 = 1;
                field_190 = 0;
                float tmp[3];
                tmp[0] = angZ;
                tmp[1] = 0.0;
                tmp[2] = 7.0;
                addbullet(chrt, this, 910, x, y, dir, 1, tmp, 3);
                return;
            }
            addition[0] += 1.0;
            angZ += 40.0;
        }
        if ( get_subseq() == 3 )
        {
            sub_48C5F0(0);
            if ( !bul_parent )
            {
                set_subseq( 5);
                alice->field_89A--;
                return;
            }
            dir = bul_parent->dir;
            x = cos_deg(-addition[0]) * addition[1] + bul_parent->x;
            y = sin_deg(-addition[0]) * addition[1] + bul_parent->y;
            if ( bul_parent->field_36C == 3 )
            {
                next_subseq();
                return;
            }
        }
        if ( get_subseq() == 4 )
        {
            angZ += 20.0;
            if ( angZ > 360.0 )
                angZ = 360.0;
            if ( !bul_parent )
            {
                set_subseq( 5);
                alice->field_89A--;
                return;
            }
            dir = bul_parent->dir;
            x = cos_deg(-addition[0]) * addition[1] + bul_parent->x;
            y = sin_deg(-addition[0]) * addition[1] + bul_parent->y;
            if ( bul_parent->field_36C == 1 )
            {
                set_subseq( 2);
                return;
            }
            addition[0] += 1.0;
        }
        if ( get_subseq() == 5 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 6 && sub_526870(5) )
            return;
        if ( get_subseq() == 7 )
        {
            if ( !bul_parent || bul_parent->get_subseq() != 3 )
            {
                next_subseq();
                return;
            }
            dir = bul_parent->dir;
            angZ = bul_parent->angZ;
            x = bul_parent->x;
            y = bul_parent->y;
        }
        if ( get_subseq() != 9 )
        {
            if ( chrt->char_is_shock() )
            {
                active = false;
                return;
            }
            if ( field_36C == 0)
            {
                field_36E++;
                if ( field_36E >= 90 )
                {
                    field_36C = 1;
                    field_36E = 30;
                }
            }
            if ( field_36C == 1 )
            {
                field_36E--;
                if ( field_36E <= 0 )
                {
                    field_36C = 2;
                    if ( x >= enemy->x )
                        dir = -1;
                    else
                        dir = 1;
                    sub_48C4B0(0.0, 180.0, 100.0);
                    chrt->play_sfx( 7);
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        addition[1] = 40.0;
                        field_36E = 30;
                        break;
                    case GAME_DIFF_HARD:
                        addition[1] = 30.0;
                        field_36E = 30;
                        break;
                    case GAME_DIFF_NORMAL:
                        addition[1] = 20.0;
                        field_36E = 30;
                        break;
                    case GAME_DIFF_EASY:
                        addition[1] = 20.0;
                        field_36E = 30;
                        break;
                    default:
                        break;
                    }
                }
            }
            if ( field_36C == 2 )
            {
                field_36E--;
                if ( field_36E <= 0 )
                {
                    field_36C = 3;
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        field_36E = 120;
                        break;
                    case GAME_DIFF_HARD:
                        field_36E = 150;
                        break;
                    case GAME_DIFF_NORMAL:
                        field_36E = 180;
                        break;
                    case GAME_DIFF_EASY:
                        field_36E = 210;
                        break;
                    default:
                        break;
                    }
                }
                h_inerc = 0.0;
                v_inerc = 0.0;
                if ( addition[1] < 10.0 )
                {
                    addition[1] -= 0.5;
                    if ( addition[1] < 0.0 )
                        addition[1] = 0.0;
                }
                else
                {
                    addition[1] -= 1.5;
                }
                set_vec_speed(addition[0], addition[1]);
            }
            if ( field_36C == 3 )
            {
                field_36E--;
                if ( field_36E <= 0 )
                {
                    field_36C = 1;
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        field_36E = 30;
                        break;
                    case GAME_DIFF_HARD:
                        field_36E = 45;
                        break;
                    case GAME_DIFF_NORMAL:
                    case GAME_DIFF_EASY:
                        field_36E = 60;
                        break;
                    default:
                        break;
                    }
                    h_inerc = 0.0;
                    v_inerc = 0.0;
                }
            }
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 9 )
            active = false;
    }
    break;

    case 920:
    {
        char_alice *alice = (char_alice *)chrt;
        if ( get_subseq() <= 1 && (chrt->char_is_shock() || health < 0) )
        {
            alice->field_898--;
            set_subseq( 2);
            return;
        }
        if ( get_subseq() == 0)
        {
            if ( get_elaps_frames() >= 120 )
            {
                angZ = 0.0;
                next_subseq();
                return;
            }
            angZ += 20.0;
            addition[0] += 0.25;
            addition[1] += addition[3];
            addition[3] *= 0.97;
            x = cos_deg(-addition[0]) * addition[1] * dir + field_37C;
            y = sin_deg(-addition[0]) * addition[1] + field_380;
        }
        if ( get_subseq() == 1 )
        {
            int32_t frames = 0;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
            case GAME_DIFF_HARD:
                frames = 180;
                break;
            case GAME_DIFF_NORMAL:
                frames = 240;
                break;
            case GAME_DIFF_EASY:
                frames = 300;
                break;
            default:
                break;
            }
            if ( (int32_t)get_elaps_frames() >= frames - 127 )
            {
                shader_cR = 2 * (get_elaps_frames() - frames) - 2;
                shader_cB = shader_cR;
                shader_cG = shader_cR;
            }
            if ( (int32_t)get_elaps_frames() >= frames )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.1;
                tmp[2] = 4.0;
                addbullet(chrt, NULL, 920, x, y, dir, 1, tmp, 3);
                chrt->play_sfx( 21);
                //shake_camera(6.0); //HACK NOT IMPLEMENTED
                h_inerc = scene_rand_rng(10) - 5.0;
                v_inerc = scene_rand_rng(50) * 0.1 + 12.5;
                shader_type = 1;
                set_subseq(3);
                return;
            }
            angZ = 0.0;
            addition[0] += 0.25;
            addition[1] += addition[3];
            addition[3] *= 0.97;
            x = cos_deg(-addition[0]) * addition[1] * dir + field_37C;
            y = sin_deg(-addition[0]) * addition[1] + field_380;
        }
        if ( get_subseq() == 2 )
        {
            if ( h_inerc > 5.0 )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( v_inerc > 5.0 )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 3 )
        {
            v_inerc -= 0.5;
            angZ += 30.0;
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            c_A -= 20;
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 4 )
        {
            if ( field_36C )
            {
                field_194 = 0;
                scaleY = scaleX *= 0.98;
                if ( c_A < 7 )
                {
                    active = false;
                    return;
                }
                c_A -= 7;
                c_G -= 7;
                c_B -= 7;
            }
            else
            {
                sub_48C5F0(0);
                sub_48C640(3);
                scaleY = scaleX += addition[1];
                addition[1] *= 0.92;
                if ( !field_194 || chrt->char_is_shock() || (int32_t)get_elaps_frames() > field_36E )
                {
                    field_194 = 0;
                    field_36C = 1;
                }
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleY = scaleX += addition[1];
            addition[1] *= 0.92;
            if ( addition[1] < 0.05 )
                addition[1] = 0.05;
            if ( c_A < 7 )
            {
                active = false;
                return;
            }
            c_A -= 7;
            c_G -= 7;
            c_B -= 7;
        }
        if ( get_subseq() == 6 )
        {
            scaleY = scaleX += 0.01;
            addition[1] *= 0.92;
            if ( addition[1] < 0.05 )
                addition[1] = 0.05;
            set_vec_speed(addition[0], addition[1]);
            angZ += field_378;

            if ( c_A < 7 )
            {
                active = false;
                return;
            }
            c_A -= 7;
            c_G -= 7;
            c_B -= 7;
            x += dir * h_inerc;
            y += v_inerc;
        }
        if(process())
            active = false;
    }
    break;

    case 930:
        switch ( get_subseq() )
        {
        case 0:
            angZ += 20.0;
            if ( angZ > 360.0 )
                angZ -= 360.0;
            h_inerc -= 0.4;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            if ( get_elaps_frames() >= 30 )
            {
                next_subseq();
                return;
            }
            x += dir * h_inerc;
            y += v_inerc;
            break;
        case 1:
            angZ += 20.0;
            if ( angZ > 360.0 )
                angZ = 360.0;
            if ( get_elaps_frames() >= 20 )
            {
                next_subseq();
                return;
            }
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            break;
        case 2:
            if ( get_elaps_frames() >= 30 )
            {
                next_subseq();
                chrt->play_sfx( 36);
                //shake_camera(10.0);
                return;
            }
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
            break;
        case 3:
            scaleX += 0.5;
            if ( scaleX > 4.0 )
            {
                scaleX = 1.0;
                scaleY = 1.0;
                next_subseq();
                return;
            }
            scaleY = scaleX;
            break;
        case 4:
            if ( get_elaps_frames() >= 90 )
            {
                field_378 = x;
                field_37C = y;
                next_subseq();
                return;
            }
            break;
        case 5:
        {
            if ( chrt->char_is_shock() )
            {
                for (int i = 0; i < 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0;
                    tmp[1] = 8.0;
                    tmp[2] = 16.0;

                    float xx = cos_deg(-tmp[0]) * 100.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 100.0 + y;

                    addbullet(chrt, NULL, 930, xx, yy, dir, 1, tmp, 3);
                }
                for (int i = 0; i < 4; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 90.0;
                    tmp[1] = 4.0;
                    tmp[2] = 16.0;

                    addbullet(chrt, NULL, 930, x, y, dir, 1, tmp, 3);
                }
                active = false;
                return;
            }
            field_378 = (640.0 - field_378) * 0.02 + field_378;
            field_37C = 0.02 * (300.0 - field_37C) + field_37C;
            addition[0] += 1.0;
            if ( addition[0] > 360.0 )
                addition[0] -= 360.0;

            float tx = cos_deg(-addition[0]) * addition[1] + field_378;
            float ty = sin_deg(-addition[0]) * (addition[1] * 0.3) + field_37C;

            if ( sin_deg(-addition[0]) <= 0.0 )
                dir = -1;
            else
                dir = 1;

            h_inerc = (tx - x) * 0.01;
            v_inerc = (ty - y) * 0.01;

            if ( sin_deg(-addition[0]) <= 0.0 )
                order = 1;
            else
                order = -1;

            if ( chrt->field_7D0 == 1 )
            {
                if ( enemy->x >= x )
                {
                    dir = 1;
                    set_subseq( 6);
                }
                else
                {
                    dir = -1;
                    set_subseq( 6);
                }
                return;
            }
            if ( chrt->field_7D0 == 2 )
            {
                set_subseq(9);
                return;
            }
            x += h_inerc;
            y += v_inerc;
        }
        break;
        case 6:
        case 7:
        case 8:
        {
            if ( chrt->char_is_shock() )
            {
                for (int i = 0; i < 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0;
                    tmp[1] = 8.0;
                    tmp[2] = 16.0;

                    float xx = cos_deg(-tmp[0]) * 100.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 100.0 + y;

                    addbullet(chrt, NULL, 930, xx, yy, dir, 1, tmp, 3);
                }
                for (int i = 0; i < 4; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 90.0;
                    tmp[1] = 4.0;
                    tmp[2] = 16.0;

                    addbullet(chrt, NULL, 930, x, y, dir, 1, tmp, 3);
                }
                active = false;
                return;
            }
            field_378 = (640.0 - field_378) * 0.02 + field_378;
            field_37C = 0.02 * (640.0 - field_37C) + field_37C;
            addition[0] += 0.5;
            if ( addition[0] > 360.0 )
                addition[0] -= 360.0;

            float tx = cos_deg(-addition[0]) * addition[1] + field_378;
            float ty = sin_deg(-addition[0]) * (addition[1] * 0.3) + field_37C;

            if ( sin_deg(-addition[0]) <= 0.0 )
                dir = -1;
            else
                dir = 1;

            h_inerc = (tx - x) * 0.01;
            v_inerc = (ty - y) * 0.01;

            if ( sin_deg(-addition[0]) <= 0.0 )
                order = 1;
            else
                order = -1;

            if ( get_subseq() == 6 )
            {
                if ( get_elaps_frames() % 2 == 0 && get_elaps_frames() <= 45 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(400) + 200.0;
                    tmp[2] = scene_rand_rngf(7);
                    addbullet(chrt, this, 933, x, y, dir, 1, tmp, 3);
                }
                if ( get_elaps_frames() >= 60 )
                {
                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 1;

                    if ( settings_get()->get_difficulty() == GAME_DIFF_HARD )
                        tmp[2] = 2.0;
                    else if ( settings_get()->get_difficulty() == GAME_DIFF_LUNA )
                        tmp[2] = 3.0;

                    CharFrameData *frm = get_pframe();

                    float yy = y - frm->extra1[5];
                    float xx = (frm->extra1[4] * dir) + x;

                    addbullet(chrt, this, 931, xx, yy, dir, 1, tmp, 3);
                    next_subseq();

                    field_36C = 0;
                    return;
                }
            }
            if ( get_subseq() == 7 )
            {
                uint32_t frames = 0;
                switch ( settings_get()->get_difficulty() )
                {
                case GAME_DIFF_LUNA:
                    frames = 180;
                    break;
                case GAME_DIFF_HARD:
                    frames = 120;
                    break;
                case GAME_DIFF_NORMAL:
                    frames = 80;
                    break;
                case GAME_DIFF_EASY:
                    frames = 40;
                    break;
                default:
                    frames = 0;
                    break;
                }
                if ( get_elaps_frames() >= frames )
                    field_36C = 1;
                if ( get_elaps_frames() >= 180 )
                {
                    next_subseq();
                    return;
                }
            }
            x += h_inerc;
            y += v_inerc;
        }
        break;
        case 9:
        case 10:
        case 11:
        {
            if ( chrt->char_is_shock() )
            {
                for (int i = 0; i < 8; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 45.0;
                    tmp[1] = 8.0;
                    tmp[2] = 16.0;

                    float xx = cos_deg(-tmp[0]) * 100.0 * dir + x;
                    float yy = sin_deg(-tmp[0]) * 100.0 + y;

                    addbullet(chrt, NULL, 930, xx, yy, dir, 1, tmp, 3);
                }
                for (int i = 0; i < 4; i++)
                {
                    float tmp[3];
                    tmp[0] = i * 90.0;
                    tmp[1] = 4.0;
                    tmp[2] = 16.0;

                    addbullet(chrt, NULL, 930, x, y, dir, 1, tmp, 3);
                }
                active = false;
                return;
            }
            field_378 = (640.0 - field_378) * 0.02 + field_378;
            field_37C = 0.02 * (640.0 - field_37C) + field_37C;
            addition[0] += 0.5;
            if ( addition[0] > 360.0 )
                addition[0] -= 360.0;

            float tx = cos_deg(-addition[0]) * addition[1] + field_378;
            float ty = sin_deg(-addition[0]) * (addition[1] * 0.3) + field_37C;

            if ( sin_deg(-addition[0]) <= 0.0 )
                dir = -1;
            else
                dir = 1;

            h_inerc = (tx - x) * 0.01;
            v_inerc = (ty - y) * 0.01;

            if ( get_subseq() == 9 )
            {
                if ( get_elaps_frames() % 2 == 0 && get_elaps_frames() <= 45 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(400) + 200.0;
                    tmp[2] = scene_rand_rngf(7);
                    addbullet(chrt, this, 933, x, y, dir, 1, tmp, 3);
                }
                if ( get_elaps_frames() >= 60 )
                {
                    next_subseq();
                    field_36C = 0;

                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        field_36E = 15;
                        field_370 = 6;
                        break;
                    case GAME_DIFF_HARD:
                        field_36E = 15;
                        field_370 = 5;
                        break;
                    case GAME_DIFF_NORMAL:
                        field_36E = 20;
                        field_370 = 4;
                        break;
                    case GAME_DIFF_EASY:
                        field_36E = 30;
                        field_370 = 3;
                        break;
                    default:
                        break;
                    }
                    return;
                }
            }
            if ( get_subseq() == 10 )
            {
                if ( (get_elaps_frames() % field_36E == 0) && field_370 > 0 )
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(70) * 0.1 + 8.0;
                    tmp[2] = 0.0;
                    addbullet(chrt, NULL, 932, x, y, dir, -1, tmp, 3);
                    chrt->play_sfx( 3);
                    field_370--;
                }
                if ( get_elaps_frames() >= 150 )
                {
                    next_subseq();
                    return;
                }
            }
            x += h_inerc;
            y += v_inerc;
        }
        break;
        case 16:
            if ( c_A < 3 )
            {
                active = false;
                return;
            }
            c_A -= 3;
            c_B -= 3;
            c_G -= 3;

            x += dir * h_inerc;
            y += v_inerc;
            break;
        default:
            break;
        }

        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            if (get_subseq() == 9 || get_subseq() == 12 || get_subseq() == 16)
                set_subseq(5);
        break;

    case 931:
        if ( get_subseq() >= 1 && get_subseq() <= 3 )
        {
            if ( chrt->char_is_shock() )
            {
                if ( field_36C <= 1 )
                {
                    active = false;
                    return;
                }
            }
            else if ( field_36C <= 1 && bul_parent && bul_parent->get_subseq() != 7 )
            {
                field_36C = 2;
            }
            if ( field_36C == 0)
            {
                if ( bul_parent )
                {
                    dir = bul_parent->dir;
                    x = bul_parent->x + (bul_parent->get_pframe()->extra1[4] * bul_parent->dir);
                    y = bul_parent->y - bul_parent->get_pframe()->extra1[5];
                }
                else
                {
                    field_36C = 2;
                }
                scaleY += 0.15;
                if ( scaleY > 1.0 )
                {
                    scaleY = 1.0;
                    field_36C = 1;
                    field_194 = 20;
                    return;
                }
            }
            if ( field_36C == 1 )
            {
                if ( get_elaps_frames() % 2 == 0 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 7.0;

                    float xx = scene_rand_rngf(960) * dir + x;

                    addbullet(chrt, this, 931, xx, y, dir, 1, tmp, 3);
                }
                if ( bul_parent )
                {
                    dir = bul_parent->dir;
                    x = bul_parent->x + (bul_parent->get_pframe()->extra1[4] * bul_parent->dir);
                    y = bul_parent->y - bul_parent->get_pframe()->extra1[5];
                    if (bul_parent->field_36C == 1)
                        field_36C = 2;
                }
                else
                {
                    field_36C = 2;
                }

                sub_48C5F0(0);
                if ( field_190 )
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_36E = 0;
                        field_190 = 0;
                    }
                }
            }
            if ( field_36C == 2 )
            {
                field_194 = 0;
                scaleY *= 0.85;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 5 )
        {
            if ( field_36C == 0)
            {
                if ( !bul_parent )
                {
                    active = false;
                    return;
                }
                x = bul_parent->x;
                y = bul_parent->y;

                if ( bul_parent->field_36C == 2 )
                    field_36C = 1;

                scaleX = scaleY = (get_elaps_frames() & 2) * 0.2 + 1.0;

                if ( chrt->char_is_shock() )
                {
                    active = false;
                    return;
                }
            }
            if ( field_36C == 1 )
            {
                scaleY = scaleX *= 0.85;
                if ( scaleX < 0.02 )
                {
                    active = false;
                    return;
                }
            }
        }
        if ( get_subseq() == 7 )
        {
            scaleY = scaleX += 0.05;
            angZ += 30.0;
            if ( bul_parent )
                y = bul_parent->y;
            if ( chrt->char_is_shock() )
            {
                active = false;
                return;
            }
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            c_A -= 10;
            c_G -= 10;
            c_B -= 10;
            x += (25 * dir);
            if ( x > 1380.0 || x < -100.0)
            {
                active = false;
                return;
            }
        }
        if (process())
            active = false;
        break;

    case 932:
        if ( get_subseq() <= 2 && (chrt->char_is_shock() || health < 0) )
        {
            set_subseq(3);
            return;
        }
        if ( get_subseq() == 0 )
        {
            angZ += 30.0;
            if ( get_elaps_frames() >= 120 )
            {
                next_subseq();
                order = -1;
                if ( x - chrt->x <= 0.0 )
                    dir = 1;
                else
                    dir = -1;
                chrt->play_sfx( 8);
                sub_48C4B0(0.0, 180.0, 100.0);
                angZ = 0.0;
                return;
            }
            set_vec_speed(addition[0], addition[1]);
            addition[1] *= 0.95;
            x += h_inerc * dir;
            y += v_inerc;
        }
        if ( get_subseq() == 1 )
        {
            if ( get_elaps_frames() == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 5.0;
                addbullet(chrt, this, 932, x, y, dir, 1, tmp, 3);
            }
            sub_48C5F0(0);
            if ( field_190 )
            {
                field_36C++;
                if ( field_36C >= 4 )
                {
                    field_36C = 0;
                    field_190 = 0;
                }
            }
            set_vec_speed(addition[0], addition[1]);
            addition[1] += 0.2;
            if ( addition[1] >= 15.0 )
                addition[1] = 15.0;
            x += h_inerc * dir;
            y += v_inerc;
            if ( x > 1380.0 || x < -100.0 || y > 1000.0 || y < -300.0 )
            {
                active = false;
                return;
            }
        }
        if ( get_subseq() == 3 )
        {
            if ( 5.0 < h_inerc )
                h_inerc = 5.0;
            if ( h_inerc < -5.0 )
                h_inerc = -5.0;
            if ( 5.0 < v_inerc )
                v_inerc = 5.0;
            if ( v_inerc < -5.0 )
                v_inerc = -5.0;
            v_inerc -= 0.5;
            x += h_inerc;
            y += v_inerc;
            angZ += 15.0;
            if ( c_A < 20 )
            {
                active = false;
                return;
            }
            c_A -= 20;
        }
        if ( get_subseq() == 5 )
        {
            angZ += 25.0;
            if ( !bul_parent )
            {
                active = false;
                return;
            }
            if ( bul_parent->get_subseq() == 1 )
            {
                x = bul_parent->x;
                y = bul_parent->y;
                scaleX += 0.1;
                if ( scaleX > 3.0 )
                    scaleX = 2.5;
                scaleY = scaleX;
                if ( c_A <= 225 )
                    c_A += 30;
                else
                    c_A = 255;
            }
            else
            {
                if ( c_A < 20 )
                {
                    active = false;
                    return;
                }
                scaleX += 0.1;
                c_A -= 20;
                c_R -= 20;
                c_G -= 20;
            }
        }
        if (process())
            active = false;
        break;

    case 933:
        if ( get_subseq() <= 6 )
        {
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( chrt->char_is_shock() )
                field_36C = 2;
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
                x = (cos_deg(-addition[0]) * addition[1]) * dir + field_37C;
                y = sin_deg(-addition[0]) * addition[1] + field_380;
                if ( c_A <= 5 )
                {
                    active = false;
                    break;
                }
                c_A -= 5;
            }
        }
        if (process())
            active = false;
        break;

    case 940:
        if ( get_subseq() >= 6 && get_subseq() <= 11 )
        {
            if ( y <= 30.0)
            {
                v_inerc += 0.01;
                if ( v_inerc >= 1.5 )
                    v_inerc = 1.5;
            }
            else
            {
                v_inerc -= 0.01;
                if ( v_inerc <= -1.5 )
                    v_inerc = -1.5;
            }
            if ( enemy->health > 0 )
                chrt->field_88A--;

            if ( chrt->field_88A <= 0 )
            {
                chrt->field_888--;
                chrt->field_88A = 60;
                if ( chrt->field_888 >= 0 && chrt->field_888 <= 9 )
                {
                    scene_play_sfx(74);
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 6.0;

                    addbullet(chrt, NULL, 1203, 320.0, 130.0, 1, 3, tmp, 3);
                }
            }
            if ( chrt->field_888 <= 0 )
            {
                //shake_camera(3.0);
                field_372++;
                if ( field_372 >= field_374 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 0.0;

                    float xx = x + 150.0 - scene_rand_rngf(300);
                    float yy = scene_rand_rngf(500) + y;

                    addbullet(chrt, NULL, 942, xx, yy, dir, 1, tmp ,3);

                    field_374 -= 3;
                    if ( field_374 <= 10 )
                        field_374 = 10;
                    field_372 = 0;
                }
                if ( chrt->field_888 <= -8 )
                {
                    chrt->play_sfx( 21);
                    active = false;
                    return;
                }
            }
        }
        switch ( get_subseq() )
        {
        case 5:
            if ( field_36C == 0 )
            {
                scaleY = scaleX += 0.005;
                if ( scaleX < 1.0 )
                {
                    if ( get_elaps_frames() % 15 == 0 )
                    {
                        for (int i = 0; i < 12; i++)
                        {
                            float tmp[3];
                            tmp[0] = scene_rand_rngf(10) + i * 30.0;
                            tmp[1] = scene_rand_rngf(25) * 0.1 + 10.0;
                            tmp[2] = 0.0;

                            float xx = cos_deg(-tmp[0]) * (tmp[1] * 10.0) * dir + x;
                            float yy = sin_deg(-tmp[0]) * (tmp[1] * 3.0) + y;

                            int8_t ord = 1 - (2 * (sin_deg(-tmp[0]) > 0.0));

                            addbullet(chrt, NULL, 941, xx, yy, dir, ord, tmp, 3);
                        }
                    }
                }
                else
                {
                    scaleX = 1.0;
                    scaleY = 1.0;
                    field_36C = 1;

                    set_elaps_frames(0);
                }
                if ( shader_cR <= 1 )
                {
                    shader_type = 0;
                }
                else
                {
                    shader_cR -= 2;
                    shader_cG = shader_cR;
                    shader_cB = shader_cR;
                }
            }
            if ( field_36C == 1 && get_elaps_frames() >= 30 )
            {
                chrt->field_888 = 60;
                chrt->field_88A = 60;
                next_subseq();
                field_380 = enemy->x;
                return;
            }
            break;
        case 6:
            h_inerc = (field_380 - x) * 0.05 * dir;
            break;
        case 7:
            h_inerc = (field_380 - x) * 0.05 * dir;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_36C = 60;
                break;
            case GAME_DIFF_HARD:
                field_36C = 90;
                break;
            case GAME_DIFF_NORMAL:
                field_36C = 120;
                break;
            case GAME_DIFF_EASY:
                field_36C = 150;
                break;
            default:
                break;
            }
            if ( chrt->field_888 <= 10 )
                field_36C *= 0.4;
            if ( chrt->field_888 <= 30 )
                field_36C *= 0.55;
            if ( chrt->field_888 <= 40 )
                field_36C *= 0.675;
            if ( chrt->field_888 <= 50 )
                field_36C *= 0.8;

            if ( (int32_t)get_elaps_frames() >= field_36C )
            {
                next_subseq();
                return;
            }
            break;
        case 8:
            h_inerc = 0.0;
            break;
        case 9:
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_36C = 20;
                break;
            case GAME_DIFF_HARD:
                field_36C = 25;
                break;
            case GAME_DIFF_NORMAL:
                field_36C = 30;
                break;
            case GAME_DIFF_EASY:
                field_36C = 35;
                break;
            default:
                break;
            }
            if ( chrt->field_888 <= 15 )
                field_36C *= 0.1;
            else if ( chrt->field_888 <= 35 )
                field_36C *= 0.3;
            else if ( chrt->field_888 <= 45 )
                field_36C *= 0.5;
            else if ( chrt->field_888 <= 55 )
                field_36C *= 0.75;
            if ( (int32_t)get_elaps_frames() >= field_36C )
            {
                next_subseq();
                return;
            }
            break;
        case 11:
            if ( chrt->field_888 >= 1 && enemy->health > 0 )
            {
                field_380 = enemy->x;
                set_subseq(6);
                return;
            }
            break;
        default:
            break;
        }
        x += h_inerc * dir;
        y += v_inerc;
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 7 )
        {
            float tmp[3];
            if ( field_374 )
            {
                tmp[0] = scene_rand_rngf(45) + 40.0;
                field_374 = 0;
            }
            else
            {
                tmp[0] = scene_rand_rngf(45);
                field_374 = 1;
            }
            tmp[1] = 1.0;
            tmp[2] = 1.0;
            float xx = enemy->x;
            float yy = enemy->y + 100.0;
            addbullet(chrt, this, 941, xx, yy, dir, 1, tmp, 3);
            addbullet(chrt, this, 941, xx, yy, -dir, 1, tmp, 3);
        }
        if ( get_subseq() == 8 )
        {
            if ( get_frame_time() == 0 && get_frame() == 1 )
            {
                chrt->play_sfx(38);
                for (int i = 0; i < 20; i++)
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(10) + i * 18.0;
                    tmp[1] = scene_rand_rngf(25) * 0.1 + 17.5;
                    tmp[2] = 0.0;

                    float xx = cos_deg(-tmp[0]) * (tmp[1] * 10.0) * dir + x;
                    float yy = sin_deg(-tmp[0]) * (tmp[1] * 3.0) + y;

                    int8_t ord = 1 - (2 * (sin_deg(-tmp[0]) > 0.0));

                    addbullet(chrt, NULL, 941, xx, yy, dir, ord, tmp, 3);
                }
            }
            if ( get_frame_time() == 0 && get_frame() == 2 )
            {
                if (chrt->field_888 <= 20)
                {
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        field_36E = 40;
                        break;
                    case GAME_DIFF_HARD:
                        field_36E = 20;
                        break;
                    case GAME_DIFF_NORMAL:
                        field_36E = 10;
                        break;
                    case GAME_DIFF_EASY:
                        field_36E = 0;
                        break;
                    default:
                        break;
                    }
                }
                else if (chrt->field_888 <= 40)
                {
                    switch ( settings_get()->get_difficulty() )
                    {
                    case GAME_DIFF_LUNA:
                        field_36E = 20;
                        break;
                    case GAME_DIFF_HARD:
                        field_36E = 10;
                        break;
                    case GAME_DIFF_NORMAL:
                        field_36E = 5;
                        break;
                    case GAME_DIFF_EASY:
                        field_36E = 0;
                        break;
                    default:
                        break;
                    }
                }
                else
                    return;

                if ( field_36E > 0 )
                    for (int i = 0; i < field_36E; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(360);
                        tmp[1] = scene_rand_rngf(20) * 0.1 + 3.0;
                        tmp[2] = 5.0;

                        float yy = y + 255.0;

                        addbullet(chrt, NULL, 941, x, yy, dir, 1, tmp, 3);
                    }
            }
        }
        break;

    case 941:
        switch ( get_subseq() )
        {
        case 0:
            angZ += field_378;
            field_378 *= 0.98;
            scaleY = scaleX += 0.03;
            if ( c_A < 8 )
            {
                active = false;
                return;
            }
            c_A -= 6;
            set_vec_speed(addition[0], addition[1]);
            v_inerc *= 0.15;
            break;
        case 1:
            scaleX += addition[1];
            addition[1] *= 0.97;
            scaleY *= 0.99;
            if ( !bul_parent )
            {
                active = false;
                return;
            }
            if ( bul_parent->get_subseq() == 11 )
            {
                active = false;
                return;
            }
            if ( bul_parent->get_subseq() == 8 && bul_parent->get_frame() == 2 )
            {
                float tmp[3];
                tmp[0] = angZ;
                tmp[1] = 0.0;
                tmp[2] = 2.0;
                if ( settings_get()->get_difficulty() == GAME_DIFF_HARD )
                    tmp[2] = 3.0;
                else if ( settings_get()->get_difficulty() == GAME_DIFF_LUNA )
                    tmp[2] = 4.0;

                addbullet(chrt, NULL, 941, x, y, dir, 1, tmp, 3);
                active = false;
                return;
            }
            break;
        case 2:
        case 3:
        case 4:
            scaleX += 0.02;
            if ( get_elaps_frames() >= 10 )
            {
                field_194 = 0;
                scaleY *= 0.98;
                if ( c_A < 5 )
                {
                    active = false;
                    return;
                }
                c_A -= 5;
            }
            break;
        case 5:
            if ( chrt->field_888 <= 0 )
                field_36C = 1;
            if ( field_36C == 0 && (get_elaps_frames() >= 180 || field_194 <= 0) )
            {
                field_36C = 1;
                field_194 = 0;
            }
            if ( field_36C == 1 )
            {
                scaleY = scaleX *= 0.95;
                if ( c_A < 5 )
                {
                    active = false;
                    return;
                }
                c_A -= 5;
            }
            break;
        default:
            break;
        }
        x += dir * h_inerc;
        y += v_inerc;
        if (process())
            active = false;
        break;

    case 942:
        if ( get_subseq() == 0)
        {
            if ( get_elaps_frames() >= 10 )
            {
                scaleY = scaleX *= 0.98;
                if ( c_A < 6 )
                {
                    active = false;
                    return;
                }
                c_A -= 6;
                c_G -= 6;
                c_B -= 6;
            }
        }
        if ( get_subseq() == 1 )
        {
            scaleY = scaleX += addition[1];
            addition[1] = 0.1455;
            if ( c_A < 6 )
            {
                active = false;
                return;
            }
            c_A -= 6;
            c_G -= 6;
            c_B -= 6;
        }
        if (get_subseq() == 2)
        {
            angZ += field_378;
            field_378 *= 0.995;
            scaleY = scaleX += 0.01;
            addition[1] *= 0.97;
            if ( addition[1] <= 1.0 )
                addition[1] = 1.0;

            if ( c_A < 7 )
            {
                active = false;
                return;
            }

            c_A -= 7;
            c_G -= 7;
            c_B -= 7;
            set_vec_speed(addition[0], addition[1]);
        }
        x += dir * h_inerc;
        y += v_inerc;
        if (process())
            active = false;
        break;

    case 970:
        if ( get_subseq() <= 6 )
        {
            addition[1] *= 0.95;
            scaleY = scaleX *= 0.98;
            angZ += field_378;
            if ( chrt->char_is_shock() )
                field_36C = 2;
            if ( field_36C == 0 )
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
                    return;
                }
                c_A -= 5;
            }
        }
        if (process())
            active = false;
        break;
    case 980:
        //sub_48C190(); //HACK
        if (process())
            active = false;
        break;

    case 998:
        if ( get_subseq() == 0 )
        {
            if ( chrt->get_seq() > 153 && chrt->get_seq() < 158 )
            {
                x = (60 * dir) + chrt->x;
                y = chrt->y + 60.0;
            }
            if ( chrt->get_seq() > 149 && chrt->get_seq() < 154 )
            {
                x = (60 * dir) + chrt->x;
                y = chrt->y + 110.0;
            }
            if ( chrt->get_seq() == 158 )
            {
                x = (60 * dir) + chrt->x;
                y = chrt->y + 100.0;
            }
            if ( chrt->get_seq() < 150 || chrt->get_seq() > 158 )
            {
                next_subseq();
                chrt->bbarrier_show = false;
            }
        }
        if ( get_subseq() == 1 )
        {
            if ( c_A < 10 )
            {
                active = false;
                return;
            }
            else
            {
                c_G -= 10;
                c_B -= 10;
                c_A -= 10;
            }
        }
        if (process())
            active = false;
        break;
    case 999:
        switch ( get_subseq() )
        {
        case 0:
            v_inerc -= 0.3;
            if ( getlvl_height() >= v_inerc + y )
            {
                chrt->field_86C = 1;
                y = getlvl_height();
                h_inerc = 0.0;
                v_inerc = 0.0;
                v_force = 0.0;
                set_subseq(1);
                return;
            }
            break;
        case 2:
            if ( chrt->field_86E == 1 )
            {
                next_subseq();
                dir = 1;
                return;
            }
            break;
        case 3:
        case 4:
            if ( get_subseq() >= 4 )
                v_inerc -= v_force;
            break;
        default:
            break;
        }
        x += h_inerc * dir;
        y += v_inerc;
        if ( process() )
            active = false;
        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
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

void alice_bullets::set_seq_params()
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
        field_194 = 1;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() >= 7 )
        {
            angX = scene_rand_rngf(90) - 45.0;
            angY = scene_rand_rngf(90) - 45.0;
        }
        break;
    case 801:
        if ( addition[2] >= 2.0 )
            set_subseq(addition[2]);

        if ( get_subseq() == 0 )
        {
            h_inerc = 40.0;
            v_inerc = 10.0;
        }
        if ( get_subseq() == 7 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;
            addbullet(chrt, this, 803, x ,y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 10 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 12.0;
            addbullet(chrt, this, 801, x ,y, dir, 1, tmp, 3);

            field_194 = 8;

            for (int i=0; i < 4; i++)
            {
                tmp[0] = 0.0;
                tmp[1] = i * 90.0;
                tmp[2] = 11.0;
                addbullet(chrt, this, 801, x ,y, dir, 1, tmp, 3);
            }
        }
        if ( get_subseq() == 11 )
        {
            angZ = addition[1];
            scaleX = 1.0;
            scaleY = 0.0;
        }
        if ( get_subseq() == 12 )
        {
            scaleX = 0.0;
            scaleY = 0.0;
        }
        break;
    case 802:
        h_inerc = 40.0;
        v_inerc = 10.0;
        break;
    case 803:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 7 )
        {
            h_inerc = addition[1];
            v_inerc = 0.0;

            float tmp[3];
            tmp[0] = 0;
            tmp[1] = 0;
            tmp[2] = 6;

            addbullet(chrt,this,803,x,y,dir,1,tmp,3);
        }
        else if ( get_subseq() == 6 && bul_parent != NULL )
        {
            angZ = -atan2_deg(enemy->y + 100 - y, enemy->x - x);

            field_378 = (bul_parent->x - x) * (bul_parent->x - x);
            field_37C = (bul_parent->y - y) * (bul_parent->y - y);
            field_380 = sqrt(field_378 + field_37C);
            scaleX = field_380 * 0.0039;
        }
        break;
    case 804:
        field_194 = 1;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() >= 7 )
        {
            field_36C = scene_rand_rng(15) + 5;
            scaleY = scaleX = scene_rand_rng(15) * 0.1 + 0.5;
        }
        break;
    case 805:
        if ( addition[2] >= 2.0 )
            set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            h_inerc = 40.0;
            v_inerc = 0.0;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 7.0;
            addbullet(chrt, this, 805, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 7 && bul_parent )
        {
            angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
            field_378 = (bul_parent->x - x) * (bul_parent->x - x);
            field_37C = (bul_parent->y - y) * (bul_parent->y - y);
            field_380 = sqrt(field_378 + field_37C);
            scaleX = field_380 * 0.0039;
        }
        break;
    case 806:
        field_194 = 1;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() >= 7 )
        {
            angX = scene_rand_rngf(90) - 45.0;
            angY = scene_rand_rngf(90) - 45.0;
        }
        break;
    case 807:
        scaleX = 4.0;
        scaleY = 0.1;
        angZ = addition[0];
        set_subseq(addition[2]);
        field_36C = 0;
        break;
    case 810:
        field_18C = 0;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 4;
            if ( chrt->skills_1[0] >= 2 )
                field_194 = 5;
            if ( chrt->skills_1[0] >= 4 )
                field_194++;
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;
            addbullet(chrt, this, 810, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 4 )
        {
            if ( bul_parent )
            {
                angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_378 + field_37C);
                scaleX = field_380 * 0.0039;
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleX = 2.5;
            scaleY = 2.5;
            angX = scene_rand_rngf(5) + 70.0;
            angZ = scene_rand_rngf(360);
            c_A = 0;
        }
        break;
    case 811:
        field_194 = 1;
        field_18C = 4;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 2.0;
            addbullet(chrt, this, 811, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 2 )
        {
            if ( bul_parent )
            {
                angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_378 + field_37C);
                scaleX = field_380 * 0.0039;
            }
        }
        if ( get_subseq() == 3 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
            angX = scene_rand_rngf(5) + 70.0;
            angZ = scene_rand_rngf(360);
            c_A = 0;
        }
        break;
    case 812:
        field_18C = 8;
        field_194 = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 7.0;
            addbullet(chrt, this, 812, x, y, dir, 1, tmp, 3);
            field_378 = x;
            field_37C = y;
            field_388 = 125.0;
        }
        if ( get_subseq() == 7 )
        {
            if ( bul_parent )
            {
                angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_378 + field_37C);
                scaleX = field_380 * 0.0039;
            }
        }
        if ( get_subseq() == 9 )
            angZ = addition[0];
        break;
    case 815:
        field_18C = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            set_vec_speed(addition[0], addition[1]);
            if ( chrt->skills_1[1] >= 2 )
                field_194 = 1;
        }
        if ( get_subseq() == 2 || get_subseq() == 5 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;
            addbullet( chrt, NULL, 815, x, y, dir, 1, tmp,3);
            tmp[2] = 4.0;

            addbullet( chrt, NULL, 815, x, y, dir, 1, tmp,3);
            field_194 = 1;
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
        }
        break;
    case 816:
        field_18C = 5;
        field_194 = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            h_inerc = addition[0];
            v_inerc = addition[1];
            field_194 = chrt->skills_1[5] >= 4;
        }
        if ( get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;
            addbullet( chrt, NULL, 816, x, y, dir, 1, tmp,3);
            tmp[2] = 4.0;
            addbullet( chrt, NULL, 816, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
        }
        break;
    case 817:
        field_18C = 9;
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 9 )
        {
            field_138 = -6.0;
            has_shadow = 1;
            h_inerc = addition[0];
            v_inerc = addition[1];
        }
        if ( get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;
            addbullet( chrt, NULL, 817, x, y, dir, 1, tmp,3);
            tmp[2] = 4.0;
            addbullet( chrt, NULL, 817, x, y, dir, 1, tmp,3);
        }
        if ( get_subseq() == 4 )
        {
            angZ = scene_rand_rngf(360);
        }
        break;
    case 820:
        field_18C = 2;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 1;
            h_inerc = addition[0];
            v_inerc = addition[1];
            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;
            tmp[3] = 0.0;
            addbullet(chrt, this, 820, x, y, dir, 1, tmp, 4);
        }
        if ( get_subseq() == 6 && bul_parent )
        {
            angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
            field_378 = SQR(bul_parent->x - x);
            field_37C = SQR(bul_parent->y - y);
            field_380 = sqrt(field_378 + field_37C);
            scaleX = field_380 * 0.0039;
        }
        break;
    case 821:
        field_18C = 6;
        field_194 = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            h_inerc = -2.0;
            v_inerc = 0.0;
        }
        if ( get_subseq() == 4 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;
            addbullet( chrt, NULL, 821, x - (140 * dir), y, dir, 1, tmp,3);
        }
        break;
    case 822:
        field_18C = 10;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 7.0;
            tmp[3] = 0.0;
            addbullet(chrt, this, 822, x, y, dir, 1, tmp, 4);
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 1;
            angZ = addition[0];
            tail_add(991, 3.0, 15, 1, gr_alpha);
            set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 7 && bul_parent )
        {
            angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
            field_378 = SQR(bul_parent->x - x);
            field_37C = SQR(bul_parent->y - y);
            field_380 = sqrt(field_378 + field_37C);
            scaleX = field_380 * 0.0039;
        }
        break;
    case 825:
        field_18C = 3;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_194 = 4;
            if ( chrt->skills_1[3] >= 2 )
                field_194 = 5;
            if ( chrt->skills_1[3] >= 4 )
                field_194++;

            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(chrt, this, 810, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 4 )
        {
            if ( bul_parent )
            {
                angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_378 + field_37C);
                scaleX = field_380 * 0.0039;
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleX = 2.5;
            scaleY = 2.5;
            angX = scene_rand_rngf(5) + 70.0;
            c_A = 0;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 827:
        field_18C = 11;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 3 || get_subseq() == 5 || get_subseq() == 6 )
            field_194 = 1;
        if ( get_subseq() == 2 || get_subseq() == 4 )
            field_378 = 0.4;
        break;
    case 830:
        field_194 = 1;
        field_37C = 20.0;
        break;
    case 831:
        field_18C = 7;
        field_194 = 1;
        field_190 = 0;
        set_subseq(addition[2]);
        if ( get_subseq() == 5 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;
            addbullet(chrt, this, 831, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 0;
            scaleX = 50.0;
            scaleY = 0.1;
        }
        break;
    case 834:
        field_194 = 1;
        field_18C = 7;
        set_subseq( addition[2]);
        if ( get_subseq() == 5 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;
            addbullet(chrt, this, 834, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 6 )
        {
            field_194 = 0;
            scaleX = 50.0;
            scaleY = 0.1;
        }
        break;
    case 849:
        set_subseq(addition[2]);
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 5 || get_subseq() == 13 )
            angZ = addition[0];
        if ( get_subseq() == 6 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 8 )
        {
            for (int8_t i = 0; i < 6; i++)
            {
                float tmp[4];
                tmp[0] = i * 60.0 + 30.0;
                tmp[1] = 0.0;
                tmp[2] = 6.0;
                tmp[3] = 1.0;
                if ( tmp[0] <= 90.0 || tmp[0] >= 270.0 )
                    addbullet(chrt, this, 849, x, y, dir, -1, tmp, 4);
                else
                    addbullet(chrt, this, 849, x, y, dir, 1, tmp, 4);
            }
        }
        if ( get_subseq() == 26 )
        {
            h_inerc = 30.0;
            field_194 = 1;
            field_190 = 0;
            v_inerc = 0.0;
            for (int8_t i = 0; i < 8; i++)
            {
                float tmp[4];
                tmp[0] = i * 45.0 + 30.0;
                tmp[1] = 0.0;
                tmp[2] = 6.0;
                tmp[3] = 1.25;
                if ( tmp[0] <= 90.0 || tmp[0] >= 270.0 )
                    addbullet(chrt, this, 849, x, y, dir, -1, tmp, 4);
                else
                    addbullet(chrt, this, 849, x, y, dir, 1, tmp, 4);
            }
        }
        if ( get_subseq() == 10 )
        {
            if ( bul_parent )
            {
                angZ = -atan2_deg(enemy->y + 100.0 - y, enemy->x - x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_378 + field_37C);
                scaleX = field_380 * 0.0039;
            }
        }
        if ( get_subseq() == 11 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
            field_194 = 1;
            field_190 = 0;
            angZ = addition[0];
        }
        if ( get_subseq() == 14 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 16 )
        {
            for (int8_t i = 0; i < 6; i++)
            {
                float tmp[3];
                tmp[0] = i * 60.0 + 30.0;
                tmp[1] = 0.0;
                tmp[2] = 14.0;
                if ( tmp[0] <= 90.0 || tmp[0] >= 270.0 )
                    addbullet(chrt, this, 849, x, y, dir, -1, tmp, 3);
                else
                    addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
            }
        }
        if ( get_subseq() == 19 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 10.0;
            addbullet(chrt, this, 849, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 22 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
            angX = scene_rand_rng(5) + 70.0;
            c_A = 0;
            angZ = scene_rand_rng(360);
        }
        break;
    case 850:
        field_194 = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            field_360 = 1;
            h_inerc = fabs(enemy->x - x) / 42.0;
            if ( h_inerc < 2.0 )
                h_inerc = 2.0;
            v_inerc = 20.0;
        }
        if ( get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;
            addbullet(chrt, NULL, 850, x, y, dir, -1, tmp, 3);

            tmp[2] = 4.0;
            addbullet(chrt, NULL, 850, x, y, dir, 1, tmp, 3);

            float angl = 0;
            while (angl < 360.0)
            {
                tmp[0] = angl;
                tmp[1] = 30.0;
                tmp[2] = 5.0;

                addbullet(chrt, NULL, 850, x, y, dir, 1, tmp, 3);
                angl += 45;
            }
        }
        if ( get_subseq() == 5 )
            angZ = scene_rand_rng(360);
        break;
    case 851:
        field_380 = 30.0;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_378 = x;
            field_37C = y;

            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;
            tmp[3] = 0.0;
            addbullet(chrt, this, 851, x, y, dir, 1, tmp, 4);

            field_194 = 0;
            if ( addition[3] == 0.0 )
                field_194 = 1;
        }
        if ( get_subseq() == 4 )
        {
            if ( bul_parent )
            {
                float e_x = enemy->x - x;
                float e_y = enemy->y + 100.0 - y;
                angZ = -atan2_deg(e_y, e_x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_37C + field_378);
                scaleX = field_380 * 0.004;
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
            angX = 70.0;
        }
        break;
    case 852:
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 5 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;

            addbullet(chrt, this, 852, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 6 )
        {
            chrt->play_sfx( 23);
            scaleX = 50.0;
            field_194 = 0;
            scaleY = 0.1;
        }
        if ( get_subseq() == 7 )
            angY = 70.0;
        break;
    case 853:
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            h_inerc = fabs(enemy->x - x) / 22.0;
            if ( h_inerc < 2.0 )
                h_inerc = 2.0;
            v_inerc = 20.0;
        }
        if ( get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;

            addbullet(chrt, NULL, 853, x, y, dir, -1, tmp, 3);

            tmp[2] = 4.0;
            addbullet(chrt, NULL, 853, x, y, dir, 1, tmp, 3);

            float angl = 0;
            while (angl < 360)
            {

                tmp[0] = angl;
                tmp[1] = 40.0;
                tmp[2] = 5.0;
                addbullet(chrt, NULL, 853, x, y, dir, 1, tmp, 3);

                angl += 30;
            }
        }
        if ( get_subseq() == 5 )
        {
            angZ = scene_rand_rngf(360);
        }
        break;
    case 854:
        field_380 = 30.0;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_378 = x;
            field_37C = y;
            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;
            tmp[3] = 0.0;
            addbullet(chrt, this, 851, x, y, dir, 1, tmp,4);
        }
        if ( get_subseq() == 4 )
        {
            if ( bul_parent )
            {
                float e_x = enemy->x - x;
                float e_y = enemy->y + 100.0 - y;
                angZ = -atan2_deg(e_y, e_x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_37C + field_378);
                scaleX = field_380 * 0.004;
            }
        }
        if ( get_subseq() == 5 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
            angX = 70.0;
            angZ = 0.0;
        }
        if ( get_subseq() == 6 )
        {
            scaleX = 2.5;
            scaleY = 2.5;
            angX = 70.0;
            angZ = 0.0;
        }
        break;
    case 855:
        field_194 = 1;
        set_subseq( addition[2]);
        if ( get_subseq() == 5 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 6.0;
            addbullet(chrt, this, 855, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 6 )
        {
            chrt->play_sfx( 27);
            scaleX = 50.0;
            scaleY = 0.1;
        }
        break;
    case 856:
        set_subseq( addition[2]);
        if ( get_subseq() == 0 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 7.0;
            addbullet(chrt, this, 856, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 7 )
        {
            if ( bul_parent )
            {
                float e_x = enemy->x - x;
                float e_y = enemy->y + 100.0 - y;
                angZ = -atan2_deg(e_y, e_x);
                field_378 = SQR(bul_parent->x - x);
                field_37C = SQR(bul_parent->y - y);
                field_380 = sqrt(field_37C + field_378);
                scaleX = field_380 * 0.004;
            }
        }
        if ( get_subseq() == 8 )
        {
            field_190 = 0;
            field_194 = 0;
            field_378 = (4 * ((int)addition[3] % 2)) - 2.0;
            scaleX = 4.0;
            scaleY = 0.1;
            angZ = addition[0];
            float tmp[4];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 9.0;
            tmp[3] = 0.0;
            addbullet(chrt, this, 856, x, y, dir, 1, tmp, 4);
        }
        break;
    case 857:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 7.0;
            addbullet(chrt, this, 857, x, y, dir, -1, tmp, 3);
        }
        if ( get_subseq() == 3 )
        {
            field_378 = 1.0;
            scaleX = 0.25;
            scaleY = 0.25;
        }
        if ( get_subseq() == 2 )
        {
            angZ = addition[0];
            scaleY = 0.0;
            scaleX = 1.5;
        }
        break;
    case 858:
        set_subseq(addition[2]);
        if ( get_subseq() == 1 )
        {
            h_inerc = 10.0;
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 20.0;

            addbullet(chrt, this, 858, x, y, dir, -1, tmp, 3);

            tmp[2] = 24.0;
            addbullet(chrt, this, 858, x, y, dir, -1, tmp, 3);
        }
        if ( get_subseq() == 3 )
        {
            h_inerc = 10.0;
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 20.0;

            addbullet(chrt, this, 858, x, y, dir, -1, tmp, 3);

            tmp[2] = 24.0;
            addbullet(chrt, this, 858, x, y, dir, -1, tmp, 3);
        }
        if ( get_subseq() == 21 || get_subseq() == 22 )
        {
            angZ = addition[0];
            c_meta::set_vec_speed(addition[0], addition[1]);
        }
        if ( get_subseq() == 23 )
        {
            scaleX = 2.5;
            scaleY = 2.5;
            angX = scene_rand_rngf(5) + 70.0;
            angZ = scene_rand_rngf(360);
            c_A = 0;
        }
        if ( get_subseq() >= 26 && get_subseq() <= 32 )
        {
            field_194 = 1;
            angZ = addition[0];
        }
        if ( get_subseq() == 33 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 34.0;

            addbullet(chrt, this, 858, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 34 )
        {
            chrt->play_sfx(23);
            scaleX = 50.0;
            field_194 = 0;
            scaleY = 0.1;
        }
        if ( get_subseq() == 37 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 36.0;

            addbullet(chrt, NULL, 858, x, y, dir, 1, tmp, 3);

            tmp[2] = 35.0;
            addbullet(chrt, NULL, 858, x, y, dir, 1, tmp, 3);

            field_194 = 1;
        }
        break;
    case 859:
        set_subseq(addition[2]);
        if ( get_subseq() == 6 )
            scaleY = scaleX = scene_rand_rngf(10) * 0.1 + 0.5;
        break;

    case 860:
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            h_inerc = -2.0;
            v_inerc = 0.0;
        }
        if ( get_subseq() == 4 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;

            float xx = x - (140 * dir);

            addbullet(chrt, NULL, 860, xx, y, dir, 1, tmp, 3);
        }
        break;

    case 861:
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 || get_subseq() == 9 )
        {
            has_shadow = 1;
            h_inerc = addition[0];
            v_inerc = addition[1];
            field_378 = scene_rand_rngf(120) * 0.1 + 6.0;
            field_36E = scene_rand_rngf(10);
            if ( get_subseq() == 9 )
                field_380 = scene_rand_rngf(20) - 10.0;
            has_shadow = 1;
            field_138 = field_380 - 6.0;
        }
        if ( get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;

            addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 3);

            tmp[2] = 4.0;

            addbullet(chrt, NULL, 861, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 4 )
            angZ = scene_rand_rngf(360);
        break;

    case 900:
        field_18C = 1;
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            set_vec_speed(addition[0], addition[1]);
        if ( get_subseq() == 3 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(chrt, NULL, 900, x, y, dir, 1, tmp, 3);

            tmp[2] = 5.0;

            addbullet(chrt, NULL, 900, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 5 )
            angZ = scene_rand_rngf(360);
        break;
    case 901:
        field_194 = 1;
        angZ = addition[0];
        set_subseq(addition[2]);
        if ( get_subseq() <= 6 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = get_subseq() + 7.0;

            addbullet(chrt, NULL, 901, x, y, dir, 1, tmp, 3);

            scaleY = 0.5;
            scaleX = 3.0;
        }
        break;
    case 902:
        set_subseq(addition[2]);
        if ( get_subseq() == 0)
        {
            set_vec_speed(addition[0], addition[1]);
            if ( chrt->skills_1[1] >= 2 )
                field_194 = 1;
        }
        if ( get_subseq() == 2 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 3.0;

            addbullet(chrt, NULL, 902, x, y, dir, 1, tmp, 3);

            tmp[2] = 4.0;

            addbullet(chrt, NULL, 902, x, y, dir, 1, tmp, 3);

            field_194 = 1;
        }
        if ( get_subseq() == 4 )
            angZ = scene_rand_rngf(360);
        break;

    case 910:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_37C = 15.0;
                field_378 = 22.5;
                break;
            case GAME_DIFF_HARD:
                field_37C = 15.0;
                field_378 = 20.0;
                break;
            case GAME_DIFF_NORMAL:
                field_37C = 15.0;
                field_378 = 17.5;
                break;
            case GAME_DIFF_EASY:
                field_37C = 15.0;
                field_378 = 15.0;
                break;
            default:
                break;
            }
        }
        if ( get_subseq() == 7 )
            angZ = addition[0];
        if ( get_subseq() == 9 )
        {
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_378 = 18.0;
                break;
            case GAME_DIFF_HARD:
                field_378 = 15.0;
                break;
            case GAME_DIFF_NORMAL:
                field_378 = 12.0;
                break;
            case GAME_DIFF_EASY:
                field_378 = 8.0;
                break;
            default:
                break;
            }

            for (int i = 0; i < field_378; i++)
            {
                float tmp[3];
                tmp[0] = (float)i * 360.0 / field_378;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                addbullet(chrt, this, 910, x, y, dir, -1, tmp, 3);

                ((char_alice *)chrt)->field_89A++;
            }
        }
        break;

    case 920:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_37C = x;
            field_380 = y;
        }
        if ( get_subseq() == 4 )
        {
            field_194 = 1;
            switch ( settings_get()->get_difficulty() )
            {
            case GAME_DIFF_LUNA:
                field_36E = 60;
                break;
            case GAME_DIFF_HARD:
                field_36E = 45;
                break;
            case GAME_DIFF_NORMAL:
                field_36E = 30;
                break;
            case GAME_DIFF_EASY:
                field_36E = 15;
                break;
            default:
                break;
            }
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.2;
            tmp[2] = 5.0;

            addbullet(chrt, NULL, 920, x, y, dir, -1, tmp, 3);
        }
        if ( get_subseq() == 6 )
            field_378 = scene_rand_rngf(100) * 0.1 - 5.0;
        break;
    case 930:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            h_inerc = 14.5;
        if ( get_subseq() == 16 )
            set_vec_speed(addition[0], addition[1]);
        break;
    case 931:
        field_194 = 1;
        set_subseq(addition[2]);
        if ( get_subseq() <= 3 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 5.0;

            addbullet(chrt, this, 931, x, y, dir, 1, tmp, 3);
        }
        if ( get_subseq() == 5 )
        {
            scaleX = 2.0;
            scaleY = 2.0;
        }
        if ( get_subseq() <= 3 )
        {
            chrt->play_sfx( 23);
            scaleX = 50.0;
            field_194 = 0;
            scaleY = 0.1;
        }
        if ( get_subseq() == 7 )
            angY = 70.0;
        break;
    case 932:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
            field_194 = 4;
        if ( get_subseq() == 5 )
        {
            scaleX = 2.5;
            scaleY = 2.5;
            angX = scene_rand_rngf(5) + 70.0;
            angZ = scene_rand_rngf(360);
            c_A = 0;
        }
        break;
    case 933:
        set_subseq(addition[2]);
        if ( get_subseq() <= 6 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
            if ( bul_parent )
            {
                field_37C = bul_parent->x;
                field_380 = bul_parent->y;
            }
        }
        break;
    case 940:
        set_subseq(addition[2]);
        if ( get_subseq() == 5 )
        {
            field_138 = -6.0;
            has_shadow = 1;
            scaleX = 0.1;
            shader_type = 3;
            scaleY = 0.1;
            shader_cR = -2;
            shader_cG = -2;
            shader_cB = -2;
            field_374 = 40;
        }
        break;
    case 941:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            field_378 = 5.0 - scene_rand_rngf(11);
            scaleY = scaleX = scene_rand_rngf(75) * 0.01 + 0.75;
            angZ = scene_rand_rng(360);
        }
        if ( get_subseq() == 1 )
            angZ = addition[0];
        if ( get_subseq() >= 2 && get_subseq() <= 4 )
        {
            field_194 = 1;
            angZ = addition[0];
        }
        if ( get_subseq() == 5 )
        {
            field_194 = 1;
            angZ = addition[0];
            set_vec_speed(addition[0], addition[1]);
        }
        break;
    case 942:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            chrt->play_sfx( 25);

            float tmp[3];
            tmp[0] = scene_rand_rngf(75) * 0.01 + 0.75;
            tmp[1] = 0.15;
            tmp[2] = 1.0;

            scaleY = scaleX = tmp[0];

            addbullet(chrt, NULL, 942, x, y, dir, 1, tmp, 3);

            for (int i = 0; i < 6; i++)
            {
                tmp[0] = scene_rand_rngf(360);
                tmp[1] = scene_rand_rngf(9) + 10.0;
                tmp[2] = 2.0;
                addbullet(chrt, NULL, 942, x, y, dir, 1, tmp, 3);
            }
        }
        if ( get_subseq() == 1 )
        {
            scaleY = scaleX = addition[0];
        }
        if ( get_subseq() == 2 )
        {
            field_378 = 5.0 - scene_rand_rngf(11);
            scaleY = scaleX = scene_rand_rngf(75) * 0.01 + 0.75;
            angZ = scene_rand_rngf(360);
        }
        break;
    case 970:
        set_subseq(addition[2]);
        if ( get_subseq() <= 6 )
        {
            angZ = scene_rand_rngf(360);
            field_378 = scene_rand_rngf(12) - 6.0;
            scaleY = scaleX = scene_rand_rngf(15) * 0.1 + 0.5;
            field_37C = chrt->x + (chrt->get_pframe()->extra1[4] * dir) ;
            field_380 = chrt->y - chrt->get_pframe()->extra1[5];
        }
        break;
    case 980:
        //sub_48C360(); //HACK
        break;
    case 998:
        break;
    case 999:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
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




