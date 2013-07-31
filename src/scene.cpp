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
#include "bullets.h"
#include "weather.h"
#include "c_scene_one.h"

#define VERT_SCALE    2.0
#define SCR_WIDTH     640.0
#define VERT_ZERO_PNT 100.0
#define CHAR_VERT_POS 420.0

#define CAM_SPEED     0.3

#define MAX_GLB_SFX     0x100

c_scene_sp *img_sp = NULL;

static sfxc *snds[MAX_GLB_SFX];

mtwist randomm;

c_scene *scn = NULL;

//0 - easy, 3 - Lunatic
int32_t game_difficulty = 3;


GAME_TYPE  game_type = GAME_TYPE_P_VS_P;

GAME_TYPE game_type_get()
{
    return game_type;
}

void game_type_set(GAME_TYPE type)
{
    game_type = type;
}

int32_t get_game_difficulty()
{
    return game_difficulty;
}


void draw_spell_images(spell_bkg_images *sbi)
{
    if (sbi->alpha != 255)
    {
        if (sbi->spell_image[0] == NULL)
            sbi->spell_image[0] = sbi->spell_image[1];
        if (sbi->spell_image[1] == NULL)
            sbi->spell_image[1] = sbi->spell_image[0];

        gr_tex_box box;
        box.a = (255 - sbi->alpha ) * (3.0/8.0);
        box.r = 255;
        box.g = 255;
        box.b = 255;
        box.autosize = false;
        box.x = 0;
        box.y = 0;
        box.w = 640;
        box.h = 480;
        box.overlay_tex = true;
        box.skew_in_pix = false;
        box.tex = sbi->spell_image[0];
        box.skew_x = sbi->dx[0];
        box.skew_y = sbi->dy[0];

        if (box.tex)
            gr_draw_tex_box(&box,gr_alpha,PLANE_GUI);

        box.tex = sbi->spell_image[1];
        box.skew_x = sbi->dx[1];
        box.skew_y = sbi->dy[1];
        if (box.tex)
            gr_draw_tex_box(&box,gr_alpha,PLANE_GUI);
    }
}



bool sub_479510(frame_box *a1, frame_box *a2, int32_t x, int32_t y)
{
    return ((y - a1->y2) * a2->y2 + (x - a1->x2) * a2->x2 - 1) < 0 &&
           (a2->y2 * (a1->y1 - y)+ a2->x2 * (a1->x1 - x) - 1) < 0 &&
           ((y - a1->y2) * a2->y1+ (x - a1->x2) * a2->x1 - 1) < 0 &&
           ((a1->y1 - y) * a2->y1 + (a1->x1 - x) * a2->x1 - 1) < 0;
}


