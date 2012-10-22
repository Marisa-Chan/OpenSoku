#include "global_types.h"
#include "input.h"

#define KF_LEFT   0x01
#define KF_RIGHT  0x02
#define KF_UP     0x04
#define KF_DOWN   0x08
#define KF_A      0x10
#define KF_B      0x20
#define KF_C      0x40
#define KF_D      0x80


inp_ab::inp_ab()
{
    for (uint32_t i=0; i<INP_KEYS; i++)
    {
        pr_key_dn[i] = false;
        key_dn[i] = false;
        key_frm[i] = 0;
    }

    x_axis = 0;
    y_axis = 0;

    flush_kframes();
}

void inp_ab::zero_input()
{
    for (uint32_t i=0; i<INP_KEYS; i++)
        key_dn[i] = false;
}

void inp_ab::flush_cur()
{
    for (uint32_t i=0; i<INP_KEYS; i++)
    {
        pr_key_dn[i] = key_dn[i];
        key_dn[i] = false;
    }
}

void inp_ab::fill_kframes()
{
    for(uint32_t i=INPKEYBUF-1; i>0; i--)
        k_frames[i] = k_frames[i-1];

    uint8_t vkf = 0;

    if (key_dn[INP_UP])
        vkf |= KF_UP;

    if (key_dn[INP_DOWN])
        vkf |= KF_DOWN;

    if (key_dn[INP_LEFT])
        vkf |= KF_LEFT;

    if (key_dn[INP_RIGHT])
        vkf |= KF_RIGHT;

    if (key_dn[INP_A])
        vkf |= KF_A;

    if (key_dn[INP_B])
        vkf |= KF_B;

    if (key_dn[INP_C])
        vkf |= KF_C;

    if (key_dn[INP_D])
        vkf |= KF_D;

    k_frames[0] = vkf;

    for (uint32_t i=0; i<INP_KEYS; i++)
    {
        if (key_dn[i] && key_frm[i] < 255)
            key_frm[i]++;
        else if (!pr_key_dn[i] && !key_dn[i])
            key_frm[i] = 0;
    }
}

void inp_ab::set_key(inp_keys key)
{
    key_dn[key] = true;
}

bool inp_ab::keyDown(inp_keys key)
{
    return key_dn[key];
}

bool inp_ab::keyHit(inp_keys key)
{
    return key_dn[key] && (!pr_key_dn[key]);
}

bool inp_ab::keyUp(inp_keys key)
{
    return (!key_dn[key]) && pr_key_dn[key];
}

uint8_t inp_ab::keyFramed(inp_keys key)
{
    return key_frm[key];
}

void inp_ab::flush_kframes()
{
    for(uint32_t i=0; i<INPKEYBUF; i++)
        k_frames[i] = 0;
}


int8_t inp_ab::check_input_seq(const char *sq, uint8_t frames, int8_t direction)
{
    uint8_t buf[0x100];

    uint32_t sl = strlen(sq);

    uint8_t XX = KF_A | KF_B | KF_C;

    int8_t ret_val = 0;

    for (uint32_t i=0; i < sl; i++)
    {
        uint8_t t = 0;

        char in = tolower(sq[i]);

        if (in == '0')
            t = KF_DOWN;
        else if (in == '5')
            t = 0;
        else if (in == '1')
            t = KF_LEFT | KF_DOWN;
        else if (in == '2')
            t = KF_DOWN;
        else if (in == '3')
            t = KF_RIGHT | KF_DOWN;
        else if (in == '4')
            t = KF_LEFT;
        else if (in == '6')
            t = KF_RIGHT;
        else if (in == '7')
            t = KF_UP | KF_LEFT;
        else if (in == '8')
            t = KF_UP;
        else if (in == '9')
            t = KF_UP | KF_RIGHT;
        else if (in == 'd')
            t = KF_D;
        else if (in == 'x')
            t = KF_A | KF_B | KF_C ;

        if (direction != 1)
        {
            if (t & KF_LEFT)
                t = (~KF_LEFT & t) | KF_RIGHT;
            else if (t & KF_RIGHT)
                t = (~KF_RIGHT & t) | KF_LEFT;

        }

        if (in == 'r')
            t = KF_RIGHT;
        else if (in == 'l')
            t = KF_LEFT;

        buf[i] = t;
    }

    uint32_t j = 0;

    for (int32_t i=frames-1; i >= 0; i--)
    {
        if (buf[j] != 0)
        {
            if (buf[j] != XX) // movements
            {
                if (k_frames[i] == buf[j])
                    j++;
            }
            else //keys check
            {
                if (k_frames[i] & buf[j])
                    j++;

                if (k_frames[i] & KF_A)
                    ret_val = 1;
                else if (k_frames[i] & KF_B)
                    ret_val = 2;
                else if (k_frames[i] & KF_C)
                    ret_val = 3;
            }
        }
        else if (k_frames[i] == 0) // no input check
            j++;


        if (j == sl)
        {
            flush_kframes();
            if (ret_val == 0)
                ret_val = 1;

            //printf("pressed %s %d\n",sq,ret_val);
            return ret_val;
        }

    }

    return ret_val;
}


int8_t inp_ab::gX(int8_t dir)
{
    return x_axis * dir;
}

int8_t inp_ab::gY()
{
    return y_axis;
}





