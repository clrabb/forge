#include "forge_fan.h"

void
forge_fan::tick()
{
    analogWrite( this->m_pin, this->m_percent_open );
}
