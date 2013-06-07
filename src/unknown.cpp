#include "global_types.h"
#include "framedata.h"
#include "scene.h"
#include "input.h"
#include "character_def.h"
#include "bullets.h"


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


void scene_set_ibox(c_scene *scn, frame_box *a2, frame_box *a3)
{
    int32_t min = 0;

    if ( a2->x1 >= a2->x2 )
    {
        if ( scn->ibox.x1 < a2->x2 )
            scn->ibox.x1 = a2->x2;
        min= a2->x1;
    }
    else
    {
        if ( scn->ibox.x1 < a2->x1 )
            scn->ibox.x1 = a2->x1;
        min = a2->x2;
    }
    if ( scn->ibox.x2 > min )
        scn->ibox.x2 = min;

    if ( a3->x1 >= a3->x2 )
    {
        if ( scn->ibox.x1 < a3->x2 )
            scn->ibox.x1 = a3->x2;
        min = a3->x1;
    }
    else
    {
        if ( scn->ibox.x1 < a3->x1 )
            scn->ibox.x1 = a3->x1;
        min = a3->x2;
    }
    if ( scn->ibox.x2 > min )
        scn->ibox.x2 = min;


    if ( scn->ibox.y1 < a2->y1 )
        scn->ibox.y1 = a2->y1;

    if ( scn->ibox.y1 < a3->y1 )
        scn->ibox.y1 = a3->y1;

    if ( scn->ibox.y2 > a2->y2 )
        scn->ibox.y2 = a2->y2;

    if ( scn->ibox.y2 > a3->y2 )
        scn->ibox.y2 = a3->y2;
}

void sub_479250(c_scene *scn, frame_box *a2, frame_box *a3, frame_box *a4, frame_box *a5)
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

    scene_set_ibox(scn, &b2, &b1);
}




bool sub_479720(c_scene *scn, frame_box *a1, frame_box *a2, frame_box *b1, frame_box *b2)
{
    if  ( (a1->x1 - b1->x2) < 0 && (b1->x1 - a1->x2) < 0 &&
            (b1->y1 + b2->y1 - a2->y2 - a1->y1) < 0 && (a1->y1 + a2->y1 - b2->y2 - b1->y1) < 0 )
    {
        if ( sub_479510(b1, b2, a1->x1, a1->y1) || sub_479510(a1, a2, b1->x1, b1->y1) )
        {
            sub_479250(scn, a1, a2, b1, b2);
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
            sub_479250(scn, a1, a2, b1, b2);
            return true;
        }
    }
    return false;
}



void sub_479200(c_scene *scn, frame_box *a1, frame_box *a2, frame_box *a3)
{
    frame_box tmp;

    tmp.x1 = a1->x1;
    tmp.x2 = a1->x2;
    tmp.y1 = a1->y1 + a2->y1;
    tmp.y2 = a1->y1 + a2->y2;

    scene_set_ibox(scn, &tmp, a3);
}

bool sub_479420(c_scene *scn, frame_box *a1, frame_box *a2, frame_box *a3)
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
        sub_479200(scn, a1, a2, a3);
        return true;
    }
    return false;
}


bool sub_479D50(c_scene *scn, c_meta *p1, c_meta *p2)
{
    bool hit = false;

    for (int32_t i=0; i< p1->hit_box_cnt; i++)
    {
        if (p1->hit_area_flags[i] != NULL)
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479720(scn, &p1->hit_area_2o[i], p1->hit_area_flags[i], &p2->hit_area_2o[j], p2->hit_area_flags[j]);
                else
                    hit |= sub_479420(scn, &p1->hit_area_2o[i], p1->hit_area_flags[i], &p2->hit_area_2o[j]);
            }
        }
        else
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479420(scn, &p2->hit_area_2o[j], p2->hit_area_flags[j], &p1->hit_area_2o[i]);
                else
                {
                    frame_box *fb1 = &p1->hit_area_2o[i];
                    frame_box *fb2 = &p2->hit_area_2o[j];

                    if ((fb2->x1 - fb1->x2) < 0 &&
                            (fb1->x1 - fb2->x2) < 0 &&
                            (fb1->y1 - fb2->y2) < 0 &&
                            (fb2->y1 - fb1->y2) < 0)
                    {
                        scene_set_ibox(scn, fb1, fb2);
                        hit |= true;
                    }
                }
            }
        }
    }
    return hit;
}

