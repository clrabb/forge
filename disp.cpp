#include "disp.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
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
disp::is_same_temp_temp_display()
{
    Log.notice( "In is_same_temp_temp_display()" CR );

    forge_data& fd = singleton_t<forge_data>::instance();
    bool is_same_temp = this->last_temp_seen() == fd.current_temp();

    Log.notice( "Leaving is_same_temp_temp_display() with retval: %T" CR, is_same_temp );

    return is_same_temp;
}

bool
disp::is_joe_fiddling_sp()
{
    Log.notice( "In disp::is_joe_fiddling_sp()" CR );

    forge_data& fd = singleton_t< forge_data >::instance();
    signed short last_seen = this->last_setpoint_seen();
    signed short current_setpoint = fd.setpoint();

    bool is_fiddling = ( last_seen != current_setpoint );
    
    Log.notice( "Leaving is_joe_fiddlng_sp() with retval %T" CR, is_fiddling );

    return is_fiddling;
}

// Main calling point from loop()
//
void
disp::display()
{
    Log.notice( "In disp::display()" CR );

    this->display_setpoint_if_changing();

    digitalWrite( SP_LED_PIN, LOW );
    
    this->display_temp();

    Log.notice( "Leaving disp::display()" CR );
    return;
}

void 
disp::display_temp()
{
    Log.notice( "In disp::display_temp()" CR );
    
    // Main debouncing routine
    //
    // I realize this can be done with a short circuit but I want to
    // log the results of all three calls
    //
    bool too_soon     = this->is_too_soon_temp_display();
    bool same_temp    = this->is_same_temp_temp_display();
    bool joe_fiddling = is_joe_fiddling_sp();
    if ( too_soon || same_temp || joe_fiddling )
    {
        Log.notice( "Nothing to do.  too_soon: %T; same_temp: %T; joe fiddling: %T" CR,
            too_soon,
            same_temp,
            joe_fiddling
        );
    }
    else
    {
        forge_data& fd = singleton_t<forge_data>::instance();
        signed short current_temp = fd.current_temp();
        this->print( current_temp );
        this->last_temp_seen( current_temp );
        this->last_temp_display_mills( millis() );
    }  

    Log.notice( "Leaving disp::display_temp()" CR );
    return;
}

void 
disp::display_setpoint_if_changing()
{
    Log.notice( "In disp::display_setpoint()" CR );

    if ( !( is_joe_fiddling_sp() ) )
    {
        Log.notice( "Joe's not fiddling with the set point.  I'm outta here" CR );
        return;
    }

    Log.notice( "Looks like the setpoint is changing.  Print the current setpoint" CR );
    
    disp& displ    = singleton_t<disp>::instance();
    forge_data& fd = singleton_t<forge_data>::instance();
    
    this->print( fd.setpoint() );
    digitalWrite( SP_LED_PIN, HIGH );
    delay( BLINK_ON_T );
    //digitalWrite( SP_LED_PIN, LOW );

    this->last_setpoint_seen( fd.setpoint() );
    this->last_setpoint_dipslay_mills( millis() );

    Log.notice( "Leaving disp::display_setpoint()" CR );
    return;
}

void
disp::print( int number )
{
    Log.notice( "In disp::print()" CR );

    Log.notice( "Printing %d" CR, number );
    seven_seg& disp_led = singleton_t<seven_seg>::instance();
    disp_led.print( number, DEC );
    disp_led.writeDisplay();

    Log.notice( "Leaving disp::print()" CR );
     
    return;
}

