#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED

class char_c
{
    protected:

    float x;
    float y;
    char_graph   viz;

    inp_ab      *input;


    public:

    void set_seq(uint32_t idx);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool process(bool ignore_loop = false);

    virtual void draw(float x, float y, float dir);
};

#endif // CHARACTER_DEF_H_INCLUDED
