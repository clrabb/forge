#ifndef FORGE_STEPPER_IMPL_H
#define FORGE_STEPPER_IMPL_H

#include <Arduino.h>

// This is the guts of the stepper itself, responsible for
// moving the rotor by energizing the stator coils
//
class forge_stepper_impl
{
public:
    forge_stepper_impl();

private:
    uint8_t m_current_coil;

public:
    // Open is clockwise when viewed from the front of the motor
    //
    void step_open();
    void step_closed();

private:
    // Accessing
    uint8_t current_coil() { return m_current_coil; }
    void current_coil( uint8_t coil ) { m_current_coil = coil; }
    
    // Disable complier generated garbage
    //
    forge_stepper_impl( const forge_stepper_impl& );
    const forge_stepper_impl& operator=( const forge_stepper_impl& );

    // Coil management
    //
    void step_impl( uint8_t coil );
};


#endif // FORGE_STEPPER_IMPL_H
