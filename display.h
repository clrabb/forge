#ifndef DISPLAY_H
#define DISPLAY_H

class display
{
private:
    // Member vars
    //
    unsigned long m_last_temp_display_mills = 0;
    unsigned long m_last_sp_display_mills   = 0;
    
public:
    // Ctors & dtors
    //
    display() {}

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
    display( const display& );
    display& operator=( const display& );
};

#endif // DISPLAY_H

