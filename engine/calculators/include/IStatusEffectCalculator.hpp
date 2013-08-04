#pragma once
#include "Creature.hpp"

// An interface class for the status ailments.
class IStatusEffectCalculator
{
  public:
    virtual ~IStatusEffectCalculator() {};

    virtual int calculate_pct_chance_effect(CreaturePtr creature) const = 0;
    virtual int calculate_duration_in_minutes(CreaturePtr creature) const = 0;
};

typedef boost::shared_ptr<IStatusEffectCalculator> IStatusEffectCalculatorPtr;