bool sub_4795A0(int32_t x11, int32_t y11, int32_t x12, int32_t y12, int32_t x21, int32_t y21, int32_t x22, int32_t y22)
{
    return ((((y12 - y11) * (x22 - x11) - (x12 - x11) * (y22 - y11)) < 0 ) ^
            (((y12 - y11) * (x21 - x11) - (x12 - x11) * (y21 - y11)) < 0 )) &&
           ((((y22 - y21) * (x12 - x21) - (x22 - x21) * (y12 - y21)) < 0 ) ^
            (((y22 - y21) * (x11 - x21) - (x22 - x21) * (y11 - y21)) < 0 ));
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

c_scene::c_scene()
{
    frames = 0;
    cur_game_state = 0;
    game_state = 0;
    field_8 = 0;

    init_lvl_height();

    reset_ibox();

    randomm.set_seed(time(NULL));


    if (!img_sp)
        img_sp = new c_scene_sp;

    weather_init_manager();

    w_man = weather_manager_get();

    spell_images.alpha = 255;
    spell_images.alpha = 255;
    spell_images.spell_image[0] = NULL;
    spell_images.spell_image[1] = NULL;
    spell_images.alpha_delta = 0;
    spell_images.dx[0] = 0.0;
    spell_images.dy[0] = 0.0;
    spell_images.dx[1] = 0.3;
    spell_images.dy[1] = 0.3;

    //add_infoeffect(2,1);
    //weather_sp->addeffect(1,1);

}

c_scene::~c_scene()
{

}

void c_scene::draw_scene()
{
    upd_camera(chrs[0],chrs[1]);

    for(uint32_t i=0; i < w_man->sky_deque.size(); i++)
    {
        s_asky *tmp = &w_man->sky_deque[i];
        w_man->skys.draw(tmp->sky_id,tmp->alpha,2);
    }

    w_man->wfx_holder.draw(-2,1);

    bkg->draw_back();

    draw_spell_images(&spell_images);

    for (uint32_t i=0; i < 2; i++)
        bkg->draw_shadow(chrs[i]);

    bkg->draw_mid();
    w_man->wfx_holder.draw(-1,1);

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->stand_gfx->draw(PLANE_GUI);

    img_sp->draw(-1, 1);

    for (uint32_t i=0; i < 2; i++)
        drawbullet(chrs[i],-1);

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->draw();

    bkg->draw_near();
    w_man->wfx_holder.draw(1,1);

    img_sp->draw(1, 1);

    for (uint32_t i=0; i < 2; i++)
        drawbullet(chrs[i],1);

}

void c_scene::players_input()
{
    for (uint32_t i=0; i < 2; i++)
    {
        chrs[i]->input_update();
        chrs[i]->check_seq_input();
    }
}






int32_t c_scene::get_stage_id()
{
    return bkg->get_idx();
}

void c_scene::func14()
{
    draw_scene();
    ui->draw();
}

void c_scene::func15()
{
    if ( chrs[0]->field_740 || chrs[1]->field_740 )
        spell_images.alpha_delta = -10;
    //if ( game_type_get() != GAME_TYPE_HOST ) //HACK
    //  if ( game_type_get() != GAME_TYPE_CLIENT )
    //    sub_429E80(practice_params);//HACK

    img_sp->update();
    upd_wfx_bkg_sky(/*dword_8855C0*/);
    time_count_inc();
}

void c_scene::upd_wfx_bkg_sky()
{
    //HACK   NOT FULL CODE!!!

    WEATHER_ID wid;

    if (spell_images.alpha_delta != 0)
    {
        int32_t tmp = spell_images.alpha_delta + spell_images.alpha;
        if ( tmp <= 255 )
        {
            if ( tmp >= 60 )
            {
                spell_images.alpha = tmp;
            }
            else
            {
                spell_images.alpha = 60;
                spell_images.alpha_delta = 0;
            }
        }
        else
        {
            spell_images.alpha = 255;
            spell_images.alpha_delta = 0;
        }
        wid = WEATHER_CLEAR;
    }
    else
    {
        if ( spell_images.alpha >= 245 )
            spell_images.alpha = 255;
        else
            spell_images.alpha += 10;

        wid = w_man->current_sky_weather;
    }

    weather_spawn_effects_by_id(wid);

    spell_images.dx[0] += 0.005;
    spell_images.dx[1] -= 0.005;
    spell_images.dy[0] += 0.005;
    spell_images.dy[1] += 0.005;

    w_man->wfx_holder.update();//from: update_sky_bkgs__and__wefx

    for (int32_t i=w_man->sky_deque.size() - 1 ; i > 0; i--) //from: update_sky_bkgs__and__wefx
    {
        if (w_man->sky_deque[i].alpha > 15)
            w_man->sky_deque[i].alpha -= 15;
        else
            w_man->sky_deque.erase(w_man->sky_deque.begin() + i);
    }

    bkg->update();
}

void c_scene::reset_ibox()
{
    ibox.x1 = -10000;
    ibox.y1 = -10000;
    ibox.x2 = 10000;
    ibox.y2 = 10000;
}


void c_scene::scene_subfunc1()
{
    for (uint32_t i=0; i < 2; i++)
        chrs[i]->func16();

    //HACK NOT NEEDED
    //for (uint32_t i=0; i < 2; i++)
    //chrs[i]->bullets_func16;

    for (uint32_t i=0; i < 2; i++)
    {
        chrs[i]->func10();
    }


    for (uint32_t i=0; i < 2; i++)
    {
        if ( chrs[i]->hit_stop == 0 )
        {

            if ( !chrs[i]->enemy->time_stop )
            {
                if ( chrs[i]->char_idle_or_move() )
                {
                    chrs[i]->func18();
                    if ( !chrs[i]->field_4C0 )
                        chrs[i]->damage_limit = 0;
                }
                if (chrs[i]->char_is_shock())
                    if ( chrs[i]->y > 0.0 )
                        chrs[i]->sub_462FF0();
            }
            if ( chrs[i]->get_seq() < 300 )
            {
                //if ( v1->some_input_var <= 6 )
                //zero_input_charclass_ispressed_vars(v1); //HACK
            }
            chrs[i]->func20();
        }
    }

    for (uint32_t i=0; i < 2; i++)
    {
        if (!chrs[i]->enemy->time_stop)
        {
            bullist *lst = chrs[i]->get_bullets();
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
    }
}





void c_scene::scene_subfunc2()
{
    for(int32_t i=0; i < 2; i++)
    {
        list1[i].clear();
        list2[i].clear();
        list3[i].clear();
        scn_p1[i] = 0;
        scn_p2[i] = 0;
    }

    for(int32_t i=0; i < 2; i++)
    {
        chrs[i]->scn_char_ss2();
        chrs[i]->field_575 = chrs[i]->field_574;

        bullist *blst = chrs[i]->get_bullets();
        for(bullist_iter i = blst->begin(); i != blst->end(); i++)
        {
            c_bullet *bul = *i;

            int32_t plindex = bul->chrt->player_index;

            char_frame *frm = bul->get_pframe();

            int32_t atk_sz = frm->box_atk.size();
            int32_t hit_sz = frm->box_hit.size();

            if (bul->cust_box)
            {
                atk_sz++;
                if (frm->fflags & FF_ATK_AS_HIT)
                    hit_sz++;
            }

            if (!bul->parent_mlist)
            {
                if (atk_sz && bul->field_190 == 0 && bul->field_194 > 0)
                {
                    bul->scn_char_ss2();

                    list1[plindex].push_back(bul);

                    if (hit_sz)
                        list2[plindex].push_back(bul);

                    list3[plindex].push_back(bul);
                }
                else if (hit_sz)
                {
                    bul->scn_char_ss2();

                    list2[plindex].push_back(bul);

                    list3[plindex].push_back(bul);
                }
            }
            else if ( hit_sz )
            {
                list2[plindex].push_back(bul);
            }
        }
    }

    for(int32_t i=0; i < 2; i++)
    {
        if (chrs[i]->atk_box_cnt)
            if (chrs[i]->field_190 == 0 && chrs[i]->field_194 > 0)
            {
                list1[i].push_back(chrs[i]);
                list3[i].push_back(chrs[i]);
            }
    }

    sub_47C180();
    sub_47C430();

    for(int32_t i=0; i < 2; i++)
    {
        char_c *enm = chrs[i]->enemy;

        metalst *lst = &list1[i];

        for(metalst_iter mt = lst->begin(); mt != lst->end(); mt++)
        {
            c_meta *meta = *mt;

            sub_47BE70(meta,enm); //BUllet collide with player enemy

            if (meta->get_pframe()->aflags & AF_HITSALL)
                sub_47BE70(meta,chrs[i]); //BUllet collide with player
        }
    }

    for(int32_t i=0; i < 2; i++)
    {
        if (!chrs[i]->field_574)
        {
            chrs[i]->health += scn_p1[i];
            if (chrs[i]->health >= chrs[i]->max_health)
                chrs[i]->health = chrs[i]->max_health;
            else if (chrs[i]->health <= 1)
                chrs[i]->health = 1;
        }
        if (scn_p2[i] < 0)
        {
            chrs[i]->sub_4689D0(-scn_p2[i]);
        }
    }
}




void c_scene::sub_47BE70(c_meta *plr, char_c *enm)
{
    if ( plr->chrt->field_575 == 0 && enm->field_575 != 2 )
    {
        if ( !enm->sub_4699E0() && enm->damage_limit < 100 )
        {
            char_frame *frm = plr->get_pframe();
            if (plr != enm || (frm->aflags & AF_HITSALL) == 0 || plr->enemy->field_575 == 0)
            {
                if (!plr->childs.empty())
                {
                    if (sub_47BD80(plr, enm))
                        plr->sub_4647B0(plr);
                    else
                    {
                        metalst *lst = &plr->childs;
                        for(metalst_iter i = lst->begin(); i != lst->end(); i++)
                            if (sub_47BD80(*i, enm))
                                plr->sub_4647B0(*i);
                    }
                }
                else
                {
                    sub_47BD80(plr, enm);
                }
            }
        }
    }
}

void c_scene::sub_47C430()
{
    for (int8_t i=0; i<2; i++)
    {
        char_c *chr = chrs[i];

        metalst *lst1 = &list3[chr->player_index];

        for(metalst_iter m1 = lst1->begin(); m1 != lst1->end(); m1++)
        {
            c_meta *mt1 = *m1;

            if (mt1->field_190 ==0 && mt1->field_194 > 0)
            {
                metalst *lst2 = &list2[chr->enemy->player_index];
                for(metalst_iter m2 = lst2->begin(); m2 != lst2->end(); m2++)
                {
                    c_meta *mt2 = *m2;

                    if ( !sub_47C080(mt1, mt2))
                        sub_47BFA0(mt1, mt2);
                }

                if (mt1->get_pframe()->aflags & AF_HITSALL)
                {
                    metalst *lst2 = &list2[chr->player_index];
                    for(metalst_iter m2 = lst2->begin(); m2 != lst2->end(); m2++)
                    {
                        c_meta *mt2 = *m2;

                        if ( !sub_47C080(mt1, mt2))
                            sub_47BFA0(mt1, mt2);
                    }
                }
            }
        }
    }
}

char c_scene::sub_47AC70(c_meta *plr, c_meta *enm)
{
    if ( sub_479BC0(plr, enm) )
    {
        char_frame *frm = plr->get_pframe();
        plr->field_194 = plr->field_1BC - 1;
        plr->field_190 = 9;
        plr->hit_stop = frm->flag196_char;
        enm->health -= frm->damage;
        scene_play_sfx(frm->hit_sfx);
        scene_add_effect_ibox(frm->unk19, plr->dir);
        reset_ibox();
        return true;
    }

    return false;
}

void c_scene::sub_47BFA0(c_meta *plr, c_meta *enm)
{
    if ( (enm->get_pframe()->fflags & FF_CH_ON_HIT) && enm->field_1AC )
    {
        if ( !plr->childs.empty() )
        {
            if ( sub_47AC70(plr, enm) )
                plr->sub_4647B0(plr);
            else
            {
                metalst *lst = &plr->childs;

                for (metalst_iter i = lst->begin(); i != lst->end(); i++)
                    if ( sub_47AC70(*i, enm) )
                    {
                        plr->sub_4647B0(*i);
                        break;
                    }
            }
        }
        else
            sub_47AC70(plr,enm);
    }
}


bool c_scene::sub_47AD00(c_meta *plr, c_meta *enm)
{
    if (plr->chrt != enm->chrt)
    {
        if ( !(plr->get_pframe()->fflags & FF_UNK80000) || !sub_479D50(plr, enm))
            return false;
        enm->sub_464890(plr);
        plr->field_1A0++;
        reset_ibox();
    }
    return true;
}



bool c_scene::sub_47C080(c_meta *plr, c_meta *enm)
{
    char_frame *frm2 = enm->get_pframe();

    if ( !(frm2->aflags & AF_UNK20000) && !enm->field_1A1 && (frm2->aflags & AF_UNK400000))
    {
        if (plr->childs.empty())
        {
            return sub_47AD00(plr, enm);
        }
        else
        {
            if (sub_47AD00(plr, enm))
                return true;

            metalst *lst = &plr->childs;

            for (metalst_iter bl = lst->begin(); bl != lst->end(); bl++)
            {
                if (sub_47AD00(*bl, enm))
                    return true;
            }
        }
    }
    return false;
}


void c_scene::sub_47C180()
{
    for (int8_t c=0; c < 2; c++) //Bullets to own bullets hit, if AF_HITSALL
    {
        metalst *lst = &list2[c];

        for(metalst_iter i=lst->begin(); i != lst->end(); i++)
        {
            c_meta *mt =  *i;
            char_frame *frm = mt->get_pframe();

            if ((frm->aflags & AF_HITSALL) && !(frm->fflags & (FF_CH_ON_HIT | FF_INV_AIRBORNE)) && mt->field_1BC > 0)
            {
                for(metalst_iter j=lst->begin(); j != lst->end(); j++)
                {
                    c_meta *mt2 =  *j;
                    char_frame *frm2 = mt2->get_pframe();

                    if (mt2 != mt)
                        if (!(frm2->fflags & (FF_CH_ON_HIT | FF_INV_AIRBORNE)) && mt2->field_1BC > 0)
                            sub_47AD60(mt,mt2);
                }

            }
        }
    }

    metalst *lst1 = &list2[0];
    metalst *lst2 = &list2[1];

    for(metalst_iter i=lst1->begin(); i != lst1->end(); i++)
    {
        c_meta *mt =  *i;
        char_frame *frm = mt->get_pframe();

        if (!(frm->fflags & (FF_CH_ON_HIT | FF_INV_AIRBORNE)) && mt->field_1BC > 0)
        {
            for(metalst_iter j=lst2->begin(); j != lst2->end(); j++)
            {
                c_meta *mt2 =  *j;
                char_frame *frm2 = mt2->get_pframe();

                if (!(frm2->fflags & (FF_CH_ON_HIT | FF_INV_AIRBORNE)) && mt2->field_1BC > 0)
                    sub_47AD60(mt,mt2);
            }
        }
    }
}




bool c_scene::scene_collid(box_box *b1, box_box *b2)
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
        //sub_4790B0(this, a2, a3); //HACK
        return true;
    }
}

