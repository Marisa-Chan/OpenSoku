#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED


class char_c
{
    protected:

    char_graph   viz;

    inp_ab      *input;

    public:

    float x;
    float y;
    float dir;
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

    int16_t field_196;
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

    int8_t  field_49A;

    int8_t  not_charge_attack;


    int16_t health;
    int16_t SP;

    float   speed_mult;
    int16_t field_834;


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


    virtual void draw(float x, float y, float dir);
    virtual void draw();

    virtual void check_seq_input();

    bool flip_to_enemy();
    void reset_forces();

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

#endif // CHARACTER_DEF_H_INCLUDED
