#include "CreatureFeatures.hpp"

using namespace std;

CreatureConstants::CreatureConstants()
{
}

CreatureConstants::~CreatureConstants()
{
}

const int CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH = 6;
const int CreatureConstants::MAX_CREATURE_LEVEL = 50;

CreatureEvents::CreatureEvents()
{
}

CreatureEvents::~CreatureEvents()
{
}

const string CreatureEvents::CREATURE_EVENT_DEATH = "CREATURE_EVENT_DEATH";
