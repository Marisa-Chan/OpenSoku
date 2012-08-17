#include "global_types.h"
#include <math.h>
#include "scene.h"
#include "graph.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"

#define VERT_SCALE    2.0
#define SCR_WIDTH     640.0
#define VERT_ZERO_PNT 100.0
#define CHAR_VERT_POS 420.0
#define BKG_VERT_POS  946.0
#define BKG_HOR_PAD   60.0

#define CAM_SPEED     0.3

float lvl_height[BKG_WIDTH];

void init_scene_height()
{
    for(uint32_t i=0; i< BKG_WIDTH; i++)
        lvl_height[i] = 0;
}

void c_scene::set_camera(char_c *p1,char_c *p2)
{
    set_camera(p1->x, p1->y,
               p2->x, p2->y);
}

void c_scene::set_camera(float x1, float y1, float x2, float y2)
{
    float xdist = fabs(x1-x2)+CHAR_PADDING * 2;
    float ydist = fabs(y1-y2);

    float sq = sqrt(ydist*VERT_SCALE*
                    ydist*VERT_SCALE+
                    xdist*xdist);

    float new_scale = 1.0;

    if (sq > 0)
        new_scale = SCR_WIDTH/sq;

    if (new_scale > 1.0)
        new_scale = 1.0;
    if (new_scale < 0.5)
        new_scale = 0.5;

    float xpos = (x1+x2+CHAR_PADDING * 2)/2.0 - (SCR_WIDTH/2.0)/new_scale - CHAR_PADDING;

    if (xpos < 0)
        xpos = 0;

    if (xpos >= (BKG_WIDTH - SCR_WIDTH/new_scale))
        xpos  = (BKG_WIDTH - SCR_WIDTH/new_scale);

    float ypos = (y1+y2)/2.0 - VERT_ZERO_PNT/new_scale;

    if (ypos < 0)
        ypos = 0;

    if (ypos >= CHAR_VERT_POS * (new_scale -0.5)*2.0)
        ypos  = CHAR_VERT_POS * (new_scale -0.5)*2.0;

    cam.x = xpos;
    cam.y = ypos;
    cam.scale = new_scale;

}

void c_scene::apply_camera()
{
    gr_reset_state(1);
    gr_plane_translate(1,0,CHAR_VERT_POS+cam.y);
    gr_plane_scale(1,cam.scale,cam.scale);
    gr_plane_translate(1,-cam.x,0);

    gr_reset_state(2);
    gr_plane_translate(2,0,CHAR_VERT_POS+cam.y);
    gr_plane_scale(2,cam.scale,cam.scale);
    gr_plane_translate(2,-cam.x-BKG_HOR_PAD,-BKG_VERT_POS);
}

void c_scene::upd_camera(float x1, float y1, float x2, float y2)
{
    s_camera tmp = cam;
    set_camera(x1,y1,x2,y2);

    cam.x = tmp.x + (cam.x - tmp.x) * CAM_SPEED;
    cam.y = tmp.y + (cam.y - tmp.y) * CAM_SPEED;
    cam.scale = tmp.scale + (cam.scale - tmp.scale) * CAM_SPEED;

    apply_camera();
}

void c_scene::upd_camera(char_c *p1,char_c *p2)
{
    upd_camera(p1->x, p1->y,
               p2->x, p2->y);
}

c_scene::c_scene(background *bg, char_c *p1, char_c *p2)
{
    bkg = bg;
    chrs[0] = p1;
    chrs[1] = p2;

    chrs[0]->x = 480;
    chrs[0]->y = 0;
    chrs[1]->x = 800;
    chrs[1]->y = 0;

    chrs[0]->dir = 1.0;
    chrs[1]->dir = 1.0;

    chrs[0]->enemy = chrs[1];
    chrs[1]->enemy = chrs[0];

    set_camera(chrs[0],chrs[1]);
    init_scene_height();
}

void c_scene::draw_scene()
{
    upd_camera(chrs[0],chrs[1]);

    bkg->draw();

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->draw();
}

void c_scene::update_char_anims()
{
    for (uint32_t i=0; i < 2; i++)
        chrs[i]->process();
}

void c_scene::players_input()
{
    for (uint32_t i=0; i < 2; i++)
        chrs[i]->input_update();

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->basic_input();
}

