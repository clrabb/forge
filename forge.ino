
#include "thermoc.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "forge_pid.h"
#include "disp.h"
#include <arduino.h>
#include <Wire.h>
#include <math.h>
#include <ArduinoLog.h>

// Interrupt routines
//
void upButton_ISR()
{
    forge_data& fd     = singleton_t< forge_data >::instance();
    
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


void heartbeat( int times_through )
{
    if ( times_through % 10 == 0 )
    {
        digitalWrite( 5, HIGH );
        delay( 20 );
        digitalWrite( 5, LOW );
    }

    return;
}

void init_singletons()
{
    singleton_t< thermoc >    s_tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t< forge_data > s_fdata( new forge_data() );    
    singleton_t< disp >       s_display( new disp() );
    singleton_t< forge_pid >  fpid( new forge_pid() );

    disp& d = singleton_t< disp >::instance();
    d.init();

    return;
}

void init_pins()
{   
    // Set up pin usage
    //
    pinMode( UP_BTN_PIN,     INPUT  );
    pinMode( DN_BTN_PIN,     INPUT  );
    pinMode( PWR_LED_PIN,    OUTPUT );
    pinMode( STATUS_LED_PIN, OUTPUT );
;
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
    Log.begin( LOG_LEVEL_VERBOSE, &Serial );

    // All the various initializing needed
    //  

    init_pins();
    init_interrupts();
    init_singletons();

    // wait for MAX chip to stabilize
    //
    delay( MAX6675_INIT_STABALIZE_WAIT );

    forge_data& fd   = singleton_t< forge_data >::instance();
    thermoc&    tc   = singleton_t< thermoc    >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();
    disp&       d    = singleton_t< disp >::instance();
    
    fd.setpoint( START_SP );
    fd.current_temp( tc.read_f() );

    //initialize pid
    //
    //fpid.initial_values( fd.current_temp(), fd.setpoint(), 10 /* ms */ );
    fpid.initial_values( fd.current_temp(), fd.setpoint() );

    delay( 1000 );
    
    fpid.start();

    // Everything seems good.  Turnon the power light
    //
    digitalWrite( PWR_LED_PIN, HIGH );

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

    analogWrite( PID_OUTPUT_PIN, output );

    return;
}

int g_times_through;
void loop() 
{

    // Snag the various globals
    //
    forge_data& fd = singleton_t< forge_data >::instance();
    disp& displ    = singleton_t< disp >::instance();
    thermoc& tc    = singleton_t< thermoc >::instance();
    
    // update the current temp in the global data struct
    //
    temp_t nt = tc.read_f();
    fd.current_temp( nt );

    // Change pid output if needed
    //
    output_pid();
    
    // Display everything
    //
    displ.display();

    // Send a heartbeat to an external LED
    //
    heartbeat( g_times_through++ );
    
    return;
}



