#ifndef FORGE_SERVO_H
#define FORGE_SERVO_H

#include <Arduino.h>
#include <Servo.h>

class forge_servo
{
private:
    unsigned long m_last_move_mills;
    Servo         m_servo;

public:
    forge_servo( uint8_t servo_pin ) 
        : m_servo( Servo() )
    {
        m_last_move_mills = 0;
        m_servo.attach( servo_pin );
    }

    // --------------- ACCESSING ------------------
    //
    unsigned long last_move_mills() { return m_last_move_mills; }
    void last_move_mills( unsigned long mills ) { m_last_move_mills = mills; }

    // --------------- MOVEMENT ------------------
    //
    void move_to( uint8_t percent_open );
    void initialize_movement();

private:
    // ---------------- ACCESSING ----------------
    //
    Servo& servo_impl() { return m_servo; }

    // -------------- MOVEMENT --------------------
    //
    void move_to_impl( uint8_t percent_open );

private:
    forge_servo( const forge_servo& ); // copy ctor
    const forge_servo& operator=( const forge_servo& ); // assignment operator
};

#endif // FORGE_SERVO_H
