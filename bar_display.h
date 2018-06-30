#ifndef BAR_DISPLAY_H
#define BAR_DISPLAY_H

#include "forge_types.h"
#include "display_led_abc.h"


class bar_display : public display_led_abc
{
public:
    static const short ANIMATION_DELAY = 0;
    
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

    virtual const char* name() { return "BAR_DISPLAY"; }


protected:
    // Virtual overrides
    //
    virtual void write_number_impl( int number );
    virtual void run_tests();
    virtual ada_led_display* create_display();
    virtual void increment_number_leds_lit();
    virtual void decrement_number_leds_lit();

private:
    // Accessing
    //
    void number_leds_lit( uint8_t num ) { m_number_leds_lit = num; }
    
    // Behavior
    //
    void animate_leds_to( signed short pos );
    void animate_up_to( signed short pos );
    void animate_down_to( signed short pos );
    void turn_on_led( signed short pos );
    void turn_off_led( signed short pos );

private:
    // Disable compiler generated shit
    //
    bar_display( const bar_display& );
    bar_display& operator=( const bar_display& );
};

#endif // BAR_DISPLAY_H
