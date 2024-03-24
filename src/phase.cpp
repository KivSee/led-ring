#include <phase.h>

PhaseType randomPhaseType()
{
    return (PhaseType)(random8(4));
}

void phase(PhaseType phaseType, CRGB src[NUM_LEDS], CRGB dest[NUM_LEDS])
{
    switch (phaseType)
    {

    case PhaseType::PHASE_TYPE_NO_PHASE:
        for (int i = 0; i < NUM_LEDS; i++)
        {
            dest[i] = src[i];
        }
        break;

    case PhaseType::PHASE_TYPE_CYCLIC:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int ringStart = r * NUM_RINGS;
            for (int c = 0; c < NUM_RINGS; c++)
            {
                int srcIndex = ringStart + c;
                int shift = (c + NUM_LEDS - 1 - r) % NUM_RINGS;
                int destIndex = ringStart + shift;
                dest[destIndex] = src[srcIndex];
            }
        }
        break;

    case PhaseType::PHASE_TYPE_ALTERNATE:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int ringStart = r * NUM_RINGS;
            bool alternateQ = r % 2 == 0;
            for (int c = 0; c < NUM_RINGS; c++)
            {
                int srcIndex = ringStart + c;
                int shift = alternateQ ? c : (c + NUM_RINGS / 2) % NUM_RINGS;
                int destIndex = ringStart + shift;
                dest[destIndex] = src[srcIndex];
            }
        }
        break;

    case PhaseType::PHASE_TYPE_DOUBLE:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int ringStart = r * NUM_RINGS;
            for (int c = 0; c < NUM_RINGS; c++)
            {
                int srcIndex = ringStart + c;
                int shift = (c + r * 2) % NUM_RINGS;
                int destIndex = ringStart + shift;
                dest[destIndex] = src[srcIndex];
            }
        }
        break;

    case PhaseType::PHASE_TYPE_ALTERNATE_REVERSE:
        for (int r = 0; r < NUM_RINGS; r++)
        {
            int ringStart = r * NUM_RINGS;
            bool alternateQ = r % 2 == 0;
            for (int c = 0; c < NUM_RINGS; c++)
            {
                int srcIndex = ringStart + c;
                int shift = alternateQ ? c : (NUM_RINGS - c) % NUM_RINGS;
                int destIndex = ringStart + shift;
                dest[destIndex] = src[srcIndex];
            }
        }
        break;

    }
}
