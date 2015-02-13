#include "../global_types.h"
#include "../scene.h"
#include "../input.h"
#include "../gui.h"
#include "menus.h"

pause_menu::pause_menu(c_scene *scn)
{
    scene = scn;

    cur_pos = 0;
    state = 0;

    if ( settings_get()->get_gametype() != GAME_TYPE_SCENARIO && settings_get()->get_gametype() != GAME_TYPE_ARCADE && settings_get()->get_gametype() != GAME_TYPE_P_VS_C )
    {
        if ( settings_get()->get_gametype() == 7 )
        {
            gui.load_dat("data/menu/battle","pausePractice.dat");
            id_elements.push_back(0);
            id_elements.push_back(1);
            id_elements.push_back(4);
            for (uint32_t i = 0; i < id_elements.size(); i++)
            {
                gui_elements[i] = gui.get_gui(100 + i * 10);
                gui_elements[i]->renderable = true;
            }
        }
        else
        {
            gui.load_dat("data/menu/battle","pause.dat");
            id_elements.push_back(0);
            id_elements.push_back(1);
            id_elements.push_back(2);
            id_elements.push_back(3);
            id_elements.push_back(4);
            for (uint32_t i = 0; i < id_elements.size(); i++)
            {
                gui_elements[i] = gui.get_gui(100 + i * 10);
                gui_elements[i]->renderable = true;
            }
        }
    }
    else
    {
        gui.load_dat("data/menu/battle","pauseStory.dat");
        id_elements.push_back(0);
        id_elements.push_back(1);
        id_elements.push_back(3);
        id_elements.push_back(4);
        for (uint32_t i = 0; i < id_elements.size(); i++)
        {
            gui_elements[i] = gui.get_gui(100 + i * 10);
            gui_elements[i]->renderable = true;
        }
    }

    elements = id_elements.size();
}

pause_menu::~pause_menu()
{

}


int32_t pause_menu::update()
{
    if (scene->game_state != 0)
        return 1;

    switch(state)
    {
    case 0:
    {
        int8_t y = get_global_input()->keyHit(INP_DOWN) - get_global_input()->keyHit(INP_UP);
        if (y > 0)
        {
            cur_pos = (cur_pos + 1) % elements;
            scene_play_sfx(39);
        }
        else if (y < 0)
        {
            cur_pos = (elements + cur_pos - 1) % elements;
            scene_play_sfx(39);
        }

        if (get_global_input()->keyHit(INP_A))
        {
            scene_play_sfx(40);
            switch(id_elements[cur_pos])
            {
            case 0:
                return 0;
            case 1: //key config player1
            case 2: //key config player2
                break;
            case 3:
            case 4:
                if (settings_get()->get_gameplay() == GAMEPLAY_NORMAL)
                {

                }
                else
                {

                }
                if (id_elements[cur_pos] == 3)
                    scene->game_state = 1;
                else
                    scene->game_state = 2;
                return 1;
                break;
            default:
                break;
            }
        }
        else
        {
            if (get_global_input()->keyHit(INP_B) || get_global_input()->rawHit(kC_Escape))
            {
                scene_play_sfx(41);
                return 0;
            }
        }
    }
    break;

    default:
        break;
    }
    return 1;
}

void pause_menu::draw()
{
    gui_element *elm = gui_elements[cur_pos];
    menu_get_fader()->draw_cursor(elm->getX(), elm->getY() + 5.0, 256.0);
    gui.draw_all(PLANE_GUI);
}

