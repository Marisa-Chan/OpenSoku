#include "menus.h"
#include "title.h"

id_menus menu_id = MENU_TITLE;


void menu_call()
{
    switch(menu_id)
    {
    case MENU_TITLE:
        menu_title_call();
    default:
        break;
    }
}