//Previous frame character near border
// -1 - no char, 0 - player 1, 1 - player 2
int8_t bdr_r_char = -1;
int8_t bdr_l_char = -1;

void c_scene::scene_check_collisions()
{
    char_c *p1 = chrs[0];
    char_c *p2 = chrs[1];

    p1->field_744 = 0.0;
    p2->field_744 = 0.0;

    if ( !p1->get_pframe()->box_coll || !p2->get_pframe()->box_coll )
        return;

    //Detecting who firstly take border

    if      ( bdr_r_char == 1 && p2->get_border_near() != BORD_RIGHT )
        bdr_r_char = -1;
    else if ( bdr_r_char == 0 && p1->get_border_near() != BORD_RIGHT )
        bdr_r_char = -1;

    if      ( bdr_l_char == 1 && p2->get_border_near() != BORD_LEFT )
        bdr_l_char = -1;
    else if ( bdr_l_char == 0 && p1->get_border_near() != BORD_LEFT )
        bdr_l_char = -1;

    if      (p1->get_border_near() == BORD_LEFT  && bdr_l_char == -1)
        bdr_l_char = 0;
    else if (p1->get_border_near() == BORD_RIGHT && bdr_r_char == -1)
        bdr_r_char = 0;

    if      (p2->get_border_near() == BORD_LEFT  && bdr_l_char == -1)
        bdr_l_char = 1;
    else if (p2->get_border_near() == BORD_RIGHT && bdr_r_char == -1)
        bdr_r_char = 1;

    //now we finally know it.

    box_box p1_box;
    box_box p2_box;

    p1->box_coll_get(&p1_box);
    p2->box_coll_get(&p2_box);

    if ( !scene_collid(&p1_box, &p2_box) )
        return;

    reset_ibox();

    float p1_frc = (p2->field_74C + p1->h_inerc) * p1->field_564;
    float p2_frc = (p1->field_74C + p2->h_inerc) * p2->field_564;

    if ( p1->get_border_near() == BORD_RIGHT && bdr_r_char == 0 ) //P1 at right border
    {
        p2->x -= (p2_box.x2 - p1_box.x1 - 1.0);

        if ( p2->dir * p2_frc + p1->dir * p1_frc >= 0.0 &&
                p2->dir * p2_frc >= 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else if ( p1->get_border_near() == BORD_LEFT  && bdr_l_char == 0 ) //P1 at left border
    {
        p2->x += (p1_box.x2 - p2_box.x1 - 1.0);

        if ( p2->dir * p2_frc + p1->dir * p1_frc <= 0.0 &&
                p2->dir * p2_frc <= 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else if ( p2->get_border_near() == BORD_RIGHT && bdr_r_char == 1 ) //P2 at right border
    {
        p1->x -= (p1_box.x2 - p2_box.x1 - 1.0);

        if ( p1->dir * p1_frc + p2->dir * p2_frc > 0.0 &&
                p1->dir * p1_frc > 0.0 )
        {
            p1->field_744 = -p1_frc;
            p2->field_744 = -p2_frc;
        }
    }
    else if ( p2->get_border_near() == BORD_LEFT && bdr_l_char == 1 ) //P2 at left border
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

            if ( p1->getlvl_height(mv_dist) == 0 )
                p1->x += mv_dist;

            if ( p2->getlvl_height(-mv_dist) == 0 )
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

            if ( p1->getlvl_height(mv_dist) == 0 )
                p1->x -= mv_dist;

            if ( p2->getlvl_height(-mv_dist) == 0 )
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

void c_scene::scene_subfunc4()
{
    for (uint32_t i=0; i < 2; i++)
        chrs[i]->char_xy_pos_calculation();

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->sub_469A20();

    for (uint32_t i=0; i < 2; i++)
        chrs[i]->char_stats_check();
}

void c_scene::scene_subfunc5()
{
//HACK
    func15();
    field_8 = 0;
    ui->update();
    //((void (*)(void))battle_manager->vtbl->bman_func4)();
    //sub_428990(&transform_values__);
    //sub_428BB0(&transform_values__);
}

bool c_scene::sub_479720(frame_box *a1, frame_box *a2, frame_box *b1, frame_box *b2)
{
    if  ( (a1->x1 - b1->x2) < 0 && (b1->x1 - a1->x2) < 0 &&
            (b1->y1 + b2->y1 - a2->y2 - a1->y1) < 0 && (a1->y1 + a2->y1 - b2->y2 - b1->y1) < 0 )
    {
        if ( sub_479510(b1, b2, a1->x1, a1->y1) || sub_479510(a1, a2, b1->x1, b1->y1) )
        {
            sub_479250(a1, a2, b1, b2);
            return true;
        }
        if (    sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x1, b1->y1, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x1, b1->y1, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x2, b1->y2, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x2, b1->y2, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x1, b1->y1, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x1, b1->y1, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x2, b1->y2, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x1, a1->y1, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x2, b1->y2, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x1, b1->y1, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x1, b1->y1, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x2, b1->y2, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x1, a1->y1 + a2->y1,  b1->x2, b1->y2, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x1, b1->y1, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x1, b1->y1, b1->x1 + b2->x2, b1->y1 + b2->y2) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x2, b1->y2, b2->x1 + b1->x1, b1->y1 + b2->y1) ||
                sub_4795A0(a1->x2, a1->y2, a1->x1 + a2->x2, a1->y1 + a2->y2,  b1->x2, b1->y2, b1->x1 + b2->x2, b1->y1 + b2->y2) )
        {
            sub_479250(a1, a2, b1, b2);
            return true;
        }
    }
    return false;
}

void c_scene::sub_479250(frame_box *a2, frame_box *a3, frame_box *a4, frame_box *a5)
{
    frame_box b1;
    frame_box b2;

    b2.x1 = a2->x1;
    b2.y1 = a2->y1 + a3->y1;
    b2.x2 = a2->x2;
    b2.y2 = a2->y1 + a3->y2;

    b1.x1 = a4->x1;
    b1.y1 = a4->y1 + a5->y1;
    b1.x2 = a4->x2;
    b1.y2 = a4->y1 + a5->y2;

    scene_set_ibox(&b2, &b1);
}

void c_scene::scene_set_ibox(frame_box *a2, frame_box *a3)
{
    int32_t min = 0;

    if ( a2->x1 >= a2->x2 )
    {
        if ( ibox.x1 < a2->x2 )
            ibox.x1 = a2->x2;
        min= a2->x1;
    }
    else
    {
        if ( ibox.x1 < a2->x1 )
            ibox.x1 = a2->x1;
        min = a2->x2;
    }
    if ( ibox.x2 > min )
        ibox.x2 = min;

    if ( a3->x1 >= a3->x2 )
    {
        if ( ibox.x1 < a3->x2 )
            ibox.x1 = a3->x2;
        min = a3->x1;
    }
    else
    {
        if ( ibox.x1 < a3->x1 )
            ibox.x1 = a3->x1;
        min = a3->x2;
    }
    if ( ibox.x2 > min )
        ibox.x2 = min;


    if ( ibox.y1 < a2->y1 )
        ibox.y1 = a2->y1;

    if ( ibox.y1 < a3->y1 )
        ibox.y1 = a3->y1;

    if ( ibox.y2 > a2->y2 )
        ibox.y2 = a2->y2;

    if ( ibox.y2 > a3->y2 )
        ibox.y2 = a3->y2;
}

void c_scene::sub_479200(frame_box *a1, frame_box *a2, frame_box *a3)
{
    frame_box tmp;

    tmp.x1 = a1->x1;
    tmp.x2 = a1->x2;
    tmp.y1 = a1->y1 + a2->y1;
    tmp.y2 = a1->y1 + a2->y2;

    scene_set_ibox(&tmp, a3);
}

bool c_scene::sub_479420(frame_box *a1, frame_box *a2, frame_box *a3)
{

    if ( (a3->x1 - a1->x2) < 0 &&
            (a1->x1 - a3->x2) < 0 &&
            (a3->y1 - a2->y2 - a1->y1) < 0 &&
            (a1->y1 + a2->y1 - a3->y2) < 0 &&
            (a2->x1 * (a3->y2 - a1->y1) - a2->y1 * (a3->x2 - a1->x1)) >= 0 &&
            (a2->y2 * (a3->x2 - a1->x1) - a2->x2 * (a3->y1 - a1->y1)) >= 0 &&
            (a2->y2 * (a3->x1 - a1->x2) - a2->x2 * (a3->y2 - a1->y2)) <= 0 &&
            (a2->x1 * (a3->y1 - a1->y2) - a2->y1 * (a3->x1 - a1->x2)) <= 0 )
    {
        sub_479200(a1, a2, a3);
        return true;
    }
    return false;
}

bool c_scene::sub_479D50(c_meta *p1, c_meta *p2)
{
    bool hit = false;

    for (int32_t i=0; i< p1->hit_box_cnt; i++)
    {
        if (p1->hit_area_flags[i] != NULL)
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479720(&p1->hit_area_2o[i], p1->hit_area_flags[i], &p2->hit_area_2o[j], p2->hit_area_flags[j]);
                else
                    hit |= sub_479420(&p1->hit_area_2o[i], p1->hit_area_flags[i], &p2->hit_area_2o[j]);
            }
        }
        else
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479420(&p2->hit_area_2o[j], p2->hit_area_flags[j], &p1->hit_area_2o[i]);
                else
                {
                    frame_box *fb1 = &p1->hit_area_2o[i];
                    frame_box *fb2 = &p2->hit_area_2o[j];

                    if ((fb2->x1 - fb1->x2) < 0 &&
                            (fb1->x1 - fb2->x2) < 0 &&
                            (fb1->y1 - fb2->y2) < 0 &&
                            (fb2->y1 - fb1->y2) < 0)
                    {
                        scene_set_ibox(fb1, fb2);
                        hit |= true;
                    }
                }
            }
        }
    }
    return hit;
}

