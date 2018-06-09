#include "display_led_abc.h"
#include <ArduinoLog.h>


display_led_abc::~display_led_abc()
{
    if ( this->m_ada_display != NULL )
    {
        delete this->m_ada_display;
    }

    return;
}

void
display_led_abc::write_number( uint8_t number )
{
    Log.notice( "************ DISPLAY_LED_ABC::WRITE_NUMBER() ************" CR );
    Log.notice( "%s In display_led_abc::write_number with number: %d" CR, this->name(), number );
    
    if ( ( millis() - this->last_display_mills()  ) < DEFAULT_MIN_REFRESH_TIME )
        return;  // Bail.  not time to display yet

    uint8_t last_displayed = this->last_displayed_number();
    Log.notice( "Number is %d, last displayed number is %d" CR, number, last_displayed );
    if ( number == last_displayed )
        return // Bail, number the same as last time
        
    this->write_number_impl( number );
    this->last_displayed_number( number );
    this->last_display_mills( millis() );

    Log.notice( "Leaving display_led_abc::write_number()" CR );
    Log.notice( "***********" CR );
    return;
}

void
display_led_abc::init( uint8_t address, uint8_t brightness, unsigned long min_refresh_time )
{
    // Create display is a virtual function implemented
    // by subclasses
    //    
    this->ada_display( this->create_display() );
    this->ada_display()->begin( address );
    this->ada_display()->setBrightness( brightness );
    this->min_refresh_time( min_refresh_time );
    
    this->run_tests();

    return;
}

