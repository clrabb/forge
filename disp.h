#ifndef DISP_H
#define DISP_H

class disp
{
private:
    // Member vars
    //
    unsigned long m_last_temp_display_mills = 0;
    unsigned long m_last_sp_display_mills   = 0;
    signed short  m_last_temp_seen          = 0;
    signed short  m_last_sp_seen            = 0;
    
    static const int BLINK_OFF_T = 700; // ms for blinking off
    static const int BLINK_ON_T  = 700; // ms for blinking on
    static const int TEMP_DISPLAY_DEBOUNCE_PERIOD = 1000;
    
public:
    // Ctors & dtors
    //
    disp() {}

    // Accessing
    //
    unsigned long mills_since_last_temp_display();
    double seconds_since_last_temp_display();
    
    unsigned long mills_since_last_sp_display();
    double seconds_since_last_sp_display();

    // Behavior
    //
    void display_temp();
    void display_setpoint();

private:
    void last_temp_display_mills( unsigned long mills ) 
        { m_last_temp_display_mills = mills; }
  
    void last_sp_dipslay_mills( unsigned long mills )
        { m_last_sp_display_mills = mills; } 

    void last_sp_seen( signed short sp ) { m_last_sp_seen = sp; }
    signed short last_sp_seen() { return m_last_sp_seen; }
    
    void last_temp_seen( signed short temp ) { m_last_temp_seen = temp; }
    signed short last_temp_seen() { return m_last_temp_seen; }

    void print( int number );
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

