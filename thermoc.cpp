#include "thermoc.h"

// Ctors
//
thermoc::thermoc(const int do_pin, const int cs_pin, const int clock_pin)
{
    m_tc = new MAX6675(clock_pin, cs_pin, do_pin);
}

thermoc::~thermoc()
{
    delete( m_tc );
}

// Decorate the Thermocouple lib
//
float
thermoc::read_f()
{
    return m_tc->readFahrenheit();
}

float
thermoc::read_c()
{
    return m_tc->readCelsius();
}
