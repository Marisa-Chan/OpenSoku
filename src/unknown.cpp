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
    return chr->y > 0.0 && chr->field_4BA == 0 && char_is_shock(chr);
}

bool sub_479650(c_scene *scn, c_meta *p1, c_meta *p2)
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

    char_frame *frm = p1->get_pframe();
    char_frame *frm2 = p2->get_pframe();

    bool hit = false;
//    printf("%d\n",frm->box_atk.size());
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


void sub_479330(c_scene *scn)
{
    scn->ibox.x1 = -10000;
    scn->ibox.y1 = -10000;
    scn->ibox.x2 = 10000;
    scn->ibox.y2 = 10000;
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

void sub_478FC0(char_c *plr, char_c *enm)
{
    enm->health_prev = enm->health;
    enm->field_4BE = 0;
    plr->combo_count = 0;
    plr->combo_rate = 1.0;
    plr->combo_damage = 0;
    plr->combo_limit = 0;
    plr->correction = 0;
    //sub_478540((battle_manager + 52 * (character->player_index + 7)));
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

  /*if ( plr->field_18C >= 0 )
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
        enm->field_4BE += (plr->chrt->field_53C * frm->limit);
        enm->field_19C = 15.0;
        enm->field_4C0 = 20;

        plr->chrt->combo_limit = enm->field_4BE;
        plr->field_190 = 7;
    }
    else
    {

        enm->field_4BC = 0;
        enm->field_4BE += (plr->chrt->field_53C * frm->limit);
        enm->field_4C0 = 0;

        plr->field_190 = 1;
        plr->chrt->combo_limit = enm->field_4BE;

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


        if ( enm->health <= 0 || enm->field_4BE >= 100 )
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


 /*   if ( !playing_seq_is_in_50___150(enm) )
    {
        for ( i = 0; i <= a2a; ++i )
        {
            if ( i >= 3 )
                break;
            call_effects_func3_2(thisa, 201, enm->rend_cls.dir);
        }
        if ( a2a >= 2 )
            call_effects_func3_2(thisa, 201, enm->rend_cls.dir);
    }*/

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
        //call_effects_func3_2(thisa, 54, plr->rend_cls.dir);
    }
    else
    {
        enm->field_1A4 = frm->velocity_x;
        enm->field_1A8 = frm->velocity_y;
        enm->field_4BA = (plr->chrt->combo_rate * frm->untech);

        dmg = sub_464240(plr);
    }
    //int32_t energ = (plr->selft_pointer1?->field_54C * v5->props_card_energy);
    //card_energy_add(plr->selft_pointer1?, energ);
    //v26 = 0.0;
    if ( plr->chrt->field_554 <= 0.0 )
    {
        //card_energy_add(enm, dmg / 20);
        //v26 = 0.0;
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
            //(thisa->vtbl->scene_func_11)(thisa, enm);
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

    //call_effects_func3_2(thisa, v5->props_unk16, plr->rend_cls.dir);
    sub_479330(scn);
    scene_play_sfx(frm->hit_sfx);
}


bool sub_47BD80(c_scene *scn, c_meta *plr, char_c *enm)
{
    char_frame *frm = plr->get_pframe();
    char_frame *frm2 = enm->get_pframe();

//    printf("%d %d %d %d\n",frm->aflags & AF_UNK400000 != 0,frm->aflags & AF_UNK40000 != 0,enm->field_520,frm2->fflags & FF_INV_FIRE != 0);

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
            printf("Hit\n");
//            if ( !sub_47BBA0(scn, plr, enm) )
                sub_47A060(scn, plr, enm);
        }
    }
    return true;
}




