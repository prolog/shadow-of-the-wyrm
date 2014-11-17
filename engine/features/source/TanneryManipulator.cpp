#include "TanneryManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SkinningConstants.hpp"

using namespace std;

TanneryManipulator::TanneryManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void TanneryManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_TANNERY));
    manager.send();
  }
}

bool TanneryManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  if (creature && tile)
  {
    // Check for skins
    if (!creature->get_inventory()->has_item_with_property(SkinningConstants::SKIN_DESCRIPTION_SID))
    {
      add_no_skins_message(creature);
    }
    else
    {
      // ...
    }
  }

  return handled;
}

// Skins are required in order to make hide armours.
void TanneryManipulator::add_no_skins_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_NO_SKINS));
  manager.send();
}


