#include "HiveManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Features.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

HiveManipulator::HiveManipulator(FeaturePtr feature)
: DefaultFeatureManipulator(feature)
{
}

void HiveManipulator::kick(CreaturePtr creature, MapPtr /*current_map*/, TilePtr feature_tile, const Coordinate& /*feature_coord*/, FeaturePtr tile_feature)
{
  shake_hive(feature_tile, tile_feature, creature, ActionTextKeys::ACTION_KICK_HIVE);
}

// Messing with an insect nest generates insects (which may or may not be
// angry) and potentially generates items such as honey, honeycomb, etc.
bool HiveManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  return shake_hive(tile, tile->get_feature(), creature, ActionTextKeys::ACTION_SHAKE_HIVE);
}

bool HiveManipulator::shake_hive(TilePtr feature_tile, FeaturePtr tile_feature, CreaturePtr creature, const std::string& message_sid)
{
  if (feature_tile != nullptr && tile_feature != nullptr && creature != nullptr)
  {
    bool hive_destroyed = false;
    std::shared_ptr<Hive> hive = dynamic_pointer_cast<Hive>(tile_feature);

    if (feature_tile && hive && creature && creature->get_is_player())
    {
      string msg_sid = message_sid;
      int charges = hive->get_charges();

      if (charges > 0)
      {
        // erupt... (TODO)

        // Reduce the hive's capacity
        hive->set_charges(charges - 1);
      }
      else
      {
        hive_destroyed = true;
      }

      if (hive_destroyed)
      {
        msg_sid = ActionTextKeys::ACTION_KICK_HIVE_EMPTY;
      }

      IMessageManager& manager = MMF::instance();
      manager.add_new_message(StringTable::get(msg_sid));
      manager.send();
    }

    if (hive_destroyed)
    {
      feature_tile->remove_feature();
    }

    return true;
  }

  return false;
}