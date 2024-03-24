#ifndef PHASE_H
#define PHASE_H

#include <FastLED.h>
#include <leds.h>

enum PhaseType {
  PHASE_TYPE_NO_PHASE,
  PHASE_TYPE_CYCLIC,
  PHASE_TYPE_ALTERNATE,
  PHASE_TYPE_DOUBLE,
  PHASE_TYPE_ALTERNATE_REVERSE,
};

PhaseType randomPhaseType();

// Phase applies a phase transformation to the src array and stores the result in the dest array
// the phase is static and is determined by the phaseType.
// the phase is not time dependent.
// phase is ring index dependent.
void phase(PhaseType phaseType, CRGB src[NUM_LEDS], CRGB dest[NUM_LEDS]);

#endif