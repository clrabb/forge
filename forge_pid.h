#ifndef FORGE_PID_H
#define FORGE_PID_H

#include "forge_types.h"

class forge_pid
{
public:

    
public:
    // Ctor
    //
    forge_pid()
        : m_pid_guts( 
                &( this->m_input ), 
                &( this->m_output ),
                &( this->m_setpoint ),
                PID_CON_KP,
                PID_CON_KI,
                PID_CON_KD,
                DIRECT
        )
    {}

public:
    // Methods
    double compute( double input, double setpoint );
    void initial_values( double input, double setpoint, int sample_time );
    void initial_values( double input, double setpoint );
    void set_output_limits( double min, double max );
    void start();

private:
    // Member vars
    //
    pid_v1 m_pid_guts;
    double m_input;
    double m_output;
    double m_setpoint;

private:
    // Disable copy ctor and assignment op
    //
    forge_pid( const forge_pid& );
    forge_pid operator=(const forge_pid& );
    
};

#endif // FORGE_PID_H
