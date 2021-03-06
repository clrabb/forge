#ifndef UP_BUTTON_H
#define UP_BUTTON_H

#include "button.h"

class up_button : public button
{
public:
    up_button( short pin );

public:
    virtual void update_setpoint();

    
private:
    up_button( const up_button& ); // COPY CTOR
    up_button& operator=( const up_button& ); // ASSIGNMENT OP  
};

#endif // UP_BUTTON_H
