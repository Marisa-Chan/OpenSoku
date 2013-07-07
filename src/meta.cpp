#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "framedata.h"
#include "meta.h"
#include "character_def.h"


c_meta::c_meta(char_graph *_pgp)
{
    pgp  = _pgp;

    //field_154 = NULL; //HACK
    //field_134 = 0;    //HACK
    has_shadow = 0;
    atk_area_of[0] = NULL;
    atk_area_of[1] = NULL;
    atk_area_of[2] = NULL;
    atk_area_of[3] = NULL;
    atk_area_of[4] = NULL;
    hit_area_flags[0] = NULL;
    hit_area_flags[1] = NULL;
    hit_area_flags[2] = NULL;
    hit_area_flags[3] = NULL;
    hit_area_flags[4] = NULL;
    hit_area_flags[5] = NULL;
    atk_box_cnt = 0;
    hit_box_cnt = 0;
    cust_box  = NULL;
    field_190 = 0;
    field_194 = 0;
    hit_stop = 0;
    field_1A0 = 0;
    field_1A1 = 0;
    field_188 = 0;
    field_18C = -1;
    field_1AC = 1;
    chrt = NULL;
    enemy = NULL;
    parent_mlist = NULL;

    //additional params init
    field_1A2 = 0;
}

c_meta::c_meta():
    c_meta(NULL)
{
}

void c_meta::set_seq(uint32_t idx)
{
    // printf("%d\n",idx);
    if (pgp)
        if (pgp->get_seq(idx))
        {
            index = idx;
            sprite.set_seq(pgp->get_seq(idx));
        }
}

seq *c_meta::get_seq(uint32_t idx)
{
    if (pgp)
        return pgp->get_seq(idx);
    else
        return NULL;
}

bool c_meta::process(bool ignore_loop)
{
    return sprite.process(ignore_loop);
}

bool c_meta::next_frame(bool ignore_loop)
{
    return sprite.next_frame(ignore_loop);
}

bool c_meta::next_subseq()
{
    return sprite.next_subseq();
}

bool c_meta::set_subseq(uint32_t idx)
{
    return sprite.set_subseq(idx);
}

void c_meta::reset_seq()
{
    sprite.reset_seq();
}

void c_meta::set_frame(uint32_t frm)
{
    sprite.set_frame(frm);
}



uint32_t c_meta::get_subseq()
{
    return sprite.get_subseq();
}
uint32_t c_meta::get_frame()
{
    return sprite.get_frame();
}
uint32_t c_meta::get_frame_time()
{
    return sprite.get_frame_time();
}
uint32_t c_meta::get_elaps_frames()
{
    return sprite.get_elaps_frames();
}

char_frame * c_meta::get_pframe()
{
    return sprite.get_pframe();
}


uint32_t c_meta::get_seq()
{
    return index;
}

uint16_t c_meta::get_prior()
{
    return sprite.get_prior();
}
uint16_t c_meta::get_cprior()
{
    return sprite.get_cprior();
}

uint16_t c_meta::get_cprior(uint32_t idx)
{
    if (pgp)
        return pgp->get_cprior(idx);
    else
        return 0xFFFF;
}
uint16_t c_meta::get_prior(uint32_t idx)
{
    if (pgp)
        return pgp->get_prior(idx);
    else
        return 0xFFFF;
}

void c_meta::draw_shadow(shd_trans */*trans*/, gr_shader */*shader*/)
{
}

void c_meta::draw(gr_shader */*shader*/)
{
}



