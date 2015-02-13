#include "../global_types.h"
#include "../scene.h"
#include "menus.h"

screen_gameplay::screen_gameplay()
{
    scene = scene_get_scene();
}

id_screen screen_gameplay::update()
{
    int32_t t = scene->update();
    switch (t)
    {
    case 1:
        if ( settings_get()->get_gameplay() == GAMEPLAY_REPLAY )
            return SCREEN_MAIN;
        /*
        if ( !game_type_get() || (v3 = game_type_get() == GAME_TYPE_ARCADE, result = 3, v3) )//HACK
        result = 16;
        return result;*/
        return SCREEN_MAIN; // HACK
    case 2:
        return SCREEN_MAIN;
    case 3:
        return (id_screen)20;

    case 0:
    default:
        return SCREEN_GAMEPLAY;
    }
    return SCREEN_MAIN;
}

bool screen_gameplay::draw()
{
    gr_clear(126,206,244);
    if (true)//HACK DON'T NEED FRAME SKIP?
    {
        scene->func14();
        return true;
    }

    return false;
}

void screen_gameplay::onExit()
{
    menu_get_fader()->clear_list();
    menu_get_fader()->fade_out(0, 0, 0, 0, 0);
}



id_screen screen_gameplay::getID()
{
    return SCREEN_GAMEPLAY;
}