bool c_scene::sub_47AD60(c_meta *plr, c_meta *enm)
{

    if ( !sub_479D50(plr, enm) )
        return false;

    if ( plr->get_cprior() == 0 )
    {
        if ( enm->get_cprior() != 0 )
        {
            if ( enm->get_prior() < 0 )
            {
                enm->set_mlist_hitflag(4);
            }
            else
            {
                plr->set_mlist_hitflag(5);
                enm->set_mlist_hitflag(8);
            }
        }
        else
        {
            if (plr->get_prior() > enm->get_prior())
            {
                enm->set_mlist_hitflag(4);
            }
            else if (plr->get_prior() < enm->get_prior())
            {
                plr->set_mlist_hitflag(4);
            }
            else
            {
                plr->set_mlist_hitflag(8);
                enm->set_mlist_hitflag(8);
            }
        }
    }
    else if ( plr->get_cprior() > enm->get_cprior() )
    {
        if ( enm->get_cprior() != 0 )
        {
            plr->set_mlist_hitflag(8);
            enm->set_mlist_hitflag(4);
        }
        else
        {
            if ( plr->get_cprior() < enm->get_prior() )
            {
                plr->set_mlist_hitflag(4);
            }
            else
            {
                plr->set_mlist_hitflag(8);
                enm->set_mlist_hitflag(5);
            }
        }
    }
    else if (plr->get_cprior() < enm->get_cprior())
    {
        plr->set_mlist_hitflag(4);
        enm->set_mlist_hitflag(8);
    }
    else //plr->get_cprior() == enm->get_cprior()
    {
        plr->set_mlist_hitflag(4);
        enm->set_mlist_hitflag(4);
    }
    reset_ibox();
    return true;
}

