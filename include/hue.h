#ifndef HUE_H
#define HUE_H

#include <leds.h>

enum HueType {
    HUE_TYPE_CONSTANT,
    HUE_TYPE_FULL_RAINBOW,
    HUE_TYPE_RING_RAINBOW,
    HUE_TYPE_RING_ALTERNATING,
    HUE_TYPE_PIXEL_ALTERNATING,
    HUE_TYPE_RING_HALF_LR,
    HUE_TYPE_MIDDLE,
};

void hue(HueType hueType, CHSV leds[NUM_LEDS]);

#endif // HUE_H