#include "../global_types.h"
#include "../scene.h"
#include "../input.h"
#include "../gui.h"
#include "menus.h"

screen_loading::screen_loading()
{
    bkg = gr_load_cv2("data/scene/logo/kitou.cv2",NULL);
    gear_tex = gr_load_cv2("data/scene/logo/gear.cv2",NULL);
    gear = gr_create_sprite();

    gr_set_smoth(gear_tex, true);
    gr_set_spr_tex(gear, gear_tex);

    gr_info inf = gr_get_info(gear_tex);

    gr_setorigin_sprite(gear, inf.w / 2.0, inf.h / 2.0);

    frames = 0;
}

screen_loading::~screen_loading()
{
    gr_delete_sprite(gear);
    gr_delete_tex(gear_tex);
    gr_delete_tex(bkg);
}

id_screen screen_loading::update()
{
    frames++;

    if (frames > 180) //HACK
        return SCREEN_GAMEPLAY;
    else
        return SCREEN_LOADING;
}

bool screen_loading::draw()
{
        gr_tex_box box;
        box.a = 255;
        box.r = 255;
        box.g = 255;
        box.b = 255;
        box.autosize = true;
        box.tex_scl_x = 1.0;
        box.tex_scl_y = 1.0;
        box.overlay_tex = false;
        box.skew_in_pix = true;
        box.skew_x = 0;
        box.skew_y = 0;
        box.x = 0;
        box.y = 0;
        box.tex = bkg;

        gr_draw_tex_box(&box, gr_alpha, PLANE_GUI);

        gr_setxy_sprite(gear, 582.0, 446.0);
        gr_setrotate_sprite(gear, frames);
        gr_draw_sprite(gear, gr_alpha, PLANE_GUI);

        gr_setxy_sprite(gear, 605.0, 428.0);
        gr_setrotate_sprite(gear, -frames);
        gr_draw_sprite(gear, gr_alpha, PLANE_GUI);

        return true;
}

id_screen screen_loading::getID()
{
    return SCREEN_LOADING;
}
