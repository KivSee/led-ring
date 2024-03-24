#include <hue.h>

void hue(HueType hueType, CHSV leds[NUM_LEDS]) {
    uint8_t gHue = millis() / 30;

    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i].h = 0;
        leds[i].s = 255;
        leds[i].v = 0;
    }

    switch (hueType) {
        case HueType::HUE_TYPE_CONSTANT:
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = gHue;
            }
            break;

        case HueType::HUE_TYPE_FULL_RAINBOW:
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = gHue + (i * 256 / NUM_LEDS);
            }
            break;

        case HueType::HUE_TYPE_RING_RAINBOW:
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = gHue + (i * 256 / NUM_RINGS);
            }
            break;

        case HueType::HUE_TYPE_RING_ALTERNATING:
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = gHue + ((i / NUM_RINGS) % 2 == 0 ? 0 : 128);
            }
            break;

        case HueType::HUE_TYPE_PIXEL_ALTERNATING:
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = gHue + (i % 2 == 0 ? 0 : 64);
            }
            break;

        case HueType::HUE_TYPE_RING_HALF_LR:
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].h = gHue + ((i % NUM_RINGS) < NUM_RINGS / 2 ? 0 : 64);
            }
            break;

        case HueType::HUE_TYPE_MIDDLE:
            for (int i = 0; i < NUM_LEDS; i++) {
                int ri = i % NUM_RINGS;
                uint8_t h = gHue;
                if (ri == 3 || ri == 9) {
                    h = gHue + 64;
                } else if (ri == 2 || ri == 4 || ri == 8 || ri == 10) {
                    h = gHue + 32;
                }
                leds[i].h = h;
            }
            break;
    }
}