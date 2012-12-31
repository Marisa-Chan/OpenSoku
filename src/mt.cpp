#include "global_types.h"
#include "mt.h"

void mtwist::gen_next_table()
{
    static const uint32_t table[2] = { 0, 0x9908B0DF};
    uint32_t v;

    for (uint16_t i = 0; i < 0x26F; i++)
    {
        v = ( mt[i] & 0x80000000) | (mt[i + 1] & 0x7fffffff);

        mt[i] = mt[( i + 0x18D) % 0x270] ^ (v >> 1) ^ table[v & 1];
    }

    v = (mt[0x26F] & 0x80000000) | (mt[0] & 0x7fffffff);

    mt[0x26F] = mt[0x18C] ^ (v >> 1);

    if (v & 1)
        mt[0x26F] ^= table[1];

    pos = 0;
}

void mtwist::set_seed(uint32_t seed)
{
    mt[0] = seed;
    for (uint16_t i = 1; i < 0x270; i++)
        mt[i] = 0x6C078965 * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;

    gen_next_table();
}

uint32_t mtwist::get_next()
{
    if (pos >= 0x270)
        gen_next_table();

    uint32_t v = mt[pos];

    pos++;

    v ^= (v >> 11);
    v ^= (v << 7 ) & 0x9d2c5680;
    v ^= (v << 15) & 0xefc60000;
    v ^= (v >> 18);

    return v;
}

uint32_t mtwist::get_next_ranged(uint32_t range)
{
    return get_next() / (0xFFFFFFFF / range);
    //return get_next() % (range+1);
}

mtwist::mtwist()
{
    pos = 0;
}

mtwist::mtwist(uint32_t seed)
{
    set_seed(seed);
}