void  sub_47BE70(c_scene *scn, c_meta *plr, char_c *enm)
{
    if ( plr->chrt->field_575 == 0 && enm->field_575 != 2 )
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


/*bool char __thiscall sub_47C080(void *this, bullet_class *a2, bullet_class *a3)
{
  int v4; // eax@8
  int v5; // ebx@8
  char *v6; // esi@8
  int v7; // ecx@9
  int v8; // edx@17
  void *v9; // [sp+Ch] [bp-1Ch]@1
  int *i; // [sp+10h] [bp-18h]@8
  int v11; // [sp+14h] [bp-14h]@8
  int v12; // [sp+1Ch] [bp-Ch]@9
  char v13; // [sp+20h] [bp-8h]@18

  v9 = this;
  if ( !(a3->current_frame_params->aflags & 0x20000)
    && !HIBYTE(a3->field_1A0)
    && a3->current_frame_params2->aflags & 0x400000 )
  {
    if ( !a2->field_180 )
      return sub_47AD00(this, a2, a3);
    if ( sub_47AD00(this, a2, a3) )
      return 1;
    v4 = a2->psomelist1;
    v5 = *(_DWORD *)v4;
    v6 = (char *)&a2->field_178;
    v11 = *(_DWORD *)v4;
    for ( i = &a2->field_178; ; v6 = (char *)i )
    {
      v7 = a2->psomelist1;
      v12 = a2->psomelist1;
      if ( !v6 || (int *)v6 != &a2->field_178 )
        _invalid_parameter_noinfo(v7);
      if ( v5 == v12 )
        break;
      if ( !v6 )
        _invalid_parameter_noinfo(v7);
      if ( v5 == *((_DWORD *)v6 + 1) )
        _invalid_parameter_noinfo(v7);
      if ( sub_47AD00(v9, *(bullet_class **)(v5 + 8), a3) )
        return 1;
      sub_4645C0((int)&i, v8, (int)&v13, 0);
      v5 = v11;
    }
  }
  return 0;
}*/

void scn_char_ss2(c_meta *chr);

void sub_47C430(c_scene *scn)
{
  /*scene_class_vars *v1; // ebx@1
  char_class_vars **current_char; // edi@1
  bullet_class *v3; // ecx@2
  scene_class_vars *v4; // ebp@2
  bullets_list *v5; // edx@2
  bullets_list *v6; // esi@2
  list_iterator *list; // ebp@2
  bullet_class *v8; // eax@2
  int v9; // edx@10
  bullets_list **v10; // eax@10
  bullets_list *v11; // edi@10
  list_iterator *v12; // ebx@10
  bullets_list **v13; // ecx@10
  list_node *v14; // edi@28
  char v15; // zf@52
  scene_class_vars *v17; // [sp+10h] [bp-28h]@1
  char_class_vars **v18; // [sp+14h] [bp-24h]@1
  signed int v19; // [sp+18h] [bp-20h]@1
  scene_class_vars *v20; // [sp+1Ch] [bp-1Ch]@2
  bullets_list *v21; // [sp+24h] [bp-14h]@2
  bullets_list *v22; // [sp+2Ch] [bp-Ch]@10
  list_node *v23; // [sp+34h] [bp-4h]@28

  for (int8_t i=0; i<2; i++)
  {
      char_c *chr = scn->chrs[i];
      if ()

  }

  v1 = this;
  current_char = this->chars;
  v17 = this;
  v18 = this->chars;
  v19 = 2;
  do
  {
    v3 = (bullet_class *)(3 * (*current_char)->player_index);
    v4 = (scene_class_vars *)((char *)v1 + 12 * (*current_char)->player_index);
    v5 = (bullets_list *)v4->field_5C[0].list;  // field_5C[player_index]
    v6 = v5->next_bullet;
    v20 = (scene_class_vars *)((char *)v1 + 12 * (*current_char)->player_index);
    list = v4->field_5C;
    LOBYTE(v8) = (_BYTE)v5;
    v21 = v5;
    while ( v6 != v21 )
    {
      if ( (list_node *)v6 == list->list )
        LOBYTE(v8) = _invalid_parameter_noinfo(v3);
      v3 = v6->bullet;                          // v3 = v6->bullet
      if ( !v3->field_190 )                     // !v3->field_190
      {
        if ( (list_node *)v6 == list->list )
          LOBYTE(v8) = _invalid_parameter_noinfo(v3);
        if ( v6->bullet->field_194 > 0 )
        {
          v9 = 3 * (*current_char)->enemy->player_index;
          v10 = (bullets_list **)v1->field_44[(*current_char)->enemy->player_index].list;
          v11 = *v10;
          v12 = &v1->field_44[4 * v9 / 0xCu];
          v13 = v10;
          v22 = (bullets_list *)v10;
          while ( v11 != v22 )
          {
            if ( (list_node *)v11 == v12->list )
              _invalid_parameter_noinfo(v13);
            if ( (list_node *)v6 == list->list )
              _invalid_parameter_noinfo(v13);
            if ( !sub_47C080(v17, v6->bullet, v11->bullet) )
            {
              if ( (list_node *)v11 == v12->list )
                _invalid_parameter_noinfo(v13);
              if ( (list_node *)v6 == list->list )
                _invalid_parameter_noinfo(v13);
              sub_47BFA0(v17, v6->bullet, v11->bullet);
            }
            if ( (list_node *)v11 == v12->list )
              _invalid_parameter_noinfo(v13);
            v11 = v11->next_bullet;
          }
          if ( (list_node *)v6 == list->list )
            _invalid_parameter_noinfo(v13);
          v8 = v6->bullet;
          v3 = (bullet_class *)v8->current_frame_params2;
          if ( LODWORD(v3->rend_cls.v[2].rhw) & 0x100000 )// v3->aflags & 0x100000
          {
            v14 = v20->field_44[0].list->next_node;
            v8 = (bullet_class *)v20->field_44[0].list;
            v23 = v20->field_44[0].list;
            while ( v14 != v23 )
            {
              if ( (list_node *)v6 == list->list )
                LOBYTE(v8) = _invalid_parameter_noinfo(v3);
              if ( v14 == v20->field_44[0].list )
                LOBYTE(v8) = _invalid_parameter_noinfo(v3);
              v3 = v6->bullet;
              if ( v3 != (bullet_class *)v14->value )
              {
                if ( v14 == v20->field_44[0].list )
                  _invalid_parameter_noinfo(v3);
                if ( (list_node *)v6 == list->list )
                  _invalid_parameter_noinfo(v3);
                LOBYTE(v8) = sub_47C080(v17, v6->bullet, (bullet_class *)v14->value);
                if ( !(_BYTE)v8 )
                {
                  if ( v14 == v20->field_44[0].list )
                    _invalid_parameter_noinfo(v3);
                  if ( (list_node *)v6 == list->list )
                    _invalid_parameter_noinfo(v3);
                  LOBYTE(v8) = sub_47BFA0(v17, v6->bullet, (bullet_class *)v14->value);
                }
              }
              if ( v14 == v20->field_44[0].list )
                LOBYTE(v8) = _invalid_parameter_noinfo(v3);
              v14 = v14->next_node;
            }
          }
          v1 = v17;
          current_char = v18;
        }
      }
      if ( (list_node *)v6 == list->list )
        LOBYTE(v8) = _invalid_parameter_noinfo(v3);
      v6 = v6->next_bullet;
    }
    ++current_char;
    v15 = v19-- == 1;
    v18 = current_char;
  }
  while ( !v15 );
  return (char)v8;
  */


      bul_vec * blst = getbulllist();
    for(int32_t i=blst->size()-1; i>=0; i--)
    {
        if ( !(*blst)[i]->field_190 && (*blst)[i]->field_194)
        {
            scn_char_ss2((*blst)[i]);
//            if ( !sub_47C080(scn, (*blst)[i], scn->chrs[1]) )
//              sub_47BFA0(scn, (*blst)[i], scn->chrs[1]);
        }
    }

}
