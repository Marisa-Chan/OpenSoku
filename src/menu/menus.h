#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <list>

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
    //virtual void func4();
    //virtual void func5();
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

typedef list<ingame_menu *>              menu_list;
typedef list<ingame_menu *>::iterator    menu_list_it;

class menu_fader
{
    protected:
    menu_list  menu_stack;
    bool todelete;

    public:
        menu_fader();

        void update(); //func2
        void draw();   //func3

        int32_t get_count();
        void add_menu(ingame_menu *menu);
        bool isempty();
};

menu_fader *menu_get_fader();
int32_t menu_get_count();
void menu_add(ingame_menu *menu);
bool menu_isempty();


screen *screen_create(id_screen);


#include "gameplay.h"

#endif // MENUS_H_INCLUDED
