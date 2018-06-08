#ifndef DISPLAY_LED_ABC
#define DISPLAY_LED_ABC

#include "forge_types.h"


// Abstract base class for the various display
// leds in use
//
class display_led_abc
{
private:
    // Member Vars
    ada_led_display* m_ada_display = NULL;
    
public:
    // Ctors/dtors
    //
    display_led_abc() {}
    virtual ~display_led_abc();

    // initializing
    //
    void init( uint8_t address, uint8_t brightness );

    // Behavior
    //
    virtual void write_number( uint8_t number ) = 0; 

protected:
    // template methods
    // See 'design patterns', Gamma et al
    // Subclasses MUST implement this method
    // to return the type of backpack they are 
    //
    virtual ada_led_display* create_display() = 0;

    // Accessors
    //
    ada_led_display* ada_display() { return m_ada_display; }

    // Testing displays
    //
    virtual void run_tests() = 0;
    

private:
    // Disable copy ctor and assignment
    // operator
    display_led_abc( const display_led_abc& );
    display_led_abc& operator=( const display_led_abc& ); 

    // Set the display pointer to something.
    // This is used in init()
    //
    void ada_display( ada_led_display* disp ) { m_ada_display = disp; }
};


#endif // DISPLAY_LED_ABC
