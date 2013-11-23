#include "DangerLevelCalculatorFactory.hpp"
#include "OverworldMapDangerLevelCalculator.hpp"
#include "UnderworldMapDangerLevelCalculator.hpp"
#include "WorldMapDangerLevelCalculator.hpp"

using std::make_shared;

DangerLevelCalculatorFactory::DangerLevelCalculatorFactory()
{
}

DangerLevelCalculatorFactory::~DangerLevelCalculatorFactory()
{
}

IDangerLevelCalculatorPtr DangerLevelCalculatorFactory::create_danger_level_calculator(const MapType map_type)
{
  IDangerLevelCalculatorPtr danger_level_calculator;

  switch(map_type)
  {
    case MAP_TYPE_WORLD:
      danger_level_calculator = make_shared<WorldMapDangerLevelCalculator>();
      break;
    case MAP_TYPE_OVERWORLD:
      danger_level_calculator = make_shared<OverworldMapDangerLevelCalculator>();
      break;
    case MAP_TYPE_UNDERWORLD:
    default:
      danger_level_calculator = make_shared<UnderworldMapDangerLevelCalculator>();
      break;
  }

  return danger_level_calculator;
}

