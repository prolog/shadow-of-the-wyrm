#include "CastleGeneratorStrategyFactory.hpp"
#include "MotteBaileyCastleGeneratorStrategy.hpp"

CastleGeneratorStrategyPtr CastleGeneratorStrategyFactory::create_strategy(const CastleType castle_type)
{
  CastleGeneratorStrategyPtr castle_strategy;

  switch(castle_type)
  {
    case CastleType::CASTLE_TYPE_MOTTE_AND_BAILEY:
      castle_strategy = std::make_shared<MotteBaileyCastleGeneratorStrategy>();
      break;
    default:
      break;
  }

  return castle_strategy;
}

