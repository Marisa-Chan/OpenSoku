#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED


class char_c
{
    protected:

    float x;
    float y;
    float dir;
    char_graph   viz;

    inp_ab      *input;


    public:

    char_c(inp_ab *func);

    void set_seq(uint32_t idx);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool process(bool ignore_loop = false);
    char_frame * get_pframe();

    void input_update();

    float getX();
    float getY();

    void setX(float x);
    void setY(float y);
    void setXY(float x,float y);
    void setDir(float d);
    float getDir();
    void mvX(float x);
    void mvY(float y);

    virtual void draw(float x, float y, float dir);
    virtual void draw();

    virtual void basic_input();
};

#endif // CHARACTER_DEF_H_INCLUDED
