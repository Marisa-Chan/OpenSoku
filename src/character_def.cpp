#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"


char_c::char_c(inp_ab *func)
{
    input = func;
    x = 0;
    y = 0;
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
    viz.draw(x,y,1,1);
    gr_draw_box(x,-y,255,0,0,1);
}

void char_c::input_update()
{
    input->update();
}

void char_c::basic_input()
{
    if (input->keyDown(INP_LEFT))
        x -= 5;
    if (input->keyDown(INP_RIGHT))
        x += 5;

    int32_t asd = input->check_input_seq("236X",20,1);
    if (asd > -1)
    {
        printf("236X!\n");
        set_seq(720);
    }


    asd = input->check_input_seq("623X",15,1);
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

float char_c::getX()
{
    return x;
}

float char_c::getY()
{
    return y;
}

void char_c::setX(float _x)
{
    x = _x;
}

void char_c::setY(float _y)
{
    y = _y;
}

void char_c::setXY(float _x, float _y)
{
    x = _x;
    y = _y;
}
