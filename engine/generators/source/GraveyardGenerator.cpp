#include "GraveyardGenerator.hpp"
#include "Game.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

GraveyardGenerator::GraveyardGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_GRAVEYARD)
, TOMB_MIN_SIZE(7)
, TOMB_MAX_SIZE(7)
, PCT_CHANCE_INSCRIPTION(65)
{
}

MapPtr GraveyardGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(dim);
  fill(map, TileType::TILE_TYPE_FIELD);
  
  add_graves(map);
  add_framing_trees(map);
  add_random_foliage(map);
  
  // This goes last so the foliage/etc doesn't overwrite any of the tiles.
  add_tomb_if_necessary(map);
  
  return map;
}

void GraveyardGenerator::generate(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  add_graves(map, start_coord.first, end_coord.first, start_coord.second, end_coord.second);
}

TilePtr GraveyardGenerator::generate_tile(MapPtr /*current_map*/, const int /*row*/, const int /*col*/)
{
  TilePtr grave_tile = tg.generate(TileType::TILE_TYPE_GRAVE);

  return grave_tile;
}

bool GraveyardGenerator::get_permanence_default() const
{
  return true;
}

void GraveyardGenerator::add_tomb_if_necessary(MapPtr map)
{
  // 50/50 chance
  int rand = RNG::range(1, 100);
  
  if (rand < 50) add_tomb(map);
}

void GraveyardGenerator::add_tomb(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int tomb_size = RNG::range(TOMB_MIN_SIZE, TOMB_MAX_SIZE);
  int start_row = (rows / 2) - (tomb_size / 2);
  int start_col = (cols / 2) - (tomb_size / 2);
  int end_row = start_row + tomb_size+1;
  int end_col = start_col + tomb_size;
  
  // Fill with rock.
  for (int row = start_row; row < end_row; row++)
  {
    for (int col = start_col; col < end_col; col++)
    {
      TilePtr rock_tile = tg.generate(TileType::TILE_TYPE_ROCK);
      map->insert(row, col, rock_tile);
    }
  }
  
  // Dig out tomb.
  for (int row = start_row+1; row < end_row-1; row++)
  {
    for (int col = start_col+1; col < end_col-1; col++)
    {
      TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(row, col, floor_tile);
    }
  }
  
  // Do other stuff.  Item generation, etc
  
  // Add doorway.  
}

void GraveyardGenerator::add_framing_trees(MapPtr map)
{
  Dimensions dim = map->size();
  int max_y = dim.get_y();
  int max_x = dim.get_x();
  int y, x;
  
  // Top left
  y = x = 0;
  map->insert(y, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y+1, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y, x+1, tg.generate(TileType::TILE_TYPE_TREE));
  
  // Top right
  x = dim.get_x()-1;
  y = 0;
  map->insert(y, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y+1, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y, x-1, tg.generate(TileType::TILE_TYPE_TREE));
  
  // Bottom left
  y = max_y-1;
  x = 0;
  map->insert(y, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y-1, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y, x+1, tg.generate(TileType::TILE_TYPE_TREE));
  
  // Bottom right
  y = max_y-1;
  x = max_x-1;
  map->insert(y, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y-1, x, tg.generate(TileType::TILE_TYPE_TREE));
  map->insert(y, x-1, tg.generate(TileType::TILE_TYPE_TREE));

}

void GraveyardGenerator::add_random_foliage(MapPtr map)
{
  Dimensions dim = map->size();
  
  for (int i = 0; i < 100; i++)
  {
    int y = RNG::range(2, dim.get_y()-2);
    int x = RNG::range(2, dim.get_x()-2);
    
    TilePtr tile = map->at(y, x);
    if (tile && tile->get_tile_type() != TileType::TILE_TYPE_GRAVE)
    {
      int rand = RNG::range(1, 100);
      
      TilePtr new_tile;

      if (rand < 35) // Bush
      {
        new_tile = tg.generate(TileType::TILE_TYPE_BUSH);
      }
      else if (rand < 45) // Weeds
      {
        new_tile = tg.generate(TileType::TILE_TYPE_WEEDS);
      }
      else // Tree
      {
        new_tile = tg.generate(TileType::TILE_TYPE_TREE);
      }
      
      map->insert(y, x, new_tile);
    }
    else
    {
      add_inscription(tile);
    }
  }
}

// JCD FIXME - If graves are generated outside of graveyards more
// frequently, refactor this elsewhere.
void GraveyardGenerator::add_inscription(TilePtr grave_tile)
{
  if (grave_tile != nullptr && RNG::percent_chance(PCT_CHANCE_INSCRIPTION))
  {
    World* world = Game::instance().get_current_world();

    if (world != nullptr)
    {
      int current_year = world->get_calendar().get_date().get_year();
      grave_tile->set_inscription_sid(gig.generate_inscription(current_year));
    }
  }
}
