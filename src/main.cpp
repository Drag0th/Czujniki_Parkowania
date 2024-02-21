#include <Arduino.h>
#include <FastLED.h>

long measureTime(int echo_pin, int trig_pin);
void measureDistance();
void setLED(int distance);

// ultrasonic sensor defines/variables
#define sensor0_trig_pin 9
#define sensor0_echo_pin 8
#define sensor1_trig_pin 7
#define sensor1_echo_pin 6
#define sensor2_trig_pin 5
#define sensor2_echo_pin 4
#define sensor3_trig_pin 3
#define sensor3_echo_pin 2
long duration[4];
long average_duration;
int distance;

// led strip defines
#define LED_PIN 13
#define NUM_LEDS 32
#define CHIPSET WS2812
#define COLOR_ORDER RGB
#define BRIGHTNESS 128
CRGB leds[NUM_LEDS];

void setup()
{
  pinMode(sensor0_trig_pin, OUTPUT);
  pinMode(sensor1_trig_pin, OUTPUT);
  pinMode(sensor2_trig_pin, OUTPUT);
  pinMode(sensor3_trig_pin, OUTPUT);
  pinMode(sensor0_echo_pin, INPUT);
  pinMode(sensor1_echo_pin, INPUT);
  pinMode(sensor2_echo_pin, INPUT);
  pinMode(sensor3_echo_pin, INPUT);
  digitalWrite(sensor0_trig_pin, LOW);
  digitalWrite(sensor1_trig_pin, LOW);
  digitalWrite(sensor2_trig_pin, LOW);
  digitalWrite(sensor3_trig_pin, LOW);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  measureDistance();
  setLED(distance);
  FastLED.show();
}

long measureTime(int echo_pin, int trig_pin)
{
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  return pulseIn(echo_pin, HIGH);
}
void measureDistance()
{
  duration[0] = measureTime(sensor0_echo_pin, sensor0_trig_pin);
  duration[1] = measureTime(sensor1_echo_pin, sensor1_trig_pin);
  duration[2] = measureTime(sensor2_echo_pin, sensor2_trig_pin);
  duration[3] = measureTime(sensor3_echo_pin, sensor3_trig_pin);
  for (int i = 0; i < 4; i++)
  {
    average_duration = average_duration + duration[i];
  }
  distance = average_duration * 0.034 / 2;
}

void setLED(int distance)
{
  // red
  if (distance < 50)
  {
    for (int i = 0; i <= 7; i++)
    {
      leds[i] = CRGB(252, 3, 3);
    }
  }
  // orange
  else if (distance > 50 && distance < 100)
  {
    for (int i = 8; i <= 15; i++)
    {
      leds[i] = CRGB(252, 186, 3);
    }
  }
  // yellow
  else if (distance > 100 && distance < 150)
  {
    for (int i = 16; i <= 23; i++)
    {
      leds[i] = CRGB(223, 252, 3);
    }
  }
  // green
  else
  {
    for (int i = 24; i <= 31; i++)
    {
      leds[i] = CRGB(65, 252, 3);
    }
  }
}
