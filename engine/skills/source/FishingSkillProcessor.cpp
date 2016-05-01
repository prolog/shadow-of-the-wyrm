#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "FishingCalculator.hpp"
#include "FishingSkillProcessor.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

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
    bool has_fishing_eq = check_for_fishing_equipment(creature);

    if (has_fishing_eq)
    {
      // Are we land-locked?
      pair<bool, WaterType> adj_water = check_for_adjacent_water_tile(creature, map);

      if (adj_water.first)
      {
        fish(creature, map, adj_water.second);
      }
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
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FISHING_NO_WATER));
      manager.send();
    }
  }

  return adj_water;
}

void FishingSkillProcessor::fish(CreaturePtr creature, MapPtr map, const WaterType water)
{
  FishingCalculator fc;
  Game& game = Game::instance();
  vector<pair<FishingOutcomeType, int>> outcomes = fc.calculate_fishing_outcomes(creature);
  
  for (const auto& outcome_pair : outcomes)
  {
    if (RNG::percent_chance(outcome_pair.second))
    {
      FishingOutcomeType fot = outcome_pair.first;

      // Add a message about fishing, if appropriate
      if (creature && creature->get_is_player())
      {
        IMessageManager& manager = MessageManagerFactory::instance();
        manager.add_new_message(ActionTextKeys::get_random_bait_message());
        manager.add_new_message(ActionTextKeys::get_fishing_outcome_message(fot));
        manager.send();
      }

      // If the creature caught something, add it to the tile
      if (fot == FishingOutcomeType::FISHING_OUTCOME_CATCH)
      {
        TilePtr creature_tile = map->at(map->get_location(creature->get_id()));

        if (creature_tile != nullptr)
        {
          auto f_it = fish_types.find(water);

          if (f_it != fish_types.end())
          {
            vector<string> fishies = f_it->second;
            
            if (!fishies.empty())
            {
              string fish_type = fishies.at(RNG::range(0, fishies.size()-1));
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

              // If the creature's on terra firma, add it to the ground
              if (creature_tile->get_tile_super_type() == TileSuperType::TILE_SUPER_TYPE_GROUND)
              {
                creature_tile->get_items()->add_front(fish);
              }
              // If the creature's on water (air?!), try to add it to the 
              // creature's inventory.
              else
              {
                // ... JCD FIXME ...
              }
            }
          }
        }
      }

      // Don't try any other fishing outcomes.
      break;
    }
  }
}

// Fishing takes a very long time.
ActionCostValue FishingSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 100;
}