#include "global_types.h"
#include "scene.h"
#include "graph.h"

#include "file_read.h"
#include "archive.h"

#include "infoeffect.h"
#include "battle_ui.h"
#include "weather.h"
#include "text.h"

//Weather don't change from level to level, when we not needed in reloading this data
t_weather_manager *weather_manager = NULL;

WEATHER_ID weather_id_efx = WEATHER_CLEAR;
uint32_t weather_efx_time = 0;

c_weather_fx::c_weather_fx(int32_t idx, gfx_seq *sq, float _x, float _y, int8_t _dir, int8_t _order)
{
    index = idx;
    sprite.set_seq(sq);
    x = _x;
    y = _y;
    dir = _dir;

    active = true;
    order = _order;

    set_Y_to_up(true);

    set_seq_params();
}



void c_weather_fx::func10()
{
//    v1 = this;
    int32_t stage_number = scene_get_scene()->get_stage_id();

    int32_t v2 = 0;
    switch ( stage_number )
    {
    case 4:
    case 6:
    case 14:
    case 16:
        v2 = 1;
        break;
    case 5:
        v2 = 2;
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 10:
    case 11:
    case 12:
    case 13:
    case 15:
    case 17:
    case 18:
        v2 = 0;
        break;
    default:
        break;
    }
    switch ( get_seq())
    {
    case 1:
    case 3:
        if ( weather_id_efx != WEATHER_SUNNY || v2 != 0 )
            par1 = 1;
        if (par1 == 1)
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (active)
        {
            if (process())
                active = false;
            else
            {
                x -= 1.0;
                if (get_elaps_frames() >= 180)
                    active = false;
            }
        }
        break;
    case 2:
    case 4:
        if ( weather_id_efx != WEATHER_SUNNY || v2 != 0 )
            par1 = 1;
        if (par1 == 1)
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (active)
        {
            if (process())
                active = false;
            else
            {
                x += 1.0;
                if (get_elaps_frames() >= 180)
                    active = false;
            }
        }
        break;
    case 5:
        if ( weather_id_efx != WEATHER_SUNNY || v2 != 0 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 235 )
                c_A = 255;
            else
                c_A += 20;
        }
        if (active)
            if (process())
                active = false;
        break;
    case 11:
        if ( weather_id_efx != WEATHER_DRIZZLE || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        if (active)
        {
            if (process())
                active = false;

            y += sin_deg(-100) * 6.0;
            x += cos_deg(-100) * 6.0;
            if ( get_elaps_frames() <= 60 )
            {
                if (c_A >= 250)
                    c_A = 255;
                else
                    c_A += 5;
            }
            if (get_elaps_frames() >= 180 || y < 480.0)
            {
                if (c_A <= 10)
                    active = false;
                else
                    c_A -= 10;
            }
        }
        break;

    case 41:
        if ( weather_id_efx != WEATHER_HAIL || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }

        if (get_frame() == 0)
        {
            if ( y + v_inerc <= -100.0)
            {
                h_inerc *= 0.5;
                set_frame(1);
                v_inerc *= 0.15;
                break;
            }
            else if ( y <= 0.0 && scene_rand_rng(100) <= 30 )
            {
                h_inerc *= 0.5;
                set_frame(1);
                v_inerc *= 0.25;
                break;
            }
        }

        if ( get_frame() != 1 )
        {
            y += v_inerc;
            x += h_inerc;
            if (process())
                active = false;
        }

        if (active)
        {
            v_inerc -= 0.75;

            if (c_A < 10)
                active = false;
            else
                c_A -= 10;

            if (active)
            {
                y += v_inerc;
                x += h_inerc;
                if (process())
                    active = false;
            }
        }
        break;

    case 42:
        if ( weather_id_efx != WEATHER_HAIL || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }

        if ( (get_frame() == 0 && y + v_inerc <= 0) || (y < 50.0 && scene_rand_rng(100) <= 30) )
        {
            h_inerc *= 0.5;
            v_inerc *= 0.15;
            set_frame(1);
            break;
        }

        if (active)
        {
            if ( get_frame() == 1 )
            {
                v_inerc -= 0.5;
                if (c_A < 10)
                    active = false;
                else
                    c_A -= 10;
            }
            y += v_inerc;
            x += h_inerc;
            if (process())
                active = false;
        }
        break;
    case 61:
        if ( weather_id_efx != WEATHER_HEAVY_FOG || v2 == 1 || v2 == 2 )
            par1 = 1;

        if ( par1 == 1 )
        {
            if ( c_A < 0xAu )
                active = false;
            else
                c_A -= 10;
        }
        else
        {
            if ( c_A > 125 )
                c_A = 128;
            else
                c_A += 3;
        }
        par3 += 0.25;
        setSkew(par3,0);

        if (process())
            active = false;
        break;

    case 62:
    case 63:
        if ( weather_id_efx != WEATHER_HEAVY_FOG || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 || get_elaps_frames() > 180 )
        {
            if ( c_A < 3 )
                active = false;
            else
                c_A -= 3;
        }
        else
        {
            if ( c_A > 125 )
                c_A = 128;
            else
                c_A += 3;
        }
        x -= 0.6;
        if (process())
            active = false;
        break;

    case 71:
        if ( weather_id_efx != WEATHER_SNOW || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 || get_elaps_frames() > 240 )
        {
            if (c_A < 3)
                active = false;
            else
                c_A -= 3;
        }
        else
        {
            if (c_A > 252)
                c_A = 255;
            else
                c_A += 3;
        }
        if (y < -200)
            active = false;
        else
        {
            h_inerc += sin_deg(4 * get_elaps_frames()) * 0.02;
            x += h_inerc * dir;
            y += v_inerc;
            if (process())
                active = false;
        }
        break;
    case 72:
        angZ += 1.0;
        if ( weather_id_efx != WEATHER_SNOW || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 || get_elaps_frames() > 240 )
        {
            if (c_A < 3)
                active = false;
            else
                c_A -= 3;
        }
        else
        {
            if (c_A > 252)
                c_A = 255;
            else
                c_A += 3;
        }
        if (y < -200)
            active = false;
        else
        {
            h_inerc += sin_deg(4 * get_elaps_frames()) * 0.05;
            x += h_inerc * dir;
            y += v_inerc;
            if (process())
                active = false;
        }
        break;

    case 81:
        if ( weather_id_efx != WEATHER_SUNSHOWER || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 252 )
                c_A = 255;
            else
                c_A += 3;
        }
        if (process())
            active = false;
        break;

    case 82:
    case 84:
        if ( weather_id_efx != WEATHER_SUNSHOWER || v2 == 1 || v2 == 2 )
            par1 = 1;
        if (par1 == 1)
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (active)
        {
            if (process())
                active = false;
            else
            {
                x -= 1.0;
                if (get_elaps_frames() >= 180)
                    active = false;
            }
        }
        break;
    case 83:
    case 85:
        if ( weather_id_efx != WEATHER_SUNSHOWER || v2 == 1 || v2 == 2 )
            par1 = 1;
        if (par1 == 1)
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (active)
        {
            if (process())
                active = false;
            else
            {
                x += 1.0;
                if (get_elaps_frames() >= 180)
                    active = false;
            }
        }
        break;

    case 86:
        if ( weather_id_efx != WEATHER_SUNSHOWER || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A > 235)
                c_A = 255;
            else
                c_A += 20;
        }
        break;
    case 91:
        if ( weather_id_efx != WEATHER_SPRINKLE || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        if (process())
            active = false;
        y += sin_deg(-angZ) * 60.0;
        x += cos_deg(-angZ) * 60.0;

        if ( get_elaps_frames() <= 20 )
        {
            if (c_A >= 240)
                c_A = 255;
            else
                c_A += 15;
        }
        if (get_elaps_frames() >= 180 || y < 480.0)
        {
            if (c_A <= 25)
                active = false;
            else
                c_A -= 25;
        }
        break;
    case 101:
        if ( weather_id_efx != WEATHER_DUST_STORM || v2 == 1 || v2 == 2 )
            par1 = 1;

        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if (c_A > 125)
                c_A = 128;
            else
                c_A += 3;
        }
        par3 += 0.5;
        setSkew(par3,0);

        if (process())
            active = false;
        break;
    case 111:
        if ( weather_id_efx != WEATHER_TEMPEST || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        if (process())
            active = false;

        y += sin_deg(-angZ - 90.0) * 40.0;
        x += cos_deg(-angZ - 90.0) * 40.0;

        if ( get_elaps_frames() <= 20 )
        {
            if (c_A >= 240)
                c_A = 255;
            else
                c_A += 15;
        }
        if (get_elaps_frames() >= 180 || y < 480.0)
        {
            if (c_A <= 25)
                active = false;
            else
                c_A -= 25;
        }
        break;
    case 121:
        set_vec_speed(-10.0, 100.0);
        if ( x > 1880.0 )
            active = false;
        x += h_inerc;
        y += v_inerc;
        return;
    case 131:
        if ( weather_id_efx != WEATHER_RIVER_MIST || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 125 )
                c_A = 128;
            else
                c_A += 3;
        }
        par3 -= 0.5;
        setSkew(par3,0);

        return;
    case 132:
        if ( weather_id_efx != WEATHER_RIVER_MIST || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 || get_elaps_frames() > 180 )
        {
            if (c_A < 3)
                active = false;
            else
                c_A -= 3;
        }
        else
        {
            if (c_A > 252)
                c_A = 255;
            else
                c_A += 3;
        }
        x -= 0.8;
        if (process())
            active = false;
        break;
    case 141:
        if ( weather_id_efx != WEATHER_TYPHOON || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        if (process())
            active = false;

        y += sin_deg(-angZ - 90.0) * 60;
        x += cos_deg(-angZ - 90.0) * 60;

        if ( get_elaps_frames() <= 20 )
        {
            if ( c_A >= 240 )
                c_A = 255;
            else
                c_A += 15;
        }
        if ( get_elaps_frames() >= 180 || y < 480.0 )
        {
            if (c_A <= 25)
                active = false;
            else
                c_A -= 25;
        }
        break;
    case 151:
        if ( par2 != weather_id_efx
                || (weather_id_efx != WEATHER_AURORA && stage_number != 5)
                || (weather_id_efx != WEATHER_CLEAR && weather_id_efx == WEATHER_HISOUTEN) || (weather_id_efx == WEATHER_CLEAR && stage_number == 5) || v2 == 4)
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 252 )
                c_A = 255;
            else
                c_A += 3;
        }
        if (process())
            active = false;
        break;
    case 152:
    case 153:
    case 154:
    case 155:
        if ( (weather_id_efx != WEATHER_AURORA && stage_number != 5)
                || (weather_id_efx != WEATHER_CLEAR && weather_id_efx == WEATHER_HISOUTEN) ||
                (weather_id_efx == WEATHER_CLEAR && stage_number == 5) || v2 == 4)
            par1 = 1;
        if (par1 == 1)
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (active)
        {
            if (process())
                active = false;

            angZ += par3;
            scaleY += 0.01;

            if (get_elaps_frames() >= 180)
                active = false;
        }
        break;
    case 170:
        if (c_A < 3)
            active = false;
        else
            c_A -= 3;
        if (process())
            active = false;
        break;
    case 185:
        if ( weather_id_efx != WEATHER_CALM || v2 != 0 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 235)
                c_A = 255;
            else
                c_A += 20;
        }
        process();
        break;
    case 191:
        if ( weather_id_efx != WEATHER_DIAMOND_DUST || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 125 )
                c_A = 128;
            else
                c_A += 3;
        }
        par3 += 2.5;
        setSkew(par3,0);
        break;
    case 192:
        if ( weather_id_efx != WEATHER_DIAMOND_DUST || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 != 1 && get_elaps_frames() <= 180 )
        {
            if ( c_A > 189 )
                c_A = 192;
            else
                c_A += 3;
        }
        if (active)
        {
            x += 3.5;

            if (c_A < 3)
                active = false;
            else
                c_A -= 3;

            if (active && process())
                active = false;
        }
        break;
    case 193:
        angZ = -atan2_deg(v_inerc, h_inerc);

        if ( weather_id_efx != WEATHER_DIAMOND_DUST || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 || get_elaps_frames() > 50 )
        {
            if (c_A < 6)
                active = false;
            else
                c_A -= 6;
        }
        else
        {
            if (c_A > 250)
                c_A = 255;
            else
                c_A += 5;
        }
        x += dir * h_inerc;
        y += v_inerc;

        if ( process())
            active = false;
        break;
    case 194:
        angZ += 2.0;

        if ( weather_id_efx != WEATHER_DIAMOND_DUST || v2 == 1 || v2 == 2 )
            par1 = 1;

        if ( par1 == 1 || get_elaps_frames() > 50 )
        {
            if (c_A < 6)
                active = false;
            else
                c_A -= 6;
        }
        else
        {
            scaleY = scaleX *= 0.99;

            if ( c_A > 250 )
                c_A = 255;
            else
                c_A += 5;
        }

        x += h_inerc * dir;
        y += v_inerc;

        if ( process() )
            active = false;
        break;
    case 201:
        if ( weather_id_efx != WEATHER_SCORCHING_SUN || v2 != 0 )
            par1 = 1;
        if (par1 == 1)
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (active)
        {
            if (process())
                active = false;
            else
            {
                x -= 1.0;
                if (get_elaps_frames() >= 180)
                    active = false;
            }
        }
        break;
    case 202:
    case 204:
        if ( weather_id_efx != WEATHER_SCORCHING_SUN || v2 != 0 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;

        if (process())
            active = false;

        x += 1.0;
        if (get_elaps_frames() >= 180)
            active = false;
        break;

    case 203:
        if ( weather_id_efx != WEATHER_SCORCHING_SUN || v2 != 0 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        else
            c_A = sin_deg(get_elaps_frames()) * 255.0;
        if (process())
            active = false;

        x -= 1.0;
        if (get_elaps_frames() >= 180)
            active = false;
        break;


    case 205:
    case 206:
        angZ -= 0.2;
        if ( weather_id_efx != WEATHER_SCORCHING_SUN || v2 != 0 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if ( c_A < 20 )
                active = false;
            else
                c_A -= 20;
        }
        else
        {
            if ( c_A > 235 )
                c_A = 255;
            else
                c_A += 20;
        }
        break;
    case 211:
        if ( weather_id_efx != WEATHER_MONSOON || v2 == 1 || v2 == 2 )
            par1 = 1;
        if ( par1 == 1 )
        {
            if (c_A < 20)
                active = false;
            else
                c_A -= 20;
        }
        if (process())
            active = false;
        y += sin_deg(-100) * 6.0;
        x += cos_deg(-100) * 6.0;
        if ( get_elaps_frames() <= 60 )
        {
            if (c_A >= 250)
                c_A = 255;
            else
                c_A += 5;
        }
        if ( get_elaps_frames() >= 180 || y < 480.0 )
        {
            if (c_A <= 10)
                active = false;
            else
                c_A -= 10;
        }
        break;
    default:
        active = false;
        break;
    }
}

