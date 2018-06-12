#include "disp.h"
#include "singleton_t.h"
#include "forge_types.h"
#include "forge_data.h"
#include "thermoc.h"
#include "forge_pid.h"
#include <arduino.h>



// Construction
disp::disp() 
{
    m_temp_display = new seven_seg_display();
    m_setpoint_display = new seven_seg_display();
    m_output_bar = new bar_display( NUM_LEDS_IN_BAR );
}

// Initializing
//

void 
disp::init_setpoint_led()
{
    seven_seg_display* sp_display = this->setpoint_display();
    sp_display->init( BLUE_LED_ADDR, BLUE_LED_BRIGHTNESS );

    return;
}

void
disp::init_temp_led()
{
    seven_seg_display* temp_display = this->temp_display();
    temp_display->init( RED_LED_ADDR, RED_LED_BRIGHTNESS );

    return;
}

void
disp::init_led_bar()
{
    bar_display* bar = this->output_bar();
    bar->init( LED_BAR_ADDR, LED_BAR_BRIGHTNESS );

    return;
}

void
disp::init()
{
    this->init_displays();

    return;
}

void
disp::init_displays()
{
    this->init_led_bar();
    this->init_temp_led();
    this->init_setpoint_led();

    return;
}

// Main calling point from loop()
//
void
disp::display()
{
   this->display_temp();
   this->display_setpoint();
   this->display_pid_output();
   
   return;
}

void
disp::display_pid_output()
{   
    forge_data& fd = singleton_t< forge_data >::instance();
    bar_display* bar = this->output_bar();

    bar->write_number( fd.current_pid_output() );

    return;
}

void
disp::display_setpoint()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    seven_seg_display* disp = this->setpoint_display();
    disp->write_number( fd.setpoint() );

    return;
}

void 
disp::display_temp()
{
    forge_data& fd = singleton_t< forge_data >::instance();
    seven_seg_display* disp = this->temp_display();
    disp->write_number( fd.current_temp() );
    
    return;
}

