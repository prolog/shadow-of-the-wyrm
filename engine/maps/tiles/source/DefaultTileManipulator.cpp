#include "DefaultTileManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureGenerationManager.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemGenerationManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

const int DefaultTileManipulator::UNDEAD_LEVEL_UPPER_BOUND_OFFSET = 5;
const int DefaultTileManipulator::PCT_CHANCE_DETRITUS = 30;
const int DefaultTileManipulator::PCT_CHANCE_CLAY = 4;
const int DefaultTileManipulator::PCT_CHANCE_CLAY_NEARBY = 40;

DefaultTileManipulator::DefaultTileManipulator()
  : super_type_message_sids({ { TileSuperType::TILE_SUPER_TYPE_GROUND, ActionTextKeys::ACTION_DIG_GROUND },
                             { TileSuperType::TILE_SUPER_TYPE_WATER, ActionTextKeys::ACTION_DIG_WATER },
                             { TileSuperType::TILE_SUPER_TYPE_AIR, ActionTextKeys::ACTION_DIG_AIR } })
{
}

// Add a default digging message based on the creature and the tile super
// type - "Splash!" for water, "Whoosh!" for air, etc.
bool DefaultTileManipulator::dig(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  bool dug = false;

  if (creature != nullptr && tile != nullptr)
  {
    TileSuperType super_type = tile->get_tile_super_type();

    if (creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();

      auto s_it = super_type_message_sids.find(super_type);
      if (s_it != super_type_message_sids.end())
      {
        manager.add_new_message(StringTable::get(super_type_message_sids[super_type]));
        manager.send();
      }
    }

    // Only add undead/items if the tile has not been dug already.
    if (!(tile->get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG) == std::to_string(true)))
    {
      add_undead_if_necessary(creature, map, tile);
      add_item_if_necessary(creature, map, tile);
    }

    dug = true;
  }

  return dug;
}

// Potentially add an undead creature around the creature doing the digging.
void DefaultTileManipulator::add_undead_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  if (tile != nullptr)
  {
    int pct_chance_undead = tile->get_dig_chances().get_pct_chance_undead();

    string pct_chance_undead_override = tile->get_additional_property(TileProperties::TILE_PROPERTY_PCT_CHANCE_UNDEAD);
    if (!pct_chance_undead_override.empty())
    {
      pct_chance_undead = String::to_int(pct_chance_undead_override);
    }

    if (RNG::percent_chance(pct_chance_undead))
    {
      int min_danger_level = std::max<int>(1, creature->get_level().get_current() / 2);
      int max_danger_level = std::max<int>(1, map->get_danger()) + UNDEAD_LEVEL_UPPER_BOUND_OFFSET;

      Game& game = Game::instance();
      CreaturePtr undead;
      CreatureGenerationManager cgm;
      std::map<string, string> additional_properties = { { MapProperties::MAP_PROPERTIES_GENERATED_CREATURE_RACE_ID, "_undead" } };
      CreatureGenerationIndex generation_index = cgm.generate_creature_generation_map({ tile->get_tile_type() }, map->get_permanent(), map->is_islet(), map->get_map_type(), min_danger_level, max_danger_level, Rarity::RARITY_VERY_RARE, additional_properties);

      undead = cgm.generate_creature(game.get_action_manager_ref(), generation_index.get(), map);
      
      if (undead != nullptr)
      {
        // Add the undead to the map: randomize the adjacent tiles, and then
        // iterate through the tiles, trying to place.
        bool placed = false;

        TileDirectionMap directions = MapUtils::get_adjacent_tiles_to_creature(map, creature);
        vector<Direction> keys;
        for (const auto& d : directions)
        {
          keys.push_back(d.first);
        }

        std::random_shuffle(keys.begin(), keys.end());

        for (const auto& direction : keys)
        {
          TilePtr d_tile = directions.at(direction);

          if (d_tile != nullptr && !d_tile->has_creature())
          {
            Coordinate undead_coords = CoordUtils::get_new_coordinate(MapUtils::get_coordinate_for_creature(map, creature), direction);
            GameUtils::add_new_creature_to_map(game, undead, map, undead_coords);

            placed = true;
            break;
          }
        }

        // Add a message about the dead rising...
        if (placed && creature->get_is_player())
        {
          IMessageManager& manager = MM::instance();

          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_UNDEAD_FOUND));
          manager.send();
        }
      }
    }
  }
}

