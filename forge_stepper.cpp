#include "forge_stepper.h"
#include "forge_types.h"

forge_stepper::forge_stepper( uint8_t max_input_value )
    : m_stepper_impl( Stepper( STEPS_PER_REVOLUTION, FSTEPPER_PIN1, FSTEPPER_PIN2, FSTEPPER_PIN3, FSTEPPER_PIN4 ) )
{
    m_max_input_value = max_input_value;        
}

