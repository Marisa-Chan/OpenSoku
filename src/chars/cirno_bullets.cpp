#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "cirno_bullets.h"
#include <math.h>


void cirno_bullets::func10()
{
    switch(get_seq())
    {
    default:
        if (process())
            active = false;
    }
}

void cirno_bullets::set_seq_params()
{
    switch(get_seq())
    {
    default:
    break;
    }
}




