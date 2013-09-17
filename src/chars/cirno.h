#ifndef CIRNO_CPP_INCLUDED
#define CIRNO_CPP_INCLUDED

class char_cirno: public char_c
{
    public:

    int32_t field_890;

    char_cirno(inp_ab *func,uint8_t pal = 0);

    void sub_6E28C0();

    void set_seq_params();

    void func10();
    void func20();
    void init_vars();
    c_bullet *new_bullet();
};

#endif // CIRNO_CPP_INCLUDED
