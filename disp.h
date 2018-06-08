#ifndef DISP_H
#define DISP_H

#include "forge_types.h"
#include "forge_data.h"


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
    ada_seven_seg     m_temp_display;
    ada_seven_seg     m_setpoint_display;
    ada_led_bar       m_output_bar;
    unsigned long m_last_temp_display_mills       = 0;
    unsigned long m_last_setpoint_display_mills   = 0;
    unsigned long m_last_pid_output_display_mills = 0;
    short         m_last_pid_output_seen          = 0;
    temp_t        m_last_temp_seen                = 0;
    temp_t        m_last_setpoint_seen            = 0;
    
public:
    // Ctors & dtors
    //
    disp();

    // Accessing
    //
    unsigned long mills_since_last_temp_display();
    double seconds_since_last_temp_display();
    
    unsigned long mills_since_last_setpoint_display();
    double seconds_since_last_setpoint_display();

    // Behavior
    //
    void display();
    void init();
    

private:    

    ada_led_bar& led_output_bar() { return m_output_bar; }
    ada_seven_seg& setpoint_display() { return m_setpoint_display; }
    ada_seven_seg& temp_display() { return m_temp_display; }
    
    void last_temp_display_mills( unsigned long mills ) 
        { m_last_temp_display_mills = mills; }

    unsigned long last_temp_display_mills()
        { return m_last_temp_display_mills; }
  
    void last_setpoint_display_mills( unsigned long mills )
        { m_last_setpoint_display_mills = mills; } 

    unsigned long last_setpoint_display_mills()
        { return m_last_setpoint_display_mills; }

    void last_setpoint_seen( setpoint_t sp ) { m_last_setpoint_seen = sp; }
    setpoint_t last_setpoint_seen() { return m_last_setpoint_seen; }
    
    void last_temp_seen( temp_t temp ) { m_last_temp_seen = temp; }
    temp_t last_temp_seen() { return m_last_temp_seen; }

    void last_pid_output_seen( short pid_output ) { m_last_pid_output_seen = pid_output; }
    short last_pid_output_seen() { return m_last_pid_output_seen; }

    void last_pid_output_display_mills( unsigned long mills )
        { m_last_pid_output_display_mills = mills; }

    unsigned long last_pid_output_display_mills() 
        { return m_last_pid_output_display_mills; }

    void init_displays();
    void init_led_bar();
    void init_temp_led();
    void init_setpoint_led();

    bool is_too_soon_display( unsigned long last_display_mills );
    bool is_same_temp_as_last_display();
    bool is_same_setpoint_as_last_display();
    bool is_same_pid_output_as_last_display();
    
    void display_temp();
    void display_setpoint();
    void display_pid_output();

    void break_number( int number, int& tens, int& ones );
    
    void display_temp_impl( temp_t temp );
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

