#include "WheelAndLoomManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

WheelAndLoomManipulator::WheelAndLoomManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void WheelAndLoomManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_WHEEL_AND_LOOM));
    manager.send();
  }
}

bool WheelAndLoomManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  return handled;
}