bool c_scene::sub_479650(c_meta *p1, c_meta *p2)
{
    bool hit = false;

    if ( p2->pcoll_box != NULL )
    {
        for (int32_t i = 0; i < p1->atk_box_cnt; i++)
        {
            if (p1->atk_area_of[i] != NULL)
            {
                hit |= sub_479420(&p1->atk_area_2o[i], p1->atk_area_of[i], p2->pcoll_box);
            }
            else
            {
                frame_box *fb1 = &p1->atk_area_2o[i];
                frame_box *fb2 = p2->pcoll_box;

                if ((fb2->x1 - fb1->x2) < 0 &&
                        (fb1->x1 - fb2->x2) < 0 &&
                        (fb1->y1 - fb2->y2) < 0 &&
                        (fb2->y1 - fb1->y2) < 0)
                {
                    scene_set_ibox(fb1, fb2);
                    hit |= true;
                }
            }
        }
    }
    return hit;
}

bool c_scene::sub_479BC0(c_meta *p1, c_meta *p2)
{
    bool hit = false;

    for (int32_t i=0; i< p1->atk_box_cnt; i++)
    {
        if (p1->atk_area_of[i] != NULL)
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479720(&p1->atk_area_2o[i], p1->atk_area_of[i], &p2->hit_area_2o[j], p2->hit_area_flags[j]);
                else
                    hit |= sub_479420(&p1->atk_area_2o[i], p1->atk_area_of[i], &p2->hit_area_2o[j]);
            }
        }
        else
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479420(&p2->hit_area_2o[j], p2->hit_area_flags[j], &p1->atk_area_2o[i]);
                else
                {
                    frame_box *fb1 = &p1->atk_area_2o[i];
                    frame_box *fb2 = &p2->hit_area_2o[j];

                    if ((fb2->x1 - fb1->x2) < 0 &&
                            (fb1->x1 - fb2->x2) < 0 &&
                            (fb1->y1 - fb2->y2) < 0 &&
                            (fb2->y1 - fb1->y2) < 0)
                    {
                        scene_set_ibox(fb1, fb2);
                        hit |= true;
                    }
                }
            }
        }
    }
    return hit;
}

