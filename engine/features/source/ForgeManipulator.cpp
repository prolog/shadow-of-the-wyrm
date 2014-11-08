#include "ForgeManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SmithingConstants.hpp"
#include "WeaponManager.hpp"

using namespace std;

ForgeManipulator::ForgeManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void ForgeManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_FORGE));
    manager.send();
  }
}

bool ForgeManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (feature != nullptr)
  {
    // Is the creature wielding something suitably hammer-y?
    WeaponManager wm;
    WeaponPtr weapon1 = wm.get_weapon(creature, ATTACK_TYPE_MELEE_PRIMARY);
    WeaponPtr weapon2 = wm.get_weapon(creature, ATTACK_TYPE_MELEE_SECONDARY);

    // Does the creature know anything about smithing?
    SkillPtr smithing_skill;
    if (creature && (smithing_skill = creature->get_skills().get_skill(SKILL_GENERAL_SMITHING)) != nullptr)
    {
      if (smithing_skill->get_value() <= 0)
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_NO_SMITHING_SKILL));
        manager.send();

        return false;
      }
    }

    // Either weapon a club/hammer?
    if (!((weapon1 && weapon1->get_trained_skill() == SKILL_MELEE_BLUDGEONS) ||
        (weapon2 && weapon2->get_trained_skill() == SKILL_MELEE_BLUDGEONS)))
    {
      // Inform the creature of the lack of suitable hammer.
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_NO_SUITABLE_HAMMER));
      manager.send();

      return false;
    }
  }

  // Have a chunk of ore or something similar?
  if (!creature->get_inventory()->has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE))
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_NO_INGOTS));
    manager.send();

    return false;
  }

  // The creature's got some skill in smithing, is wielding the appropriate
  // weapon, and has something to smith with.
  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();

  // Empty string means no particular value required; item just has to have this
  // property.
  //
  // We want to match all items that have the "smithing material property", which
  // implies the item can be used to improve other items in smithing.
  vector<pair<string, string>> item_property_filter = {make_pair(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE, "")};

  // Select an ingot-type item.
  list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);
  ItemPtr selected_ingot = am.inventory(creature, creature->get_inventory(), display_filter_list, false);

  if (selected_ingot)
  {
    // Select the item to smith.
    MaterialType ingot_material = static_cast<MaterialType>(String::to_int(selected_ingot->get_additional_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE)));
    list<IItemFilterPtr> smithable_item_list = ItemFilterFactory::create_material_type_filter(ingot_material);
    list<IItemFilterPtr> weapon_or_armour_filter = ItemFilterFactory::create_item_type_filter(list<ItemType>{ITEM_TYPE_WEAPON, ITEM_TYPE_ARMOUR});

    // Create a filter list that contains all weapons and armour that match the material type.
    copy(weapon_or_armour_filter.begin(), weapon_or_armour_filter.end(), back_inserter(smithable_item_list));

    ItemPtr selected_item = am.inventory(creature, creature->get_inventory(), smithable_item_list, false);

    if (selected_item)
    {
      if (selected_item->get_artifact())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_ARTIFACT_SELECTED));
        manager.send();
      }
      else if (!selected_item->can_smith())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_FULL_POTENTIAL));
        manager.send();
      }
      else
      {
        // Use up an ingot.
        int num_ingot = selected_ingot->get_quantity();
        if (num_ingot > 1)
        {
          selected_ingot->set_quantity(num_ingot - 1);
        }
        else
        {
          creature->get_inventory()->remove(selected_ingot->get_id());
        }

        // Improve the item.
        int num_points = RNG::range(2, 3);

        // If the creature's good at smithing, there's a chance it gets an extra
        // point to work with.
        bool extra_point = RNG::percent_chance(creature->get_skills().get_value(SKILL_GENERAL_SMITHING));
        if (extra_point) num_points++;

        selected_item->smith(num_points);

        // Let the player know the smithing was successful.
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_SUCCESSFUL));
        manager.send();
      }
    }
  }

  return true;
}


