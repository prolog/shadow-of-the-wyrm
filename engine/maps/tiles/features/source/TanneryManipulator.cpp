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
#include "Weapon.hpp"
#include "Wearable.hpp"
#include "WornLocationScreenFactory.hpp"

using namespace std;

TanneryManipulator::TanneryManipulator(FeaturePtr feature)
: FeatureManipulator(feature),
skin_items({ {EquipmentWornLocation::EQUIPMENT_WORN_HEAD, "_hide_cap"}, {EquipmentWornLocation::EQUIPMENT_WORN_WIELDED, "_hide_whip"}, {EquipmentWornLocation::EQUIPMENT_WORN_BODY, "_hide_armour"}, {EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, "_hide_cloak"}, {EquipmentWornLocation::EQUIPMENT_WORN_FEET, "_hide_boots"}, { EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON, "_hide_sling" } })
{
}

void TanneryManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
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
    if (!creature->get_inventory()->has_item_with_property(SkinningConstants::SKIN_IS_SKIN))
    {
      add_no_skins_message(creature);
    }
    else
    {
      ItemPtr selected_skin;
      vector<ItemPtr> skins = creature->get_inventory()->get_all_from_property(SkinningConstants::SKIN_IS_SKIN, std::to_string(true));

      if (skins.size() == 1)
      {
        selected_skin = skins[0];
      }
      else
      {
        vector<pair<string, string>> item_property_filter = { make_pair(SkinningConstants::SKIN_IS_SKIN, std::to_string(true)) };
        list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);

        selected_skin = am.inventory(creature, creature->get_inventory(), display_filter_list, {}, false, false);
      }

      if (selected_skin)
      {
        DisplayPtr display = game.get_display();

        WornLocationScreenFactory fac;
        string slot_selection;
        vector<EquipmentWornLocation> worn_locs;

        {
          WornLocationSelectionScreenPtr wlss = fac.create_skin_screen(display);
          worn_locs = wlss->get_worn_locs();

          slot_selection = wlss->display();
        }

        if (!slot_selection.empty())
        {
          char selection = slot_selection.at(0) - 'a';
          EquipmentWornLocation selection_loc = static_cast<EquipmentWornLocation>(selection);

          if (std::find(worn_locs.begin(), worn_locs.end(), selection_loc) != worn_locs.end())
          {
            EquipmentWornLocation slot = static_cast<EquipmentWornLocation>(selection);

            // Create the armour or sling.
            ItemPtr armour = create_hide_equipment(creature, selected_skin, slot);

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

bool TanneryManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

// Create an appropriate piece of hide equipment from the given skin for the
// given slot.
ItemPtr TanneryManipulator::create_hide_equipment(CreaturePtr creature, ItemPtr selected_skin, const EquipmentWornLocation slot)
{
  ItemPtr item;

  if (creature && selected_skin)
  {
    auto slot_item_it = skin_items.find(slot);

    if (slot_item_it != skin_items.end())
    {
      TanningCalculator tc;
      string item_id = slot_item_it->second;

      // Create the item.
      item = ItemManager::create_item(item_id);
      WearablePtr wearable = dynamic_pointer_cast<Wearable>(item);
      wearable->set_status(selected_skin->get_status());

      // Set the skin details: creature description, resistances, etc.
      // Additional evade and soak may be added if the tanner is skilled, and
      // also based on the base evade/soak of the skinned creature.
      if (wearable)
      {
        WeaponPtr weapon = dynamic_pointer_cast<Weapon>(item);

        if (weapon != nullptr)
        {
          int th_bonus = weapon->get_to_hit() + RNG::range(tc.calculate_combat_bonus_min(creature), tc.calculate_combat_bonus_max(creature));

          Damage d = weapon->get_damage();
          int damage_bonus = RNG::range(tc.calculate_combat_bonus_min(creature), tc.calculate_combat_bonus_max(creature));
          int damage_type_bonus = d.get_effect_bonus() + RNG::range(tc.calculate_combat_bonus_min(creature), tc.calculate_combat_bonus_max(creature));

          weapon->set_to_hit(th_bonus);
          weapon->set_addl_damage(damage_bonus);
          d.set_effect_bonus(damage_type_bonus);
          weapon->set_damage(d);
        }
        else
        {
          int hide_evade = wearable->get_evade() + RNG::range(tc.calculate_evade_bonus_min(creature), tc.calculate_evade_bonus_max(creature));
          int hide_soak = wearable->get_soak() + RNG::range(tc.calculate_soak_bonus_min(creature), tc.calculate_soak_bonus_max(creature));

          if (selected_skin->has_additional_property(SkinningConstants::SKIN_SOAK))
          {
            hide_soak += RNG::range(0, String::to_int(selected_skin->get_additional_property(SkinningConstants::SKIN_SOAK)));
          }

          wearable->set_evade(hide_evade);
          wearable->set_soak(hide_soak);
        }

        item->set_resistances(tc.calculate_item_resistances(creature, selected_skin->get_resistances()));
        item->set_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID, selected_skin->get_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID));
    		item->set_additional_property(SkinningConstants::SKIN_USAGE_DESCRIPTION_SID, selected_skin->get_additional_property(SkinningConstants::SKIN_USAGE_DESCRIPTION_SID));

        creature->get_skills().mark(SkillType::SKILL_GENERAL_TANNING);
	    }
    }
  }

  return item;
}

// Add a message that the armour was created successfully.
void TanneryManipulator::add_successful_armour_creation_message(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_CREATE_ARMOUR));
  manager.send();
}

// Skins are required in order to make hide armours.
void TanneryManipulator::add_no_skins_message(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_NO_SKINS));
  manager.send();
}


