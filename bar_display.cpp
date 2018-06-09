#include "bar_display.h"
#include <ArduinoLog.h>

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
    static const int FULL_BAR_DELAY  = 1000;
    static const int END_DELAY       = 1000;
    
    ada_led_bar* bar = static_cast< ada_led_bar* >( this->ada_display() ); 

    for ( uint8_t i = 0; i < 24; ++i )
    {
        if ((i % 3) == 0)  bar->setBar( i, LED_RED    );
        if ((i % 3) == 1)  bar->setBar( i, LED_YELLOW );
        if ((i % 3) == 2)  bar->setBar( i, LED_GREEN  );
    }    
    
    bar->writeDisplay();
    delay( FULL_BAR_DELAY );

    for ( uint8_t i = 0; i < 24; ++i ) 
    {
        bar->setBar( i, LED_RED );
        bar->writeDisplay();
        delay( ANIMATION_DELAY );
        bar->setBar( i, LED_OFF );
        bar->writeDisplay();
    }
    
    for ( uint8_t i = 0; i < 24; ++i ) 
    {
        bar->setBar( i, LED_GREEN );
        bar->writeDisplay();
        delay( ANIMATION_DELAY );
        bar->setBar( i, LED_OFF );
        bar->writeDisplay();
    }

    for ( uint8_t i = 0; i < 24; ++i ) 
    {
        bar->setBar( i, LED_YELLOW );
        bar->writeDisplay();
        delay( ANIMATION_DELAY );
        bar->setBar( i, LED_OFF );
        bar->writeDisplay();
    }

    delay( END_DELAY );

    return;
}

void
bar_display::write_number_impl( uint8_t number )
{
    if ( this->number_of_leds() == 0 )
        return;

    // Map the number passed in to the number of LEDs in the bar
    //
    uint8_t num_leds = this->number_of_leds();
    uint8_t num_to_light = round( ( num_leds - 0 ) * (( number - PWM_OUTPUT_MIN )/( PWM_OUTPUT_MAX - PWM_OUTPUT_MIN )) );
    
    this->animate_leds_to( num_to_light );

    return;
}

void
bar_display::animate_leds_to( uint8_t num_to_light )
{
    Log.notice( "In bar_display::animate_leds_to with num_to_light = %d" CR, num_to_light );
    
    uint8_t difference = num_to_light - this->number_leds_lit();

    if ( 0 == difference )
    {
        Log.notice( "Bailing.  same nums" CR );
        return;  // Bail, leds are the same number as last time
    }
    else if ( difference > 0 )
    {
        this->animate_up_to( num_to_light );
    }
    else
    {
        this->animate_down_to( num_to_light );
    }

    Log.notice( "Leaving bar_display::animate_leds_to()" CR );
    return;
}

void 
bar_display::animate_up_to( uint8_t num_to_light )
{
    Log.notice( "In bar_display::animate_up_to with num_to_light = %d" CR, num_to_light );
    uint8_t num_lit = this->number_leds_lit();
    uint8_t delta   = num_to_light - num_lit;
    
    for ( int i = 0; i < delta; ++i )
    {
        Log.notice( "Turning on led %d" CR, i + num_lit );
        this->turn_on_led( i + num_lit );
        delay( ANIMATION_DELAY );
    }

    Log.notice( "Leaving bar_display::animate_up_to()" CR );
    return;
}

void 
bar_display::animate_down_to( uint8_t num_to_light )
{
    Log.notice( "In bar_display::animate_down_to() with num_to_light = " CR, num_to_light );
    uint8_t num_lit = this->number_leds_lit();
    uint8_t delta   = num_lit - num_to_light;
    
    for ( int i = 0; i < delta; ++i )
    {
        this->turn_off_led( i + num_lit );
        delay( ANIMATION_DELAY );
    }
    
    Log.notice( "Leaving bar_display::animate_down_to()" CR );
    return;
}

void 
bar_display::turn_on_led( uint8_t num_to_light )
{
    Log.notice( "In bar_display::turn_on_led() with num: %d" CR, num_to_light );
    
    ada_led_bar* bar = static_cast< ada_led_bar* >( this->ada_display() );
    
    short percent = round( ( num_to_light / this->number_of_leds() ) * 100 );

    Log.notice( "Number of LEDs in bar: %d" CR, this->number_of_leds() );
    Log.notice( "Percent is: %d" CR, percent );
    if ( percent < 6 )
    {
        bar->setBar( num_to_light, LED_YELLOW );
    }
    else if ( percent >= 6 && percent < 95 )
    {
        bar->setBar( num_to_light, LED_GREEN );
    }
    else
    {
        bar->setBar( num_to_light, LED_RED );
    }

    bar->writeDisplay();

    this->increment_number_leds_lit();

    Log.notice( "Leaving bar_display::turn_on_led()" CR );
    return;
}

void 
bar_display::turn_off_led( uint8_t pos )
{
    Log.notice( "In bar_display::turn_off_led() with pos: %d" CR, pos );
    
    ada_led_bar* bar = static_cast< ada_led_bar* >( this->ada_display() );
    
    bar->setBar( pos, LED_OFF );
    bar->writeDisplay();

    this->decrement_number_leds_lit();

    Log.notice( "Leaving bar_display::turn_off_led()" CR );
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



