#include "disp.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "thermoc.h"
#include "forge_pid.h"
#include <ArduinoLog.h>
#include <arduino.h>



// Construction
disp::disp() :
    m_temp_display( ada_seven_seg() ),
    m_setpoint_display( ada_seven_seg() ),
    m_output_bar( ada_led_bar() )
{
}

// Initializing
//

void 
disp::init_setpoint_led()
{
    ada_seven_seg& sp_display = this->setpoint_display();
    sp_display.begin( BLUE_LED_ADDR );
    sp_display.setBrightness( BLUE_LED_BRIGHTNESS );

    return;
}

void
disp::init_temp_led()
{
    ada_seven_seg& temp_display = this->temp_display();
    temp_display.begin( RED_LED_ADDR );
    temp_display.setBrightness( RED_LED_BRIGHTNESS );

    return;
}

void
disp::init()
{
    this->init_displays();

    return;
}

void
disp::init_displays()
{
    this->init_led_bar();
    this->init_temp_led();
    this->init_setpoint_led();

    return;
}


// Accessing
//
unsigned long 
disp::mills_since_last_temp_display()
{
    unsigned long now = millis();

    return now - this->last_temp_display_mills();
}


double 
disp::seconds_since_last_temp_display()
{
    unsigned long retval = this->mills_since_last_temp_display() / 1000;
    return retval;
}

unsigned long 
disp::mills_since_last_setpoint_display()
{
    unsigned long now = millis();
    return now - this->last_setpoint_display_mills();
}

double 
disp::seconds_since_last_setpoint_display()
{
    return this->mills_since_last_setpoint_display() / 1000;
}

bool
disp::is_too_soon_display( unsigned long last_mills_display )
{
    Log.notice( "In disp::is_too_soon_display() with value: %d" CR, last_mills_display );

    unsigned long now = millis();
    bool retval = !( ( now - last_mills_display ) > DISPLAY_DEBOUNCE_MILLS );

    Log.notice( "Leaving disp::is_too_soon_display() with retval %T" CR, retval );
    return retval;
}

bool
disp::is_same_temp_as_last_display()
{
    forge_data& fd = singleton_t<forge_data>::instance();

    int last_temp_displayed = round( this->last_temp_seen() );
    int current_temp        = round( fd.current_temp() );
    
    bool is_same_temp = ( last_temp_displayed == current_temp );

    return is_same_temp;
}

bool
disp::is_same_pid_output_as_last_display()
{
    forge_data& fd = singleton_t< forge_data >::instance();

    double current_pid_output = fd.current_pid_output();
      
    if ( 0 == current_pid_output )
        return false;  // If it's zero nothing has been set yet.  We do want to update
    
    short last_pid_output_display  = round( this->last_pid_output_seen() );
    short rnded_current_pid_output = round( current_pid_output           );

    return last_pid_output_display == rnded_current_pid_output;
}

// Main calling point from loop()
//
void
disp::display()
{
   this->display_temp();
   this->display_setpoint();
   this->display_pid_output();
   
   return;
}

void
disp::display_pid_output()
{   
    Log.notice( "In disp::display_pid_output()" CR );
    
    // Debounce
    //
    if ( this->is_same_pid_output_as_last_display() )
    {
        Log.notice( "Same pid as last time, bailing" CR );
        return;
    }
    
    if ( this->is_too_soon_display( this->last_pid_output_display_mills() ) )
    {
        Log.notice( "Too soon to display pid, bailing" CR );
        return;
    }

    forge_data& fd = singleton_t< forge_data >::instance();
    ada_led_bar& bar   = this->led_output_bar();

    double pid_output = fd.current_pid_output();
    short rnded_output = round( pid_output / NUM_BAR_LEDS );
    
    Log.notice( "current_pid_output is %d" CR, round( pid_output ) );
    Log.notice( "Rounded_output to pid_led is %d" CR, rnded_output );

    for ( int i = 0; i < rnded_output; ++i )
    {
        Log.notice( "Setting led_bar segment %d to GREEN" CR, i );
        bar.setBar( i, LED_GREEN );
    }

    bar.writeDisplay();

    this->last_pid_output_display_mills( millis() );

    Log.notice( "Leaving disp::display_pid_output()" CR );
    return;
}

void
disp::display_setpoint()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    ada_seven_seg& seg = singleton_t< ada_seven_seg >::instance();

    int last_setpoint_seen = round( this->last_setpoint_seen() );
    int current_setpoint   = round( fd.setpoint() );

    if ( last_setpoint_seen == current_setpoint )
    {
        Log.notice( "No need to update the screen with the same setpoint.  bailing" CR );
    }
    else
    {
        Log.notice( "Setpoint different than last displayed.  Updating LED" CR );
        int tens = 0;
        int ones = 0;
    
        break_number( fd.setpoint(), tens, ones );
    
        seg.writeDigitNum( 3, tens );
        seg.writeDigitNum( 4, ones );
        seg.writeDisplay();
    
        this->last_setpoint_seen( fd.setpoint() );
    }

    return;
}



void 
disp::display_temp()
{
    // Main debouncing routine
    //
    bool too_soon   = this->is_too_soon_display( this->last_temp_display_mills() );
    bool same_temp  = this->is_same_temp_as_last_display();
  
    if ( too_soon || same_temp  )
    {
        Log.notice( "Nothing to do.  too_soon: %T; same_temp: %T" CR,
            too_soon,
            same_temp
        );
    }
    else
    {
        forge_data& fd = singleton_t< forge_data >::instance();
        temp_t current_temp = fd.current_temp();
        
#ifdef __DEBUG__
        Serial.print( "Changing display temp from " );
        Serial.print( round( this->last_temp_seen() ) );
        Serial.print( " to " );
        Serial.println( round( current_temp ) );
#endif // __DEBUG__      
     
        this->display_temp_impl( current_temp );
        this->last_temp_seen( current_temp );
        this->last_temp_display_mills( millis() );
    }  

    return;
}


void
disp::display_temp_impl( temp_t temp )
{ 
    ada_seven_seg& seg = singleton_t< ada_seven_seg >::instance();

    // Hack
    // This is temprary until the second display shows up
    //

    // get tens digit
    // Yeah, ugly.  This is temporary
    //
    int rounded_temp = round( temp );
    int tens = 0;
    int ones = 0;    
    this->break_number( rounded_temp, tens, ones );

    // Display tens
    seg.writeDigitNum( 0, tens );

    // display one
    // 
    seg.writeDigitNum( 1, ones );

    seg.writeDisplay();

    return;
}

// Break two digit number into ones and test
//
void 
disp::break_number( int num, int& tens, int& ones )
{
    // Returns the tens digit of a positive number.
    // 
    tens = ( num / 10 ) % 10;
    ones = num - ( tens * 10 );
    
    return;
}




