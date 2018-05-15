#ifndef SINGLETON_H
#define SINGLETON_H

#include "arduino.h"
#include "max6675.h"

class singleton_thermo
{
public:

    // Initialize the single instance
    //
    static void init(const int do_pin, const int cs_pin, const int clock_pin)
    {
        // Way not thread safe
        //
        s_instance = singleton_thermo(do_pin, cs_pin, clock_pin);
    }

private:
    // Single instance member vars
    //
    static singleton_thermo s_instance;
    MAX6675* m_thermoc = NULL;

    // Singleton imp ctor
    //
    singleton_thermo(int do_pin, int cs_pin, int clock_pin)
    {
        m_thermoc = new MAX6675(clock_pin, cs_pin, do_pin);
    }

    ~singleton_thermo()
    {
        delete( m_thermoc );
    }

public:
    // Get the single instance
    //
    static singleton_thermo & instance()
    {
        return singleton_thermo::s_instance;
    }

    // Decorate the Thermocouple lib
    //
    float read_f()
    {
        //return m_thermoc->readFahrenheit();
        return 500;
    }

    float read_c()
    {
        return m_thermoc->readCelsius();
    }

private:
    singleton_thermo(const singleton_thermo&); // disable copy ctor
    singleton_thermo & operator=(const singleton_thermo&); //disable assignment op
    singleton_thermo(); // disable default ctor

};

#endif
