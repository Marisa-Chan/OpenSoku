#ifndef MARISA_CPP_INCLUDED
#define MARISA_CPP_INCLUDED

class char_marisa: public char_c
{
    public:
    char_marisa(inp_ab *func,uint8_t pal = 0);

    void set_seq_params();

    void func10();
    void func20();
    c_bullet *new_bullet();
};

#endif // MARISA_CPP_INCLUDED
