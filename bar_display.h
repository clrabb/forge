#ifndef BAR_DISPLAY_H
#define BAR_DISPLAY_H

#include "forge_types.h"
#include "display_led_abc.h"

class bar_display : public display_led_abc
{
public:
    // Ctor
    //
    bar_display() {}
    virtual ~bar_display() {}

    virtual void run_tests();
    virtual ada_led_display* create_display();

private:
    // Disable compiler generated shit
    //
    bar_display( const bar_display& );
    bar_display& operator=( const bar_display& );
};

#endif // BAR_DISPLAY_H
