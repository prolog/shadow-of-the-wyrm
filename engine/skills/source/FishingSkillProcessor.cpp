#include "ActionTextKeys.hpp"
#include "FishingSkillProcessor.hpp"
#include "ItemTypes.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

ActionCostValue FishingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature && map)
  {
    // Does the creature have the necessary equipment?
    bool has_fishing_eq = check_for_fishing_equipment(creature);

    if (has_fishing_eq)
    {
      // Are we land-locked?
      bool adj_water = check_for_adjacent_water_tile(creature, map);
    }
  }

  return acv;
}

bool FishingSkillProcessor::check_for_fishing_equipment(CreaturePtr creature)
{
  bool has_fishing_eq = false;

  if (creature != nullptr)
  {
    ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    ItemPtr off_hand = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);

    if ((wielded != nullptr && wielded->get_base_id() == ItemIdKeys::ITEM_ID_FISHING_ROD) || (off_hand != nullptr && off_hand->get_base_id() == ItemIdKeys::ITEM_ID_FISHING_ROD))
    {
      has_fishing_eq = true;
    }

    if (!has_fishing_eq && creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FISHING_NO_EQUIPMENT));
      manager.send();
    }
  }

  return has_fishing_eq;
}

bool FishingSkillProcessor::check_for_adjacent_water_tile(CreaturePtr creature, MapPtr map)
{
  bool adj_water = false;
  TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);

  bool adjacent_water = false;

  if (creature != nullptr)
  {
    for (const auto& tdm_pair : tdm)
    {
      TilePtr tile = tdm_pair.second;

      if (tile != nullptr)
      {
        TileSuperType tst = tile->get_tile_super_type();

        if (tst == TileSuperType::TILE_SUPER_TYPE_WATER)
        {
          adjacent_water = true;
          break;
        }
      }
    }

    if (!adjacent_water && creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FISHING_NO_WATER));
      manager.send();
    }
  }

  return adj_water;
}
