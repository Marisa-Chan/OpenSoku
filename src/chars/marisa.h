#ifndef MARISA_CPP_INCLUDED
#define MARISA_CPP_INCLUDED

class char_marisa: public char_c
{
public:

    int16_t field_890;
    int16_t field_892;
    int16_t field_894;
    //__int16 field_896;
    float   field_898;
    float   field_89C;
    float   field_8A0;
    float   field_8A4;
    int8_t  field_8A8;
    //int8_t  field_8A9;
    //int8_t  field_8AA;
    //int8_t  field_8AB;

    char_marisa(inp_ab *func,uint8_t pal = 0);

    void set_seq_params();

    void func10();
    void func20();
    void init_vars();
    c_bullet *new_bullet();
};

#endif // MARISA_CPP_INCLUDED
