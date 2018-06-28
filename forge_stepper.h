#ifndef FORGE_STEPPER_H
#define FORGE_STEPPER_H

#include <Stepper.h>
#include <arduino.h>

class forge_stepper
{
private:
    Stepper         m_stepper_impl;
    int             m_max_input_value;
    int             m_current_pos;
    unsigned long   m_last_move_mills;
    
public:
    // Ctor
    //
    forge_stepper( int max_input_value );

    // behavior
    //
    void step_to( int position );
    void step_up( int steps );
    void step_down( int steps );

    // testing
    //
    bool is_time_to_move();
    bool is_not_time_to_move();

private:
    Stepper& stepper_impl() { return m_stepper_impl; }

    int max_input_value() { return m_max_input_value; }
    void max_intput_value( int max_input_value ) { m_max_input_value = max_input_value; }

    int current_pos() { return m_current_pos; }
    void current_pos( int pos ) { m_current_pos = pos; }

    unsigned long last_move_mills() { return m_last_move_mills; }
    void last_move_mills( unsigned long mills ) { m_last_move_mills = mills; }

private:
    forge_stepper( const forge_stepper& );
    const forge_stepper& operator=( const forge_stepper& );
};


#endif // FORGE_STEPPER_H

