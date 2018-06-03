
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
    Log.notice( "In init_singletons()" CR );
    
    singleton_t<thermoc> s_tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t<forge_data> s_fdata( new forge_data() );
    singleton_t<seven_seg> s_matrix( new seven_seg() );
    singleton_t<disp> s_display( new disp() );
    singleton_t<forge_pid> fpid( new forge_pid() );

    Log.notice( "Leaving init_singletons()" CR );
    return;
}

void init_pins()
{
    Log.notice( "In init_pins()" CR );
    
    // Set up pin usage
    //
    pinMode( UP_BTN_PIN,     INPUT  );
    pinMode( DN_BTN_PIN,     INPUT  );
    pinMode( PWR_LED_PIN,    OUTPUT );
    pinMode( STATUS_LED_PIN, OUTPUT );

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
    static const int TEST_NUMBER_DELAY = 100;
    static const int TEST_END_DELAY    = 1000;

    seven_seg& matrix = singleton_t< seven_seg >::instance();
    
    matrix.begin( 0x70 );

    matrix.print( 8, DEC );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.print( 88, DEC );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.drawColon( true );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.print( 888, DEC );
    matrix.drawColon( true );
    matrix.writeDisplay();
    delay( TEST_NUMBER_DELAY );

    matrix.print(8888, DEC);
    matrix.drawColon( true );
    matrix.writeDisplay();

    delay( TEST_END_DELAY );

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

    forge_data& fd   = singleton_t< forge_data >::instance();
    thermoc&    tc   = singleton_t< thermoc    >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();
    
    fd.setpoint( START_SP );
    fd.current_temp( tc.read_f() );

    //initialize pid
    //
    fpid.initial_values( fd.current_temp(), fd.setpoint() );
    fpid.start();

    // Everything seems good.  Turnon the power light
    //
    digitalWrite( PWR_LED_PIN, HIGH );

    Log.notice( "Leaving setup()" CR );
    return;
}


int g_times_through;
void loop() 
{
    Log.notice( "In loop()" CR );

    // Snag the various globals
    //
    forge_data& fd = singleton_t< forge_data >::instance();
    disp& displ    = singleton_t< disp >::instance();
    thermoc& tc    = singleton_t< thermoc >::instance();
    
    // update the current temp in the global data struct
    //
    fd.current_temp( tc.read_f() );

    // Change pid output if needed
    //
    output_pid();
    
    // /Run the display loop
    //
    displ.display();

#ifdef __DEBUG__
    // Send a heartbeat to an external LED
    //
    heartbeat( g_times_through++ );
#endif // __DEBUG__

    Log.notice( "Leaving loop()" CR );
    
    return;
}

void output_pid()
{
    Log.notice( "**************** IN OUTPUT_ID() **************" CR );
    // Snag any needed globals
    //
    forge_data& fd   = singleton_t< forge_data >::instance();
    forge_pid&  fpid = singleton_t< forge_pid >::instance();

    double output = fpid.compute( fd.current_temp(), fd.setpoint() );

#ifdef __DEBUG__
    // Fucking logging framework doesn't deal with floats
    //
    Serial.print( "Computed new output to regulator: " );
    Serial.print( output );
    Serial.print( ". Setpoint was " );
    Serial.print( fd.setpoint() );
    Serial.print( " . Temp was " );
    Serial.println( fd.current_temp() );
#endif // __DEBUG __

    analogWrite( PID_OUTPUT_PIN, output );

    Log.notice( "***************** LEAVING OUTPUT_PID() **************" CR );
    return;
}




