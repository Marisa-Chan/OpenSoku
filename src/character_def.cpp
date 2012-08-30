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

    not_charge_attack = 1;

    enemy = NULL;

}

void char_c::set_seq(uint32_t idx)
{
    viz.set_seq(idx);
    set_seq_params();
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
        for (uint32_t i=0; i<pf->box_atk.size(); i++)
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
    input->update();
}

void char_c::check_seq_input()
{
    pres_move = 0;
    pres_comb = 0;

    if (input->check_input_seq("NRNR", 15,dir))
        pres_move |= 1;
    if (input->check_input_seq("NLNL", 15,dir))
        pres_move |= 2;

    if (input->check_input_seq("N09", 20,dir))
        pres_move |= 0x10;
    if (input->check_input_seq("N07", 20,dir))
        pres_move |= 8;
    if (input->check_input_seq("N08", 20,dir))
        pres_move |= 4;

    if (input->check_input_seq("DD", 15,dir))
        pres_move |= 0x20;

    int8_t t = 0;

    t = input->check_input_seq("421X", 15,dir);
    if (t)
        pres_comb |= 0x1000 << (t - 1);

    t = input->check_input_seq("214X", 15,dir);
    if (t)
        pres_comb |= 0x10 << (t - 1);

    t = input->check_input_seq("412X", 15,dir);
    if (t)
        pres_comb |= 0x10000 << (t - 1);

    t = input->check_input_seq("623X", 15,dir);
    if (t)
        pres_comb |= 0x100 << (t - 1);

    t = input->check_input_seq("236X", 15,dir);
    if (t)
        pres_comb |= 0x1 << (t - 1);

    t = input->check_input_seq("4136X", 20,dir);
    if (t)
        pres_comb |= 0x100000 << (t - 1);

    t = input->check_input_seq("6314X", 20,dir);
    if (t)
        pres_comb |= 0x1000000 << (t - 1);

    t = input->check_input_seq("2N2X", 15,dir);
    if (t)
        pres_comb |= 0x10000000 << (t - 1);

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
    viz.process(true);
}

void char_c::set_seq_params()
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

void char_c::reset_forces()
{
    h_inerc = 0;
    v_inerc = 0;
    v_force = 0;
    //h_force = 0;
}

void char_c::func18()
{


    bool grn = char_on_ground(this);
    /*if ( grn && v1->field_4C4 == offsetof(char_class_vars, class) )
    {
      v1->field_49B = 0;
      v1->field_49C = 0;
    }*/
    if ( viz.get_prior() == 0)
    if ( grn /*&& v1->field_4C4 == 0*/ )
    {
        int32_t sq = get_seq();
        if ( sq != 6 && sq != 7 && sq != 8 )
        {
            int8_t in_y = input->gY();
            int8_t in_x = input->gX(dir);

            if (in_y == 0)
            {
                if (in_x == 0)
                {
                    if ( sq == 1 || sq == 2 )
                        set_seq(3);
                    else if ( sq != 0 && sq != 3 && sq != 10 )
                        set_seq(0);
                }
                else
                {
                    flip_to_enemy();
                    if (in_x < 0)
                    {
                        if ( sq != 5 )
                            set_seq(5);
                    }
                    else /*if (in_x > 0)*/
                    {
                        if ( sq != 4 )
                            set_seq(4);
                    }

                }
                flip_to_enemy();
            }
            else if (in_y > 0)
            {
                flip_to_enemy();
                in_x = input->gX(dir);

                if ( in_x < 0 )
                {
                    if ( sq != 8 )
                        set_seq(8);
                }
                else if (in_x > 0)
                {
                    if ( sq != 7 )
                        set_seq(7);
                }
                else /*if (in_x == 0)*/
                {
                    if ( sq != 6 )
                        set_seq(6);
                }
            }
            else if (in_y < 0)
            {
                if ( sq != 2 && sq != 1 )
                {
                    set_seq(1);
                    flip_to_enemy();
                }
            }
        }
    }
}


bool sub10func(char_c *chr)
{
    int32_t sq = chr->get_seq();

    if ( chr->field_4C4 || (char_on_ground(chr) && chr->field_4C4 == 0))
        return false;
    if ( chr->y - getlvl_height(chr) <= 5.0|| sq == 98 || sq == 99 )
    {
        chr->y = getlvl_height(chr);
        return false;
    }
    if ( sq < 50 || sq > 149 )
    {
        chr->v_inerc = 0.0;
        chr->v_force = 0.5;

        if ( chr->h_inerc > 10.0 )
            chr->h_inerc = 10.0;
        if ( chr->h_inerc < -10.0 )
            chr->h_inerc = -10.0;

        if ( sq < 700 || sq > 799 )
        {
            chr->scaleX = 1.0;
            chr->scaleY = 1.0;

            chr->set_seq(9);
        }
        else
            chr->set_seq(704);
    }
    else
    {
        chr->field_1A8 = 0.0;
        chr->field_1A4 = -chr->h_inerc;
        chr->scaleX = 1.0;
        chr->scaleY = 1.0;
        chr->angZ    = 0.0;
        chr->v_force = 0.5;

        chr->set_seq(71);
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



