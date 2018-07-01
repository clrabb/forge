#include "forge_servo.h"
#include "forge_types.h"

// move the servo to the sepecified percentage open
// this needs to be a number between 0 and 180.
// The multiplication for turning those movements into
// what is effectively two full turns on the valve is done
// with gearing and need not be handled here
//
// In order to avoid moving the servo all the time and
// run the possibility of telling it to move while it's moving
// we are only going to move it at most every SERVER_DEAD_TIME
//
void 
forge_servo::move_to( uint8_t percent_open )
{
    uint8_t mills = millis();
    if ( mills - this->last_move_mills() > SERVO_DEAD_MILLS )
    {
        this->move_to_impl( percent_open );
    }

    return;
}

void
forge_servo::move_to_impl( uint8_t percent_open )
{
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

