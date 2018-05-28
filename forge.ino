
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
static const int UP_BTN_PIN  = 2;   // Pin for the 'up' button
static const int DN_BTN_PIN  = 3;   // Pin for the 'down' button
static const int OK_LED_PIN  = 4;   // Pin for the 'green' led
static const int SP_LED_PIN  = 5;   // Pin for the 'red' led
static const int THERM_DO    = 8;   // Data out from the MAX6675 module
static const int THERM_CS    = 9;   // Chip select from same
static const int THERM_CLK   = 10;  // Clock from same
static const int START_SP    = 70;  // initial starting set point
static const int BLINK_OFF_T = 700; // ms for blinking off
static const int BLINK_ON_T  = 700; // ms for blinking on
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
    up_button_state = digitalRead( UP_BTN_PIN );
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
    down_button_state = digitalRead( DN_BTN_PIN );
    if ( down_button_state == 1 && fd.setpoint() > 0 )
    {
        fd.setpoint( fd.setpoint() - 1 );
    }
    fd.last_sp_changed_mills( millis() );

    return;
}

void init_singletons()
{
    singleton_t<thermoc> s_tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
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
    attachInterrupt( 0, upButton_ISR, RISING );
    attachInterrupt( 1, dnButton_ISR, RISING );

    return;
}

// Sets up LED and prints test pattern
//
void init_led_matrix()
{
    static const int TEST_NUMBER_DELAY = 100;
    static const int TEST_END_DELAY    = 1000;
    matrix.begin( 0x70 );

    matrix.print( 8, DEC );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.print( 88, DEC );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.print( 888, DEC );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.print(8888, DEC);
    matrix.writeDisplay();
    delay( TEST_END_DELAY );

    return;
}

void setup() 
{
    static const int MAX6675_INIT_STABALIZE_WAIT = 500;

#ifdef __DEBUG__
    Serial.begin( BAUD_RATE );
#endif // __DEBUG__

    // All the various initializing needed
    //  
    init_pins();
    init_interrupts();
    init_singletons();
    init_led_matrix();

    // wait for MAX chip to stabilize
    //
    delay( MAX6675_INIT_STABALIZE_WAIT );

    // Everything seems good.  Turnon the power light
    //
    digitalWrite( OK_LED_PIN, HIGH );
    
    return;
}

void display_sp_if_changing()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    int current_setpoint = fd.setpoint();
    if ( g_last_set_point != fd.setpoint() )
    {
        matrix.print( current_setpoint, DEC );
        matrix.writeDisplay();
        digitalWrite( SP_LED_PIN, HIGH );
        g_last_set_point = current_setpoint;
        delay( 500 );
    }

    matrix.print( fd.current_temp(), DEC );
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

    // Calculate percent difference of the set point temp
    // and the read temp
    //
    forge_data& fd = singleton_t< forge_data >::instance();
    int   abs_diff     = abs( fd.setpoint() - fd.current_temp() );
    float avg          = ( fd.setpoint() + fd.current_temp() ) / 2;
    float percent_diff = ( abs_diff / avg ) * 100;
    
    if ( percent_diff > DISPLAY_SP_OFF_TOLERANCE )
    {
        digitalWrite( SP_LED_PIN, HIGH );       
        matrix.print( fd.setpoint(), DEC );
        matrix.writeDisplay();
        delay( BLINK_ON_T );
        digitalWrite( SP_LED_PIN, LOW );
    }

    matrix.print( fd.current_temp(), DEC );
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
        matrix.print( fd.current_temp(), DEC );
        matrix.writeDisplay();

        delay( BLINK_ON_T );

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



