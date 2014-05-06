#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
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




