#pragma once
#include "Creature.hpp"

// Used in some cases to override the default behaviour of the probability checking.
// Useful for things like quests, etc., where it may be desired to always mark a
// stat regardless of its value.
class StatisticsMarkerProbabilityDetails
{
  public:
    StatisticsMarkerProbabilityDetails(const bool new_override_p_denom, const int new_p_denom);

    bool get_override_p_denom() const;
    int get_p_denom() const;

  protected:
    bool override_p_denom;
    int p_denom;
};

class StatisticsMarker
{
  public:
    // Marks a statistic with a declining probability.  The probability
    // is based off the statistic's base value.
    bool mark_statistic(Statistic& stat, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));

    bool mark_strength(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));
    bool mark_dexterity(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));
    bool mark_agility(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));
    bool mark_health(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));
    bool mark_intelligence(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));
    bool mark_willpower(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));
    bool mark_charisma(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd = StatisticsMarkerProbabilityDetails(false, -1));

  protected:
    friend class SW_Engine_Calculators_StatisticsMarkerFixture;
    
    // The probability of marking a statistic is a 1-in-x chance.
    // This function calculates x.
    int calculate_mark_probability_denominator(const int stat_base_value);
};

