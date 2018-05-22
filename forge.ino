
#include "thermoc.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "error.h"
#include <arduino.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
//#include <PinChangeInt.h>

#define __DEBUG__


// Constants
//
static const int UP_BTN_PIN = 2;
static const int DN_BTN_PIN = 3;
static const int THERM_DO   = 8;
static const int THERM_CS   = 9;
static const int THERM_CLK  = 10;

static const long BAUD_RATE = 115200;

// Globals :[
//
Adafruit_7segment matrix = Adafruit_7segment();
int g_last_set_point              = 0;
volatile int up_button_state      = 0;
volatile int down_button_state    = 0;
volatile int g_set_point          = 0;

void init_singletons()
{
    singleton_t<thermoc> s_tc( new thermoc(THERM_DO, THERM_CS, THERM_CLK) );
    singleton_t<forge_data> s_fdata( new forge_data() );
    singleton_t<error> s_error( new error() );

    return;
}

// Sets up LED and prints test pattern
//
void init_led()
{
    matrix.begin(0x70);

    matrix.print(8, DEC);
    matrix.writeDisplay();
    delay(100);

    matrix.print(88, DEC);
    matrix.writeDisplay();
    delay(100);

    matrix.print(888, DEC);
    matrix.writeDisplay();
    delay(100);

    matrix.print(8888, DEC);
    matrix.writeDisplay();
    delay(1000);

    return;
}


// There is some concern here regarding global vs non-global
// variables.  In general I stay away from globals like the plague.
// The arduino has a very limited memory size, though, and allocating
// and deallocating heap objects will fragment what little is there.
// Placing them on the stack is probably ok but even those frames will chew
// up memory.  I still don't know which practices are good or bad, here.
// For those reasons, and because the setup/loop style really forces the
// use of some globals, I am going to use singletons which are
// effectively globals in any case.
// -- CR 5/14/2018
//
void setup() 
{
    Serial.begin(BAUD_RATE);

    // Set up pin usage
    //
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(UP_BTN_PIN, INPUT  );
    pinMode(DN_BTN_PIN, INPUT  );

    // Set up interrupts for buttons
    //
    attachInterrupt(0, upButton_ISR, CHANGE);
    attachInterrupt(1, dnButton_ISR, CHANGE);
    
    // Initialize the various singletons
    //
    init_singletons();

    // Set up display
    //
    init_led();

    // wait for MAX chip to stabilize
    //
    delay(500);

    return;
}

void loop() 
{
    thermoc& tc      = singleton_t<thermoc>::instance();
    forge_data& fd   = singleton_t<forge_data>::instance();
    error& es = singleton_t<error>::instance();


   
#ifdef __DEBUG__
    Serial.print( "F = " );
    Serial.println( tc.read_f() );
    Serial.println( "set point: " );
    Serial.println( g_set_point );
#endif

    if ( g_last_set_point != g_set_point )
    {
        digitalWrite( LED_BUILTIN, HIGH );
        matrix.println( g_set_point );
        matrix.writeDisplay();
        g_last_set_point = g_set_point;
        delay( 1000 );
    }

    digitalWrite( LED_BUILTIN, LOW );
    matrix.println( round( tc.read_f() ) );
    matrix.writeDisplay(); 

    delay( 1000 );

    return;
}

// Interrupt routines
//
void upButton_ISR()
{
    // up_button_state is a global
    //
    up_button_state = digitalRead(UP_BTN_PIN);
    if ( up_button_state == 1 )
    {
        ++g_set_point;
    }

    
    /*
    forge_data& fd = singleton_t<forge_data>::instance();
    fd.setpoint( fd.setpoint() + 1 );
    */
}

void dnButton_ISR()
{
    // up_button_state is a global
    //
    down_button_state = digitalRead(DN_BTN_PIN);
    if ( down_button_state == 1 )
    {
        --g_set_point;
    }

    /*
    forge_data& fd = singleton_t<forge_data>::instance();
    fd.setpoint( fd.setpoint() + 1 );
    */
}

