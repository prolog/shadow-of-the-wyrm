#include "HiveManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

HiveManipulator::HiveManipulator(FeaturePtr feature)
: DefaultFeatureManipulator(feature)
{
}

void HiveManipulator::kick(CreaturePtr creature, MapPtr /*current_map*/, TilePtr feature_tile, const Coordinate& /*feature_coord*/, FeaturePtr /*feature*/)
{
  bool hive_destroyed = true;

  if (feature_tile && creature && creature->get_is_player())
  {
    string message_sid = ActionTextKeys::ACTION_KICK_HIVE;

    if (hive_destroyed)
    {
      message_sid = ActionTextKeys::ACTION_KICK_HIVE_EMPTY;;
    }

    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
  }

  if (hive_destroyed)
  {
    feature_tile->remove_feature();
  }
}

// Messing with an insect nest generates insects (which may or may not be
// angry) and potentially generates items such as honey, honeycomb, etc.
bool HiveManipulator::handle(TilePtr /*tile*/, CreaturePtr /*creature*/)
{
  return false;
}

