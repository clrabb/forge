
// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "arduino.h"
#include "max6675.h"
#include "singleton.h"

static const int thermoDO   = 4;
static const int thermoCS   = 7;
static const int thermoCLK  = 9;

static const int VCC_PIN     = 3;
static const int GND_PIN     = 2;

static const long BAUD_RATE = 115200;

void setup() {
    singleton_thermo::init(thermoDO, thermoCS, thermoCLK);

    // Setup pin usage
    //
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(VCC_PIN,     OUTPUT);
    pinMode(GND_PIN,     LOW   );


    digitalWrite(GND_PIN, LOW);
    digitalWrite(VCC_PIN, HIGH);

    Serial.begin(BAUD_RATE);

    // wait for MAX chip to stabilize
    delay(500);
}

void loop() {
    singleton_thermo& s = singleton_thermo::instance();

    Serial.print("C = ");
    Serial.println(s.read_c());
    Serial.print("F = ");
    Serial.println(s.read_f());

    delay(1000);
}

