#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

class button_array
{
private:
    button* m_up_button;
    button* m_dn_button;

public:
    button_array() {}

    button* get_up_button() { return m_up_button; }
    void set_up_button( button* btn ) { m_up_button = btn; }
    
    button* get_dn_button() { return m_dn_button; }
    void set_dn_button( button* btn ) { m_dn_button = btn; }

private:
    button_array( const button_array& );                // copy ctor
    button_array& operator=( const button_array& );     // assignment op
    
};

#endif
