#include "forge_pid.h"


double
forge_pid::compute( double input, double setpoint )
{
    m_input    = input;
    m_setpoint = setpoint;
/*
#ifdef __DEBUG__ 
    Serial.print( "About to compute new output based on temp: " );
    Serial.print( m_input );
    Serial.print( "; setpoint: " );
    Serial.println( m_setpoint );
#endif // __DEBUG__
*/
    double gap = abs( setpoint - input );
    ( gap < 10 )
        ? m_pid_guts.SetTunings( CON_KP, CON_KI, CON_KD ) // Close, use conservative
        : m_pid_guts.SetTunings( AGG_KP, AGG_KI, AGG_KD ) // Far, use aggresive
    ;
   
    m_pid_guts.Compute();

    return m_output;
}

void
forge_pid::initial_values( double input, double setpoint, int sample_time )
{
    m_pid_guts.SetSampleTime( sample_time );
    this->initial_values( input, setpoint );

    return;
}

void
forge_pid::initial_values( double input, double setpoint )
{
    m_input = input;
    m_setpoint = setpoint;

    return;
}

void
forge_pid::start()
{
    m_pid_guts.SetMode( AUTOMATIC );
}

