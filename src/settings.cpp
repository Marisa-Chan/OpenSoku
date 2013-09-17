#include "global_types.h"
#include "input.h"
#include "settings.h"

settings *m_settings = NULL;

settings *settings_get()
{
    if (!m_settings)
        m_settings = new settings();

    return m_settings;
}

settings::settings()
{
    profile_init_profile(&profiles[0]);
    profile_init_profile(&profiles[1]);

    difficult = GAME_DIFF_LUNA;
    gametype = GAME_TYPE_P_VS_P;
    gameplay = GAMEPLAY_NORMAL;

    sfx_volume = 100;
}

settings::~settings()
{

}

s_profile *settings::get_profile(int8_t player)
{
    return &profiles[player & 1];
}

GAME_DIFF_TYPE settings::get_difficulty()
{
    return difficult;
}

void settings::set_difficulty(GAME_DIFF_TYPE m_diff)
{
    difficult = m_diff;
}

GAMEPLAY_TYPE settings::get_gameplay()
{
    return gameplay;
}

void settings::set_gameplay(GAMEPLAY_TYPE m_gameplay)
{
    gameplay = m_gameplay;
}

GAME_TYPE settings::get_gametype()
{
    return gametype;
}

void settings::set_gametype(GAME_TYPE m_gametype)
{
    gametype = m_gametype;
}

int32_t settings::get_sfx_volume()
{
    return sfx_volume;
}

void settings::set_sfx_volume(int32_t new_vol)
{
    sfx_volume = new_vol;
}
