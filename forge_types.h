#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

// Don't comment this line out unless
// you want to just spam the snot out of the 
// serial out.  It will also inflate the size of the code space
// to something like the twinky in ghostbusters
//
// #define __T_DEBUG__
//#define __DEBUG__
//¨#define __DEBUG_PID__
//#define __DEBUG_SERVO__
//#define __DEBUG_BAR__
//#define __DEBUG_TC__

#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <PID_v1.h>

/* -------------- TYPEDEFS ----------- */
typedef double                temp_t;
typedef Adafruit_LEDBackpack  ada_led_display;
typedef Adafruit_7segment     ada_seven_seg;
typedef Adafruit_24bargraph   ada_led_bar;
typedef Adafruit_GFX          gfx;
typedef PID                   pid_v1;
typedef unsigned short        setpoint_t;

/* --------------- GENERAL CONSTANTS -----------*/
static const int MAX6675_INIT_STABALIZE_WAIT = 2000;
static const int BAUD_RATE                   = 9600;
static const int INIT_BOOT_STABALIZE_WAIT    = 5000;

/* --------------- PINS ----------------------*/
static const int     BTN_UP_PIN         = 2;    // Pin for the 'up' button
static const int     BTN_DN_PIN         = 3;    // Pin for the 'down' button
static const int     PWR_LED_PIN        = 4;    // Pin for the Power led
static const int     HEARTBEAT_LED_PIN  = 5;    // Pin for the Heartbeat LED
static const int     THERM_DO           = 6;    // Data out from the MAX6675 module
static const int     THERM_CS           = 7;    // Chip select from same
static const int     THERM_CLK          = 8;    // Clock from same

/* ----------------- SERVO CONSTANCES ----------*/
static const int     SERVO_DEAD_MILLS     = 500;
static const int     SERVO_PIN            = 9;
static const int     SERVO_MIN            = 11;
static const int     SERVO_MAX            = 175;

/* ----------------- SETPOINT CONSTANTS --------*/
static const int SP_START = 50;                           // Beginning setpoint

/* ------------------ LED CONSTANTS ------------ */
static const int        SP_DISP_ADDR              = 0x70; // ID of the 'blue' setpoint led display
static const int        SP_DISP_BRIGHTNESS        = 3;    // between 0 and 15
static const int        TEMP_DISP_ADDR            = 0X73; // ID of the 'red' temperature led display
static const int        TEMP_DISP_BRIGHTNESS      = 3;    // between 0 and 15
static const int        VALVE_DISP_ADDR           = 0X72; // ID of the LED bar
static const int        VALVE_DISP_BRIGHTNESS     = 3;    // between 0 and 1s
static unsigned long    HEARTBEAT_DURATION_ON     = 100;  // milliseconds on
static unsigned long    HEARTBEAT_DURATION_OFF    = 1000; // milliseconds off
static const uint8_t    NUM_LEDS_IN_BAR           = 24;   // Number of LEDs in the bar display
static const short      BAR_ANIMATION_DELAY       = 0;    // Amount of time between each LED in the bar being lit up.  Gives an animation effect

/* ----------------- PID CONSTANTS -------------*/
static const double        PID_RANGE_MIN   = SERVO_MIN;
static const double        PID_RANGE_MAX   = SERVO_MAX;
static const unsigned long PID_SAMPLE_TIME = 200; // Milliseconds

/* ----------------- LED REFRESH TIMES --------- */
static const unsigned long DEFAULT_DISP_REFRESH_TIME  = 500;
static const unsigned long SP_DISP_REFRESH_TIME       = 50;     
static const unsigned long TEMP_DISP_REFRESH_TIME     = 3000;
static const unsigned long VALVE_DISP_REFRESH_TIME    = 500;

/* ---------------- BUTTON CONSTANTS ---------- */
static const int BTN_LATCHED_MILLS = 700;
static const int BTN_UPDATE_SP_DELAY = 5; // Time beteween setpoint updates in fast mode.
static const int MAX_SETPOINT = 9999;
static const int MIN_SETPOINT = 0;

#endif FORGE_TYPES_H