void set_mlist_hitflag(c_meta *plr, int8_t flag )
{
    c_meta *mt = plr;
    while (mt->parent_mlist)
        mt = mt->parent_mlist;

    mt->field_190 = flag;
    mt->field_194 = mt->field_1BC - 1;

    metalst *lst = &mt->childs;

    for (metalst_iter i= lst->begin(); i != lst->end(); i++)
    {
        c_meta *obj = *i;
        obj->field_190 = flag;
        obj->field_194 = obj->field_1BC - 1;
    }
}

bool sub_47AD60(c_scene *scn, c_meta *plr, c_meta *enm)
{

    if ( !sub_479D50(scn, plr, enm) )
        return false;

    if ( plr->get_cprior() == 0 )
    {
        if ( enm->get_cprior() != 0 )
        {
            if ( enm->get_cprior() < 0 )
            {
                set_mlist_hitflag(plr, 4);
            }
            else if ( enm->get_cprior() > 0 )
            {
                set_mlist_hitflag(plr, 5);
                set_mlist_hitflag(enm, 8);
            }
        }
        else
        {
            if (plr->get_prior() > enm->get_prior())
            {
                set_mlist_hitflag(plr, 4);
            }
            else if (plr->get_prior() < enm->get_prior())
            {
                set_mlist_hitflag(plr, 4);
            }
            else
            {
                set_mlist_hitflag(plr, 8);
                set_mlist_hitflag(enm, 8);
            }
        }
    }
    else if ( plr->get_cprior() > enm->get_cprior() )
    {
        if ( enm->get_cprior() != 0 )
        {
            set_mlist_hitflag(plr, 8);
            set_mlist_hitflag(enm, 4);
        }
        else
        {
            if ( plr->get_cprior() < enm->get_prior() )
            {
                set_mlist_hitflag(plr, 4);
            }
            else
            {
                set_mlist_hitflag(plr, 8);
                set_mlist_hitflag(enm, 5);
            }
        }
    }
    else if (plr->get_cprior() < enm->get_cprior())
    {
        set_mlist_hitflag(plr, 4);
        set_mlist_hitflag(enm, 8);
    }
    else //plr->get_cprior() == enm->get_cprior()
    {
        set_mlist_hitflag(plr, 4);
        set_mlist_hitflag(enm, 4);
    }
    scn->reset_ibox();
    return true;
}

bool sub_4699E0(char_c *chr)
{
    return chr->y > 0.0 && chr->field_4BA == 0 && char_is_shock(chr);
}

bool sub_479650(c_scene *scn, c_meta *p1, c_meta *p2)
{
    bool hit = false;

    if ( p2->pcoll_box != NULL )
    {
        for (int32_t i = 0; i < p1->atk_box_cnt; i++)
        {
            if (p1->atk_area_of[i] != NULL)
            {
                hit |= sub_479420(scn, &p1->atk_area_2o[i], p1->atk_area_of[i], p2->pcoll_box);
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
                    scene_set_ibox(scn, fb1, fb2);
                    hit |= true;
                }
            }
        }
    }
    return hit;
}

bool sub_479BC0(c_scene *scn, c_meta *p1, c_meta *p2)
{
    bool hit = false;

    for (int32_t i=0; i< p1->atk_box_cnt; i++)
    {
        if (p1->atk_area_of[i] != NULL)
        {
            for (int32_t j=0; j< p2->atk_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479720(scn, &p1->atk_area_2o[i], p1->atk_area_of[i], &p2->hit_area_2o[j], p2->hit_area_flags[j]);
                else
                    hit |= sub_479420(scn, &p1->atk_area_2o[i], p1->atk_area_of[i], &p2->hit_area_2o[j]);
            }
        }
        else
        {
            for (int32_t j=0; j< p2->hit_box_cnt; j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479420(scn, &p2->hit_area_2o[j], p2->hit_area_flags[j], &p1->atk_area_2o[i]);
                else
                {
                    frame_box *fb1 = &p1->atk_area_2o[i];
                    frame_box *fb2 = &p2->hit_area_2o[j];

                    if ((fb2->x1 - fb1->x2) < 0 &&
                            (fb1->x1 - fb2->x2) < 0 &&
                            (fb1->y1 - fb2->y2) < 0 &&
                            (fb2->y1 - fb1->y2) < 0)
                    {
                        scene_set_ibox(scn, fb1, fb2);
                        hit |= true;
                    }
                }
            }
        }
    }
    return hit;
}