void c_weather_fx::set_seq_params()
{
    par1 = 0;
    par2 = 0;
    par3 = 0.0;
    switch ( get_seq() )
    {
    case 41:
        angZ = 80.0 - scene_rand_rngf(25);
        h_inerc = cos_deg(angZ) * 60;
        v_inerc = -sin_deg(angZ) * 60;
        break;
    case 42:
        angZ = 80.0 - scene_rand_rngf(25);
        h_inerc = cos_deg(angZ) * 50;
        v_inerc = -sin_deg(angZ) * 50;
        break;
    case 61:
        c_A = 0;
        par1 = 0;
        if ( y >= 480.0 )
            angZ = 180;
        break;
    case 62:
    case 63:
        c_A = 0;
        scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        scaleY = scene_rand_rngf(100) * 0.01 + 1.0;
        par1 = 0;
        break;
    case 71:
        c_A = 0;
        par1 = 0;
        h_inerc = scene_rand_rngf(40) * 0.1 - 2.0;
        v_inerc = -2.0 - scene_rand_rngf(150) * 0.01;
        scaleY = scaleX = scene_rand_rngf(75) * 0.01 + 0.25;
        break;
    case 72:
        c_A = 0;
        par1 = 0;
        h_inerc = scene_rand_rngf(40) * 0.1 - 2.0;
        v_inerc = -3.0 - scene_rand_rngf(200) * 0.01;
        scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 0.5;
        break;
    case 81:
        par1 = 0;
        c_A = 0;
        break;
    case 86:
        par1 = 0;
        break;
    case 91:
        par1 = 0;
        c_A = 0;
        angZ = 95.0 - scene_rand_rngf(10);
        scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        break;
    case 101:
        scaleX = 1.5;
        c_A = 0;
        par1 = 0;
        break;
    case 131:
    case 191:
        c_A = 0;
        par1 = 0;
        break;
    case 111:
        c_A = 0;
        angZ = scene_rand_rngf(15) + 30.0;
        break;
    case 121:
        scaleY = scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        angZ = -10.0;
        break;
    case 132:
    case 133:
        c_A = 0;
        scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        scaleY = scene_rand_rngf(100) * 0.01 + 1.0;
        par1 = 0;
        break;
    case 141:
        angZ = scene_rand_rngf(15) + 30.0;
        break;
    case 151:
        c_A = 0;
        scaleY = 2.0;
        par2 = weather_id_efx;
        break;
    case 152:
    case 153:
    case 154:
    case 155:
        c_A = 0;
        angZ = scene_rand_rngf(50) - 25.0;
        par3 = scene_rand_rngf(10) * 0.01;
        break;
    case 170:
        scaleX = 3.0;
        scaleY = 1.5;
        break;
    case 192:
        c_A = 0;
        scaleX = scene_rand_rngf(100) * 0.01 + 1.0;
        scaleY = scene_rand_rngf(100) * 0.01 + 1.0;
        break;
    case 193:
    case 194:
        c_A = 0;
        par1 = 0;
        h_inerc = -12.5 - scene_rand_rngf(50) * 0.1;
        v_inerc = scene_rand_rngf(100) * 0.1 - 5.0;
        scaleY = scaleX = scene_rand_rngf(10) * 0.1 + 0.5;
        break;
    case 205:
    case 206:
        c_A = 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 11:
    case 82:
    case 83:
    case 84:
    case 85:
    case 201:
    case 202:
    case 203:
    case 204:
    case 211:
        c_A = 0;
        angZ = 10.0;
        break;
    default:
        break;
    }
}





