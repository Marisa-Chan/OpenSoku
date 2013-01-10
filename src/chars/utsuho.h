#ifndef UTSUHO_CPP_INCLUDED
#define UTSUHO_CPP_INCLUDED

class char_utsuho: public char_c
{
private:
    gr_tex  *backtex;
    gr_shader *shader;
    float      shd_p;

    public:
    char_utsuho(inp_ab *func,uint8_t pal = 0);

    void func10();
    void func20();
    void set_seq_params();
    void draw(gr_shader *shader = NULL);
    void draw_shadow(shd_trans *trans, gr_shader *shader = NULL);
};

#endif // UTSUHO_CPP_INCLUDED
