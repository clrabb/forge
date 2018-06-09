#include "seven_seg_display.h"

ada_led_display*
seven_seg_display::create_display()
{
    return new ada_seven_seg();
}

void
seven_seg_display::write_number_impl( uint8_t number )
{
    ada_seven_seg* disp = static_cast< ada_seven_seg* >( this->ada_display() );

    disp->print( number, DEC );
    disp->writeDisplay();

    return;
}

void
seven_seg_display::run_tests()
{ 
    static const int TEST_NUMBER_DELAY = 100;
    static const int TEST_END_DELAY    = 1000;

    ada_seven_seg* disp = static_cast< ada_seven_seg* >( this->ada_display() );

    disp->print( 8, DEC );
    disp->writeDisplay();
    delay( TEST_NUMBER_DELAY );

    disp->print( 88, DEC );
    disp->writeDisplay();
    delay( TEST_NUMBER_DELAY );

    disp->drawColon( true );
    disp->writeDisplay();
    delay( TEST_NUMBER_DELAY );

    disp->print( 888, DEC );
    disp->drawColon( true );
    disp->writeDisplay();
    delay( TEST_NUMBER_DELAY );

    disp->print(8888, DEC);
    disp->drawColon( true );
    disp->writeDisplay();

    delay( TEST_END_DELAY );
    
    return;
}
