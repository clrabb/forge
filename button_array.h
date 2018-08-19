#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include "button.h"

class button_array
{
private:
    button* m_up_button;
    button* m_dn_button;

public:
    button_array() {}

    button* up_button() { return m_up_button; }
    void up_button( button* btn ) { m_up_button = btn; }
    
    button* dn_button() { return m_dn_button; }
    void dn_button( button* btn ) { m_dn_button = btn; }

    void update_buttons();

private:
    button_array( const button_array& );                // copy ctor
    button_array& operator=( const button_array& );     // assignment op
    
};

#endif
