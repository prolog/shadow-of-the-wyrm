#include "PulperManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

PulperManipulator::PulperManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}


void PulperManipulator::kick(CreaturePtr creature, MapPtr /*current_map*/, TilePtr /*feature_tile*/, const Coordinate& /*feature_coord*/, FeaturePtr /*feat*/)
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
    IMessageManager& manager = MM::instance();
    ItemPtr pulp_item = get_item_to_pulp(creature);

    if (pulp_item != nullptr)
    {
      if (pulp_item->get_artifact())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PULP_ARTIFACT_SELECTED));
        manager.send();
      }
      else
      {
        // It might be unrealistic to assume that when you pulp something you get
        // exactly 100% of the weight in paper pulp.
        //
        // But it sure simplifies the implementation.

        Weight pulp_weight = pulp_item->get_total_weight();
        ItemPtr paper_pulp = ItemManager::create_item(ItemIdKeys::ITEM_ID_PAPER_PULP);
        paper_pulp->set_weight(pulp_weight);
        tile->get_items()->merge_or_add(paper_pulp, InventoryAdditionType::INVENTORY_ADDITION_BACK);

        creature->get_inventory()->remove(pulp_item->get_id());

        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PULP_CREATED));
        manager.send();
      }
    }
  }

  return handled;
}

bool PulperManipulator::drop(CreaturePtr /*dropping_creature*/, TilePtr /*tile*/, ItemPtr /*item*/)
{
  return false;
}

ItemPtr PulperManipulator::get_item_to_pulp(CreaturePtr creature)
{
  ItemPtr pulp_item;

  if (creature != nullptr)
  {
    list<IItemFilterPtr> display_filter = ItemFilterFactory::create_material_type_filter({MaterialType::MATERIAL_TYPE_PAPER, MaterialType::MATERIAL_TYPE_WOOD});
    pulp_item = Game::instance().get_action_manager_ref().inventory(creature, creature->get_inventory(), display_filter, {}, false, false);
  }

  return pulp_item;
}