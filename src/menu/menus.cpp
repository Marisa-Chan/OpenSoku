#include "../global_types.h"
#include "../scene.h"
#include "../input.h"
#include "menus.h"
#include "title.h"


screen::~screen()
{

}

void screen::onExit()
{

}
void screen::onStart()
{

}

ingame_menu::~ingame_menu()
{

}

fader::fader()
{
    init();
}

void fader::init()
{
    a = 0;
    r = 0;
    g = 0;
    b = 0;
}

void fader::fade_in()
{
    if (a == 120)
    {
        a = 0;
        r = 0;
        g = 0;
        b = 0;
    }
    if (a)
        a++;
}

int8_t fader::fade_out()
{
    if ( a == 60 )
        return 1;
    else
    {
        if ( a > 60 )
            a = 120 - a;
        a++;
    }
    return 0;
}

void fader::draw()
{
    int32_t real_alpha;

    if ( a <= 60 )
        real_alpha = 255 * a;
    else
        real_alpha = 255 * (120 - a);

    gr_draw_box(0,0,640,480, r, g ,b, real_alpha / 60, PLANE_GUI);
}



menu_fader::menu_fader()
{
    menu_stack.clear();
    todelete = false;
    saved_menus = 0;
    context_alpha = 0;
    fade_alpha = 0.0;
    fade_alpha_delta = 0.0;

    main_gear_angle = 0.0;

    doors[0] = gr_load_cv2("data/menu/door_l.cv2",NULL);
    doors[1] = gr_load_cv2("data/menu/door_r.cv2",NULL);

    cursor_tex[0] = gr_load_cv2("data/menu/cursor.cv2",NULL);
    cursor_tex[1] = gr_load_cv2("data/menu/cursor3.cv2",NULL);
    cursor_tex[2] = gr_load_cv2("data/menu/cursor4.cv2",NULL);

    cursor[0] = gr_create_sprite();
    cursor[1] = gr_create_sprite();
    cursor[2] = gr_create_sprite();

    gr_set_spr_tex(cursor[0],cursor_tex[0]);
    gr_set_spr_tex(cursor[1],cursor_tex[1]);
    gr_set_spr_tex(cursor[2],cursor_tex[2]);

    gr_setorigin_sprite(cursor[1],10,10);
    gr_setorigin_sprite(cursor[2],10,10);

    menuProfile.load_dat("data/menu","menuProfile.dat");
    uiProfileNames[0] = menuProfile.get_gui(100);
    uiProfileNames[1] = menuProfile.get_gui(101);
    uiProfileNames[0]->renderable = true;
    uiProfileNames[1]->renderable = true;

    gearUpper.load_dat("data/menu/gear","gearUpper.dat");
    gearLower.load_dat("data/menu/gear","gearLower.dat");

    uiGearRail[0] = gearLower.get_gui(300);
    uiGearRail[1] = gearLower.get_gui(301);
    uiGearRail[0]->renderable = true;
    uiGearRail[1]->renderable = true;

    gr_set_smoth(uiGearRail[0]->getTex()->tex, true);
    gr_set_smoth(uiGearRail[1]->getTex()->tex, true);

    for(int32_t i=0; i<39; i++)
    {
        if (i < 21)
            uiGears[i] = gearUpper.get_gui(100 + i);
        else
            uiGears[i] = gearLower.get_gui(179 + i);
        uiGears[i]->renderable = 1;

        float orig = uiGears[i]->getTexW() / 2.0;
        uiGears[i]->setDXDY(orig,orig);
        uiGears[i]->setOrigin(orig,orig);

        int32_t w = uiGears[i]->getTexW();

        gr_set_smoth(uiGears[i]->getTex()->tex, true);

        if (w > 350)
            gearAngles[i] = 48.0;
        else if (w > 300)
            gearAngles[i] = 48.0;
        else if (w > 150)
            gearAngles[i] = 24.0;
        else if (w > 100)
            gearAngles[i] = 48.0;
        else if (w > 70 || w <= 50)
            gearAngles[i] = 12.0;
        else
            gearAngles[i] = 24.0;
    }
}

