#include "WheatFieldGenerator.hpp"
#include "CoordUtils.hpp"
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

  generate_field(result_map);
  generate_divisions(result_map, {}, 2);
  place_scarecrow(result_map);

  return result_map;
}

void WheatFieldGenerator::generate_field(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
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
        }

        TilePtr tile = tg.generate(tt);
        map->insert({ y, x }, tile);
      }
    }
  }
}

// Generates little divisions in the field. This is to keep it from having an
// overwhelming "block of wheat" structure and make it look nice. Trees are
// planted in the divisions to serve as wind breaks and protect the topsoil.
void WheatFieldGenerator::generate_divisions(MapPtr map, const vector<pair<Coordinate, Coordinate>>& divisions, const int count)
{
  if (map != nullptr)
  {
    vector<pair<Coordinate, Coordinate>> divs = divide_field(map, divisions, count);
    TileGenerator tg;

    for (const pair<Coordinate, Coordinate>& div : divs)
    {
      vector<Coordinate> div_c = CoordUtils::get_coordinates_in_range(div.first, div.second);

      for (const Coordinate& dc : div_c)
      {
        TilePtr tile = tg.generate(TileType::TILE_TYPE_FIELD);
        map->insert(dc, tile);
      }
    }

    if (!divs.empty() && RNG::percent_chance(70))
    {
      pair<Coordinate, Coordinate> row = divs.at(0);
      Coordinate c = row.first;

      if (RNG::percent_chance(50))
      {
        c = row.second;
      }

      ItemPtr shovel = ItemManager::create_item(ItemIdKeys::ITEM_ID_SHOVEL);
      map->at(c)->get_items()->merge_or_add(shovel, InventoryAdditionType::INVENTORY_ADDITION_BACK);
    }
  }
}

vector<pair<Coordinate, Coordinate>> WheatFieldGenerator::divide_field(MapPtr map, const vector<pair<Coordinate, Coordinate>>& divisions, const int count)
{
  auto div = divisions;

  if (map != nullptr)
  {
    int cnt = count;

    // To generate variety, there's a chance of reducing the total number of divisions
    for (int i = 0; i < count; i++)
    {
      if (RNG::percent_chance(20))
      {
        cnt--;
      }
    }

    if (cnt <= 0)
    {
      return {};
    }

    // Generate a horizontal or vertical line
    Dimensions dim = map->size();
    bool horizontal = RNG::percent_chance(50);
    Coordinate startc = { 0,0 };
    Coordinate endc = { 0, 0 };
    vector<pair<Coordinate, Coordinate>> divs;

    if (horizontal)
    {
      int block = dim.get_y() / 5;
      int rand_row = RNG::range(block, dim.get_y());
      startc = { rand_row, 1 };
      endc = { rand_row, dim.get_x() - 2 };
    }
    else
    {
      int block = dim.get_x() / 5;
      int rand_col = RNG::range(block, dim.get_y());
      startc = { 1, rand_col };
      endc = { dim.get_y() - 2, rand_col };
    }

    GeneratorUtils::fill(map, startc, endc, TileType::TILE_TYPE_ROCKY_EARTH);
    divs = divide_field(map, divs, cnt - 1);

    div.insert(div.end(), divs.begin(), divs.end());
  }

  return div;
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