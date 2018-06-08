#include "seven_seg_display.h"

ada_led_display*
seven_seg_display::create_display()
{
    return new ada_seven_seg();
}

void
seven_seg_display::run_tests()
{
    // Do stuff here
}

