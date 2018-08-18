#include "up_button.h"
#include "forge_data.h"
#include "singleton_t.h"

up_button::up_button( short pin )
       : button( pin )
    {}

void
up_button::update_data_impl()
{
    forge_data& fd = singleton_t< forge_data >::instance();

    fd.increment_setpoint();

    return;
}