// FX-holder

c_weather_sp::c_weather_sp()
{
    load_dat("effect.pat","data/weather/effect");
}

void c_weather_sp::addeffect(int32_t idx, float x, float y, int8_t dir, int8_t order)
{
    gfx_seq *sq = get_seq(idx);
    if (sq)
    {
        c_weather_fx *ff = new c_weather_fx(idx, sq, x, y, dir, order);
        fx.push_back(ff);
    }
}

void c_weather_sp::draw(int8_t order, int8_t plane)
{
    for(uint32_t i=0; i<fx.size(); i++)
        if (fx[i]->order == order)
            fx[i]->draw(plane);
}

// //FX-holder



c_weather_bg::c_weather_bg()
{
    cur_weather = -1;
    char buf[CHRBUF];
    for (int8_t i=0; i<20; i++)
    {
        sprintf(buf,"data/weather/%02d.cv2",i);
        filehandle *f = arc_get_file(buf);
        if (f)
        {
            bg[i] = gr_load_cv2(f,NULL);
            delete f;
        }
    }
}

c_weather_bg::~c_weather_bg()
{
    for (int8_t i=0; i<20; i++)
        delete bg[i];
}

void c_weather_bg::draw(int8_t weather, int8_t plane)
{
    if (weather != cur_weather)
    {
        gr_set_spr_tex(&sprite, bg[weather]);
        cur_weather = weather;
    }
    //gr_setxy_sprite(&sprite,-BKG_WIDTH / 2,0);
    //gr_setorigin_sprite(&sprite,,0);
    gr_setscale_sprite(&sprite,3.0,3.0);
    gr_setcolor_sprite(&sprite,255,255,255,255);

    gr_draw_sprite(&sprite,gr_alpha,plane,NULL);
}

