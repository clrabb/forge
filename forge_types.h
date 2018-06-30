#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

// Don't comment this line out unless
// you want to just spam the snot out of the 
// serial out.  It will also inflate the size of the code space
// to something like the twinky in ghostbusters
//
#define DISABLE_LOGGING
//#define __T_DEBUG__
//#define __DEBUG__
//¨#define __DEBUG_PID__
#define __DEBUG_STEPPER__
#define __DEBUG_BAR__

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

/* --------------- PINS ----------------------*/
static const int     UP_BTN_PIN         = 2;    // Pin for the 'up' button
static const int     DN_BTN_PIN         = 3;    // Pin for the 'down' button
static const int     PWR_LED_PIN        = 4;    // Pin for the Power led
static const int     HEARTBEAT_LED_PIN  = 5;    // Pin for the Heartbeat LED
static const int     THERM_DO           = 6;    // Data out from the MAX6675 module
static const int     THERM_CS           = 7;    // Chip select from same
static const int     THERM_CLK          = 8;    // Clock from same
static const int     PID_OUTPUT_PIN     = 9;    // Output PWM from pid
static const int     FSTEPPER_PIN1      = 10;   // Obvious
static const int     FSTEPPER_PIN2      = 11;   // ...
static const int     FSTEPPER_PIN3      = 12;   // ...
static const int     FSTEPPER_PIN4      = 13;   // ...


/* ----------------- STEPPER CONSTANTS  ------- */
static const int     STEPS_PER_REVOLUTION = 4096;
static const int     STEPS_TO_CLOSED      = 0;
static const int     STEPS_TO_FULL_OPEN   = STEPS_PER_REVOLUTION * 2;
static const int     STEP_DEAD_MILLS      = 2000; // Stepper won't move in this many mills

static const double  PWM_OUTPUT_MIN  = 0;    // 0% duty cycle
static const double  PWM_OUTPUT_MAX  = 255;  // 100% duty cycle
static const int     START_SP        = 50;   // initial starting set point


/* ------------------ LED CONSTANTS ------------ */
static const int        SP_DISP_ADDR              = 0x70; // ID of the 'blue' setpoint led display
static const int        SP_DISP_BRIGHTNESS        = 3;    // between 0 and 15
static const int        TEMP_DISP_ADDR            = 0X73; // ID of the 'red' temperature led display
static const int        TEMP_DISP_BRIGHTNESS      = 3;    // between 0 and 15
static const int        VALVE_DISP_ADDR           = 0X72; // ID of the LED bar
static const int        VALVE_DISP_BRIGHTNESS     = 3;    // between 0 and 15
static unsigned long    HEARTBEAT_DURATION_ON     = 20;   // milliseconds on
static unsigned long    HEARTBEAT_DURATION_OFF    = 2000; // milliseconds off
static const uint8_t    NUM_LEDS_IN_BAR           = 24;   // Number of LEDs in the bar display

/* ----------------- LED REFRESH TIMES --------- */
static const unsigned long DEFAULT_DISP_REFRESH_TIME  = 500;
static const unsigned long SP_DISP_REFRESH_TIME       = 50;     
static const unsigned long TEMP_DISP_REFRESH_TIME     = 3000;
static const unsigned long VALVE_DISP_REFRESH_TIME    = 500;

/* ---------------- BUTTON CONSTANTS ---------- */
static const int BTN_SLOW_CHANGE = 100;


#endif FORGE_TYPES_H

