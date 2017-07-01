#include "BaseDangerLevelCalculator.hpp"
#include "DangerLevelCalculatorFactory.hpp"
#include "DepthBasedDangerLevelCalculator.hpp"
#include "WorldMapDangerLevelCalculator.hpp"

using std::make_shared;

DangerLevelCalculatorFactory::DangerLevelCalculatorFactory()
{
}

DangerLevelCalculatorFactory::~DangerLevelCalculatorFactory()
{
}

IDangerLevelCalculatorPtr DangerLevelCalculatorFactory::create_danger_level_calculator(const MapType map_type, const bool depth_based, const ExitMovementType emt)
{
  IDangerLevelCalculatorPtr danger_level_calculator;

  if (depth_based)
  {
    danger_level_calculator = make_shared<DepthBasedDangerLevelCalculator>(emt);
  }
  else
  {
    switch (map_type)
    {
      case MapType::MAP_TYPE_WORLD:
        danger_level_calculator = make_shared<WorldMapDangerLevelCalculator>();
        break;
      case MapType::MAP_TYPE_OVERWORLD:
        danger_level_calculator = make_shared<BaseDangerLevelCalculator>();
        break;
      case MapType::MAP_TYPE_UNDERWORLD:
      default:
        danger_level_calculator = make_shared<DepthBasedDangerLevelCalculator>(emt);
        break;
    }
  }

  return danger_level_calculator;
}

