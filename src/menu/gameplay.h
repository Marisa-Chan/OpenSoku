#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

class screen_gameplay: public screen
{
    protected:
    c_scene * scene;

    public:
    screen_gameplay();
    virtual id_screen update(); //func1, Return next screen ID
    virtual bool draw(); //func2

    virtual void onExit(); //func5

    virtual id_screen getID();
};


#endif // GAMEPLAY_H_INCLUDED
