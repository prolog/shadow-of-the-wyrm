#include "CreatureFeatures.hpp"

using namespace std;

CreatureConstants::CreatureConstants()
{
}

CreatureConstants::~CreatureConstants()
{
}

const unsigned int CreatureConstants::MAX_CREATURE_LEVEL = 50;
const int CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE = 99;

CreatureEventScripts::CreatureEventScripts()
{
}

CreatureEventScripts::~CreatureEventScripts()
{
}

const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH = "CREATURE_EVENT_SCRIPT_DEATH";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_ATTACK = "CREATURE_EVENT_SCRIPT_ATTACK";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT = "CREATURE_EVENT_SCRIPT_CHAT";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_DECISION = "CREATURE_EVENT_SCRIPT_DECISION";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_DROP = "CREATURE_EVENT_SCRIPT_DROP";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_ENTER_TILE = "CREATURE_EVENT_SCRIPT_ENTER_TILE";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_TAME = "CREATURE_EVENT_SCRIPT_TAME";

CreatureID::CreatureID()
{
}

CreatureID::~CreatureID()
{
}

const string CreatureID::CREATURE_ID_SHOPKEEPER = "_shopkeeper";
const string CreatureID::CREATURE_ID_FAIRY_SPIRIT = "_fairy_spirit";
const string CreatureID::CREATURE_ID_MAGICAL_SPIRIT = "_magical_spirit";
const string CreatureID::CREATURE_ID_VENDOR = "_vendor";
const string CreatureID::CREATURE_ID_PLAYER = "player";
const string CreatureID::CREATURE_ID_PREFIX_ANCIENT_BEAST = "_ancient_beast_";
const string CreatureID::CREATURE_ID_POTTER = "_potter";
const string CreatureID::CREATURE_ID_SMITH = "_smith";
const string CreatureID::CREATURE_ID_JEWELER = "_jeweler";
const string CreatureID::CREATURE_ID_WEAVER = "_weaver";
const string CreatureID::CREATURE_ID_TANNER = "_tanner";
const string CreatureID::CREATURE_ID_SCRIBE = "_scribe";
const string CreatureID::CREATURE_ID_COMMONER = "_commoner";
const string CreatureID::CREATURE_ID_NOBLE = "_noble";
const string CreatureID::CREATURE_ID_FISHERMAN = "_fisherman";
const string CreatureID::CREATURE_ID_FARMER = "_farmer";
const string CreatureID::CREATURE_ID_SMALL_CHILD = "_small_child";
const string CreatureID::CREATURE_ID_GUARD = "_guard";
const string CreatureID::CREATURE_ID_BARTENDER = "_bartender";
const string CreatureID::CREATURE_ID_DRUNK = "_drunk";
