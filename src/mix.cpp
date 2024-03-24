#include <mix.h>

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

Mix getRandomMix()
{
    Mix mix = {
        static_cast<PatternType>(random8(8)),
        static_cast<PhaseType>(random8(5)),
        static_cast<HueType>(random8(7)),
    };

    return mix;
}