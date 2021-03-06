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
    ada_led_display* m_ada_display           = NULL;
    unsigned long    m_last_display_mills    = 0;
    int              m_last_displayed_number = 0;
    unsigned long    m_refresh_time          = 0;
    
public:
    // Ctors/dtors
    //
    display_led_abc() {}
    virtual ~display_led_abc();

    // initializing
    //
    void init( 
            uint8_t address, 
            uint8_t brightness, 
            unsigned long refresh_time = DEFAULT_DISP_REFRESH_TIME  
    );

    // Behavior
    //
    void write_number( int number );

    // Printing
    //
    virtual const char* name() = 0;

protected:
    // template methods
    // See 'design patterns', Gamma et al
    // Subclasses MUST implement these methods
    // 
    virtual ada_led_display* create_display() = 0;
    virtual void write_number_impl( int number ) = 0;

    // Accessors
    //
    ada_led_display* ada_display() { return m_ada_display; }
    
    int last_displayed_number() { return m_last_displayed_number; }
    void last_displayed_number( int number ) { m_last_displayed_number = number; }
    
    unsigned long last_display_mills() { return m_last_display_mills; }
    void last_display_mills( unsigned long mills ) { m_last_display_mills = mills; }

    // refresh times are in milliseconds 
    //
    unsigned long refresh_time() { return m_refresh_time; }
    void refresh_time( unsigned long t ) { m_refresh_time = t; }

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
