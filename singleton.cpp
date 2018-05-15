#include "singleton.h"

singleton_thermo* singleton_thermo::s_thermo = 0;

// Initialize the single instance
//
static void singleton_thermo::init(const int do_pin, const int cs_pin, const int clock_pin)
{
    // Way not thread safe
    //
    singleton_thermo::s_thermo = new singleton_thermo(do_pin, cs_pin, clock_pin);
}

singleton_thermo::singleton_thermo(const int do_pin, const int cs_pin, const int clock_pin)
{
    m_thermoc = new MAX6675(clock_pin, cs_pin, do_pin);
}

singleton_thermo::~singleton_thermo()
{
    delete( m_thermoc );
}

// Decorate the Thermocouple lib
//
float
singleton_thermo::read_f()
{
    return m_thermoc->readFahrenheit();
}

float
singleton_thermo::read_c()
{
    return m_thermoc->readCelsius();
}
