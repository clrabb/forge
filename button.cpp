#include "button.h"
#include "forge_types.h"
#include <arduino.h>


button::button( short button_pin )
{
    m_button_pin = button_pin;
}

bool
button::is_pressed()
{
    return digitalRead( m_button_pin ) == HIGH;
}

bool
button::is_still_pressed()
{
    unsigned long now = millis();

    unsigned long mills_since_pressed = now - this->initial_pressed_mills();

    return mills_since_pressed > BTN_SPEEDUP_MILLS;   
}


