#pragma once
#include "IDangerLevelCalculator.hpp"
#include "MovementTypes.hpp"

class DangerLevelCalculatorFactory
{
  public:
    static IDangerLevelCalculatorPtr create_danger_level_calculator(const MapType map_type, const bool depth_based, const ExitMovementType emt);

  protected:
    DangerLevelCalculatorFactory();
    ~DangerLevelCalculatorFactory();
};

