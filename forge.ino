
#include "thermoc.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "error.h"
#include "disp.h"
#include <arduino.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <math.h>
#include <ArduinoLog.h>

// Interrupt routines
//
void upButton_ISR()
{
    forge_data& fd     = singleton_t< forge_data >::instance();

    
    // up_button_state is a global
    //
    
    volatile int up_button_state = digitalRead( UP_BTN_PIN );
    if ( up_button_state == 1 )
    {
        fd.increment_setpoint();
    }

    return;
}

void dnButton_ISR()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    // up_button_state is a global
    //

    volatile int down_button_state = digitalRead( DN_BTN_PIN );
    if ( down_button_state == 1 && fd.setpoint() > 0 )
    {
        fd.decrement_setpoint();
    }

    return;
}

void init_singletons()
{
    Log.notice( "In init_singletons()" CR );
    
    singleton_t<thermoc> s_tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t<forge_data> s_fdata( new forge_data() );
    singleton_t<error> s_error( new error() );
    singleton_t<seven_seg> s_matrix( new seven_seg() );
    singleton_t<disp> s_display( new disp() );

    Log.notice( "Leaving init_singletons()" CR );
    return;
}

void init_pins()
{
    Log.notice( "In init_pins()" CR );
    // Set up pin usage
    //
    pinMode( UP_BTN_PIN,  INPUT   );
    pinMode( DN_BTN_PIN,  INPUT   );
    pinMode( PWR_LED_PIN, OUTPUT  );
    pinMode( SP_LED_PIN,  OUTPUT  );

    Log.notice( "Leaving init_pins()" CR );
    return;
}

void init_interrupts()
{
    Log.notice( "In init_interrupts()" CR );
    // Set up interrupts for buttons
    //
    attachInterrupt( 0, upButton_ISR, RISING );
    attachInterrupt( 1, dnButton_ISR, RISING );

    Log.notice( "Leaving init_interrupts()" CR );
    return;
}

// Sets up LED and prints test pattern
//
void init_led_matrix()
{
    Log.notice( "in init_led_matrix()" CR );
    
    static const int TEST_NUMBER_DELAY = 100;
    static const int TEST_END_DELAY    = 1000;

    Adafruit_7segment& matrix = singleton_t<Adafruit_7segment>::instance();
    
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

    Log.notice( "Leaving init_led_matrix()" CR );
    return;
}

void setup() 
{
    static const int MAX6675_INIT_STABALIZE_WAIT = 500;
    static const int BAUD_RATE = 9600;

    Serial.begin( BAUD_RATE );
    Log.begin( LOG_LEVEL_VERBOSE, &Serial );
    Log.notice( "In setup" CR );


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
    digitalWrite( PWR_LED_PIN, HIGH );

    Log.notice( "Leaving setup()" CR );
    return;
}


void loop() 
{
    Log.notice( "In loop()" CR );
   
    disp& displ = singleton_t<disp>::instance();
    displ.display();

    digitalWrite( SP_LED_PIN, LOW );
 
    Log.notice( "Leaving loop()" CR );
    return;
}




