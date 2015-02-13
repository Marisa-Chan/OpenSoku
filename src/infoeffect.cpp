#include "global_types.h"
#include "scene.h"
#include "graph.h"
#include "moveable.h"
#include "battle_ui.h"
#include "infoeffect.h"

int32_t weather_to_ieid[22] =
{
    100, //0
    110, //1
    120, //2
    130, //3
    140, //4
    150, //5
    160, //6
    170, //7
    180, //8
    190, //9
    210, //10
    220, //11
    230, //12
    240, //13
    250, //14
    260, //15
    270, //16
    280, //17
    290, //18
    300, //19
    310, //20
    320  //21
};

int32_t get_ieid_by_weather(WEATHER_ID id)
{
    return weather_to_ieid[id % WEATHER_ID_COUNT];
}

c_infoef_fx::c_infoef_fx(int32_t idx, gfx_seq *sq, float _x, float _y, int8_t _dir, int8_t _order)
{
    index = idx;
    sprite.set_seq(sq);
    x = _x;
    y = _y;
    dir = _dir;

    active = true;
    order = _order;

    y_to_down = true;

    set_seq_params();
}

void sub_6DC5E0(int8_t flag)
{
    scene_get_scene()->set_start_flag(flag);
}

void c_infoef_fx::func10()
{
    switch(get_seq())
    {
    case 1:
        scaleX += 0.2;
        scaleY += 0.2;
        if (process())
            active = false;
        break;
    case 2:
        if ( get_elaps_frames() == 0 )
            scene_play_sfx(47);
        if (process())
            active = false;
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        if ( get_elaps_frames() == 0 )
            battle_ui_effect(20, x, y, 1, 1);
        if ( get_elaps_frames() < 15 )
            scaleY = scaleX = cos_deg(get_elaps_frames() * 6.0) + 1.0;
        else
        {
            scaleX -= 0.001;
            scaleY -= 0.001;
            if (get_elaps_frames() == 90)
            {
                battle_ui_effect(15, x, y, 1, 1);
                battle_ui_effect(21, x, y, 1, 1);
                active = false;
            }
        }
        if (active)
            if (process())
                active = false;
        break;
    case 15:
        if ( get_elaps_frames() == 30 )
            sub_6DC5E0(1);
        if ( scaleX > 1.5 )
        {
            scaleX += 0.001;
            scaleY += 0.001;
        }
        else
        {
            scaleX += 0.2;
            scaleY += 0.2;
        }
        if ( get_elaps_frames() > 30 )
        {
            scaleX += 0.5;
            scaleY += 0.5;

            if (c_A < 15)
                active = false;
            else
                c_A -= 15;
        }

        if (active)
            if (process())
                active = false;
        break;
    case 16:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(22, x, y, 1, 1);
            scene_play_sfx(44);
        }
        if ( scaleX > 1.5 )
        {
            scaleX += 0.001;
            scaleY += 0.001;
        }
        else
        {
            scaleX += 0.2;
            scaleY += 0.2;
        }
        if ( get_elaps_frames() > 60 )
        {
            scaleX += 0.5;
            scaleY += 0.5;

            if (c_A < 15)
                active = false;
            else
                c_A -= 15;
        }

        if (active)
            if (process())
                active = false;
        break;
    case 17:
        if ( get_elaps_frames() == 0 )
            battle_ui_effect(22, x, y, 1, 1);

        if ( scaleX > 2.0 )
        {
            scaleX += 0.001;
            scaleY += 0.001;
        }
        else
        {
            scaleX += 0.2;
            scaleY += 0.2;
        }
        if ( get_elaps_frames() > 120 )
        {
            scaleX += 0.5;
            scaleY += 0.5;

            if (c_A < 15)
                active = false;
            else
                c_A -= 15;
        }

        if (active)
            if (process())
                active = false;
        break;
    case 18:
        if ( get_elaps_frames() == 0 )
            battle_ui_effect(22, x, y, 1, 1);

        if ( scaleX > 1.5 )
        {
            scaleX += 0.001;
            scaleY += 0.001;
        }
        else
        {
            scaleX += 0.2;
            scaleY += 0.2;
        }
        if ( get_elaps_frames() > 60 )
        {
            scaleX += 0.5;
            scaleY += 0.5;

            if (c_A < 15)
                active = false;
            else
                c_A -= 15;
        }

        if (active)
            if (process())
                active = false;
        break;
    case 20:
        scaleX += 0.001;
        scaleY += 0.001;
        if (get_elaps_frames() == 90)
            active = false;
        if (active)
            if (process())
                active = false;
        break;
    case 21:
    case 22:
        scaleX += 0.3;
        scaleY += 0.3;

        if (c_A < 15)
            active = false;
        else
            c_A -= 15;
        if (active)
            if (process())
                active = false;
        break;
    case 30:
    case 31:
        c_A  = (127.0 - cos_deg(get_elaps_frames() * 12.0) * 127.0);
        if (process())
            active = false;
        break;

    case 100:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(103, x, y - 10.0, 1, 1);
            if ( weather_setted_get() == WEATHER_SUNNY && weather_get() != WEATHER_CLEAR )
                if ( settings_get()->get_gametype() != GAME_TYPE_SCENARIO )
                    battle_ui_effect(105, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0)
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if ( get_elaps_frames() % 60 == 0)
                battle_ui_effect(101, x, y, 1, 2);
        }
        else
        {
            if (c_A > 10)
                c_A -= 10;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SUNNY )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 101:
    case 111:
    case 121:
    case 131:
    case 141:
    case 151:
    case 161:
    case 171:
    case 181:
    case 191:
    case 201:
    case 211:
    case 221:
    case 231:
    case 241:
    case 251:
    case 261:
    case 271:
    case 281:
    case 291:
    case 301:
    case 311:
        c_A = sin_deg(3 * get_elaps_frames()) * 255.0;
        scaleY = scaleX += 0.01;
        if ( get_elaps_frames() <= 60 )
        {
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 102:
    case 112:
    case 122:
    case 132:
    case 142:
    case 152:
    case 162:
    case 172:
    case 182:
    case 192:
    case 202:
    case 212:
    case 222:
    case 232:
    case 242:
    case 252:
    case 262:
    case 272:
    case 282:
    case 292:
    case 302:
    case 312:
        if ( c_A > 10)
        {
            c_A -= 10;
            int32_t frms = get_elaps_frames();
            if (frms > 30 )
                frms = 30;
            scaleY = scaleX = sin_deg(frms * 3) * 20.0 + 1.0;
            if (process())
                active = false;
        }
        else
            active = false;
        break;
    case 103:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SUNNY )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;
    case 104:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_SUNNY)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 105:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_SUNNY )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   110

    case 110:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(113, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_DRIZZLE)
                battle_ui_effect(115, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(111, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_DRIZZLE )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 113:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_DRIZZLE)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 114:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_DRIZZLE)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 115:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_DRIZZLE )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   120

    case 120:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(123, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_CLOUDY )
                battle_ui_effect(125, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(121, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_CLOUDY )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 123:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_CLOUDY)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;
    case 124:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_CLOUDY)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;
    case 125:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_CLOUDY )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   130


    case 130:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(133, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_BLUE_SKY )
                battle_ui_effect(135, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(131, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_BLUE_SKY )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 133:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_BLUE_SKY)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 134:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_BLUE_SKY)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 135:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_BLUE_SKY )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   140

    case 140:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(143, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_HAIL )
                battle_ui_effect(145, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(141, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_HAIL )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 143:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_HAIL)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 144:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_HAIL)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 145:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_HAIL )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   150

    case 150:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(153, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_SPRING_HAZE )
                battle_ui_effect(155, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(151, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_SPRING_HAZE )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 153:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SPRING_HAZE)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 154:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_SPRING_HAZE)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 155:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_SPRING_HAZE )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   160

    case 160:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(163, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_HEAVY_FOG )
                battle_ui_effect(165, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(161, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_HEAVY_FOG )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 163:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_HEAVY_FOG)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 164:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_HEAVY_FOG)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 165:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_HEAVY_FOG )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   170

    case 170:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(173, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_SNOW )
                battle_ui_effect(175, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(171, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_SNOW )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 173:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SNOW)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 174:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_SNOW)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 175:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_SNOW )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   180

    case 180:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(183, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_SUNSHOWER )
                battle_ui_effect(185, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(181, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_SUNSHOWER )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 183:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SUNSHOWER)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 184:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_SUNSHOWER)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 185:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_SUNSHOWER )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   190

    case 190:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(193, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_SPRINKLE )
                battle_ui_effect(195, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(191, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_SPRINKLE )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 193:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SPRINKLE)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 194:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_SPRINKLE)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 195:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_SPRINKLE )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   200

    case 200:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(203, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_DUST_STORM )
                battle_ui_effect(205, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(201, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_DUST_STORM )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 203:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_DUST_STORM)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 204:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_DUST_STORM)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