void c_weather_bg::draw(int8_t weather, int32_t alpha, int8_t plane)
{
    if (weather != cur_weather)
    {
        gr_set_spr_tex(&sprite, bg[weather]);
        cur_weather = weather;
    }
    //gr_setxy_sprite(&sprite,-BKG_WIDTH / 2,0);
    //gr_setorigin_sprite(&sprite,,0);
    gr_setscale_sprite(&sprite,3.0,3.0);
    gr_setcolor_sprite(&sprite,255,255,255,alpha);

    gr_draw_sprite(&sprite,gr_alpha,plane,NULL);
}


WEATHER_ID weather = WEATHER_CLEAR;
int32_t weather_time = 0;
WEATHER_ID weather_index_for_name = WEATHER_CLEAR;
WEATHER_ID weather_setted = WEATHER_CLEAR;

WEATHER_ID weather_get()
{
    return weather;
}

void weather_set(WEATHER_ID id)
{
    weather = id;
}

int32_t weather_time_mul(float m)
{
    weather_time = (int32_t)((float)weather_time * m);
    return weather_time;
}

int32_t weather_time_add(int32_t vl)
{
    weather_time += vl;
    return weather_time;
}

int32_t weather_time_sub(int32_t vl)
{
    weather_time -= vl;
    return weather_time;
}

