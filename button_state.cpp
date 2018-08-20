#include "button_state.h"
#include "button.h"
#include "forge_data.h"
#include "singleton_t.h"
#include "arduino.h"

/* -------------------- BASE -------------------- */

void
button_state::update( button* btn )
{
    ( digitalRead( btn->pin() ) == HIGH )
        ? this->button_pressed( btn )
        : this->button_unpressed( btn )
    ;

    return;
}

void
button_state::switch_to_pressed( button* btn )
{
    this->clear_state();
    btn->current_state( btn->pressed_state() );

    return;
}

void 
button_state::switch_to_unpressed( button* btn )
{
    this->clear_state();
    btn->current_state( btn->unpressed_state() );

    return;
}

void 
button_state::switch_to_latched( button* btn )
{
    this->clear_state();
    btn->current_state( btn->latched_state() );

    return;
}

/* -------------------- PUSHED -------------------- */

unsigned long 
button_state_pressed::mills_since_first_pressed()
{
    return millis() - this->first_pressed_mills();
}

void
button_state_pressed::button_unpressed( button* btn )
{
    this->switch_to_unpressed( btn );

    return;
}

void
button_state_pressed::clear_state() 
{
    button_state::clear_state();
    this->first_pressed_mills( 0 );

    return;
}

button_state_pressed::button_state_pressed()
{
    this->first_pressed_mills( 0 );
}

void
button_state_pressed::button_pressed( button* btn )
{
    Serial.println( "In button_state_pushed::button_pressed()" );
    if ( digitalRead( btn->pin() ) == LOW )
    {
        this->switch_to_unpressed( btn );
    }

    return;
}

/* -------------------- UNPUSHED -------------------- */

void
button_state_unpressed::button_pressed( button* btn )
{
    Serial.println( "In button_state_unpressed::button_pressed()" );
    btn->update_setpoint();
    this->switch_to_pressed( btn ); 
  
    return;
}

void
button_state_unpressed::button_unpressed( button* btn )
{
    // I'm already unpresed
    //
    return;
}


/* -------------------- LATCHED -------------------- */




