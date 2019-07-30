#pragma once
#include "Creature.hpp"

// An abstract base class for the status ailments.
class StatusEffectCalculator
{
  public:
    virtual ~StatusEffectCalculator() {};

    int pct_chance_effect(CreaturePtr creature, const int effect_bonus) const;
    virtual int calculate_duration_in_minutes(CreaturePtr creature) const = 0;

    int pct_chance_counteract_negative(CreaturePtr creature) const;

  protected:
    virtual int calculate_pct_chance_effect(CreaturePtr creature) const = 0;

    static const int MEDICINE_SUBTRAHEND;
};

using StatusEffectCalculatorPtr = std::shared_ptr<StatusEffectCalculator>;
