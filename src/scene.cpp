#include "global_types.h"
#include <math.h>
#include "scene.h"
#include "graph.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"
#include "archive.h"
#include "file_read.h"
#include "mt.h"

#define VERT_SCALE    2.0
#define SCR_WIDTH     640.0
#define VERT_ZERO_PNT 100.0
#define CHAR_VERT_POS 420.0
#define BKG_VERT_POS  946.0
#define BKG_HOR_PAD   60.0

#define CAM_SPEED     0.3

#define MAX_GLB_SFX     0x100

c_scene_sp img_sp;

static sfxc *snds[MAX_GLB_SFX];

float lvl_height[BKG_WIDTH];

mtwist randomm;

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
    float ydist = fabs(y1-y2)*VERT_SCALE;

    float sq = sqrt(ydist*ydist+
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
    chrs[1]->dir = -1.0;

    chrs[0]->enemy = chrs[1];
    chrs[1]->enemy = chrs[0];

    chrs[0]->player_index = 0;
    chrs[1]->player_index = 1;

    set_camera(chrs[0],chrs[1]);
    init_scene_height();

    img_sp.load_dat();
    randomm.set_seed(time(NULL));
}

void c_scene::draw_scene()
{
    upd_camera(chrs[0],chrs[1]);

    bkg->draw();

    img_sp.draw(-1);

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->draw();

    img_sp.draw(1);

}

void c_scene::update_char_anims()
{
   // for (uint32_t i=0; i < 2; i++)
      //  chrs[i]->process(true);
}

void c_scene::players_input()
{
    for (uint32_t i=0; i < 2; i++)
        chrs[i]->input_update();

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->check_seq_input();
}

//Borders:
// 0 - center
//-1 - right border
// 1 - left border
s_border get_border_near(char_c *chr)
{
    if ( chr->x - 40.0 > 0.0 )
    {
        if ( chr->x + 40.0 < 1280.0 )
            return BORD_CENT;
        else
            return BORD_RIGHT;
    }
    return BORD_LEFT;
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

bool char_on_ground_flag(char_c *chr)
{
    return getlvl_height(chr) >= chr->y && chr->field_4C4 == 0;
}

bool char_on_ground_down(char_c *chr)
{
    return getlvl_height(chr) >= chr->y &&
            chr->v_inerc < 0 /*&&
            !chr->field_4C4*/;
}


void char_xy_pos_calculation(char_c *chr)
{

    char_c *enemy = chr->enemy;

    if ( !chr->hit_stop )
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
                chr->x += (enemy->field_74C + chr->h_inerc) * chr->dir * chr->field_564;

            chr->y = chr->field_568 * chr->v_inerc + chr->y;

            if ( chr->field_572 )
                if ( char_on_ground(chr) && chr->field_4C4 == 0 )
                    chr->y = getlvl_height(chr);
        }
    }
}

void c_scene::func16()
{

}

void c_scene::func12()
{

}

void scene_subfunc1(c_scene *scn)
{
    for (uint32_t i=0; i < 2; i++)
        scn->chrs[i]->func16();

    //for (uint32_t i=0; i < 2; i++)
    //scn->chrs[i]->smclass2->func3();

    for (uint32_t i=0; i < 2; i++)
        scn->chrs[i]->func10();

    for (uint32_t i=0; i < 2; i++)
    {
        if ( !scn->chrs[i]->hit_stop )
        {
            if ( !scn->chrs[i]->enemy->field_4A8 )
            {
                if ( char_idle_or_move(scn->chrs[i]) )
                {
                    scn->chrs[i]->func18();
                    if ( !scn->chrs[i]->field_4C0 )
                        scn->chrs[i]->field_4BE = 0;
                }
                /*if (char_is_shock(scn->chrs[i]))
                    if ( scn->chrs[i]->y > 0.0 )
                        sub_462FF0(scn->chrs[i]);*/
            }
            if ( scn->chrs[i]->get_seq() < 300 )
            {
                //if ( v1->some_input_var <= 6 )
                //zero_input_charclass_ispressed_vars(v1);
            }
            scn->chrs[i]->func20();
        }
    }

    //for (uint32_t i=0; i < 2; i++)
    //scn->chrs[i]->smclass2->func4();

}


