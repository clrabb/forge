#include "disp.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include <arduino.h>



// Accessing
//
unsigned long 
disp::mills_since_last_temp_display()
{
    unsigned long now = millis();
    return now - this->m_last_temp_display_mills;
}


double 
disp::seconds_since_last_temp_display()
{
    return this->mills_since_last_temp_display() / 1000;
}

unsigned long 
disp::mills_since_last_sp_display()
{
    unsigned long now = millis();
    return now - this->m_last_sp_display_mills; 
}

double 
disp::seconds_since_last_sp_display()
{
    return this->mills_since_last_sp_display() / 1000;
}

// Behavior
//
void 
disp::display_temp()
{
#ifdef __DEBUG__
    Serial.println( "In display_temp()" );
#endif // __DEBUG

    forge_data& fd   = singleton_t<forge_data>::instance();
    signed short temp = fd.current_temp();

#ifdef __DEBUG__
    Serial.print( "temp: " );
    Serial.println( temp );
    Serial.print( "last temp: " );
    Serial.println( this->last_temp_seen() );
    
#endif // __DEBUG__

    if ( this->mills_since_last_temp_display() < TEMP_DISPLAY_DEBOUNCE_PERIOD || temp == this->last_temp_seen() )
    {

#ifdef __DEBUG__
    Serial.println( "Bailing" );
#endif // __DEBUG__
        return;
    }

    this->print( fd.current_temp() );
    this->last_temp_display_mills( millis() );
    this->last_temp_seen( temp );

    return;
}

void 
disp::display_setpoint()
{
#ifdef __DEBUG__
    Serial.println( "In display_setpoint()" );
#endif // __DEBUG__

    disp& displ   = singleton_t<disp>::instance();
    forge_data& fd = singleton_t<forge_data>::instance();
    
    this->print( fd.setpoint() );

    return;
}

void
disp::print( int number )
{
#ifdef __DEBUG__
    Serial.println( "In disp::print()" );
    Serial.print( "Printing: " );
    Serial.println( number );
#endif // __DEBUG__

    seven_seg& disp_led = singleton_t<seven_seg>::instance();
    disp_led.print( number, DEC );
    disp_led.writeDisplay();
    
    return;
}

