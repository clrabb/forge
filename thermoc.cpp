#include "thermoc.h"
#include "stdio.h"
#include "stdlib.h"

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
int
thermoc::read_f()
{
    return round( this->m_tc.readFahrenheit() );
}

int
thermoc::read_c()
{
    return round( this->m_tc.readCelsius() );
}
