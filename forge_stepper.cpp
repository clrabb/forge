#include "forge_stepper.h"
#include "forge_types.h"


forge_stepper::forge_stepper( int max_input_value )
    : m_stepper_impl( Stepper( STEPS_PER_REVOLUTION, FSTEPPER_PIN1, FSTEPPER_PIN2, FSTEPPER_PIN3, FSTEPPER_PIN4 ) )
{
    m_max_input_value = max_input_value;  
    m_current_pos = 0;      
    m_last_move_mills = 0;
    
}

bool
forge_stepper::is_time_to_move()
{
    return ( millis() - this->last_move_mills() ) > STEP_DEAD_MILLS;
}


bool
forge_stepper::is_not_time_to_move()
{
    return !( this->is_time_to_move() );    
}

void
forge_stepper::step_to( int new_pos )
{

void
forge_stepper::step_right()
{
    uint8_t next_step = this->current_step() + 1;
    this->step_impl( next_step );
    this->current_step( next_step );

    return;
}

void 
forge_stepper::step_left()
{
    uint8_t next_step = this->current_step() - 1;
    this->step_impl( next_step );
    this->current_step( next_step );

    return;
}



    int cur_pos = this->current_pos();
    
    if ( new_pos < cur_pos )
    {
        this->step_down( cur_pos - new_pos );
    }
    else if ( new_pos > cur_pos )
    {
        this->step_up( new_pos - cur_pos );
    }

    return;
}

void
forge_stepper::step_up( int steps )
{
#ifdef __DEBUG_STEPPER__
    Serial.print("forge_stepper::step_up(");
    Serial.print( steps );
    Serial.println( ")" );
#endif

    Stepper& stepper = this->stepper_impl();
    for ( int i = 0; i < steps; ++i )
    {
        stepper.step( 1 ); // Number of steps to move is 1
        this->current_pos( this->current_pos() + 1);
    }

    this->last_move_mills( millis() );

    return;
}

void
forge_stepper::step_down( int steps )
{
#ifdef __DEBUG_STEPPER__
    Serial.print("forge_stepper::step_down(");
    Serial.print( steps );
    Serial.println( ")" );
#endif

    Stepper& stepper = this->stepper_impl();
    for ( int i = 0; i < steps; ++i )
    {
        stepper.step( -1 ); // Number of steps to move (backwards) is 1 
        this->current_pos( this->current_pos() - 1 );
    }

    this->last_move_mills( millis() );

    return;
}





