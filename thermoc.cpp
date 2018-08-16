#include "thermoc.h"


// Ctors
//
thermoc::thermoc(const int do_pin, const int cs_pin, const int clock_pin)
 : m_tc( clock_pin, cs_pin, do_pin )
{
}

thermoc::~thermoc()
{
}

// Decorate the Thermocouple lib
//
temp_t
thermoc::read_f()
{
    unsigned long mills_now = millis();
    if ( ( mills_now - this->last_read_mills() ) < thermoc::MIN_TC_READ_TIME )
        return this->last_temp_read();

    temp_t t = this->m_tc.readFahrenheit();
    this->last_temp_read( t );
    this->last_read_mills( mills_now );

    Serial.print( "reading tc: " );
    Serial.println( t );

    return t;
}


temp_t
thermoc::read_c()
{
    return this->m_tc.readCelsius();
}

