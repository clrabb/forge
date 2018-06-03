#ifndef DISP_H
#define DISP_H

#include "forge_types.h"
#include "forge_data.h"


class disp
{
private:
    // Member vars
    //
    unsigned long m_last_temp_display_mills     = 0;
    unsigned long m_last_setpoint_display_mills = 0;
    temp_t        m_last_temp_seen              = 0;
    temp_t        m_last_setpoint_seen          = 0;
    
public:
    // Ctors & dtors
    //
    disp() {}

    // Accessing
    //
    unsigned long mills_since_last_temp_display();
    double seconds_since_last_temp_display();
    
    unsigned long mills_since_last_setpoint_display();
    double seconds_since_last_setpoint_display();

    // Behavior
    //
    void display();

private:    
    void last_temp_display_mills( unsigned long mills ) 
        { m_last_temp_display_mills = mills; }
  
    void last_setpoint_dipslay_mills( unsigned long mills )
        { m_last_setpoint_display_mills = mills; } 

    void last_setpoint_seen( setpoint_t sp ) { m_last_setpoint_seen = sp; }
    setpoint_t last_setpoint_seen() { return m_last_setpoint_seen; }
    
    void last_temp_seen( temp_t temp ) { m_last_temp_seen = temp; }
    temp_t last_temp_seen() { return m_last_temp_seen; }

    bool is_too_soon_temp_display();
    bool is_same_temp_as_last_display();
    bool is_same_setpoint_as_last_display();

    void print_temp( temp_t temp, setpoint_t setpoint );
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

