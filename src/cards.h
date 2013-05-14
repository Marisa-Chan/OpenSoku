#ifndef CARDS_H_INCLUDED
#define CARDS_H_INCLUDED

//enum CARD_TYPE

#include <deque>


struct s_card
{
    char name[256];
    char description[4096];

    uint16_t id;
    uint8_t  type;
    uint8_t  cost;
    uint16_t stage;
    uint16_t rare;
    uint16_t sort;
    uint16_t p7;
    uint16_t p9;
    uint16_t p11;
    uint8_t  p8;
    uint8_t p10;
    uint8_t p12;
    uint32_t p13;

    gr_tex * tex;
};

typedef vector<s_card > cards_holder_vec;
typedef map<int32_t,s_card *> card_map;
typedef map<int32_t,s_card *>::iterator card_map_it;
typedef deque<s_card *> card_deq;

struct s_cards
{
    cards_holder_vec cards_holder;
    card_map card_mapping;
};

bool cards_load_cards(s_cards *cards, const char *charname);
s_card *cards_get_card(s_cards *cards, uint32_t id);
void cards_draw_card(s_card * card, int16_t x, int16_t y, float scale, uint8_t plane);
#endif // CARDS_H_INCLUDED
