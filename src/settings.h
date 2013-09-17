#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "profile.h"

enum GAME_TYPE
{
    GAME_TYPE_SCENARIO = 0,
    GAME_TYPE_ARCADE = 1,
    GAME_TYPE_P_VS_C = 2,
    GAME_TYPE_P_VS_P = 3,
    GAME_TYPE_HOST   = 4,
    GAME_TYPE_CLIENT = 5,
    GAME_TYPE_SPECTATE = 6,
    GAME_TYPE_UNK      = 7,
    GAME_TYPE_TRAINING = 8
};

enum GAMEPLAY_TYPE
{
    GAMEPLAY_NORMAL = 1,
    GAMEPLAY_REPLAY = 2
};

enum GAME_DIFF_TYPE
{
    GAME_DIFF_EASY = 0,
    GAME_DIFF_NORMAL = 1,
    GAME_DIFF_HARD = 2,
    GAME_DIFF_LUNA = 3
};

class char_c;
class background;

class settings
{
protected:

    s_profile profiles[2];
    int32_t sfx_volume;
    int32_t bgm_volume;
    int8_t fullscreen;
    int8_t show_fps;
    int8_t skip_1_frame;
    int8_t replay_save_mode;
    int8_t simple_utsuho;
    GAME_DIFF_TYPE difficult;
    GAMEPLAY_TYPE  gameplay;
    GAME_TYPE      gametype;

    background *bkg;
    int32_t     bkg_id;

    char_c    *chars[2];
    int32_t    char_id[2];
    int32_t    deck_id[2];
    int32_t    pal_id[2];

public:
    settings();
    ~settings();

    s_profile *get_profile(int8_t player);

    GAME_TYPE get_gametype();
    void      set_gametype(GAME_TYPE type);

    GAME_DIFF_TYPE get_difficulty();
    void           set_difficulty(GAME_DIFF_TYPE diff);

    GAMEPLAY_TYPE get_gameplay();
    void          set_gameplay(GAMEPLAY_TYPE type);

    int32_t get_sfx_volume();
    void    set_sfx_volume(int32_t volume);


};

settings *settings_get();

#endif // SETTINGS_H_INCLUDED
