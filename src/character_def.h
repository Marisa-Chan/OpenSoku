#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED

#define MAX_CHR_SFX     0x100

#include "bullets.h"

class c_bullet;

class char_c : public c_meta
{
    protected:

    inp_ab      *input;
    bullist     bullets;

    public:

        int8_t input_function;//HACK



    sfxc *sfx[MAX_CHR_SFX];

    char_c(inp_ab *func);

    int16_t field_4BA;
    int16_t field_4BC;
    int16_t field_4C0;
    int8_t  field_4C4;
    int8_t  field_571;
    float   field_744;
    float   field_74C;
    float   field_564;
    float   field_568;
    int8_t  field_572;


    int16_t time_stop;
    int16_t life_recovery;
    int8_t  controlling_type;
    int16_t current_card_energy;
    int16_t spell_energy;
    int16_t max_spell_energy;
    int16_t spell_energy_stop;

    int32_t field_110;
    int8_t  field_114;
    int8_t  field_115;
    int8_t  field_116;
    int8_t  field_18C;
    int32_t field_198;
    float   field_19C;
    int8_t  field_49D;
    int16_t field_4A4;
    int16_t field_4A6;
    int16_t field_4AA;
    int16_t field_4AC;
    int16_t field_4BE;
    int16_t field_4C2;
    int32_t field_4C8;
    int8_t  field_4CC;
    int8_t  field_4CD;
    int8_t  field_4CE;
    int16_t field_4D4;
    int8_t  field_4D8;
    int16_t field_51C;
    int16_t field_520;
    int16_t field_522;
    int16_t field_524;
    int16_t field_526;
    int16_t field_52A;
    int32_t field_530;
    int32_t field_534;
    int32_t field_538;
    int32_t field_53C;
    int32_t field_540;
    int32_t field_544;
    int32_t field_548;
    int32_t field_54C;
    int32_t field_550;
    float   field_554;
    int32_t field_558;
    int16_t field_560;
    int8_t  field_56C;
    int8_t  field_56D;
    int8_t  field_56E;
    int8_t  field_56F;
    int8_t  field_570;
    int8_t  field_574;
    int8_t  field_577;
    int8_t  field_578;
    int32_t field_6EC;
    int8_t  cards_added;    // 0x5E6
    int32_t field_710;
    int16_t field_740;
    int16_t field_7D0;
    int16_t field_7D2;
    int16_t field_7D4;
    int16_t field_7D6;
    int16_t field_7D8;
    float   field_7DC;
    float   field_7E4;
    float   field_7E8;
    float   field_7EC;
    float   field_7F0;
    bool    bbarrier_show;  //if true - block barrier showing  0x7F5
    int8_t  field_7F7;
    int16_t field_7F8;
    int8_t  field_800;
    int8_t  field_801;
    int8_t  field_802;
    int8_t  field_803;
    int8_t  field_804;
    int32_t field_808;
    int8_t  field_80C;
    int8_t  field_80D;
    int8_t  field_80E;
    int32_t field_810;
    int32_t field_814;
    int16_t field_82A;
    int16_t field_836;
    int32_t field_838;
    int8_t  field_83C;
    int32_t field_840;
    int32_t field_844;
    int32_t field_848;
    int16_t field_84C;
    int16_t field_84E;
    int16_t field_850;
    int16_t field_852;
    float   field_854;
    float   field_858;
    float   field_85C;
    float   field_860;
    float   field_864;
    int16_t field_882;
    int16_t field_892;
    int16_t field_890;
    int16_t field_894;
    float   field_898;
    float   field_89C;
    int16_t weather;        //Must be global var
    int16_t weather_time;   //Must be global var
    int16_t weather_var;    //Must be global var???
    int32_t time_count;    //Must be global var???
    int8_t  player_index;
    float  dash_angle;




    int16_t field_4C6;
    int16_t field_51E;
    int8_t field_575;
    int8_t field_576;
    int8_t field_880;

    int16_t x_delta; //x_offset
    int16_t y_delta; //y_offset

    int16_t health_prev;
    int16_t combo_count;
    float combo_rate;
    int16_t combo_damage;
    int16_t combo_limit;
    int16_t correction;



    void sub_486FD0(float p1, float p2);


    int8_t  field_49A;

    int8_t  not_charge_attack;
    int8_t  air_dash_cnt;



    int16_t SP;

    float   speed_mult;
    int16_t tengu_fan;  //by system spell card


    uint32_t pres_comb;
    uint32_t pres_move;


    bullist *get_bullets();

    void set_seq(uint32_t idx);

    void input_update();

    virtual void draw(gr_shader *shader = NULL);

    virtual void check_seq_input();

    void stopping(float p);
    void stopping_posit(float p);

    bool flip_to_enemy();
    bool field_sq_check();
    void flip_with_force();
    void reset_forces();
    void health_to_max();

    void play_sfx(uint32_t idx);

    virtual void func10();
    virtual void set_seq_params(); //func15
    virtual void func16();
    virtual void func18();
    virtual void func20();

    virtual c_bullet *new_bullet() ;

    //input functions
    bool keyDown(inp_keys key);
    bool keyHit(inp_keys key);
    int8_t gX(int8_t dir);
    int8_t gY();
    void   setgX(int8_t dir);
    void   setgY(int8_t dir);
};

typedef list<char_c *> charlist;
typedef list<char_c *>::iterator charlist_iter;



bool char_idle_or_move(char_c *chr);
bool char_is_shock(char_c *chr);
bool char_is_block_knock(char_c *chr);
void char_h_move(char_c *chr, float move);
bool sub10func(char_c *chr);
void char_loadsfx(char_c *chr, const char *name);



bool hi_jump_after_move(char_c *chr);
bool border_escape_ground(char_c *chr);
bool hi_jump(char_c *chr, uint16_t cprior, uint32_t hjc);
bool fw_bk_dash_ground(char_c *chr, uint16_t cprior, uint32_t hjc);
bool border_escape_air(char_c *chr);
bool fwd_dash_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse);
bool bkg_dash_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse);
bool flying_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash);

void sub_4689D0(char_c *, int32_t);

#endif // CHARACTER_DEF_H_INCLUDED
