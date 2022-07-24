#include "forge_fan.h"

void
forge_fan::tick()
{
    analogWrite( this->m_pin, this->m_percent_open );
}

void
forge_fan::set_percent( short percent )
{
    if ( percent >= FAN_RANGE_MIN && percent <= FAN_RANGE_MAX )
    {
        this->m_percent_open = percent;
    }
}
