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

    return;
}

// Initializing
//

void 
disp::init_setpoint_led()
{    
    seven_seg_display* sp_display = this->setpoint_display();
    sp_display->init( SP_DISP_ADDR, SP_DISP_BRIGHTNESS, SP_DISP_REFRESH_TIME );

    return;
}

void
disp::init_heartbeat_led()
{
    m_heartbeat_led = new heartbeat( HEARTBEAT_LED_PIN, HEARTBEAT_DURATION_OFF, HEARTBEAT_DURATION_ON );

    return;
}

void
disp::init_temp_led()
{
    seven_seg_display* temp_display = this->temp_display();
    temp_display->init( TEMP_DISP_ADDR, TEMP_DISP_BRIGHTNESS, TEMP_DISP_REFRESH_TIME );

    return;
}

void
disp::init_led_bar()
{
    bar_display* bar = this->output_bar();
    bar->init( VALVE_DISP_ADDR, VALVE_DISP_BRIGHTNESS, VALVE_DISP_REFRESH_TIME );

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
    this->init_heartbeat_led();

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
   this->display_heartbeat();
   
   return;
}

void 
disp::display_heartbeat()
{
#ifdef __DEBUG__
    Serial.println( "In disp::display_heartbeat()" );
#endif 
    this->heartbeat_led()->beat();

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