bool sub_47ABE0(c_scene *scn, c_meta *plr, c_meta *enm)
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
        scn->reset_ibox();
        return true;
    }
    return false;
}

bool sub_47AAA0(c_scene *scn, c_meta *plr, char_c *enm)
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
                spell_energy_spend(enm, 4, 30);
            else
                return false;
        }

        plr->field_194 = plr->field_1BC - 1;
        plr->field_190 = 6;
    }
    else
    {
        scene_add_effect_ibox(scn,201,enm->dir);

        if (frm->aflags & AF_UNK400000 )
        {
            if ( (frm->aflags & AF_UNK1000000)  && enm->spell_energy >= 10 )
                spell_energy_spend(enm, 10, 60);
            else if ((frm->aflags & AF_UNK1000000) == 0  && enm->spell_energy > 30)
                spell_energy_spend(enm, 4, 30);
            else
                return false;

            plr->field_194 = plr->field_1BC - 1;
            plr->field_190 = 6;
        }
        else if ( enm->spell_energy >= 50 )
            spell_energy_spend(enm, 50, 60);
        else
            return false;
    }

    enm->field_4C6++;
    scene_add_effect_ibox(scn, 52, enm->dir);
    scn->reset_ibox();
    return true;
}

int32_t dword_8841B4 = 3; //HACK
int8_t dummy_block_type = 0;

int8_t sub_469750(char_c *plr, uint32_t enemu_aflags)
{
    if ( enemu_aflags & AF_U_HIT )
        return 0;
    if ( plr->field_4AA )
        return 0;

    char_frame *frm = plr->get_pframe();

    if ( frm->fflags & FF_GUARD2 )
        return 6;
    if ( !(frm->fflags & FF_GUARDCANC) )
        return 0;

    if ( !char_is_block_knock(plr) )
    {
        if ( plr->input_function )
        {
            if ( plr->field_578 == 0  && ((plr->enemy->x - plr->x) * plr->gX(1) > 0  || plr->gX(1) == 0))
                return 0;
        }
        else if ( plr->controlling_type == 3 ) //CHAR_CTRL_TRAIN_DUMMY
        {
            plr->setgY(0);
            plr->setgX(0);
            /*if ( practice_params->field_C <= 0 ) //HACK
            {
                if ( plr->field_578 == 0  && ((plr->enemy->x - plr->x) * plr->gX(1) > 0  || plr->gX(1) == 0))
                    return 0;
            }*/
        }
        else if ( dword_8841B4 == 1 && scene_rand_rng(100) >= 95 )
        {
            if ( plr->field_578 == 0  && ((plr->enemy->x - plr->x) * plr->gX(1) > 0  || plr->gX(1) == 0))
                return 0;
        }
        else if ( dword_8841B4 == 0 && scene_rand_rng(100) >= 70 )
        {
            if ( plr->field_578 == 0  && ((plr->enemy->x - plr->x) * plr->gX(1) > 0  || plr->gX(1) == 0))
                return 0;
        }
        else
        {
            if ( plr->enemy->x - plr->x <= 0.0 )
                plr->setgX(1);
            else
                plr->setgX(-1);

            if ( plr->controlling_type == 3 )
            {
                if ( /*practice_params->dummy_block_type*/ dummy_block_type == 2 ) // HACK
                    plr->setgY(0);
                else if ( dummy_block_type == 3 )
                    plr->setgY(1);
                else
                    plr->setgY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);
            }
            else
                plr->setgY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);

            if ( plr->field_578 == 0  && ((plr->enemy->x - plr->x) * plr->gX(1) > 0  || plr->gX(1) == 0))
                return 0;
        }
    }
    else
    {
        if ( plr->input_function )
        {
            if ( plr->gX(1) == 0 && (enemu_aflags & AF_GUARDCRUSH) )
                return 0;
        }
        else if ( plr->controlling_type == 3 )
        {
            if ( dummy_block_type == 2 )
                plr->setgY(0);
            else if ( dummy_block_type == 3 )
                plr->setgY(1);
            else
                plr->setgY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);
        }
        else
            plr->setgY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);
    }

    if ( !char_on_ground_flag(plr) || frm->fflags & FF_AIRBORNE )
    {
        return (enemu_aflags & AF_AIR_HIT) == 0 ? 0 : 5;
    }
    else
    {
        if ( plr->gY() <= 0 )
        {
            if ( enemu_aflags & AF_MID_HIT )
                return 1;
            else
                return  (enemu_aflags & AF_UNK40) == 0 ? 2 : 0;
        }
        else
        {
            if ( enemu_aflags & AF_LOW_HIT )
                return 3;
            else
                return (enemu_aflags & AF_UNK40) == 0 ? 4 : 0;
        }
    }
    return 0;
}

