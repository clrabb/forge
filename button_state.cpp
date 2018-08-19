#include "button_state.h"
#include "button.h"
#include "forge_data.h"
#include "singleton_t.h"

void
button_state_unpushed::button_pressed( button* btn )
{
    Serial.println( "in button_state_unpushed::button_pressed()" );
    this->update_setpoint( btn );
    btn->current_state( btn->pushed_state() );   
    
    return;
}

void
button_state_unpushed::update_setpoint( button* btn )
{
    forge_data& fd = singleton_t< forge_data >::instance();
    btn->update_setpoint();

    return;
}



void
button_state_pushed::button_pressed( button* btn )
{
    this->update_setpoint( btn );
    btn->current_state( btn->unpushed_state() );

    return;
}

void
button_state_pushed::update_setpoint( button* btn )
{
    if ( this->has_updated_setpoint() )
        return;

    forge_data& fd = singleton_t< forge_data >::instance();
    fd.increment_setpoint();

    return;
}


void
button_state_latched::button_pressed( button* btn )
{
        
}

void
button_state_latched::update_setpoint( button* btn )
{
    return this;
}

