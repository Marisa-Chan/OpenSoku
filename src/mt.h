#ifndef MT_H_INCLUDED
#define MT_H_INCLUDED

class mtwist {
private:
    uint32_t	mt[0x270];
    uint16_t	pos;

    void gen_next_table();
public:
    void set_seed(uint32_t seed);
    uint32_t get_next();
    uint32_t get_next_ranged(uint32_t range);

    mtwist();
    mtwist(uint32_t seed);
};

#endif // MT_H_INCLUDED
