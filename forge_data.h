#ifndef FORGE_DATA_H
#define FORGE_DATA_H

#include "forge_types.h"


// Pretty much a struct
//
class forge_data
{
private:
    // Member variables
    //
    volatile unsigned short m_setpoint;
    unsigned short          m_current_temp;
    unsigned long           m_last_sp_changed_mills;
    unsigned long           m_last_temp_changed_mills;

public:
    // Ctors and dtors
    //
    forge_data() {};

    // Member functions
    //
    int setpoint() { return m_setpoint; }
    void setpoint( signed short setpoint );
    
    signed short current_temp() { return m_current_temp; }
    void current_temp( signed short new_temp );

    unsigned long last_sp_changed_mills() { return m_last_sp_changed_mills; }
    void last_sp_changed_mills( unsigned long mills ) { m_last_sp_changed_mills = mills; }

    unsigned long last_temp_changed_mills() { return m_last_temp_changed_mills; }
    void last_temp_changed_mills( unsigned long mills ) { m_last_temp_changed_mills = mills; }

private:
    // Disable unwanted compiler generated crap
    //
    forge_data( const forge_data& );
    forge_data& operator=(const forge_data&);
    
};

#endif // FORGE_DATA_H
