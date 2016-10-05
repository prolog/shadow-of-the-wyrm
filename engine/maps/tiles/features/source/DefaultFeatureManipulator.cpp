#include "ActionTextKeys.hpp"
#include "DefaultFeatureManipulator.hpp"
#include "MessageManagerFactory.hpp"

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
  if (creature)
  {
    if (creature && creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_HANDLE_DEFAULT));
      manager.send();
    }
  }

  return true;
}

bool DefaultFeatureManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}
