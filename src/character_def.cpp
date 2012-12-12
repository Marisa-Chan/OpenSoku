#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "scene.h"
#include "archive.h"
#include "file_read.h"
#include <math.h>

char_c::char_c(inp_ab *func)
{
    if (!pgp)
        pgp = new char_graph;

    chrt = this;

    input = func;
    x = 0;
    y = 0;
    dir = 1.0;

    angZ = 0;
    angX = 0;
    angY = 0;

    x_off = 0;
    y_off = 0;

    hit_stop = 0;
    field_4A6 = 0;
    field_4A8 = 0;
    field_4C4 = 0;
    field_564 = 1.0;
    field_568 = 1.0;
    field_571 = 1;
    field_572 = 1;
    field_710 = 0;
    field_744 = 0;
    field_74C = 0;
    field_4C2 = 0;
    field_852 = 0;

    field_19C = 0;
    field_838 = 0;
    field_526 = 0;

    field_890 = 0;
    field_892 = 0;

    weather_var = 0;

    field_80C = 0;

    dash_angle = 0;
    field_7D2 = 0;
    field_7D4 = 0;
    field_7D6 = 0;
    field_7DC = 0;
    field_7F0 = 0;

    time_stop = 0;


    field_180 = 1;
    field_1A4 = 0;
    field_1A8 = 0;

    field_190 = 1;
    //field_49A = 0;
    field_84C = 0;
    spell_energy = 1000;
    max_spell_energy = 1000;

    speed_mult = 1.0;
    tengu_fan  = 0;

    field_1BC = 1;
    field_4BE = 0;
    field_51E = 0;
    field_575 = 0;
    field_51C = 0;
    field_520 = 0;
    field_522 = 0;
    field_538 = 0;
    field_4BE = 0;
    field_4BC = 0;
    field_4BA = 0;
    field_4C0 = 0;
    field_4AC = 0;
    field_882 = 0;

    field_574 = 0;
    field_576 = 0;
    field_880 = 0;

    h_inerc = 0;
    v_inerc = 0;
    v_force = 0;

    field_348 = NULL;

    not_charge_attack = 1;
    air_dash_cnt = 0;

    health = 10000;
    max_health = 10000;

    enemy = NULL;

    for (uint32_t i=0; i<MAX_CHR_SFX; i++)
        sfx[i] = NULL;

    memset(atk_area_2o,0,sizeof(frame_box) * 15);
    memset(hit_area_2o,0,sizeof(frame_box) * 5);
}

void char_c::set_seq(uint32_t idx)
{
    c_meta::set_seq(idx);
    set_seq_params();
    if (player_index == 1)
        printf("%d\n",idx);
}

void char_c::draw()
{

    sprite.setRotate(angZ);
    sprite.setScale(dir*1.0,1);
    // }

    sprite.setXY(x,y+y_off);
    sprite.setOrigin(-x_off,-y_off);
    sprite.draw(1);

    //setOrigin(-x_off,-y_off);
    //draw(x,y+y_off,1,dir,angZ);

    //if (angZ != 0)
    //    draw(x,y+y_off,1,dir,angZ);
    //else
    //   draw(x,y+y_off,1,dir);

    // gr_draw_box(x,-y,255,0,0,1);
    // gr_draw_box(x,-y-y_off,0,255,0,1);

    for (uint32_t i = 0; i<get_pframe()->box_hit.size(); i++)
        //if (atk_area_2o[i])
    {
        frame_box *bx = &hit_area_2o[i];
        gr_draw_box(bx->x1,
                    bx->y1,
                    bx->x2-bx->x1,
                    bx->y2-bx->y1,
                    0,255,0,60,1);
    }
    /*if (pf->box_atk.size() > 0)
    {
        for (uint32_t i=0; i<pf->box_atk.size(); i++)
        {
            gr_draw_box(x+pf->box_atk[i].x1,
                        -y+pf->box_atk[i].y1,
                        pf->box_atk[i].x2-pf->box_atk[i].x1,
                        pf->box_atk[i].y2-pf->box_atk[i].y1,
                        0,255,0,128,1);
        }
    }*/

}

