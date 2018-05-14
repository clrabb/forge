
// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "arduino.h"
#include "max6675.h"

static const int thermoDO  = 4;
static const int thermoCS  = 7;
static const int thermoCLK = 9;
static const int TOO_HOT = 105;
static const long BAUD_RATE = 115200;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

void setup() {
  // Set up simple indicator
  //
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(BAUD_RATE);
  // use Arduino pins
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp

   Serial.print("C = ");
   Serial.println(thermocouple.readCelsius());
   Serial.print("F = ");
   Serial.println(thermocouple.readFahrenheit());

   if (thermocouple.readFahrenheit() >= TOO_HOT)
   {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("HOT HOT HOT");
   }
   else
   {
      digitalWrite(LED_BUILTIN, LOW);
   }

   delay(1000);
}