// Potentially add an item to the tile being digged.
// As valuable items are often buried, any item within the danger level
// range can be found via digging.
void DefaultTileManipulator::add_item_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  if (tile != nullptr)
  {
    DigChances dc = tile->get_dig_chances();
    ItemManager im;
    Game& game = Game::instance();
    const ItemMap& items = game.get_items_ref();
    vector<string> item_ids = dc.get_item_ids();

    add_detritus(creature, map, tile);

    int pct_chance_item = dc.get_pct_chance_item();
    string pct_chance_item_override = tile->get_additional_property(TileProperties::TILE_PROPERTY_PCT_CHANCE_ITEMS);
    if (!pct_chance_item_override.empty())
    {
      pct_chance_item = String::to_int(pct_chance_item_override);
    }

    if (RNG::percent_chance(pct_chance_item))
    {
      int danger_level = map->get_danger();

      ItemGenerationManager igm;
      vector<ItemType> i_restr = {};
      ItemGenerationMap igmap = igm.generate_item_generation_map({1, std::max<int>(danger_level, creature->get_level().get_current()), Rarity::RARITY_VERY_RARE, i_restr, ItemValues::DEFAULT_MIN_GENERATION_VALUE});

      ActionManager& am = game.get_action_manager_ref();

      bool items_placed = false;
      int num_items_found = RNG::range(1, 3);

      for (int i = 0; i < num_items_found; i++)
      {
        ItemPtr item;

        if (item_ids.empty())
        {
          item = igm.generate_item(am, igmap, Rarity::RARITY_RARE, i_restr, RNG::range(1, static_cast<int>(danger_level / 2)));
        }
        else
        {
          string item_id = item_ids.at(RNG::range(0, item_ids.size()-1));
          item = im.create_item(items, item_id, 1);
        }
        
        if (item != nullptr)
        {
          tile->get_items()->add(item);
          items_placed = true;
        }
      }

      if (items_placed && creature->get_is_player())
      {
        IMessageManager& manager = MM::instance();

        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_ITEM_FOUND));
        manager.send();
      }
    }
  }
}

void DefaultTileManipulator::add_detritus(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  if (creature != nullptr && map != nullptr && tile != nullptr)
  {
    ItemManager im;
    auto tiles = MapUtils::get_adjacent_tiles_to_creature_unsorted(map, creature);
    IInventoryPtr items = tile->get_items();
    int chance_clay = PCT_CHANCE_CLAY;

    for (TilePtr adj_tile : tiles)
    {
      if (adj_tile != nullptr)
      {
        if (adj_tile->get_water_type() == WaterType::WATER_TYPE_FRESH)
        {
          chance_clay = 100;
          break;
        }
        if (adj_tile->get_additional_property(TileProperties::TILE_PROPERTY_CLAY) == "1")
        {
          chance_clay = PCT_CHANCE_CLAY_NEARBY;
          break;
        }
      }
    }

    if (RNG::percent_chance(chance_clay))
    {
      ItemPtr clay = im.create_item(ItemIdKeys::ITEM_ID_CLAY);
      items->merge_or_add(clay, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      tile->set_additional_property(TileProperties::TILE_PROPERTY_CLAY, std::to_string(true));
    }

    vector<string> general_detritus_ids = { ItemIdKeys::ITEM_ID_STONE, ItemIdKeys::ITEM_ID_ROCK };

    for (const string& detritus : general_detritus_ids)
    {
      if (RNG::percent_chance(PCT_CHANCE_DETRITUS))
      {
        ItemPtr item = im.create_item(detritus, RNG::range(1,4));
        items->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }
  }
}
