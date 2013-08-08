#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "./character_def.h"
#include "bullets.h"
#include "scene.h"
#include "archive.h"
#include "file_read.h"
#include <math.h>

static char_graph *common_pgp = NULL;

void bullets_init_common()
{
    if (!common_pgp)
    {
        common_pgp = new char_graph;
        common_pgp->load_dat("common",0);
    }
}


void addbullet(char_c *chr, c_bullet *bul, int32_t idx, float x, float y, int8_t dir, int8_t order,float *addit, int8_t num)
{
    if (chr && chr->get_seq(idx))
    {
        c_bullet *tmp = chr->new_bullet();
        if (tmp)
        {
            tmp->init(chr,bul,idx,x,y,dir,order,addit,num);
            if (chr)
                chr->get_bullets()->push_back(tmp);
        }
    }
    else if (common_pgp && common_pgp->get_seq(idx))
    {
        c_bullet *tmp = new c_bullet;
        if (tmp)
        {
            tmp->init(chr,bul,idx,x,y,dir,order,addit,num,common_pgp);
            if (chr)
                chr->get_bullets()->push_back(tmp);
        }
    }
}

void updatebullet(char_c *chr)
{
    bullist *lst = chr->get_bullets();
    bullist_iter iter = lst->begin();

    while(iter != lst->end())
    {
        c_bullet *blt = *iter;

        if ( !blt->chrt->time_stop || blt->field_360)
        {
            if (blt->hit_stop)
                blt->hit_stop--;
            else
            {
                blt->func10();
                if (blt->tail)
                    blt->tail->update(blt->x, blt->y);
            }
        }

        if (blt->active)
            iter++;
        else
        {
            delete blt;
            iter = lst->erase(iter);
        }
    }
}

void drawbullet(char_c *chr, int8_t order)
{
    bullist *lst = chr->get_bullets();

    for(bullist_iter i=lst->begin(); i != lst->end(); i++)
        if ((*i)->order == order)
        {
            (*i)->draw();
            if ((*i)->tail)
                (*i)->tail->draw();
        }

}

c_bullet::c_bullet()
{
    field_194 = 0;
    active = true;
    bul_parent = NULL;
    //  parent = NULL;
    //pgp = _pgp;
    tail = NULL;
}

c_bullet::~c_bullet()
{
    if (bul_parent)
        bul_parent->bul_childs.remove(this);


    bullist_iter it = bul_childs.begin();
    while(it != bul_childs.end())
    {
        (*it)->bul_parent = NULL;
        it++;
    }

    if (tail)
        delete tail;
}

void c_bullet::func16()
{

}

void c_bullet::init(char_c *_parent, c_bullet *bul, int32_t idx, float _x, float _y, int8_t _dir, int8_t _order, float *addit, int8_t num, char_graph *_pgp)
{
//    parent = _parent;
    chrt = _parent;
    enemy = chrt->enemy;

    bul_parent = bul;

    if (bul_parent)
    {
        bul_parent->bul_childs.push_back(this);
    }

    if (_pgp)
        pgp = _pgp;
    else if (chrt)
        pgp = chrt->pgp;
    else if (bul_parent)
        pgp = bul_parent->pgp;

    x = _x;
    y = _y;
    dir = _dir;
    order = _order;
    for (int8_t i=0; i< num; i++)
        addition[i] = addit[i];

    set_seq(idx);
}

void c_bullet::set_seq(uint32_t idx)
{
    c_meta::set_seq(idx);
    set_seq_params();
}

