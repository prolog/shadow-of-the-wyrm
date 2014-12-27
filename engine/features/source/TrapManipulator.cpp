#include "TrapManipulator.hpp"
#include "Trap.hpp"

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
  FeaturePtr feature = tile->get_feature();
  TrapPtr trap = dynamic_pointer_cast<Trap>(feature);

  if (trap)
  {
    trap->set_triggered(true);
  }

  return true;
}

