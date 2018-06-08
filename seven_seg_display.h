#ifndef SEVEN_SEG_DISPLAY_H
#define SEVEN_SEG_DISPLAY_H

#include "display_led_abc.h"

class seven_seg_display : public display_led_abc
{
public:
    // Ctors
    //
    seven_seg_display() {}

    // Overrides
    //
    virtual ada_led_display* create_display();
    virtual void run_tests();
    void write_number( short number );

private:
    // stop compiler generated crap
    //
    seven_seg_display( const seven_seg_display& );
    seven_seg_display& operator=( const seven_seg_display& );
};

#endif // SEVEN_SEG_DISPLAY_H
