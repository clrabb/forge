#ifndef STEPPER_STEP_H
#define STEPPER_STEP_H

#include "forge_stepper_impl.h"

class stepper_step_abc
{
    virtual void step( forge_stepper_impl& ) = 0;
};

class stepper_step_open : public stepper_step_abc
{
    virtual void step( forge_stepper_impl& stepper ) { stepper.step_open(); }
};

class stepper_step_closed : public stepper_step_abc
{
    virtual void step( forge_stepper_impl& stepper ) { stepper.step_closed(); }
};

#endif 
