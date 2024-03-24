#include <FastLED.h>

#include <leds.h>
#include <hue.h>
#include <pattern.h>
#include <phase.h>
#include <mix.h>

FASTLED_USING_NAMESPACE

CHSV leds[NUM_LEDS];
CRGB ledsRgb[NUM_LEDS];
CRGB ledsPhased[NUM_LEDS];

Mix mix = getRandomMix();

// void rainbow() 
// {
//   // FastLED's built-in rainbow generator
//   fill_rainbow( leds, NUM_LEDS, gHue, 7);
// }

// void addGlitter( fract8 chanceOfGlitter) 
// {
//   if( random8() < chanceOfGlitter) {
//     leds[ random16(NUM_LEDS) ] += CRGB::White;
//   }
// }

// void rainbowWithGlitter() 
// {
//   // built-in FastLED rainbow, plus some random sparkly glitter
//   rainbow();
//   addGlitter(80);
// }

// void confetti() 
// {
//   // random colored speckles that blink in and fade smoothly
//   fadeToBlackBy( leds, NUM_LEDS, 10);
//   int pos = random16(NUM_LEDS);
//   leds[pos] += CHSV( gHue + random8(64), 200, 255);
// }

// void sinelon()
// {
//   // a colored dot sweeping back and forth, with fading trails
//   fadeToBlackBy( leds, NUM_LEDS, 20);
//   int pos = (millis() / 15) % 144;
//   // int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//   leds[pos] += CHSV( gHue, 255, 192);
// }

// void bpm()
// {
//   // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
//   uint8_t BeatsPerMinute = 62;
//   CRGBPalette16 palette = PartyColors_p;
//   uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
//   for( int i = 0; i < NUM_LEDS; i++) { //9948
//     leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
//   }
// }

// void juggle() {
//   // eight colored dots, weaving in and out of sync with each other
//   fadeToBlackBy( leds, NUM_LEDS, 20);
//   uint8_t dothue = 0;
//   for( int i = 0; i < 8; i++) {
//     leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
//     dothue += 32;
//   }
// }

// void dot() {
//   fadeToBlackBy( leds, NUM_LEDS, 20);
//   for(int r=0; r<12; r++) {
//     int start = r*12;
//     int offset = beatsin16( 15, 0, 11 );
//     leds[start + offset] = CHSV(gHue + r * (256/12), 200, 255);
//   }
// }

// void dot() {
//   fill_solid(leds, NUM_LEDS, CRGB::Black);
//   int offset = (millis() / 100) % 12;
//   for(int r=0; r<12; r++) {
//     int start = r*12;
//     leds[start + offset] = CHSV(gHue + r * (256/12), 200, 255);
//   }
// }

// void circle() {
//   int offset = (millis() / 100) % 12;
//   fadeToBlackBy( leds, NUM_LEDS, 128);
//   for(int r=0; r<12; r++) {
//     int start = r*12;
//     // int index = r % 2 == 0 ? 11 - offset : offset;
//     int index = offset;
//     int hue = r % 2 == 0 ? gHue : gHue + 128;
//     leds[start + index] = CHSV(hue, 200, 255);
//   }
// }

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  mix = getRandomMix();
}

void setup() {
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(ledsPhased, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{

  hue(mix.hueType, leds);
  // Call the current pattern function once, updating the 'leds' array
  pattern(mix.patternType, leds);
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsRgb[i] = leds[i];
  }
  phase(mix.phaseType, ledsRgb, ledsPhased);

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

  EVERY_N_SECONDS( 15 ) { nextPattern(); } // change patterns periodically
}
