#ifndef PROFILE_H_INCLUDED
#define PROFILE_H_INCLUDED

struct s_keybind
{
    uint32_t inp_id;
    uint32_t UP;
    uint32_t DOWN;
    uint32_t LEFT;
    uint32_t RIGHT;
    uint32_t A;
    uint32_t B;
    uint32_t C;
    uint32_t D;
    uint32_t AB;
    uint32_t BC;
    uint32_t START;
    uint32_t unk;
};

struct s_profile
{
    char    name[256];
    s_keybind kbd;
    s_keybind joy;
    uint8_t unk1;
    uint8_t unk2;
    //           [charid] [deckid] [cardid]
    int16_t decks[20][4][20];
};

s_profile *profile_load_from_file(const char *file);
bool profile_load_from_file(const char *file, s_profile *profile);

void profile_init_profile(s_profile *profile);

#endif // PROFILE_H_INCLUDED
