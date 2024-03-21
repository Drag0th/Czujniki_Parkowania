#include <Arduino.h>
#include <FastLED.h>

long measureTime(int echo_pin, int trig_pin);
void measureDistance();
void setSystem(int distance);

// ultrasonic sensor defines/variables
#define sensor0_trig_pin 5
#define sensor0_echo_pin 6
#define sensor1_trig_pin 16
#define sensor1_echo_pin 17
#define sensor2_trig_pin 18
#define sensor2_echo_pin 19
#define sensor3_trig_pin 20
#define sensor3_echo_pin 21
long duration[4];
long average_duration;
int distance;

// led strip defines
#define LED_PIN 12
#define NUM_LEDS 32
#define CHIPSET WS2812
#define COLOR_ORDER RGB
#define BRIGHTNESS 128
CRGB leds[NUM_LEDS];

// buzzer defines
#define BUZZER_PIN 3

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

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
  measureDistance();
  setSystem(distance);
  FastLED.show();
}

long measureTime(int echo_pin, int trig_pin)
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  return pulseIn(echo_pin, HIGH);
}
void measureDistance()
{
  duration[0] = measureTime(sensor0_echo_pin, sensor0_trig_pin);
  // duration[1] = measureTime(sensor1_echo_pin, sensor1_trig_pin);
  // duration[2] = measureTime(sensor2_echo_pin, sensor2_trig_pin);
  // duration[3] = measureTime(sensor3_echo_pin, sensor3_trig_pin);
  // for (int i = 0; i < 4; i++)
  //{
  average_duration = duration[0];
  //}
  distance = average_duration * 0.034 / 2;
}

void setSystem(int distance)
{
  // red
  FastLED.clear();
  if (distance > 30 && distance < 40)
  {
    for (int i = 0; i <= 1; i++)
    {
      leds[i] = CRGB(252, 3, 3);
    }
    analogWrite(BUZZER_PIN, 0);
    delay(500);
    analogWrite(BUZZER_PIN, 50);
    delay(100);
    analogWrite(BUZZER_PIN, 0);
  }
  // orange
  else if (distance > 20 && distance < 30)
  {
    FastLED.clear();
    for (int i = 0; i <= 1; i++)
    {
      leds[i] = CRGB(252, 3, 3);
    }
    for (int i = 2; i <= 3; i++)
    {
      leds[i] = CRGB(252, 186, 3);
    }

    analogWrite(BUZZER_PIN, 0);
    delay(400);
    analogWrite(BUZZER_PIN, 100);
    delay(100);
    analogWrite(BUZZER_PIN, 0);
  }
  // yellow
  else if (distance > 10 && distance < 20)
  {
    FastLED.clear();
    for (int i = 0; i <= 1; i++)
    {
      leds[i] = CRGB(252, 3, 3);
    }
    for (int i = 2; i <= 3; i++)
    {
      leds[i] = CRGB(252, 186, 3);
    }
    for (int i = 4; i <= 5; i++)
    {
      leds[i] = CRGB(223, 252, 3);
    }
    analogWrite(BUZZER_PIN, 0);
    delay(300);
    analogWrite(BUZZER_PIN, 200);
    delay(100);
    analogWrite(BUZZER_PIN, 0);
  }
  // green
  else if (distance > 0 && distance < 10)
  {
    FastLED.clear();
    for (int i = 0; i <= 1; i++)
    {
      leds[i] = CRGB(252, 3, 3);
    }
    for (int i = 2; i <= 3; i++)
    {
      leds[i] = CRGB(252, 186, 3);
    }
    for (int i = 4; i <= 5; i++)
    {
      leds[i] = CRGB(223, 252, 3);
    }
    for (int i = 6; i <= 7; i++)
    {
      leds[i] = CRGB(65, 252, 3);
    }

    analogWrite(BUZZER_PIN, 250);
    }
  // too far > 50cm
  else
  {
    FastLED.clear();
    analogWrite(BUZZER_PIN, 0);
  }
}