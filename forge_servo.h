#ifndef FORGE_SERVO_H
#define FORGE_SERVO_H

#include <Arduino.h>
#include <Servo.h>

class forge_servo
{
private:
    unsigned long m_last_command_mills;
    unsigned long m_last_moved_mills;
    uint8_t       m_target_percent_open;
    Servo         m_servo;

public:
    forge_servo( uint8_t servo_pin ) 
        : m_servo( Servo() )
    {
        m_last_moved_mills = 0;
        m_servo.attach( servo_pin );
    }

    // --------------- ACCESSING ------------------
    //
    unsigned long last_command_mills() { return m_last_command_mills; }
    void last_command_mills( unsigned long mills ) { m_last_command_mills = mills; }

    uint8_t target_percent_open() { return m_target_percent_open; }
    void target_percent_open( uint8_t percent ) { m_target_percent_open = percent; }

    unsigned long last_moved_mills() { return m_last_moved_mills; }
    void last_moved_mills( unsigned long mills ) { m_last_moved_mills = mills; }

    // --------------- MOVEMENT ------------------
    //
    void move_to( uint8_t percent_open );
    void initialize_movement();
    void tick();
    uint8_t calculate_next_position( uint8_t current_pos, uint8_t next_pos );

private:
    // ---------------- ACCESSING ----------------
    //
    Servo& servo_impl() { return m_servo; }

    // -------------- MOVEMENT --------------------
    //
    void move_impl( uint8_t new_pos );


private:
    forge_servo( const forge_servo& ); // copy ctor
    const forge_servo& operator=( const forge_servo& ); // assignment operator
};

#endif // FORGE_SERVO_H
