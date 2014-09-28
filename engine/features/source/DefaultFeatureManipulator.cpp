#include "DefaultFeatureManipulator.hpp"

using namespace std;

DefaultFeatureManipulator::DefaultFeatureManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void DefaultFeatureManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
}

bool DefaultFeatureManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  return true;
}


