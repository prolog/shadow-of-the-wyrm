#include "BarrelManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Features.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

BarrelManipulator::BarrelManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

void BarrelManipulator::kick(CreaturePtr creature, MapPtr /*current_map*/, TilePtr /*feature_tile*/, const Coordinate& /*feature_coord*/, FeaturePtr /*feature*/)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_BARREL));
    manager.send();
  }
}

// Check to see if the barrel has a tap (if so, it can pour a drink).
// If the barrel has a tap, attempt to pour a drink, creating the item
// on the barrel's tile.
bool BarrelManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  std::shared_ptr<Barrel> barrel = dynamic_pointer_cast<Barrel>(feature);

  if (barrel != nullptr)
  {
    if (creature && barrel->get_tap())
    {
      if (barrel->can_pour())
      {
        barrel->pour();

        ItemPtr item = ItemManager::create_item(barrel->get_pour_item_id());
        
        if (item != nullptr)
        {
          IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

          IInventoryPtr inv = tile->get_items();
          inv->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);

          manager.add_new_message(ActionTextKeys::get_pour_message(creature->get_description_sid(), item->get_usage_description_sid(), creature->get_is_player()));
          manager.send();
        }
      }
      else
      {
        IMessageManager& pl_manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
        pl_manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_POUR_EMPTY));
        pl_manager.send();
      }
    }
  }

  return true;
}

bool BarrelManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}


