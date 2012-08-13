#include "global_types.h"
#include "input.h"

void inp_ab::flush_cur()
{
    for (uint32_t i=0; i<INP_KEYS; i++)
    {
        pr_key_dn[i] = key_dn[i];
        key_dn[i] = false;
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

void inp_kb::update()
{
    for (uint32_t i=0; i<sf::Keyboard::KeyCount; i++)
    {
        state[i] = kbd.isKeyPressed((sf::Keyboard::Key)i);
    }
}

bool inp_kb::rawPressed(uint32_t key)
{
    return state[key];
}

inp_kb::inp_kb()
{
    for (uint32_t i=0; i<sf::Keyboard::KeyCount; i++)
        state[i] = false;
}
