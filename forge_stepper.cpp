#include "forge_stepper.h"
#include "forge_types.h"


forge_stepper::forge_stepper()
{
    m_current_pos     = 0;      
    m_last_move_mills = 0;
    m_stepper_impl    = new forge_stepper_impl();
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
    int cur_pos = this->current_pos();
    
    if ( new_pos < cur_pos )
    {
        this->step_closed( cur_pos - new_pos );
    }
    else if ( new_pos > cur_pos )
    {
        this->step_open( new_pos - cur_pos );
    }

    this->work_queue();

    return;
}

void 
forge_stepper::step_open( int new_pos )
{
    int cur_pos = this->current_pos();
    int num_steps = new_pos - cur_pos;
    
    for ( int i = 0; i < num_steps; ++i )
    {
        this->push_step( new stepper_step_open() );
    }

    return;
}

void 
forge_stepper::step_closed( int new_pos )
{
    int cur_pos = this->current_pos();
    int num_steps = cur_pos - new_pos;

    for ( int i = 0; i < num_steps; ++i )
    {
        this->push_step( new stepper_step_closed() );
    }
}

void
forge_stepper::push_step( stepper_step_abc* step )
{
    m_step_queue.push_back( step );

    return;
}

stepper_step_abc*
forge_stepper::pop_next_step()
{
    stepper_step_abc* step = m_step_queue.front();
    m_step_queue.pop_front();

    return step;
}

void
forge_stepper::work_queue()
{
    if ( this->is_not_time_to_move() )
        return;

    stepper_step_abc* stepper_step = this->pop_next_step();
    stepper_step->step( this->stepper_impl() );
    this->reset_move_counter();

    delete stepper_step;

    return;
}

void 
forge_stepper::reset_move_counter()
{
    this->last_move_mills( millis() );

    return;
}


