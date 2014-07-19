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
        scaleX = field_380 * 0.004;

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
            if ( get_elaps_frames() >= 0 )
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
            if ( get_elaps_frames() >= 0 )
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
                if ( get_elaps_frames() >= 0 )
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
        if ( get_subseq() != 4 )
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
    default:
        if (process())
            active = false;
    }
}

void alice_bullets::set_seq_params()
{
    set_subseq(addition[2]);
    switch(get_seq())
    {
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
            scaleX = field_380 * 0.004;
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
            scaleX = field_380 * 0.004;
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
    default:
        break;
    }
}




