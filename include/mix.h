#ifndef MIX_H
#define MIX_H

#include <hue.h>
#include <pattern.h>
#include <phase.h>

struct Mix
{
    PatternType patternType;
    PhaseType phaseType;
    HueType hueType;
};

Mix getRandomMix();

#endif // MIX_H