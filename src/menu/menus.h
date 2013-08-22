#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <list>
#include <deque>

using namespace std;

enum id_screen
{
    SCREEN_UNK = -1,
    SCREEN_TITLE = 0,
    SCREEN_MAIN  = 2,
    SCREEN_GAMEPLAY = 5
};

class screen
{
public:
    virtual ~screen();
    virtual id_screen update() = 0; //func1, Return next screen ID
    virtual bool draw() = 0; //func2
    //virtual void func3();
    virtual void onStart(); //func4
    virtual void onExit(); //func5
    virtual id_screen getID() = 0;
};

class screen_exit: public screen
{
public:
    id_screen update()
    {
        return SCREEN_UNK;
    }
    bool draw()
    {
        return false;
    }
    id_screen getID()
    {
        return SCREEN_UNK;
    }
};

class ingame_menu
{
public:
    virtual ~ingame_menu();

    //virtual void func1() = 0;
    virtual int32_t update() = 0; //func2
    virtual void draw()   = 0; //func3
};

class fader
{
protected:
    uint8_t a,r,g,b;

public:
    fader();
    void init();        //func0
    void   fade_in();   //func2
    int8_t fade_out();  //func3
    void   draw();      //func4
};

typedef list<screen *>              scrn_list;
typedef list<screen *>::iterator    scrn_list_it;

typedef deque<ingame_menu *>              menu_list;
typedef deque<ingame_menu *>::iterator    menu_list_it;

class menu_fader
{
protected:
    menu_list  menu_stack;
    bool todelete;

    uint32_t  saved_menus;

    float fade_alpha;
    float fade_alpha_delta;

    float main_gear_angle;

    int32_t context_alpha;

    gr_tex *doors[2];

    gr_tex *cursor_tex[3];
    gr_sprite *cursor[3];

    gui_holder menuProfile;
    gui_element *uiProfileNames[2];

    gui_holder gearUpper;
    gui_holder gearLower;

    gui_element *uiGears[40];
    float gearAngles[40];
    gui_element *uiGearRail[2];

public:

    menu_fader();
    ~menu_fader();

    void update(); //func2
    void draw();   //func3
    void gears_update();
    void draw_context();
    void draw_doors(int32_t alpha);
    void draw_gears(int32_t alpha);
    void draw_cursor(float x, float y, float width);

    int32_t get_count();
    void add_menu(ingame_menu *menu);
    bool is_not_empty();
    void clear_list();
};

menu_fader *menu_get_fader();
int32_t menu_get_count();
void menu_add(ingame_menu *menu);


screen *screen_create(id_screen);
inp_both *get_global_input();

#include "title.h"
#include "gameplay.h"
#include "pause.h"

#endif // MENUS_H_INCLUDED
