#pragma once
#include "IDangerLevelCalculator.hpp"

class DangerLevelCalculatorFactory
{
  public:
    static IDangerLevelCalculatorPtr create_danger_level_calculator(const MapType map_type);

  protected:
    DangerLevelCalculatorFactory();
    ~DangerLevelCalculatorFactory();
};

