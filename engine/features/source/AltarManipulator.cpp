#include "AltarManipulator.hpp"

using namespace std;

AltarManipulator::AltarManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

bool AltarManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  return true;
}

