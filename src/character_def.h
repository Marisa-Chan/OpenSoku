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

    char_c *enemy;

    char_c(inp_ab *func);

    int16_t field_196;
    int16_t field_4A8;
    int8_t  field_4C4;
    int8_t  field_571;
    float   field_744;
    float   field_74C;
    float   field_564;
    float   field_568;
    int8_t  field_572;








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

    virtual void basic_input();
};

#endif // CHARACTER_DEF_H_INCLUDED