float box_col_intersect(float x11, float y11, float x12, float y12,
                        float x21, float y21, float x22, float y22)
{
    float l1,r1,t1,b1;
    if (x11 > x12)
    {
        l1 = x12;
        r1 = x11;
    }
    else
    {
        r1 = x12;
        l1 = x11;
    }
    if (y11 > y12)
    {
        t1 = y12;
        b1 = y11;
    }
    else
    {
        b1 = y12;
        t1 = y11;
    }

    float l2,r2,t2,b2;
    if (x21 > x22)
    {
        l2 = x22;
        r2 = x21;
    }
    else
    {
        r2 = x22;
        l2 = x21;
    }
    if (y21 > y22)
    {
        t2 = y22;
        b2 = y21;
    }
    else
    {
        b2 = y22;
        t2 = y21;
    }

    if ((t1 < b2) && (t2 < b1)) // intersect?
    {
        if ((r2 > l1) && (l2 < r1)) //intersect!
        {

            return  (min(r1,r2)-max(l1,l2))/2.0;
        }
    }
    return 0;
}

void c_scene::players_collisions()
{
    float mm = 0;

    char_frame *p1 = chrs[0]->get_pframe();
    char_frame *p2 = chrs[1]->get_pframe();

    for (uint32_t i=0; i < p1->box_coll.size(); i++)
        for (uint32_t j=0; j < p2->box_coll.size(); j++)
        {
            mm = box_col_intersect(chrs[0]->x + chrs[0]->dir*p1->box_coll[i].x1,
                                   chrs[0]->y + p1->box_coll[i].y1,
                                   chrs[0]->x + chrs[0]->dir*p1->box_coll[i].x2,
                                   chrs[0]->y + p1->box_coll[i].y2,
                                   chrs[1]->x + chrs[1]->dir*p2->box_coll[i].x1,
                                   chrs[1]->y + p2->box_coll[i].y1,
                                   chrs[1]->x + chrs[1]->dir*p2->box_coll[i].x2,
                                   chrs[1]->y + p2->box_coll[i].y2);
            if (mm > 0)
            {
                if (chrs[0]->x > chrs[1]->x)
                {
                    chrs[0]->x += mm;
                    chrs[1]->x -= mm;
                }
                else
                {
                    chrs[0]->x -= mm;
                    chrs[1]->x += mm;
                }
            }
        }
}

void c_scene::xy_pos_check()
{
    for (uint32_t i=0; i < 2; i++)
    {
        char_xy_pos_calculation(chrs[i]);
    }

}


int8_t get_border_near(char_c *chr)
{
    if ( chr->x - 40.0 > 0.0 )
    {
        if ( chr->x + 40.0 < 1280.0 )
            return 0;
        else
            return -1;
    }
    return 1;
}

float getlvl_height(char_c *chr)
{
    if ( chr->x > 0.0 )
    {
        if ( chr->x < BKG_WIDTH )
            return lvl_height[(uint32_t)(chr->x+0.5)];
        else
            return lvl_height[BKG_WIDTH - 1];
    }
    return lvl_height[0];
}

float getlvl_height(char_c *chr, float dx)
{
    float t = chr->x + dx;
    if ( t > 0.0 )
    {
        if ( t < BKG_WIDTH )
            return lvl_height[(uint32_t)(t+0.5)];
        else
            return lvl_height[BKG_WIDTH - 1];
    }
    return lvl_height[0];
}

bool char_on_ground(char_c *chr)
{
    return getlvl_height(chr) >= chr->y;
}


void char_xy_pos_calculation(char_c *chr)
{

    char_c *enemy = chr->enemy;

    if ( !chr->field_196 )
    {
        if ( !enemy->field_4A8 )
        {
            if ( chr->field_571 )
            {
                float v4 = (chr->field_744 + chr->h_inerc + enemy->field_74C) * chr->dir * chr->field_564;
                if ( get_border_near(chr) * v4 >= 0.0 )
                    if ( getlvl_height(chr, v4) == 0 )
                        chr->x += v4;

                if ( chr->x < CHAR_PADDING )
                    chr->x = CHAR_PADDING;
                if ( chr->x > (BKG_WIDTH - CHAR_PADDING) )
                    chr->x = (BKG_WIDTH - CHAR_PADDING);
            }
            else
                chr->x = (enemy->field_74C + chr->h_inerc) * chr->dir * chr->field_564 + chr->x;

            chr->y = chr->field_568 * chr->v_inerc + chr->y;

            if ( chr->field_572 )
                if ( char_on_ground(chr) && chr->field_4C4 == 0 )
                    chr->y = getlvl_height(chr);
        }
    }
}