bool char_c::field_sq_check()
{
    uint32_t sq = get_seq();
    return (sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300;
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
        pres_move |= PMOVE_NRNR;
    if (input->check_input_seq("NLNL", 15,dir))
        pres_move |= PMOVE_NLNL;

    if (input->check_input_seq("N09", 20,dir))
        pres_move |= PMOVE_N09;
    if (input->check_input_seq("N07", 20,dir))
        pres_move |= PMOVE_N07;
    if (input->check_input_seq("N08", 20,dir))
        pres_move |= PMOVE_N08;

    if (input->check_input_seq("DD", 15,dir))
        pres_move |= PMOVE_DD;

    int8_t t = 0;

    t = input->check_input_seq("421X", 15,dir);
    if (t)
        pres_comb |= PCOMB_421A << (t - 1);

    t = input->check_input_seq("214X", 15,dir);
    if (t)
        pres_comb |= PCOMB_214A << (t - 1);

    t = input->check_input_seq("412X", 15,dir);
    if (t)
        pres_comb |= PCOMB_412A << (t - 1);

    t = input->check_input_seq("623X", 15,dir);
    if (t)
        pres_comb |= PCOMB_623A << (t - 1);

    t = input->check_input_seq("236X", 15,dir);
    if (t)
        pres_comb |= PCOMB_236A << (t - 1);

    t = input->check_input_seq("4136X", 20,dir);
    if (t)
        pres_comb |= PCOMB_4136A << (t - 1);

    t = input->check_input_seq("6314X", 20,dir);
    if (t)
        pres_comb |= PCOMB_6314A << (t - 1);

    t = input->check_input_seq("2N2X", 15,dir);
    if (t)
        pres_comb |= PCOMB_2N2A << (t - 1);

}


void char_c::func10()
{
    int32_t sq = get_seq();

    switch(sq)
    {
    case 50:
    case 51:
    case 52:
        sub10func(this);
        if ( h_inerc < 0.0 )
        {
            h_inerc += 3.0;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }

        if ( get_border_near(this) )
        {
            if ( field_4AC != 0)
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(0);

        break;
    case 56:
    case 57:
    case 58:
        sub10func(this);
        if (h_inerc < 0.0 )
        {
            h_inerc += 1.5;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }

        if ( get_border_near(this) )
        {
            if ( field_4AC != 0)
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(0);

        break;
    case 71:
        if ( get_subseq() == 1 && v_inerc < 2.0 )
            next_subseq();
        else
        {

            v_inerc -= v_force;
            if ( v_inerc > 0.0 )
                v_inerc -= v_force;

            if ( char_on_ground_down(this) )
            {
                if ( field_80C == 0 )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height(this);
                    set_seq(97);

                    //v30 = 2.0;
                }
                else if ( weather_var != 18 )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height(this);
                    set_seq(89);

                    //v30 = 5.0;
                }
                else
                {
                    weather_time *= 0.75;

                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height(this);
                    set_seq(89);

                    //v30 = 5.0;
                }

                //v34 = v30;
                //shake_camera(v34);
                scene_play_sfx(22);
            }
            else
            {
                if ( field_7D0 > 0 )
                    field_7D0--;
                if ( get_border_near(this) )
                {
                    if ( h_inerc < 0.0 )
                    {
                        h_inerc++;
                        if ( h_inerc > 0.0 )
                            h_inerc = 0.0;
                        if ( field_4AC != 0)
                            field_74C = -2.0 * field_7D0;
                    }
                }
                process();
            }
        }
        break;

    case 73:
        if ( char_on_ground_down(this) )
        {
            if ( field_80C == 0)
            {
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();

                y = 0;
                set_seq(97);
            }
            else
            {
                if (weather_var == 18)
                    weather_time *= 0.75;
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();

                y = getlvl_height(this);
                set_seq(89);
            }
            //shake_camera(5.0);
            scene_play_sfx(22);
        }
        else
        {
            process();

            if ( get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1 && v_inerc != 0)
            {
                if ( h_inerc == 0 )
                    set_subseq(3);
                else
                    set_subseq(2);
            }
            else
            {
                field_7D0--;
                if ( field_7D0 < 0 )
                    field_7D0 = 0;

                if ( get_border_near(this) )
                {
                    if ( h_inerc < 0.0 )
                    {
                        h_inerc += 2.5;
                        if ( h_inerc > 0.0 )
                            h_inerc = 0.0;

                        if ( field_4AC )
                            field_74C = field_7D0 * -2.0;
                    }
                }
            }
        }
        break;
    case 74:
        if ( get_subseq() == 1 && v_inerc < 2.0 )
        {
            next_subseq();
        }
        else
        {
            if ( get_border_near(this) && (h_inerc <= -25.0 || field_80C != 0) )
            {
                /*if ( v1->weather_var? == 18 )
                {
                    v43 = (double)weather_time;
                weather_time = (signed int)(v43 * 0.75);
                }*/

                set_seq(76);
            }
            else if ( get_border_near(this) && h_inerc <= -15.0 )
            {
                set_seq(78);
            }
            else
            {
                v_inerc -= v_force;

                if ( !char_on_ground_down(this) )
                {
                    process();
                }
                else if ( field_80C == 0 )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height(this);
                    set_seq(97);

                    //shake_camera(2.0);
                    scene_play_sfx(22);
                }
                else
                {
                    /*if ( v1->weather_var? == 18 )
                    {
                    v26 = (double)weather_time;
                    weather_time = (signed int)(v26 * 0.75);
                    }*/

                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height(this);
                    set_seq(89);
                    //shake_camera(5.0);
                    scene_play_sfx(22);
                }
            }
        }
        break;

    case 76:
        if ( get_subseq() > 0 )
            angZ -= 30.0;

        v_inerc -= v_force;

        if ( char_on_ground_down(this) )
        {
            scene_play_sfx(22);

            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height(this);

            set_seq(97);
            angZ = 0;

            //shake_camera(2.0);
            reset_ofs();
        }
        else
        {
            process();

            if ( get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1)
            {
                h_inerc = -3.0;
                v_inerc = 10.0;
                v_force = 0.5;
                dir = -dir;
            }
        }
        break;
    case 77:
        angZ -= 30;
        v_inerc -= v_force;

        if ( !char_on_ground_down(this) )
            process();
        else
        {
            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height(this);

            if ( field_80C != 0)
                set_seq(89);
            else
                set_seq(97);

            angZ = 0;

            //shake_camera(2.0);
            reset_ofs();
            scene_play_sfx(22);
        }
        break;
    case 78:
        v_inerc -= v_force;
        if ( char_on_ground_down(this) )
        {
            scene_play_sfx(22);

            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height(this);
            set_seq(97);
            //shake_camera(2.0);
        }
        else
        {
            process();
            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1 )
            {
                h_inerc = -5.0;
                v_inerc = 3.0;
                v_force = 0.5;
                dir = -dir;
            }
        }
        break;
    case 88:
        if ( char_on_ground_down(this) )
        {
            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height(this);

            set_seq(89);
            //shake_camera(5.0);
            scene_play_sfx(22);
        }
        else
        {
            process();

            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1 &&
                    v_inerc != 0)
            {
                if (h_inerc == 0)
                    set_subseq(3);
                else
                    set_subseq(2);
            }
            else
            {
                field_7D0--;
                if (field_7D0 < 0)
                    field_7D0 = 0;

                if ( get_border_near(this) )
                {
                    if ( h_inerc < 0.0 )
                    {
                        h_inerc += 2.5;
                        if ( h_inerc > 0.0 )
                            h_inerc = 0;
                        if ( field_4AC != 0)
                            field_74C = -2.0 * field_7D0;
                    }
                }
            }

        }
        break;
    case 89:
        if ( get_subseq() > 0)
        {
            angZ -= 40;
            v_inerc -= v_force;
            if (char_on_ground_down(this))
            {
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();

                y = getlvl_height(this);
                set_seq(97);
                angZ = 0;
                //shake_camera(2.0);
                reset_ofs();
                scene_play_sfx(22);
            }
        }
        else
        {
            process();
            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1)
            {
                h_inerc = field_7D0 * 0.0025;
                v_inerc = -field_7D2 * 0.0025;
                v_force = 0.25;
                x_off = x_delta;
                y_off = y_delta;
            }
        }
        break;
    case 96:
    case 97:
        if ( get_subseq() == 3 )
            sub10func(this);

        if ( gX(dir) > 0 )
        {
            if ( keyHit(INP_A) || keyHit(INP_B) || keyHit(INP_C) || keyHit(INP_D)  )
                field_7D0 = 1;
        }
        else if ( gX(dir) < 0 )
        {
            if ( keyHit(INP_A) || keyHit(INP_B) || keyHit(INP_C) || keyHit(INP_D)  )
                field_7D0 = 2;
        }

        v_inerc -= v_force;

        if ( (get_subseq() == 1 || get_subseq() == 2) && char_on_ground_down(this))
        {
            y = getlvl_height(this);
            reset_forces();
            set_subseq(3);
        }
        else
        {
            if ( process() )
            {
                set_seq(98);
                if ( field_574 != 0 || field_880 != 0 )
                    set_seq(99);
            }

            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1)
            {
                h_inerc = field_7D0 * 0.005;
                v_inerc = -field_7D2 * 0.005;
                v_force = 2.0;
            }
        }
        break;

    case 98:
        sub10func(this);
        /* if ( v1->weather_var? == 15 )
         {
           if ( weather_time > 10 )
             weather_time -= 10;
           v67 = v1->health;
           if ( v67 > 0 )
           {
             if ( v67 <= 50 )
               v1->health = 1;
             else
               v1->health = v67 - 50;
           }
         }
         else*/
        {
            if ( gX(dir) > 0 )
            {
                if ( keyHit(INP_A) || keyHit(INP_B) || keyHit(INP_C) || keyHit(INP_D)  )
                    field_7D0 = 1;
            }
            else if ( gX(dir) < 0  )
            {
                if ( keyHit(INP_A) || keyHit(INP_B) || keyHit(INP_C) || keyHit(INP_D)  )
                    field_7D0 = 2;
            }
        }
        if ( process() )
        {
            set_seq(199);
            if (field_7D0 == 1)
                set_seq(197);
            else if (field_7D0 == 2)
                set_seq(198);
        }
        break;

    case 99:
        sub10func(this);
        if ( get_subseq() == 3 )
        {
            if(c_A <= 3)
                c_A = 0;
            else
                c_A -= 3;

            //field_134 = 0;
        }
        process();

        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2)
        {
            if (field_576 == 0 && field_880 == 0)
            {
                /*if ( v1->cards_added > 0 )
                    {
                      if ( LOBYTE(v1->controlling_type) == 2 )
                      {
                        if ( *(_WORD *)get_card_id(&v1->field_5E8, 0) >= 248 )
                        {
                          //sub_463150(v1);
                          field_867 = 0;
                        }
                      }
                    }*/
                set_seq(199);
                field_574 = 0;
                field_577 = 1;
            }
            field_880 = 0;
        }
        return;

    default:
        process(true);
    }
}


