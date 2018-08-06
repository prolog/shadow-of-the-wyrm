#include "MapItemGenerator.hpp"
#include "Conversion.hpp"
#include "CreationUtils.hpp"
#include "Game.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemGenerationManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

const int MapItemGenerator::OUT_OF_DEPTH_ITEMS_CHANCE = 15;

// Generate items based on the provided danger level, and place them
// on the given map.
bool MapItemGenerator::generate_items(MapPtr map, const int danger_level, const tuple<bool, int, Rarity>& creature_details)
{
  bool items_generated = false;

  Dimensions dim = map->size();
  pair<Coordinate, Coordinate> g_coords = map->get_generation_coordinates();

  ItemGenerationManager igm;

  bool creature_danger_override = std::get<0>(creature_details);
  int creature_danger_level = std::get<1>(creature_details);
  Rarity creature_rarity = std::get<2>(creature_details);

  Rarity rarity = CreationUtils::generate_rarity();

  // The minimum rarity should always be what was used for creature generation.
  if (rarity < creature_rarity)
  {
    rarity = creature_rarity;
  }

  Game& game = Game::instance();

  ActionManager am = game.get_action_manager_ref();
  uint num_items_to_place = RNG::range(1, CreationUtils::random_maximum_items(dim.get_y(), dim.get_x()));
  uint current_items_placed = 0;
  uint unsuccessful_attempts = 0;
  int max_danger_level = danger_level;

  // Small chance to keep increasing the max item danger level
  while (RNG::percent_chance(OUT_OF_DEPTH_ITEMS_CHANCE))
  {
    max_danger_level++;
  }

  // Take the max of the current max danger level and the one used for
  // creature generation.
  if (creature_danger_override && creature_danger_level > 0)
  {
    max_danger_level = std::max<int>(max_danger_level, creature_danger_level);
  }

  // Generate the vector of possible items for this map.
  vector<ItemType> i_restr = {};
  ItemGenerationMap generation_map = igm.generate_item_generation_map({1, max_danger_level, rarity, i_restr, ItemValues::DEFAULT_MIN_GENERATION_VALUE});
  ItemEnchantmentCalculator iec;

  while ((current_items_placed < num_items_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_ITEM_ATTEMPTS))
  {
    int enchant_points = iec.calculate_enchantments(danger_level);
    ItemPtr generated_item = igm.generate_item(am, generation_map, rarity, i_restr, enchant_points);

    bool placed_item = false;

    if (generated_item)
    {
      while (!placed_item)
      {
        int item_row = RNG::range(g_coords.first.first, g_coords.second.first);
        int item_col = RNG::range(g_coords.first.second, g_coords.second.second);

        // Check to see if the tile isn't blocking
        TilePtr tile = map->at(item_row, item_col);

        if (MapUtils::is_tile_available_for_item(tile))
        {
          tile->get_items()->add(generated_item);

          if (!items_generated) items_generated = true;
          current_items_placed++;
          placed_item = true;
        }
        else
        {
          unsuccessful_attempts++;
        }
      }
    }
    else
    {
      unsuccessful_attempts++;
    }
  }

  return items_generated;
}

bool MapItemGenerator::generate_initial_set_items(MapPtr map, const std::map<string, string>& properties)
{
  bool items_generated = false;

  // First, check to see if there are any set items specified.
  auto ii_it = properties.find(MapProperties::MAP_PROPERTIES_INITIAL_ITEMS);
  if (ii_it != properties.end())
  {
    string initial_items_csv = ii_it->second;
    vector<string> ii_v = String::create_string_vector_from_csv_string(initial_items_csv);
    vector<TilePtr> item_tiles = MapUtils::get_tiles_supporting_items(map);

    if (!item_tiles.empty())
    {
      for (const auto& i_id : ii_v)
      {
        TilePtr tile = item_tiles.at(RNG::range(0, item_tiles.size() - 1));

        if (tile != nullptr)
        {
          ItemPtr item = ItemManager::create_item(i_id);
          tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);

          if (!items_generated)
          {
            items_generated = true;
          }
        }
      }
    }
  }

  return items_generated;
}

bool MapItemGenerator::repop_shop(MapPtr map, const string& shop_id)
{
  bool repop = false;

  if (map != nullptr)
  {
    std::map<string, Shop> shops = map->get_shops();
    auto s_it = shops.find(shop_id);

    if (s_it != shops.end())
    {
      repop = true;

      Shop shop = s_it->second;
      Coordinate start = shop.get_start();
      Coordinate end = shop.get_end();
      vector<ItemType> stocked_types = shop.get_stocked_item_types();
      int danger_level = map->get_danger();
      Rarity rarity = Rarity::RARITY_VERY_RARE;

      // Repopulate...
      ItemGenerationManager igm;
      ItemGenerationMap generation_map = igm.generate_item_generation_map({1, danger_level, rarity, stocked_types, ItemValues::DEFAULT_MIN_SHOP_VALUE});
      ItemEnchantmentCalculator iec;
      Game& game = Game::instance();
      ActionManager am = game.get_action_manager_ref();

      for (int row = start.first; row <= end.first; row++)
      {
        for (int col = start.second; col <= end.second; col++)
        {
          // Are there any unpaid items here?  If so, skip item generation
          // for that tile.
          TilePtr tile = map->at(row, col);

          if (tile)
          {
            IInventoryPtr items = tile->get_items();

            if (items != nullptr && items->has_unpaid_items())
            {
              continue;
            }
          }

          int enchant_points = iec.calculate_enchantments(danger_level);
          ItemPtr shop_item = igm.generate_item(am, generation_map, rarity, stocked_types, enchant_points);

          if (shop_item != nullptr)
          {
            shop_item->set_unpaid(true);

            TilePtr tile = map->at(row, col);

            if (tile != nullptr)
            {
              IInventoryPtr inv = tile->get_items();

              if (inv != nullptr)
              {
                inv->merge_or_add(shop_item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
              }
            }
          }
        }
      }
    }
  }

  return repop;
}
