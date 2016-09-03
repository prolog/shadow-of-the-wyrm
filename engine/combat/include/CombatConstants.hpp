#pragma once
#include "DamageTypes.hpp"

class CombatConstants
{
  public:
    static const int DEATH_THRESHOLD;
    static const int BASE_WEAPON_DIFFICULTY;
    static const DamageType DEFAULT_UNARMED_DAMAGE_TYPE;
    static const int HEAVY_WEAPON_THRESHOLD_IN_LBS;
    static const int CRITICAL_DIFFICULTY;
    static const int MIGHTY_BLOW_DIFFICULTY;
    static const int CLOSE_MISS_THRESHOLD;
    static const int AUTOMATIC_MISS_THRESHOLD;
    static const int AUTOMATIC_HIT_THRESHOLD;
    static const int INITIAL_THREAT_RATING;
    static const int THREAT_RATING_INCREMENT;
    static const double RACE_SLAY_MULTIPLIER;
    static const int PCT_CHANCE_VORPAL;

  protected:
    CombatConstants();
    ~CombatConstants();
};
