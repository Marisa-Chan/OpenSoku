#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "./character_def.h"
#include "bullets.h"
#include "scene.h"
#include "archive.h"
#include "file_read.h"
#include <math.h>


void addbullet(char_c *chr, c_bullet *bul, int32_t idx, float x, float y, int8_t dir, int8_t order,float *addit, int8_t num)
{
    if (chr->get_seq(idx))
    {
        c_bullet *tmp = chr->new_bullet();
        if (tmp)
        {
            tmp->init(chr,bul,idx,x,y,dir,order,addit,num);
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
                /*if (blt->field_354)
                  sub_4335A0(blt->field_354);*/ //HACK
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
            (*i)->draw(1);
}

c_bullet::c_bullet()
{
    field_194 = 0;
    active = true;
    bul_parent = NULL;
    //  parent = NULL;
    //pgp = _pgp;
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
}

void c_bullet::init(char_c *_parent, c_bullet *bul, int32_t idx, float _x, float _y, int8_t _dir, int8_t _order, float *addit, int8_t num)
{
//    parent = _parent;
    chrt = _parent;
    enemy = chrt->enemy;

    bul_parent = bul;

    if (bul_parent)
    {
        bul_parent->bul_childs.push_back(this);
    }

    if (chrt)
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

}

void c_bullet::set_seq_params()
{

}

void c_bullet::draw(int8_t plane)
{
    if (active)
    {
        sprite.setXY(x,y);
        sprite.setColor(c_R,c_G,c_B,c_A);

        if (scaleX < 0)
            sprite.setRotate(angX,angY,-angZ * dir);
        else
            sprite.setRotate(angX,angY,angZ * dir);

        if (scale_real)
            sprite.setAScale(dir*rs_w*scaleX,rs_h*scaleY);
        else
            sprite.setScale(dir*scaleX,scaleY);

        // scale_real = false;

        sprite.draw(plane);

        /*for (int32_t i = 0; i<5; i++)
            //if (atk_area_2o[i])
        {
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

bool c_bullet::sub_48C6A0(int32_t p1, int32_t p2, int32_t p3)
{
    if (p1 == 0 && (chrt->get_seq() <= 49 || chrt->get_seq() >= 150))
        return false;
    else if (p1 != 1 || chrt->get_seq() <= 70 || chrt->get_seq() >= 150)
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

void bul_follow_char(c_bullet *bul, int32_t h_inerc, int32_t v_inerc)
{
    char_c *chr = bul->chrt;
    bul->dir = chr->dir;
    bul->x = chr->x + chr->dir * (chr->h_inerc + h_inerc);
    bul->y = chr->y + chr->v_inerc + v_inerc;
}