bool c_scene::sub_47BD80(c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if ( frm->aflags & AF_UNK400000 )
    {
        if ( !(frm->aflags & AF_UNK40000)  && (enm->field_520 != 0 || frm2->fflags & FF_INV_FIRE) )
            return false;
    }
    else
    {
        if ( enm->field_51C != 0 || frm2->fflags & FF_MEL_INV_GND )
            return false;
    }

    if (frm->aflags & AF_UNK80) // >= 0 )
    {
        if ( enm->field_51E != 0 || frm2->fflags & FF_UNK800 || frm2->fflags & FF_UNK1000 )
            return false;
        if (!sub_479650(plr, enm))
            return false;
    }
    else
    {
        if (!sub_479BC0(plr, enm))
            return false;
    }

    enm->field_4AC = (frm->aflags & AF_UNK400000) == 0; //~(aflags >> 22) & 1
    if ( !sub_47ABE0(plr, enm) )
    {
        if ( !sub_47AAA0(plr, enm) )
        {
            if ( !sub_47BBA0(plr, enm) )
                sub_47A060(plr, enm);
        }
    }
    return true;
}

void c_scene::sub_478FC0(char_c *plr, char_c *enm)
{
    enm->health_prev = enm->health;
    enm->damage_limit = 0;
    plr->combo_count = 0;
    plr->combo_rate = 1.0;
    plr->combo_damage = 0;
    plr->combo_limit = 0;
    plr->correction = 0;
    //sub_478540((battle_manager + 52 * (character->player_index + 7))); //HACK
}

void c_scene::sub_47A060(c_meta *plr, char_c *enm)
{
    int16_t dmg = 0;

    char_frame *frm  = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if ( !enm->char_is_shock() )
    {
        if ( enm->field_4C0 == 0 )
            sub_478FC0(plr->chrt, enm);
    }
    if ( enm->field_538 != 0.0 )
    {
        if (frm->aflags & AF_UNK20 || ((frm2->fflags & (FF_SUPERARMOR | FF_GUARD )) == 0 ))
            enm->field_4BC += frm->unk9 * enm->field_538;
        else if ((frm2->fflags & FF_GUARD) == 0)
            enm->field_4BC += frm->unk9 * enm->field_538 * 0.5;
    }

    int16_t atype = frm->attack_type;
    bool v36 = false;

    int16_t fallseq = -1;

    if ( enm->field_4BC < 100 )
    {
        enm->damage_limit += (plr->chrt->limit_multiply * frm->limit);
        enm->field_19C = 15.0;
        enm->field_4C0 = 20;

        plr->chrt->combo_limit = enm->damage_limit;
        plr->field_190 = 7;
    }
    else
    {

        enm->field_4BC = 0;
        enm->damage_limit += (plr->chrt->limit_multiply * frm->limit);
        enm->field_4C0 = 0;

        plr->field_190 = 1;
        plr->chrt->combo_limit = enm->damage_limit;

        enm->reset_ofs();

        bool v10 = (frm2->fflags & FF_CH_ON_HIT) != 0 || (enm->field_56F && plr->chrt->combo_count == 0);

        if ( game_type_get() == GAME_TYPE_TRAINING )
        {
            /*if ( !practice_params->dummy_counter ) // HACK
            {
              if ( plr->chrt->combo_count == 0)
                v10 = true;
            }*/
        }

        if ( plr->field_1A2 <= 0 || plr->chrt->combo_count != 0 )
        {
            if ( frm->aflags & AF_CRASH_HIT )
            {
                if ( v10 )
                {
                    v36 = true;

                    if (atype >= 3) //?
                        atype = 3;
                    else
                        atype++;
                }
            }
        }
        else
        {
            v36 = true;

            if (atype >= 3)
                atype = 3;
            else
                atype++;
            plr->field_1A2--;
        }


        if ( enm->health <= 0 || enm->damage_limit >= 100 )
        {
            if ( frm->fall_seq == 70 )
                fallseq = 71;
            else
                fallseq = frm->fall_seq;
        }
        else
        {
            if (!enm->char_on_ground_flag() || (frm2->fflags & FF_AIRBORNE) || frm->fall_seq2 != 0)
            {
                if ( frm->fall_seq == 0 && frm->fall_seq2 == 0 )
                {
                    fallseq = 70;
                }
                else if ( frm->fall_seq != 0 || frm->fall_seq2 != 0 )
                {
                    int16_t tmp = frm->fall_seq;

                    if (tmp == 0)
                        tmp = frm->fall_seq2;

                    if (v36)
                    {
                        if (tmp == 71)
                            fallseq = 74;
                        else if (tmp == 73)
                            fallseq = 88;
                        else
                            fallseq = tmp;
                    }
                    else
                        fallseq = tmp;

                }
            }
            else if ( frm2->fflags & FF_STAND )
            {
                if ( frm->aflags & AF_UNK1 )
                {
                    fallseq = atype + 56;
                }
                else
                    fallseq = atype + 50;
            }
            else if ( frm2->fflags & FF_CROUCH )
                fallseq = atype + 62;
        }
    }


    if ( !enm->char_is_shock() )
    {
        for (int8_t i = 0; i <= atype && i < 3; ++i )
            scene_add_effect_ibox(201, enm->dir);

        if ( atype >= 2 )
            scene_add_effect_ibox(201, enm->dir);
    }

    plr->field_194 = plr->field_1BC - 1;
    plr->hit_stop = frm->flag196_char;
    enm->hit_stop = frm->flag196_enemy;
    if ( v36 )
    {
        plr->chrt->correction |= 0x20u;
        enm->field_1A4 = frm->velocity_x * 1.5;
        enm->field_1A8 = frm->velocity_y * 1.5;

        if (weather_get() == WEATHER_DUST_STORM)
        {
            weather_time_mul(3.0/4.0);
            enm->field_4BA = (2 * frm->untech) * plr->chrt->combo_rate;
        }
        else
        {
            enm->field_4BA = (3 * frm->untech / 2) * plr->chrt->combo_rate;
        }

        dmg = plr->field_198 * (plr->sub_464240() / 3);
        scene_add_effect_ibox(54, plr->dir);
    }
    else
    {
        enm->field_1A4 = frm->velocity_x;
        enm->field_1A8 = frm->velocity_y;
        enm->field_4BA = (plr->chrt->combo_rate * frm->untech);

        dmg = plr->sub_464240();
    }
    plr->chrt->add_card_energy2(plr->chrt->field_54C * (float)frm->card_energy);
    if ( plr->chrt->field_554 <= 0.0 )
    {
        enm->add_card_energy2(dmg / 20);
    }
    else
    {
        scn_p2[enm->player_index] -= plr->chrt->field_554 * plr->chrt->field_54C * (float)frm->card_energy;
    }

    plr->chrt->combo_count++;

    plr->chrt->combo_rate *= (frm->proration + plr->chrt->field_540 * (1000.0 - frm->proration)) / 1000.0;

    plr->chrt->correction |= frm->unk20;

    plr->chrt->combo_damage += dmg;

    if ( plr->chrt->field_550 > 0 )
    {
        scn_p1[plr->chrt->player_index] += plr->chrt->field_550 * dmg;
    }

    if ( plr->chrt->field_558 > 0 )
    {
        scn_p1[plr->chrt->player_index] -= plr->chrt->field_558 * dmg;
    }

    enm->field_188 += (enm->field_55C * dmg);

    if ( enm->field_575 == 0 )
    {
        enm->health -= dmg;
        if ( enm->health <= 0 )
        {
            enm->health = 0;

            func11(enm);

            if ( frm->fall_seq == 70 )
                fallseq = 71;
            else
                fallseq = frm->fall_seq;
        }
    }

    if ( plr->field_190 != 7 || enm->health <= 0 )
        enm->flip_to_enemy();
    if ( fallseq >= 0 )
        enm->set_seq(fallseq);

    scene_add_effect_ibox(frm->unk19, plr->dir);
    reset_ibox();
    scene_play_sfx(frm->hit_sfx);
}

