#ifndef ALICE_CPP_INCLUDED
#define ALICE_CPP_INCLUDED

class char_alice: public char_c
{
    public:
    char_alice(inp_ab *func,uint8_t pal = 0);

    void func10();
    void func20();
    void set_seq_params();
    c_bullet *new_bullet();
};

#endif // MARISA_CPP_INCLUDED
