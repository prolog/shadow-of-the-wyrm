#include "CombatConstants.hpp"

const int CombatConstants::DEATH_THRESHOLD = 0;
const int CombatConstants::BASE_WEAPON_DIFFICULTY = 50;
const DamageType CombatConstants::DEFAULT_UNARMED_DAMAGE_TYPE = DamageType::DAMAGE_TYPE_POUND;
const int CombatConstants::HEAVY_WEAPON_THRESHOLD_IN_LBS = 20;
const int CombatConstants::CRITICAL_DIFFICULTY = 100;
const int CombatConstants::MIGHTY_BLOW_DIFFICULTY = 96;
const int CombatConstants::CLOSE_MISS_THRESHOLD = -5;
const int CombatConstants::AUTOMATIC_MISS_THRESHOLD = 5;
const int CombatConstants::AUTOMATIC_HIT_THRESHOLD = 98;
const int CombatConstants::INITIAL_THREAT_RATING = 100;
const int CombatConstants::THREAT_RATING_INCREMENT = 25;
const double CombatConstants::RACE_SLAY_MULTIPLIER = 2.0;
const int CombatConstants::PCT_CHANCE_VORPAL = 3;
const int CombatConstants::PCT_CHANCE_DRAIN = 20;
const float CombatConstants::DRAIN_MULTIPLIER = 0.20;

CombatConstants::CombatConstants()
{
}

CombatConstants::~CombatConstants()
{
}

