#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "../file_read.h"
#include "../archive.h"
#include "utsuho.h"

const char *utsuho_ps = "\
uniform sampler2D base;\
uniform sampler2D tex;\
void main()\
{\
    vec4 color = texture2D(base, gl_TexCoord[0].xy);\
    if (color.xyz == vec3(1,0,1))\
        gl_FragColor = texture2D(tex, gl_TexCoord[1].xy) * gl_Color;\
    else\
        gl_FragColor = texture2D(base, gl_TexCoord[0].xy) * gl_Color;\
}";

const char *utsuho_vs = "\
uniform vec2 pos;\
void main()\
{\
    gl_Position = ftransform();\
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\
    gl_TexCoord[1].xy = gl_Position.xy * vec2(320.0/256.0,240.0/256.0) + pos.xy;\
    gl_FrontColor = gl_Color;\
}";

char_utsuho::char_utsuho(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    char_id = CHAR_ID_UTSUHO;
    pgp->load_dat("utsuho",pal);
    char_loadsfx("utsuho");
    filehandle *f = arc_get_file("data/character/utsuho/backA000.cv2");

    if (f)
    {
        backtex = gr_load_cv2(f,NULL);
        gr_set_repeate(backtex, true);
        delete f;

        shader = new gr_shader;
        gr_load_shader_from_mem(shader, utsuho_vs, utsuho_ps);
        gr_shader_set_texture(shader,"tex",backtex);
    }
    shd_p = 0;

    load_face("utsuho");
}

void char_utsuho::draw(gr_shader *_shader)
{
    if (!_shader)
    {
    shd_p+=0.5;
    if (shd_p >= 512)
        shd_p = 0;
    gr_shader_set_texture(shader,"base",NULL);
    gr_shader_set(shader,"pos",(x-shd_p)/512.0,(y-shd_p)/512.0);

    char_c::draw(shader);
    }
    else
    char_c::draw(_shader);

}

void char_utsuho::draw_shadow(shd_trans *trans, gr_shader *_shader)
{
    if (!_shader)
    {
    gr_shader_set_texture(shader,"base",NULL);
    gr_shader_set(shader,"pos",(x-shd_p)/512.0,(y-shd_p)/512.0);

    char_c::draw_shadow(trans,shader);
    }
    else
    char_c::draw(_shader);
}

