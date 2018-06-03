#include "disp.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "thermoc.h"
#include <ArduinoLog.h>
#include <arduino.h>

// Accessing
//
unsigned long 
disp::mills_since_last_temp_display()
{
    Log.notice( "In disp::mills_since_last_temp_display()" CR );
    
    unsigned long now = millis();

    Log.notice( "Leaving disp::mills_since_last_temp_display() with retval %l" CR, now );
    return now - this->m_last_temp_display_mills;
}


double 
disp::seconds_since_last_temp_display()
{
    Log.notice( "In disp:seconds_since_last_temp_display()" CR );

    unsigned long retval = this->mills_since_last_temp_display() / 1000;
    
    Log.notice( "Leaving disp::seconds_since_last_temp_display() with reval %D" CR, retval );
    return retval;
}

unsigned long 
disp::mills_since_last_setpoint_display()
{
    Log.notice( "In disp::mills_since_last_sp_display()" CR );
    unsigned long now = millis();
    unsigned long retval = now - this->m_last_setpoint_display_mills; 

    Log.notice( "Leaving disp::mills_since_last_sp_display() with retval %l" CR, retval );
}

double 
disp::seconds_since_last_setpoint_display()
{
    Log.notice( "In disp::seconds_since_last_sp_display()" CR );
    
    double retval = this->mills_since_last_setpoint_display() / 1000;

    Log.notice( "Leaving disp::seconds_since_last_sp_display() with retval %D" CR, retval );
}

bool
disp::is_too_soon_temp_display()
{
    Log.notice( "In disp::is_too_soon_temp_display()" CR );
    
    static const unsigned long TEMP_DISPLAY_DEBOUNCE_PERIOD = 2000;

    unsigned long last_temp_display = this->mills_since_last_temp_display();
    bool too_soon = last_temp_display < TEMP_DISPLAY_DEBOUNCE_PERIOD;
    if ( too_soon  )
    {

        Log.notice( "Last temp display mills: %l, debounce period: %l.  Too soon.  Bailing" CR, 
            last_temp_display,
            TEMP_DISPLAY_DEBOUNCE_PERIOD
        );
    }
    
    Log.notice( "Leaving disp::is_too_soon_temp_display() with retval %T" CR, too_soon );

    return too_soon;
}

bool
disp::is_same_temp_as_last_display()
{
    forge_data& fd = singleton_t<forge_data>::instance();
    bool is_same_temp = this->last_temp_seen() == fd.current_temp();

    return is_same_temp;
}

bool
disp::is_same_setpoint_as_last_display()
{
    
}

// Main calling point from loop()
//
void
disp::display()
{
   this->display_temp();
   this->display_setpoint();
   
   return;
}

void
disp::display_setpoint()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    seven_seg& seg = singleton_t< seven_seg >::instance();
    
    int tens = 0;
    int ones = 0;

    break_number( fd.setpoint(), tens, ones );

    seg.writeDigitNum( 3, tens );
    seg.writeDigitNum( 4, ones );
    seg.writeDisplay();

    return;
}



void 
disp::display_temp()
{
    // Main debouncing routine
    //
    bool too_soon   = this->is_too_soon_temp_display();
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

        Log.notice( "About to call display_temp_impl with %d" CR, round( current_temp ) );
        
        this->display_temp_impl( current_temp );
        this->last_temp_seen( current_temp );
        this->last_temp_display_mills( millis() );
    }  

    return;
}


void
disp::display_temp_impl( temp_t temp )
{ 
    seven_seg& seg = singleton_t< seven_seg >::instance();

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

    Log.notice( "Ten digit is: %d, one digit is: %d" CR, tens, ones );

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

    Log.notice( "For number %d the tens place is %d and the ones place is %d" CR, num, tens, ones );
    
    return;
}


