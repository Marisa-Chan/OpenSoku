#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "alice.h"

char_alice::char_alice(inp_ab *func):
    char_c::char_c(func)
{
    load_dat("alice",0);
};

char_alice::char_alice(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    load_dat("alice",pal);
};
