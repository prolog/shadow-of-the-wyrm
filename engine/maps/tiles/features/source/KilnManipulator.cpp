#include "KilnManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "KilnScreen.hpp"
#include "ItemTypes.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

KilnManipulator::KilnManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

void KilnManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_KILN));
    manager.send();
  }
}

bool KilnManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool kiln_used = false;

  if (feature != nullptr && creature != nullptr)
  {
    if (check_for_clay(creature))
    {
      Game& game = Game::instance();
      DisplayPtr display = game.get_display();

      bool fire_bombs = creature->get_inventory()->has_item(ItemIdKeys::ITEM_ID_MAGICI_SHARD);
      bool shadow_bombs = creature->get_inventory()->has_item(ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE);

      KilnScreen ks(display, fire_bombs, ItemIdKeys::ITEM_ID_MAGICI_SHARD, shadow_bombs, ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE);
      string d = ks.display();

      // Call the appropriate function based on the response:
      // ...
    }
  }

  return kiln_used;
}

bool KilnManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

bool KilnManipulator::check_for_clay(CreaturePtr creature)
{
  bool has_clay = false;

  if (creature != nullptr)
  {
    if (creature->get_inventory()->count_items(ItemIdKeys::ITEM_ID_CLAY) == 0)
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KILN_NO_CLAY));
      manager.send();
    }
    else
    {
      has_clay = true;
    }
  }

  return has_clay;
}