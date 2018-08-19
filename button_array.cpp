#include "button_array.h"
#include "forge_data.h"

void
button_array::update_buttons()
{
    Serial.println("in button_array::update_buttons()");
    
    this->up_button()->update();
    this->dn_button()->update();
}

