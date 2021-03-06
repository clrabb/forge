#include "display_led_abc.h"


display_led_abc::~display_led_abc()
{
    if ( this->m_ada_display != NULL )
    {
        delete this->m_ada_display;
    }

    return;
}

void
display_led_abc::write_number( int number )
{
    if ( ( millis() - this->last_display_mills()  ) < this->refresh_time() )
        return;  // Bail.  not time to display yet

    int last_displayed = this->last_displayed_number();

    if ( number == last_displayed )
        return; // Bail, number the same as last time
  
    this->write_number_impl( number );
    this->last_displayed_number( number );
    this->last_display_mills( millis() );

    return;
}

void
display_led_abc::init( uint8_t address, uint8_t brightness, unsigned long refresh_time /* milliseconds */ )
{
    // Create display is a virtual function implemented
    // by subclasses
    //    
    this->ada_display( this->create_display() );
    this->ada_display()->begin( address );
    this->ada_display()->setBrightness( brightness );
    this->refresh_time( refresh_time );
    
    this->run_tests();

    return;
}

