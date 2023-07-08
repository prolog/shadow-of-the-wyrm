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
const int CreatureConstants::COWARDLY_CREATURE_HP_PCT_FLEE = 30;

CreatureEventScripts::CreatureEventScripts()
{
}

CreatureEventScripts::~CreatureEventScripts()
{
}

const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_CREATE = "CREATURE_EVENT_SCRIPT_CREATE";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH = "CREATURE_EVENT_SCRIPT_DEATH";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_ATTACK = "CREATURE_EVENT_SCRIPT_ATTACK";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT = "CREATURE_EVENT_SCRIPT_CHAT";
const string CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT_NIGHT = "CREATURE_EVENT_SCRIPT_NIGHT";
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
const string CreatureID::CREATURE_ID_HERMIT = "_hermit";
const string CreatureID::CREATURE_ID_FAIRY_SPIRIT = "_fairy_spirit";
const string CreatureID::CREATURE_ID_MAGICAL_SPIRIT = "_magical_spirit";
const string CreatureID::CREATURE_ID_VENDOR = "_vendor";
const string CreatureID::CREATURE_ID_PLAYER = "player";
const string CreatureID::CREATURE_ID_HIRELING = "_hireling";
const string CreatureID::CREATURE_ID_ADVENTURER = "_adventurer";
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
const string CreatureID::CREATURE_ID_THATCHER = "_thatcher";
const string CreatureID::CREATURE_ID_SMALL_CHILD = "_small_child";
const string CreatureID::CREATURE_ID_GUARD = "_guard";
const string CreatureID::CREATURE_ID_BARTENDER = "_bartender";
const string CreatureID::CREATURE_ID_DRUNK = "_drunk";
const string CreatureID::CREATURE_ID_SHEEP = "_sheep";
const string CreatureID::CREATURE_ID_CHICKEN = "_chicken";
const string CreatureID::CREATURE_ID_WITCHLING = "_witchling";

MembershipID::MembershipID()
{
}

MembershipID::~MembershipID()
{
}

const string MembershipID::MEMBERSHIP_ID_HOLY_CHAMPION = "_holy_champion";
const string MembershipID::MEMBERSHIP_ID_FALLEN_CHAMPION = "_fallen_champion";
