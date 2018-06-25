#ifndef BUTTON_H
#define BUTTON_H

class button
{
private:
    static const unsigned long DEFAULT_VALUE_CHANGE_DELAY = 500;
  
    unsigned long m_last_pressed_mills = 0;
    unsigned long m_mills_between_value_change = 0;  
    
public:
    button();
    unsigned long last_pressed_mills() { return m_last_pressed_mills; }
    void last_pressed_mills( unsigned long mills ) { m_last_pressed_mills = mills; }

    // Testing
    //
    bool is_pressed();
    bool is_being_held_down();
    

private:
    button( const button& );
    button& operator=( const button& );
    
};

#endif // BUTTON_H
