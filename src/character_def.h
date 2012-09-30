#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED

#define MAX_CHR_SFX     0x100

#define FF_STAND        0x1
#define FF_CROUCH       0x2
#define FF_AIRBORNE     0x4
#define FF_UNK8         0x8
#define FF_GUARDCANC    0x10
#define FF_CANCELLEABLE 0x20
#define FF_CH_ON_HIT    0x40
#define FF_SUPERARMOR   0x80
#define FF_GUARD        0x100
#define FF_GUARD2       0x200
#define FF_GRAZE        0x400
#define FF_UNK800       0x800
#define FF_UNK1000      0x1000
#define FF_MEL_INV_GND  0x2000
#define FF_INV_FIRE     0x4000
#define FF_INV_AIRBORNE 0x8000
#define FF_INV_MID_BLOW 0x10000
#define FF_INV_LOW_BLOW 0x20000
#define FF_INV_SHOOT    0x40000
#define FF_UNK80000     0x80000
#define FF_UNK100000    0x100000
#define FF_UNK200000    0x200000
#define FF_UNK400000    0x400000
#define FF_UNK800000    0x800000
#define FF_UNK1000000   0x1000000

#define AF_UNK1         0x1
#define AF_MID_HIT      0x2
#define AF_LOW_HIT      0x4
#define AF_AIR_HIT      0x8
#define AF_U_HIT        0x10
#define AF_UNK20        0x20
#define AF_UNK40        0x40       //TRANSLATE
#define AF_UNK80        0x80       //TRANSLATE!
#define AF_UNK100       0x100
#define AF_UNK200       0x200
#define AF_CRASH_HIT    0x400
#define AF_UNK800       0x800
#define AF_UNK1000      0x1000
#define AF_UNK2000      0x2000
#define AF_UNK4000      0x4000
#define AF_KNOCK_BACK   0x8000
#define AF_UNK10000     0x10000
#define AF_UNK20000     0x20000
#define AF_UNK40000     0x40000
#define AF_GUARDCRUSH   0x80000
#define AF_UNK100000    0x100000   //TRANSLATE
#define AF_STAGGER      0x200000
#define AF_UNK400000    0x400000   //TRANSLATE
#define AF_UNK800000    0x800000   //TRANSLATE
#define AF_UNK1000000   0x1000000

class c_bullet;

class char_c : public moveable
{
    protected:

    char_graph   viz;

    inp_ab      *input;

    public:

    sfxc *sfx[MAX_CHR_SFX];

    char_c *enemy;

    char_c(inp_ab *func);

    float   field_1A4;
    float   field_1A8;

    int16_t hit_stop;
    int16_t field_4A8;
    int16_t field_4BE;
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

    int32_t field_110;
    int8_t  field_114;
    int8_t  field_115;
    int8_t  field_116;
    int8_t  field_18C;
    int32_t field_190;
    int8_t  field_194;
    int32_t field_198;
    float   field_19C;
    int16_t field_4AA;
    int16_t field_4AC;
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
    int32_t field_554;
    int32_t field_558;
    int8_t  field_56C;
    int8_t  field_56D;
    int8_t  field_56E;
    int8_t  field_56F;
    int8_t  field_570;
    int8_t  field_574;
    int8_t  field_577;
    int16_t field_7D0;
    int16_t field_7D2;
    int16_t field_7D4;
    int16_t field_7D6;
    int16_t field_7D8;
    float   field_7DC;
    float   field_7E4;
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
    int16_t field_836;
    int32_t field_838;
    int32_t field_840;
    int32_t field_844;
    int32_t field_848;
    int16_t field_84C;
    int16_t field_84E;
    int16_t field_850;
    int16_t field_852;
    int16_t field_892;
    int16_t field_890;
    int16_t weather;        //Must be global var
    int16_t weather_time;   //Must be global var
    int16_t weather_var;    //Must be global var???
    int32_t time_count;    //Must be global var???
    int8_t  player_index;
    float  dash_angle;







    int8_t  field_49A;

    int8_t  not_charge_attack;
    int8_t  air_dash_cnt;


    int16_t health;
    int16_t max_health;
    int16_t SP;

    float   speed_mult;
    int16_t tengu_fan;  //by system spell card


    uint32_t pres_comb;
    uint32_t pres_move;


    uint32_t get_seq();
    uint32_t get_subseq();
    uint32_t get_frame();
    seq * get_seq(uint32_t idx);


    void set_seq(uint32_t idx);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool process(bool ignore_loop = false);
    char_frame * get_pframe();

    void input_update();


    virtual void draw(float x, float y, int8_t dir);
    virtual void draw();

    virtual void check_seq_input();

    bool flip_to_enemy();
    bool field_sq_check();
    void flip_with_force();
    void reset_forces();

    void play_sfx(uint32_t idx);

    virtual void func10();
    virtual void set_seq_params(); //func15
    virtual void func16();
    virtual void func18();
    virtual void func20();

    uint16_t get_prior(uint32_t idx);

    virtual c_bullet *new_bullet() ;

    //input functions
    bool keyDown(inp_keys key);
    bool keyHit(inp_keys key);
    int8_t gX(int8_t dir);
    int8_t gY();
};



bool char_idle_or_move(char_c *chr);
bool char_is_shock(char_c *chr);
void char_h_move(char_c *chr, float move);
bool sub10func(char_c *chr);
void char_loadsfx(char_c *chr, const char *name);

#endif // CHARACTER_DEF_H_INCLUDED
