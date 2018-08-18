#include "button_state.h"

button_state*
button_state_pushed::update_setpoint()
{
    return this;
}

button_state*
button_state_unpushed::update_setpoint()
{
    return this;
}

button_state*
button_state_latched::update_setpoint()
{
    return this;
}

