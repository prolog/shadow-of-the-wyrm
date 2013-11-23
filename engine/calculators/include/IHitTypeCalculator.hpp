#pragma once
#include <memory>
#include "Damage.hpp"

// Interface describing different hit types - regular, mighty, 
// and critical
class IHitTypeCalculator
{
  public:
    virtual float get_soak_multiplier() const = 0;
    virtual std::string get_combat_message() const = 0;
    virtual int get_base_damage(const Damage& damage) const = 0;
};

typedef std::shared_ptr<IHitTypeCalculator> IHitTypeCalculatorPtr;

