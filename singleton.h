#ifndef SINGLETON_H
#define SINGLETON_H

#include "max6675.h"


class singleton_thermo
{
public:
    static singleton_thermo* instance() { static singleton_thermo s_thermo; return &s_thermo; }
  
private:
    static singleton_thermo* s_instance;
    MAX6675* m_thermoc = 0;

public:
    
    // Initialize the single instance
    //
    static void init(const int do_pin, const int cs_pin, const int clock_pin)
    {
        // Way not thread safe
        //
        singleton_thermo::s_instance = new singleton_thermo(do_pin, cs_pin, clock_pin);
    }
    

public:

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

