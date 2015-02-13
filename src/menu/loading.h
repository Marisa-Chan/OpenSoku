#ifndef LOADING_H_INCLUDED
#define LOADING_H_INCLUDED

class screen_loading: public screen
{
protected:
    gr_tex *bkg;
    gr_tex *gear_tex;
    gr_sprite *gear;

    int32_t frames;

public:
    screen_loading();
    ~screen_loading();
    virtual id_screen update(); //func1, Return next screen ID
    virtual bool draw(); //func2

    virtual id_screen getID();
};

#endif // LOADING_H_INCLUDED
