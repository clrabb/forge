#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

// Don't comment this line out unless
// you want to just spam the snot out of the 
// serial out.  It will also inflate the size of the code space
// to something like the twinky in ghostbusters
//
#define DISABLE_LOGGING
//#define __T_DEBUG__


#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <PID_v1.h>

typedef double                temp_t;
typedef Adafruit_LEDBackpack  ada_led_display;
typedef Adafruit_7segment     ada_seven_seg;
typedef Adafruit_24bargraph   ada_led_bar;
typedef Adafruit_GFX          gfx;
typedef PID                   pid_v1;
typedef unsigned short        setpoint_t;

static const uint8_t NUM_LEDS_IN_BAR     = 24;   // Number of LEDs in the bar display
static const double  PWM_OUTPUT_MIN      = 0;    // 0% duty cycle
static const double  PWM_OUTPUT_MAX      = 255;  // 100% duty cycle
static const int     UP_BTN_PIN          = 2;    // Pin for the 'up' button
static const int     DN_BTN_PIN          = 3;    // Pin for the 'down' button
static const int     PID_OUTPUT_PIN      = 6;    // Output pin from PID
static const int     THERM_DO            = 8;    // Data out from the MAX6675 module
static const int     THERM_CS            = 9;    // Chip select from same
static const int     THERM_CLK           = 10;   // Clock from same
static const int     START_SP            = 50;   // initial starting set point
static const int     PWR_LED_PIN         = 4;    // Pin for the 'green' led
static const int     STATUS_LED_PIN      = 5;    // Pin for the 'red' led

/* ------------------ LED CONSTANTS ------------ */
static const int        SP_DISP_ADDR              = 0x70; // ID of the 'blue' setpoint led display
static const int        SP_DISP_BRIGHTNESS        = 3;    // between 0 and 15
static const int        TEMP_DISP_ADDR            = 0X73; // ID of the 'red' temperature led display
static const int        TEMP_DISP_BRIGHTNESS      = 3;    // between 0 and 15
static const int        VALVE_DISP_ADDR           = 0X72; // ID of the LED bar
static const int        VALVE_DISP_BRIGHTNESS     = 3;    // between 0 and 15

/* ----------------- LED REFRESH TIMES --------- */
static const unsigned long DEFAULT_DISP_REFRESH_TIME  = 500;
static const unsigned long SP_DISP_REFRESH_TIME       = 50;     
static const unsigned long TEMP_DISP_REFRESH_TIME     = 3000;
static const unsigned long VALVE_DISP_REFRESH_TIME    = 500;


#endif FORGE_TYPES_H

