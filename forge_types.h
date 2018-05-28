#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

#define __DEBUG__


#include <Adafruit_LEDBackpack.h>
#include "Adafruit_GFX.h"

typedef unsigned short short_t;
typedef short_t forge_err;
typedef short_t forge_status;
typedef Adafruit_7segment seven_seg;
typedef Adafruit_GFX gfx;

static const forge_err ERR_UNKNOWN_MODE = 1;
static const forge_status SUCCESS       = 1;
static const forge_status ERR           = 0;    



#endif FORGE_TYPES_H

