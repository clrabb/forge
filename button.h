#ifndef BUTTON_H
#define BUTTON_H

class button
{
private:
    static const unsigned long HOLD_DOWN_DELAY_INTERVAL = 500;  
    unsigned long m_initial_pressed_mills = 0; 
    short m_button_pin;
    
public:
    button( short BUTTON_PIN );
    unsigned long initial_pressed_mills() { return m_initial_pressed_mills; }
    void initial_pressed_mills( unsigned long mills ) { m_initial_pressed_mills = mills; }

    short button_pin() { return m_button_pin; }

    // Testing
    //
    bool is_pressed();
    bool is_still_pressed();
    bool is_not_pressed() { return !( this->is_pressed() ); }
    

private:
    button( const button& );
    button& operator=( const button& );
    
};

#endif // BUTTON_H
