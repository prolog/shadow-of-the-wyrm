#include "TanneryManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SkinningConstants.hpp"
#include "SkinSelectionScreen.hpp"

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

// Manipulating a tannery allows turning skins into armour.
// The player can select a skin, then an armour slot, and
// an appropriate piece of armour is created.  The resistances
// on the skin are added to the armour based on the creature's
// Tanning skill.
bool TanneryManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  if (creature && tile)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();

    // Check for skins
    if (!creature->get_inventory()->has_item_with_property(SkinningConstants::SKIN_DESCRIPTION_SID))
    {
      add_no_skins_message(creature);
    }
    else
    {
      vector<pair<string, string>> item_property_filter = {make_pair(SkinningConstants::SKIN_DESCRIPTION_SID, "")};
      list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);

      ItemPtr selected_skin = am.inventory(creature, creature->get_inventory(), display_filter_list, false);

      if (selected_skin)
      {
        SkinSelectionScreen sss(game.get_display());
        string slot_selection = sss.display();

        int x = 1;
      }
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