void char_utsuho::func10()
{
    x_delta = 0;
    y_delta = 106;


    if ( hit_stop != 0 /*|| enemy->time_stop != 0 */)
        return;

    int32_t sq = get_seq();

    switch(sq)
    {
    case 0:
        sub10func();
        if (h_inerc == 0)
            field_49A = 0;
        stopping(0.5);
        process();
        break;
    case 1:
        sub10func();
        stopping(0.5);
        if (process() && get_frame() == 0)
            set_seq(2);
        break;
    case 2:
        sub10func();
        stopping(0.5);
        process();
        break;
    case 3:
        sub10func();
        stopping(0.5);
        if (process() && get_frame() == 0)
            set_seq(0);
        break;
    case 4:
        sub10func();
        char_h_move( 3.0);
        process();
        break;
    case 5:
        sub10func();
        char_h_move( -3.0);
        process();
        break;
    case 6:
        if (get_subseq() == 0)
        {
            sub10func();
            if (field_49A == 0)
                reset_forces();
        }
        if (get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down())
            {
                set_seq(10);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }
        process();

        if (get_subseq()       == 1 &&
                get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            v_inerc = 13.0;
            v_force = 0.3;
        }
        break;
    case 7:
        if (get_subseq() == 0)
        {
            sub10func();
            if (field_49A == 0)
                reset_forces();
        }

        if (get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down())
            {
                set_seq(10);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }

        process();

        if (get_subseq()       == 1 &&
                get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            v_inerc = 13.0;
            v_force = 0.3;
            char_h_move( 3.0);
            field_49A = 0;
        }
        break;
    case 8:
        if (get_subseq() == 0)
        {
            sub10func();
            if (field_49A == 0)
                reset_forces();
        }

        if (get_subseq()>0)
        {
            v_inerc -=v_force;

            if (char_on_ground_down())
            {
                set_seq(10);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }

        process();

        if (get_subseq()       == 1 &&
                get_frame_time()   == 0 &&
                get_frame()        == 0 &&
                get_elaps_frames() == 0)
        {
            v_inerc = 13.0;
            v_force = 0.3;
            char_h_move( -3.0);
        }
        break;
    case 9:
        if (v_force == 0)
            v_force = 0.6;

        v_inerc -=v_force;

        if (char_on_ground_down())
        {
            set_seq(10);
            y = getlvl_height();
            reset_forces();
            break;
        }

        process();
        break;
    case 10:
        sub10func();
        reset_forces();
        if (process())
        {
            if (dY() > 0)
                set_seq(2);
            else
                set_seq(0);
        }
        break;
    case 199:
        sub10func();
        if ( process() )
        {

            /*if ( LOBYTE(v2->controlling_type) == 2 )
            {
                set_seq(700);

                field_51C = 3;
                field_520 = 3;
            }
            else*/
            {
                set_seq(0);
                if ( dY() > 0)
                    set_seq(1);
            }
        }
        else if ( get_frame_time() == 0  && get_frame() == 5)
        {
            if (enemy->x < x)
                dir = -1;
            else
                dir = 1;
        }
        break;

    case 214:
        if ( process())
            set_seq(9);
        else
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
                scene_play_sfx(31);

            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6)
            {
                set_seq(9);
                break;
            }
            else
            {
                if ( dY() < 0)
                {
                    field_7D2 = 90 - dX(dir) * 45;
                }
                else if (dY() == 0)
                {
                    if (dX(dir) > 0 )
                        field_7D2 = 0;
                    else if (dX(dir) < 0 )
                        field_7D2 = 180;
                }
                else if (dY() > 0)
                {
                    field_7D2 = -90 - dX(dir) * 45;
                }

                if ( get_subseq() == 5 || get_subseq() == 6 )
                    v_inerc -= v_force;
                if ( get_subseq() > 0 && get_subseq() < 5 )
                {
                    field_7D6 ++;
                    field_7D4 = field_7D2 - dash_angle;
                    if ( field_7D4 >180 )
                        field_7D4 -= 360;
                    else if (field_7D4 < -180)
                        field_7D4 += 360;

                    if ( field_7D4 > 0 )
                    {
                        if ( weather_id != WEATHER_SUNNY )
                            dash_angle += 0.5;
                        else
                            dash_angle += 1.5;
                    }
                    else if ( field_7D4 < 0 )
                    {
                        if ( weather_id != WEATHER_SUNNY )
                            dash_angle -= 0.5;
                        else
                            dash_angle -= 1.5;
                    }

                    h_inerc = cos_deg(dash_angle) * field_7DC;
                    v_inerc = sin_deg(dash_angle) * field_7DC;

                    if ( y > 680.0 )
                        if ( v_inerc > 0.0 )
                            v_inerc = 0.0;

                    field_7DC += 0.3;
                    if ( field_7DC > 12.0 )
                        field_7DC = 12.0;

                    spell_energy_spend( weather_id != WEATHER_SUNNY ? 10 : 5, 1);
                    angZ = -dash_angle;


                    if ( h_inerc < 0.0 )
                        // angZ = 180 -angZ;
                        angZ = 180.0 + dash_angle;

                    if ( h_inerc < 0.0 )
                        if ( get_subseq() == 1 )
                            set_subseq(3);

                    if ( h_inerc >= 0 )
                        if ( get_subseq() == 3 )
                            set_subseq(1);

                    if ( h_inerc < 0.0 )
                        if ( get_subseq() == 2 )
                            set_subseq(4);

                    if ( h_inerc >= 0)
                        if ( get_subseq() == 4 )
                            set_subseq(2);

                    if ( get_elaps_frames() % 5 == 1 )
                    {
                        float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
                        float xx = cos_deg(dash_angle) * 100.0 * dir + x;
                        scene_add_effect(this, 125, xx, yy, dir, 1);
                    }
                    if ( (keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
                    {
                        reset_ofs();
                        angZ = 0;

                        if ( get_subseq() == 1 || get_subseq() == 2 )
                        {
                            if ( dir == 1 )
                            {
                                if ( enemy->x >= x )
                                    set_subseq(5);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(6);
                                }
                            }
                            else
                            {
                                if ( enemy->x <= x )
                                    set_subseq(5);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(6);
                                }
                            }
                        }
                        else if ( get_subseq() == 3 || get_subseq() == 4 )
                        {
                            if ( dir == 1 )
                            {
                                if ( enemy->x >= x )
                                    set_subseq(6);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(5);
                                }
                            }
                            else
                            {
                                if ( enemy->x <= x )
                                    set_subseq(6);
                                else
                                {
                                    dir = -dir;
                                    h_inerc = -h_inerc;
                                    set_subseq(5);
                                }
                            }
                        }
                        break;
                    }
                }
            }
            if ( char_on_ground_down() )
            {
                y = getlvl_height();
                v_force = 0.0;
                v_inerc = 0.0;
                if ( get_subseq() < 5 )
                {
                    reset_ofs();
                    angZ = 0;
                    set_seq(215);
                }
                else
                {
                    set_seq(10);
                    reset_forces();
                }
            }
        }
        break;

    default:
        char_c::func10();
    }
}