void c_bullet::func10()
{
    switch(get_seq())
    {
    case 1002:
        if ( chrt->field_84C > 0 && field_36C == 0)
        {
            if ( c_A >= 235 )
                c_A = 255;
            else
                c_A += 25;
        }
        else
            field_36C = 1;

        if ( field_36C == 1 )
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }
        break;

    case 1006:
        if ( get_subseq() == 1 )
        {
            if ( field_36C == 0)
            {
                if ( field_190 )
                {
                    field_190 = 0;
                    field_194 = 1;
                }
                if ( get_elaps_frames() >= 360 )
                    field_36C = 1;

                x = chrt->x;
                y = chrt->y;
                dir = chrt->dir;
            }
            if ( field_36C == 1 )
            {
                field_194 = 0;
                if (c_A < 15)
                    active = false;
                else
                {
                    c_A -= 15;
                    c_B -= 15;
                    c_G -= 15;
                }
            }
        }
        process();
        break;

    case 1007:
        if ( get_subseq() == 1 )
        {
            if ( field_36C == 0)
            {
                sub_48C4B0(0.0, 2.0, 100.0);
                addition[1] *= 0.95;

                if ( addition[1] <= 1.0 )
                {
                    field_36C = 1;
                    sub_48C4B0(0.0, 180.0, 100.0);
                }
            }
            if ( field_36C == 1 )
            {
                sub_48C4B0(0.0, 1.0, 100.0);
                addition[1] += 0.25;
            }
            if ( get_elaps_frames() % 3 == 0 )
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = scene_rand_rngf(30) * 0.1 + 4.0;
                tmp[2] = 2.0;
                addbullet(chrt,NULL,1007, x + 20 - scene_rand_rngf(40), y + 20 - scene_rand_rngf(40), dir, 1, tmp, 3);
            }
            set_vec_speed(addition[0], addition[1]);

            if ( field_190 == 6 )
            {
                field_394++;
                if ( field_394 < 5 )
                {
                    field_194++;
                    field_190 = 0;
                }
            }
            if ( field_190 != 0 )
            {
                for (int32_t i=0; i< 6; i++)
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(360);
                    tmp[1] = scene_rand_rngf(7) + 4.0;
                    tmp[2] = 3.0;
                    addbullet(chrt,NULL, 1007, x, y, dir, 1, tmp, 3);
                }
                active = false;
                break;
            }
        }
        else
        {
            if ( get_subseq() == 2 )
            {
                v_inerc += 0.5;
                scaleY = scaleX *= 0.98;
                if (c_A < 10)
                {
                    active = false;
                    break;
                }
                else
                    c_A -= 10;
            }
            else if (get_subseq() == 3)
            {
                v_inerc += field_378;
                addition[1] *= 0.97;
                field_378 += 0.25;
                set_vec_speed(addition[0], addition[1]);
                scaleY = scaleX *= 0.98;
                if (c_A < 10)
                {
                    active = false;
                    break;
                }
                else
                    c_A -= 10;
            }
        }
        if (x > 1580 || x < -300 || y > 1280 || y < -300)
            active = false;
        else
        {
            x += dir * h_inerc;
            y += v_inerc;
            process();

            if ( get_subseq() == 1 && (get_elaps_frames() % 4) == 0 )
                scaleY = scaleX = scene_rand_rngf(20) * 0.01 + 0.9;
        }
        break;
    case 1010:
        if ( get_subseq() == 1 )
            scaleY = scaleX += 0.15;
        if (process())
            active = false;
        break;
    case 1016:
        if (get_subseq() == 3)
        {
            angZ += field_378;
            v_inerc -= 0.2;
            h_inerc *= 0.99;
            scaleY = scaleX *= 0.98;

            if ( c_A < 6 )
                active = false;
            else
            {
                c_A -= 6;
                x += dir * h_inerc;
                y += v_inerc;
            }
        }
        else if (get_subseq() == 2)
        {
            if ( field_36C != 0)
            {
                if ( c_A < 10 )
                {
                    active = false;
                    break;
                }
                else
                    c_A -= 10;
            }
            else
            {
                if (c_A > 245)
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 10;
            }
            scaleY = scaleX += 0.005;
            angZ += field_378;
            field_378 *= 0.98;
            addition[1] *= 0.97;
            set_vec_speed(addition[0],addition[1]);
            x += dir * h_inerc;
            y += v_inerc * 0.2;
            if (process())
                active = false;
            break;
        }
        else if (get_subseq() == 1)
        {
            if ( field_36C != 0)
            {
                scaleY = scaleX *= 0.99;
                if (c_A < 7)
                    active = false;
                else
                    c_A -= 7;
            }
            else
            {
                field_378 += 2.0;
                if ( field_378 > 90.0 )
                {
                    field_378 = 90.0;
                    field_194 = 1;
                }

                float dist = fabs(x - enemy->x);
                if ( dist <= 150.0  && enemy->getlvl_height() >= enemy->y && !enemy->char_is_shock() &&
                        !enemy->sub_469710() && !enemy->char_is_block_knock() && enemy->get_seq() >= 6 && enemy->get_seq() <= 299)
                {
                    enemy->field_1A4 = -enemy->h_inerc * 0.75;
                    enemy->field_1A8 = 10.0;
                    enemy->damage_limit = 100;
                    enemy->set_seq(77);
                    enemy->field_4BA = 6000;
                    scene_play_sfx(1);
                    scene_add_effect(this, 2, x, y, dir, 1);
                    field_36E++;
                }

                if ( dist <= 150.0 && chrt->getlvl_height() >= chrt->y && !chrt->char_is_shock() &&
                        !chrt->sub_469710() && !chrt->char_is_block_knock() && chrt->get_seq() >= 6 && chrt->get_seq() <= 299)
                {
                    chrt->field_1A4 = -chrt->h_inerc * 0.75;
                    chrt->field_1A8 = 10.0;
                    chrt->damage_limit = 100;
                    chrt->set_seq(77);
                    chrt->field_4BA = 6000;
                    scene_play_sfx(1);
                    scene_add_effect(this, 2, x, y, dir, 1);
                    field_36E++;
                }

                if ( field_190 == 6 )
                {
                    field_394++;
                    field_194++;
                    field_190 = 0;
                }

                if ( get_elaps_frames() >= 600 || field_190 != 0 || field_36E >= 3 )
                {
                    field_36C = 1;
                    field_194 = 0;
                }
                if ( get_elaps_frames() % 60 == 0)
                {
                    for (int32_t i=0; i<12; i++)
                    {
                        float tmp[3];
                        tmp[0] = scene_rand_rngf(20) + i * 30.0;
                        tmp[1] = scene_rand_rngf(30) * 0.1 + 12.0;
                        tmp[2] = 2.0;
                        if (sin_deg(-tmp[0]) > 0.0)
                            addbullet(chrt, NULL, 1016, x, y, dir, -1, tmp, 3);
                        else
                            addbullet(chrt, NULL, 1016, x, y, dir,  1, tmp, 3);
                    }
                }
                scaleY = scaleX = sin_deg(field_378);
            }
        }

        if (active && process())
            active = false;
        break;
    case 1020:
        switch ( get_subseq() )
        {
        case 1:
            v_inerc -= 0.15;
            if ( field_36C == 0 &&  y - getlvl_height() < 640.0 )
            {
                scene_play_sfx(70);
                field_36C = 1;
            }
            if (getlvl_height() < y + v_inerc || chrt->field_4C4)
            {
                if ( y <= -800.0 )
                    active = false;
            }
            else
            {
                y = getlvl_height();
                next_subseq();
                v_inerc = 0.0;
                float tmp2[3];
                tmp2[0] = 0.0;
                tmp2[1] = 0.0;
                tmp2[2] = 7.0;

                addbullet(chrt, NULL, 1020, 640, y, dir, 1, tmp2, 3);
                for (int32_t i = 0; i< 18; i++)
                {
                    float tmp[3];
                    tmp[0] = scene_rand_rngf(10) + i * 20.0;
                    tmp[1] = scene_rand_rngf(7) + 15;
                    tmp[2] = 8.0;

                    float xx = cos_deg(tmp[0]) * 200.0 + x;
                    float yy = sin_deg(-tmp[0]) * 40.0 + y;
                    if (sin_deg(-tmp[0]) > 0.0)
                        addbullet(chrt, NULL, 1020, xx, yy, dir, -1, tmp, 3);
                    else
                        addbullet(chrt, NULL, 1020, xx, yy, dir, 1, tmp, 3);
                }
                //shake_camera(20.0); //HACK
                scene_play_sfx(71);
            }
            break;
        case 3:
            if ( get_elaps_frames() >= 60 )
                next_subseq();
            break;
        case 5:
            v_inerc -= v_force;
            if ( v_inerc < 0.0 )
            {
                //HACK
                /*sub_465E50(1099);
                a1a[0] = (double)(640 * (signed int)v1->meta.rend_cls.dir) + v1->meta.rend_cls.x_pos;
                field_154->field_E8 = a1a[0];
                field_154->field_EC = 0.0;
                field_154->field_F8 = 40.0;
                field_154->field_FC = 20.0;
                field_154->field_104 = dir;*/
            }
            if ( y <= -600.0 )
                active = false;
            break;
        case 7:
            if ( get_elaps_frames() >= 10 )
                active = false;
            break;
        case 8:
            if ( field_36C )
            {
                if ( c_A < 6u )
                    active = false;
                else
                    c_A -= 6;
            }
            else
            {
                if ( c_A > 245 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 10;
            }

            scaleY = scaleX += 0.005;
            angZ += field_378;
            field_378 *= 0.98;
            addition[1] *= 0.97;
            set_vec_speed(addition[0],addition[1]);
            v_inerc *= 0.2;
            break;
        default:
            break;
        }
        if (active)
        {
            x += h_inerc * dir;
            y += v_inerc;

            if ( process() )
                active = false;

            if (get_elaps_frames() == 0 && get_frame() == 0 && get_frame_time() == 0)
            {
                if (get_subseq() == 5)
                {
                    v_inerc = 10.0;
                    v_force = 0.5;
                }
                else if (get_subseq() == 7)
                    active = false;
            }
        }
        break;

    case 1110:
        if ( get_subseq() == 0 )
        {
            if ( field_36C != 0 )
            {
                scaleX *= 0.98;

                if (c_A < 10)
                    active = false;
                else
                    c_A -= 10;
            }
            else
            {
                if ( field_37C == 0 )
                {
                    if (c_A > 235)
                    {
                        c_A = 255;
                        field_37C = 1.0;
                    }
                    else
                        c_A += 20;
                }
                else
                {
                    c_A = 192 + cos_deg(field_37C) * 64;
                    field_37C += 2.0;
                }

                if ( chrt->field_4CD )
                {
                    x = chrt->x;
                    y = 0.0;
                }
                else
                    field_36C = 1;

                if ( get_elaps_frames() % 20 == 0 )
                {
                    float tmp[3];
                    tmp[0] = 0.0;
                    tmp[1] = 0.0;
                    tmp[2] = 1.0;

                    addbullet(chrt, NULL, 1110, x + 100.0 + scene_rand_rngf(200), y + scene_rand_rngf(200) + 150.0, dir, 1, tmp, 3);
                }
            }
        }
        if ( get_subseq() == 1 )
        {
            angZ += field_378;
            v_inerc -= 0.1;
            scaleY = scaleX *= 0.98;

            if ( field_36C == 0 )
            {
                if ( c_A > 235 )
                {
                    c_A = 255;
                    field_36C = 1;
                }
                else
                    c_A += 20;
            }
            else
            {
                if ( c_A < 8 )
                    active = false;
                else
                    c_A -= 8;
            }
            x += h_inerc * dir;
            y += v_inerc;
        }

        if (active && process())
            active = false;
        break;

    case 1201:
        if ( get_subseq() == 0 )
        {
            if ( field_36C == 0)
            {
                if ( get_frame() != 0 )
                    set_frame(0);
                if ((chrt->max_health - chrt->field_188) / chrt->max_health > 0.33)
                {
                    if ( shader_type )
                        shader_type = 0;
                    field_378 = 0.0;
                }
                else
                {
                    if ( shader_type == 0 )
                        shader_type = 3;
                    shader_cG = 0;
                    shader_cB = 0;
                    shader_cR = 128 - cos_deg(field_378) * 127;
                    field_378 += 8.0;
                }
                if ( chrt->field_882 == 2 )
                {
                    if ( get_frame() != 1 )
                        set_frame(1);

                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 2;

                    addbullet(chrt,NULL, 1201, x,y, 1, 2, tmp, 3);

                    if (chrt->health <= 0)
                        active = false;
                    else
                        field_36C = 1;
                    field_378 = 0.0;

                    break;
                }
                else
                    scaleY = scaleX = 1.0;
            }
            if ( field_36C == 1 )
            {
                if ( get_frame() != 1 )
                    set_frame(1);

                if ( shader_type != 0 )
                    shader_type = 0;

                if ( chrt->field_882 != 2 )
                {
                    field_378 = 0.0;
                    field_36C = 0;
                }

                if ( chrt->field_882 == 2 && chrt->health <= 0 )
                {
                    float tmp[3];
                    tmp[0] = 0;
                    tmp[1] = 0;
                    tmp[2] = 2.0;

                    addbullet(chrt, NULL, 1201, x,y, 1, 2, tmp, 3);
                    active = false;
                    break;
                }
                scaleY = scaleX = 1.0;
            }
        }
        else if (get_subseq() == 2)
        {
            scaleY = scaleX += 0.1;
        }
        else if (get_subseq() == 1)
        {
            if ( field_36C == 0)
            {
                if ( chrt->field_882 != 2 )
                {
                    float v92 = 0;
                    if ( (chrt->max_health - chrt->field_188) / chrt->max_health * 266.0 <= 266.0 )
                    {
                        if ( (chrt->max_health - chrt->field_188) / chrt->max_health * 266.0 >= 0.0 )
                            v92 = (chrt->max_health - chrt->field_188) / chrt->max_health * 266.0;
                        else
                            v92 = 0.0;
                    }
                    else
                    {
                        v92 = 266.0;
                    }
                    float v93 = (v92 - field_37C) * 0.25 + field_37C;
                    field_37C = v93;
                    if ( fabs(v92 - v93) <= 1.0 )
                        field_37C = v92;

                    if ( shader_type == 0 )
                        shader_type = 3;

                    field_378 += 4.0;
                    shader_cB = shader_cG = shader_cR = 64.0 - cos_deg(field_378) * 64.0;
                }
                else
                {
                    if ( chrt->health <= 0 )
                        active = false;
                    field_378 = 0.0;
                    field_36C = 1;
                    break;
                }
            }
            else if ( field_36C == 1 )
            {
                if ( chrt->field_882 == 2 )
                {
                    if ( chrt->health <= 0 )
                    {
                        active = false;
                        break;
                    }
                }
                else
                {
                    field_36C = 0;
                    field_378 = 0.0;
                }

                float v100 = 0;
                if ( (chrt->field_886 - chrt->field_884) / chrt->field_886 * 266.0 <= 266 )
                {
                    if ( (chrt->field_886 - chrt->field_884) / chrt->field_886 * 266.0 >= 0.0 )
                        v100 = (chrt->field_886 - chrt->field_884) / chrt->field_886 * 266.0;
                    else
                        v100 = 0.0;
                }
                else
                    v100 = 266;

                float v93 = (v100 - field_37C) * 0.25 + field_37C;
                field_37C = v93;
                if ( fabs(v100 - v93) <= 1.0 )
                    field_37C = v100;

                if ( shader_type == 0 )
                    shader_type = 3;

                field_378 += 32.0;
                shader_cB = shader_cG = shader_cR = 64.0 - cos_deg(field_378) * 64.0;
            }
        }

        if (process())
            active = false;
        if (get_subseq() == 1)
          sub_438450(0.0, 0.0, field_37C, 8.0);

        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3)
            active = false;
        break;

    case 1202:
        switch ( get_subseq() )
        {
        case 1:
            angZ += 1.0;
            field_378 += 1.0;
            angX = cos_deg(field_378) * field_37C;
            angZ = sin_deg(field_378) * field_37C;
            field_37C = cos_deg(field_378 * 0.5) * 30.0;

            if ( field_36C == 0)
            {
                x = chrt->x;
                if ( x > 1280.0 )
                    x = 1280.0;
                if ( x < 0.0 )
                    x = 0.0;

                y = chrt->y + 100;
                if (y < 100.0)
                    y = 100.0;

                if (chrt->field_86A >= 3)
                {
                    scaleY = scaleX -= 0.05;
                    if (c_A < 25)
                    {
                        scaleY = scaleX = 1.5;
                        c_A = 0;
                        set_subseq(3);
                        break;
                    }
                    else
                        c_A -= 25;
                }
                if (chrt->field_86A == 2)
                {
                    angY = angX = 0.0;
                    c_A = 0;
                    set_subseq(3);
                    break;
                }
                else if (chrt->field_86A == 1)
                {
                    scaleY = scaleX = 1.0;
                    if ( c_A >= 245 )
                        c_A = 255;
                    else
                        c_A += 10;
                }
                else if ( chrt->field_86A == 0 )
                    field_36C = 1;
            }
            if ( field_36C == 1 )
            {
                angZ += 4.0;
                scaleY += 0.1;
                scaleX += 0.1;
                if (c_A < 15)
                    active = false;
                else
                    c_A -= 15;
            }
            break;

        case 2:
            angZ += 2.0;
            angY = angX = 0.0;
            if ( field_36C == 0 )
            {
                angX = 0.0;
                x = chrt->x;
                if ( x > 1280.0 )
                    x = 1280.0;
                if ( x < 0.0 )
                    x = 0.0;

                y = chrt->y + 100;
                if (y < 100.0)
                    y = 100.0;

                if ( chrt->field_86A == 1 )
                {
                    scaleX -= 0.05;
                    if ( scaleX < 1.0 )
                        scaleX = 1.0;
                    scaleY = scaleX;
                    if ( c_A < 25 )
                    {
                        scaleY = scaleX = 1.0;
                        field_378 = 0.0;
                        field_37C = 0.0;
                        c_A = 0;
                        set_subseq(1);
                        break;
                    }
                    else
                        c_A -= 25;
                }
                else if ( chrt->field_86A == 2 )
                {
                    angY = angX = 0.0;
                    c_A = 0;
                    set_subseq(3);
                    break;
                }
                else if ( chrt->field_86A >= 3 )
                {
                    scaleX -= 0.05;
                    if ( scaleX < 1.0 )
                        scaleX = 1.0;
                    scaleY = scaleX;

                    if ( c_A >= 205 )
                        c_A = 255;
                    else
                        c_A += 50;
                }
                if ( chrt->field_86A == 0 )
                    field_36C = 1;
            }

            if ( field_36C == 1 )
            {
                angZ += 4.0;
                scaleY += 0.1;
                scaleX += 0.1;
                if (c_A < 15)
                    active = false;
                else
                    c_A -= 15;
            }
            break;

        case 3:
            angZ += 3.0;
            field_378 += 2.0;

            field_37C = cos_deg(field_378 * 0.5) * 45.0;
            if ( field_36C == 0 )
            {

                x = chrt->x;
                if ( x > 1280.0 )
                    x = 1280.0;
                if ( x < 0.0 )
                    x = 0.0;

                y = chrt->y + 100;
                if (y < 100.0)
                    y = 100.0;

                if ( chrt->field_86A == 1 )
                {
                    scaleY = scaleX = 1.0;
                    if ( c_A < 25 )
                    {
                        scaleY = scaleX = 1.0;
                        c_A = 0;
                        set_subseq(1);
                        break;
                    }
                    else
                        c_A -= 25;
                }
                else if ( chrt->field_86A >= 3 )
                {
                    if ( c_A < 25 )
                    {
                        scaleX = scaleY = 1.0;
                        c_A = 0;
                        set_subseq(2);
                    }
                    else
                        c_A -= 25;
                    break;
                }
                else if ( chrt->field_86A == 2 )
                {
                    c_A = 255;
                    scaleY = scaleX = chrt->field_884 / chrt->field_886 * 0.5 + 1.0;
                }
                else if ( chrt->field_86A == 0 )
                    field_36C = 1;
            }

            if ( field_36C == 1 )
            {
                angZ += 4.0;
                scaleY += 0.1;
                scaleX += 0.1;
                if (c_A < 15)
                    active = false;
                else
                    c_A -= 15;
            }
            break;

        case 4:
            angZ += 1.0;
            field_378 += 1.0;
            if ( field_36C != 0 )
            {
                angZ += 4.0;
                scaleY += 0.1;
                scaleX += 0.1;
                if (c_A < 15)
                    active = false;
                else
                    c_A -= 15;
            }
            else
            {
                if (field_368 == 0)
                    active = false;
                else
                {
                    /*  //HACK
                      this->field_36C = *(_WORD *)(v159 + 876);
                    this->meta.rend_cls.angle_y = *(float *)(v159 + 292);
                    this->meta.rend_cls.angle_x = *(float *)(v159 + 296);
                    this->meta.rend_cls.x_pos = *(float *)(v159 + 236);
                    this->meta.rend_cls.y_pos = *(float *)(v159 + 240);
                    this->meta.rend_cls.scale_x = *(float *)(v159 + 284);
                    this->meta.rend_cls.scale_y = *(float *)(v159 + 288);
                    this->meta.rend_cls.color_A = *(_BYTE *)(v159 + 275);
                    if ( *(_WORD *)(v159 + 318) != 2 )
                    goto LABEL_319;
                    v187 = 5;
                    goto LABEL_318;*/
                }
            }
            break;

        case 5:
            angZ += 2.0;
            angY = angX = 0.0;
            field_378 += 1.0;

            if ( field_36C != 0 )
            {
                angZ += 4.0;
                scaleY += 0.1;
                scaleX += 0.1;
                if (c_A < 15)
                    active = false;
                else
                    c_A -= 15;
            }
            else
            {
                if (field_368 == 0)
                    active = false;
                else
                {
                    //HACK
                    /*  this->field_36C = *(_WORD *)(v161 + 876);
                    this->meta.rend_cls.angle_x = *(float *)(v161 + 292);
                    this->meta.rend_cls.angle_y = *(float *)(v161 + 296);
                    this->meta.rend_cls.x_pos = *(float *)(v161 + 236);
                    this->meta.rend_cls.y_pos = *(float *)(v161 + 240);
                    this->meta.rend_cls.scale_x = *(float *)(v161 + 284);
                    this->meta.rend_cls.scale_y = *(float *)(v161 + 288);
                    this->meta.rend_cls.color_A = *(_BYTE *)(v161 + 275);
                    if ( *(_WORD *)(v161 + 318) == 1 )
                    {
                    v187 = 4;
                    LABEL_318:
                    ((void (__thiscall *)(bullet_class *, signed int))this->meta.vtbl->func3_set_subseq)(this, v187);
                    }
                    LABEL_319:
                    if ( *(_WORD *)(v1->field_368 + 318) == 3 )
                    ((void (__thiscall *)(bullet_class *, signed int))v1->meta.vtbl->func3_set_subseq)(v1, 6);*/
                }
            }
            break;

        case 6:
            angZ += 3.0;
            field_378 += 1.0;

            if ( field_36C != 0 )
            {
                angZ += 4.0;
                scaleY += 0.1;
                scaleX += 0.1;
                if (c_A < 15)
                    active = false;
                else
                    c_A -= 15;
            }
            else
            {
                if (field_368 == 0)
                    active = false;
                else
                {
                    //HACK
                    /*v163 = this->field_368;
                    if ( !v163 )
                    goto LABEL_189;
                    this->field_36C = *(_WORD *)(v163 + 876);
                    v164 = this->char_pointer2?;
                    v1->meta.rend_cls.angle_y = *(float *)(v163 + 292);
                    v1->meta.rend_cls.angle_x = *(float *)(v163 + 296);
                    v1->meta.rend_cls.x_pos = *(float *)(v163 + 236);
                    v1->meta.rend_cls.y_pos = *(float *)(v163 + 240);
                    v165 = (double)v164->field_884 / (double)v164->field_886 + 1.0;
                    v1->meta.rend_cls.scale_x = v165;
                    v1->meta.rend_cls.scale_y = v165;
                    v1->meta.rend_cls.color_A = *(_BYTE *)(v163 + 275);
                    if ( *(_WORD *)(v163 + 318) == 2 )
                    ((void (__thiscall *)(bullet_class *, signed int))v1->meta.vtbl->func3_set_subseq)(v1, 5);
                    if ( *(_WORD *)(v1->field_368 + 318) == 1 )
                    ((void (__thiscall *)(_DWORD, signed int))v1->meta.vtbl->func3_set_subseq)(v1, 4);*/
                }
            }
            break;
        default:
            break;
        }
        if (active && process())
            active = false;
        break;

    case 1203:
        switch ( get_subseq() )
        {
        case 0:
            /*if ( battle_manager->field_494 ) //HACK
              active = false;*/
            if ( field_36C == 0 )
            {
                if ( chrt->field_888 <= -1 )
                    active = false;
                else if ( chrt->field_888 > 9 )
                {
                    if ( shader_type != 0 )
                        shader_type = 0;
                    field_378 = 0.0;
                    scaleY = scaleX = 1.0;
                }
                else
                {
                    if ( shader_type == 0)
                        shader_type = 3;

                    shader_cG = 0;
                    shader_cB = 0;
                    shader_cR = 128.0 - cos_deg(field_378) * 127.0;
                    field_378 += 8.0;
                    scaleY = scaleX = 1.0;

                    if ( chrt->field_888 <= 5 )
                        field_378 += 8.0;
                }
            }
            break;
        case 1:
            /*if ( battle_manager->field_494 ) //HACK
              active = false;*/
            if ( chrt->field_888 <= 9 )
            {
                set_subseq(2);
                c_A = 0;
            }
            if ( chrt->field_888 >= 0 )
                set_frame(chrt->field_888 / 10);
            else
                active = false;
            break;
        case 2:
            /*if ( battle_manager->field_494 ) //HACK
            active = false;*/
            if ( chrt->field_888 <= 9 )
                c_A = 0;
            if ( chrt->field_888 >= 0 )
                set_frame(chrt->field_888 / 10);
            else
                active = false;
            break;
        case 3:
            /*if ( battle_manager->field_494 ) //HACK
              active = false;*/
            if ( chrt->field_888 <= 9 )
            {
                set_subseq(4);
                x -= 17;
            }

            if ( chrt->field_888 >= 0 )
                set_frame(chrt->field_888 % 10);
            break;
        case 4:
            /*if ( battle_manager->field_494 ) //HACK
            active = false;*/
            if ( chrt->field_888 <= 9 )
            {
                set_subseq(4);
                x -= 17;
            }

            if ( chrt->field_888 >= 0 )
                set_frame(chrt->field_888 % 10);
            break;
        case 5:
            if ( get_elaps_frames() >= 120 )
            {
                if (c_A < 5)
                    active = false;
                else
                    c_A -= 5;
            }
            if (process())
                active = false;
            break;
        case 6:
            scaleY = scaleX += field_378;
            field_378 *= 0.92;

            if ( c_A < 10 )
                active = false;
            else
                c_A -= 10;
            break;
        default:
            break;
        }
        break;
    case 1250:
    case 1251:
        if ( field_36C == 0 )
        {
            if ( c_A > 255 - addition[0] )
            {
                c_A = 255;
                field_36C = 1;
            }
            else
                c_A += addition[0];
        }
        if ( field_36C == 1 )
        {
            if ( addition[1] != 0.0)
            {
                addition[1] -= 1.0;
                if ( addition[1] <= 0.0 )
                    field_36C = 2;
            }
        }
        if ( field_36C == 2 )
        {
            if ( c_A < addition[2] )
                active = false;
            else
                c_A -= addition[2];
        }
        break;
    case 1260:
        angY += 4.0;
        scaleY = scaleX += 0.01;
        if ( field_36C == 0 )
        {
            if ( c_A > 245 )
            {
                c_A = 255;
                field_36C = 1;
            }
            else
                c_A += 10;
        }
        else
        {
            if ( c_A < 10 )
                active = false;
            else
                c_A -= 10;
        }
        break;
    default:
        break;
    }
}

