
#include "thermoc.h"
#include "forge_types.h"
#include "singleton_t.h"
#include "forge_data.h"
#include "forge_pid.h"
#include "disp.h"
#include "heartbeat.h"
#include "forge_stepper.h"
#include "forge_servo.h"
#include <arduino.h>
#include <Wire.h>

// HACK
//
unsigned long last_btn_pressed_mills;
void deal_with_buttons()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    unsigned long btn_pressed_interval = ( millis() - last_btn_pressed_mills );

    if ( btn_pressed_interval < BTN_SLOW_CHANGE )
        return;

    if ( digitalRead( UP_BTN_PIN ) )
    {
        fd.increment_setpoint();
    }
    else if ( digitalRead( DN_BTN_PIN ) && fd.setpoint() > 0 )
    {
        fd.decrement_setpoint();
    }

    last_btn_pressed_mills = millis();
    return;
}

void output_pid()
{
    // Snag any needed globals
    //
    forge_data& fd   = singleton_t< forge_data >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();

    double output = fpid.compute( fd.current_temp(), fd.setpoint() );
    fd.current_pid_output( output );

    return;
}

void init_pins()
{   
    // Set up pin usage
    //
    pinMode( UP_BTN_PIN,     INPUT  );
    pinMode( DN_BTN_PIN,     INPUT  );
    pinMode( PWR_LED_PIN,    OUTPUT );

    return;
}

void init_singletons()
{
    singleton_t< thermoc >     tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t< forge_data >  fdata( new forge_data() );    
    singleton_t< disp >        d( new disp() );
    singleton_t< forge_pid >   fpid( new forge_pid() );
    singleton_t< forge_servo > servo( new forge_servo( SERVO_PIN ) );
    
    return;
}

void init_displays()
{
    disp& d = singleton_t< disp >::instance();
    d.init();

    return;
}

void init_pid()
{
    forge_pid&  fpid  = singleton_t< forge_pid >::instance();
    forge_data& fd    = singleton_t< forge_data >::instance();
    

    fpid.set_output_limits( PID_RANGE_MIN, PID_RANGE_MAX );
    fpid.initial_values( fd.current_temp(), fd.setpoint(), PID_SAMPLE_TIME ); // Milliseconds

    return;
}


void setup() 
{

    static const int MAX6675_INIT_STABALIZE_WAIT = 2000;
    static const int BAUD_RATE = 9600;

    Serial.begin( BAUD_RATE );

    // All the various initializing needed
    //  

    init_pins();
    init_singletons();
    last_btn_pressed_mills = 0; // HACK

    // wait for MAX chip to stabilize
    //
    delay( MAX6675_INIT_STABALIZE_WAIT );

    forge_data& fd   = singleton_t< forge_data >::instance();
    thermoc&    tc   = singleton_t< thermoc >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();
    disp&       d    = singleton_t< disp >::instance();
    
    fd.current_temp( tc.read_f() );

    // initialize pid
    // .. this is not with the other inits because the temperature
    // must have already been read to initialize the pid
    //
    init_pid();
    
    delay( 1000 );
    
    fpid.start();

    // Everything seems good.  Turn on the power light
    //
    digitalWrite( PWR_LED_PIN, HIGH );

    return;
}


void loop()
{
    thermoc& tc     = singleton_t< thermoc >::instance();
    forge_data& fd  = singleton_t< forge_data >::instance();
    disp& d         = singleton_t< disp >::instance();

    deal_with_buttons();
    fd.current_temp( tc.read_f() );
    output_pid();
    d.display();
    
    return;
}


