#include "heartbeat.h"
#include "forge_types.h"
#include <arduino.h>

heartbeat::heartbeat( uint8_t led_pin, unsigned long mills_between_beats, unsigned long beat_length_mills )
    :
    m_led_pin( led_pin ),
    m_mills_between_beats( mills_between_beats ),
    m_beat_length_mills( beat_length_mills )
{
    pinMode( led_pin, OUTPUT );
}

void
heartbeat::beat()
{
#ifdef __DEBUG__
    Serial.println( "In heartbeat::beat()" );
#endif

    if ( this->is_off() )
        this->off_beat();
    else
        this->on_beat();

    return;
}

unsigned long 
heartbeat::time_on()
{
    return
        ( this->is_on() )
            ? millis() - this->last_state_change_mills() 
            : 0
        ;           
}

unsigned long
heartbeat::time_off()
{
    return
        ( this->is_off() )
            ? millis() - this->last_state_change_mills() 
            : 0
        ;
}

void 
heartbeat::off_beat()
{
#ifdef __DEBUG__
    Serial.println( "In heartbeat::off_beat()" );
#endif
   
    if ( this->time_off() >= this->mills_between_beats() )
    {
        this->turn_on();
    }

    return;
}

void
heartbeat::on_beat()
{
#ifdef __DEBUG__
    Serial.println( "In heartbeat::on_beat()" );
#endif

    if ( this->time_on() >= this->beat_length_mills() )
    {
        this->turn_off();
    }

    return;
}

void 
heartbeat::turn_on()
{
#ifdef __DEBUG__
    Serial.println( "In heartbeat::turn_on()" );
    Serial.print( "Turning on pin " );
    Serial.println( this->led_pin() );
#endif 

    digitalWrite( this->led_pin(), HIGH );

    this->last_state_change_mills( millis() );
    return;
}

void 
heartbeat::turn_off()
{
    digitalWrite( this->led_pin(), LOW );   
    this->last_state_change_mills( millis() );

    return;
}


bool
heartbeat::is_on()
{
    // Trying it this way first as it should be more reliable than a variable
    // On the ATMEL chips there is are three different registers that hold or
    // control the state of the pins.  The digital pins are PORTD.  
    //
    return 1 == bitRead( PORTD, this->led_pin() );
}

bool
heartbeat::is_off()
{
    return !( this->is_on() );
}    
