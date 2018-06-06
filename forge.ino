
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
    Log.notice( "In init_singletons()" CR );
    
    singleton_t<thermoc>    s_tc( new thermoc( THERM_DO, THERM_CS, THERM_CLK ) );
    singleton_t<forge_data> s_fdata( new forge_data() );
    singleton_t<seven_seg>  s_matrix( new seven_seg() );
    singleton_t<led_bar>        s_bar( new led_bar() );
    
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
void init_led_bar()
{
    Log.notice( "In init_led_bar()" CR );
    
    static const int BAR_LED_ADDR      = 0x72;
    led_bar& b = singleton_t< led_bar >::instance();

    b.begin(0x72);  // pass in the address
    b.setBrightness( LED_BAR_BRIGHTNESS );

    for (uint8_t i = 0; i < 24; ++i )
    {
        if ((i % 3) == 0)  b.setBar(i, LED_RED);
        if ((i % 3) == 1)  b.setBar(i, LED_YELLOW);
        if ((i % 3) == 2)  b.setBar(i, LED_GREEN);
    }    
    
    b.writeDisplay();
    delay(2000);

    for ( uint8_t i = 0; i < 24; ++i ) 
    {
        b.setBar( i, LED_RED );
        b.writeDisplay();
        delay( 50 );
        b.setBar( i, LED_OFF );
        b.writeDisplay();
    }
    
    for ( uint8_t i = 0; i < 24; ++i ) 
    {
        b.setBar( i, LED_GREEN );
        b.writeDisplay();
        delay( 50 );
        b.setBar( i, LED_OFF );
        b.writeDisplay();
    }

    for ( uint8_t i = 0; i < 24; ++i ) 
    {
        b.setBar( i, LED_YELLOW );
        b.writeDisplay();
        delay( 50 );
        b.setBar( i, LED_OFF );
        b.writeDisplay();
    }

    delay( 1000 );

    Log.notice( "Leaving init_led_bar()" CR );
    return;
}

// Sets up LED and prints test pattern
//
void init_led_matrix()
{   
    Log.notice( "In init_led_matrix()" CR );
    
    static const int TEST_NUMBER_DELAY = 100;
    static const int TEST_END_DELAY    = 1000;
    static const int BLUE_LED_ADDR     = 0x70;
    static const int RED_LED_ADDR      = 0X71;


    seven_seg& matrix = singleton_t< seven_seg >::instance();
    
    matrix.begin( 0x70 );
    matrix.setBrightness( BLUE_LED_BRIGHTNESS );

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

    Log.notice( "Leaving init_led_matrix()" CR );
    
    return;
}

void setup() 
{

    static const int MAX6675_INIT_STABALIZE_WAIT = 2000;
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
    init_led_bar();

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
    //fpid.initial_values( fd.current_temp(), fd.setpoint(), 10 /* ms */ );
    fpid.initial_values( fd.current_temp(), fd.setpoint() );

    delay( 1000 );
    
    fpid.start();

    // Everything seems good.  Turnon the power light
    //
    digitalWrite( PWR_LED_PIN, HIGH );

    Log.notice( "Leaving setup()" CR );
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
    Serial.print( "Temp: " );
    Serial.print( fd.current_temp() );
    Serial.print( ". Computed new output to regulator: " );
    Serial.println( output );
#endif // __DEBUG__

/*
    Serial.print( ". Setpoint was " );
    Serial.print( fd.setpoint() );
    Serial.print( " . Temp was " );
    Serial.println( fd.current_temp() );
#endif // __DEBUG __
*/

    analogWrite( PID_OUTPUT_PIN, output );

    Log.notice( "***************** LEAVING OUTPUT_PID() **************" CR );
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

#ifdef __T_DEBUG__
    Serial.println();
    Serial.println( "************ LOOP **************");
    Serial.print( "LOOP(); about to read temp.  Old temp was: " );
    Serial.println( fd.current_temp() );
#endif // __T_DEBUG__
    
    // update the current temp in the global data struct
    //
    temp_t nt = tc.read_f();
    fd.current_temp( nt );

#ifdef __T_DEBUG__
    Serial.print( "LOOP()::New temp read from thermocouple was: " );
    Serial.println( nt );
#endif // __T_DEBUG__
   

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



