#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SFML/Window.hpp>
#include "profile.h"

enum inp_types
{
    INP_TYPE_KB,
    INP_TYPE_JOY,
    INP_TYPE_BOTH,
    INP_TYPE_NONE
};

enum kCode
{
    kC_A,
    kC_B,
    kC_C,
    kC_D,
    kC_E,
    kC_F,
    kC_G,
    kC_H,
    kC_I,
    kC_J,
    kC_K,
    kC_L,
    kC_M,
    kC_N,
    kC_O,
    kC_P,
    kC_Q,
    kC_R,
    kC_S,
    kC_T,
    kC_U,
    kC_V,
    kC_W,
    kC_X,
    kC_Y,
    kC_Z,
    kC_Num0,
    kC_Num1,
    kC_Num2,
    kC_Num3,
    kC_Num4,
    kC_Num5,
    kC_Num6,
    kC_Num7,
    kC_Num8,
    kC_Num9,
    kC_Escape,
    kC_LControl,
    kC_LShift,
    kC_LAlt,
    kC_LSystem,
    kC_RControl,
    kC_RShift,
    kC_RAlt,
    kC_RSystem,
    kC_Menu,
    kC_LBracket,
    kC_RBracket,
    kC_SemiColon,
    kC_Comma,
    kC_Period,
    kC_Quote,
    kC_Slash,
    kC_BackSlash,
    kC_Tilde,
    kC_Equal,
    kC_Dash,
    kC_Space,
    kC_Return,
    kC_Back,
    kC_Tab,
    kC_PageUp,
    kC_PageDown,
    kC_End,
    kC_Home,
    kC_Insert,
    kC_Delete,
    kC_Add,
    kC_Subtract,
    kC_Multiply,
    kC_Divide,
    kC_Left,
    kC_Right,
    kC_Up,
    kC_Down,
    kC_Numpad0,
    kC_Numpad1,
    kC_Numpad2,
    kC_Numpad3,
    kC_Numpad4,
    kC_Numpad5,
    kC_Numpad6,
    kC_Numpad7,
    kC_Numpad8,
    kC_Numpad9,
    kC_F1,
    kC_F2,
    kC_F3,
    kC_F4,
    kC_F5,
    kC_F6,
    kC_F7,
    kC_F8,
    kC_F9,
    kC_F10,
    kC_F11,
    kC_F12,
    kC_F13,
    kC_F14,
    kC_F15,
    kC_Pause
};

enum inp_axis
{
    INP_AX_X  = 1,
    INP_AX_Y  = 2,
    INP_AX_Z  = 3,
    INP_AX_R  = 4,
    INP_AX_U  = 5,
    INP_AX_V  = 6,
    INP_AX_PX = 7,
    INP_AX_PY = 8
};

enum inp_keys
{
    INP_UP   = 0,
    INP_DOWN = 1,
    INP_LEFT = 2,
    INP_RIGHT= 3,
    INP_A    = 4,
    INP_B    = 5,
    INP_C    = 6,
    INP_D    = 7,
    INP_AB   = 8,
    INP_BC   = 9,
    INP_ST   = 10
};

#define INP_KEYS  11
#define INPKEYBUF  40 //1.5 sec

#define INP_AXIS(x,y)   (((x & 0xF) << 1 | (y & 0x1)) << 8)


class inp_ab
{
protected:

    bool key_dn[INP_KEYS];
    bool pr_key_dn[INP_KEYS];
    uint8_t key_frm[INP_KEYS];

    int8_t x_axis;
    int8_t y_axis;

    void flush_cur();
    void set_key(inp_keys key);

    uint8_t k_frames[INPKEYBUF];

    void flush_kframes();

public:
    inp_ab();

    //Adds current keystate to input stack
    void fill_kframes();
    //Get DOWN key state
    bool keyDown(inp_keys key);
    //Get Hit key state
    bool keyHit(inp_keys key);
    //Get Up key state
    bool keyUp(inp_keys key);
    //Return timer how many frames key was pressed (255 - infinity)
    uint8_t keyFramed(inp_keys key);
    //Return pressed LEFT/RIGHT with char direction care (1 - forward, -1 - backward, 0 not pressed)
    int8_t gX(int8_t dir);
    //Return pressed UP/DOWN (1 - up, -1 - down, 0 not pressed)
    int8_t gY();
    //Setting current press direction
    void   setgX(int8_t dir);
    void   setgY(int8_t dir);

    //clear all down states
    void zero_input();

    //check if pressed sq seq of num frames with care of direction
    int8_t check_input_seq(const char *sq, uint8_t frames, int8_t direction);

    //update routines
    virtual void update() = 0;
    //loads default profile
    virtual void load_def_profile() = 0;
    //loads profile
    virtual void load_profile(s_profile * prof) = 0;
    //setting device ID (useable for joystick)
    virtual void set_devid(uint32_t) = 0;
};


//keyboard input class
class inp_kb: public inp_ab
{
private:
    sf::Keyboard kbd;

    uint32_t map[INP_KEYS];

public:
    inp_kb();

    void load_profile(s_profile * prof);
    void load_def_profile();
    //get raw pressed keyboard key (any key)
    bool rawPressed(uint32_t key);
    void update();
    void set_devid(uint32_t);
};

//joystick input class
class inp_js: public inp_ab
{
    private:
    sf::Joystick js;
    int32_t joy_id;

    uint32_t map[INP_KEYS];

    bool key_chk(uint32_t key);
public:
    inp_js();

    void load_profile(s_profile * prof);
    void load_def_profile();
    void update();
    void set_devid(uint32_t);
};

//no input class
class inp_none: public inp_ab
{

public:

    void load_profile(s_profile * prof)
        {return;};
    void load_def_profile()
        {return;};
    void update()
        {return;};
    void set_devid(uint32_t)
        {return;};
};

//keyboard and joystick input class
class inp_both: public inp_ab
{
    private:
    inp_js js;
    inp_kb kb;

    public:
    void load_profile(s_profile * prof);
    void load_def_profile();
    void update();
    void set_devid(uint32_t);
};

//Create selected input class
inp_ab *inp_createinput(inp_types type);

#endif // INPUT_H_INCLUDED
