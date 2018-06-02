#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

// Don't comment this line out unless
// you want to just spam the snot out of the 
// serial out.  It will also inflate the size of the code space
// to something like the twinky in ghostbusters
//
#define DISABLE_LOGGING


#include <Adafruit_LEDBackpack.h>
#include "Adafruit_GFX.h"

typedef double temp_t;
typedef unsigned short setpoint_t;
typedef unsigned short short_t;
typedef short_t forge_err;
typedef short_t forge_status;
typedef Adafruit_7segment seven_seg;
typedef Adafruit_GFX gfx;

static const forge_err ERR_UNKNOWN_MODE = 1;
static const forge_status SUCCESS       = 1;
static const forge_status ERR           = 0;

static const int UP_BTN_PIN     = 2;   // Pin for the 'up' button
static const int DN_BTN_PIN     = 3;   // Pin for the 'down' button
static const int PWR_LED_PIN    = 4;   // Pin for the 'green' led
static const int SP_LED_PIN     = 5;   // Pin for the 'red' led
static const int PID_OUTPUT_PIN = 6;   // Output pin from PID
static const int THERM_DO       = 8;   // Data out from the MAX6675 module
static const int THERM_CS       = 9;   // Chip select from same
static const int THERM_CLK      = 10;  // Clock from same
static const int START_SP       = 70;  // initial starting set point



#endif FORGE_TYPES_H