void scene_subfunc2(c_scene *scn)
{

}



void box_coll_get(char_c *chr, box_box *box)
{
    if (chr->dir == 1)
    {
        box->x1 = chr->x + chr->get_pframe()->box_coll[0].x1;
        box->x2 = chr->x + chr->get_pframe()->box_coll[0].x2;
    }
    else
    {
        box->x1 = chr->x - chr->get_pframe()->box_coll[0].x2;
        box->x2 = chr->x - chr->get_pframe()->box_coll[0].x1;
    }
    box->y1 = chr->get_pframe()->box_coll[0].y1 - chr->y;
    box->y2 = chr->get_pframe()->box_coll[0].y2 - chr->y;

}

bool scene_collid(c_scene *scn, box_box *b1, box_box *b2)
{
    if ((b2->x1 - b1->x2) >= 0 ||
            (b1->x1 - b2->x2) >= 0 ||
            (b2->y1 - b1->y2) >= 0 ||
            (b1->y1 - b2->y2) >= 0)
    {
        return false;
    }
    else
    {
        //sub_4790B0(this, a2, a3);
        return true;
    }
}

//Previous frame character near border
// -1 - no char, 0 - player 1, 1 - player 2
int8_t bdr_r_char = -1;
int8_t bdr_l_char = -1;

