#include "display.h"
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <arduino.h>

static const int TEMP_DISPLAY_DEBOUNCE_PERIOD = 1000;

// Accessing
//
unsigned long 
display::mills_since_last_temp_display()
{
    unsigned long now = millis();
    return now - this->m_last_temp_display_mills;
}


double 
display::seconds_since_last_temp_display()
{
    return this->mills_since_last_temp_display() / 1000;
}

unsigned long 
display::mills_since_last_sp_display()
{
    unsigned long now = millis();
    return now - this->m_last_sp_display_mills; 
}

double 
display::seconds_since_last_sp_display()
{
    return this->mills_since_last_sp_display() / 1000;
}

// Behavior
//
void 
display::display_temp( signed short temp )
{
    if ( this->mills_since_last_temp_display() < TEMP_DISPLAY_DEBOUNCE_PERIOD )
        return;

    
}

void 
display::display_sp( signed short setpoint )
{
    
}

