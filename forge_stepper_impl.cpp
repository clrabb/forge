#include "forge_stepper_impl.h"
#include "forge_types.h"
/*
void 
forge_stepper_impl::step_open()
{
    uint8_t next_step = this->current_step() + 1;
    this->step_impl( next_step );
    this->current_step( next_step );

    return;
}

void 
forge_stepper_impl::step_closed()
{
    uint8_t next_step = this->current_step() - 1;
    this->step_impl( next_step );
    this->current_step( next_step );

    return;
}


// This one may take some time to get your head around until you realize
// there are four coils on the stator inside the stepper.  energizing them in a
// certain sequence makes the rotor, which is magnetized move in a direction.
// You can see the coils being energized in the various 'digitalWrite()' calls
// here.
// 
void
forge_stepper_impl::step_impl( uint8_t step )
{
    switch( step )
    {
        case 0:
            digitalWrite(FSTEPPER_PIN1, LOW); 
            digitalWrite(FSTEPPER_PIN2, LOW);
            digitalWrite(FSTEPPER_PIN3, LOW);
            digitalWrite(FSTEPPER_PIN4, HIGH);
        break; 
       
        case 1:
            digitalWrite(FSTEPPER_PIN1, LOW); 
            digitalWrite(FSTEPPER_PIN2, LOW);
            digitalWrite(FSTEPPER_PIN3, HIGH);
            digitalWrite(FSTEPPER_PIN4, HIGH);
        break; 
   
        case 2:
            digitalWrite(FSTEPPER_PIN1, LOW); 
            digitalWrite(FSTEPPER_PIN2, LOW);
            digitalWrite(FSTEPPER_PIN3, HIGH);
            digitalWrite(FSTEPPER_PIN4, LOW);
        break; 
   
        case 3:
            digitalWrite(FSTEPPER_PIN1, LOW); 
            digitalWrite(FSTEPPER_PIN2, HIGH);
            digitalWrite(FSTEPPER_PIN3, HIGH);
            digitalWrite(FSTEPPER_PIN4, LOW);
        break; 
   
        case 4:
            digitalWrite(FSTEPPER_PIN1, LOW); 
            digitalWrite(FSTEPPER_PIN2, HIGH);
            digitalWrite(FSTEPPER_PIN3, LOW);
            digitalWrite(FSTEPPER_PIN4, LOW);
        break; 
   
        case 5:
            digitalWrite(FSTEPPER_PIN1, HIGH); 
            digitalWrite(FSTEPPER_PIN2, HIGH);
            digitalWrite(FSTEPPER_PIN3, LOW);
            digitalWrite(FSTEPPER_PIN4, LOW);
        break; 
     
        case 6:
            digitalWrite(FSTEPPER_PIN1, HIGH); 
            digitalWrite(FSTEPPER_PIN2, LOW);
            digitalWrite(FSTEPPER_PIN3, LOW);
            digitalWrite(FSTEPPER_PIN4, LOW);
   
        break; 
       
        case 7:
            digitalWrite(FSTEPPER_PIN1, HIGH); 
            digitalWrite(FSTEPPER_PIN2, LOW);
            digitalWrite(FSTEPPER_PIN3, LOW);
            digitalWrite(FSTEPPER_PIN4, HIGH);
        break; 
   
        default:
            digitalWrite(FSTEPPER_PIN1, LOW); 
            digitalWrite(FSTEPPER_PIN2, LOW);
            digitalWrite(FSTEPPER_PIN3, LOW);
            digitalWrite(FSTEPPER_PIN4, LOW);
        break; 
    }

    return;
}

void
stepper_step_open::step( forge_stepper_impl& stepper )
{
    stepper.step_open();
}

void 
stepper_step_closed::step( forge_stepper_impl& stepper )
{
    stepper.step_closed()
}
*/

