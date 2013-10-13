#include "global_types.h"
#include <math.h>
#include "scene.h"
#include "graph.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"
#include "archive.h"
#include "file_read.h"

c_scene_sp::c_scene_sp()
{
    load_dat("effect.pat","data/effect");
}

void c_scene_sp::addeffect(c_meta *chr, int32_t idx, float x, float y, int8_t dir, int8_t order)
{
    gfx_seq *sq = get_seq(idx);
    if (sq)
    {
        c_scene_fx *ff = new c_scene_fx(idx, sq, chr, x,y,dir, order);
        fx.push_back(ff);
    }
}









c_scene_fx::c_scene_fx(int32_t idx, gfx_seq *sq, c_meta *chr, float _x, float _y, int8_t _dir, int8_t _order)
{
    index = idx;
    sprite.set_seq(sq);
    x = _x;
    y = _y;
    dir = _dir;

    active = true;
    parent = chr;
    order = _order;

    set_seq_params();
}


void c_scene_fx::func10()
{
    switch(get_seq())
    {
    case 1:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);
            for (int8_t i = 0; i < 4; i++)
                scene_add_effect(parent, 101, x,y,dir,1);
        }
        if (process())
            active = false;
        break;
    case 2:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            for (int8_t i = 0; i < 6; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 3; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        if (process())
            active = false;
        break;
    case 3:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);
            scene_add_effect(parent, 100, x,y,dir,1);

            for (int8_t i = 0; i < 8; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 6; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        if (process())
            active = false;
        break;
    case 4:
        if ( get_elaps_frames() == 0)
        {
            angZ = scene_rand_rng(360);
            scene_add_effect(parent, 104, x,y,dir,1);

            for (int8_t i = 0; i < 10; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 6; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        if (process())
            active = false;
        break;
    case 5:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            for (int8_t i = 0; i < 4; i++)
                scene_add_effect(parent, 101, x,y,dir,1);
        }
        if (process())
            active = false;
        break;
    case 6:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            for (int8_t i = 0; i < 6; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 3; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        if (process())
            active = false;
        break;

    case 7:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            scene_add_effect(parent, 100, x,y,dir,1);

            for (int8_t i = 0; i < 8; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 3; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        scaleY = scaleX += 0.1;

        if (process())
            active = false;
        break;
    case 8:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            scene_add_effect(parent, 100, x,y,dir,1);

            for (int8_t i = 0; i < 10; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 5; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        scaleY = scaleX += 0.1;

        if (process())
            active = false;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
        if ( get_elaps_frames() == 0 )
            angZ = scene_rand_rng(40) - 20;

        if (process())
            active = false;
        break;
    case 13:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            scene_add_effect(parent, 105, x,y,dir,1);

            for (int8_t i = 0; i < 4; i++)
                scene_add_effect(parent, 102, x,y,dir,1);
        }
        if (process())
            active = false;
        break;
    case 14:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);

            scene_add_effect(parent, 106, x,y,dir,1);

            for (int8_t i = 0; i < 6; i++)
                scene_add_effect(parent, 102, x,y,dir,1);
        }
        if (process())
            active = false;
        break;
    case 15:
    case 16:
    case 38:
        if ( get_elaps_frames() == 0 )
            angZ = scene_rand_rng(360);

        if (process())
            active = false;
        break;
    case 50:
        if ( get_elaps_frames() == 0 )
            for (int8_t i = 0; i < 4; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

        if (process())
            active = false;
        break;
    case 51:
        if ( get_elaps_frames() == 0 )
            for (int8_t i = 0; i < 4; i++)
                scene_add_effect(parent, 103, x,y,dir,1);

        if (process())
            active = false;
        break;
    case 52:
        if ( get_elaps_frames() == 0 )
        {
            scene_play_sfx(37);
            for (int8_t i = 0; i < 3; i++)
                scene_add_effect(parent, 101, x,y,dir,1);
        }

        if (process())
            active = false;
        break;
    case 53:
        if ( get_elaps_frames() == 0 )
        {
            scene_play_sfx(38);
            scene_add_effect(parent, 104, x,y,dir,1);

            for (int8_t i = 0; i < 16; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 8; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }

            for (int8_t i = 0; i < 6; i++)
                scene_add_effect(parent, 200, x,y,dir,1);

            for (int8_t i = 0; i < 10; i++)
                scene_add_effect(parent, 201, x,y,dir,1);
        }
        angZ += 5;
        scaleX += 0.3;
        scaleY += 0.3;

        if (c_A >= 10)
        {
            c_A -= 10;
            c_R -= 10;
            c_G -= 10;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 54:
        if ( get_elaps_frames() == 0 )
        {
            scene_play_sfx(25);
            scene_add_effect(parent, 104, x,y,dir,1);

            for (int8_t i = 0; i < 8; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 4; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        scaleX += 0.3;
        scaleY += 0.3;

        if (c_A >= 10)
        {
            c_A -= 10;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 58:
    case 59:
        scaleY = scaleX += 0.4;
        if (c_A >= 20)
        {
            c_A -= 20;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 61:
        if ( get_elaps_frames() == 0 )
            scene_play_sfx(43);

        scaleX += 0.3;
        scaleY += 0.3;

        if (c_A >= 20)
        {
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 62:
        if (get_elaps_frames() == 0)
        {
            scene_play_sfx(45);
            scene_add_effect(parent, 113,x,y,dir,1);
        }
        scaleX+=0.2;
        scaleY+=0.2;

        if (c_A >= 25)
        {
            c_A -= 25;
            c_R -= 25;
            c_G -= 25;
            if (process())
                active = false;
        }
        else
            active = false;

        break;
    case 63:
        if ( get_elaps_frames() == 0 )
        {
            scene_play_sfx(43);
            scene_add_effect(parent,60,x,y,dir,-1);
        }
        scaleX += 0.1;
        scaleY += 0.15;
        if (process())
            active = false;
        break;
    case 64:
        if ( get_elaps_frames() == 0 )
        {
            scene_play_sfx(50);

            scene_add_effect(parent, 104, x,y,dir,1);

            for (int8_t i = 0; i < 16; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 8; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        scaleX += 0.3;
        scaleY += 0.3;

        if (c_A >= 10)
        {
            c_A -= 10;
            if (process())
                active = false;
        }
        else
            active = false;
        break;

    case 65:
    case 66:
    case 67:
    case 68:
        if ( get_elaps_frames() == 0 )
        {
            scene_add_effect(parent, 104, x,y,dir,1);

            for (int8_t i = 0; i < 16; i++)
                scene_add_effect(parent, 101, x,y,dir,1);

            for (int8_t i = 0; i < 8; i++)
            {
                scene_add_effect(parent, 102, x,y,dir,1);
                scene_add_effect(parent, 103, x,y,dir,1);
            }
        }
        scaleX += 0.3;
        scaleY += 0.3;

        if (c_A >= 10)
        {
            c_A -= 10;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 69:
        if ( get_elaps_frames() == 0 )
            scene_play_sfx(35);

        scaleX += 0.3;
        scaleY += 0.3;
        angZ -= 25;

        if (c_A >= 15)
        {
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;

        break;
    case 70:
        if ( get_elaps_frames() == 0 )
            scene_play_sfx(53);

        scaleX += 0.3;
        scaleY += 0.3;
        angZ -= 25;

        if (c_A >= 15)
        {
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;

        break;
    case 71:
        if ( get_elaps_frames() == 0 )
            scene_play_sfx(54);

        if ( get_frame() == 0 )
            scaleY = scaleX *= 0.8;
        else if (get_frame() == 1)
        {
            scaleY = scaleX += 0.3;
            angZ -= 25;

            if (c_A >= 15)
            {
                c_A -= 15;
                c_B -= 15;
            }
            else
            {
                active = false;
            }
        }

        if (active && process())
            active = false;

        break;
    case 100:
        scaleX += 0.5;
        scaleY += 0.5;

        if (c_A >= 20)
        {
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 101:
        v_inerc--;
        y += v_inerc;
        x += h_inerc;

        if ( v_inerc < 0.0  &&  y < 0.0 )
            if ( scene_rand_rng(100) < 15 )
                v_inerc = (-v_inerc) * 0.5;

        if (c_A > 20)
        {
            scaleX *= 0.8;
            scaleY *= 0.8;
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;

            if (scaleX <= 0 || process())
                active=false;
        }
        else
            active = false;
        break;
    case 102:
    case 103:
        x += h_inerc*dir;
        y += v_inerc;

        if (c_A > 10)
        {
            scaleY *= 0.98;
            scaleX += 0.05;
            c_A -= 10;
            if (process())
                active = false;
        }
        else
            active = false;

        break;
    case 104:
        scaleX += 1.25;
        scaleY += 1.25;

        if (c_A >= 20)
        {
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 105:
        scaleY = scaleX += 0.15;
        if (c_A > 15)
        {
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 60:
    case 106:
        scaleX += 0.4;
        scaleY += 0.4;

        if (c_A >= 20)
        {
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 112:
    case 137:
    {
        c_meta *chr = parent;
        if ( chr )
        {
            x = chr->getX();
            y = chr->getY()+100;

            par1 -= 0.3;
            if (par1 < 1.0)
                par1 = 1.0;
            par2 += 3.0;
            if (get_seq() == 137)
            {
                angZ ++;
                scaleY = scaleX = (sin_deg(par2) * 0.1 + 1.1) * par1;
            }
            else
            {
                angZ --;
                scaleY = scaleX = (sin_deg(par2) * 0.1 + 1.0) * par1;
            }
            if (get_frame() == 0)
            {
                if (chr->chrt->damage_limit < 100 || chr->chrt->get_seq() == 99)
                    if ( chr->chrt->field_4C2 <= 0)
                    {
                        set_frame(1);
                        break;
                    }
            }

            if (get_frame() == 1)
            {
                if (c_A > 20)
                {
                    c_A -= 20;
                    c_R -= 20;
                    c_G -= 20;
                }
                else
                    active = false;
            }

            if (active && process() )
                active = false;

        }
        else
            active = false;
    }
    break;
    case 113:

        scaleX+=0.4;
        scaleY+=0.4;
        if (c_A >= 15)
        {
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;

        break;
    case 115:
        if ( get_elaps_frames() == 0 )
        {
            angZ = scene_rand_rng(360);
            scaleX = 2.0;
            scaleY = 2.0;
        }
        angZ += 2;
        if (get_frame() == 41)
        {
            if (c_A >= 5)
                c_A -= 5;
            else
                active = false;
        }
        if (active && process())
            active = false;
        break;
    case 123:
        if ( get_elaps_frames() == 0 )
            v_inerc = -10;

        if (c_A >= 15)
        {
            y += v_inerc;
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 124:
        if ( get_elaps_frames() == 0 )
            h_inerc = -10.0;

        if ( c_A >= 15 )
        {
            x += dir * h_inerc;
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;

        break;
    case 125:
        scaleX += 0.2;
        scaleY += 0.2;

        if (c_A >= 25)
        {
            c_A -= 25;
            c_R -= 25;
            c_G -= 25;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 136:
        scaleX -= 0.005;
        scaleY += 0.02;
        y += 15;

        c_A = sin_deg(get_elaps_frames() * 6) * 255.0;
        if (get_elaps_frames() * 6 >= 180)
            active = false;

        if (active && process())
            active = false;

        break;
    case 131:
    case 132:
    case 133:
    case 134:
    case 139:
        if (get_elaps_frames() == 0)
            v_inerc = 20;

        v_inerc--;
        if (v_inerc < 1)
            v_inerc = 1;

        scaleX += 0.1;
        if (scaleX > 1)
            scaleX = 1;

        scaleY = scaleX;

        if (get_elaps_frames() >= 60)
        {
            if (c_A > 15)
                c_A -= 15;
            else
                active = false;
        }
        y += v_inerc;
        if (active && process())
            active = false;
        break;
    case 140:
        scaleX += par1 * 0.5;
        par1 *= 0.94;

        if (c_A >= 5)
        {
            c_A -= 5;
            c_R -= 5;
            c_G -= 5;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 141:
        scaleY = scaleX *= 0.85;
        if (c_A >= 15)
        {
            c_A -= 15;
            c_R -= 15;
            c_G -= 15;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 135:
    case 142:
        scaleY = scaleX += 0.3;
        if (c_A >= 15)
        {
            c_A -= 15;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 150:
    case 152:
    case 154:
        scaleY = scaleX += 0.15;
        if (c_A >= 15)
        {
            c_A -= 15;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 151:
    case 153:
    case 155:
        if (par1 == 0)
        {
            if (c_A >= 240)
            {
                c_A = 255;
                par1 = 1.0;
                y += 10;
                if (process())
                    active = false;
                break;
            }
            c_A += 15;
        }
        else
        {
            if (c_A < 15)
            {
                active = false;
                break;
            }
            c_A -= 15;
        }
        y += 10;

        if (active && process())
            active = false;
        break;
    case 160:
        if ( get_elaps_frames() >= 25 )
        {
            if (c_A >= 15 )
                c_A -= 15;
            else
            {
                active = false;
                break;
            }
        }
        if (get_elaps_frames() % 6 == 0)
            scene_add_effect(parent,161,x,y,dir,-1);

        angZ += 6;
        v_inerc -= 0.3;
        h_inerc *= 0.96;

        if ( v_inerc + y <= 0 && v_inerc < 0 )
            v_inerc = -v_inerc;

        x += h_inerc * dir;
        y += v_inerc;

        if ( process() )
            active = false;
        break;
    case 161:
        if ( c_A >= 15 )
        {
            c_A -= 15;
            v_inerc -= 0.005;
            y += v_inerc;

            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 162:
    case 163:
    case 164:
        if (c_A >= par1)
        {
            angZ += par2;
            c_A -= par1;

            v_inerc -= 0.3;
            h_inerc *= 0.92;

            if (y + v_inerc <= 0 && v_inerc < 0)
                v_inerc = -v_inerc;

            x += h_inerc * dir;
            y += v_inerc;

            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 165:
        if (c_A >= 15)
        {
            c_A -= 15;
            angZ -= 15;
            scaleY = scaleX += 0.3;

            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 200:
        if ( get_elaps_frames() == 0 )
            set_vec_speed(scene_rand_rng(180),scene_rand_rng(10) + 5);

        angZ += 6;
        v_inerc -= 0.5;

        if (scene_rand_rng(100) < 20)
            scene_add_effect(parent,202,x,y,dir,1);

        if (v_inerc < 0 && y < 0)
        {
            if (scene_rand_rng(100) < 20)
                v_inerc = (-v_inerc) * 0.5;
            set_elaps_frames(60);
        }

        if ( get_elaps_frames() <= 60 || c_A >= 15 )
        {
            if( get_elaps_frames() > 60 )
                c_A -= 15;
            x += h_inerc * dir;
            y += v_inerc;

            if ( process() )
                active = false;
        }
        else
        {
            //HACK
            /*if ( weather == 21 )
            {
                weather_time += 40;
                if ( weather_time > 999 )
                    weather_time = 999;
            }
            else if ( weather_time >= 41 )
            {
                weather_time -= 40;
            }
            else
            {
                weather_time = 1;
            }*/
            scene_play_sfx(26);
            active = false;
        }
        break;
    case 201:
        if ( get_elaps_frames() == 0 )
            set_vec_speed(scene_rand_rng(180),scene_rand_rng(8)+4);

        angZ -= 12;
        v_inerc -= 0.25;

        if (scene_rand_rng(100) < 10)
            scene_add_effect(parent, 202, x,y,dir,1);

        if ( v_inerc < 0.0 && y < 0.0 )
        {
            if ( scene_rand_rng(100) < 20 )
                v_inerc = (-v_inerc) * 0.5;
            set_elaps_frames(60);
        }

        if ( get_elaps_frames() <= 60 || c_A >= 15 )
        {
            if( get_elaps_frames() > 60 )
                c_A -= 15;
            x += h_inerc * dir;
            y += v_inerc;

            if ( process() )
                active = false;
        }
        else
        {
            //HACK
            /*if ( weather == 21 )
            {
                weather_time += 5;
                if ( weather_time > 999 )
                    weather_time = 999;
            }
            else if ( weather_time >= 6 )
            {
                weather_time -= 5;
            }
            else
            {
                weather_time = 1;
            }*/
            scene_play_sfx(26);
            active = false;
        }
        break;
    case 202:
        if ( get_elaps_frames() == 0 )
            set_vec_speed(scene_rand_rng(180),1.0);

        v_inerc -= 0.05;

        if ( scaleX > 0.0 )
        {
            scaleX -= 0.01;
            scaleY -= 0.01;
        }

        if ( c_A >= 15 )
        {
            c_A -= 15;
            c_B -= 10;
            c_G -= 10;

            y += v_inerc;
            x += h_inerc * dir;

            if ( process() )
                active = false;
        }
        else
            active = false;
        break;
    case 126:
    case 127:
    case 128:
    case 129:
    case 138:
        if (process())
            active = false;
        break;
    default:
        active = false;
    }
}

void c_scene_fx::set_seq_params()
{
    switch(get_seq())
    {
    case 51:
        scaleY = scaleX = 2.0;
        break;
    case 53:
    case 54:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 165:
    case 200:
    case 201:
        angZ = scene_rand_rng(360);
        break;
    case 59:
        angZ = 90;
        break;
    case 62:
        scaleX = scaleY =0.1;
        break;

    case 101:
        scaleY = scaleX = scene_rand_rng(200) * 0.01 + 0.1;
        h_inerc = scene_rand_rng(60) - 30;
        v_inerc = scene_rand_rng(60) - 30;
        break;
    case 102:
    case 103:
        scaleX = scene_rand_rng(1400) * 0.01 + 2.0;
        scaleY = scene_rand_rng(300) * 0.01 + 1.0;
        angZ = scene_rand_rng(360);
        set_vec_speed_2(-angZ, scene_rand_rng(20) + 5);
        break;
    case 112:
        scaleY = scaleX = 3.0;
        par1 = 3.0;
        par2 = 0.0;
        angZ = scene_rand_rng(360);
        break;
    case 125:
        if ( parent->get_seq() == 214 )
        {
            if ( parent->get_subseq() == 1 || parent->get_subseq() == 2 )
                angZ = parent->angZ;
            else if ( parent->get_subseq() == 3 || parent->get_subseq() == 4 )
                angZ = -parent->angZ + 180.0;
        }
        break;
    case 135:
        angX = 80;
        break;
    case 136:
        scaleX = scene_rand_rng(15) * 0.1 + 0.5;
        scaleY = scene_rand_rng(10) * 0.1 + 1.0;
        c_A = 0;
        break;
    case 137:
        scaleY = scaleX = 1.0;
        par1 = 1.0;
        par2 = 0;
        angZ = scene_rand_rng(360);
        break;
    case 138:
        scaleY = scaleX = 2.0;
        angZ = scene_rand_rng(360);
        break;
    case 140:
        par1 = 1.0;
        angZ = scene_rand_rng(360);
        angX = scene_rand_rng(140) - 70;
        angY = scene_rand_rng(140) - 70;
        break;
    case 142:
        par1 = 1.0;
        break;
    case 150:
    case 152:
    case 154:
        par1 = 0.0;
        break;
    case 151:
    case 153:
    case 155:
        c_A = 0;
        par1 = 0.0;
        break;
    case 160:
        angZ = scene_rand_rng(360);
        v_inerc = scene_rand_rng(30) * 0.1 + 6.0;
        h_inerc = scene_rand_rng(50) * 0.1 + 10.0;
        scene_add_effect(parent, 162, x,y,dir, 1);
        scene_add_effect(parent, 162, x,y,dir, 1);
        scene_add_effect(parent, 163, x,y,dir, 1);
        scene_add_effect(parent, 163, x,y,dir, 1);
        scene_add_effect(parent, 164, x,y,dir, 1);
        scene_add_effect(parent, 164, x,y,dir, 1);
        scene_add_effect(parent, 165, x,y,dir, 1);
        scene_play_sfx(58);
        break;
    case 161:
        angZ = scene_rand_rng(360);
        v_inerc = 0.0;
        break;
    case 162:
    case 163:
    case 164:
        angZ = scene_rand_rng(360);
        scaleY = scaleX = scene_rand_rng(60) * 0.01 + 0.7;
        par1 = scene_rand_rng(6) + 4.0;
        par2 = 7.0 - scene_rand_rng(14);
        v_inerc = scene_rand_rng(120) * 0.1 + 2.0;
        h_inerc = scene_rand_rng(300) * 0.1 + 20.0;
        break;
    case 202:
        scaleY = scaleX = scene_rand_rng(100) * 0.01 + 0.5;
        angZ = scene_rand_rng(360);
        break;
    case 300:
    case 301:
    case 306:
    case 307:
    case 308:
    case 309:
        c_A = 0;
        angZ = 10;
        break;
    case 302:
        angZ = 80 - scene_rand_rng(25);
        set_vec_speed(angZ,60);
        break;
    case 303:
        angZ = 80 - scene_rand_rng(25);
        set_vec_speed(angZ,50);
        break;
    case 304:
        c_A = 0;
        angZ = scene_rand_rng(15);
        break;
    }
}








