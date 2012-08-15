#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "marisa.h"

char_marisa::char_marisa()
{
    viz.load_dat("marisa",0);
};

char_marisa::char_marisa(uint8_t pal)
{
    viz.load_dat("marisa",pal);
};
