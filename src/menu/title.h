#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

void menu_title_call();

class screen_title: public screen
{
    protected:
    int32_t time;
    gr_tex  *img;

    public:
    screen_title();
    ~screen_title();

    virtual id_screen update(); //func1, Return next screen ID
    virtual bool draw(); //func2

    virtual id_screen getID();
};

#endif // TITLE_H_INCLUDED
