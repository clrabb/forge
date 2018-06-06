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
    volatile setpoint_t m_setpoint;
    temp_t              m_current_temp;
    double              m_current_pid_output;
    unsigned long       m_last_pid_output_mills;
    unsigned long       m_last_sp_changed_mills;
    unsigned long       m_last_temp_changed_mills;

public:
    // Ctors and dtors
    //
    forge_data() 
        : m_setpoint( START_SP )
    {};

    // Member functions
    //
    setpoint_t setpoint() { return m_setpoint; }
    void increment_setpoint();
    void decrement_setpoint();
    void setpoint( setpoint_t sp ) { m_setpoint = sp; }
    
    temp_t current_temp() { return m_current_temp; }
    void current_temp( temp_t new_temp );

    double current_pid_output() { return m_current_pid_output; }
    void current_pid_output( double output );

    unsigned long last_sp_changed_mills() { return m_last_sp_changed_mills; }
    void last_sp_changed_mills( unsigned long mills ) { m_last_sp_changed_mills = mills; }

    unsigned long last_temp_changed_mills() { return m_last_temp_changed_mills; }
    void last_temp_changed_mills( unsigned long mills ) { m_last_temp_changed_mills = mills; }

    unsigned long last_pid_output_mills() { return m_last_pid_output_mills; }
    void last_pid_output_mills( unsigned long mills ) { m_last_pid_output_mills = mills; }
    
    unsigned long mills_since_last_sp_change();
    double seconds_since_last_sp_change();

    unsigned long mills_since_last_pid_output_change();
    double seconds_since_last_pid_output_change();

    unsigned long mills_since_last_temp_change();
    double seconds_since_last_temp_change();

   

private:
    // Disable unwanted compiler generated crap
    //
    forge_data( const forge_data& );
    forge_data& operator=(const forge_data&);
    
};

#endif // FORGE_DATA_H

