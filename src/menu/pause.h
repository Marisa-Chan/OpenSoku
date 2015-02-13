#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED

class pause_menu: public ingame_menu
{
protected:

    int8_t cur_pos;
    int8_t state;
    int8_t elements;

    gui_holder gui;
    vector<int> id_elements;
    gui_element * gui_elements[5];

    c_scene *scene;

public:
    pause_menu(c_scene *scn);
    virtual ~pause_menu();

    virtual int32_t update(); //func2
    virtual void draw(); //func3
};

#endif // PAUSE_H_INCLUDED
