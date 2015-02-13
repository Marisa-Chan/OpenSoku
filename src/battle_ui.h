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

struct combo_info {
    gui_el_t6 *hit_numb;
    gui_el_t6 *rate_numb;
    gui_el_t6 *limit_numb;
    gui_el_t6 *damage_numb;
    gui_el_t0 *RiftAttack;
    gui_el_t0 *smashAttack;
    gui_el_t0 *borderResist;
    gui_el_t0 *chainArts;
    gui_el_t0 *chainSpell;
    gui_el_t0 *counterHit;
};

struct cmb_elmnt {
    float pos_x;
    int32_t timer;
    int8_t id;
};

struct combo_player {
    int32_t last_combo_count;
    int32_t timer;
    float   field_8;
    int32_t field_14;
    int8_t old_correction;
    deque<cmb_elmnt> cmd_deq;
};

class btl_ui
{
protected:
    c_infoef_sp inf_eff;
    btl_std_plr player[2];
    combo_player cmb_plr[2];
    combo_info inf_cmb;

    gui_holder upper;
    gui_holder under;
    gui_holder combo;

    gui_el_t6 *weatherFont001;
    gui_el_t6 *weatherFont000;

    void update_cmb_info(int8_t index);
    void draw_cmb_info(int8_t index);


public:
    btl_ui();
    virtual ~btl_ui();

    virtual void link(char_c *p1, char_c *p2) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void init() = 0;
    virtual void spawneffect(int32_t idx, float x, float y, int8_t dir, int8_t order);
    virtual void spawneffect(int32_t idx);

    void spawn_orb_effect(int32_t idx, uint8_t player, uint8_t orb);
    void clear_cmb_info(int8_t index);
};

class battle_ui_std: public btl_ui
{
protected:

    void init();

public:

    battle_ui_std();
    ~battle_ui_std();

    void link(char_c *p1, char_c *p2);
    void update();
    void draw();
};

btl_ui * get_battle_ui();
battle_ui_std * init_new_battle_ui_std();
void battle_ui_effect(int32_t idx, float x, float y, int8_t dir, int8_t order);

void battle_ui_orbeffect(int32_t idx, uint8_t pl_id, uint8_t orb_id);

#endif // BATTLE_UI_H_INCLUDED
