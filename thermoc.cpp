#include "thermoc.h"
#include "forge_types.h"
#include <stdio.h>
#include <stdlib.h>

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
signed short
thermoc::read_f()
{
    signed short read_temp = round( this->m_tc.readFahrenheit() );
    return read_temp;
}


signed short
thermoc::read_c()
{
    return round( this->m_tc.readCelsius() );
}

