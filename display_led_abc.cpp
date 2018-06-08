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
display_led_abc::init( uint8_t address, uint8_t brightness )
{
    // Create display is a virtual function implemented
    // by subclasses
    //    
    this->ada_display( this->create_display() );
    this->ada_display()->begin( address );
    this->ada_display()->setBrightness( brightness );
    this->run_tests();

    return;
}

