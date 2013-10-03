#pragma once
#include "IHitTypeCalculator.hpp"

class CriticalHitTypeCalculator : public IHitTypeCalculator
{
  public:
    virtual float get_soak_multiplier() const;
    virtual std::string get_combat_message() const;
    virtual int get_base_damage(const Damage& damage) const;
};

