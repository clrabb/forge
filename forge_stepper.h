#ifndef FORGE_STEPPER_H
#define FORGE_STEPPER_H

#include "stepper_step.h"
#include <Stepper.h>
#include <arduino.h>
#include <ArduinoSTL.h>
#include <deque>
using namespace std;

typedef deque< stepper_step_abc* > step_queue;

class forge_stepper
{
private:
    int                 m_current_pos;     
    unsigned long       m_last_move_mills;
    forge_stepper_impl* m_stepper_impl;
    step_queue          m_step_queue;
    
public:
    // Ctor
    //
    forge_stepper();

    // -------------------- BEHAVIOR ---------------
    //
    void step_to( int position );
    void step_open( int steps );
    void step_closed( int steps );

    // -------------------- TESTING ----------------
    //
    bool is_time_to_move();
    bool is_not_time_to_move();

private:

    // -------------- Accessing ------------------
    
    const forge_stepper_impl* stepper_impl() { return m_stepper_impl; }
    
    unsigned long last_move_mills() { return m_last_move_mills; }
    void last_move_mills( unsigned long mills ) { m_last_move_mills = mills; }

    int current_pos() { return m_current_pos; }
    void current_pos( int pos ) { m_current_pos = pos; }

    /* ------------------- COLLECTION --------------- */
    step_queue& step_queue() { return m_step_queue; }
    void push_step( stepper_step_abc* );
    stepper_step_abc* pop_next_step();
    void work_queue();

    /* ---------------- PRIVATE BEHAVIOR ----------- */
    void reset_move_counter();

private:
    forge_stepper( const forge_stepper& );
    const forge_stepper& operator=( const forge_stepper& );
};


#endif // FORGE_STEPPER_H