bool c_scene::sub_47B5A0(c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    if ( !enm->char_is_shock() )
    {
        if ( !enm->field_4C0 )
            sub_478FC0(plr->chrt, enm);
    }
    if ( !enm->field_575 )
    {
        double tmp = plr->sub_464270();

        enm->health -= tmp;
        if ( enm->health < 1 )
            enm->health = 1;

        char_c * plr_c = plr->chrt;
        if ( plr_c->field_550 > 0.0 )
            scn_p1[plr_c->player_index] += tmp * plr_c->field_550;

        char_c * enm_c = enm->chrt;
        if ( enm_c->field_558 > 0.0 )
            scn_p1[enm_c->player_index] -= tmp * plr_c->field_558;
    }
    if ( frm->sp_smval )
    {

        int16_t old_spe = enm->spell_energy;

        if ( frm->aflags & AF_UNK400000 )
        {
            if ( enm->sub_469750(frm->aflags) == 5 )
            {
                enm->spell_energy -= frm->sp_smval;

                if ( frm->attack_type == 0 )
                    enm->spell_energy_stop = 60;
                else if ( frm->attack_type == 1 )
                    enm->spell_energy_stop = 60;
                else if ( frm->attack_type >= 2 )
                    enm->spell_energy_stop = 75;
            }
            else
            {
                enm->spell_energy -= frm->sp_smval;

                if ( frm->attack_type == 0 )
                    enm->spell_energy_stop = 60;
                else if ( frm->attack_type == 1 )
                    enm->spell_energy_stop = 60;
                else if ( frm->attack_type >= 2 )
                    enm->spell_energy_stop = 60;
            }
        }
        else
        {
            if ( enm->sub_469750(frm->aflags) == 5 )
            {
                enm->spell_energy -= frm->sp_smval/2;

                if ( frm->attack_type == 0 )
                    enm->spell_energy_stop = 60;
                else if ( frm->attack_type == 1 )
                    enm->spell_energy_stop = 75;
                else if ( frm->attack_type >= 2 )
                    enm->spell_energy_stop = 90;
            }
        }

        if ( enm->spell_energy <= 0 && enm->spell_energy < old_spe )
        {
            sub_47A980(plr, enm);
            return true;
        }
    }
    plr->field_190 = 2;
    plr->field_194 = plr->field_1BC - 1;
    plr->hit_stop = frm->flag196_char2;

    enm->hit_stop = frm->flag196_enemy2;
    enm->field_1A4 = frm->velocity_x;
    enm->field_1A8 = frm->velocity_y;

    enm->field_49D = 1;

    char_c * plr_c = plr->chrt;

    plr_c->add_card_energy2(plr_c->field_54C * (float)frm->card_energy2);

    if ( plr_c->field_554 > 0.0 )
        scn_p2[enm->player_index] -= (plr_c->field_54C * frm->card_energy2 / 2) * plr_c->field_554;

    enm->flip_to_enemy();
    scene_play_sfx(20);
    scene_add_effect_ibox(50, enm->dir);
    reset_ibox();
    return false;
}

void c_scene::sub_47A980(c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();

    if ( !plr->chrt->field_56D )
        enm->crash_spell_borders(1);

    sub_478FC0(plr->chrt, enm);

    plr->field_190 = 2;
    plr->field_194 = plr->field_1BC - 1;

    plr->hit_stop = frm->flag196_char2;
    plr->chrt->correction |= 4;

    enm->hit_stop = frm->flag196_enemy2;
    enm->field_1A4 = frm->velocity_x;
    enm->field_1A8 = frm->velocity_y;
    enm->field_4BA = 0x4000;

    plr->chrt->add_card_energy2(frm->card_energy2);

    if ( plr->chrt->field_554 > 0.0 )
        scn_p2[enm->player_index] -= (frm->card_energy2 / 2) * plr->chrt->field_554;


    enm->flip_to_enemy();
    scene_play_sfx(20);
    scene_add_effect_ibox(53, enm->dir);
    reset_ibox();
}

