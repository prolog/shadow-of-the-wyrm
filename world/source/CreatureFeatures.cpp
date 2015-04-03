#include "CreatureFeatures.hpp"

using namespace std;

CreatureConstants::CreatureConstants()
{
}

CreatureConstants::~CreatureConstants()
{
}

const int CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH = 6;
const unsigned int CreatureConstants::MAX_CREATURE_LEVEL = 50;

CreatureEventScripts::CreatureEventScripts()
{
}

CreatureEventScripts::~CreatureEventScripts()
{
}

const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH = "CREATURE_EVENT_SCRIPT_DEATH";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_ATTACK = "CREATURE_EVENT_SCRIPT_ATTACK";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT = "CREATURE_EVENT_SCRIPT_CHAT";

CreatureAdditionalProperties::CreatureAdditionalProperties()
{
}

CreatureAdditionalProperties::~CreatureAdditionalProperties()
{
}

const string CreatureAdditionalProperties::CREATURE_PROPERTY_SPEECH_TEXT_SID = "CREATURE_PROPERTY_SPEECH_TEXT_SID";