void c_bullet::set_seq_params()
{
    field_378 = 0.0;
    field_37C = 0.0;
    field_380 = 0.0;
    field_384 = 0.0;
    field_388 = 0.0;
    field_36C = 0;
    field_36E = 0;
    field_198 = 1.0;
    field_370 = 0;
    scaleY = scaleX = 1.0;
    field_372 = 0;
    field_374 = 0;
    field_1A2 = 0;
    field_194 = 0;
    field_190 = 0;

    switch ( get_seq() )
    {
    case 1002:
        set_subseq(addition[2]);
        field_360 = 1;
        c_A = 0;
        break;
    case 1006:
        set_subseq(addition[2]);
        if (get_subseq() == 1)
            field_194 = 1;
        break;
    case 1007:
        set_subseq(addition[2]);
        if ( get_subseq() == 1 )
        {
            angZ = scene_rand_rngf(360);
            field_194 = 1;
            scaleY = scaleX = scene_rand_rngf(20) * 0.01 + 0.9;
        }
        else if ( get_subseq() == 2 )
        {
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        }
        else if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        }
        break;
    case 1010:
        set_subseq(addition[2]);
        break;
    case 1016:
        set_subseq(addition[2]);
        if ( get_subseq() == 1 )
        {
            field_36C = 0;
            scaleY = scaleX = 0.0;
            for(int8_t i = 0; i < 12; i++)
            {
                float tmp[3];
                tmp[0] = -scene_rand_rngf(180);
                tmp[1] = scene_rand_rngf(75) * 0.1 + 13;
                tmp[2] = 3;

                addbullet(chrt, NULL, 1016, x, y, dir, 1, tmp, 3);
            }
        }
        else if ( get_subseq() == 2 )
        {
            c_A = 0;
            field_378 = scene_rand_rngf(9) - 4.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        }
        else if ( get_subseq() == 3 )
        {
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
            set_vec_speed(addition[0], addition[1]);
        }
        break;
    case 1020:
        set_subseq(addition[2]);
        if (get_subseq() == 7)
            field_194 = 1;
        else if (get_subseq() == 8)
        {
            field_378 = scene_rand_rngf(9) - 4.0;
            angZ = scene_rand_rngf(360);
            scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        }
        break;
    case 1110:
        set_subseq(addition[2]);
        if ( get_subseq() == 0 )
        {
            c_A = 0;
            field_36C = 0;
        }
        else if ( get_subseq() == 1 )
        {
            c_A = 0;
            field_378 = scene_rand_rngf(30) * 0.1 - 1.5;
            scaleX = scene_rand_rngf(10) * 0.1 + 0.5;
            scaleY = scene_rand_rngf(10) * 0.1 + 0.5;
        }
        break;
    case 1201:
        set_subseq(addition[2]);
        field_360 = 1;
        //field_134 = 1; //HACK
        if ( get_subseq() == 0 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 1.0;
            addbullet(chrt, NULL, 1201, x, y, 1, 2, tmp, 3);
        }
        else if ( get_subseq() == 2 )
        {
            char_frame *frm = get_pframe();
            x_off = frm->extra1[4];
            y_off = frm->extra1[5];
        }
        break;
    case 1202:
        set_subseq(addition[2]);
        field_360 = 1;
        if ( get_subseq() == 1 )
        {
            float tmp[3];
            tmp[0] = 0.0;
            tmp[1] = 0.0;
            tmp[2] = 4.0;

            addbullet(chrt, this, 1202, x, y, 1, 2, tmp, 3);
            c_A = 0;
        }
        break;
    case 1203:
        set_subseq(addition[2]);
        field_360 = 1;
        //field_134 = 1; //HACK
        if (chrt->health > 0)
        {
            if (get_subseq() == 0)
            {
                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 1.0;
                addbullet(chrt, NULL, 1203, x, y + 10.0, 1, 3, tmp, 3);

                tmp[2] = 3.0;
                addbullet(chrt, NULL, 1203, x, y + 10.0, 1, 3, tmp, 3);
            }
            else if (get_subseq() == 1)
            {
                if (chrt->field_888 <= 10)
                    set_subseq(2);
                if (chrt->field_888 >= 0)
                    set_frame(chrt->field_888 / 10);
            }
            else if ( get_subseq() == 3 )
            {
                if ( chrt->field_888 <= 10 )
                {
                    set_subseq(4);
                    x -= 17;
                }
                if (chrt->field_888 >= 0)
                    set_frame(chrt->field_888 % 10);
            }
            else if ( get_subseq() == 6 )
            {
                scaleY = scaleX = 0.5;
                field_378 = 0.25;
            }
        }
        else
            active = false;
        break;
    case 1250:
    case 1251:
        if ( addition[3] != 0)
            set_subseq(addition[3]);
        //field_134 = 1; //HACK
        field_360 = 1;
        c_A = 0;
        break;
    case 1260:
        c_A = 0;
        scaleY = scaleX = scene_rand_rngf(50) * 0.01 + 0.75;
        angY = scene_rand_rngf(360);
        field_360 = 1;
        break;
    default:
        break;
    }
}

