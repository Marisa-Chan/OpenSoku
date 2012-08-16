#include "global_types.h"
#include <math.h>
#include "scene.h"
#include "graph.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"


#define CHAR_PADDING  40
#define VERT_SCALE    2.0
#define SCR_WIDTH     640.0
#define BKG_WIDTH     1280.0
#define VERT_ZERO_PNT 100.0
#define CHAR_VERT_POS 420.0
#define BKG_VERT_POS  946.0
#define BKG_HOR_PAD   60.0

#define CAM_SPEED     0.3

void c_scene::set_camera(char_c *p1,char_c *p2)
{
    set_camera(p1->getX(), p1->getY(),
              p2->getX(), p2->getY());
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
    upd_camera(p1->getX(), p1->getY(),
               p2->getX(), p2->getY());
}

c_scene::c_scene(background *bg, char_c *p1, char_c *p2)
{
    bkg = bg;
    chrs[0] = p1;
    chrs[1] = p2;

    chrs[0]->setXY(480,0);
    chrs[1]->setXY(800,0);

    chrs[0]->setDir( 1.0);
    chrs[1]->setDir(-1.0);

    set_camera(chrs[0],chrs[1]);
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
            mm = box_col_intersect(chrs[0]->getX() + chrs[0]->getDir()*p1->box_coll[i].x1,
                                   chrs[0]->getY() + p1->box_coll[i].y1,
                                   chrs[0]->getX() + chrs[0]->getDir()*p1->box_coll[i].x2,
                                   chrs[0]->getY() + p1->box_coll[i].y2,
                                   chrs[1]->getX() + chrs[1]->getDir()*p2->box_coll[i].x1,
                                   chrs[1]->getY() + p2->box_coll[i].y1,
                                   chrs[1]->getX() + chrs[1]->getDir()*p2->box_coll[i].x2,
                                   chrs[1]->getY() + p2->box_coll[i].y2);
            if (mm > 0)
            {
                if (chrs[0]->getX() > chrs[1]->getX())
                {
                    chrs[0]->mvX(mm);
                    chrs[1]->mvX(-mm);
                }
                else
                {
                    chrs[0]->mvX(-mm);
                    chrs[1]->mvX(mm);
                }
            }
        }
}

void c_scene::xy_pos_check()
{
    for (uint32_t i=0; i < 2; i++)
    {
        if (chrs[i]->getX() < 40.0)
            chrs[i]->setX(40.0);
        if (chrs[i]->getX() > 1240.0)
            chrs[i]->setX(1240.0);
    }

}