int32_t weather_time_set(int32_t vl)
{
    weather_time = vl;
    return weather_time;
}

int32_t weather_time_get()
{
    return weather_time;
}

WEATHER_ID weather_index_for_name_get()
{
    return weather_index_for_name;
}

void weather_forecast_set(WEATHER_ID id)
{
  if ( id != WEATHER_CLEAR )
  {
    weather_index_for_name = id;
    battle_ui_effect(get_ieid_by_weather(id) + 4, 320, 32, 1, 1);
  }
}

void add_sky_bkg(t_weather_manager *wth, int32_t stage_id)
{
    mapsky::iterator it = wth->sky_mapping.find(stage_id);

    if (it != wth->sky_mapping.end())
    {
        int32_t sky_id = it->second[wth->current_sky_weather];
        if (sky_id >= 0)
        {
            s_asky tmp;
            tmp.alpha = 255;
            tmp.sky_id = sky_id;

            wth->sky_deque.push_front(tmp);
        }
    }
}


void weather_set_new_sky_if_changed(t_weather_manager *wth, WEATHER_ID id)
{
  if ( wth->current_sky_weather != id )
  {
    wth->current_sky_weather = id;
    add_sky_bkg(wth, scene_get_scene()->get_stage_id());
  }
}


WEATHER_ID weather_setted_get()
{
    return weather_setted;
}

void weather_setted_change(WEATHER_ID id)
{
    weather_setted = id;
    battle_ui_effect(get_ieid_by_weather(id), 320, 42, 1, 1);
    weather_set_new_sky_if_changed(weather_manager, id);
}

void weather_change(WEATHER_ID id, bool setted)
{
    if (setted)
        weather_setted_change(id);

    if ( id != WEATHER_CLEAR )
    {
        scene_play_sfx(53);
        battle_ui_effect(get_ieid_by_weather(id) + 2, 320, 42, 1, 1);
    }
    weather_index_for_name = id;

    if ( id == WEATHER_AURORA )
        weather = (WEATHER_ID)scene_rand_rng(19);
    else
        weather = id;
}