void c_bullet::draw_shadow(shd_trans *trans, gr_shader *shader)
{
    float rx,ry,rz;
    euler_mult(0,0,-angZ,trans->ax,trans->ay,trans->az,rx,ry,rz);

    if (trans->sx < 0)
        sprite.setRotate(rx,ry,-rz*dir);
    else
        sprite.setRotate(rx,ry,rz*dir);

    sprite.setScale(trans->sx*dir,trans->sy);
    sprite.setXY(trans->x,trans->y);
    sprite.setOrigin(-x_off ,-y_off);
    sprite.setColor(trans->r,trans->g,trans->b,trans->a);
    sprite.draw(PLANE_SCENE,shader);
}


void c_bullet::draw(gr_shader *shader)
{
    if (active)
    {
        sprite.setXY(x,y);
        sprite.setColor(c_R,c_G,c_B,c_A);

        if (scaleX < 0)
            sprite.setRotate(angX,-angY,-angZ * dir);
        else
            sprite.setRotate(angX,-angY,angZ * dir);

        if (scale_real)
            sprite.setAScale(dir*rs_w*scaleX,rs_h*scaleY);
        else
            sprite.setScale(dir*scaleX,scaleY);

        // scale_real = false;

        sprite.draw(PLANE_SCENE,shader);

//        for (int32_t i = 0; i<5; i++)
            //if (atk_area_2o[i])
        /*{
            frame_box *bx = &atk_area_2o[i];
            gr_draw_box(bx->x1,
                        bx->y1,
                        bx->x2-bx->x1,
                        bx->y2-bx->y1,
                        255,0,0,60,1);
        }*/
        /*
        char_frame *pf = sprite.get_pframe();

        if (pf->box_atk.size() > 0)
        {
            for (uint32_t i=0; i<pf->box_atk.size(); i++)
            {
                gr_draw_box(x+pf->box_atk[i].x1,
                            -y+pf->box_atk[i].y1,
                            pf->box_atk[i].x2-pf->box_atk[i].x1,
                            pf->box_atk[i].y2-pf->box_atk[i].y1,
                            255,0,0,128,1);
            }
        }*/
        //gr_draw_box(x,-y,255,0,0,1);
    }
}

