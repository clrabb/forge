#include "button.h"
#include "forge_types.h"
#include "forge_data.h"
#include "button_state.h"
#include <arduino.h>

button::button( short pin )
    :m_pin( pin )
{
    this->pushed_state( new button_state_pushed() );
    this->unpushed_state( new button_state_unpushed() );
    this->latched_state( new button_state_latched() );

    this->current_state( this->unpushed_state() );
}

bool
button::is_pushed()
{
    return this->current_state()->is_pushed();
}

bool
button::is_unpushed()
{
    return this->current_state()->is_unpushed();
}

bool 
button::is_latched()
{
    return this->current_state()->is_latched();
}

void
button::update()
{
    Serial.println( "in button::update()" );

    short pin = this->pin();
    short level = digitalRead( pin );
    bool is_pressed = ( level == HIGH );

    Serial.print( "Level for pin " );
    Serial.print( pin );
    Serial.print( " is " );
    Serial.print( level );
    Serial.print( ".  " );
    Serial.print( "That means the button is " );
    Serial.println( (is_pressed) ? "pressed." : "unpressed." );
    
    if ( digitalRead( this->pin() ) == HIGH );
        this->current_state()->button_pressed( this );

    return;
    
}

