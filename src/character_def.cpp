#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "scene.h"


char_c::char_c(inp_ab *func)
{
    input = func;
    x = 0;
    y = 0;
    dir = 1.0;

    field_196 = 0;
    field_4A8 = 0;
    field_4C4 = 0;
    field_564 = 1.0;
    field_568 = 1.0;
    field_571 = 1;
    field_572 = 1;
    field_744 = 0;
    field_74C = 0;

    speed_mult = 1.0;
    field_834  = 0;

    h_inerc = 0;
    v_inerc = 0;
    v_force = 0;

    enemy = NULL;

}

void char_c::set_seq(uint32_t idx)
{
    viz.set_seq(idx);
}

bool char_c::process(bool ignore_loop)
{
    return viz.process(ignore_loop);
}

bool char_c::next_frame(bool ignore_loop)
{
    return viz.next_frame(ignore_loop);
}

bool char_c::next_subseq()
{
    return viz.next_subseq();
}

void char_c::reset_seq()
{
    viz.reset_seq();
}

void char_c::set_frame(uint32_t frm)
{
    viz.set_frame(frm);
}

void char_c::draw(float x, float y, float dir)
{
    viz.draw(x,y,1,dir);
}

void char_c::draw()
{
    viz.draw(x,y,1,dir);
    gr_draw_box(x,-y,255,0,0,1);

    char_frame *pf = viz.get_pframe();

    if (pf->box_atk.size() > 0)
    {
        for (uint32_t i=0; i<pf->box_atk.size();i++)
        {
            gr_draw_box(x+pf->box_atk[i].x1,
                        -y+pf->box_atk[i].y1,
                        pf->box_atk[i].x2-pf->box_atk[i].x1,
                        pf->box_atk[i].y2-pf->box_atk[i].y1,
                        255,0,0,128,1);

        }
    }

}

void char_c::input_update()
{
    input->update(dir);
}

void char_c::basic_input()
{
    if (input->gX() == -1)
        char_h_move(this, -15);
    if (input->gX() == 1)
        char_h_move(this, 15);

    v_inerc = v_inerc - v_force;

    if (h_inerc > 0)
        h_inerc -= 0.5;
    if (h_inerc < 0)
        h_inerc += 0.5;

    if (input->keyDown(INP_UP))
    {
        v_force = 0.7;
        v_inerc = 15;
    }

    int32_t asd = input->check_input_seq("236X",20,dir);
    if (asd > -1)
    {
        printf("236X!\n");
        set_seq(720);
    }


    asd = input->check_input_seq("623X",20,dir);
    if (asd > -1)
    {
        printf("623X!\n");
        set_seq(521);
    }


    asd = input->check_input_seq("412X",15,dir);
    if (asd > -1)
        printf("412X!\n");

    asd = input->check_input_seq("8N8",15,dir);
    if (asd > -1)
        printf("8N8!\n");

    //if (input->KeyDown(INP_LEFT))
        //x -= 5;
}

char_frame *char_c::get_pframe()
{
    return viz.get_pframe();
}

uint32_t char_c::get_seq()
{
    return viz.get_seq_id();
}


void char_c::func10()
{

}

void char_c::func16()
{

}

void char_c::func20()
{

}

bool char_c::flip_to_enemy()
{
  int8_t d = dir;

  if (enemy->x < x)
  {
      dir = -1;
      return d != -1;
  }
  else if (enemy->x > x)
  {
      dir = 1;
      return d != 1;
  }
  return false;
}

bool char_c::func18()
{


  bool grn = char_on_ground(this);
  /*if ( grn && v1->field_4C4 == offsetof(char_class_vars, class) )
  {
    v1->field_49B = 0;
    v1->field_49C = 0;
  }*/
  //if ( !v1->current_seq_frames_vector->field_10 )
    if ( grn /*&& v1->field_4C4 == 0*/ )
    {
      int32_t sq = get_seq();
      if ( sq != 6 && sq != 7 && sq != 8 )
        {
          int8_t in_y = input->gY();
          int8_t in_x = input->gX();
          if ( in_y >= 0 )
          {
            if ( in_y == 0 )
            {
              if ( in_x != 0 )
              {
                flip_to_enemy();
                if ( in_x < 0)
                {
                  if ( sq != 5 )
                  {
                    set_seq(5);
                    return flip_to_enemy();
                  }
                }
                else if (in_x > 0)
                {
                  if ( sq != 4 )
                  {
                    set_seq(4);
                    return flip_to_enemy();
                  }
                }
              }
              else if (in_x == 0)
              {
                if ( sq == 1 || sq == 2 )
                {
                  set_seq(3);
                }
                else if ( sq != 0 && sq != 3 && sq != 10 )
                  {
                    set_seq(0);
                    return flip_to_enemy();
                  }
              }
            }
            else if ( in_y > 0 )
            {
              if ( sq != 2 && sq != 1 )
              {
                set_seq(1);
                return flip_to_enemy();
              }
            }
            return flip_to_enemy();
          }
          flip_to_enemy();

          if ( in_x != 0 )
          {

            if ( in_x <= 0 )
            {
              if ( in_x < 0 )
                if ( sq != 8 )
                    set_seq(8);
            }
            else
            {
              if ( sq != 7 )
                set_seq(7);
            }
          }
          else
          {
            if ( sq != 6 )
              set_seq(6);
          }
        }
      }
  return true;
}











bool char_idle_or_move(char_c *chr)
{
    return chr->get_seq() < 50;
}

bool char_is_shock(char_c *chr)
{
    uint32_t s = chr->get_seq();
    return s >= 50 && s < 150;
}


void char_h_move(char_c *chr, float move)
{
  float movel;

  movel = chr->speed_mult * move;
  chr->h_inerc = movel;
  if ( move > 0.0 )
    chr->h_inerc += chr->field_834 * 0.5;
  else if ( move < 0.0 )
    chr->h_inerc -= chr->field_834 * 0.5;
}
