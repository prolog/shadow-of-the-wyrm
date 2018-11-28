#include "PulperManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

PulperManipulator::PulperManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}


void PulperManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_PULPER));
    manager.send();
  }
}

bool PulperManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  if (creature && tile)
  {
    // ...
  }

  return handled;
}

bool PulperManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

