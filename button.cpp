#include "button.h"
#include "forge_types.h"
#include "forge_data.h"
#include "button_state.h"
#include <arduino.h>

button::button( short pin )
    :m_pin( pin )
{
    this->pressed_state(   new button_state_pressed()   );
    this->unpressed_state( new button_state_unpressed() );
    this->latched_state(   new button_state_latched()   );

    this->current_state( this->unpressed_state() );
}

bool
button::is_pressed()
{
    return this->current_state()->is_pressed();
}

bool
button::is_unpressed()
{
    return this->current_state()->is_unpressed();
}

bool 
button::is_latched()
{
    return this->current_state()->is_latched();
}

void
button::update()
{
    this->current_state()->update( this );
    return;
    
}

