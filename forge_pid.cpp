#include "forge_pid.h"


double
forge_pid::compute( double input, double setpoint )
{
    m_input    = input;
    m_setpoint = setpoint;

    /*
    double gap = abs( setpoint - input );
    ( gap < 10 || gap )
        ? m_pid_guts.SetTunings( CON_KP, CON_KI, CON_KD ) // Close, use conservative
        :  // Far, use aggresive
    ;
    */
    m_pid_guts.SetTunings( AGG_KP, AGG_KI, AGG_KD );
    m_pid_guts.Compute();

    return m_output;
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

