#ifndef DISP_H
#define DISP_H

#include "forge_types.h"
#include "forge_data.h"
#include "seven_seg_display.h"
#include "bar_display.h"
#include "heartbeat.h"


class disp
{
private:
    // Member vars
    //
    seven_seg_display* m_temp_display;
    seven_seg_display* m_setpoint_display;
    bar_display*       m_output_bar;
    heartbeat*         m_heartbeat_led;
    
public:
    // Ctors & dtors
    //
    disp();

    // Behavior
    //
    void display();
    void init();
    

private:    

    bar_display* output_bar() { return m_output_bar; }
    seven_seg_display* setpoint_display() { return m_setpoint_display; }
    seven_seg_display* temp_display() { return m_temp_display; }
    heartbeat* heartbeat_led() { return m_heartbeat_led; }
    
    void init_displays();
    void init_led_bar();
    void init_temp_led(); 
    void init_setpoint_led();
    void init_heartbeat_led();
    
    void display_temp();
    void display_setpoint();
    void display_pid_output();
    void display_heartbeat();
    
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

