#include "forge_data.h"
#include "forge_types.h"
#include "singleton_t.h"
#include <Arduino.h>
#include <ArduinoLog.h>


void
forge_data::current_temp( temp_t new_temp )
{
    if ( m_current_temp == new_temp )
        return;  // Bail.

    this->last_temp_changed_mills( millis() );
    this->m_current_temp = new_temp;

#ifdef __DEBUG__
    // Stupid logging framework doesn't deal with doubles???
    //
    Serial.print( "Setting temp to: " );
    Serial.print( new_temp );
    Serial.print( ". Old temp was: " );
    Serial.println( this->m_current_temp );
#endif

    return;
}

void
forge_data::increment_setpoint()
{
    // Not logging because this is called from inside interrupt
    //
    this->last_sp_changed_mills( millis() );
    ++m_setpoint;

    return;
}

void 
forge_data::decrement_setpoint()
{
    this->last_sp_changed_mills( millis() );
    --m_setpoint;
}

unsigned long
forge_data::mills_since_last_temp_change()
{
    unsigned long now_mills = millis();
    return now_mills - this->last_temp_changed_mills();
}

double 
forge_data::seconds_since_last_temp_change()
{
    return this->mills_since_last_sp_change() / 1000;
}

unsigned long 
forge_data::mills_since_last_sp_change()
{
    unsigned long now_mills = millis();
    return now_mills - this->last_sp_changed_mills();
}

double
forge_data::seconds_since_last_sp_change()
{
    return this->mills_since_last_sp_change() / 1000;
}


