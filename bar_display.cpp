#include "bar_display.h"

bar_display::bar_display( uint8_t num_leds )
{
    number_of_leds( num_leds );
}

ada_led_display*
bar_display::create_display()
{
    return new ada_led_bar();
}

void 
bar_display::run_tests()
{
    static const int   FULL_BAR_DELAY  = 1000;
    static const int   END_DELAY       = 1000;
    
    ada_led_bar* bar = static_cast< ada_led_bar* >( this->ada_display() ); 

    for ( uint8_t i = 0; i < NUM_LEDS_IN_BAR; ++i )
    {
        if ((i % 3) == 0)  bar->setBar( i, LED_RED    );
        if ((i % 3) == 1)  bar->setBar( i, LED_YELLOW );
        if ((i % 3) == 2)  bar->setBar( i, LED_GREEN  );
    }    
    
    bar->writeDisplay();
    delay( FULL_BAR_DELAY );

    for ( uint8_t i = 0; i < NUM_LEDS_IN_BAR; ++i )
    {
        bar->setBar( i, LED_OFF );    
    }
    bar->writeDisplay();

    for ( uint8_t i = 0; i < NUM_LEDS_IN_BAR; ++i ) 
    {
        bar->setBar( i, LED_RED );
        bar->writeDisplay();
        delay( BAR_ANIMATION_DELAY );
        bar->setBar( i, LED_OFF );
        bar->writeDisplay();
    }
    
    for ( uint8_t i = 0; i < NUM_LEDS_IN_BAR; ++i ) 
    {
        bar->setBar( i, LED_GREEN );
        bar->writeDisplay();
        delay( BAR_ANIMATION_DELAY );
        bar->setBar( i, LED_OFF );
        bar->writeDisplay();
    }

    for ( uint8_t i = 0; i < NUM_LEDS_IN_BAR; ++i ) 
    {
        bar->setBar( i, LED_YELLOW );
        bar->writeDisplay();
        delay( BAR_ANIMATION_DELAY );
        bar->setBar( i, LED_OFF );
        bar->writeDisplay();
    }

    delay( END_DELAY );

    return;
}

void
bar_display::write_number_impl( int number )
{
    // Map the number passed in to the number of LEDs in the bar
    //
    int num_leds = this->number_of_leds();
    int mapped = map( number, PID_RANGE_MIN, PID_RANGE_MAX, 0, num_leds );
    int num_to_light = constrain( mapped, 0, num_leds );
    
    this->animate_leds_to( num_to_light );

    return;
}

void
bar_display::animate_leds_to( signed short num_to_light )
{  
    signed short difference = num_to_light - this->number_leds_lit();

    if ( difference > 0 )
    {
        this->animate_up_to( num_to_light );
    }
    else if ( difference < 0 )
    {
        this->animate_down_to( num_to_light );
    }

    // We do nothing if the difference == 0 since that LED is already
    // lit.
    
    return;
}

void 
bar_display::animate_up_to( signed short num_to_light )
{
    uint8_t num_lit = this->number_leds_lit();
    uint8_t delta   = num_to_light - num_lit;
    
    for ( int i = 0; i < delta; ++i )
    {
        this->turn_on_led( i + num_lit );
        delay( BAR_ANIMATION_DELAY );
    }

    return;
}

void 
bar_display::animate_down_to( signed short num_to_light )
{
    uint8_t num_lit = this->number_leds_lit();
    signed short delta  = static_cast< signed short>( num_lit - num_to_light );
    
    for ( int i = 0; i < delta; ++i )
    {
        this->turn_off_led( ( num_lit - i ) - 1 );
        delay( BAR_ANIMATION_DELAY );
    }
    
    return;
}

void 
bar_display::turn_on_led( signed short num_to_light )
{
    ada_led_bar* bar = static_cast< ada_led_bar* >( this->ada_display() );
    uint8_t num_leds_in_bar = this->number_of_leds();
    
    signed short percent = ( static_cast< double >( num_to_light ) / static_cast< double >( num_leds_in_bar ) ) * 100;

    if ( percent < 10 )
    {
        bar->setBar( num_to_light, LED_YELLOW );
    }
    else if ( percent >= 10 && percent < 85 )
    {
        bar->setBar( num_to_light, LED_GREEN );
    }
    else
    {
        bar->setBar( num_to_light, LED_RED );
    }

    bar->writeDisplay();

    this->increment_number_leds_lit();
    return;
}

void 
bar_display::turn_off_led( signed short pos )
{    
    ada_led_bar* bar = static_cast< ada_led_bar* >( this->ada_display() );
    
    bar->setBar( pos, LED_OFF );
    bar->writeDisplay();

    this->decrement_number_leds_lit();
    return;
}

void
bar_display::increment_number_leds_lit()
{
    this->number_leds_lit( this->number_leds_lit() + 1 );

    return;
}

void 
bar_display::decrement_number_leds_lit()
{
    this->number_leds_lit( this->number_leds_lit() - 1 );

    return;
}



