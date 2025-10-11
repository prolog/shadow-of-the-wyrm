#include "HiveManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Features.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
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
      MapPtr map = Game::instance().get_current_map();

      if (charges > 0)
      {
        // Summon a bunch of drones around the disturber.
        Dice d(2, 3, 0);
        pair<Dice, vector<std::string>> summoned_creature_details = { d, {hive->get_drone_id() } };

        string summon_message_sid = ActionTextKeys::ACTION_ERUPT_HIVE;
        GameUtils::summon_creatures(creature, map, summoned_creature_details, summon_message_sid);

        // Reduce the hive's capacity
        hive->set_charges(charges - 1);
      }
      else
      {
        hive_destroyed = true;
      }

      // If there are hive items, add some on the hive tile.
      vector<string> item_ids = hive->get_item_ids();
      if (!item_ids.empty())
      {
        int num_items = RNG::range(1, 3);

        for (int i = 0; i < num_items; i++)
        {
          string item_id = item_ids.at(RNG::range(0, item_ids.size() - 1));
          ItemPtr item = ItemManager::create_item(item_id);

          feature_tile->get_items()->merge_or_add(item);
        }
      }

      if (hive_destroyed)
      {
        // The leader emerges
        Dice d(1, 1, 0);
        pair<Dice, vector<std::string>> summoned_creature_details = { d, {hive->get_leader_id() } };

        string summon_message_sid = ActionTextKeys::ACTION_KICK_HIVE_EMPTY;
        GameUtils::summon_creatures(creature, map, summoned_creature_details, summon_message_sid);
      }
    }

    if (hive_destroyed)
    {
      feature_tile->remove_feature();
    }

    return true;
  }

  return false;
}