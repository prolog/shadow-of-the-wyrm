#include "WheatFieldGenerator.hpp"
#include "CreatureFactory.hpp"
#include "CreatureTypes.hpp"
#include "ForestCalculator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int WheatFieldGenerator::PCT_CHANCE_SCARECROW = 90;
const int WheatFieldGenerator::PCT_CHANCE_LIVING_SCARECROW = 25;

WheatFieldGenerator::WheatFieldGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_WHEAT)
{
}

MapPtr WheatFieldGenerator::generate(const Dimensions& dim)
{
  MapPtr result_map = std::make_shared<Map>(dim);

  int rows = dim.get_y();
  int cols = dim.get_x();
  TileType tt;
  TileGenerator tg;

  for (int y = 0; y < rows; y++)
  {
    for (int x = 0; x < cols; x++)
    {
      if (y == 0 || x == 0 || y == rows - 1 || x == cols - 1)
      {
        tt = TileType::TILE_TYPE_FIELD;
      }
      else
      {
        tt = TileType::TILE_TYPE_WHEAT;

        if (RNG::x_in_y_chance(1, 150))
        {
          tt = TileType::TILE_TYPE_TREE;
        }
      }


      TilePtr tile = tg.generate(tt);
      result_map->insert({ y, x }, tile);
    }
  }

  place_scarecrow(result_map);

  return result_map;
}

void WheatFieldGenerator::place_scarecrow(MapPtr map)
{
  if (map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_SCARECROW))
    {
      string scarecrow_id = ItemIdKeys::ITEM_ID_SCARECROW;
      Dimensions dim = map->size();
      Coordinate c = { RNG::range(1, dim.get_y() - 2), RNG::range(1, dim.get_x() - 2) };

      if (RNG::percent_chance(PCT_CHANCE_LIVING_SCARECROW))
      {
        scarecrow_id = CreatureID::CREATURE_ID_LIVING_SCARECROW;
        Game& game = Game::instance();
        CreatureFactory cf;
        CreaturePtr creature = cf.create_by_creature_id(game.get_action_manager_ref(), scarecrow_id, map);
        GameUtils::add_new_creature_to_map(game, creature, map, c);
      }
      else
      {
        ItemPtr scarecrow = ItemManager::create_item(scarecrow_id);
        map->at(c)->get_items()->merge_or_add(scarecrow, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
      }
    }
  }
}