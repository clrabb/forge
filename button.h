#ifndef BUTTON_H
#define BUTTON_H

#include "button_state.h"

class button
{
private:
    short m_pin;
    button_state* m_current_state;
    button_state* m_btn_unpushed;
    button_state* m_btn_pushed;
    button_state* m_btn_latched;
    
public:
    button( short pin );
    short pin() { return m_pin; }

    void update();

    button_state* current_state() { return m_current_state; }
    void current_state( button_state* state ) { m_current_state = state; }

    button_state* unpushed_state() { return m_btn_unpushed; }
    void unpushed_state( button_state* state ) { m_btn_unpushed = state; }

    button_state* pushed_state() { return m_btn_pushed; }
    void pushed_state( button_state* state ) { m_btn_pushed = state; }

    button_state* latched_state() { return m_btn_latched; }
    void latched_state( button_state* state ) { m_btn_latched = state; }

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
