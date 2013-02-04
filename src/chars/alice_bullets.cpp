#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "alice_bullets.h"
#include <math.h>


bool sub_5269B0(c_bullet *bul)
{
    bul->field_380 = -atan2_deg(bul->chrt->y + 100 - bul->y, bul->chrt->x - bul->x);
    bul->field_378 += 2;
    if (bul->field_378 > 20)
        bul->field_378 = 20.0;

    bul->set_vec_speed(bul->field_380, bul->field_378);

    if (bul->x - bul->chrt->x > 0)
        bul->dir = -1;
    else if (bul->x - bul->chrt->x < 0)
        bul->dir = 1;

    if (fabs (bul->x - bul->chrt->x) >= 20 || fabs(bul->chrt->y + 100 - bul->y) >= 20.0)
        return false;

    bul->active = false;
    return true;
}

bool sub_526870(c_bullet *bul, uint16_t subseq)
{
    c_meta * par = bul->chrt;
    c_bullet * parb = bul->bul_parent;

    bul->x = par->x;
    bul->y = par->y + 100;

    if ( bul->bul_parent )
    {
        if (bul->dir == 1)
            bul->angZ = -atan2_deg(parb->y - (par->y + 100), parb->x - bul->x);
        else
            bul->angZ = atan2_deg(parb->y - (par->y + 100), parb->x - bul->x) + 180;

        bul->field_378 = (parb->x - bul->x) * (parb->x - bul->x);
        bul->field_37C = (parb->y - bul->y) * (parb->y - bul->y);
        bul->field_380 = sqrt(bul->field_378 + bul->field_37C);
        bul->scaleX = bul->field_380 * 0.004;

        if (parb->get_subseq() == subseq)
        {
            bul->active = false;
            return true;
        }
    }
    else
    {
        bul->active = false;
        return true;
    }
    return false;
}




void alice_bullets::func10()
{
    switch(sprite.get_seq_id())
    {
    case 803:
    {
        if (char_is_shock(chrt))
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
                tmp[0] = scene_rand_rng(60) - 30;
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
            if ( sub_5269B0(this) )
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
            if ( !sub_526870(this, 5) )
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
    default:
        if (sprite.process())
            active = false;
    }
}

void alice_bullets::set_seq_params()
{
    switch(sprite.get_seq_id())
    {
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
    default:
        break;
    }
}




