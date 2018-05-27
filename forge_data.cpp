#include "forge_data.h"
#include "forge_types.h"
#include "singleton_t.h"
#include "error.h"
#include <Arduino.h>

void
forge_data::current_temp( signed short new_temp )
{
    if ( new_temp != m_current_temp )
    {
        last_temp_changed_mills( millis() );
    }

    m_current_temp = new_temp;

    return;
}


void
forge_data::setpoint( signed short new_setpoint )
{
    if ( new_setpoint != m_setpoint )
    {
        last_sp_changed_mills( millis() );
    }

    m_setpoint = new_setpoint; 

    return;
}
