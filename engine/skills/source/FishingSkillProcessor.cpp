#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "FishingCalculator.hpp"
#include "FishingSkillProcessor.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemIdentifier.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "Weapon.hpp"

using namespace std;

const int FishingSkillProcessor::CATCH_PCT_CHANCE_FISH = 95;

FishingSkillProcessor::FishingSkillProcessor()
: fish_types{{WaterType::WATER_TYPE_FRESH, {ItemIdKeys::ITEM_ID_TROUT, ItemIdKeys::ITEM_ID_CARP, ItemIdKeys::ITEM_ID_PIKE}}, 
             {WaterType::WATER_TYPE_SALT,  {ItemIdKeys::ITEM_ID_SALMON, ItemIdKeys::ITEM_ID_TUNA, ItemIdKeys::ITEM_ID_COD}}}
{
}

ActionCostValue FishingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature && map)
  {
    // Does the creature have the necessary equipment?
    TilePtr creature_tile = MapUtils::get_tile_for_creature(map, creature);
    pair<bool, FishingType> fishing_details = check_for_fishing_equipment(creature, creature_tile);
    bool has_fishing_eq = fishing_details.first;

    if (has_fishing_eq)
    {
      // Are we land-locked?
      pair<bool, WaterType> adj_water = check_for_adjacent_water_tile(creature, map);

      if (adj_water.first)
      {
        fish(creature, map, fishing_details.second, adj_water.second);
      }
    }
  }

  return acv;
}

pair<bool, FishingType> FishingSkillProcessor::check_for_fishing_equipment(CreaturePtr creature, TilePtr creature_tile)
{
  pair<bool, FishingType> fishing_details = make_pair(false, FishingType::FISHING_TYPE_NONE);

  if (creature != nullptr && creature_tile != nullptr)
  {
    ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    ItemPtr off_hand = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);
    WeaponPtr wielded_weap = std::dynamic_pointer_cast<Weapon>(wielded);
    string bad_eq_msg = ActionTextKeys::ACTION_FISHING_NO_EQUIPMENT;

    if ((wielded != nullptr && wielded->get_base_id() == ItemIdKeys::ITEM_ID_FISHING_ROD) || (off_hand != nullptr && off_hand->get_base_id() == ItemIdKeys::ITEM_ID_FISHING_ROD))
    {
      fishing_details.first = true;
      fishing_details.second = FishingType::FISHING_TYPE_ROD_AND_LINE;
    }

    // Spearfishing only works if you're wielding the spear - it doesn't work
    // in your off hand.
    if (wielded_weap && wielded_weap->get_trained_skill() == SkillType::SKILL_MELEE_SPEARS)
    {
      fishing_details.second = FishingType::FISHING_TYPE_SPEAR;

      if (creature_tile->get_tile_super_type() == TileSuperType::TILE_SUPER_TYPE_WATER)
      {
        bad_eq_msg = ActionTextKeys::ACTION_FISHING_SPEARFISHING_WATER;
      }
      else
      {
        fishing_details.first = true;
      }
    }

    if (!fishing_details.first && creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(bad_eq_msg));
      manager.send();
    }
  }

  return fishing_details;
}

pair<bool, WaterType> FishingSkillProcessor::check_for_adjacent_water_tile(CreaturePtr creature, MapPtr map)
{
  pair<bool, WaterType> adj_water = {false, WaterType::WATER_TYPE_UNDEFINED};
  TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);

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
          adj_water.first = true;
          adj_water.second = tile->get_water_type();

          break;
        }
      }
    }

    if (!adj_water.first && creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FISHING_NO_WATER));
      manager.send();
    }
  }

  return adj_water;
}

