#pragma once
#include "Creature.hpp"

// An abstract base class for the status ailments.
class StatusEffectCalculator
{
  public:
    virtual ~StatusEffectCalculator() {};

    int chance_of_effect(CreaturePtr creature, const int effect_bonus) const;
    virtual int calculate_duration_in_minutes(CreaturePtr creature) const = 0;

  protected:
    virtual int calculate_pct_chance_effect(CreaturePtr creature) const = 0;
};

typedef std::shared_ptr<StatusEffectCalculator> StatusEffectCalculatorPtr;