bool c_scene::sub_47B8F0(c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_c *plr_c = plr->chrt;

    if ( !enm->char_is_shock() )
        if ( !enm->field_4C0 )
            sub_478FC0(plr_c, enm);

    if ( !enm->field_575 )
    {
        float tmp = plr->sub_464270();
        enm->health -= tmp;

        if ( enm->health < 1 )
            enm->health = 1;

        if ( plr_c->field_550 > 0.0 )
            scn_p1[plr_c->player_index] += tmp * plr_c->field_550;

        if ( enm->field_558 > 0.0 )
            scn_p1[enm->player_index] -= tmp * enm->field_558;
    }

    if ( (frm->aflags & AF_GUARDCRUSH)  || plr->chrt->field_56D )
    {
        sub_47A980(plr, enm);
        return true;
    }

    if ( frm->sp_smval)
    {
        int16_t old_sp = enm->spell_energy;

        if ( frm->aflags & AF_UNK400000 )
            enm->spell_energy -= 2 * frm->sp_smval;
        else
            enm->spell_energy -= frm->sp_smval;

        if ( frm->attack_type == 0 )
            enm->spell_energy_stop = 60;
        else if ( frm->attack_type == 1 )
            enm->spell_energy_stop = 60;
        else if ( frm->attack_type >= 2 )
            enm->spell_energy_stop = 90;

        if ( enm->spell_energy <= 0 && enm->spell_energy < old_sp )
        {
            sub_47A980(plr, enm);
            return true;
        }
    }

    plr->field_190 = 2;
    plr->field_194 = plr->field_1BC - 1;
    plr->hit_stop = frm->flag196_char2;

    enm->hit_stop = frm->flag196_enemy2;
    enm->field_1A4 = frm->velocity_x;
    enm->field_1A8 = frm->velocity_y;
    plr_c->add_card_energy2(plr_c->field_54C * (float)frm->card_energy2);

    if ( plr_c->field_554 > 0.0 )
        scn_p2[enm->player_index] -= (frm->card_energy2 / 2.0) * plr_c->field_554;

    enm->flip_to_enemy();
    scene_play_sfx(21);

    scene_add_effect_ibox(51, enm->dir);
    reset_ibox();
    return false;
}

bool c_scene::sub_47BBA0(c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();

    switch ( enm->sub_469750(frm->aflags) )
    {
    case 0:
        return false;

    case 1:
        if ( sub_47B5A0(plr, enm) )
            enm->set_seq(143);
        else
            enm->set_seq(150 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 2:
        if ( sub_47B8F0(plr, enm))
            enm->set_seq(143);
        else
            enm->set_seq(159 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 3:
        if ( sub_47B5A0(plr, enm) )
            enm->set_seq(143);
        else
            enm->set_seq(154 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 4:
        if ( sub_47B8F0(plr, enm))
            enm->set_seq(143);
        else
            enm->set_seq(163 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 5:
        if ( sub_47B5A0(plr, enm) )
            enm->set_seq(145);
        else
            enm->set_seq(158);

        enm->reset_ofs();
        break;

    case 6:
        if ( sub_47B5A0(plr, enm) )
        {
            if (enm->char_on_ground_flag())
                enm->set_seq(143);
            else
                enm->set_seq(145);

            enm->reset_ofs();
        }
        break;

    default:
        enm->reset_ofs();
    }
    return true;
}

bool c_scene::sub_47AAA0(c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if ( ((frm2->fflags & FF_GRAZE) == 0 && enm->field_522 == 0 ) || (frm->aflags & AF_UNK800000) != 0 )
        return false;

    if ( enm->field_56C == 0 )
    {
        if ( (frm->aflags & AF_UNK400000) == 0 )
            return false;

        if ((frm->aflags & AF_UNK1000000) == 0 )
        {
            if (enm->spell_energy > 4 )
                enm->spell_energy_spend(4, 30);
            else
                return false;
        }

        plr->field_194 = plr->field_1BC - 1;
        plr->field_190 = 6;
    }
    else
    {
        scene_add_effect_ibox(201,enm->dir);

        if (frm->aflags & AF_UNK400000 )
        {
            if ( (frm->aflags & AF_UNK1000000)  && enm->spell_energy >= 10 )
                enm->spell_energy_spend(10, 60);
            else if ((frm->aflags & AF_UNK1000000) == 0  && enm->spell_energy > 30)
                enm->spell_energy_spend(4, 30);
            else
                return false;

            plr->field_194 = plr->field_1BC - 1;
            plr->field_190 = 6;
        }
        else if ( enm->spell_energy >= 50 )
            enm->spell_energy_spend(50, 60);
        else
            return false;
    }

    enm->field_4C6++;
    scene_add_effect_ibox(52, enm->dir);
    reset_ibox();
    return true;
}

bool c_scene::sub_47ABE0(c_meta *plr, c_meta *enm)
{
    char_frame *frm = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if (((frm->aflags & AF_UNK2000) && (frm2->fflags & FF_INV_AIRBORNE)) ||
            ((frm->aflags & AF_UNK4000) && (frm2->fflags & FF_INV_MID_BLOW)) ||
            ((frm->aflags & AF_KNOCK_BACK) && (frm2->fflags & FF_INV_LOW_BLOW)) ||
            ((frm->aflags & AF_UNK10000) && (frm2->fflags & FF_INV_SHOOT)))
    {
        plr->field_190 = 3;
        enm->field_190 = 3;
        reset_ibox();
        return true;
    }
    return false;
}

void c_scene::clear_action_keys()
{
    for (int8_t i=0; i<2; i++)
    {
        chrs[i]->clear_key(INP_A);
        chrs[i]->clear_key(INP_B);
        chrs[i]->clear_key(INP_C);
        chrs[i]->clear_key(INP_BC);
        chrs[i]->pres_comb = 0;
    }
}

void c_scene::clear_all_keys()
{
    for (int8_t i=0; i<2; i++)
    {
        chrs[i]->clear_key();
        chrs[i]->pres_comb = 0;
        chrs[i]->pres_move = 0;
    }
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
    return img_sp;
}

void scene_add_effect(c_meta *chr, int32_t idx, float x, float y, int8_t dir, int8_t order)
{
    img_sp->addeffect(chr, idx,x,y,dir, order);
}

void c_scene::scene_add_effect_ibox(int32_t idx, int8_t dir)
{
    float x = (ibox.x1 + ibox.x2) / 2.0;
    float y = -(ibox.y1 + ibox.y2) / 2.0;
    img_sp->addeffect(NULL,idx,x,y,dir,1);
}

void c_scene::set_start_flag(int8_t flag)
{
    field_8 = flag;
}


uint32_t scene_rand()
{
    return randomm.get_next();
}

uint32_t scene_rand_rng(uint32_t rng)
{
    return randomm.get_next_ranged(rng);
}

float scene_rand_rngf(uint32_t rng)
{
    return randomm.get_next_ranged(rng);
}


int32_t time_count = 0;

int32_t time_count_get()
{
    return time_count;
}

void time_count_inc()
{
    time_count++;
}

void time_count_set(int32_t st)
{
    time_count = st;
}


c_scene *scene_new_scene(background *bg, char_c *p1, char_c *p2)
{
    if (scn)
        delete scn;
    scn = new c_scene_one;
    scn->init(bg, p1, p2);
    return scn;
}

c_scene *scene_get_scene()
{
    return scn;
}

void scene_set_spell_img(uint8_t idx, gr_tex *img)
{
    scn->spell_images.spell_image[idx] = img;
}