void c_meta::set_mlist_hitflag(int8_t flag )
{
    c_meta *mt = this;
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

int32_t c_meta::sub_464240()
{
    return (sub_4636B0() * get_pframe()->damage);
}

float c_meta::sub_464270()
{
    return get_pframe()->health_smval * sub_4636B0();
}

void c_meta::sub_4647B0( c_meta *enm)
{
    field_190 = enm->field_190;
    hit_stop = enm->hit_stop;
    field_194 = field_1BC - (enm->field_1BC - enm->field_194);

    metalst *lst = &childs;

    for (metalst_iter i = lst->begin(); i != lst->end(); i++)
    {
        c_meta *mt = *i;

        mt->field_190 = enm->field_190;
        mt->hit_stop = enm->hit_stop;
        mt->field_194 = mt->field_1BC - (enm->field_1BC - enm->field_194);
    }
}

void c_meta::sub_464890(c_meta *enm)
{

    c_meta *mt = this;
    while (mt->parent_mlist)
        mt = mt->parent_mlist;

    dir *= -1;
    chrt = enm->chrt;
    field_1A0++;
    enemy = enm->enemy;

    metalst *lst = &childs;

    for ( metalst_iter i = lst->begin(); i != lst->end(); i++)
    {
        c_meta *mt = *i;

        mt->dir *= -1;
        mt->chrt = enm->chrt;
        mt->enemy = enm->enemy;
        mt->field_1A0++;
    }
}

void c_meta::box_coll_get(box_box *box)
{
    frame_box *bx = get_pframe()->box_coll;
    if (dir == 1)
    {
        box->x1 = x + bx->x1;
        box->x2 = x + bx->x2;
    }
    else
    {
        box->x1 = x - bx->x2;
        box->x2 = x - bx->x1;
    }
    box->y1 = bx->y1 - y;
    box->y2 = bx->y2 - y;
}

double c_meta::sub_4636B0()
{

    float dmg = 0;

    char_c * chr = chrt;
    char_c * enm = enemy;

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

    uint32_t aflgs = get_pframe()->aflags;

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

void c_meta::frame_box_fullflip( frame_box *src, frame_box *dst)
{
    if (dir == 1)
    {
        dst->x1 = src->x1 + ceil(x);
        dst->x2 = src->x2 + ceil(x);
        dst->y1 = src->y1 - ceil(y);
        dst->y2 = src->y2 - ceil(y);
    }
    else
    {
        dst->x1 = ceil(x) - src->x2;
        dst->x2 = ceil(x) - src->x1;
        dst->y1 = src->y2 - ceil(y);
        dst->y2 = src->y1 - ceil(y);
    }
}

void frame_box_move_rotate(frame_box *src, int16_t angle, int16_t x_c, int16_t y_c, frame_box *dst1, frame_box *dst2)
{
    float sin_ = sin_deg(angle);
    float cos_ = cos_deg(angle);

    if ( sin_ < 0.0 )
    {
        if ( cos_ < 0.0 )
        {
            dst1->x1 = x_c + ((src->x2 - x_c) * cos_) - ((src->y1 - y_c) * sin_);
            dst1->y1 = y_c + ((src->x2 - x_c) * sin_) + ((src->y1 - y_c) * cos_);
            dst1->x2 = x_c + ((src->x1 - x_c) * cos_) - ((src->y2 - y_c) * sin_);
            dst1->y2 = y_c + ((src->x1 - x_c) * sin_) + ((src->y2 - y_c) * cos_);
            dst2->x1 = -((src->y2 - src->y1) * sin_);
            dst2->y1 = (src->y2 - src->y1) * cos_;
            dst2->x2 = -(cos_ * (src->x2 - src->x1));
            dst2->y2 = -(sin_ * (src->x2 - src->x1));
        }
        else
        {
            dst1->x1 = x_c + ((src->x1 - x_c) * cos_) - ((src->y1 - y_c) * sin_);
            dst1->y1 = y_c + ((src->x1 - x_c) * sin_) + ((src->y1 - y_c) * cos_);
            dst1->x2 = x_c + ((src->x2 - x_c) * cos_) - ((src->y2 - y_c) * sin_);
            dst1->y2 = y_c + ((src->x2 - x_c) * sin_) + ((src->y2 - y_c) * cos_);
            dst2->x1 = (src->x2 - src->x1) * cos_;
            dst2->y1 = (src->x2 - src->x1) * sin_;
            dst2->x2 = -(sin_ * (src->y2 - src->y1));
            dst2->y2 = cos_ * (src->y2 - src->y1);
        }
    }
    else
    {
        if ( cos_ < 0.0 )
        {
            dst1->x1 = x_c + ((src->x2 - x_c) * cos_) - ((src->y2 - y_c) * sin_);
            dst1->y1 = y_c + ((src->y2 - y_c) * cos_) + ((src->x2 - x_c) * sin_);
            dst1->x2 = x_c + ((src->x1 - x_c) * cos_) - ((src->y1 - y_c) * sin_);
            dst1->y2 = y_c + ((src->y1 - y_c) * cos_) + ((src->x1 - x_c) * sin_);
            dst2->x1 = -((src->x2 - src->x1) * cos_);
            dst2->y1 = -((src->x2 - src->x1) * sin_);
            dst2->x2 = sin_ * (src->y2 - src->y1);
            dst2->y2 = -(cos_ * (src->y2 - src->y1));
        }
        else
        {
            dst1->x1 = x_c + ((src->x1 - x_c) * cos_) - ((src->y2 - y_c) * sin_);
            dst1->y1 = y_c + ((src->y2 - y_c) * cos_) + ((src->x1 - x_c) * sin_);
            dst1->x2 = x_c + ((src->x2 - x_c) * cos_) - ((src->y1 - y_c) * sin_);
            dst1->y2 = y_c + ((src->y1 - y_c) * cos_) + ((src->x2 - x_c) * sin_);
            dst2->x1 = (src->y2 - src->y1) * sin_;
            dst2->y1 = -((src->y2 - src->y1) * cos_);
            dst2->x2 = cos_ * (src->x2 - src->x1);
            dst2->y2 = sin_ * (src->x2 - src->x1);
        }
    }
}

void c_meta::frame_box_flip(frame_box *src, frame_box *dst)
{
    if ( dir == 1 )
    {
        dst->x1 = ceil(x) + src->x1;
        dst->x2 = ceil(x) + src->x2;
    }
    else
    {
        dst->x1 = ceil(x) - src->x2;
        dst->x2 = ceil(x) - src->x1;
    }
    dst->y1 = src->y1 - ceil(y);
    dst->y2 = src->y2 - ceil(y);
}

void c_meta::set_custom_box(int32_t x1, int32_t y1, int32_t x2, int32_t y2, float angl, int32_t dx, int32_t dy)
{
    if (!cust_box)
        cust_box = new custom_box;

    if (x1 <= x2)
    {
        cust_box->box.x1 = x1;
        cust_box->box.x2 = x2;
    }
    else
    {
        cust_box->box.x1 = x2;
        cust_box->box.x2 = x1;
    }

    if (y1 <= y2)
    {
        cust_box->box.y1 = y1;
        cust_box->box.y2 = y2;
    }
    else
    {
        cust_box->box.y1 = y2;
        cust_box->box.y2 = y1;
    }

    cust_box->angle = angl;
    cust_box->c_x = dx;
    cust_box->c_y = dy;
}



void c_meta::scn_char_ss2()
{
    field_1B4 = health;
    field_1B8 = field_190;
    field_1BC = field_194;
    field_1C8 = get_seq();
    field_1CA = dir;

    char_frame *frm = get_pframe();

    atk_box_cnt = frm->box_atk.size();
    hit_box_cnt = frm->box_hit.size();

    for(int32_t i=0; i<atk_box_cnt; i++)
    {
        if (frm->box_unk_atk[i] != NULL || frm->fflags & FF_UNK400000)
            atk_area_of[i] = &atk_area_2o[5 + i];
        else
            atk_area_of[i] = NULL;
    }

    for(int32_t i=0; i<hit_box_cnt; i++)
    {
        if (frm->fflags & FF_UNK800000)
            hit_area_flags[i] = &atk_area_2o[10 + i];
        else
            hit_area_flags[i] = NULL;
    }

    for(int32_t i=0; i<atk_box_cnt; i++)
    {
        if (frm->box_unk_atk[i] != NULL)
        {
            frame_box_fullflip(&frm->box_atk[i],&atk_area_2o[i]);
            frame_box *bx = atk_area_of[i];
            if (dir < 0)
            {
                bx->x1 = frm->box_unk_atk[i]->x2;
                bx->y1 = -frm->box_unk_atk[i]->y2;
                bx->x2 = frm->box_unk_atk[i]->x1;
                bx->y2 = -frm->box_unk_atk[i]->y1;
            }
            else
            {
                bx->x1 = frm->box_unk_atk[i]->x1;
                bx->y1 = frm->box_unk_atk[i]->y1;
                bx->x2 = frm->box_unk_atk[i]->x2;
                bx->y2 = frm->box_unk_atk[i]->y2;
            }
        }
        else if (frm->fflags & FF_UNK400000)
        {
            frame_box tmp,tmp2;
            frame_box_move_rotate(&frm->box_atk[i],angZ,x_off,-y_off,&tmp,&tmp2);
            frame_box_fullflip(&tmp,&atk_area_2o[i]);

            frame_box *bx = atk_area_of[i];
            if ( dir < 0 )
            {
                bx->x1 = tmp2.x2;
                bx->y1 = -tmp2.y2;
                bx->x2 = tmp2.x1;
                bx->y2 = -tmp2.y1;
            }
            else
            {
                bx->x1 = tmp2.x1;
                bx->y1 = tmp2.y1;
                bx->x2 = tmp2.x2;
                bx->y2 = tmp2.y2;
            }
        }
        else
        {
            frame_box_flip(&frm->box_atk[i],&atk_area_2o[i]);
        }
    }

    if ( frm->fflags & FF_UNK800000 )
    {
        for(int32_t i=0; i<hit_box_cnt; i++)
        {
            frame_box tmp,tmp2;
            frame_box_move_rotate(&frm->box_hit[i],angZ,x_off,-y_off,&tmp,&tmp2);
            frame_box_fullflip(&tmp,&hit_area_2o[i]);

            frame_box *bx = hit_area_flags[i];
            if ( dir < 0 )
            {
                bx->x1 = tmp2.x2;
                bx->y1 = -tmp2.y2;
                bx->x2 = tmp2.x1;
                bx->y2 = -tmp2.y1;
            }
            else
            {
                bx->x1 = tmp2.x1;
                bx->y1 = tmp2.y1;
                bx->x2 = tmp2.x2;
                bx->y2 = tmp2.y2;
            }
        }
    }
    else
    {
        for(int32_t i=0; i<hit_box_cnt; i++)
        {
            frame_box_flip(&frm->box_hit[i],&hit_area_2o[i]);
        }
    }

    if ( cust_box )
    {
        if (cust_box->angle != 0)
        {
            frame_box tmp,tmp2;
            atk_area_of[atk_box_cnt] = &atk_area_2o[5 + atk_box_cnt];
            frame_box_move_rotate(&cust_box->box, cust_box->angle, cust_box->c_x, cust_box->c_y, &tmp,&tmp2);
            frame_box_fullflip(&tmp,&atk_area_2o[atk_box_cnt]);

            frame_box *bx = atk_area_of[atk_box_cnt];
            if ( dir < 0 )
            {
                bx->x1 = tmp2.x2;
                bx->y1 = -tmp2.y2;
                bx->x2 = tmp2.x1;
                bx->y2 = -tmp2.y1;
            }
            else
            {
                bx->x1 = tmp2.x1;
                bx->y1 = tmp2.y1;
                bx->x2 = tmp2.x2;
                bx->y2 = tmp2.y2;
            }
        }
        else
        {
            atk_area_of[atk_box_cnt] = NULL;
            frame_box_flip(&cust_box->box ,&atk_area_2o[atk_box_cnt]);
        }

        if ( frm->fflags & FF_ATK_AS_HIT )
        {
            hit_area_2o[hit_box_cnt] = atk_area_2o[atk_box_cnt];
            hit_area_flags[hit_box_cnt] = atk_area_of[atk_box_cnt];
            hit_box_cnt++;
        }
        atk_box_cnt++;
    }

    if (frm->box_coll)
    {
        pcoll_box = &atk_area_2o[15];
        frame_box_flip(frm->box_coll, &atk_area_2o[15]);
    }
    else
        pcoll_box = NULL;
}
