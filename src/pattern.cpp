#include <pattern.h>

uint8_t upPixels[] = {
    4, 5, 6, 7, 8, 9,
    16, 17, 18, 19, 20, 21,
    28, 29, 30, 31, 32, 33,
    40, 41, 42, 43, 44, 45,
    52, 53, 54, 55, 56, 57,
    64, 65, 66, 67, 68, 69,
    76, 77, 78, 79, 80, 81,
    88, 89, 90, 91, 92, 93,
    100, 101, 102, 103, 104, 105,
    112, 113, 114, 115, 116, 117,
    124, 125, 126, 127, 128, 129,
    136, 137, 138, 139, 140, 141
};

uint8_t downPixels[] = {
    142, 143, 132, 133, 134, 135,
    130, 131, 120, 121, 122, 123,
    118, 119, 108, 109, 110, 111,
    106, 107, 96, 97, 98, 99,
    94, 95, 84, 85, 86, 87,
    82, 83, 72, 73, 74, 75,
    70, 71, 60, 61, 62, 63,
    58, 59, 48, 49, 50, 51,
    46, 47, 36, 37, 38, 39,
    34, 35, 24, 25, 26, 27,
    22, 23, 12, 13, 14, 15,
    10, 11, 0, 1, 2, 3
};

void pattern(PatternType patternType, CHSV leds[NUM_LEDS])
{
    int offset = (millis() / 100) % NUM_RINGS;
    int offsetFull = beatsin8(45, 0, NUM_LEDS / 2);
    int offsetSin = beatsin8(15, 0, 4 * NUM_RINGS);

    switch (patternType)
    {
    case PatternType::PATTERN_TYPE_DOT:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int start = r * NUM_RINGS;
            leds[start + offset].v = 255;
        }
        break;

    case PatternType::PATTERN_TYPE_ADJACENT_DOTS:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int start = r * NUM_RINGS;
            leds[start + offsetSin % NUM_RINGS].v = 255;
            leds[start + (offsetSin + NUM_RINGS / 2) % NUM_RINGS].v = 255;
        }
        break;

    case PatternType::PATTERN_TYPE_RIGHT_LEFT_DOTS:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int start = r * NUM_RINGS;
            leds[start + (NUM_RINGS / 2 + offset) % NUM_RINGS].v = 255;
            leds[start + (2 * NUM_RINGS - offset) % NUM_RINGS].v = 255;
        }
        break;

    case PatternType::PATTERN_TYPE_UP_DOWN_DOTS:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int start = r * NUM_RINGS;
            leds[start + offset].v = 255;
            leds[start + (NUM_RINGS - offset) % NUM_RINGS].v = 255;
        }
        break;

    case PatternType::PATTERN_TYPE_SNAKE_CYCLE:
        for (int i = 0; i < NUM_LEDS; i++)
        {
            int ringIndex = (NUM_RINGS + i - offset) % NUM_RINGS;
            int v = ringIndex < 4 ? 255 / (4 - ringIndex) : 0;
            leds[i].v = v;
        }
        break;

    case PatternType::PATTERN_TYPE_4_DOTS:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int start = r * NUM_RINGS;
            leds[start + offset].v = 255;
            leds[start + (offset + NUM_RINGS / 2 - 1) % NUM_RINGS].v = 128;
            leds[start + (offset + NUM_RINGS / 2) % NUM_RINGS].v = 255;
            leds[start + (offset + NUM_RINGS / 2 + 1) % NUM_RINGS].v = 128;
        }
        break;

    case PatternType::PATTERN_TYPE_LOADER:
    {

        // the moving dot completes a full circle every 500 ms
        unsigned long beatTimeMs = 200;

        // the loop completes every 500ms * 12 = 6s
        unsigned long cycleTime = millis() % (beatTimeMs * NUM_RINGS);

        // the full static section is 3 pixels, and the dot moves 9 pixels until hitting the static start
        // on each dot cycle, the end advances by 1
        unsigned long staticPixels = NUM_RINGS / 4;
        unsigned long dotMovePixels = NUM_RINGS - staticPixels - 1;

        unsigned long startIndex = cycleTime / beatTimeMs;
        unsigned long endIndex = (startIndex + staticPixels);
        unsigned long dotRelIndex = (cycleTime % beatTimeMs) / (beatTimeMs / dotMovePixels);

        for (int r = 0; r < NUM_RINGS; r++)
        {
            int ringStart = r * NUM_RINGS;
            for (int s = 0; s < staticPixels; s++)
            {
                int i = (startIndex + s) % NUM_RINGS;
                leds[ringStart + i].v = 255;
            }
            int dotIndex = (NUM_RINGS - 1 + startIndex - dotRelIndex) % NUM_RINGS;
            leds[ringStart + dotIndex].v = 255;
        }
        break;
    }

    case PatternType::PATTERN_TYPE_PIXEL_ALTERNATING:
    {
        int phase = millis() / 333;
        int vSin0 = beatsin8(90, 0, 255);
        int vSin1 = beatsin8(90, 0, 64, 0, 128);
        for (int i = 0; i < NUM_LEDS; i++)
        {
            int x = (i + phase) % 3;
            int v = (x == 0) ? vSin0 : vSin1;
            leds[i].v = v;
        }
        break;
    }

    }

}
