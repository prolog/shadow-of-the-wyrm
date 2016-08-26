#pragma once
#include "Creature.hpp"

class StatisticsMarker
{
  public:
    // Marks a statistic with a declining probability.  The probability
    // is based off the statistic's base value.
    bool mark_statistic(Statistic& stat);

    bool mark_strength(CreaturePtr creature);
    bool mark_dexterity(CreaturePtr creature);
    bool mark_agility(CreaturePtr creature);
    bool mark_health(CreaturePtr creature);
    bool mark_intelligence(CreaturePtr creature);
    bool mark_willpower(CreaturePtr creature);
    bool mark_charisma(CreaturePtr creature);

  protected:
    friend class SW_Engine_Calculators_StatisticsMarkerFixture;
    
    // The probability of marking a statistic is a 1-in-x chance.
    // This function calculates x.
    int calculate_mark_probability_denominator(const int stat_base_value);
};

