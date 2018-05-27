
#include "thermoc.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "error.h"
#include <arduino.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <math.h>

#define __DEBUG__


// Constants
//
static const int UP_BTN_PIN = 2;
static const int DN_BTN_PIN = 3;
static const int OK_LED_PIN = 4;
static const int SP_LED_PIN = 5;
static const int THERM_DO   = 8;
static const int THERM_CS   = 9;
static const int THERM_CLK  = 10;
static const int START_SP   = 70;
static const long BAUD_RATE = 115200;

// Globals :[
//
Adafruit_7segment matrix = Adafruit_7segment();
int           g_last_set_point               = 0;
volatile int  up_button_state                = 0;
volatile int  down_button_state              = 0;

// Interrupt routines
//
void upButton_ISR()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    
    // up_button_state is a global
    //
    up_button_state = digitalRead(UP_BTN_PIN);
    if ( up_button_state == 1 )
    {
        fd.setpoint( fd.setpoint() + 1 );
    }

    return;
}

void dnButton_ISR()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    // up_button_state is a global
    //
    down_button_state = digitalRead(DN_BTN_PIN);
    if ( down_button_state == 1 && fd.setpoint() > 0 )
    {
        fd.setpoint( fd.setpoint() - 1 );
    }
    fd.last_sp_changed_mills( millis() );

    return;
}

void init_singletons()
{
    singleton_t<thermoc> s_tc( new thermoc(THERM_DO, THERM_CS, THERM_CLK) );
    singleton_t<forge_data> s_fdata( new forge_data() );
    singleton_t<error> s_error( new error() );

    forge_data& fd = singleton_t< forge_data >::instance();
    fd.last_sp_changed_mills( millis() ); // millis() returns milliseconds since startup
    fd.setpoint( START_SP );

    return;
}

void init_pins()
{
    // Set up pin usage
    //
    pinMode( UP_BTN_PIN, INPUT   );
    pinMode( DN_BTN_PIN, INPUT   );
    pinMode( OK_LED_PIN, OUTPUT  );
    pinMode( SP_LED_PIN, OUTPUT  );

    return;
}

void init_interrupts()
{
    // Set up interrupts for buttons
    //
    attachInterrupt(0, upButton_ISR, RISING);
    attachInterrupt(1, dnButton_ISR, RISING);

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

    init_pins();
    init_interrupts();
    init_singletons();
    init_led();

    digitalWrite( OK_LED_PIN, HIGH );

    // wait for MAX chip to stabilize
    //
    delay(500);

    return;
}

void display_sp_if_changing()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    int current_setpoint = fd.setpoint();
    if ( g_last_set_point != fd.setpoint() )
    {
        matrix.println( current_setpoint );
        matrix.writeDisplay();
        digitalWrite( SP_LED_PIN, HIGH );
        g_last_set_point = current_setpoint;
        delay( 500 );
    }

    matrix.println( fd.current_temp() );
    matrix.writeDisplay();
    digitalWrite( SP_LED_PIN, LOW );
    return;
}

void flash_setpoint_if_off()
{
     // If the current temp and the setpoint are off by this percent 
    // flash the setpoint
    //
    static const int DISPLAY_SP_OFF_TOLERANCE = 5; 

    forge_data& fd = singleton_t< forge_data >::instance();
    int   abs_diff     = abs( fd.setpoint() - fd.current_temp() );
    float avg          = ( fd.setpoint() + fd.current_temp() ) / 2;
    float percent_diff = ( abs_diff / avg ) * 100;
    
    if ( percent_diff > DISPLAY_SP_OFF_TOLERANCE )
    {
        digitalWrite( SP_LED_PIN, HIGH );
        matrix.println( fd.setpoint() );
        matrix.writeDisplay();
        delay( 500 );
        digitalWrite( SP_LED_PIN, LOW );
    }

    matrix.println( fd.current_temp() );
    matrix.writeDisplay();
    return;
}

void display_current_temp()
{
    // If the setpoint has not changed recently display the current temp
    //
    static const unsigned long MAX_MILLS_BETWEEN_SP_DISPLAY = 500;
    static const unsigned long MIN_MILLS_BETWEEN_DISPLAY    = 2000;    

    thermoc&    tc = singleton_t< thermoc >::instance();
    forge_data& fd = singleton_t< forge_data >::instance();

    // Bail if the last time we updated the display was too recent
    //
    if ( millis() - fd.last_temp_changed_mills() < MIN_MILLS_BETWEEN_DISPLAY )
        return;

    // Only show the current temp if Joe is done playing with the setpoint
    //
    if ( millis() - fd.last_sp_changed_mills() > MAX_MILLS_BETWEEN_SP_DISPLAY )
    {
        matrix.println( fd.current_temp() );
        matrix.writeDisplay();

        delay( 500 );

        flash_setpoint_if_off();
    }

    return;
}

void loop() 
{
    thermoc& tc      = singleton_t<thermoc>::instance();
    forge_data& fd   = singleton_t<forge_data>::instance();

    fd.current_temp( tc.read_f() );
    
    display_sp_if_changing();
    display_current_temp();

    delay( 50 );

    return;
}