menu_fader::~menu_fader()
{
    for(int8_t i=0; i<2; i++)
        gr_delete_tex(doors[i]);

    for(int8_t i=0; i<3; i++)
    {
        gr_delete_tex(cursor_tex[i]);
        gr_delete_sprite(cursor[i]);
    }

    for(uint32_t i=0; i<menu_stack.size(); i++)
        delete menu_stack[i];

}


void menu_fader::gears_update()
{
    float angles[40];

    angles[21] = main_gear_angle;
    angles[20] = -main_gear_angle * gearAngles[20] / gearAngles[19];
    angles[0] = -angles[20];
    angles[8] = gearAngles[19] * angles[0] / gearAngles[7];
    angles[9] = gearAngles[7] * -angles[8] / gearAngles[8];
    angles[10] = gearAngles[8] * -angles[9] / gearAngles[9];
    angles[11] = gearAngles[9] * -angles[10] / gearAngles[10];
    angles[19] = gearAngles[10] * -angles[11] / gearAngles[18];
    angles[12] = angles[19];
    angles[15] = -angles[19] * gearAngles[11] / gearAngles[14];
    angles[7] = gearAngles[14] * -angles[15] / gearAngles[6];
    angles[18] = gearAngles[6] * -angles[7] / gearAngles[17];
    angles[16] = angles[18];
    angles[13] = -angles[18] * gearAngles[15] / gearAngles[12];
    angles[0] = main_gear_angle * 0.25;
    angles[2] = angles[0];
    angles[5] = main_gear_angle * 0.5;
    angles[17] = main_gear_angle;
    angles[6] = angles[20];
    angles[3] = angles[0] * gearAngles[5] / gearAngles[2];
    angles[4] = gearAngles[2] * -angles[3] / gearAngles[3];
    angles[1] = angles[4];
    angles[14] = angles[7];
    angles[28] = angles[0];
    angles[22] = -angles[0] * gearAngles[27] / gearAngles[21];
    angles[23] = gearAngles[21] * -angles[22] / gearAngles[22];
    angles[24] = main_gear_angle;
    angles[29] = -main_gear_angle * gearAngles[23] / gearAngles[28];
    angles[32] = main_gear_angle;
    angles[0] = -main_gear_angle;
    angles[39] = angles[0] * gearAngles[31] / gearAngles[38];
    angles[38] = gearAngles[38] * -angles[39] / gearAngles[37];
    angles[31] = main_gear_angle;
    angles[37] = angles[0] * gearAngles[30] / gearAngles[36];
    angles[34] = gearAngles[36] * -angles[37] / gearAngles[33];
    angles[36] = gearAngles[33] * -angles[34] / gearAngles[35];
    angles[33] = gearAngles[35] * -angles[36] / gearAngles[32];
    angles[30] = main_gear_angle;
    angles[35] = main_gear_angle;
    angles[27] = main_gear_angle;
    angles[25] = angles[0] * gearAngles[26] / gearAngles[24];
    angles[26] = gearAngles[24] * -angles[25] / gearAngles[25];

    for(int8_t i=0; i<39; i+=3)
    {
        uiGears[i]->setRotate(angles[i + 1]);
        uiGears[i+1]->setRotate(angles[i + 2]);
        uiGears[i+2]->setRotate(angles[i+3]);
    }

    angles[0] = main_gear_angle - 90.0;
    uiGearRail[0]->setDXDY(cos_deg(angles[0]) * 43.0, sin_deg(angles[0]) * 43.0 + 43.0);
    uiGearRail[1]->setDXDY(uiGearRail[0]->getDX(), uiGearRail[0]->getDY());
}

