#ifndef BATTLE_UI_H_INCLUDED
#define BATTLE_UI_H_INCLUDED

#include "gui.h"
#include "infoeffect.h"
#include "character_def.h"

struct btl_std_plr
{
    char_c *chr;
    gui_el_t0 *lifeBarB;
    gui_el_t0 *lifeUnderB;
    gui_el_t0 *borderBarB[5];
    gui_el_t0 *borderBarCrashB[5];
    gui_el_t0 *borderBarFullB[5];
    gui_el_t0 *borderGaugeB[5];
    gui_el_t0 *borderGaugeCrashB[5];
    gui_el_t0 *cardBarBigB[5];
    gui_el_t0 *cardFaceDown[5];
    gui_el_t0 *cardGaugeBigB[5];
    gui_el_t0 *cardGaugeBigB2[5];
    gui_el_t1  addedCards[5];
    c_infoef_fx *cardBlink[5];
    gui_el_t0 *win[2];
    int32_t    health;
    int32_t    health_prev;
};

class battle_ui_std
{
    protected:

    btl_std_plr player[2];

    gui_holder upper;
    gui_holder under;
    gui_holder combo;

    c_infoef_sp inf_eff;

    void init();

    public:

    battle_ui_std();
    ~battle_ui_std();

    void link(char_c *p1, char_c *p2);
    void update();
    void draw();
};


#endif // BATTLE_UI_H_INCLUDED
