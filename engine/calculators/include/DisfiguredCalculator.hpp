#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is disfigured (reduced
// statistics) as the result of an acid attack, and for how long.
class DisfiguredCalculator : public StatusEffectCalculator
{
  public:
    virtual ~DisfiguredCalculator() = default;

    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

    // Return the min/max stat reduction percentages, based on the danger level.
    std::pair<int, int> calculate_reduction_pcts(const int danger_level) const;

  protected:
    static const int BASE_DISFIGURED_DURATION_MEAN;
    static const int BASE_DISFIGURED_PCT_CHANCE;
    static const int BASE_DISFIGURED_CHANCE_HEALTH_MODIFIER;
    static const int BASE_REDUCTION_PCT_MIN;
    static const int BASE_REDUCTION_PCT_MAX;
    static const int REDUCTION_PCT_MAX;
};

