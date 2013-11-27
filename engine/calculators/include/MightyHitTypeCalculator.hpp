#pragma once
#include "IHitTypeCalculator.hpp"

class MightyHitTypeCalculator : public IHitTypeCalculator
{
  public:
    virtual float get_soak_multiplier() const override;
    virtual std::string get_combat_message() const override;
    virtual int get_base_damage(const Damage& damage) const override;
};

