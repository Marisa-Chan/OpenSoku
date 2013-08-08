#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

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


class screen_main: public screen
{
protected:
    gui_holder *title;

    gui_el_t1 *bkg[5];
    gr_tex    *bkg_imgs[5];

    int32_t t_frms;

    float  bkgs[3];

    int8_t title_punkt;
    int8_t title_stage;
    int8_t menu_frames;
    float menu_pos;

    gr_tex *moji1_tex;
    gr_tex *moji2_tex;

    gui_el_t1 *moji1;
    gui_el_t1 moji2;

    gui_el_t0 *men_bkg;
    gui_el_t0 *cop;
    gui_el_t0 *titl;

    gr_tex *gear_tex;
    gui_el_t1 *gear;
    gui_el_t0 *cursor;

    float cur_pos = 0;

    inp_both inp;

public:
    screen_main();
    ~screen_main();

    virtual id_screen update();
    virtual bool      draw();

    virtual id_screen getID();
};

#endif // TITLE_H_INCLUDED
