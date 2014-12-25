#include "TrapManipulator.hpp"

using namespace std;

TrapManipulator::TrapManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void TrapManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  // JCD FIXME add a message about "narrowly setting off the trap"...
}

bool TrapManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  return true;
}