void inp_kb::update()
{
    flush_cur();

    for (uint32_t i=0; i<INP_KEYS; i++)
        key_dn[i] = kbd.isKeyPressed((sf::Keyboard::Key)map[i]);

    x_axis = 0;
    y_axis = 0;

    if (key_dn[INP_LEFT])
        x_axis -= 1;

    if (key_dn[INP_RIGHT])
        x_axis += 1;

    if (key_dn[INP_UP])
        y_axis += 1;

    if (key_dn[INP_DOWN])
        y_axis -= 1;

    fill_kframes();
}

bool inp_kb::rawPressed(uint32_t key)
{
    return kbd.isKeyPressed((sf::Keyboard::Key)key);
}

inp_kb::inp_kb()
{
    load_def_profile();
}

void inp_kb::set_devid(uint32_t)
{
    return;
}

void inp_kb::load_profile(kmapper maps)
{

}

void inp_kb::load_def_profile()
{
    map[INP_UP]    = kC_Up;
    map[INP_DOWN]  = kC_Down;
    map[INP_LEFT]  = kC_Left;
    map[INP_RIGHT] = kC_Right;
    map[INP_A]     = kC_Z;
    map[INP_B]     = kC_X;
    map[INP_C]     = kC_C;
    map[INP_D]     = kC_S;
    map[INP_AB]    = kC_A;
    map[INP_BC]    = kC_D;
    map[INP_ST]    = kC_Q;
}



inp_js::inp_js()
{
    joy_id = 1;
    load_def_profile();
}

void inp_js::load_profile(kmapper keys)
{
    return;
}

void inp_js::update()
{
    js.update();
    flush_cur();

    for (uint32_t i=0; i<INP_KEYS; i++)
        key_dn[i] = key_chk(map[i]);

    x_axis = 0;
    y_axis = 0;

    if (key_dn[INP_LEFT])
        x_axis -= 1;

    if (key_dn[INP_RIGHT])
        x_axis += 1;

    if (key_dn[INP_UP])
        y_axis += 1;

    if (key_dn[INP_DOWN])
        y_axis -= 1;

    fill_kframes();
}

void inp_js::load_def_profile()
{
    map[INP_UP]    = INP_AXIS(INP_AX_Y,0);
    map[INP_DOWN]  = INP_AXIS(INP_AX_Y,1);
    map[INP_LEFT]  = INP_AXIS(INP_AX_X,0);
    map[INP_RIGHT] = INP_AXIS(INP_AX_X,1);
    map[INP_A]     = 0;
    map[INP_B]     = 1;
    map[INP_C]     = 2;
    map[INP_D]     = 3;
    map[INP_AB]    = 5;
    map[INP_BC]    = 6;
    map[INP_ST]    = 4;
}

void inp_js::set_devid(uint32_t id)
{
    joy_id = id;
}

bool inp_js::key_chk(uint32_t key)
{
    if (key & 0xFF00)
    {
        key >>= 8;

        sf::Joystick::Axis ax= sf::Joystick::X;

        switch( (key >> 1) & 0xF)
        {
        case INP_AX_Y:
            ax = sf::Joystick::Y;
            break;
        case INP_AX_Z:
            ax = sf::Joystick::Z;
            break;
        case INP_AX_R:
            ax = sf::Joystick::R;
            break;
        case INP_AX_U:
            ax = sf::Joystick::U;
            break;
        case INP_AX_V:
            ax = sf::Joystick::V;
            break;
        case INP_AX_PX:
            ax = sf::Joystick::PovX;
            break;
        case INP_AX_PY:
            ax = sf::Joystick::PovY;
            break;
        case INP_AX_X:
        default:
            ax = sf::Joystick::X;
        }

        if (key & 0x1)
            return js.getAxisPosition(joy_id,ax) >= 50;
        else
            return js.getAxisPosition(joy_id,ax) <= -50;
    }
    else
    {
        return js.isButtonPressed(joy_id, key & 0x1F);
    }
}


void inp_both::load_def_profile()
{
    kb.load_def_profile();
    js.load_def_profile();
}

void inp_both::load_profile(kmapper keys)
{
    kb.load_profile(keys);
    js.load_profile(keys);
}

void inp_both::update()
{
    kb.update();
    js.update();

    flush_cur();

    for (uint32_t i=0; i<INP_KEYS; i++)
        key_dn[i] = kb.keyDown((inp_keys)i) || js.keyDown((inp_keys)i);

    x_axis = 0;
    y_axis = 0;

    if (key_dn[INP_LEFT])
        x_axis -= 1;

    if (key_dn[INP_RIGHT])
        x_axis += 1;

    if (key_dn[INP_UP])
        y_axis += 1;

    if (key_dn[INP_DOWN])
        y_axis -= 1;

    fill_kframes();
}

void inp_both::set_devid(uint32_t id)
{
    kb.set_devid(id);
    js.set_devid(id);
}




inp_ab *inp_createinput(uint8_t type)
{
    switch(type)
    {
    case INP_TYPE_KB:
        return new inp_kb;
    case INP_TYPE_JOY:
        return new inp_js;
    case INP_TYPE_BOTH:
        return new inp_both;
    case INP_TYPE_NONE:
    default:
        return new inp_none;
    }
}
