#pragma once
#include "IHitTypeCalculator.hpp"
#include "HitTypes.hpp"

class IHitTypeFactory
{
  public:
    static IHitTypeCalculatorPtr create_hit_type(const HitTypeEnum hit_type);

  protected:
    IHitTypeFactory();
};