void char_c::func16()
{
    if (field_524 > 0  &&
            time_stop == 0 &&
            hit_stop == 0  &&
            field_524 % 15 == 0 )
    {
        /*v106 = 0.0;
        v107 = 0.0;
        v108 = 0.0;
        v4 = x + 100.0;
        v5 = get_MT_range(0x96u) + y + 100.0;
        v6 = v5;
        v7 = v4 - get_MT_range(0xC8u);
        sub_46E2F0(v2, 1260, v7, v6, 1, 1, &v106, 3);
        v1 = 0.0;*/
    }
    if ( field_526 <= 0 || time_stop != 0 )
    {
        if ( field_814 <= 0 )
            field_80D = 0;
    }
    else
        field_80D = 1;


    field_80E = get_seq() >= 600 && get_seq() <= 689;

    if ( get_seq() >= 600 && get_seq() < 690 )
        field_7F8 = 120;

    if ( health <= 0 )
    {
        field_524 = 0;
        field_526 = 0;
        life_recovery = 0;
    }
    if ( enemy->health <= 0 )
    {
        field_524 = 0;
        field_526 = 0;
    }
    /*if ( health <= 0 )
    {
      if ( LOBYTE(v2->controlling_type) == CHAR_CTRL_PC_STORY )
      {
        if ( get_seq() >= 50 )
        {
          if ( get_seq() <= 149 )
          {
            sub_4685C0(this, enemy, 0);
            sub_46AB50(this, v12, 0, 0);
          }
        }
      }
    }*/
    if ( hit_stop  == 0  &&
            field_19C  > 0  &&
            field_4AC != 0 )
    {
        field_74C -= field_19C;
        field_19C -= 5.0;
        if ( field_19C < 0 )
            field_19C = 0;
    }

    if ( life_recovery > 0 )
    {
        if ( char_is_shock(this) )
            life_recovery = 0;

        health += 4;
        if ( health >= max_health )
            health = max_health;

        /*if ( life_recovery % 15 == 0 )
          sub_438170(v2, 151, x, y, dir, 1);
        if ( !(v2->life_recovery % 10) )
        {
          if ( char_on_ground(this) )
            sub_438170(v2, 150, x, y, dir, -1);
        }*/
        life_recovery--;
    }
    if ( field_52A == 1 )
    {
        if ( weather != 21 )
        {
            if ( weather_time >= 3 )
                weather_time -= 3;
            else
            {
                weather_time = 0;
                field_52A = 0;
            }
        }
        else
            field_52A = 0;
    }

    if ( char_on_ground(this) )
        if ( !(get_pframe()->fflags & 4) )
            air_dash_cnt = 0;


    if ( controlling_type == 0 || enemy->controlling_type == 2 )
    {
        if ( get_seq() >= 197 && get_seq() <= 199 )
        {
            field_4C2 = 60;
            field_4BE = 100;
        }

        if (get_subseq() == 0)
            if ((get_seq() == 70 && get_elaps_frames() >= 18) ||
                    (get_seq() >= 180 && get_seq() <= 181))
            {
                field_4C2 = 60;
                field_4BE = 100;
            }

        if ( field_4C2 > 0 )
        {
            field_4C2--;
            field_51C = 2;
            field_520 = 2;
        }
        if ( field_4C4 != 0 )
        {
            if ( get_seq() == 9 )
                flip_with_force();

            field_572 = 0;
            air_dash_cnt = 0;

            if ( char_is_shock(this) )
            {
                if ( y < -600 )
                {
                    if ( health > 0 )
                    {
                        set_seq(9);
                        angZ = 0.0;
                        v_inerc = 0.0;
                        h_inerc = 0.0;
                        field_4C2 = 60;
                        field_4BE = 100;
                        return;
                    }

                    if ( y < -600.0 )
                        y = -600.0;
                    if ( get_elaps_frames() >= 300 )
                    {
                        set_seq(9);
                        angZ = 0.0;
                        v_inerc = 0.0;
                        h_inerc = 0.0;
                        field_4C2 = 60;
                        field_4BE = 100;
                        field_574 = 0;
                        field_577 = 1;
                        return;
                    }
                }
                else if ( health <= 0 )
                {
                    if ( y < -600.0 )
                        y = -600.0;
                    if ( get_elaps_frames() >= 300 )
                    {
                        set_seq(9);
                        angZ = 0.0;
                        v_inerc = 0.0;
                        h_inerc = 0.0;
                        field_4C2 = 60;
                        field_4BE = 100;
                        field_574 = 0;
                        field_577 = 1;
                        return;
                    }
                }
            }
            else
            {
                v_inerc *= 0.98;
                v_force *= 0.8999999;
                if ( hit_stop == 0 || !enemy->time_stop )
                {
                    if (y < -200.0)
                    {
                        v_force = 0;
                        if (v_inerc < 0)
                            v_inerc *= 0.8999999;
                    }

                    float tmp = (240.0 - y) * 0.025;

                    if ( tmp < - 12.0 )
                        y -= 12.0;
                    else if (tmp > 12.0)
                        y += 12.0;
                    else
                        y += tmp;

                    if ( (get_seq() <= 9 || get_seq() >= 200) && get_seq() <= 299 )
                    {

                        if (input->gX(dir) == 0)
                        {
                            if ( 0 < h_inerc )
                            {
                                h_inerc -= 0.5;
                                if ( h_inerc < 0 )
                                    h_inerc = 0;
                            }
                            if ( 0 > h_inerc )
                            {
                                h_inerc += 0.5;
                                if ( h_inerc > 0 )
                                    h_inerc = 0;
                            }
                        }
                        else if (input->gX(dir) < 0)
                        {
                            if ( h_inerc > -8.0 )
                                h_inerc -= 0.5;
                        }
                        else if (input->gX(dir) > 0)
                        {
                            if ( h_inerc < 8.0 )
                                h_inerc += 0.5;
                        }

                        if (input->gY() == 0)
                        {
                            if (  v_inerc > 0)
                            {
                                v_inerc -= 0.5;
                                if ( v_inerc < 0 )
                                    v_inerc = 0;
                            }
                            if ( v_inerc < 0 )
                            {
                                v_inerc += 0.5;
                                if ( v_inerc > 0 )
                                    v_inerc = 0;
                            }
                        }
                        else if (input->gY() > 0)
                        {
                            if ( v_inerc > -12 )
                                v_inerc -= 0.5;
                        }
                        else if (input->gY() < 0)
                        {
                            if ( v_inerc < 12 )
                                v_inerc +=  0.5;
                        }
                    }
                }
            }
        }
    }

    if ( field_4BE >= 100 && field_7F7 == 0 )
    {
//            sub_438170(v2, 112, x, y + 100.0, dir, -1);
//            sub_438170(v2, 137, x, y + 100.0, dir, -1);
        field_7F7 = 1;
    }

    if ( !char_is_shock(this) && field_4C0 <= 0 && field_4C2 == 0)
        field_7F7 = 0;

    if ( field_80D )
    {
        if ( field_814 <= 0 )
            field_80D = 0;
        else
            field_814--;

        if ( field_810 > 0 )
            field_810--;
        else
        {
            /*field_810 = get_MT_range(0x3Cu) + 60;
            v106 = get_MT_range(0x168u);
            v107 = get_MT_range(0x3Cu) + 90.0;
            v108 = 0.0;
            v100 = 25.0 - get_MT_range(0x32u);
            v43 = v100 >= 0.0;
            v44 = v100 + v2->rend_cls.y_pos;
            v45 = (1 - 2 * v43);
            v46 = v2->rend_cls.dir;
            v47 = v44;
            v48 = get_MT_range(0x64u) + v2->rend_cls.x_pos - 50.0;
            sub_46E2F0(v2, 980, v48, v47, v46, v45, &v106, 3);
            */
        }
    }

    field_18C = -1;
    if ( weather_var != 3 || field_526 > 0 )
    {
        field_800 = 1;
        field_801 = 1;
        field_802 = 1;
        field_803 = 1;
        field_804 = 1;
        field_4C8 = 0;
    }
    if ( weather_var != 11 )
        field_4CC = 0;
    if ( weather_var != 12 )
    {
        field_808 = 0;
        field_4D4 = 480;
    }
    if ( weather_var != 14 )
    {
        field_4CD = 0;
        field_4CE = 0;
    }
    if ( weather_var != 18 )
    {
        field_4D8 = 0;

        /*v51 = &v2->field_4FC;

        for (uint32_t i=0; i< 1280; i+=160)
        {
            *(v51 - 8) = 0;
            *v51 = 0;
            sub_437E10(i, i + 159.0, 0);
            v51 += 4;
        }*/
    }

    field_54C = 1.0;
    field_530 = 1.0;
    field_534 = 1.0;
    field_56D = 0;
    field_198 = 1.0;
    field_56E = 0;
    field_548 = 1.0;
    field_56F = 0;
    field_544 = 1.0;
    field_570 = 0;
    speed_mult = 1.0;
    field_4AA = 0;
    field_538 = 1.0;
    field_56C = 0;
    field_53C = 1.0;
    field_80C = 0;
    field_550 = 0;
    field_554 = 0;
    field_558 = 0;
    field_540 = 0;
    if ( !input->keyHit(INP_BC) || input->keyHit(INP_BC) >= 3 )
        field_836 = 0;
    /*if ( controlling_type == 2 )
    {
        if ( dword_8841B4 <= 3 )
        {
            switch ( dword_8841B4 )
            {
            case 0:
                field_530 = 0.94999999;
                break;
            case 1:
                field_530 = 1.0;
                break;
            case 2:
                field_530 = 1.2;
                break;
            case 3:
                field_530 = 1.5;
                break;
            }
        }
    }*/
    if ( field_7F8 != 0 )
    {
        field_54C = 0;
        field_7F8--;
    }
    if ( field_526 == 0)
    {
        switch ( weather_var )
        {
        case 1:
            field_544 = 1.25;
            break;
        case 2:
            field_54C += field_54C;
            break;
        case 3:
            if ( get_seq() <= 499 || get_seq() >= 600 )
            {
                field_800 = 0;
                field_801 = 0;
                field_802 = 0;
                field_803 = 0;
                field_804 = 0;
                field_4C8 = 0;
            }
            break;
        case 4:
            field_548 = 1.25;
            break;
        case 5:
            field_56C = 1;
            break;
        case 6:
            field_550 = 0.5;
            break;
        case 7:
            field_554 = 0.5;
            break;
        case 8:
            field_56D = 1;
            break;
        case 9:
            field_56E = 1;
            break;
        case 0x10:
            field_56F = 1;
            break;
        case 0xB:
            field_570 = 1;
            if ( field_4CC == 0 )
            {
                field_4CC = 1;
//                sub_469280(v2, v15);

            }
            break;
        default:
            break;
        case 0xC:
            if ( player_index == 1 )
                field_4D4 = enemy->field_4D4;
            else
                field_4D4 = (sin(field_808 * 3.1415926/180.0) * 480.0 + 480.0);

            if ( get_seq() < 100 || (get_seq() > 111 && get_seq() < 500 ))
            {

                field_808++;

                float tmp = (fabs(enemy->x - x) - field_4D4) * 0.01;

                if ( tmp < -3.0 )
                    tmp = -3.0;
                else if (tmp > 3.0)
                    tmp = 3.0;

                if ((x < enemy->x && dir == -1) || (x > enemy->x && dir == 1))
                    enemy->field_74C -= tmp;
                else
                    enemy->field_74C = tmp;
            }
            break;
        case 0xD:
            field_538 = 0;
            field_4AA = 1;
            break;
        case 0xE:
            if ( char_is_shock(this) )
            {
                field_4CD = 0;
            }
            else
            {
                if ( field_4CD )
                {
LABEL_219:
                    if ( !(time_count % 0xAu) )
                    {
                        if ( health > 0 )
                        {
                            /*v81 = health + field_4CE + 5;
                            v19 = (health + field_4CE - 9995) < 0;
                            health = health + field_4CE + 5;;
                            if ( !((v19 ^ __OFSUB__(v81, 10000)) | v81 == 10000) )
                                v2->health = 10000;*/
                        }
                    }
                    break;
                }
                if ( char_is_shock(enemy) )
                {
                    field_4CE += 3;
                    field_4CD = 1;
                    if ( field_4CE >= 15 )
                        field_4CE = 15;
                    enemy->field_4CE = field_4CE;
                    //v106 = 0.0;
                    weather_time = (weather_time * 0.8999999);
                    //v107 = 0.0;
                    //sub_46E2F0(v2, 1110, v2->rend_cls.x_pos, 0.0, dir, -1, &v106, 3);
                }
            }
            if ( !field_4CD )
            {
                break;
            }
            goto LABEL_219;
        case 0x11:
        {
            float tmp = y - 100.0;
            if ( tmp < 0.0 )
                break;
            if ( tmp <= 600.0 )
            {
                if ( tmp <= 0.0 )
                    break;
            }
            else
            {
                tmp = 600.0;
            }
            float tmp2 = (10.0 * tmp / 600.0);
            current_card_energy += (tmp * 5.0 / 600.0);
            if ( char_is_shock(this) )
                tmp2 *= 0.25;

            if ( health > 0 )
            {
                if ( health <= tmp2 )
                    health = 1;
                else
                    health -= tmp2;
            }
            field_530 = tmp * 0.35 / 600.0 + 1.0;

        }
        break;
        case 0x12:
            field_80C = 1;
            break;
        }
    }
    if ( field_84C > 0 )
    {
        field_84C --;
        time_stop = 2;

        if ( enemy->field_110 != 1 )
            enemy->field_110 = 1;
        if ( field_84C <= 0 )
        {
            field_84C = 0;
            enemy->field_110 = 0;
        }
    }
    if ( field_848 > 0 )
    {
        // if ( (field_848 % 15) == 0 )
        //   sub_438170(v2, 155, x, y, dir, 1);

        // if ( !(field_848 % 10) == 0 )
        //   sub_438170(v2, 154, x, getlvl_height(this), dir, -1);

        spell_energy += 10;
        field_848--;
        if ( spell_energy > max_spell_energy )
            spell_energy = max_spell_energy;
    }
    if ( tengu_fan == 1 )
        speed_mult = 1.0;
    if ( tengu_fan == 2 )
        speed_mult = 1.0;
    if ( tengu_fan == 3 )
        speed_mult = 1.0;
    if ( tengu_fan >= 4 )
        speed_mult = 1.0;

    if ( field_526 == 0 )
        if ( weather_var == 10 )
            speed_mult = 1.4;


    field_530 *= (field_844 * 0.1   + 1.0);
    field_534 *= (field_844 * 0.075 + 1.0);

    if ( 1.0 == field_840 )
        field_534 *= 0.97;
    if ( 2.0 == field_840 )
        field_534 *= 0.93;
    if ( 3.0 == field_840 )
        field_534 *= 0.87999999;
    if ( field_840 >= 4.0 )
        field_534 *= 0.8;

    if ( field_84E > 0 )
    {
        field_538 *= 0.5;

        if ( field_110 == 0 )
            field_110 = 3;

        field_84E--;
        field_114 = 0;
        field_116 = (64.0 - cos(field_84E * 8.0) * 64.0);
        field_115 = (64.0 - cos(field_84E * 8.0) * 64.0);

        if ( field_84E <= 0 )
        {
            field_110 = 0;
            field_84E = 0;
        }
    }
    field_74C -= field_838;

    field_838 --;
    if (field_838 < 0)
        field_838 = 0;

    if ( field_852 > 0 )
    {
        if ( field_51C < 2 )
            field_51C = 1;

        if ( field_520 < 2 )
            field_520 = 1;


        speed_mult *= 1.2;

        if ( speed_mult >= 2.0 )
            speed_mult = 2.0;

        field_848++;

        if ( get_seq() != 691 )
            field_852--;

        if ( field_110 )
            field_110 = 3;

        uint32_t tm_c = 6 * time_count % 0x168u;

        if ( tm_c < 60 )
        {
            field_114 = 0;
            field_115 = (tm_c / 60.0 * 255.0);
            field_116 = -1;
        }
        else if ( tm_c <= 119 ) //60..120
        {
            field_115 = -1;
            field_114 = 0;
            field_116 = (255.0 - (tm_c - 60.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 179 ) //120..180
        {
            field_115 = -1;
            field_116 = 0;
            field_114 = ((tm_c - 120.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 239 )
        {
            field_114 = -1;
            field_116 = 0;
            field_115 = (255.0 - (tm_c - 180.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 299 )
        {
            field_114 = -1;
            field_115 = 0;
            field_116 = ((tm_c - 240.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 359 )
        {
            field_115 = 0;
            field_114 = (255.0 - (tm_c - 300.0) / 60.0 * 255.0);
            field_116 = -1;
        }

        if ( field_852 <= 0 )
        {
            field_110 = 0;
            field_850 = 0;
        }

    }

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

void char_c::flip_with_force()
{
    if ( dir == 1 )
    {
        if ( enemy->x < x )
        {
            dir = -1;
            h_inerc = -h_inerc;
        }
    }
    if ( dir == -1 )
    {
        if ( enemy->x > x )
        {
            dir = 1;
            h_inerc = -h_inerc;
        }
    }
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
    if ( grn /*&& v1->field_4C4 == 0*/ ) //hack
    {
        air_dash_cnt = 0;
        // field_49C = 0;
    }
    if ( get_prior() == 0)
        if ( grn /*&& v1->field_4C4 == 0*/)  //hack
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

    if ( chr->field_4C4 || (char_on_ground(chr) != 1 && chr->field_4C4 != 1))
        return false;
    if ( chr->y - getlvl_height(chr) <= 5.0|| sq == 98 || sq == 99 )
    {
        chr->y = getlvl_height(chr);
        return false;
    }
    if ( !char_is_shock(chr))
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



void char_c::play_sfx(uint32_t idx)
{
    if (sfx[idx % MAX_CHR_SFX] != NULL)
        sfx_play(sfx[idx % MAX_CHR_SFX]);
}

bool char_c::keyDown(inp_keys key)
{
    return input->keyDown(key);
}
bool char_c::keyHit(inp_keys key)
{
    return input->keyHit(key);
}

int8_t char_c::gX(int8_t dir)
{
    return input->gX(dir);
}
int8_t char_c::gY()
{
    return input->gY();
}


void char_c::sub_486FD0(float p1, float p2)
{
    field_7F0 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);

    if ( field_7F0 < p2)
        field_7F0 = p2;
    else if ( field_7F0 > p1 )
        field_7F0 = p1;
}

void char_c::set_seq_params()
{
    int32_t sq = get_seq();
    switch(sq)
    {
    case 6:
        if ( (pres_move & PMOVE_N08) == 0  && (input->keyDown(INP_D) == 0 || input->gY() <= 0 || input->gX(dir) != 0 ))
        {
            if ( field_49A == 0 )
                reset_forces();
            v_force = 0.0;
        }
        else
            set_seq(208);

        break;
    case 7:
        if ( (pres_move & PMOVE_N09) == 0  && (input->keyDown(INP_D) == 0 || input->gY() <= 0 || input->gX(dir) <= 0 ))
        {
            if ( field_49A == 0 )
                reset_forces();
            v_force = 0.0;
        }
        else
            set_seq(209);

        break;
    case 8:
        if ( (pres_move & PMOVE_N07) == 0  && (input->keyDown(INP_D) == 0 || input->gY() <= 0 || input->gX(dir) >= 0 ))
        {
            if ( field_49A == 0 )
                reset_forces();
            v_force = 0.0;
        }
        else
            set_seq(210);

        break;
    case 50:
    case 57:
    case 63:
        h_inerc = -15;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 51:
    case 55:
    case 58:
    case 61:
    case 64:
    case 67:
        h_inerc = -20;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 71:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 0.5;
        field_7D0 = 7;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 73:
    case 88:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;

        v_force = 0.8;
        field_7D0 = 7;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 74:
    case 75:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 0.8;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 76:
        field_571 = 1;
        field_572 = 1;
        //sub_4835C0();
        /*v13 = 5;
        do
        {
          v14 = v1->rend_cls.y_pos + 100.0;
          scene_add_effect(v1, 201, v1->rend_cls.x_pos, v14, v1->rend_cls.dir, 1);
          --v13;
        }
        while ( v13 );*/

        field_7D0++;
        x_off = x_delta;
        y_off = y_delta;

        hit_stop = 5;


        /*v21 = v1->rend_cls.y_pos + 100.0;
        v22 = v1->rend_cls.x_pos - (double)(50 * (signed int)(char)dir);
        scene_add_effect(v1, 38, v22, v21, dir, 1);

        v23 = v1->rend_cls.y_pos + 100.0;
        v25 = v1->rend_cls.x_pos - (double)(50 * (signed int)v1->rend_cls.dir);
        scene_add_effect(v1, 59, v25, v23, v1->rend_cls.dir, 1);*/

        h_inerc = 0.0;
        v_inerc = 0.0;
        v_force = 0.0;
        //shake_camera(2.0);
        scene_play_sfx(22);
        angZ = 0;
        break;

    case 77:
          h_inerc = -field_1A4;
          v_inerc = field_1A8;
          v_force = 0.8;
          x_off = x_delta;
          y_off = y_delta;
          field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 78:
        field_571 = 1;
        field_572 = 1;
        field_7D0++;
        //sub_4835C0();
        /*v28 = 5;
        do
        {
          scene_add_effect(v1, 201, v1->rend_cls.x_pos, v1->rend_cls.y_pos, v1->rend_cls.dir, 1);
          --v28;
        }
        while ( v28 );*/


        h_inerc = 0.0;
        v_inerc = 0.0;
        v_force = 0.0;
        //shake_camera(4.0);
        scene_play_sfx(22);
        /*v29 = v1->rend_cls.dir;
        v30 = v1->rend_cls.y_pos + 100.0;
        v31 = v30;
        v32 = v1->rend_cls.x_pos - (50 * v29);
        scene_add_effect(v1, 38, v32, v31, v29, 1);
        v33 = v1->rend_cls.y_pos + 100.0;
        v34 = v33;
        v35 = v1->rend_cls.x_pos - (50 * v1->rend_cls.dir);
        scene_add_effect(v1, 59, v35, v34, v1->rend_cls.dir, 1);*/

        angZ = 0;
        break;

    case 97:
        //sub_4835C0();
        /*scene_add_effect(v1, 58, v1->rend_cls.x_pos, v1->rend_cls.y_pos, v1->rend_cls.dir, -1);
        v38 = 5;
        do
        {
          scene_add_effect(v1, 201, v1->rend_cls.x_pos, v1->rend_cls.y_pos, v1->rend_cls.dir, 1);
          --v38;
        }
        while ( v38 );*/
        angZ = 0;
        if ( field_882 > 0 )
            set_seq(96);
        break;

    case 200:
        field_49A = 1;
        reset_forces();
        field_7DC = 0.0;
        dash_angle = 0.0;
        field_7E4 = 0.0;
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 201:
    case 202:
    case 203:
        reset_forces();
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
        if ( field_49A == 0 )
            reset_forces();
        v_force = 0.0;
        break;
    }
}

c_bullet *char_c::new_bullet()
{
    return NULL;
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
        chr->h_inerc += chr->tengu_fan * 0.5;
    else if ( move < 0.0 )
        chr->h_inerc -= chr->tengu_fan * 0.5;
}


void char_loadsfx(char_c *chr, const char *name)
{
    char buf[CHRBUF];
    for (uint32_t i=0; i<MAX_CHR_SFX; i++)
    {
        sprintf(buf,"data/se/%s/%3.3d.cv3",name,i);

        filehandle *ft = arc_get_file(buf);

        chr->sfx[i] = NULL;

        if (ft)
        {
            chr->sfx[i] = sfx_load_cv3(ft);
            delete ft;
        }
    }
}





bool hi_jump_after_move(char_c *chr)
{
    if ( chr->gY() > 0)
    {
        if ( chr->gX(chr->dir) > 0 )
        {
            chr->angZ = 0.0;
            chr->set_seq(209);
            return true;
        }
        else if ( chr->gX(chr->dir) < 0 )
        {
            chr->angZ = 0.0;
            chr->set_seq(210);
            return true;
        }
        else
        {
            chr->angZ = 0.0;
            chr->set_seq(208);
            return true;
        }
    }

    return false;
}

bool border_escape_ground(char_c *chr)
{
    if ( chr->pres_move & PMOVE_DD  && chr->field_80E == 0)
        if (  chr->get_seq() >= 150  && chr->get_seq() <= 157 && (chr->max_spell_energy >= 200 || chr->weather_var == 0) )
        {
            if ( chr->gY() <= 0 )
            {
                chr->angZ = 0.0;
                if ( chr->gX(chr->dir) <= 0 )
                    chr->set_seq(224);
                else
                    chr->set_seq(223);
                //if ( v1->weather_var? )
                // sub_463160(v1, 1);
                return true;
            }
            else
            {
                chr->angZ = 0.0;
                if ( chr->gX(chr->dir) >= 0 )
                    chr->set_seq(220);
                else
                    chr->set_seq(222);
                //if ( chr->weather_var )
                // sub_463160(v1, 1);
                return true;
            }
        }
    return false;
}

bool hi_jump(char_c *chr, uint16_t cprior, uint32_t hjc)
{
    if ( (chr->pres_move & PMOVE_N08) || (chr->gY() > 0 && chr->gX(chr->dir)==0 && (chr->keyDown(INP_D) || cprior >= 40)) )
        if ( cprior <= chr->get_prior(208) || hjc )
            if ( chr->field_sq_check() )
            {
                chr->angZ = 0.0;
                chr->set_seq(208);
                return true;
            }
    if ( chr->pres_move & PMOVE_N09 || (chr->gY() > 0 && chr->gX(chr->dir) > 0 && (chr->keyDown(INP_D) || cprior >= 40)))
        if ( cprior <= chr->get_prior(209) || hjc )

            if ( chr->field_sq_check())
            {
                chr->angZ = 0.0;
                chr->set_seq(209);
                return true;
            }


    if ( chr->pres_move & PMOVE_N07 || (chr->gY() > 0 && chr->gX(chr->dir) < 0 && (chr->keyDown(INP_D) || cprior >= 40)))
        if ( cprior <= chr->get_prior(210) || hjc)
            if ( chr->field_sq_check())
            {
                chr->angZ = 0.0;
                chr->set_seq(210);
                return true;
            }
    return false;
}

bool fw_bk_dash_ground(char_c *chr, uint16_t cprior, uint32_t hjc)
{
    if ( ((chr->pres_move & PMOVE_NRNR && chr->dir == 1)
            || (chr->pres_move & PMOVE_NLNL && chr->dir == -1)
            || (chr->keyDown(INP_D) && chr->gY() == 0 && chr->gX(chr->dir) > 0))
            && chr->get_seq() != 204
            && cprior <= chr->get_prior(200)
            && chr->field_sq_check())
    {
        chr->angZ = 0.0;
        chr->set_seq(200);
        return true;
    }
    else if (((chr->pres_move & PMOVE_NLNL && chr->dir == 1)
              || (chr->pres_move & PMOVE_NRNR && chr->dir == -1)
              || (chr->keyDown(INP_D) && chr->gY() == 0 && chr->gX(chr->dir) < 0))
             && (cprior <= chr->get_prior(201) || hjc)
             && chr->field_sq_check())
    {
        chr->angZ = 0.0;
        chr->set_seq(201);
        return true;
    }
    return false;
}


bool border_escape_air(char_c *chr)
{
    if ( (chr->pres_move & PMOVE_DD) != 0  && chr->field_80E == 0 && chr->get_seq() == 158 &&
            (chr->max_spell_energy >= 200 || chr->weather_var==0 ))
    {
        chr->angZ = 0.0;
        if ( chr->gX(chr->dir) > 0 )
        {
            chr->set_seq(226);
            //if ( chr->weather_var == 0 )
            //sub_463160(v1, 1);
            return 1;
        }
        else
        {
            chr->set_seq(225);
            //if ( v1->weather_var? )
            //sub_463160(v1, 1);
            return true;
        }
    }
    return false;
}

bool fwd_dash_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse)
{
    if ( chr->air_dash_cnt < max_dash
            && (chr->get_seq() != 202 || chr->get_subseq() >= subse)
            && (((chr->pres_move & PMOVE_NRNR) != 0 && chr->dir == 1) || ((chr->pres_move & PMOVE_NLNL) != 0 && chr->dir == -1))
            && (cprior <= chr->get_prior(202) || hjc)
            && (chr->v_inerc <= 0.0 || chr->y > 100.0)
            && chr->field_sq_check())
    {
        chr->angZ = 0.0;
        chr->set_seq(202);
        chr->air_dash_cnt++;
        return true;
    }
    return false;
}

bool bkg_dash_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse)
{
    if ( chr->air_dash_cnt < max_dash
            && (chr->get_seq() != 203 || chr->get_subseq() >= subse)
            && (((chr->pres_move & PMOVE_NLNL) != 0 && chr->dir == 1) || ((chr->pres_move & PMOVE_NRNR) != 0 && chr->dir == -1))
            && (cprior <= chr->get_prior(203) || hjc)
            && (chr->v_inerc <= 0.0 || chr->y > 100.0)
            && chr->field_sq_check())
    {
        chr->angZ = 0.0;
        chr->set_seq(203);
        chr->air_dash_cnt++;
        return true;
    }
    return false;
}

bool flying_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash)
{
    if ( chr->air_dash_cnt < max_dash
            && chr->keyDown(INP_D)
            && (chr->gX(chr->dir) != 0 || chr->gY() != 0)
            && (chr->v_inerc <= 0.0 || chr->y > 100.0)
            && (cprior <= chr->get_prior(214) || hjc)
            && chr->field_sq_check() )
    {
        if ( chr->gY() < 0 )
        {
            if (chr->gX(chr->dir) > 0)
                chr->dash_angle = -45.0;
            else if( chr->gX(chr->dir) < 0 )
                chr->dash_angle = -135.0;
            else
                chr->dash_angle = -90.0;
        }
        else if ( chr->gY() > 0 )
        {
            if (chr->gX(chr->dir) > 0)
                chr->dash_angle = 45.0;
            else if( chr->gX(chr->dir) < 0 )
                chr->dash_angle = 135.0;
            else
                chr->dash_angle = 90.0;
        }
        else
        {
            if (chr->gX(chr->dir) > 0)
                chr->dash_angle = 0.0;
            else if( chr->gX(chr->dir) < 0 )
                chr->dash_angle = 180.0;
            else
                chr->dash_angle = 0.0;
        }
        chr->angZ = 0;
        chr->air_dash_cnt++;
        chr->set_seq(214);
        return true;
    }

    return false;
}



void char_c::stopping(float p)
{
    if (field_49A)
    {
        if (h_inerc > 0)
        {
            h_inerc -= p;
            if (h_inerc < 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
        if ( h_inerc < 0)
        {
            h_inerc += p;
            if (h_inerc > 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
    }
    else
        reset_forces();
}

void char_c::stopping_posit(float p)
{
    if (field_49A)
    {
        h_inerc -= p;
        if (h_inerc < 0)
        {
            reset_forces();
            field_49A = 0;
        }
    }
    else
        reset_forces();
}


