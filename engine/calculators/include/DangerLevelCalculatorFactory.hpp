#pragma once
#include "DangerLevelCalculator.hpp"
#include "MovementTypes.hpp"

class DangerLevelCalculatorFactory
{
  public:
    static DangerLevelCalculatorPtr create_danger_level_calculator(const MapType map_type, const bool depth_based, const ExitMovementType emt);

  protected:
    DangerLevelCalculatorFactory();
    ~DangerLevelCalculatorFactory();
};

