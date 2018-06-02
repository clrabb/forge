#ifndef DISP_H
#define DISP_H

class disp
{
private:
    // Member vars
    //
    unsigned long m_last_temp_display_mills     = 0;
    unsigned long m_last_setpoint_display_mills = 0;
    signed short  m_last_temp_seen              = 0;
    signed short  m_last_setpoint_seen          = 0;
    
    static const int BLINK_OFF_T = 700; // ms for blinking off
    static const int BLINK_ON_T  = 700; // ms for blinking on
    
public:
    // Ctors & dtors
    //
    disp() {}

    // Accessing
    //
    unsigned long mills_since_last_temp_display();
    double seconds_since_last_temp_display();
    
    unsigned long mills_since_last_setpoint_display();
    double seconds_since_last_setpoint_display();

    // Behavior
    //
    void display();

private:

    void display_setpoint_if_changing();
    void display_temp();
    void flash_setpoint_if_off();
    
    void last_temp_display_mills( unsigned long mills ) 
        { m_last_temp_display_mills = mills; }
  
    void last_setpoint_dipslay_mills( unsigned long mills )
        { m_last_setpoint_display_mills = mills; } 

    void last_setpoint_seen( signed short sp ) { m_last_setpoint_seen = sp; }
    signed short last_setpoint_seen() { return m_last_setpoint_seen; }
    
    void last_temp_seen( signed short temp ) { m_last_temp_seen = temp; }
    signed short last_temp_seen() { return m_last_temp_seen; }

    bool is_too_soon_temp_display();
    bool is_same_temp_temp_display();
    bool is_joe_fiddling_sp();

    void print( int number );
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

