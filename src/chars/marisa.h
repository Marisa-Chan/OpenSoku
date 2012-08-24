#ifndef MARISA_CPP_INCLUDED
#define MARISA_CPP_INCLUDED

class char_marisa: public char_c
{
    public:
    char_marisa(inp_ab *func);
    char_marisa(inp_ab *func,uint8_t pal);

    void stopping();
    void set_seq_params();

    void func10();
};

#endif // MARISA_CPP_INCLUDED
