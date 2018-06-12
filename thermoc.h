#ifndef THERMOC_H
#define THERMOC_H

#include "max6675.h"
#include "forge_types.h"

class thermoc
{
private:
    
    MAX6675       m_tc;
    temp_t        m_last_temp_read  = 0;
    unsigned long m_last_read_mills = 0;
    static const unsigned long MIN_TC_READ_TIME = 500;

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
    // This is used to stop from flooding the MAX6675 with requests.
    // It doesn't seem to like that.
    //
    void last_read_mills( unsigned long mills ) { m_last_read_mills = mills; }
    temp_t last_temp_read() { return m_last_temp_read; }
    void last_temp_read( temp_t temp ) { m_last_temp_read = temp; }
    unsigned long last_read_mills() { return m_last_read_mills; }

    
    thermoc(const thermoc&); // disable copy ctor
    thermoc & operator=(const thermoc&); //disable assignment op
    thermoc(); // disable default ctor
};

#endif // THERMOC_H