void FishingSkillProcessor::fish(CreaturePtr creature, MapPtr map, const FishingType fishing, const WaterType water)
{
  FishingCalculator fc;
  vector<pair<FishingOutcomeType, int>> outcomes = fc.calculate_fishing_outcomes(creature);
  
  for (const auto& outcome_pair : outcomes)
  {
    if (RNG::percent_chance(outcome_pair.second))
    {
      FishingOutcomeType fot = outcome_pair.first;

      // Add a message about fishing, if appropriate
      if (creature && creature->get_is_player())
      {
        IMessageManager& manager = MM::instance();
        manager.add_new_message(ActionTextKeys::get_random_bait_message(fishing));
        manager.add_new_message(ActionTextKeys::get_fishing_outcome_message(fishing, fot));
        manager.send();
      }

      // If the creature caught something, add it to the tile
      if (fot == FishingOutcomeType::FISHING_OUTCOME_CATCH)
      {
        if (RNG::percent_chance(CATCH_PCT_CHANCE_FISH))
        {
          catch_fish(creature, map, water);
        }
        else
        {
          catch_item(creature, map);
        }
      }

      // Don't try any other fishing outcomes.
      break;
    }
  }
}

void FishingSkillProcessor::catch_fish(CreaturePtr creature, MapPtr map, const WaterType water)
{
  if (creature != nullptr && map != nullptr)
  {
    Game& game = Game::instance();
    TilePtr creature_tile = map->at(map->get_location(creature->get_id()));

    if (creature_tile != nullptr)
    {
      auto f_it = fish_types.find(water);

      if (f_it != fish_types.end())
      {
        vector<string> fishies = f_it->second;

        if (!fishies.empty())
        {
          string fish_type = fishies.at(RNG::range(0, fishies.size() - 1));
          ItemPtr fish = ItemManager::create_item(fish_type);
          ConsumablePtr food = dynamic_pointer_cast<Consumable>(fish);

          // There's some variation in size between every fish.
          if (food != nullptr)
          {
            float size_variation = RNG::range_f(0.5, 1.5);
            Weight new_weight = food->get_weight();
            new_weight.set_weight(static_cast<uint>(new_weight.get_weight() * size_variation));

            food->set_nutrition(static_cast<int>(food->get_nutrition() * size_variation));
            food->set_weight(new_weight);
          }

          // A fish has been caught - the map should now become permanent.
          GameUtils::make_map_permanent(game, creature, map);

          // Add the fish to the inventory, if possible.
          if (CreatureUtils::can_pick_up(creature, fish).first)
          {
            IInventoryPtr inv = creature->get_inventory();
            if (!inv->merge(fish))
            {
              // Add to the end of the inventory
              inv->add(fish);
            }
          }
          else
          {
            if (creature && creature->get_is_player())
            {
              IMessageManager& manager = MM::instance();
              manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FISHING_THROW_BACK));
              manager.send();
            }
          }
        }
      }
    }
  }
}

void FishingSkillProcessor::catch_item(CreaturePtr creature, MapPtr map)
{
  if (creature != nullptr && map != nullptr)
  {
    Game& game = Game::instance();
    ItemGenerationManager igm;
    Rarity rarity = Rarity::RARITY_COMMON;
    ItemEnchantmentCalculator iec;
    int danger_level = map->get_danger();

    int enchant_points = iec.calculate_enchantments(danger_level);
    ItemGenerationMap generation_map = igm.generate_item_generation_map({ 1, creature->get_level().get_current(), Rarity::RARITY_COMMON, {}, ItemValues::DEFAULT_MIN_GENERATION_VALUE });
    ItemPtr generated_item = igm.generate_item(game.get_action_manager_ref(), generation_map, rarity, {}, enchant_points);

    TilePtr creature_tile = MapUtils::get_tile_for_creature(map, creature);

    if (creature_tile != nullptr && generated_item != nullptr)
    {
      // Can only pull in one item at a time while fishing.
      generated_item->set_quantity(1);
      IInventoryPtr items = creature_tile->get_items();

      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

      if (CreatureUtils::can_pick_up(creature, generated_item).first)
      {
        IInventoryPtr inv = creature->get_inventory();
        inv->merge_or_add(generated_item, InventoryAdditionType::INVENTORY_ADDITION_BACK);

        // Add a message about the item that was added to the pack.
        ItemIdentifier iid;
        manager.add_new_message(ActionTextKeys::get_item_pack_message(creature->get_description_sid(), creature->get_is_player(), iid.get_appropriate_usage_description(generated_item)));
      }
      else
      {
        if (creature && creature->get_is_player())
        {
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FISHING_THROW_BACK));
        }
      }

      manager.send();
    }
  }
}

// Fishing takes a very long time.
ActionCostValue FishingSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return ActionCostConstants::FISHING;
}