void sub_478FC0(char_c *plr, char_c *enm)
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

double sub_4636B0(c_meta *plr)
{

    float dmg = 0;

    char_c * chr = plr->chrt;
    char_c * enm = plr->enemy;

    dmg = chr->field_530 * enm->field_534 * chr->combo_rate;

    if ( enm->field_1B4 >= 0 )
    {
        if ( enm->max_health > enm->field_1B4 )
            dmg *= (enm->field_1B4 / enm->max_health * 0.3 + 0.7);
    }
    else
    {
        dmg *= 0.7;
    }

    /*if ( plr->field_18C >= 0 ) //Hack
    {
      if ( plr->field_18C < 32 )
        dmg *= (*(&chr->field_6A4 + plr->field_18C) / 10.0 + 1.0);
    }*/

    uint32_t aflgs = plr->get_pframe()->aflags;

    if ( aflgs & AF_UNK1000 )
        dmg *= chr->field_544;
    if ( aflgs & AF_UNK800 )
        dmg *= chr->field_548;

    if ( chr->correction & 1 )
        dmg *= 0.8;
    if ( chr->correction & 2 )
        dmg *= 0.8;
    if ( chr->correction & 4 )
        dmg *= 0.8;
    if ( chr->correction & 8 )
        dmg *= 0.85;
    if ( chr->correction & 0x10 )
        dmg *= 0.925;
    return dmg;
}


float sub_464270(c_meta *plr)
{
    return plr->get_pframe()->health_smval * sub_4636B0(plr);
}

void sub_47A980(c_scene *scn, c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();

    if ( !plr->chrt->field_56D )
      crash_spell_borders(enm, 1);

    sub_478FC0(plr->chrt, enm);

    plr->field_190 = 2;
    plr->field_194 = plr->field_1BC - 1;

    plr->hit_stop = frm->flag196_char2;
    plr->chrt->correction |= 4;

    enm->hit_stop = frm->flag196_enemy2;
    enm->field_1A4 = frm->velocity_x;
    enm->field_1A8 = frm->velocity_y;
    enm->field_4BA = 0x4000;

    add_card_energy2(plr->chrt, frm->card_energy2);

    if ( plr->chrt->field_554 > 0.0 )
        scn->scn_p2[enm->player_index] -= (frm->card_energy2 / 2) * plr->chrt->field_554;


    enm->flip_to_enemy();
    scene_play_sfx(20);
    scene_add_effect_ibox(scn, 53, enm->dir);
    scn->reset_ibox();
}

