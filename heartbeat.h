#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <Arduino.h>

// The ENTIRE purpose of this class is to not do a delay() for the flashing of the led.
// I don't know if this will work or not but I'm trying to remove all calls to delay().
// The idea here is that we'll turn on the LED one time through the main loop
// and then each subsequent time check to see if it's time to shut it off.
// The alternative is to write something like:
//
// digitalWrite( pin, HIGH );
// delay( 50 );
// digitialWrite( pin, LOW );
//
// the problem with this is you are pausing the entire arduino for 50 milliseconds when
// it could be doing other things.
//
class heartbeat
{
  private:
    unsigned long m_last_state_change_mills  = 0;
    uint8_t       m_led_pin                  = 0;
    unsigned long m_mills_between_beats      = 0;
    unsigned long m_beat_length_mills        = 0;

  public:
    // Ctor
    //
    heartbeat( uint8_t led_pin, unsigned long mills_between_beats, unsigned long beat_length_mills );

    // Accessors
    //
    unsigned long last_state_change_mills() {
      return m_last_state_change_mills;
    }
    void last_state_change_mills( unsigned long mills ) {
      m_last_state_change_mills = mills;
    }

    uint8_t led_pin() {
      return m_led_pin;
    }
    void led_pin( uint8_t pin ) {
      m_led_pin = pin;
    }

    unsigned long mills_between_beats() {
      return m_mills_between_beats;
    }
    void mills_between_beats( unsigned long mills ) {
      m_mills_between_beats = mills;
    }

    unsigned long beat_length_mills() {
      return m_beat_length_mills;
    }
    void beat_length_mills( unsigned long mills ) {
      m_beat_length_mills = mills;
    }

    // Behavior
    //
    void beat();
    void off_beat();
    void on_beat();
    void turn_on();
    void turn_off();

    // Testing
    //
    bool is_on();
    bool is_off();
    unsigned long time_on();
    unsigned long time_off();


  private:
    // Disable compiler generated crap
    //
    heartbeat( const heartbeat& );
    heartbeat& operator=( const heartbeat& );
};

#endif // HEARTBEAH_H
