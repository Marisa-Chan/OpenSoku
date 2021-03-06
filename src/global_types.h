#ifndef GLOBAL_TYPES_H_INCLUDED
#define GLOBAL_TYPES_H_INCLUDED

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>

#include "utils.h"
#include "graph.h"
#include "sfx.h"
#include "moveable.h"
#include "meta.h"

#define CHRBUF 256

enum RENDER_PLANE
{
    PLANE_GUI = 0,
    PLANE_SCENE = 1,
    PLANE_BKG = 2
};

#include "settings.h"

#endif // GLOBAL_TYPES_H_INCLUDED
