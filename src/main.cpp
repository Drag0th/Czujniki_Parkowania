#include <Arduino.h>
#include <FastLED.h>

long measureTime(int echo_pin, int trig_pin);
void measureDistance();

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
}

void loop()
{
  measureDistance();
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