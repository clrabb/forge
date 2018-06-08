#ifndef BAR_DISPLAY_H
#define BAR_DISPLAY_H

class bar_display : public display_led_abc
{
public:
    // Ctor
    //
    bar_display() {}

private:
    // Disable compiler generated shit
    //
    bar_display( const bar_display& );
    bar_display& operator=( const bar_display& );
    
};

#endif // BAR_DISPLAY_H
