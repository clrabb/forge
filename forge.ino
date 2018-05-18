
#include "forge.h"
#include "singleton.h"
#include "singleton_t.h"
#include <arduino.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
//#include <PinChangeInt.h>



//#define __DEBUG__

// Constants
//
static const int GND_PIN    = 2;
static const int VCC_PIN    = 3;
static const int THERM_DO   = 8;
static const int THERM_CS   = 9;
static const int THERM_CLK  = 10;
static const long BAUD_RATE = 115200;

// Globals :[
//
Adafruit_7segment matrix = Adafruit_7segment();
forge_data d;

// Sets up LED and prints test pattern
//
void init_led()
{
    matrix.begin(0x70);

    matrix.print(8, DEC);
    matrix.writeDisplay();
    delay(100);

    matrix.print(88, DEC);
    matrix.writeDisplay();
    delay(100);

    matrix.print(888, DEC);
    matrix.writeDisplay();
    delay(100);

    matrix.print(8888, DEC);
    matrix.writeDisplay();
    delay(1000);

    return;
}


// There is some concern here regarding global vs non-global
// variables.  In general I stay away from globals like the plague.
// The arduino has a very limited memory size, though, and allocating
// and deallocating heap objects will fragment what little is there.
// Placing them on the stack is probably ok but even those frames will chew
// up memory.  I still don't know which practices are good or bad, here.
// For those reasons, and because the setup/loop style really forces the
// use of some globals, I am going to use singletons which are
// effectively globals in any case.
// -- CR 5/14/2018
//
void setup() {
    singleton_thermo::init(THERM_DO, THERM_CS, THERM_CLK);
    singleton<int> s;

    // Set up pin usage
    //
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(VCC_PIN,     OUTPUT);
    pinMode(GND_PIN,     LOW   );
    

    // Set up display
    //
    init_led();

    digitalWrite(GND_PIN, LOW);
    digitalWrite(VCC_PIN, HIGH);

    Serial.begin(BAUD_RATE);

    // wait for MAX chip to stabilize
    //
    delay(500);
}

void loop() {
    singleton_thermo* s = singleton_thermo::instance();

#ifdef __DEBUG__
    Serial.print("C = ");
    Serial.println(s->read_c());
    Serial.print("F = ");
    Serial.println(s->read_f());
#endif

    matrix.println(round(s->read_f()));
    matrix.writeDisplay();

    delay(1000);
}