///////////////   210

    case 210:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(213, x, y - 10.0, 1, 1);
            if ( weather_setted_get() == WEATHER_TEMPEST && weather_get() != WEATHER_CLEAR )
                if ( settings_get()->get_gametype() != GAME_TYPE_SCENARIO )
                    battle_ui_effect(215, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(211, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_TEMPEST )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 213:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_TEMPEST)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 214:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_TEMPEST)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 215:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_TEMPEST )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   220

    case 220:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(223, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_MOUNTAIN_VAPOR )
                battle_ui_effect(225, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(221, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_MOUNTAIN_VAPOR )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 223:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_MOUNTAIN_VAPOR)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 224:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_MOUNTAIN_VAPOR)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 225:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_MOUNTAIN_VAPOR )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   230

    case 230:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(233, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_RIVER_MIST )
                battle_ui_effect(235, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(231, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_RIVER_MIST )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 233:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_RIVER_MIST)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 234:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_RIVER_MIST)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 235:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_RIVER_MIST )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   240

    case 240:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(243, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_TYPHOON )
                battle_ui_effect(245, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(241, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_TYPHOON )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 243:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_TYPHOON)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 244:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_TYPHOON)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 245:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_TYPHOON )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   250

    case 250:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(253, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_CALM )
                battle_ui_effect(255, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(251, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_CALM )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 253:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_CALM)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 254:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_CALM)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 255:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_CALM )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   260

    case 260:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(263, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_DIAMOND_DUST )
                battle_ui_effect(265, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(261, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_DIAMOND_DUST )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 263:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_DIAMOND_DUST)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 264:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_DIAMOND_DUST)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 265:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_DIAMOND_DUST )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   270

    case 270:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(273, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_DUST_STORM )
                battle_ui_effect(275, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(271, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_DUST_STORM )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 273:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_DUST_STORM )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 274:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_DUST_STORM)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 205:
    case 275:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_DUST_STORM )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   280

    case 280:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(283, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_SCORCHING_SUN )
                battle_ui_effect(285, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(281, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_SCORCHING_SUN )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 283:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_SCORCHING_SUN )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 284:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_SCORCHING_SUN)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 285:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_SCORCHING_SUN )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   290

    case 290:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(293, x, y - 10.0, 1, 1);
            if ( weather_get() == WEATHER_MONSOON )
                battle_ui_effect(295, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(291, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_MONSOON )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 293:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_MONSOON )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 294:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_MONSOON)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 295:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_MONSOON )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   300

    case 300:
        if ( get_elaps_frames() == 0 )
        {
            battle_ui_effect(303, x, y - 10.0, 1, 1);
            if ( weather_setted_get() == WEATHER_AURORA && weather_get() != WEATHER_CLEAR )
                if ( settings_get()->get_gametype() != GAME_TYPE_SCENARIO)
                    battle_ui_effect(305, 320.0, 120.0, 1, 1);
        }
        if ( par2 == 0.0 )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(301, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if ( weather_setted_get() != WEATHER_AURORA )
            par2 = 1.0;

        if (process())
            active = false;
        break;

    case 303:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_AURORA )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 304:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_AURORA)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 305:
        if (par2 == 0.0)
        {
            scaleY = scaleX -= 0.25;
            if (scaleX <= 1.0)
            {
                if (c_A > 240)
                    c_A = 255;
                else
                    c_A += 15;
                scaleY = scaleX = 1.0;
                par2 = 1.0;
            }
        }
        else
        {
            par2 += 1.0;
            if (par2 >= 90.0)
            {
                scaleY *= 0.95;
                scaleX += 0.1;
                if (c_A <= 15)
                    active = false;
                else
                    c_A -= 15;
            }
        }
        if ( weather_setted_get() != WEATHER_AURORA )
        {
            if (c_A <= 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        if (active)
            if (process())
                active = false;
        break;

///////////////   310

    case 310:
        if ( get_elaps_frames() == 0 )
            battle_ui_effect(313, x, y - 10.0, 1, 1);

        if ( weather_setted_get() == WEATHER_HISOUTEN  )
        {
            if ( c_A >= 245 )
                c_A = 255;
            else
                c_A += 10;
            if (get_elaps_frames() % 60 == 0)
                battle_ui_effect(311, x, y, 1, 2);
        }
        else
        {
            if ( c_A <= 10 )
                active = false;
            else
                c_A -= 10;
        }

        if (process())
            active = false;
        break;

    case 313:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if ( weather_setted_get() != WEATHER_HISOUTEN )
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

    case 314:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;
        if (par2 == 0)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if ( weather_index_for_name_get() != WEATHER_HISOUTEN)
            par2 = 1.0;

        if (active)
            if (process())
                active = false;
        break;

///////////////   320

    case 320:
        if ( get_elaps_frames() == 0 )
            battle_ui_effect(323, x, y - 10.0, 1, 1);

        if (process())
            active = false;
        break;

    case 323:
        if ( weather_setted_get() == WEATHER_CLEAR && weather_index_for_name_get() == WEATHER_CLEAR )
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }

        if (active)
            if (process())
                active = false;
        break;

    case 394:
        scaleX -= 0.1;
        if (scaleX < 1.0)
            scaleX = 1.0;
        scaleY = scaleX;

        if (weather_index_for_name_get() == WEATHER_CLEAR)
        {
            if (c_A >= 245)
                c_A = 255;
            else
                c_A += 10;
        }
        else
        {
            if (c_A > 20)
                c_A -= 20;
            else
                active = false;
        }
        if (active)
            if (process())
                active = false;
        break;
    case 900:
    case 901:
    case 902:
    case 903:
    case 904:
    case 905:
    case 906:
    case 907:
    case 908:
    case 909:
    case 910:
    case 911:
    case 912:
    case 913:
    case 914:
    case 915:
    case 916:
    case 917:
    case 918:
    case 919:
    case 920:
    case 921:
    case 922:
    case 930:
    case 931:
    case 932:
    case 933:
    case 934:
    case 935:
    case 940:
    case 941:
    case 942:
    case 943:
        if ( get_frame_time() > 150 )
        {
            if (c_A > 5)
                c_A -= 5;
            else
                active = false;
        }
        else if ( get_frame_time() < 30 )
        {
            x = (1.0 - sin_deg(get_frame_time() * 3.0)) * 480.0 + 640.0;
        }
        if (process())
            active = false;
        break;
    default:
        if (process())
            active = false;
        break;
    }
}

