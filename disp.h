#ifndef DISP_H
#define DISP_H

class disp
{
private:
    // Member vars
    //
    unsigned long m_last_temp_display_mills = 0;
    unsigned long m_last_sp_display_mills   = 0;
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
    
    unsigned long mills_since_last_sp_display();
    double seconds_since_last_sp_display();

    // Behavior
    //
    void display_temp( signed short temp );
    void display_sp( signed short setpoint );
      
private:
    // Disable copy ctor and assignment op
    //
    disp( const disp& );
    disp& operator=( const disp& );
};

#endif // DISP_H

