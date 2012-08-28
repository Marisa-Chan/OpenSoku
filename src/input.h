#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SFML/Window.hpp>

enum inp_types
{
    INP_TYPE_KB,
    INP_TYPE_JOY,
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


struct kmapper
{
    uint32_t keys[INP_KEYS];
};

class inp_ab
{
protected:

    bool key_dn[INP_KEYS];
    bool pr_key_dn[INP_KEYS];

    int8_t x_axis;
    int8_t y_axis;

    void flush_cur();
    void set_key(inp_keys key);

    uint8_t k_frames[INPKEYBUF];

    void flush_kframes();

public:
    inp_ab();

    void fill_kframes();
    bool keyDown(inp_keys key);
    bool keyHit(inp_keys key);
    bool keyUp(inp_keys key);
    int8_t gX(int8_t dir);
    int8_t gY();

    int8_t check_input_seq(const char *sq, uint8_t frames, int8_t direction);

    virtual void update() = 0;
    virtual void load_def_profile() = 0;
    virtual void load_profile(kmapper keys) = 0;
};

class inp_kb: public inp_ab
{
private:
    sf::Keyboard kbd;

    uint32_t map[INP_KEYS];

public:
    inp_kb();

    void load_profile(kmapper keys);
    void load_def_profile();
    bool rawPressed(uint32_t key);
    void update();
};

class inp_js: public inp_ab
{
public:
    void load_profile(kmapper keys);
    void load_def_profile();
    void update();
};

class inp_none: public inp_ab
{

public:

    void load_profile(kmapper keys)
        {return;};
    void load_def_profile()
        {return;};
    void update()
        {return;};
};



inp_ab *inp_createinput(uint8_t type);

#endif // INPUT_H_INCLUDED
