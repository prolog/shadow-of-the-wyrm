#include "TanneryManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SkinningConstants.hpp"
#include "TanningCalculator.hpp"
#include "Wearable.hpp"
#include "WornLocationScreenFactory.hpp"

using namespace std;

TanneryManipulator::TanneryManipulator(FeaturePtr feature)
: IFeatureManipulator(feature),
skin_items({ {EquipmentWornLocation::EQUIPMENT_WORN_HEAD, "_hide_cap"}, {EquipmentWornLocation::EQUIPMENT_WORN_BODY, "_hide_armour"}, {EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, "_hide_cloak"}, {EquipmentWornLocation::EQUIPMENT_WORN_FEET, "_hide_boots"} })
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
      vector<pair<string, string>> item_property_filter = {make_pair(SkinningConstants::SKIN_IS_SKIN, Bool::to_string(true))};
      list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);

      ItemPtr selected_skin = am.inventory(creature, creature->get_inventory(), display_filter_list, {}, false);

      if (selected_skin)
      {
        DisplayPtr display = game.get_display();

        WornLocationScreenFactory fac;
        WornLocationSelectionScreen wlss = fac.create_skin_screen(display);
        vector<EquipmentWornLocation> worn_locs = wlss.get_worn_locs();

        string slot_selection = wlss.display();

        if (!slot_selection.empty())
        {
          char selection = slot_selection.at(0) - 'a';
          EquipmentWornLocation selection_loc = static_cast<EquipmentWornLocation>(selection);

          if (std::find(worn_locs.begin(), worn_locs.end(), selection_loc) != worn_locs.end())
          {
            EquipmentWornLocation slot = static_cast<EquipmentWornLocation>(selection);

            // Create the armour.
            ItemPtr armour = create_hide_armour(creature, selected_skin, slot);

            if (armour)
            {
              // Reduce/remove the skin.
              selected_skin->set_quantity(selected_skin->get_quantity() - 1);

              if (selected_skin->get_quantity() <= 0)
              {
                creature->get_inventory()->remove(selected_skin->get_id());
              }

              // Add a message about successfully creating the skin.
              add_successful_armour_creation_message(creature);

              // Add the skin to the tile.
              tile->get_items()->add_front(armour);
              handled = true;
            }
          }
        }        
      }
    }
  }

  return handled;
}

// Create an appropriate piece of hide armour from the given skin.
ItemPtr TanneryManipulator::create_hide_armour(CreaturePtr creature, ItemPtr selected_skin, const EquipmentWornLocation slot)
{
  ItemPtr armour;

  if (creature && selected_skin)
  {
    auto slot_item_it = skin_items.find(slot);

    if (slot_item_it != skin_items.end())
    {
      string item_id = slot_item_it->second;

      // Create the item.
      armour = ItemManager::create_item(item_id);
      WearablePtr wearable = dynamic_pointer_cast<Wearable>(armour);

      // Set the skin details: creature description, resistances, etc.
      // Additional evade and soak may be added if the tanner is skilled, and
      // also based on the base evade/soak of the skinned creature.
      if (wearable)
      {
        TanningCalculator tc;
        int hide_evade = wearable->get_evade() + tc.calculate_evade_bonus(creature);
        int hide_soak = wearable->get_soak() + tc.calculate_soak_bonus(creature);

        if (selected_skin->has_additional_property(SkinningConstants::SKIN_SOAK))
        {
          hide_soak += RNG::range(0, String::to_int(selected_skin->get_additional_property(SkinningConstants::SKIN_SOAK)));
        }

        wearable->set_evade(hide_evade);
        wearable->set_soak(hide_soak);

        armour->set_resistances(selected_skin->get_resistances());
        armour->set_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID, selected_skin->get_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID));
    		armour->set_additional_property(SkinningConstants::SKIN_USAGE_DESCRIPTION_SID, selected_skin->get_additional_property(SkinningConstants::SKIN_USAGE_DESCRIPTION_SID));
	    }
    }
  }

  return armour;
}

// Add a message that the armour was created successfully.
void TanneryManipulator::add_successful_armour_creation_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_CREATE_ARMOUR));
  manager.send();
}

// Skins are required in order to make hide armours.
void TanneryManipulator::add_no_skins_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_NO_SKINS));
  manager.send();
}


