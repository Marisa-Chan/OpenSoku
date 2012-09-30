#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "./character_def.h"
#include "bullets.h"
#include "scene.h"
#include "archive.h"
#include "file_read.h"
#include <math.h>


vector<c_bullet *> bullst;

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



c_bullet::c_bullet()
{
    field_194 = 0;
    active = true;
    parent = NULL;
    bul_parent = NULL;
}

c_bullet::~c_bullet()
{

}

void c_bullet::init(char_c *_parent, c_bullet *bul, seq *sq, float _x, float _y, int8_t _dir, int8_t _order, float *addit, int8_t num)
{
    parent = _parent;
    bul_parent = bul;
    viz.set_seq(sq);
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
        viz.setXY(x,y);
        viz.setColor(c_R,c_G,c_B,c_A);

        if (angZ < -90 || angZ > 90)
        {
            viz.setRotate(180-angZ);
            if (scale_real)
                viz.setAScale(-dir*rs_w*scaleX,rs_h*scaleY);
            else
                viz.setScale(-dir*scaleX,scaleY);
        }
        else
        {
            viz.setRotate(angZ);
            if (scale_real)
                viz.setAScale(dir*rs_w*scaleX,rs_h*scaleY);
            else
                viz.setScale(dir*scaleX,scaleY);
        }

       // scale_real = false;

        viz.draw(plane);

        /*char_frame *pf = viz.get_pframe();

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
