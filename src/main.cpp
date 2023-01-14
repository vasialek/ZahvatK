#include <Arduino.h>
#include <FastLED.h>
// #include "randomprovider.h"

#define DATA_PIN 7
#define NUM_LEDS 6

// RandomProvider _randomProvider;
int getRandomDirection();
int getRandomWind();
CRGB windToColor(int wind);

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);

  // Seed random
  randomSeed(analogRead(0));
}

void loop()
{
  auto direction = getRandomDirection();
  auto color = windToColor(getRandomWind());
  leds[direction] = color;
  FastLED.show();
  delay(3000);

  // Now turn the LED off, then pause
  leds[direction] = CRGB::Black;
  FastLED.show();
  delay(3000);
}

int getRandomDirection()
{
  auto direction = random(NUM_LEDS);
  return direction;
  // return _randomProvider.Random(NUM_LEDS);
}

int getRandomWind()
{
  auto wind = random(14);
  return wind;
}

CRGB windToColor(int wind)
{
  switch (wind)
  {
  case 0:
    return CRGB::Yellow;
  case 1:
  case 5:
    return CRGB::Red;
  default:
    return CRGB::Green;
  }
}
