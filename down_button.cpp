#include "down_button.h"
#include "forge_data.h"
#include "singleton_t.h"

down_button::down_button( short pin )
    : button( pin ) 
    {}

void
down_button::update_setpoint()
{
    Serial.println( "In down_button::update_setpoint()" );
    
    forge_data& fd = singleton_t< forge_data >::instance();

    fd.decrement_setpoint();

    return;
}

    