void weather_init_manager()
{
    if (!weather_manager)
    {
        weather_manager = new t_weather_manager;

        filehandle *f = arc_get_file("data/csv/background/sky.cv1");
        if (f)
        {
            char * txt = txt_load_cv1(f);

            delete f;

            char buf[1024];
            const char *text = txt;

            while (text)
            {
                text = txt_mgets(text, buf, 1024);
                int32_t getsz = strlen(buf);

                if (getsz > 0)
                {
                    bool good_line = true;
                    int32_t period = 0;
                    for (int32_t i=0; i< getsz; i++)
                        if (buf[i] >= ':')
                        {
                            good_line = false;
                            break;
                        }
                        else if (buf[i] == ',')
                            period++;

                    if (good_line && period == 22)
                    {
                        char *nxt = strtok(buf,",");
                        int32_t id = atoi(nxt);

                        sky_of_bkg tmp;
                        tmp.resize(WEATHER_ID_COUNT);

                        for (int32_t i=0; i< WEATHER_ID_COUNT; i++)
                        {
                            nxt = strtok(NULL,",");
                            tmp[i] = atoi(nxt);
                        }

                        weather_manager->sky_mapping[id] = tmp;
                    }
                }
            }
            free(txt);
        }

        if (!weather_manager->sky_deque.empty())
            weather_manager->sky_deque.clear();
    }

    weather_id_efx = WEATHER_CLEAR;
    weather_efx_time = 0;

    weather_manager->field_DC = 1.0;
    weather_manager->field_E0 = 0.0;
    weather_manager->field_E4 = 0.0;
    weather_manager->field_E8 = 0.0;
    weather_manager->current_sky_weather = WEATHER_UNK;
}

t_weather_manager *weather_manager_get()
{
    return weather_manager;
}


