#include "forge_servo.h"
#include "forge_types.h"


void 
forge_servo::move_to( uint8_t percent_open )
{
    
    if ( percent_open < SERVO_MIN || percent_open > SERVO_MAX )
        return;

    unsigned long mills = millis();
    unsigned long interval = mills - this->last_command_mills();
    if ( interval > SERVO_DEBOUNCE_INTERVAL )
    {
        //this->target_percent_open( percent_open );
        this->last_command_mills( mills );
        this->move_impl( percent_open );
    }

    return;
}

void 
forge_servo::tick()
{
    /*
    unsigned long mills = millis();
    unsigned long interval = millis() - this->last_moved_mills();
    if ( interval > SERVO_MILLS_BETWEEN_TICKS )
    {
        this->move_impl();
        this->last_moved_mills( mills );
    }

    return;
    */

    return;
}

uint8_t 
forge_servo::calculate_next_position( uint8_t current_pos, uint8_t target_pos )
{
    return
        ( current_pos > target_pos )
            ?
                current_pos - SERVO_MOVE_STEP_SIZE
            :   current_pos + SERVO_MOVE_STEP_SIZE
    ;
}

void
forge_servo::move_impl( uint8_t new_pos )
{
    Servo& servo = this->servo_impl();

/*
    uint8_t current_pos = servo.read();
    uint8_t target_pos  = this->target_percent_open();
        
    if ( current_pos == target_pos ) 
        return;

    uint8_t new_pos = this->calculate_next_position( current_pos, target_pos );

    this->servo_impl().write( new_pos );
    this->last_moved_mills( millis() );
*/
    servo.write( new_pos );

    return;
}

// Used during initialization to move the servo to the 0
// position
//
void
forge_servo::initialize_movement()
{
    this->last_moved_mills( millis() );
    this->move_to( SERVO_MIN );

    return;
}

