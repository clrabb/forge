#include "forge_pid.h"
#include "forge_types.h"


double
forge_pid::compute( double input, double setpoint )
{
    unsigned long current_time = millis();
    if ( current_time - this->last_time_change() < PID_SAMPLE_TIME )
    {
        // Early out
        //
        return;
    }

    m_input    = input;
    m_setpoint = setpoint;

    double gap = abs( setpoint - input );
    ( gap < PID_GAP_THRESHOLD )
        ? m_pid_guts.SetTunings( PID_CON_KP, PID_CON_KI, PID_CON_KD ) // Close, use conservative
        : m_pid_guts.SetTunings( PID_AGG_KP, PID_AGG_KI, PID_AGG_KD ) // Far, use aggresive
    ;
   
    m_pid_guts.Compute();

    this->last_time_change( current_time );

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

void 
forge_pid::set_output_limits( double min, double max )
{
    m_pid_guts.SetOutputLimits( min, max );
}