void c_infoef_fx::set_seq_params()
{
    switch(get_seq())
    {
    case 10:
    case 11:
    case 12:
    case 13:
        scaleX = 2.0;
        scaleY = 2.0;
        break;
    case 15:
    case 16:
    case 17:
    case 18:
        scaleX = 0.5;
        scaleY = 0.5;
        break;
    case 20:
        c_A = 128;
        break;
    case 22:
        scene_play_sfx(44);
        break;
    case 32:
        //x_off = 20.0;
        //y_off = -33.0;
        break;
    case 103:
    case 104:
    case 113:
    case 114:
    case 123:
    case 124:
    case 133:
    case 134:
    case 143:
    case 144:
    case 153:
    case 154:
    case 163:
    case 164:
    case 173:
    case 174:
    case 183:
    case 184:
    case 193:
    case 194:
    case 203:
    case 204:
    case 213:
    case 214:
    case 223:
    case 224:
    case 233:
    case 234:
    case 243:
    case 244:
    case 253:
    case 254:
    case 263:
    case 264:
    case 273:
    case 274:
    case 283:
    case 284:
    case 293:
    case 294:
    case 303:
    case 304:
    case 313:
    case 314:
        scaleX = 4.0;
        scaleY = 4.0;
    case 100:
    case 101:
    case 110:
    case 111:
    case 120:
    case 121:
    case 130:
    case 131:
    case 140:
    case 141:
    case 150:
    case 151:
    case 160:
    case 161:
    case 170:
    case 171:
    case 180:
    case 181:
    case 190:
    case 191:
    case 200:
    case 201:
    case 210:
    case 211:
    case 220:
    case 221:
    case 230:
    case 231:
    case 240:
    case 241:
    case 250:
    case 251:
    case 260:
    case 261:
    case 270:
    case 271:
    case 280:
    case 281:
    case 290:
    case 291:
    case 300:
    case 301:
    case 310:
    case 311:
        c_A = 0;
    case 102:
    case 112:
    case 122:
    case 132:
    case 142:
    case 152:
    case 162:
    case 172:
    case 182:
    case 192:
    case 202:
    case 212:
    case 222:
    case 232:
    case 242:
    case 252:
    case 262:
    case 272:
    case 282:
    case 292:
    case 302:
    case 312:
        par2 = 0.0;
        break;
    case 105:
    case 115:
    case 125:
    case 135:
    case 145:
    case 155:
    case 165:
    case 175:
    case 185:
    case 195:
    case 205:
    case 215:
    case 225:
    case 235:
    case 245:
    case 255:
    case 265:
    case 275:
    case 285:
    case 295:
    case 305:
    case 315:
        par2 = 0.0;
        c_A = 0;
        scaleX = 5.0;
        scaleY = 5.0;
        break;
    case 30:
    case 31:
    case 320:
    case 323:
        c_A = 0;
        break;
    default:
        break;
    }
}


c_infoef_sp::c_infoef_sp()
{
    load_dat("effect.pat","data/infoeffect");
}

c_infoef_fx *c_infoef_sp::addeffect(int32_t idx, float x, float y, int8_t dir, int8_t order)
{
    gfx_seq *sq = get_seq(idx);
    if (sq)
    {
        c_infoef_fx *ff = new c_infoef_fx(idx, sq, x, y, dir, order);
        fx.push_back(ff);
        return ff;
    }
    return NULL;
}
