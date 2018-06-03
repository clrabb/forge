#include "thermoc.h"
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
temp_t
thermoc::read_f()
{
    return this->m_tc.readFahrenheit();
}


temp_t
thermoc::read_c()
{
    return this->m_tc.readCelsius();
}

