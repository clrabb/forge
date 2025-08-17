#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <PID_v1.h>


/* -------------- TYPEDEFS ----------- */
typedef double                temp_t;               // This section creates the typedefs used in the program.
typedef Adafruit_LEDBackpack  ada_led_display;      // A typedef is used as a shorthand or to give more context to a
typedef Adafruit_7segment     ada_seven_seg;        // base type.  For example you could type 'double' instead of 'temp_t'
typedef Adafruit_24bargraph   ada_led_bar;          // but the temp_t label makes the code more readable.
typedef Adafruit_GFX          gfx;                  // Or you could use shorthand; ada_led_display instead of Adafruit_LEDBackpack
typedef PID                   pid_v1;
typedef unsigned short        setpoint_t;

/* --------------- GENERAL CONSTANTS -----------*/
static const int MAX6675_INIT_STABALIZE_WAIT = 2000;    // pause at the start of the program used to let the hardware that reads
                                                        // the thermocouple to 'settle'
static const int BAUD_RATE                   = 9600;    // Baud rate to use when connecting to the serial port
static const int INIT_BOOT_STABALIZE_WAIT    = 5000;    // The arduino seems to reset itself if you start work immediately after boot
                                                        // Five seconds seems to stop this

/* --------------- PINS ----------------------*/
static const int     BTN_UP_PIN         = 2;    // Pin for the 'up' button
static const int     BTN_DN_PIN         = 3;    // Pin for the 'down' button
static const int     PWR_LED_PIN        = 4;    // Pin for the Power led
static const int     HEARTBEAT_LED_PIN  = 5;    // Pin for the Heartbeat LED
static const int     THERM_DO           = 6;    // Data out from the MAX6675 module
static const int     THERM_CS           = 7;    // Chip select from same
static const int     THERM_CLK          = 8;    // Clock from same
static const int     FAN_PIN            = 9;    // Fan PWM pins

/*----------------- FAN CONSTANT ----------*/
static const int FAN_INIT_PERCENT_OPEN  = 0;
static const int FAN_RANGE_MIN          = 0;
static const int FAN_RANGE_MAX          = 255;


/* ----------------- SERVO CONSTANTS ----------*/
static const int     SERVO_DEBOUNCE_INTERVAL    = 0;    // Depricated - though still in the code.  Leave as 0
static const int     SERVO_MILLS_BETWEEN_TICKS  = 0;    // Depricated - how far to move on each tick
static const uint8_t SERVO_MOVE_STEP_SIZE       = 1;    // Depricated - step size in degrees 
static const int     SERVO_PIN                  = 9;
static const int     SERVO_MIN                  = 11;   // The servo being used is relatively cheap and does not
static const int     SERVO_MAX                  = 175;  // have a full 180 degrees of motion.  These are the limits
                                                        // found by empiracle observations.  If you try to move the
                                                        // servo beyond these points it will hit a wall and keep trying
                                                        // to move (but never getting there)


/* ----------------- SETPOINT CONSTANTS --------*/
static const int SP_START = 100;                           // Beginning setpoint

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
static const double        PID_RANGE_MIN     = FAN_RANGE_MIN;   // Used to map the current temp to the bar display
static const double        PID_RANGE_MAX     = FAN_RANGE_MAX;   // Same
static const unsigned long PID_SAMPLE_TIME   = 500;             // Time between each PID refresh (sample rate)
static const int           PID_GAP_THRESHOLD = 10;              // Difference in fahrenheit between current read temp and when
static const int           PID_THERMO_OFFSET = 0;               // to switch from a conservative to an 'aggressive' tuning.
                                                                // We are not limited to two states.  This can be expanded if needed
                                                                // Adding offset to calibrate probe
                                                                
/* These were so big it basically made a thermostat rather than a pid
 *  
static const double        PID_AGG_KP        = 800;               // These constants are the PID tunables.  There are currently two tunnable settings, 
static const double        PID_AGG_KI        = 0;                 // one for agressive tuning and one for conservative tuning (PID_AGG_.. AND PID_CON_...
static const double        PID_AGG_KD        = 0;                 // For more information on this see 
static const double        PID_CON_KP        = 200;               // http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/ 
static const double        PID_CON_KI        = 20;                // for more information
static const double        PID_CON_KD        = 0;
**/


/*
 *  These values taken from https://forum.arduino.cc/t/pid-library/333329/4
 */
static const double        PID_AGG_KP        = 2;                 // These constants are the PID tunables.  There are currently two tunnable settings, 
static const double        PID_AGG_KI        = 0.2;               // one for agressive tuning and one for conservative tuning (PID_AGG_.. AND PID_CON_...
static const double        PID_AGG_KD        = 1;                 // For more information on this see 
static const double        PID_CON_KP        = .5;                 // http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/ 
static const double        PID_CON_KI        = 0.05;              // for more information
static const double        PID_CON_KD        = 0.25;



/* ----------------- LED REFRESH TIMES --------- */
static const unsigned long DEFAULT_DISP_REFRESH_TIME  = 500;
static const unsigned long SP_DISP_REFRESH_TIME       = 50;     
static const unsigned long TEMP_DISP_REFRESH_TIME     = 3000;
static const unsigned long VALVE_DISP_REFRESH_TIME    = 500;

/* ---------------- BUTTON CONSTANTS ---------- */
static const int BTN_LATCHED_MILLS   = 700;     // How long you need to hold the button down before it speeds up
static const int BTN_UPDATE_SP_DELAY = 20;      // Time beteween setpoint updates in fast mode (speed of the 'fast' mode)
static const int MAX_SETPOINT        = 1800;    // The highest temp the buttons will let you go
static const int MIN_SETPOINT        = 0;       // The lowest temp the buttons will let you go

#endif FORGE_TYPES_H
   