void char_utsuho::set_seq_params()
{
    uint32_t sq = get_seq();
    switch(sq)
    {
    case 4:
        h_inerc = 6.0;
        break;
    case 5:
        h_inerc = -5.0;
        break;
    case 214:
        reset_ofs();
        h_inerc = 0.0;
        v_inerc = 0.0;
        v_force = 0.60000002;
        x_off = 0.0;
        y_off = 95.0;
        field_7DC = 12;
        field_7D6 = 0;
        field_7EC = 0;
        break;
    default:
        char_c::set_seq_params();
        break;
    }
}


void char_utsuho::func20()
{


    /*v1 = a1;
      v2 = a1->current_frame_params;
      v3 = v2->fflags;
      v147 = a1->current_seq_frames_vector->cprior;
      v4 = v2->fflags & FF_CANCELLEABLE;
      v148 = v2->fflags & FF_CANCELLEABLE;
      v5 = v3 & FF_UNK200000;*/

    uint16_t cprior = get_cprior();
    uint32_t fflags = get_pframe()->fflags;

    bool cc = (fflags & FF_CANCELLEABLE) != 0;
    bool cu = (fflags & FF_HJC) != 0;
    //int32_t sq = get_seq();

    if ( !check_AB_pressed() )
    {
        if ( cc || cu )
        {
            /*
             if ( pres_comb >= 700 && pres_comb < 800 )
             {
               //v1->class->func2_set_seq(v1, LOWORD(v1->pressed_combination));
               return;
             }
             else*/
            if ( char_on_ground_flag() )
            {
                if ( (cu && cprior >= 10 && hi_jump_after_move())
                        || border_escape_ground()
                        || hi_jump(cprior, cu)
                        || fw_bk_dash_ground(cprior, cu) )
                    return;
            }
            else
            {
                int8_t mx = (weather_id == WEATHER_TEMPEST) + 2;
                if ( border_escape_air()
                        || fwd_dash_air(cprior, cu, mx, 2)
                        || bkg_dash_air(cprior, cu, mx, 2)
                        || flying_air(cprior, cu, mx) )
                    return;
            }
        }
        if ( field_84C == 0 && cc )
        {
        }
    }
}
