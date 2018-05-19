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
    unsigned short m_setpoint;
    unsigned short m_current_temp;
    forge_mode m_mode;


public:
    // Ctors and dtors
    //
    forge_data() {};

    // Member functions
    //
    int setpoint() { return m_setpoint; }
    void setpoint( unsigned short setpoint ) { m_setpoint = setpoint; }
    
    int current_temp() { return m_current_temp; }
    void current_temp( unsigned short current_temp ) { m_current_temp = current_temp; }
    
    int mode() { return m_mode; }
    forge_status mode( forge_mode mode );

private:
    // Disable unwanted compiler generated crap
    //
    forge_data( const forge_data& );
    forge_data& operator=(const forge_data&);
    
};

#endif // FORGE_DATA_H
