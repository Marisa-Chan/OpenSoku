#ifndef C_SCENE_ONE_H_INCLUDED
#define C_SCENE_ONE_H_INCLUDED

#include "scene.h"
#include "battle_ui.h"

class c_scene_one: public c_scene
{
    public:
    c_scene_one();

    virtual void init(background *bg, char_c *p1, char_c *p2);
    virtual int8_t update();
    virtual int8_t state0_update();
    virtual int8_t state1_update();
    virtual int8_t state2_update();
    virtual int8_t state3_update();
    virtual int8_t state5_update();
    virtual int8_t state6_update();
    virtual int8_t state7_update();
    virtual void func11(char_c *pl);
    virtual void func12();
    virtual void func13(int32_t val);
    virtual void func14();
    virtual void func15();
    virtual void func16();

    protected:

    int8_t field_904;
};

#endif // C_SCENE_ONE_H_INCLUDED
