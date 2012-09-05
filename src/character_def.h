#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED

#define MAX_CHR_SFX     0x100

class char_c
{
    protected:

    char_graph   viz;

    inp_ab      *input;

    public:

    sfxc *sfx[MAX_CHR_SFX];

    float x;
    float y;
    int8_t dir;
    float h_inerc;
    float v_inerc;
    float v_force;

    float angX;
    float angY;
    float angZ;

    float scaleX;
    float scaleY;

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
    int16_t weather;        //Must be global var
    int16_t weather_time;   //Must be global var
    int16_t weather_var;    //Must be global var???
    int32_t time_count;    //Must be global var???
    int8_t  player_index;







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
    void flip_with_force();
    void reset_forces();

    void play_sfx(uint32_t idx);

    virtual void func10();
    virtual void set_seq_params(); //func15
    virtual void func16();
    virtual void func18();
    virtual void func20();
};



bool char_idle_or_move(char_c *chr);
bool char_is_shock(char_c *chr);
void char_h_move(char_c *chr, float move);
bool sub10func(char_c *chr);
void char_loadsfx(char_c *chr, const char *name);

#endif // CHARACTER_DEF_H_INCLUDED
