#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "./character_def.h"
#include "bullets.h"
#include "scene.h"
#include "archive.h"
#include "file_read.h"
#include <math.h>


bul_vec bullst;

void addbullet(char_c *chr, c_bullet *bul, int32_t idx, float x, float y, int8_t dir, int8_t order,float *addit, int8_t num)
{
    seq *sq = chr->get_seq(idx);
    if (sq)
    {
        c_bullet *tmp = chr->new_bullet();
        if (tmp)
        {
            bullst.push_back(tmp);
            tmp->init(chr,bul,sq,x,y,dir,order,addit,num);
        }
    }
}

void updatebullet()
{
    for(int32_t i=bullst.size()-1; i>=0; i--)
        if (bullst[i]->active)
            bullst[i]->func10();
        else
        {
            delete bullst[i];
            bullst.erase(bullst.begin() + i);
        }
}

void drawbullet(int8_t order)
{
    for(uint32_t i=0; i<bullst.size(); i++)
        if (bullst[i]->order == order)
            bullst[i]->draw(1);
}

bul_vec *getbulllist()
{
    return &bullst;
}


c_bullet::c_bullet()
{
    field_194 = 0;
    active = true;
    bul_parent = NULL;
    parent = NULL;
    //pgp = _pgp;
}

c_bullet::~c_bullet()
{

}

void c_bullet::init(char_c *_parent, c_bullet *bul, seq *sq, float _x, float _y, int8_t _dir, int8_t _order, float *addit, int8_t num)
{
    parent = _parent;
    chrt = parent;
    enemy = chrt->enemy;

    bul_parent = bul;

    if (parent)
        pgp = parent->pgp;
    else if (bul_parent)
        pgp = bul_parent->pgp;

    sprite.set_seq(sq);
    x = _x;
    y = _y;
    dir = _dir;
    order = _order;
    for (int8_t i=0; i< num; i++)
        addition[i] = addit[i];
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


        sprite.setRotate(angX,angY,angZ);
        if (scale_real)
            sprite.setAScale(dir*rs_w*scaleX,rs_h*scaleY);
        else
            sprite.setScale(dir*scaleX,scaleY);

        // scale_real = false;

        sprite.draw(plane);

            for (int32_t i = 0; i<5; i++)
    //if (atk_area_2o[i])
    {
        frame_box *bx = &atk_area_2o[i];
        gr_draw_box(bx->x1,
                        bx->y1,
                        bx->x2-bx->x1,
                        bx->y2-bx->y1,
                        255,0,0,60,1);
    }
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
    if (p1 == 0 && (parent->get_seq() <= 49 || parent->get_seq() >= 150))
        return false;
    else if (p1 != 1 || parent->get_seq() <= 70 || parent->get_seq() >= 150)
        return false;

    for (int32_t i=0; i < p2; i++)
    {
        scene_add_effect(parent,200,x,y,dir,1);
    }

    for (int32_t i=0; i < p3; i++)
    {
        scene_add_effect(parent,201,x,y,dir,1);
    }

    return true;
}

void c_bullet::sub_48C4B0(float p1, float p2, float p3)
{
    c_meta *enemy = parent->enemy;

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
