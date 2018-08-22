#include "forge_servo.h"
#include "forge_types.h"


void 
forge_servo::move_to( uint8_t percent_open )
{
    unsigned long mills = millis();
    unsigned long interval = mills - this->last_move_mills();
    
    if ( mills - this->last_move_mills() > SERVO_DEAD_MILLS )
    {
        this->move_to_impl( percent_open );
    }

    return;
}

void
forge_servo::move_to_impl( uint8_t percent_open )
{
    if ( percent_open < SERVO_MIN || percent_open > SERVO_MAX )
        return;
        
    this->servo_impl().write( percent_open );
    this->last_move_mills( millis() );

    return;
}

// Used during initialization to move the servo to the 0
// position
//
void
forge_servo::initialize_movement()
{
    this->move_to_impl( SERVO_MIN );

    return;
}

