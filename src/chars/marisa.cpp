#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "marisa.h"

char_marisa::char_marisa(inp_ab *func):
    char_c::char_c(func)
{
    viz.load_dat("marisa",0);
};

char_marisa::char_marisa(inp_ab *func, uint8_t pal):
    char_c::char_c(func)
{
    viz.load_dat("marisa",pal);
};
