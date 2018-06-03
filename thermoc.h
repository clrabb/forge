#ifndef THERMOC_H
#define THERMOC_H

#include "max6675.h"
#include "forge_types.h"

class thermoc
{
private:
    MAX6675 m_tc;

public:

    // ctor-dtor
    //
    thermoc(const int do_pin, const int cs_pin, const int clock_pin);
    ~thermoc();
 
    // Decorate the Thermocouple lib
    //
    temp_t read_f();
    temp_t read_c();

private:
    thermoc(const thermoc&); // disable copy ctor
    thermoc & operator=(const thermoc&); //disable assignment op
    thermoc(); // disable default ctor
};

#endif // THERMOC_H


