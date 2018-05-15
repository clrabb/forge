#ifndef SINGLETON_H
#define SINGLETON_H

#include "max6675.h"


class singleton_thermo
{
private:
    static singleton_thermo* s_thermo; 
    MAX6675* m_thermoc = 0;

public:
    static singleton_thermo* instance() { return s_thermo; }
    static void init(const int do_pin, const int cs_pin, const int clock_pin);

public:

    // Singleton imp ctor/dtor
    //
    singleton_thermo(const int do_pin, const int cs_pin, const int clock_pin);
    ~singleton_thermo();

 
    // Decorate the Thermocouple lib
    //
    float read_f();
    float read_c();


private:
    singleton_thermo(const singleton_thermo&); // disable copy ctor
    singleton_thermo & operator=(const singleton_thermo&); //disable assignment op
    singleton_thermo(); // disable default ctor

};

#endif

