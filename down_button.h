#ifndef DOWN_BUTTON_H
#define DOWN_BUTTON_H

#include "button.h"

class down_button : public button
{
public:
    down_button( short pin );

public:
    virtual void update_setpoint();
    
private:
    down_button( const down_button& );            // COPY CTOR
    down_button& operator=( const down_button& ); // ASSIGNMENT OP
 

};

#endif // DOWN_BUTTON_H
