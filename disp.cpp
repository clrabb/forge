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
    unsigned long now = millis();

    return now - this->m_last_temp_display_mills;
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
    return now - this->m_last_setpoint_display_mills; 
}

double 
disp::seconds_since_last_setpoint_display()
{
    return this->mills_since_last_setpoint_display() / 1000;
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

    int last_temp_displayed = round( this->last_temp_seen() );
    int current_temp        = round( fd.current_temp() );
    
    bool is_same_temp = ( last_temp_displayed == current_temp );

    return is_same_temp;
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

    int last_setpoint_seen = round( this->last_setpoint_seen() );
    int current_setpoint   = round( fd.setpoint() );

    if ( last_setpoint_seen == current_setpoint )
    {
        Log.notice( "No need ot update the screen with the same setpoint.  bailing" CR );
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


