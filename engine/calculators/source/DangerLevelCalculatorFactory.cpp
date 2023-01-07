#include "BaseDangerLevelCalculator.hpp"
#include "DangerLevelCalculatorFactory.hpp"
#include "DepthBasedDangerLevelCalculator.hpp"
#include "WorldMapDangerLevelCalculator.hpp"

DangerLevelCalculatorFactory::DangerLevelCalculatorFactory()
{
}

DangerLevelCalculatorFactory::~DangerLevelCalculatorFactory()
{
}

DangerLevelCalculatorPtr DangerLevelCalculatorFactory::create_danger_level_calculator(const MapType map_type, const bool depth_based, const ExitMovementType emt)
{
  DangerLevelCalculatorPtr danger_level_calculator;

  if (depth_based)
  {
    danger_level_calculator = std::make_unique<DepthBasedDangerLevelCalculator>(emt);
  }
  else
  {
    switch (map_type)
    {
      case MapType::MAP_TYPE_WORLD:
        danger_level_calculator = std::make_unique<WorldMapDangerLevelCalculator>();
        break;
      case MapType::MAP_TYPE_OVERWORLD:
        danger_level_calculator = std::make_unique<BaseDangerLevelCalculator>();
        break;
      case MapType::MAP_TYPE_AIR:
      case MapType::MAP_TYPE_COSMOS:
      case MapType::MAP_TYPE_UNDERWORLD:
      default:
        danger_level_calculator = std::make_unique<DepthBasedDangerLevelCalculator>(emt);
        break;
    }
  }

  return danger_level_calculator;
}

