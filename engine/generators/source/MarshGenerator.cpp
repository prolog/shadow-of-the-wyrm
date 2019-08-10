#include "AllTiles.hpp"
#include "ItemManager.hpp"
#include "MarshGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

const int MarshGenerator::PCT_CHANCE_BOG_IRON = 25;

MarshGenerator::MarshGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_MARSH)
{
}

MapPtr MarshGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_MARSH);
  add_random_trees_bushes_weeds_and_reeds(result_map);

  if (RNG::percent_chance(PCT_CHANCE_BOG_IRON))
  {
    add_bog_iron(result_map);
    result_map->set_permanent(true);
  }

  return result_map;
}

TilePtr MarshGenerator::generate_tile(MapPtr current_map, const int row, const int col)
{
  TilePtr result_tile;

  int rand = RNG::range(1, 100);

  if (rand <= 3)
  {
    result_tile = tg.generate(TileType::TILE_TYPE_WEEDS);
  }
  else if (rand <= 4)
  {
    result_tile = tg.generate(TileType::TILE_TYPE_BUSH);
  }
  else if (rand <= 10)
  {
    result_tile = tg.generate(TileType::TILE_TYPE_TREE);
  }
  else if (rand <= 28)
  {
    result_tile = tg.generate(TileType::TILE_TYPE_REEDS);
  }

  return result_tile;
}

void MarshGenerator::add_random_trees_bushes_weeds_and_reeds(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    Dimensions d = result_map->size();
    int rows = d.get_y();
    int cols = d.get_x();

    for (int row = 0; row < rows; row++)
    {
      for (int col = 0; col < cols; col++)
      {
        TilePtr tile = generate_tile(result_map, row, col);

        if (tile)
        {
          result_map->insert(row, col, tile);
        }
      }
    }
  }
}

void MarshGenerator::add_bog_iron(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    Dimensions d = result_map->size();
    int rows = d.get_y();
    int cols = d.get_x();
    int num_iron = cols / 10;
    int rand_y = 0;
    int rand_x = 0;
    ItemPtr bog_iron;

    for (int i = 0; i < num_iron; i++)
    {
      bog_iron = ItemManager::create_item(ItemIdKeys::ITEM_ID_BOG_IRON, RNG::range(1, 2));
      rand_y = RNG::range(0, rows - 1);
      rand_x = RNG::range(0, cols - 1);
      TilePtr tile = result_map->at(rand_y, rand_x);

      if (tile != nullptr)
      {
        tile->get_items()->merge_or_add(bog_iron, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }
  }
}