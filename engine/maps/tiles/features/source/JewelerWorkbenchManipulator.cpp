#include "JewelerWorkbenchManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SmithingConstants.hpp"

using namespace std;

JewelerWorkbenchManipulator::JewelerWorkbenchManipulator(FeaturePtr feature)
: ForgeManipulator(feature)
{
}

void JewelerWorkbenchManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_JEWELER_WORKBENCH));
    manager.send();
  }
}

// The jeweler's workbench doesn't require a hammer, like the forge does,
// because the workbench has all the tools required.
bool JewelerWorkbenchManipulator::check_creature_passes_prerequisites(CreaturePtr creature)
{
  if (!check_creature_has_jewelry_skill(creature) ||
      !check_creature_has_ingots(creature))
  {
    return false;
  }

  return true;
}

// Smithing uses iron and steel.  Goldsmithing uses, well, gold.
bool JewelerWorkbenchManipulator::check_creature_has_ingots(CreaturePtr creature)
{
  bool has_ingots = true;

  // Have a chunk of ore or something similar?
  if (!creature->get_inventory()->has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_JEWELRY_MATERIAL_TYPE))
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_NO_INGOTS));
    manager.send();

    has_ingots = false;
  }

  return has_ingots;
}

ItemPtr JewelerWorkbenchManipulator::get_selected_ingot(CreaturePtr creature, ActionManager& am)
{
  vector<pair<string, string>> item_property_filter = { make_pair(SmithingConstants::SMITHING_CONSTANTS_JEWELRY_MATERIAL_TYPE, "") };

  // Select an ingot-type item.
  list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);
  ItemPtr selected_ingot = am.inventory(creature, creature->get_inventory(), display_filter_list, false);

  return selected_ingot;
}

ItemPtr JewelerWorkbenchManipulator::get_selected_item(CreaturePtr creature, ItemPtr ingot, ActionManager& am)
{
  MaterialType ingot_material = static_cast<MaterialType>(String::to_int(ingot->get_additional_property(SmithingConstants::SMITHING_CONSTANTS_JEWELRY_MATERIAL_TYPE)));
  list<IItemFilterPtr> smithable_item_list = ItemFilterFactory::create_material_type_filter(ingot_material);
  list<IItemFilterPtr> ring_or_amulet_filter = ItemFilterFactory::create_item_type_filter(list<ItemType>{ItemType::ITEM_TYPE_RING, ItemType::ITEM_TYPE_AMULET});

  // Create a filter list that contains all weapons and armour that match the material type.
  copy(ring_or_amulet_filter.begin(), ring_or_amulet_filter.end(), back_inserter(smithable_item_list));

  ItemPtr selected_item = am.inventory(creature, creature->get_inventory(), smithable_item_list, false);
  return selected_item;
}

// Check the Jeweler skill.
bool JewelerWorkbenchManipulator::check_creature_has_jewelry_skill(CreaturePtr creature)
{
  bool knows_jewelry = true;

  SkillPtr jeweler_skill;
  if (creature && (jeweler_skill = creature->get_skills().get_skill(SkillType::SKILL_GENERAL_JEWELER)) != nullptr)
  {
    if (jeweler_skill->get_value() <= 0)
    {
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_JEWELER_WORKBENCH_NO_JEWELER_SKILL));
      manager.send();

      knows_jewelry = false;
    }
  }

  return knows_jewelry;
}
