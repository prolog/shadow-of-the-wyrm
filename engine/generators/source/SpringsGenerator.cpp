#include "CreatureFactory.hpp"
#include "CreatureFeatures.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "RNG.hpp"
#include "SpringsGenerator.hpp"
#include "TileGenerator.hpp"
#include "SpringsTile.hpp"

const int SpringsGenerator::PCT_CHANCE_FAIRY_SPIRIT = 50;

MapPtr SpringsGenerator::generate(MapPtr map, const int start_row, const int start_col, const int springs_size, const SpringsType type)
{
  MapPtr result_map = std::make_shared<Map>(*map);

  if (type == SpringsType::SPRINGS_TYPE_WIDE)
  {
    result_map = generate_wide(result_map, start_row, start_col, springs_size);
  }
  else if (type == SpringsType::SPRINGS_TYPE_TALL)
  {
    result_map = generate_tall(result_map, start_row, start_col, springs_size);
  }

  return result_map;
}

MapPtr SpringsGenerator::generate_wide(MapPtr map, const int start_row, const int start_col, const int springs_size)
{
  TileGenerator tg;
  MapPtr result_map = std::make_shared<Map>(*map);

  int first_row;
  int second_row;
  int col_start   = start_col;
  int centre_line = start_row;
  int spring_size = springs_size;

  // Find the centre line.
  for (int y = springs_size; y >= 1; y = y - 2)
  {
    centre_line++;
  }

  first_row = second_row = centre_line;

  while (spring_size > 0)
  {
    for (int col = col_start; col < (start_col + spring_size); col++)
    {
      TilePtr springs_tile = tg.generate(TileType::TILE_TYPE_SPRINGS);
      result_map->insert(first_row, col, springs_tile);
    }

    if (second_row != first_row)
    {
      for (int col = col_start; col < (start_col + spring_size); col++)
      {
        TilePtr second_springs_tile = tg.generate(TileType::TILE_TYPE_SPRINGS);
        result_map->insert(second_row, col, second_springs_tile);
      }
    }

    first_row--;
    second_row++;
    col_start++;
    spring_size = spring_size - 1;
  }

  add_fairy_spirit_if_necessary(result_map, centre_line, (start_col + springs_size / 2));

  return result_map;
}

MapPtr SpringsGenerator::generate_tall(MapPtr map, const int start_row, const int start_col, const int springs_size)
{
  TileGenerator tg;
  MapPtr result_map = std::make_shared<Map>(*map);

  int first_col;
  int second_col;
  int row_start   = start_row;
  int centre_line = start_col;
  int spring_size = springs_size;

  // Find the centre line.
  for (int x = springs_size; x >= 1; x = x - 2)
  {
    centre_line++;
  }

  first_col = second_col = centre_line;

  while (spring_size > 0)
  {
    for (int row = row_start; row < (start_row + spring_size); row++)
    {
      TilePtr springs_tile = tg.generate(TileType::TILE_TYPE_SPRINGS);
      result_map->insert(row, first_col, springs_tile);
    }

    if (second_col != first_col)
    {
      for (int row = row_start; row < (start_row + spring_size); row++)
      {
        TilePtr second_springs_tile = tg.generate(TileType::TILE_TYPE_SPRINGS);
        result_map->insert(row, second_col, second_springs_tile);
      }
    }

    first_col--;
    second_col++;
    row_start++;

    spring_size = spring_size - 1;
  }

  add_fairy_spirit_if_necessary(result_map, start_row + (springs_size / 2), centre_line);

  return result_map;
}

void SpringsGenerator::add_fairy_spirit_if_necessary(MapPtr result_map, const int row, const int col)
{
  // Chance of generating a fairy spirit.
  if (RNG::percent_chance(PCT_CHANCE_FAIRY_SPIRIT))
  {
    Game& game = Game::instance();
    CreatureFactory cf;

    CreaturePtr spirit = cf.create_by_creature_id(game.get_action_manager_ref(), CreatureID::CREATURE_ID_FAIRY_SPIRIT);
    GameUtils::add_new_creature_to_map(game, spirit, result_map, {row, col});

    result_map->set_permanent(true);
  }
}