bool sub_47B5A0(c_scene *scn, c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    if ( !char_is_shock(enm) )
    {
        if ( !enm->field_4C0 )
            sub_478FC0(plr->chrt, enm);
    }
    if ( !enm->field_575 )
    {
        double tmp = sub_464270(plr);

        enm->health -= tmp;
        if ( enm->health < 1 )
            enm->health = 1;

        char_c * plr_c = plr->chrt;
        if ( plr_c->field_550 > 0.0 )
            scn->scn_p1[plr_c->player_index] += tmp * plr_c->field_550;

        char_c * enm_c = enm->chrt;
        if ( enm_c->field_558 > 0.0 )
            scn->scn_p1[enm_c->player_index] -= tmp * plr_c->field_558;
    }
    if ( frm->sp_smval )
    {

        int16_t old_spe = enm->spell_energy;

        if ( frm->aflags & AF_UNK400000 )
        {
            if ( sub_469750(enm, frm->aflags) == 5 )
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
            if ( sub_469750(enm, frm->aflags) == 5 )
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
            sub_47A980(scn, plr, enm);
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

    add_card_energy2(plr_c, plr_c->field_54C * (float)frm->card_energy2);

    if ( plr_c->field_554 > 0.0 )
        scn->scn_p2[enm->player_index] -= (plr_c->field_54C * frm->card_energy2 / 2) * plr_c->field_554;

    enm->flip_to_enemy();
    scene_play_sfx(20);
    scene_add_effect_ibox(scn, 50, enm->dir);
    scn->reset_ibox();
    return false;
}

bool sub_47B8F0(c_scene *scn, c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_c *plr_c = plr->chrt;

    if ( !char_is_shock(enm) )
        if ( !enm->field_4C0 )
            sub_478FC0(plr_c, enm);

    if ( !enm->field_575 )
    {
        float tmp = sub_464270(plr);
        enm->health -= tmp;

        if ( enm->health < 1 )
            enm->health = 1;

        if ( plr_c->field_550 > 0.0 )
            scn->scn_p1[plr_c->player_index] += tmp * plr_c->field_550;

        if ( enm->field_558 > 0.0 )
            scn->scn_p1[enm->player_index] -= tmp * enm->field_558;
    }

    if ( (frm->aflags & AF_GUARDCRUSH)  || plr->chrt->field_56D )
    {
        sub_47A980(scn, plr, enm);
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
            sub_47A980(scn, plr, enm);
            return true;
        }
    }

    plr->field_190 = 2;
    plr->field_194 = plr->field_1BC - 1;
    plr->hit_stop = frm->flag196_char2;

    enm->hit_stop = frm->flag196_enemy2;
    enm->field_1A4 = frm->velocity_x;
    enm->field_1A8 = frm->velocity_y;
    add_card_energy2(plr_c, plr_c->field_54C * (float)frm->card_energy2);

    if ( plr_c->field_554 > 0.0 )
        scn->scn_p2[enm->player_index] -= (frm->card_energy2 / 2.0) * plr_c->field_554;

    enm->flip_to_enemy();
    scene_play_sfx(21);

    scene_add_effect_ibox(scn, 51, enm->dir);
    scn->reset_ibox();
    return false;
}

bool sub_47BBA0(c_scene *scn, c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();

    switch ( sub_469750(enm, frm->aflags) )
    {
    case 0:
        return false;

    case 1:
        if ( sub_47B5A0(scn, plr, enm) )
            enm->set_seq(143);
        else
            enm->set_seq(150 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 2:
        if ( sub_47B8F0(scn, plr, enm))
            enm->set_seq(143);
        else
            enm->set_seq(159 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 3:
        if ( sub_47B5A0(scn, plr, enm) )
            enm->set_seq(143);
        else
            enm->set_seq(154 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 4:
        if ( sub_47B8F0(scn, plr, enm))
            enm->set_seq(143);
        else
            enm->set_seq(163 + frm->attack_type);

        enm->reset_ofs();
        break;

    case 5:
        if ( sub_47B5A0(scn, plr, enm) )
            enm->set_seq(145);
        else
            enm->set_seq(158);

        enm->reset_ofs();
        break;

    case 6:
        if ( sub_47B5A0(scn, plr, enm) )
        {
            if (char_on_ground_flag(enm))
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


int32_t sub_464240(c_meta *plr)
{
    return (sub_4636B0(plr) * plr->get_pframe()->damage);
}

void sub_47A060(c_scene *scn, c_meta *plr, char_c *enm)
{
//    char_class_vars *_enemy; // esi@1
//    char_class_vars *_character; // edi@1
//    frame_head *v5; // ebp@1
//    double v6; // st7@6
//    DWORD v7; // eax@7
//    double v8; // st7@9
//    __int16 v9; // cx@14
//    char v10; // bl@17
//    __int16 v11; // ax@23
//    unsigned __int8 v12; // zf@25
//    char v13; // sf@25
//    unsigned __int8 v14; // of@25
//    FFFLAGS v15; // ecx@35
//    __int16 v16; // ax@36
//    __int16 v17; // ax@52
//    char_class_vars *v18; // eax@55
//    signed int i; // ebx@57
//    double v20; // st7@64
//    __int64 v21; // qax@65
//    __int16 v22; // ax@66
//    signed __int16 v23; // bx@66
//    signed int v24; // eax@68
//    char_class_vars *v25; // ecx@68
//    double v26; // st7@68
//    char *v27; // ST20_4@69
//    double v28; // st6@71
//    char_class_vars *v29; // ecx@71
//    char *v30; // ST20_4@72
//    char_class_vars *v31; // ecx@73
//    char *v32; // ST20_4@74
//    scene_class_vars *v33; // ebx@76
//    __int16 v34; // ax@77
//    char v36; // [sp+13h] [bp-9h]@1
//    scene_class_vars *thisa; // [sp+14h] [bp-8h]@1
//    char a2a; // [sp+20h] [bp+4h]@13
//    int a2b; // [sp+20h] [bp+4h]@68
//    signed int enemya; // [sp+24h] [bp+8h]@13

    //v5 = plr->current_frame_params2?;
    //thisa = this;

    int16_t dmg = 0;

    char_frame *frm  = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if ( !char_is_shock(enm) )
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
        /*if ( get_game_type() == 8 )
        {
          if ( !practice_params->dummy_counter )
          {
            if ( plr->chrt->combo_count == 0)
              v10 = 1;
          }
        }*/

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
            if (!char_on_ground_flag(enm) || (frm2->fflags & FF_AIRBORNE) || frm->fall_seq2 != 0)
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


    if ( !char_is_shock(enm) )
    {
        for (int8_t i = 0; i <= atype && i < 3; ++i )
            scene_add_effect_ibox(scn, 201, enm->dir);

        if ( atype >= 2 )
            scene_add_effect_ibox(scn, 201, enm->dir);
    }

    plr->field_194 = plr->field_1BC - 1;
    plr->hit_stop = frm->flag196_char;
    enm->hit_stop = frm->flag196_enemy;
    if ( v36 )
    {
        plr->chrt->correction |= 0x20u;
        enm->field_1A4 = frm->velocity_x * 1.5;
        enm->field_1A8 = frm->velocity_y * 1.5;
        /*if ( weather == 16 )
        {
            weather_time = 3 * weather_time / 4;
            enm->field_4BA = (2 * v5->untech) * plr->selft_pointer1?->combo_rate;
        }
        else*/
        {
            enm->field_4BA = (3 * frm->untech / 2) * plr->chrt->combo_rate;
        }
        //v22 = sub_464240(plr);
        //v23 = (plr->field_198 * (((5726623064i64 * v22) >> 32) + (((5726623064i64 * v22) >> 32) >> 31)));
        dmg = sub_464240(plr);
        scene_add_effect_ibox(scn, 54, plr->dir);
    }
    else
    {
        enm->field_1A4 = frm->velocity_x;
        enm->field_1A8 = frm->velocity_y;
        enm->field_4BA = (plr->chrt->combo_rate * frm->untech);

        dmg = sub_464240(plr);
    }
    add_card_energy2(plr->chrt, plr->chrt->field_54C * (float)frm->card_energy);
    if ( plr->chrt->field_554 <= 0.0 )
    {
        add_card_energy2(enm, dmg / 20);
    }
    else
    {
        /*v27 = (&thisa->field_7C + enm->player_index);
        *v27 -= (plr->chrt->field_554 * energ);*/
    }

    plr->chrt->combo_count++;

    plr->chrt->combo_rate *= (frm->proration + plr->chrt->field_540 * (1000.0 - frm->proration)) / 1000.0;

    plr->chrt->correction |= frm->unk20;

    plr->chrt->combo_damage += dmg;

    if ( plr->chrt->field_550 > 0 )
    {
        // v30 = (&thisa->field_74 + plr->chrt->player_index);
        // *v30 += (plr->chrt->field_550 * dmg);
    }

    if ( plr->chrt->field_558 > 0 )
    {
        // v32 = (&thisa->field_74 + plr->selft_pointer1?->player_index);
        // *v32 -= (dmg * plr->chrt->field_558);
    }

    //*&enm->field_188 += (enm->field_55C * dmg);
    if ( enm->field_575 == 0 )
    {
        enm->health -= dmg;
        if ( enm->health <= 0 )
        {
            enm->health = 0;

            scn->func11(enm);

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

    scene_add_effect_ibox(scn,frm->unk19, plr->dir);
    scn->reset_ibox();
    scene_play_sfx(frm->hit_sfx);
}


bool sub_47BD80(c_scene *scn, c_meta *plr, char_c *enm)
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
        if (!sub_479650(scn, plr, enm))
            return false;
    }
    else
    {
        if (!sub_479BC0(scn, plr, enm))
            return false;
    }

    enm->field_4AC = (frm->aflags & AF_UNK400000) == 0; //~(aflags >> 22) & 1
    if ( !sub_47ABE0(scn, plr, enm) )
    {
        if ( !sub_47AAA0(scn, plr, enm) )
        {
            if ( !sub_47BBA0(scn, plr, enm) )
                sub_47A060(scn, plr, enm);
        }
    }
    return true;
}

void sub_4647B0(c_meta *plr, c_meta *enm)
{
    plr->field_190 = enm->field_190;
    plr->hit_stop = enm->hit_stop;
    plr->field_194 = plr->field_1BC - (enm->field_1BC - enm->field_194);

    metalst *lst = &plr->childs;

    for (metalst_iter i = lst->begin(); i != lst->end(); i++)
    {
        c_meta *mt = *i;

        mt->field_190 = enm->field_190;
        mt->hit_stop = enm->hit_stop;
        mt->field_194 = mt->field_1BC - (enm->field_1BC - enm->field_194);
    }
}


void  sub_47BE70(c_scene *scn, c_meta *plr, char_c *enm)
{
    if ( plr->chrt->field_575 == 0 && enm->field_575 != 2 )
    {
        if ( !sub_4699E0(enm) && enm->damage_limit < 100 )
        {
            char_frame *frm = plr->get_pframe();
            if (plr != enm || (frm->aflags & AF_HITSALL) == 0 || plr->enemy->field_575 == 0)
            {
                if (!plr->childs.empty())
                {
                    if (sub_47BD80(scn, plr, enm))
                        sub_4647B0(plr, plr);
                    else
                    {
                        metalst *lst = &plr->childs;
                        for(metalst_iter i = lst->begin(); i != lst->end(); i++)
                            if (sub_47BD80(scn, *i, enm))
                                sub_4647B0(plr, *i);
                    }
                }
                else
                {
                    sub_47BD80(scn, plr, enm);
                }
            }
        }
    }
}

void sub_464890(c_meta *plr, c_meta *enm)
{

    c_meta *mt = plr;
    while (mt->parent_mlist)
        mt = mt->parent_mlist;

    plr->dir *= -1;
    plr->chrt = enm->chrt;
    plr->field_1A0++;
    plr->enemy = enm->enemy;

    metalst *lst = &plr->childs;

    for ( metalst_iter i = lst->begin(); i != lst->end(); i++)
    {
        c_meta *mt = *i;

        mt->dir *= -1;
        mt->chrt = enm->chrt;
        mt->enemy = enm->enemy;
        mt->field_1A0++;
    }
}

bool sub_47AD00(c_scene *scn, c_meta *plr, c_meta *enm)
{
    if (plr->chrt != enm->chrt)
    {
        if ( !(plr->get_pframe()->fflags & FF_UNK80000) || !sub_479D50(scn, plr, enm))
            return false;
        sub_464890(enm, plr);
        plr->field_1A0++;
        scn->reset_ibox();
    }
    return true;
}

bool sub_47C080(c_scene *scn, c_meta *plr, c_meta *enm)
{
    char_frame *frm2 = enm->get_pframe();

    if ( !(frm2->aflags & AF_UNK20000) && !enm->field_1A1 && (frm2->aflags & AF_UNK400000))
    {
        if (plr->childs.empty())
        {
            return sub_47AD00(scn, plr, enm);
        }
        else
        {
            if (sub_47AD00(scn, plr, enm))
                return true;

            metalst *lst = &plr->childs;

            for (metalst_iter bl = lst->begin(); bl != lst->end(); bl++)
            {
                if (sub_47AD00(scn, *bl, enm))
                    return true;
            }
        }
    }
    return false;
}

void scn_char_ss2(c_meta *chr);

char sub_47AC70(c_scene *scn, c_meta *plr, c_meta *enm)
{
    if ( sub_479BC0(scn, plr, enm) )
    {
        char_frame *frm = plr->get_pframe();
        plr->field_194 = plr->field_1BC - 1;
        plr->field_190 = 9;
        plr->hit_stop = frm->flag196_char;
        enm->health -= frm->damage;
        scene_play_sfx(frm->hit_sfx);
        scene_add_effect_ibox(scn, frm->unk19, plr->dir);
        scn->reset_ibox();
        return true;
    }

    return false;
}

void sub_47BFA0(c_scene *scn, c_meta *plr, c_meta *enm)
{
    if ( (enm->get_pframe()->fflags & FF_CH_ON_HIT) && enm->field_1AC )
    {
        if ( !plr->childs.empty() )
        {
            if ( sub_47AC70(scn, plr, enm) )
                sub_4647B0(plr, plr);
            else
            {
                metalst *lst = &plr->childs;

                for (metalst_iter i = lst->begin(); i != lst->end(); i++)
                    if ( sub_47AC70(scn, *i, enm) )
                    {
                        sub_4647B0(plr, *i);
                        break;
                    }
            }
        }
        else
            sub_47AC70(scn,plr,enm);
    }
}

void sub_47C430(c_scene *scn)
{
    for (int8_t i=0; i<2; i++)
    {
        char_c *chr = scn->chrs[i];

        metalst *lst1 = &scn->list3[chr->player_index];

        for(metalst_iter m1 = lst1->begin(); m1 != lst1->end(); m1++)
        {
            c_meta *mt1 = *m1;

            if (mt1->field_190 ==0 && mt1->field_194 > 0)
            {
                metalst *lst2 = &scn->list2[chr->enemy->player_index];
                for(metalst_iter m2 = lst2->begin(); m2 != lst2->end(); m2++)
                {
                    c_meta *mt2 = *m2;

                    if ( !sub_47C080(scn, mt1, mt2))
                        sub_47BFA0(scn, mt1, mt2);
                }

                if (mt1->get_pframe()->aflags & AF_HITSALL)
                {
                    metalst *lst2 = &scn->list2[chr->player_index];
                    for(metalst_iter m2 = lst2->begin(); m2 != lst2->end(); m2++)
                    {
                        c_meta *mt2 = *m2;

                        if ( !sub_47C080(scn, mt1, mt2))
                            sub_47BFA0(scn, mt1, mt2);
                    }
                }
            }
        }
    }
}


void sub_47C180(c_scene *scn)
{
    for (int8_t c=0; c < 2; c++) //Bullets to own bullets hit, if AF_HITSALL
    {
        metalst *lst = &scn->list2[c];

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
                            sub_47AD60(scn,mt,mt2);
                }

            }
        }
    }

    metalst *lst1 = &scn->list2[0];
    metalst *lst2 = &scn->list2[1];

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
                    sub_47AD60(scn,mt,mt2);
            }
        }
    }
}
