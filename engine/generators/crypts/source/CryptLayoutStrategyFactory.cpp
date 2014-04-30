#include "CryptLayoutStrategyFactory.hpp"
#include "PillarCryptLayoutStrategy.hpp"

ICryptLayoutStrategyPtr CryptLayoutStrategyFactory::create_layout_strategy(const CryptLayoutType layout_type)
{
  ICryptLayoutStrategyPtr layout_strategy;

  switch(layout_type)
  {
    case CRYPT_LAYOUT_PILLARS:
    default:
      layout_strategy = std::make_shared<PillarCryptLayoutStrategy>();
      break;
  }
  
  return layout_strategy;
}

#ifdef UNIT_TESTS
#include "unit_tests/CryptLayoutStrategyFactory_test.cpp"
#endif

