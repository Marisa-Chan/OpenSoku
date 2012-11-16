#include "global_types.h"
#include "framedata.h"
#include "scene.h"
#include "input.h"
#include "character_def.h"


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


bool sub_479D50(c_scene *scn, char_c *p1, char_c *p2)
{

    char_frame *frm = p1->get_pframe();
    char_frame *frm2 = p2->get_pframe();

    bool hit = false;

    for (uint32_t i=0; i< frm->box_hit.size(); i++)
    {
        if (p1->hit_area_flags[i] != NULL)
        {
            for (uint32_t j=0; j< frm2->box_hit.size(); j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479720(scn, &p1->hit_area_2o[i], p1->hit_area_flags[i], &p2->hit_area_2o[j], p2->hit_area_flags[j]);
                else
                    hit |= sub_479420(scn, &p1->hit_area_2o[i], p1->hit_area_flags[i], &p2->hit_area_2o[j]);
            }
        }
        else
        {
            for (uint32_t j=0; j< frm2->box_hit.size(); j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479420(scn, &p2->hit_area_2o[j], p2->hit_area_flags[j], &p1->hit_area_2o[i]);
                else
                {
                    frame_box *fb1 = &p1->hit_area_2o[i];
                    frame_box *fb2 = &p2->hit_area_2o[j];

                    if ((fb2->x1 - fb1->x2) < 0 ||
                            (fb1->x1 - fb2->x2) < 0 ||
                            (fb1->y1 - fb2->y2) < 0 ||
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



/*
bool sub_47AD60(c_scene *scn, char_c *p1, char_c *p2)
{
  scene_class_vars *v3; // ebx@1
  num_of_seqs *v4; // edx@1
  num_of_seqs *v6; // ecx@3
  __int16 v7; // ax@3
  __int16 v8; // cx@4
  num_of_seqs *v9; // eax@14
  __int16 v10; // cx@17
  __int16 v11; // ax@17
  int v12; // [sp-4h] [bp-10h]@6
  int v13; // [sp-4h] [bp-10h]@8

  v3 = scn;

  if ( !sub_479D50(scn, p1, p2) )
    return false;

    char_frame *frm1 = p1->get_pframe();

    p1->get_cprior();

  v6 = p1->field_1C4;
  v7 = v6->cprior;
  if ( !p1->get_cprior() )
  {
      if (p2->get_cprior())
      {
          if (p2->get_prior() < 0)
      }
    v9 = p2->field_1C4;
    if ( v9->cprior )
    {
      if ( v9->prior < 0 )
        goto LABEL_6;
      v13 = 5;
    }
    else
    {
      v10 = v6->prior;
      v11 = v9->prior;
      if ( v10 > v11 )
        goto LABEL_6;
      if ( v10 < v11 )
      {
        sub_464700(p1, v4, 4);
        sub_479330(v3);
        return 1;
      }
      v13 = 8;
    }
LABEL_21:
    sub_464700(p1, v4, v13);
    v12 = 8;
    goto LABEL_22;
  }
  v4 = p2->field_1C4;
  v8 = v4->cprior;
  if ( v7 != v8 )
  {
    if ( v7 >= v8 )
    {
      if ( v8 )
      {
        sub_464700(p1, v4, 8);
        v12 = 4;
      }
      else
      {
        if ( v7 < v4->prior )
        {
          sub_464700(p1, v4, 4);
          sub_479330(v3);
          return 1;
        }
        sub_464700(p1, v4, 8);
        v12 = 5;
      }
      goto LABEL_22;
    }
    v13 = 4;
    goto LABEL_21;
  }
  sub_464700(p1, v4, 4);
LABEL_6:
  v12 = 4;
LABEL_22:
  sub_464700(p2, v4, v12);
  sub_479330(v3);
  return 1;
}*/

bool sub_4699E0(char_c *chr)
{
    return chr->y > 0.0 /*&& !chr->field_4BA*/ && chr->get_seq() >= 50 && chr->get_seq() < 150;
}

bool sub_479650(c_scene *scn, char_c *p1, char_c *p2)
{
    bool hit = false;

    if ( p2->field_348 != NULL )
    {
        char_frame *frm = p1->get_pframe();

        for (uint32_t i = 0; i < frm->box_atk.size(); i++)
        {
            if (p1->atk_area_of[i] != NULL)
            {
                hit |= sub_479420(scn, &p1->atk_area_2o[i], p1->atk_area_of[i], p2->field_348);
            }
            else
            {
                frame_box *fb1 = &p1->atk_area_2o[i];
                frame_box *fb2 = p2->field_348;

                if ((fb2->x1 - fb1->x2) < 0 ||
                        (fb1->x1 - fb2->x2) < 0 ||
                        (fb1->y1 - fb2->y2) < 0 ||
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

bool sub_479BC0(c_scene *scn, char_c *p1, char_c *p2)
{

    char_frame *frm = p1->get_pframe();
    char_frame *frm2 = p2->get_pframe();

    bool hit = false;

    for (uint32_t i=0; i< frm->box_atk.size(); i++)
    {
        if (p1->atk_area_of[i] != NULL)
        {
            for (uint32_t j=0; j< frm2->box_atk.size(); j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479720(scn, &p1->atk_area_2o[i], p1->atk_area_of[i], &p2->hit_area_2o[j], p2->hit_area_flags[j]);
                else
                    hit |= sub_479420(scn, &p1->atk_area_2o[i], p1->atk_area_of[i], &p2->hit_area_2o[j]);
            }
        }
        else
        {
            for (uint32_t j=0; j< frm2->box_hit.size(); j++)
            {
                if (p2->hit_area_flags[j] != NULL)
                    hit |= sub_479420(scn, &p2->hit_area_2o[j], p2->hit_area_flags[j], &p1->atk_area_2o[i]);
                else
                {
                    frame_box *fb1 = &p1->atk_area_2o[i];
                    frame_box *fb2 = &p2->hit_area_2o[j];

                    if ((fb2->x1 - fb1->x2) < 0 ||
                            (fb1->x1 - fb2->x2) < 0 ||
                            (fb1->y1 - fb2->y2) < 0 ||
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


void sub_479330(c_scene *scn)
{
    scn->ibox.x1 = -10000;
    scn->ibox.y1 = -10000;
    scn->ibox.x2 = 10000;
    scn->ibox.y2 = 10000;
}


bool sub_47ABE0(c_scene *scn, char_c *plr, char_c *enm)
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
        sub_479330(scn);
        return true;
    }
    return false;
}

void sub_479FF0(char_c *chr, int32_t a1, int32_t a2)
{
    if ( chr->get_seq() >= 500  && chr->get_seq() < 600)
        if ( chr->field_4C8 > 0 )
            a1 >>= (chr->field_4C8 - 1);

    chr->spell_energy -= a1;

    if ( chr->spell_energy < 0 )
        chr->spell_energy = 0;

    if ( chr->spell_energy_stop < a2 )
        chr->spell_energy_stop = a2;
}


bool sub_47AAA0(c_scene *scn, char_c *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if ( ((frm2->fflags & FF_GRAZE) == 0 && enm->field_522 == 0 ) || (frm->aflags & AF_UNK800000) == 0 )
        return false;

    if ( enm->field_56C == 0 )
    {
        if ( (frm->aflags & AF_UNK400000) == 0 )
            return false;

        if (frm->aflags & AF_UNK1000000)
        {
            if (enm->spell_energy > 4 )
                sub_479FF0(enm, 4, 30);
            else
                return false;
        }

        plr->field_194 = plr->field_1BC - 1;
        plr->field_190 = 6;
    }
    else
    {
//        call_effects_func3_2(scn, 201, enm->dir);

        if (frm->aflags & AF_UNK400000 )
        {
            if ( (frm->aflags & AF_UNK1000000)  && enm->spell_energy >= 10 )
                sub_479FF0(enm, 10, 60);
            else if ((frm->aflags & AF_UNK1000000) == 0  && enm->spell_energy > 30)
                sub_479FF0(enm, 4, 30);
            else
                return false;

            plr->field_194 = plr->field_1BC - 1;
            plr->field_190 = 6;
        }
        else if ( enm->spell_energy >= 50 )
            sub_479FF0(enm, 50, 60);
        else
            return false;
    }

    enm->field_4C6++;
  //  call_effects_func3_2(scn, 52, enm->dir);
    sub_479330(scn);
    return true;
}
//
//int8_t sub_469750(char_c *chr, uint32_t aflags)
//{
//  char_class_vars *v2; // esi@1
//  unsigned int result; // eax@2
//  FFFLAGS v4; // eax@4
//  int v5; // eax@10
//  int v6; // eax@32
//
//  v2 = this;
//
//  char_frame *frm = chr->get_pframe();
//
//  if ( (aflags & AF_U_HIT) || chr->field_4AA)
//    return 0;
//
//  v4 = this->current_frame_params->fflags;
//
//  if ( frm->fflags & FF_GUARD2 )
//    return 6;
//  if ( !(frm->fflags & FF_GUARDCANC) )
//    return 0;
//
//  if ( chr->get_seq() < 150 && chr->get_seq() > 168 )
//  {
//    /*if ( v2->input_function )
//      goto LABEL_38;
//    if ( LOBYTE(v2->controlling_type) == 3 )
//    {
//      v2->pressed_y_axis = 0;
//      v2->pressed_x_axis = 0;
//      if ( practice_params->field_C <= 0 )
//        goto LABEL_38;
//    }
//    else
//    {
//      if ( dword_8841B4 )
//      {
//        if ( dword_8841B4 == 1 && get_MT_range(0x64u) >= 0x5F )
//        {
//LABEL_38:*/
//    if ( chr->field_578 || ((chr->enemy->x - chr->x) * chr->gX(1) <= 0 && chr->gX(1) != 0 ))
//    {
//        if ( !char_on_ground_flag(chr) || (frm->fflags & FF_AIRBORNE) )
//            return  (aflags & AF_AIR_HIT) != 0 ? 5 : 0;
//        else
//        {
//            if ( chr->gY() > 0)
//            {
//                if ( aflags & AF_MID_HIT )
//                    return 1;
//                else if (aflags & AF_UNK40)
//                    return 0;
//
//                return 2;
//            }
//            else
//            {
//            if ( aflags & AF_LOW_HIT )
//                return 3;
//            else if (aflags & AF_UNK40)
//                return 0;
//
//                return 4;
//            }
//        }
//    }
//    return 0;
//        /*}
//      }
//      else
//      {
//        if ( get_MT_range(0x64u) >= 0x46 )
//          goto LABEL_38;
//      }*/
//    }
//    if ( v2->enemy->rend_cls.x_pos - v2->rend_cls.x_pos <= 0.0 )
//      v2->pressed_x_axis = 1;
//    else
//      v2->pressed_x_axis = -1;
//   /* if ( LOBYTE(v2->controlling_type) == 3 )
//    {
//      v6 = practice_params->dummy_block_type;
//      if ( v6 == 2 )
//      {
//        v2->pressed_y_axis = 0;
//      }
//      else
//      {
//        if ( v6 == 3 )
//          v2->pressed_y_axis = 1;
//        else
//          v2->pressed_y_axis = (~enemu_aflags >> 1) & 1;
//      }
//    }
//    else
//    {*/
//      v2->pressed_y_axis = (~enemu_aflags >> 1) & 1;
//    }
//    goto LABEL_38;
//  }
//  if ( v2->input_function )
//  {
//    if ( v2->pressed_x_axis || !(enemu_aflags & 0x80000) )
//      goto LABEL_41;
//    return 0;
//  }
//  if ( LOBYTE(v2->controlling_type) == 3 )
//  {
//    v5 = practice_params->dummy_block_type;
//    if ( v5 == 2 )
//    {
//      v2->pressed_y_axis = 0;
//    }
//    else
//    {
//      if ( v5 == 3 )
//        v2->pressed_y_axis = 1;
//      else
//        v2->pressed_y_axis = (~enemu_aflags >> 1) & 1;
//    }
//  }
//  else
//  {
//    v2->pressed_y_axis = (~enemu_aflags >> 1) & 1;
//  }
//LABEL_41:
//  if ( !char_on_ground_flag(v2) || v2->current_frame_params->fflags & 4 )
//  {
//    result = (enemu_aflags & 8) != 0 ? 5 : 0;
//  }
//  else
//  {
//    if ( v2->pressed_y_axis <= 0 )
//    {
//      if ( enemu_aflags & 2 )
//        result = 1;
//      else
//        result = (~enemu_aflags >> 5) & 2;
//    }
//    else
//    {
//      if ( enemu_aflags & 4 )
//        result = 3;
//      else
//        result = (~enemu_aflags >> 4) & 4;
//    }
//  }
//  return result;
//}
//
//char __thiscall sub_47BBA0(scene_class_vars *this, char_class_vars *a2, char_class_vars *a3)
//{
//  scene_class_vars *v3; // ebx@1
//  char result; // al@2
//  char v5; // al@3
//  int v6; // ecx@3
//  char_class *v7; // edx@3
//  char v8; // zf@9
//  int v9; // edx@9
//  char_class *v10; // eax@9
//  void (__thiscall *v11)(char_class_vars *, _DWORD); // eax@12
//  char v12; // al@15
//  int v13; // edx@17
//  void (__thiscall *v14)(char_class_vars *, _DWORD); // eax@20
//
//  v3 = this;
//  switch ( sub_469750(a3, a2->current_frame_params2?->aflags) )
//  {
//    case 0u:
//      return 0;
//    case 1u:
//      v5 = sub_47B5A0(v3, a2, a3);
//      v7 = a3->class;
//      if ( v5 )
//        goto LABEL_4;
//      LOWORD(v6) = a2->current_frame_params2?->attack_type + 150;
//      goto LABEL_6;
//    case 3u:
//      v8 = sub_47B5A0(v3, a2, a3) == 0;
//      v10 = a3->class;
//      if ( !v8 )
//        goto LABEL_10;
//      LOWORD(v9) = a2->current_frame_params2?->attack_type + 154;
//      v10->func2_set_seq(a3, v9);
//      initclass_rendercharclass(&a3->rend_cls);
//      return 1;
//    case 5u:
//      v8 = sub_47B5A0(v3, a2, a3) == 0;
//      v11 = a3->class->func2_set_seq;
//      if ( v8 )
//      {
//        v11(a3, 158);
//        initclass_rendercharclass(&a3->rend_cls);
//        result = 1;
//      }
//      else
//      {
//        v11(a3, 145);
//        initclass_rendercharclass(&a3->rend_cls);
//        result = 1;
//      }
//      return result;
//    case 2u:
//      v12 = sub_47B8F0(v3, a2, a3);
//      v7 = a3->class;
//      if ( v12 )
//      {
//LABEL_4:
//        v7->func2_set_seq(a3, 143);
//        initclass_rendercharclass(&a3->rend_cls);
//        result = 1;
//      }
//      else
//      {
//        LOWORD(v6) = a2->current_frame_params2?->attack_type + 159;
//LABEL_6:
//        v7->func2_set_seq(a3, v6);
//LABEL_7:
//        initclass_rendercharclass(&a3->rend_cls);
//LABEL_8:
//        result = 1;
//      }
//      return result;
//    case 4u:
//      v8 = sub_47B8F0(v3, a2, a3) == 0;
//      v10 = a3->class;
//      if ( v8 )
//      {
//        LOWORD(v13) = a2->current_frame_params2?->attack_type + 163;
//        v10->func2_set_seq(a3, v13);
//        initclass_rendercharclass(&a3->rend_cls);
//        result = 1;
//      }
//      else
//      {
//LABEL_10:
//        v10->func2_set_seq(a3, 143);
//        initclass_rendercharclass(&a3->rend_cls);
//        result = 1;
//      }
//      return result;
//    case 6u:
//      if ( !sub_47B5A0(v3, a2, a3) )
//        goto LABEL_8;
//      v8 = char_on_ground_flag(a3) == 0;
//      v14 = a3->class->func2_set_seq;
//      if ( v8 )
//      {
//        v14(a3, 145);
//        result = 1;
//      }
//      else
//      {
//        v14(a3, 143);
//        result = 1;
//      }
//      return result;
//    default:
//      goto LABEL_7;
//  }
//}


bool sub_47BD80(c_scene *scn, char_c *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

    if ( frm->aflags & AF_UNK400000 )
    {
        if ( !(frm->aflags & AF_UNK40000) && (enm->field_520 != 0 || frm2->fflags & FF_INV_FIRE) )
            return false;
    }
    else
    {
        if ( enm->field_51C != 0 || frm2->fflags & FF_MEL_INV_GND )
            return false;
    }

    if ( frm->aflags & 0x80000000) // >= 0 )
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
            printf("Hit\n");
//            if ( !sub_47BBA0(scn, plr, enm) )
//                sub_47A060(scn, plr, enm);
        }
    }
    return true;
}




void  sub_47BE70(c_scene *scn, char_c *plr, char_c *enm)
{

    if ( plr->field_575 == 0 && enm->field_575 != 2 )
    {
        if ( !sub_4699E0(enm) && enm->field_4BE < 100 )
        {
            char_frame *frm = plr->get_pframe();
            if (plr != enm || (frm->aflags & AF_HITSALL) == 0 || plr->enemy->field_575 == 0)
            {
                if (plr->field_180 != 0)
                {
                    if (sub_47BD80(scn, plr, enm))
                    {
                        //sub_4647B0(plr, plr);
                    }
                    else
                    {
                        /*v5 = a2->psomelist1?;
                        v6 = *v5;
                        v12 = *v5;
                        v11 = &a2->field_178;
                        v13 = &a2->field_178;
                        while ( 1 )
                        {
                            v14 = a2->psomelist1?;
                            if ( !sub_44CF50(&v11, v6, &v13) )
                                break;
                            v8 = sub_464590(&v11, v7);
                            if ( sub_47BD80(v3, *v8, a3) )
                            {
                                v10 = sub_464590(&v11, v9);
                                sub_4647B0(a2, *v10);
                                return;
                            }
                            sub_4645C0(&v11, v6, &v15, 0);
                        }
                        */
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

