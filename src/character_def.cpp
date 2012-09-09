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
    input = func;
    x = 0;
    y = 0;
    dir = 1.0;

    hit_stop = 0;
    field_4A8 = 0;
    field_4C4 = 0;
    field_564 = 1.0;
    field_568 = 1.0;
    field_571 = 1;
    field_572 = 1;
    field_744 = 0;
    field_74C = 0;

    field_19C = 0;
    field_838 = 0;
    field_526 = 0;
    weather_var = 0;

    speed_mult = 1.0;
    tengu_fan  = 0;

    h_inerc = 0;
    v_inerc = 0;
    v_force = 0;

    not_charge_attack = 1;
    air_dash_cnt = 0;

    enemy = NULL;

    for (uint32_t i=0; i<MAX_CHR_SFX; i++)
        sfx[i] = NULL;

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

void char_c::draw(float x, float y, int8_t dir)
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


    field_80E = viz.get_seq_id() >= 600 && viz.get_seq_id() <= 689;

    if ( viz.get_seq_id() >= 600 && viz.get_seq_id() < 690 )
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
        if ( viz.get_seq_id() >= 50 )
        {
          if ( viz.get_seq_id() <= 149 )
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
        if ( viz.get_seq_id() >= 197 && viz.get_seq_id() <= 199 )
        {
            field_4C2 = 60;
            field_4BE = 100;
        }

        if (viz.get_subseq() == 0)
            if ((viz.get_seq_id() == 70 && viz.get_elaps_frames() >= 18) ||
                    (viz.get_seq_id() >= 180 && viz.get_seq_id() <= 181))
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
            if ( viz.get_seq_id() == 9 )
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
                    if ( viz.get_elaps_frames() >= 300 )
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
                    if ( viz.get_elaps_frames() >= 300 )
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

                    if ( (viz.get_seq_id() <= 9 || viz.get_seq_id() >= 200) && viz.get_seq_id() <= 299 )
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
            if ( viz.get_seq_id() <= 499 || viz.get_seq_id() >= 600 )
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

            if ( viz.get_seq_id() < 100 || (viz.get_seq_id() > 111 && viz.get_seq_id() < 500 ))
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
            field_530 = tmp * 0.34999999 / 600.0 + 1.0;

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

        if ( viz.get_seq_id() != 691 )
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
    if ( grn /*&& v1->field_4C4 == 0*/ )
    {
        air_dash_cnt = 0;
        //v1->field_49C = 0;
    }
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



void char_c::play_sfx(uint32_t idx)
{
    if (sfx[idx % MAX_CHR_SFX] != NULL)
        sfx_play(sfx[idx % MAX_CHR_SFX]);
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


