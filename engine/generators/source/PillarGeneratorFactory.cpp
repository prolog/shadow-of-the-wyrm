#include "PillarGeneratorFactory.hpp"
#include "CrossPillarGenerator.hpp"
#include "SquarePillarGenerator.hpp"

using namespace std;

IPillarGeneratorPtr PillarGeneratorFactory::create_generator(const PillarType pt)
{
  IPillarGeneratorPtr p_gen;

  switch(pt)
  {
    case PillarType::PILLAR_TYPE_SQUARE:
      p_gen = std::make_shared<SquarePillarGenerator>();
      break;
    case PillarType::PILLAR_TYPE_CROSS:
    default:
      p_gen = std::make_shared<CrossPillarGenerator>();
      break;
  }

  return p_gen;
}

#ifdef UNIT_TESTS
#include "unit_tests/PillarGeneratorFactory_test.cpp"
#endif

