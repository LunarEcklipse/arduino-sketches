/* This sketch uses the NewPing.h library. Make sure you have it installed! 

Sketch by Kaden Duncan-Matis, Created on January 15, 2024. Licensed under the GNU GPL-3.0.

*/

#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200 // The maximum distance in centimeters 
#define GREEN_PIN 2
#define YELLOW_PIN 3
#define RED_PIN 4

#define MIN_SONAR_DISTANCE 8 // The distance from 0 where the sonar has a red light
#define MAX_SONAR_DISTANCE 30 // The distance after which the sonar has a green light. Anything in between the min and max will be yellow.

#define RED 0
#define YELLOW 1
#define GREEN 2

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distanceAway;
int color; // 0 = red, 1 = yellow, 2 = green

int determineLightColorByDistance(int distance)
{
  if (distance <= MIN_SONAR_DISTANCE)
  {
    return RED;
  }
  else if (distance > MAX_SONAR_DISTANCE)
  {
    return GREEN;
  }
  return YELLOW;
}

void setLight(int color)
{
  switch(color)
  {
    case RED:
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(RED_PIN, HIGH);
      break;
    case YELLOW:
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(RED_PIN, LOW);
      break;
    case GREEN:
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(RED_PIN, LOW);
      break;
  }
}

// This function was included in the code for anyone who wants to experiment with this using inches instead of centimeters. It is not used in this example here.
float convertCmToInches(float cm)
{
  return cm / 2.54f;
}

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  delay(50);
  distanceAway = sonar.ping_cm();
  color = determineLightColorByDistance(distanceAway);
  setLight(color);
}
