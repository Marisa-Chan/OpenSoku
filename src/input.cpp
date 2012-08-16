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
    }

    flush_kframes();
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

    for (uint32_t i=0; i < sl; i++)
    {
        uint8_t t = 0;

        char in = tolower(sq[i]);

        if (in == '0')
            t = 0;
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
        buf[i] = t;
    }

    uint32_t j = 0;

    for (int32_t i=frames-1; i > 0; i--)
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
            }
        }
        else if (k_frames[i] == 0) // no input check
            j++;


        if (j == sl)
        {
            flush_kframes();
            return 0;
        }

    }

    return -1;
}
















void inp_kb::update()
{
    flush_cur();

    for (uint32_t i=0; i<sf::Keyboard::KeyCount; i++)
        state[i] = kbd.isKeyPressed((sf::Keyboard::Key)i);

    for (uint32_t i=0; i<INP_KEYS; i++)
        key_dn[i] = state[map[i]];

    fill_kframes();
}

bool inp_kb::rawPressed(uint32_t key)
{
    return state[key];
}

inp_kb::inp_kb()
{
    for (uint32_t i=0; i<sf::Keyboard::KeyCount; i++)
        state[i] = false;

    load_def_profile();
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


void inp_js::load_profile(kmapper keys)
{
    return;
}

void inp_js::load_def_profile()
{
    return;
}

void inp_js::update()
{
    return;
}


inp_ab *inp_createinput(uint8_t type)
{
    switch(type)
    {
        case INP_TYPE_KB:
            return new inp_kb;
        case INP_TYPE_JOY:
            return new inp_js;
        case INP_TYPE_NONE:
        default:
            return new inp_none;
    }
}