void scene_check_collisions(c_scene *scn)
{
    char_c *p1 = scn->chrs[0];
    char_c *p2 = scn->chrs[1];

    p1->field_744 = 0.0;
    p2->field_744 = 0.0;

    if ( !p1->get_pframe()->box_coll.size() || !p2->get_pframe()->box_coll.size() )
        return;

    //Detecting who firstly take border

    if      ( bdr_r_char == 1 && get_border_near(p2) != BORD_RIGHT )
        bdr_r_char = -1;
    else if ( bdr_r_char == 0 && get_border_near(p1) != BORD_RIGHT )
        bdr_r_char = -1;

    if      ( bdr_l_char == 1 && get_border_near(p2) != BORD_LEFT )
        bdr_l_char = -1;
    else if ( bdr_l_char == 0 && get_border_near(p1) != BORD_LEFT )
        bdr_l_char = -1;

    if      (get_border_near(p1) == BORD_LEFT  && bdr_l_char == -1)
        bdr_l_char = 0;
    else if (get_border_near(p1) == BORD_RIGHT && bdr_r_char == -1)
        bdr_r_char = 0;

    if      (get_border_near(p2) == BORD_LEFT  && bdr_l_char == -1)
        bdr_l_char = 1;
    else if (get_border_near(p2) == BORD_RIGHT && bdr_r_char == -1)
        bdr_r_char = 1;

    //now we finally know it.

    box_box p1_box;
    box_box p2_box;

    box_coll_get(p1, &p1_box);
    box_coll_get(p2, &p2_box);

    if ( !scene_collid(scn, &p1_box, &p2_box) )
        return;
//    sub_479330(v1);



    float p1_frc = (p2->field_74C + p1->h_inerc) * p1->field_564;
    float p2_frc = (p1->field_74C + p2->h_inerc) * p2->field_564;

    if ( get_border_near(p1) == BORD_RIGHT && bdr_r_char == 0 ) //P1 at right border
    {
        p2->x -= (p2_box.x2 - p1_box.x1 - 1.0);

        if ( p2->dir * p2_frc + p1->dir * p1_frc >= 0.0 &&
             p2->dir * p2_frc >= 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else if ( get_border_near(p1) == BORD_LEFT  && bdr_l_char == 0 ) //P1 at left border
    {
        p2->x += (p1_box.x2 - p2_box.x1 - 1.0);

        if ( p2->dir * p2_frc + p1->dir * p1_frc <= 0.0 &&
             p2->dir * p2_frc <= 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else if ( get_border_near(p2) == BORD_RIGHT && bdr_r_char == 1 ) //P2 at right border
    {
        p1->x -= (p1_box.x2 - p2_box.x1 - 1.0);

        if ( p1->dir * p1_frc + p2->dir * p2_frc > 0.0 &&
             p1->dir * p1_frc > 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else if ( get_border_near(p2) == BORD_LEFT && bdr_l_char == 1 ) //P2 at left border
    {
        p1->x += (p2_box.x2 - p1_box.x1 - 1.0);

        if ( p1->dir * p1_frc + p2->dir * p2_frc <= 0.0 &&
             p1->dir * p1_frc <= 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else // not at border
    {
        float p1_xx = p1_box.x1 + p1_box.x2;
        float p2_xx = p2_box.x1 + p2_box.x2;
        float p1_yy = p1_box.y1 + p1_box.y2;
        float p2_yy = p2_box.y1 + p2_box.y2;

        if ( p1_xx > p2_xx || (p1_xx == p2_xx && p2_yy > p1_yy)) // if p1 at right of p2 or if p1 == p2 and p2 upper than p1
        {
            float dist = (p2_box.x2 - p1_box.x1 - 1.0);

            if ( dist < 0.0 )
                dist = 0.0;

            float mv_dist = dist / 2.0;

            if ( getlvl_height(p1, mv_dist) == 0 )
                p1->x += mv_dist;

            if ( getlvl_height(p2,-mv_dist) == 0 )
                p2->x -= mv_dist;

            if ( p2->dir * p2->field_564 * p2->h_inerc >=
                 p1->dir * p1->field_564 * p1->h_inerc )
            {
                float force = (p1_frc * p1->dir + p2_frc * p2->dir) / 2.0;
                p1->field_744 = p1->dir * force - p1->h_inerc;
                p2->field_744 = p2->dir * force - p2->h_inerc;
            }
        }
        else
        {
            float dist = (p1_box.x2 - p2_box.x1 - 1.0);

            if ( dist < 0.0 )
                dist = 0.0;

            float mv_dist = dist / 2.0;

            if ( getlvl_height(p1, mv_dist) == 0 )
                p1->x -= mv_dist;

            if ( getlvl_height(p2,-mv_dist) == 0 )
                p2->x += mv_dist;


            if ( p2->dir * p2->field_564 * p2->h_inerc <=
                 p1->dir * p1->field_564 * p1->h_inerc )
            {
                float force = (p1_frc * p1->dir + p2_frc * p2->dir) / 2.0;
                p1->field_744 = p1->dir * force - p1->field_564 * p1->h_inerc;
                p2->field_744 = p2->dir * force - p2->field_564 * p2->h_inerc;
            }
        }
    }
}

void scene_subfunc4(c_scene *scn)
{
    for (uint32_t i=0; i < 2; i++)
        char_xy_pos_calculation(scn->chrs[i]);
}

void scene_subfunc5(c_scene *scn)
{

}

void c_scene::update()
{
    func16();
    scene_subfunc1(this);
    scene_subfunc2(this);
    scene_check_collisions(this);
    scene_subfunc4(this);
    scene_subfunc5(this);
    func12();
    img_sp.update();
}


void scene_load_sounds()
{
    char buf[CHRBUF];
    for (uint32_t i=0; i<MAX_GLB_SFX; i++)
    {
        sprintf(buf,"data/se/%3.3d.cv3",i);

        filehandle *ft = arc_get_file(buf);

        snds[i] = NULL;

        if (ft)
        {
            snds[i] = sfx_load_cv3(ft);
            delete ft;
        }
    }
}

void scene_play_sfx(uint32_t idx)
{
    if (snds[idx % MAX_GLB_SFX] != NULL)
        sfx_play(snds[idx % MAX_GLB_SFX]);
}


c_scene_sp *scene_get_sp()
{
    return &img_sp;
}

void scene_add_effect(char_c *chr, int32_t idx, float x, float y, int8_t dir, int8_t order)
{
    img_sp.addeffect(chr, idx,x,y,dir, order);
}


uint32_t scene_rand()
{
    return randomm.get_next();
}

uint32_t scene_rand_rng(uint32_t rng)
{
    return randomm.get_next_ranged(rng);
}