void menu_fader::draw_cursor(float x, float y, float width)
{

    gr_setscale_sprite(cursor[0], width / 512.0, 1.0);
    gr_setxy_sprite(cursor[0],x - 7.0, y);
    gr_draw_sprite(cursor[0], gr_alpha, PLANE_GUI);

    gr_setrotate_sprite(cursor[1],main_gear_angle * 4.0);
    gr_setxy_sprite(cursor[1], x - 7.0, y + 8.0);
    gr_draw_sprite(cursor[1], gr_alpha, PLANE_GUI);

    gr_setrotate_sprite(cursor[2],-main_gear_angle * 4.0);
    gr_setxy_sprite(cursor[2], x - 21.0, y - 1.0);
    gr_draw_sprite(cursor[2], gr_alpha, PLANE_GUI);
}

void menu_fader::update()
{
    if ( fade_alpha_delta != 0.0 )
    {
        fade_alpha += fade_alpha_delta;

        if ( fade_alpha < 0.0 )
        {
            fade_alpha = 0.0;
            fade_alpha_delta = 0.0;
        }
        else if ( fade_alpha > 1.0 )
        {
            fade_alpha = 1.0;
            fade_alpha_delta = 0.0;
        }
    }

    main_gear_angle += 0.4;

    if ( menu_stack.size() == saved_menus )
    {
        if ( context_alpha )
            context_alpha -= 15;
    }
    else
    {
        if ( context_alpha < 255 )
            context_alpha += 15;
    }

    if (context_alpha)
        gears_update();

    if ( !menu_stack.empty() )
    {
        if ( todelete )
        {
            inp_both * inp = get_global_input();

            if (!inp->keyHit(INP_A) && !inp->keyHit(INP_B) && !inp->rawHit(kC_Escape))
            {
                delete menu_stack.back();
                menu_stack.pop_back();
                todelete = false;
            }
        }
        else
        {
            if (menu_stack.size() > saved_menus)
            {
                //if ( dword_86FA94 == 22 )
                //{
                if (menu_stack.back()->update() == 0)
                    todelete = true;
                //}
            }
        }
    }
}

void menu_fader::fade_out(uint8_t r,uint8_t g,uint8_t b, uint8_t a, int32_t frames)
{
    fade_a = a;
    fade_r = r;
    fade_g = g;
    fade_b = b;

    if ( frames > 0 )
        fade_alpha_delta = -1.0 / (double)frames;
    else
    {
        fade_alpha = 0.0;
        fade_alpha_delta = 0.0;
    }
}

void menu_fader::fade_in(uint8_t r,uint8_t g,uint8_t b, uint8_t a, int32_t frames)
{
    fade_a = a;
    fade_r = r;
    fade_g = g;
    fade_b = b;

    if ( frames > 0 )
        fade_alpha_delta = 1.0 / (double)frames;
    else
    {
        fade_alpha = 0.0;
        fade_alpha_delta = 0.0;
    }
}

void menu_fader::draw_doors(int32_t alpha)
{
    if (alpha > 0)
    {
        gr_tex_box box;
        box.a = 255;
        box.r = 128;
        box.g = 128;
        box.b = 128;
        box.autosize = true;
        box.tex_scl_x = 1.0;
        box.tex_scl_y = 1.0;
        box.overlay_tex = false;
        box.skew_in_pix = true;
        box.skew_x = 0;
        box.skew_y = 0;
        box.y = 0;

        float xx = 0.0;
        if (alpha < 255)
        {
            xx = alpha / 255.0;
            xx *= xx;
        }
        else
            xx = 1.0;

        box.tex = doors[0];
        box.x = -480.0 + xx * 480.0;
        gr_draw_tex_box(&box, gr_alpha, PLANE_GUI);


        box.tex = doors[1];
        box.x = 640.0 - xx * 480.0;
        gr_draw_tex_box(&box, gr_alpha, PLANE_GUI);
    }

}

