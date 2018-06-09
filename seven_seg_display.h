#ifndef SEVEN_SEG_DISPLAY_H
#define SEVEN_SEG_DISPLAY_H

#include "display_led_abc.h"

class seven_seg_display : public display_led_abc
{
public:
    // Ctors
    //
    seven_seg_display() {}

    virtual const char* name() { return "SEVEN_SEG_DISPLAY"; }


protected:
    virtual ada_led_display* create_display();
    virtual void run_tests();
    virtual void write_number_impl( uint8_t number );

private:
    // stop compiler generated crap
    //
    seven_seg_display( const seven_seg_display& );
    seven_seg_display& operator=( const seven_seg_display& );
};

#endif // SEVEN_SEG_DISPLAY_H
