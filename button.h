#ifndef BUTTON_H
#define BUTTON_H

#include "button_state.h"

class button
{
private:
    short m_pin;
    button_state* m_current_state;
    button_state* m_btn_unpressed;
    button_state* m_btn_pressed;
    button_state* m_btn_latched;
    
public:
    button( short pin );
    short pin() { return m_pin; }

    void update();

    button_state* current_state() { return m_current_state; }
    void current_state( button_state* state ) { state->reset_state(); m_current_state = state; }

    button_state* unpressed_state() { return m_btn_unpressed; }
    void unpressed_state( button_state* state ) { state->reset_state(); m_btn_unpressed= state; }

    button_state* pressed_state() { return m_btn_pressed; }
    void pressed_state( button_state* state ) { state->reset_state(); m_btn_pressed = state; }

    button_state* latched_state() { return m_btn_latched; }
    void latched_state( button_state* state ) { state->reset_state(); m_btn_latched = state; }

    //------------------------------------------
    // 
    // Virtual methods
    //
    //------------------------------------------
    virtual void update_setpoint() = 0;
        
    //------------------------------------------
    // 
    // Testing
    //
    //------------------------------------------
    bool is_pushed();
    bool is_latched();
    bool is_unpushed();

private:
    button( const button& );
    button& operator=( const button& );
    
};

#endif // BUTTON_H