void menu_fader::draw_gears(int32_t alpha)
{
    if (alpha > 0)
    {

        float yy = 0.0;
        if (alpha < 255)
        {
            yy = alpha / 255.0;
            yy *= yy;
        }
        else
            yy = 1.0;

        gearUpper.draw_all_dx_dy(PLANE_GUI,0,-128 + 128 * yy);
        gearLower.draw_all_dx_dy(PLANE_GUI,0,128 - 128 * yy);
    }
}

void menu_fader::draw_context()
{
    if ( context_alpha && (menu_stack.size() > saved_menus || saved_menus == 0))
    {
        draw_doors(context_alpha);
        draw_gears(context_alpha);

        menuProfile.setColor(context_alpha, 255,255,255);
        menuProfile.draw_all(PLANE_GUI);
        /*if ( get_huge_var() && byte_887435 ) //HACK DRAW NAMES
        {
          v12 = (graph_2dui **)get_huge_var()->imgs;
          v4 = (char *)&get_huge_var()->imgs[1];
        }
        else
        {
          v12 = (graph_2dui **)&get_player_profile(0)->player_name_sprite;
          v4 = (char *)&get_player_profile(1)->player_name_sprite;
        }
        v13 = v4;
        v5 = 0;
        do
        {
          v6 = (&v12)[v5];
          ((void (__thiscall *)(graph_2dui **, int))(*v6)->tex_id)((&v12)[v5], v1);
          v7 = *(int *)((char *)&menuProfile_gui100 + v5 * 4);
          v8 = *(float *)(v7 + 16) + 10.0;
          v9 = v8;
          v10 = *(float *)(v7 + 12) + 88.0;
          LODWORD((*v6)->v[0].tu)(v6, LODWORD(v10), LODWORD(v9));
          ((void (__thiscall *)(graph_2dui **, signed int))(*v6)->tex_id)(v6, -1);
          ++v5;
        }
        while ( v5 < 2 );*/
        if ( !menu_stack.empty() )
            menu_stack.back()->draw();
    }
}

void menu_fader::draw()
{
    if ( fade_alpha > 0.0 )
        gr_draw_box(0,0,640,480, fade_r, fade_g ,fade_b, fade_alpha * fade_a, PLANE_GUI);

    draw_context();
}

int32_t menu_fader::get_count()
{
    return menu_stack.size();
}

void menu_fader::add_menu(ingame_menu *menu)
{
    menu_stack.push_back(menu);
}

bool menu_fader::is_not_empty()
{
    return (menu_stack.size() - saved_menus) > 0;
}

void menu_fader::clear_list()
{
    int32_t num = menu_stack.size() - saved_menus;
    for (int32_t i =0; i < num; i++)
    {
        delete menu_stack.back();
        menu_stack.pop_back();
    }

    if (menu_stack.size() == 0)
    {
        todelete = false;
        context_alpha = 0;
    }
}



static menu_fader *global_menu_fader = NULL;


menu_fader *menu_get_fader()
{
    if (!global_menu_fader)
        global_menu_fader = new menu_fader;

    return global_menu_fader;
}

int32_t menu_get_count()
{
    return menu_get_fader()->get_count();
}

void menu_add(ingame_menu *menu)
{
    menu_get_fader()->add_menu(menu);
}


screen *screen_create(id_screen scrn)
{
    switch (scrn)
    {
    case SCREEN_GAMEPLAY:
        return new screen_gameplay;

    case SCREEN_TITLE:
        return new screen_title;

    case SCREEN_MAIN:
        return new screen_main;

    case SCREEN_LOADING:
        return new screen_loading;

    case SCREEN_UNK:
    default:
        return new screen_exit;
    }
    return NULL;
}



inp_both *global_input = NULL;

inp_both *get_global_input()
{
    if (!global_input)
        global_input = new inp_both;

    return global_input;
}
