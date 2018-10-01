#include "thermoc.h"
#include "forge_types.h"
#include "singleton_t.h"
#include "forge_data.h"
#include "forge_pid.h"
#include "disp.h"
#include "heartbeat.h"
#include "forge_servo.h"
#include "up_button.h"
#include "down_button.h"
#include "button_array.h"
#include <arduino.h>
#include <Wire.h>

void deal_with_buttons()
{
    button_array& buttons = singleton_t< button_array >::instance();
    buttons.update_buttons();

    return;
}

void output_pid()
{
    // Snag any needed globals
    //
    forge_data&  fdata  = singleton_t< forge_data  >::instance();
    forge_pid&   fpid   = singleton_t< forge_pid   >::instance();
    forge_servo& fservo = singleton_t< forge_servo >::instance();

    uint8_t output = fpid.compute( fdata.current_temp(), fdata.setpoint() );

    uint8_t percent_open = fservo.target_percent_open();
    
    ( fservo.target_percent_open() != output )
        ? fservo.move_to( output )
        : fservo.tick()
        
    ;
        
    fdata.current_pid_output( output );

    return;
}

void init_servo()
{
    forge_servo& fservo = singleton_t< forge_servo >::instance();
    fservo.initialize_movement();

    return;
}

void init_pins()
{   
    // Set up pin usage
    //
    pinMode( BTN_UP_PIN,     INPUT  );
    pinMode( BTN_DN_PIN,     INPUT  );
    pinMode( PWR_LED_PIN,    OUTPUT );

    return;
}

void init_singletons()
{
    singleton_t< thermoc >      tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t< forge_data >   fdata( new forge_data() );    
    singleton_t< disp >         d( new disp() );
    singleton_t< forge_pid >    fpid( new forge_pid() );
    singleton_t< forge_servo >  servo( new forge_servo( SERVO_PIN ) );

    button_array* buttons = new button_array();
    buttons->up_button( new up_button( BTN_UP_PIN ) );
    buttons->dn_button( new down_button( BTN_DN_PIN ) );

    singleton_t< button_array > b( buttons );
    
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
    delay( INIT_BOOT_STABALIZE_WAIT );
    Serial.begin( BAUD_RATE );

    // All the various initializing needed
    //  
    init_pins();
    init_singletons();
    init_displays();
    init_servo();

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