void weather_spawn_effects_by_id(WEATHER_ID wid)
{
    weather_efx_time++;
    if ( weather_id_efx != wid )
    {
        weather_id_efx = wid;
        weather_efx_time = 0;
    }

    int32_t v2 = 0;

    int32_t stage_number = scene_get_scene()->get_stage_id();

    switch ( stage_number )
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 10:
    case 11:
    case 12:
    case 13:
    case 15:
    case 18:
    case 30:
    case 31:
        v2 = 0;
        break;
    case 5:
        v2 = 2;
        break;
    case 17:
        v2 = 3;
        break;
    case 32:
        v2 = 4;
        break;
    case 4:
    case 6:
    case 14:
    case 16:
    case 33:
    case 34:
    case 35:
        v2 = 1;
        break;
    default:
        break;
    }

    switch ( wid )
    {
    case WEATHER_SUNNY:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

        }
        else
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
            if ( v2 == 0 )
            {
                if ( weather_efx_time == 0 )
                    weather_manager->wfx_holder.addeffect(5, 1280.0, 900.0, 1, 1);

                if ( weather_efx_time % 180 == 0 )
                    weather_manager->wfx_holder.addeffect(1, scene_rand_rngf(1280), 900.0, 1, 1);

                if ( weather_efx_time % 180 == 45 )
                    weather_manager->wfx_holder.addeffect(2, scene_rand_rngf(1280), 900.0, 1, 1);

                if ( weather_efx_time % 180 == 90 )
                    weather_manager->wfx_holder.addeffect(3, scene_rand_rngf(1280), 900.0, 1, 1);

                if ( weather_efx_time % 180 == 135 )
                    weather_manager->wfx_holder.addeffect(4, scene_rand_rngf(1280), 900.0, 1, 1);
            }
        }
        break;

    case WEATHER_DRIZZLE:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

        }
        else
        {
            if ( weather_efx_time == 0 )
                scene_play_sfx(100);

            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time % 90 == 0 )
                weather_manager->wfx_holder.addeffect(11, scene_rand_rngf(480), 1560.0, 1, 1);
            }
        break;

    case WEATHER_CLOUDY:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else
        {
            if ( v2 == 0 || v2 == 3 )
            {
                weather_manager->field_E0 = -0.03;
                weather_manager->field_E4 = -0.03;
                weather_manager->field_E8 = -0.03;
            }
            else
            {
                weather_manager->field_E0 = 0.0;
                weather_manager->field_E4 = 0.0;
                weather_manager->field_E8 = 0.0;
            }
        }
        break;

    case WEATHER_BLUE_SKY:
        if ( v2 != 2 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        else
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0)
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        break;

    case WEATHER_HAIL:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        else
        {
            weather_manager->field_E0 = -0.1;
            weather_manager->field_E4 = -0.1;
            weather_manager->field_E8 = -0.1;

            if ( weather_efx_time == 0 )
                scene_play_sfx(105);

            if ( (weather_efx_time & 3) == 0 )
                weather_manager->wfx_holder.addeffect(41, scene_rand_rngf(1280) - 480.0, 1560.0 - scene_rand_rngf(280), 1, 1);

            if ( (weather_efx_time & 3) == 2 )
                weather_manager->wfx_holder.addeffect(42, scene_rand_rngf(1280) - 480.0, 1560.0 - scene_rand_rngf(280), 1, -1);
        }
        break;

    case WEATHER_SPRING_HAZE:
        if ( v2 != 2 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        else
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        break;

    case WEATHER_HEAVY_FOG:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && stage_number != 16 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0;
            weather_manager->field_E4 = 0;
            weather_manager->field_E8 = 0;
        }
        else
        {
            weather_manager->field_E0 = 0.05;
            weather_manager->field_E4 = 0.05;
            weather_manager->field_E8 = 0.05;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(61, 640.0, -150.0, 1, 1);

            if ( weather_efx_time % 30 == 0 )
                weather_manager->wfx_holder.addeffect(62, scene_rand_rngf(1280), scene_rand_rngf(480), 1, 1);

            if ( weather_efx_time % 30 == 15 )
                weather_manager->wfx_holder.addeffect(63, scene_rand_rngf(1280), scene_rand_rngf(480), 1, 1);
        }
        break;

    case WEATHER_SNOW:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time  == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0;
            weather_manager->field_E4 = 0;
            weather_manager->field_E8 = 0;
        }
        else
        {
            weather_manager->field_E0 = -0.1;
            weather_manager->field_E4 = -0.1;
            weather_manager->field_E8 = -0.1;

            if ( weather_efx_time == 0)
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 6 == 0 )
            {
                if ( scene_rand_rngf(100) > 50 )
                    weather_manager->wfx_holder.addeffect(71, scene_rand_rngf(1280), scene_rand_rngf(640) + 480, -1, 1);
                else
                    weather_manager->wfx_holder.addeffect(71, scene_rand_rngf(1280), scene_rand_rngf(640) + 480, 1, 1);
            }

            if ( weather_efx_time % 90 == 0 )
                weather_manager->wfx_holder.addeffect(72, scene_rand_rngf(1280), scene_rand_rngf(640) + 480, 1, 1);
        }
        break;

    case WEATHER_SUNSHOWER:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 == 3 || v2 == 4 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
            if ( weather_efx_time == 0 )
            {
                scene_play_sfx(101);
                weather_manager->wfx_holder.addeffect(81, 0.0, 860.0, 1, 1);
            }
        }
        else if ( v2 == 0 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
            {
                scene_play_sfx(101);
                weather_manager->wfx_holder.addeffect(81, 0.0, 860.0, 1, 1);
                weather_manager->wfx_holder.addeffect(86, 0.0, 0.0, 1, -1);
            }

            if ( weather_efx_time % 240 == 0 )
                weather_manager->wfx_holder.addeffect(82, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 240 == 60 )
                weather_manager->wfx_holder.addeffect(83, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 240 == 120 )
                weather_manager->wfx_holder.addeffect(84, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 240 == 180 )
                weather_manager->wfx_holder.addeffect(85, scene_rand_rngf(1280), 900.0, 1, 1);
        }
        break;
    case WEATHER_SPRINKLE:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640)+320, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640)+320, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640)+320, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640)+320, 1980.0, -1, 1);
        }
        else if ( v2 == 0 || v2 == 3 || v2 == 4 )
        {
            if ( weather_efx_time == 0 )
                scene_play_sfx(100);

            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time % 3 == 0 )
            {
                if ( scene_rand_rngf(100) > 50 )
                    weather_manager->wfx_holder.addeffect(91, scene_rand_rngf(1280), scene_rand_rngf(320)+960, -1, 1);
                else
                    weather_manager->wfx_holder.addeffect(91, scene_rand_rngf(1280), scene_rand_rngf(320)+960, 1, 1);
            }
        }
        break;
    case WEATHER_TEMPEST:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0;
            weather_manager->field_E4 = 0;
            weather_manager->field_E8 = 0;
        }
        else
        {
            if ( weather_efx_time == 0 )
                scene_play_sfx(104);

            weather_manager->field_E0 = -0.1;
            weather_manager->field_E4 = -0.1;
            weather_manager->field_E8 = -0.1;

            if ( weather_efx_time % 20 == 0 )
                weather_manager->wfx_holder.addeffect(111, scene_rand_rngf(640) + 556.0, 2400.0, 1, 1);
        }
        break;
    case WEATHER_MOUNTAIN_VAPOR:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 > 0 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        else
        {
            if ( weather_efx_time == 0)
                scene_play_sfx(104);

            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time % 15 == 0 )
                weather_manager->wfx_holder.addeffect(121, -400.0 - scene_rand_rngf(128), scene_rand_rngf(640) - 180.0, 1, 1);
        }
        break;
    case WEATHER_RIVER_MIST:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0;
            weather_manager->field_E4 = 0;
            weather_manager->field_E8 = 0;
        }
        else
        {
            weather_manager->field_E0 = -0.05;
            weather_manager->field_E4 = -0.05;
            weather_manager->field_E8 = -0.05;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(131, 0.0, -240.0, 1, 1);

            if ( weather_efx_time % 90 == 0 )
            {
                if ( scene_rand_rng(100) > 50 )
                    weather_manager->wfx_holder.addeffect(132, scene_rand_rngf(1600), scene_rand_rngf(40), 1, -1);
                else
                    weather_manager->wfx_holder.addeffect(132, scene_rand_rngf(1600), -scene_rand_rngf(40), 1, 1);
            }
        }
        break;
    case WEATHER_TYPHOON:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0)
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0;
            weather_manager->field_E4 = 0;
            weather_manager->field_E8 = 0;
        }
        else
        {
            if ( weather_efx_time == 0 )
                scene_play_sfx(104);

            weather_manager->field_E0 = -0.2;
            weather_manager->field_E4 = -0.2;
            weather_manager->field_E8 = -0.2;

            if ( weather_efx_time % 20 == 0 )
                weather_manager->wfx_holder.addeffect(141, scene_rand_rngf(640) + 556.0, 2400.0, 1, 1);
        }
        break;

    case WEATHER_CALM:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0)
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 == 0)
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0)
                weather_manager->wfx_holder.addeffect(185, 1280.0, 900.0, 1, 1);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(1, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(2, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(3, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(4, scene_rand_rngf(1280), 900.0, 1, 1);
        }
        else
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        break;

    case WEATHER_DIAMOND_DUST:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0;
            weather_manager->field_E4 = 0;
            weather_manager->field_E8 = 0;
        }
        else
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(191, 0.0, -240.0, 1, 1);

            if ( (weather_efx_time & 3) == 0 )
            {
                if (scene_rand_rng(100) > 50)
                    weather_manager->wfx_holder.addeffect(194, scene_rand_rngf(1600),scene_rand_rngf(150),1,1);
                else
                    weather_manager->wfx_holder.addeffect(193, scene_rand_rngf(1600),scene_rand_rngf(150),1,1);
            }
            if ( weather_efx_time % 90 == 0 )
            {
                if (scene_rand_rng(100) > 50)
                    weather_manager->wfx_holder.addeffect(192, scene_rand_rngf(1600),scene_rand_rngf(40),1,-1);
                else
                    weather_manager->wfx_holder.addeffect(192, scene_rand_rngf(1600),-scene_rand_rngf(40),1,1);
            }
        }
        break;

    case WEATHER_DUST_STORM:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 != 0 && v2 != 3 && v2 != 4 )
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        else
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = -0.15;

            if ( weather_efx_time == 0)
            {
                scene_play_sfx(104);
                weather_manager->wfx_holder.addeffect(101, 0.0, -120.0, 1, 1);
            }
        }
        break;

    case WEATHER_SCORCHING_SUN:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 == 0 )
        {
            weather_manager->field_E0 = 0.05;
            weather_manager->field_E4 = 0.05;
            weather_manager->field_E8 = 0.05;

            if ( weather_efx_time == 0 )
            {
                weather_manager->wfx_holder.addeffect(206, 640.0, 1000.0, 1, 1);
                weather_manager->wfx_holder.addeffect(205, 640.0, 1000.0, 1, 1);
            }
            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(201, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(202, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(203, scene_rand_rngf(1280), 900.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(204, scene_rand_rngf(1280), 900.0, 1, 1);
        }
        else
        {
            weather_manager->field_E0 = 0.05;
            weather_manager->field_E4 = 0.05;
            weather_manager->field_E8 = 0.05;
        }
        break;

    case WEATHER_MONSOON:
        if ( v2 == 2 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        else if ( v2 == 0 || v2 == 3 || v2 == 4 )
        {
            if ( weather_efx_time == 0 )
                scene_play_sfx(100);

            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time % 90 == 0 )
                weather_manager->wfx_holder.addeffect(211, scene_rand_rngf(480), 1560.0, 1, 1);
        }
        break;

    case WEATHER_AURORA:
        if ( v2 == 4 )
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;
        }
        else if (v2 == 1)
        {
            weather_manager->field_E0 = 0.0;
            weather_manager->field_E4 = 0.0;
            weather_manager->field_E8 = 0.0;
        }
        else
        {
            weather_manager->field_E0 = -0.5;
            weather_manager->field_E4 = -0.5;
            weather_manager->field_E8 = 0.0;

            if ( weather_efx_time == 0 )
                weather_manager->wfx_holder.addeffect(151, 0.0, 900.0, 1, -2);

            if ( weather_efx_time % 180 == 0 )
                weather_manager->wfx_holder.addeffect(152, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 45 )
                weather_manager->wfx_holder.addeffect(153, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);

            if ( weather_efx_time % 180 == 90 )
                weather_manager->wfx_holder.addeffect(154, scene_rand_rngf(640) + 320.0, 1980.0, 1, 1);

            if ( weather_efx_time % 180 == 135 )
                weather_manager->wfx_holder.addeffect(155, scene_rand_rngf(640) + 320.0, 1980.0, -1, 1);
        }
        break;

    case WEATHER_HISOUTEN:
        weather_manager->field_E0 = 0.0;
        weather_manager->field_E4 = 0.0;
        weather_manager->field_E8 = 0.0;
        break;

    case WEATHER_CLEAR:
        weather_manager->field_E0 = 0.0;
        weather_manager->field_E4 = 0.0;
        weather_manager->field_E8 = 0.0;
        break;
    default:
        break;
    }
}

