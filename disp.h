#ifndef DISP_H
#define DISP_H

#include "forge_types.h"
#include "forge_data.h"
#include "seven_seg_display.h"
#include "bar_display.h"


class disp
{
private:

    // Debouncing period
    // We don't re-display something that we'eve
    // already displayed this number of milliseconds
    // ago 
    //
    static const int DISPLAY_DEBOUNCE_MILLS = 1000;

    // Number of leds in the bar 
    //
    static const int NUM_BAR_LEDS = 24;
    
    // Member vars
    //
    seven_seg_display* m_temp_display;
    seven_seg_display* m_setpoint_display;
    bar_display*       m_output_bar;
    
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
    
    void init_displays();
    void init_led_bar();
    void init_temp_led();
    void init_setpoint_led();
    
    void display_temp();
    void display_setpoint();
    void display_pid_output();
    
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

