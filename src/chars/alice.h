#ifndef ALICE_CPP_INCLUDED
#define ALICE_CPP_INCLUDED

class char_alice: public char_c
{
    public:

    int16_t field_890[4];
     //CF_SP_DOLL_COUNT 0x890 // short
     //CF_DOLL_COUNT 0x892 // short

    int16_t field_892;

    int16_t field_898;
    int16_t field_89A;
    float field_89C[4]; // Dolls X
    float field_8AC[4]; // Dolls Y
    int8_t field_8BC[5];

    char_alice(inp_ab *func,uint8_t pal = 0);

    void func10();
    void func20();
    void set_seq_params();
    c_bullet *new_bullet();
    void init_vars();
};

#endif // MARISA_CPP_INCLUDED
