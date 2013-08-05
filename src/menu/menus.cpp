#include "../global_types.h"
#include "../scene.h"
#include "menus.h"
#include "title.h"


screen::~screen()
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
}

void menu_fader::update()
{
    if (todelete)
    {
        if (!menu_stack.empty())
            delete menu_stack.front();

        menu_stack.pop_front();
        todelete = false;
    }

    if (!menu_stack.empty())
        if (menu_stack.front()->update() == 0)
            todelete = true;
}

void menu_fader::draw()
{
    if (!menu_stack.empty())
        menu_stack.front()->draw();
}

int32_t menu_fader::get_count()
{
    return menu_stack.size();
}

void menu_fader::add_menu(ingame_menu *menu)
{
    menu_stack.push_front(menu);
}

bool menu_fader::isempty()
{
    return menu_stack.empty();
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

bool menu_isempty()
{
    return menu_get_fader()->isempty();
}

screen *screen_create(id_screen scrn)
{
    switch (scrn)
    {
        case SCREEN_GAMEPLAY:
            return new screen_gameplay;

        case SCREEN_TITLE:
            return new screen_title;

        case SCREEN_UNK:
        case SCREEN_MAIN:
        default:
        return new screen_exit;
    }
    return NULL;
}


