#include "WheelAndLoomManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "Wearable.hpp"
#include "WeavingCalculator.hpp"
#include "WeavingConstants.hpp"
#include "WornLocationScreenFactory.hpp"

using namespace std;

WheelAndLoomManipulator::WheelAndLoomManipulator(FeaturePtr feature)
: IFeatureManipulator(feature),
loom_map({ {EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, "_cloak"}, {EquipmentWornLocation::EQUIPMENT_WORN_BODY, "_robes"} })
{
}

void WheelAndLoomManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_WHEEL_AND_LOOM));
    manager.send();
  }
}

// Weave natural fibres into cloaks and robes.
// Any improvements to the items are in terms of resistances.
bool WheelAndLoomManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  if (tile && creature)
  {
    // Check for weaving skill.
    if (creature->get_skills().get_value(SkillType::SKILL_GENERAL_WEAVING) <= 0)
    {
      add_no_weaving_skill_message(creature);
    }
    else
    {
      // Has weaving - check for fibres, etc.
      if (!creature->get_inventory()->has_item_with_property(WeavingConstants::WEAVING_MATERIAL_TYPE_KEY))
      {
        add_no_fibres_message(creature);
      }
      else
      {
        // Has fibres (whiteflower, etc).  Select one, then a worn slot.
        Game& game = Game::instance();
        DisplayPtr display = game.get_display();
        ActionManager& am = game.get_action_manager_ref();

        vector<pair<string, string>> item_property_filter = { make_pair(WeavingConstants::WEAVING_MATERIAL_TYPE_KEY, "") };
        list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);

        ItemPtr selected_fibre = am.inventory(creature, creature->get_inventory(), display_filter_list, false);

        if (selected_fibre)
        {
          WornLocationScreenFactory fac;
          WornLocationSelectionScreen wlss = fac.create_weaving_screen(display);
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
              ItemPtr armour = create_woven_armour(creature, selected_fibre, slot);

              if (armour)
              {
                // Reduce/remove the skin.
                selected_fibre->set_quantity(selected_fibre->get_quantity() - 1);

                if (selected_fibre->get_quantity() <= 0)
                {
                  creature->get_inventory()->remove(selected_fibre->get_id());
                }

                // Add a message about successfully creating the skin.
                add_successful_weaving_message(creature);

                // Add the skin to the tile.
                tile->get_items()->add_front(armour);
                handled = true;
              }
            }
          }
        }
      }
    }
  }

  return handled;
}

ItemPtr WheelAndLoomManipulator::create_woven_armour(CreaturePtr creature, ItemPtr fibre, const EquipmentWornLocation slot)
{
  ItemPtr armour;

  if (creature && fibre)
  {
    auto slot_item_it = loom_map.find(slot);

    if (slot_item_it != loom_map.end())
    {
      string item_id = slot_item_it->second;

      // Create the item.
      armour = ItemManager::create_item(item_id);
      WearablePtr wearable = dynamic_pointer_cast<Wearable>(armour);

      // Weaving has fewer usable slots than tanning, but instead of providing
      // a straight-up bonus to evade or soak, it provides free enchantments,
      // based on the weaver's skill.
      if (wearable)
      {
        WeavingCalculator wc;

        int min_points = wc.calculate_min_enchant_points(creature);
        int max_points = wc.calculate_max_enchant_points(creature);

        int num_points = RNG::range(min_points, max_points);
        wearable->enchant(num_points);
      }
    }
  }

  return armour;
}

void WheelAndLoomManipulator::add_no_weaving_skill_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WEAVE_NO_WEAVING_SKILL));
  manager.send();
}

// The creature has no fibres in its inventory - add a message.
void WheelAndLoomManipulator::add_no_fibres_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WEAVE_NO_FIBRES));
  manager.send();
}

// An item was created successfully!
void WheelAndLoomManipulator::add_successful_weaving_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WEAVE_SUCCESSFUL));
  manager.send();
}