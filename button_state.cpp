#include "button_state.h"
#include "button.h"
#include "forge_data.h"
#include "singleton_t.h"
//#include "arduino.h"

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
    btn->current_state( btn->pressed_state() );

    return;
}

void
button_state::switch_to_unpressed( button* btn )
{
    btn->current_state( btn->unpressed_state() );

    return;
}

void
button_state::switch_to_latched( button* btn )
{
    btn->current_state( btn->latched_state() );

    return;
}

/* -------------------- UNPRESSED -------------------- */

void
button_state_unpressed::button_pressed( button* btn )
{
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

/* -------------------- PRESSED -------------------- */

button_state_pressed::button_state_pressed()
{
}

unsigned long
button_state_pressed::mills_since_first_pressed()
{
    unsigned long now = millis();
    unsigned long first_pressed = this->first_pressed_mills();
    unsigned long interval = now - first_pressed;

    return interval;
}

void
button_state_pressed::button_unpressed( button* btn )
{
    this->switch_to_unpressed( btn );
    return;
}

void
button_state_pressed::reset_state()
{
    button_state::reset_state();
    this->first_pressed_mills( millis() );
    this->has_updated_setpoint( false );

    return;
}

bool
button_state_pressed::should_latch()
{
    unsigned long interval = this->mills_since_first_pressed();
    bool should_latch = ( interval > BTN_LATCHED_MILLS );

    return should_latch;
}

bool
button_state_pressed::is_first_pressed()
{
    return !( this->has_updated_setpoint() );
}

void 
button_state_pressed::switch_to_latched_if_needed( button* btn )
{
    if ( this->should_latch() )
    {
        this->switch_to_latched( btn );
    }

    return;
}

void
button_state_pressed::button_pressed( button* btn )
{
    if ( this->is_first_pressed() )
    {
        btn->update_setpoint();
        this->has_updated_setpoint( true );
    }
    else
    {
        this->switch_to_latched_if_needed( btn );
    }

    return;
}



/* -------------------- LATCHED -------------------- */

void
button_state_latched::button_pressed( button* btn )
{
    if ( ( millis() - this->last_sp_change_mills() ) > BTN_UPDATE_SP_DELAY  )
    {
        btn->update_setpoint();
        this->last_sp_change_mills( millis() );
    }

    return;
}

void
button_state_latched::reset_state()
{
    button_state_pressed::reset_state();
    this->last_sp_change_mills( 0 );
}