bool c_bullet::sub_48C640(int32_t p)
{
    if ( field_190 == 8 )
    {
        field_396++;
        if ( p <= 0 || field_396 < p )
        {
            field_194++;
            field_190 = 0;
            return false;
        }
    }
    else if (field_190 == 4)
        field_194 = 0;
    else
        return false;

    return true;
}

bool c_bullet::sub_48C5F0(int32_t a2)
{
    if ( field_190 == 6 )
    {
        field_394++;
        if (a2 > 0 && field_394 >= a2)
            return true;

        field_194++;
        field_190 = 0;
    }
    return false;
}

bool c_bullet::sub_48C6A0(int32_t p1, int32_t p2, int32_t p3)
{
    if (p1 == 0 && (chrt->get_seq() <= 49 || chrt->get_seq() >= 150))
        return false;
    else if (p1 != 0 )
        if (p1 != 1 || chrt->get_seq() <= 70 || chrt->get_seq() >= 150)
            return false;

    for (int32_t i=0; i < p2; i++)
    {
        scene_add_effect(chrt,200,x,y,dir,1);
    }

    for (int32_t i=0; i < p3; i++)
    {
        scene_add_effect(chrt,201,x,y,dir,1);
    }

    return true;
}

void c_bullet::sub_48C4B0(float p1, float p2, float p3)
{
    c_meta *enemy = chrt->enemy;

    float tmp = p1 - atan2(enemy->getY() + p3 - y, (enemy->getX() - x) * dir) * 180.0/3.1415926;
    int angl = (int)(tmp - addition[0]) % 360;

    if (angl > 180)
        angl -= 360;
    else if (angl < -180)
        angl += 360;

    if (p2 < abs(angl))
    {
        if (angl > 0)
            addition[0] += p2;
        else if (angl < 0)
            addition[0] -= p2;
    }
    else
        addition[0] = tmp;

}

void c_bullet::sub_438450(int32_t /*x*/, int32_t /*y*/, int32_t w, int32_t h)
{
    set_real_size(w,h);
}

void c_bullet::tail_add(int32_t idx, float width, int32_t segments, int32_t seg_subd, gr_blend blending)
{
    seq * sq = pgp->get_seq(idx);
    if (sq)
    {
        char_frame *frm = sq->subseqs[0].frames[0];
        tail = new c_tail(frm->img, 255,255,255,255,width,segments,seg_subd,blending);
    }
}

void c_bullet::tail_alpha(uint8_t a)
{
    if (tail)
        tail->set_alpha(a);
}


void bul_follow_char(c_bullet *bul, int32_t h_inerc, int32_t v_inerc)
{
    char_c *chr = bul->chrt;
    bul->dir = chr->dir;
    bul->x = chr->x + chr->dir * (chr->h_inerc + h_inerc);
    bul->y = chr->y + chr->v_inerc + v_inerc;
}
