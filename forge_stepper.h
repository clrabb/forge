#ifndef FORGE_STEPPER_H
#define FORGE_STEPPER_H

#include "stepper_step.h"
#include <Stepper.h>
#include <arduino.h>
#include <ArduinoSTL.h>
#include <deque>
using namespace std;

class forge_stepper
{
private:
    int             m_max_input_value;
    int             m_current_pos;     
    unsigned long   m_last_move_mills;
    forge_stepper_impl         m_stepper_impl;
    deque< stepper_step_abc* > m_step_queue;
    
public:
    // Ctor
    //
    forge_stepper( int max_input_value );

    // behavior
    //
    void step_to( int position );
    void step_open( int steps );
    void step_closed( int steps );

    // testing
    //
    bool is_time_to_move();
    bool is_not_time_to_move();

private:
    forge_stepper_impl& stepper_impl() { return m_stepper_impl; }

    int max_input_value() { return m_max_input_value; }
    void max_intput_value( int max_input_value ) { m_max_input_value = max_input_value; }
    
    unsigned long last_move_mills() { return m_last_move_mills; }
    void last_move_mills( unsigned long mills ) { m_last_move_mills = mills; }

    int current_pos() { return m_current_pos; }
    void current_pos( int pos ) { m_current_pos = pos; }

    uint8_t current_step() { return m_current_step; }
    void current_step( uint8_t step ) { m_current_step = step; }


private:
    forge_stepper( const forge_stepper& );
    const forge_stepper& operator=( const forge_stepper& );
};


#endif // FORGE_STEPPER_H

