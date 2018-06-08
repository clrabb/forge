#ifndef BAR_DISPLAY_H
#define BAR_DISPLAY_H

#include "forge_types.h"
#include "display_led_abc.h"

static const short ANIMATION_DELAY = 10;

class bar_display : public display_led_abc
{
private:
    // Member variables
    //
    uint8_t m_number_leds     = 0;
    uint8_t m_number_leds_lit = 0;
    
public:
    // Ctor
    //
    bar_display( uint8_t num_leds );
    virtual ~bar_display() {}

    // Accessing
    //
    uint8_t number_of_leds() { return m_number_leds; }
    uint8_t number_leds_lit() { return m_number_leds_lit; }
    void number_of_leds( uint8_t number ) { m_number_leds = number; }

    // Virtual overrides
    //
    virtual void write_number( uint8_t number );

protected:
    virtual void run_tests();
    virtual ada_led_display* create_display();

private:
    // Behavior
    //
    void animate_leds_to( uint8_t pos );
    void animate_up_to( uint8_t pos );
    void animate_down_to( uint8_t pos );
    void turn_on_led( uint8_t pos );
    void turn_off_led( uint8_t pos );

private:
    // Disable compiler generated shit
    //
    bar_display( const bar_display& );
    bar_display& operator=( const bar_display& );
};

#endif // BAR_DISPLAY_H
