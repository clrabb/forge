#ifndef FORGE_STEPPER_H
#define FORGE_STEPPER_H

#include <Stepper.h>
#include <arduino.h>

class forge_stepper
{
private:


    Stepper     m_stepper_impl;
    uint8_t     m_max_input_value;
 
    forge_stepper( uint8_t max_input_value );

private:
    Stepper& stepper_impl();

    uint8_t max_input_value() { return m_max_input_value; }
    void max_intput_value( uint8_t max_input_value ) { m_max_input_value = max_input_value; }
    
    

private:
    forge_stepper( const forge_stepper& );
    const forge_stepper& operator=( const forge_stepper& );
};


#endif // FORGE_STEPPER_H

