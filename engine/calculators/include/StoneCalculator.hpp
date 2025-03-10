#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature will be petrified, and how
// long the process will take.
class StoneCalculator : public StatusEffectCalculator
{
  public:
    virtual ~StoneCalculator() = default;

    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_STONE_DURATION_MEAN;
    static const int BASE_STONE_PCT_CHANCE;
    static const int BASE_STONE_CHANCE_HEALTH_MODIFIER;
};

