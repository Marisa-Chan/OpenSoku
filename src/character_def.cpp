#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"


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

    if (pf->box_coll.size() > 0)
    {
        for (uint32_t i=0; i<pf->box_coll.size();i++)
        {
            gr_draw_box(x+pf->box_coll[i].x1,
                        -y+pf->box_coll[i].y1,
                        pf->box_coll[i].x2-pf->box_coll[i].x1,
                        pf->box_coll[i].y2-pf->box_coll[i].y1,
                        255,255,255,128,1);

        }
    }

}

void char_c::input_update()
{
    input->update();
}

void char_c::basic_input()
{
    if (input->keyDown(INP_LEFT))
        char_h_move(this, -15);
    if (input->keyDown(INP_RIGHT))
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

    int32_t asd = input->check_input_seq("236X",20,1);
    if (asd > -1)
    {
        printf("236X!\n");
        set_seq(720);
    }


    asd = input->check_input_seq("623X",20,1);
    if (asd > -1)
    {
        printf("623X!\n");
        set_seq(521);
    }


    asd = input->check_input_seq("412X",15,1);
    if (asd > -1)
        printf("412X!\n");

    asd = input->check_input_seq("8N8",15,1);
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

void char_c::func18()
{

}

void char_c::func20()
{

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
