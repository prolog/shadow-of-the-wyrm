#include "BarrelManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Barrel.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

BarrelManipulator::BarrelManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void BarrelManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_BARREL));
    manager.send();
  }
}

// Check to see if the barrel has a tap (if so, it can pour a drink).
// If the barrel has a tap, attempt to pour a drink, creating the item
// on the barrel's tile.
bool BarrelManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  shared_ptr<Barrel> barrel = dynamic_pointer_cast<Barrel>(feature);

  if (barrel != nullptr)
  {
    if (creature && barrel->get_tap())
    {
      string pour_item_id = barrel->get_pour_item_id();

      if (!pour_item_id.empty())
      {
        ItemPtr item = ItemManager::create_item(pour_item_id);
        if (item != nullptr)
        {
          IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

          IInventoryPtr inv = tile->get_items();
          inv->add(item);

          manager.add_new_message(ActionTextKeys::get_pour_message(creature->get_description_sid(), item->get_usage_description_sid(), creature->get_is_player()));
          manager.send();
        }
      }
    }
    else
    {
    }
  }

  return true;
}


