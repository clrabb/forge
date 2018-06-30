
#include "thermoc.h"
#include "forge_types.h"
#include "singleton_t.h"
#include "forge_data.h"
#include "forge_pid.h"
#include "disp.h"
#include "heartbeat.h"
#include "forge_stepper.h"
#include <arduino.h>
#include <Wire.h>

// Interrupt routines
//
void upButton_ISR()
{
    forge_data& fd     = singleton_t< forge_data >::instance();
    
    volatile int up_button_state = digitalRead( UP_BTN_PIN );
    if ( 1 == up_button_state )
    {
        fd.increment_setpoint();
    }

    return;
}

void dnButton_ISR()
{
    forge_data& fd = singleton_t< forge_data >::instance();

    volatile int down_button_state = digitalRead( DN_BTN_PIN );
    if ( 1 == down_button_state  && fd.setpoint() > 0 )
    {
        fd.decrement_setpoint();
    }

    return;
}

forge_stepper stepper; // HACK
void output_pid()
{
    // Snag any needed globals
    //
    forge_data& fd   = singleton_t< forge_data >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();

    double output = fpid.compute( fd.current_temp(), fd.setpoint() );
    fd.current_pid_output( output );

    stepper.step_to( output );

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
    singleton_t< thermoc >    tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t< forge_data > fdata( new forge_data() );    
    singleton_t< disp >       d( new disp() );
    singleton_t< forge_pid >  fpid( new forge_pid() );
    
    singleton_t< disp >::instance().init();

    return;
}

void init_displays()
{
    disp& d = singleton_t< disp >::instance();
    d.init();

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
    init_interrupts();
    init_singletons();

    // wait for MAX chip to stabilize
    //
    delay( MAX6675_INIT_STABALIZE_WAIT );

    forge_data& fd   = singleton_t< forge_data >::instance();
    thermoc&    tc   = singleton_t< thermoc >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();
    disp&       d    = singleton_t< disp >::instance();
    
    fd.setpoint( START_SP );
    fd.current_temp( tc.read_f() );

    //initialize pid
    //
    fpid.initial_values( fd.current_temp(), fd.setpoint(), 10 ); // ten ms 
    fpid.initial_values( fd.current_temp(), fd.setpoint() );

    delay( 1000 );
    
    fpid.start();

    // Everything seems good.  Turn on the power light
    //
    digitalWrite( PWR_LED_PIN, HIGH );

    return;
}


void init_pid()
{
    forge_pid&  p  = singleton_t< forge_pid >::instance();
    forge_data& fd = singleton_t< forge_data >::instance();

    p.initial_values( fd.current_temp(), fd.setpoint(), 10 ); // ten ms 
    p.initial_values( fd.current_temp(), fd.setpoint() );
    p.start();

    return;
}

void loop()
{
    thermoc& tc     = singleton_t< thermoc >::instance();
    forge_data& fd  = singleton_t< forge_data >::instance();
    disp& d         = singleton_t< disp >::instance();

    fd.current_temp( tc.read_f() );

    output_pid();
    
    d.display();
    
    return;
}


