#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "ShadeGardenGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

ShadeGardenGenerator::ShadeGardenGenerator(const string& new_deity_id, const AlignmentRange new_ar)
: GardenSectorFeature(new_deity_id, new_ar)
{
}

// Generate the shade garden
bool ShadeGardenGenerator::generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  generate_tree_cover(map, start_coord, end_coord);
  generate_plants(map, start_coord, end_coord);
  generate_features(map, start_coord, end_coord);

  return true;
}

// Generate the trees surrounding the garden
void ShadeGardenGenerator::generate_tree_cover(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  TileGenerator tg;
  TilePtr tree_tile;

  for (int row = start_coord.first; row <= end_coord.first; row++)
  {
    tree_tile = tg.generate(TileType::TILE_TYPE_TREE);
    map->insert(row, start_coord.second, tree_tile); 

    tree_tile = tg.generate(TileType::TILE_TYPE_TREE);
    map->insert(row, end_coord.second, tree_tile);
  }

  for (int col = start_coord.second; col <= end_coord.second; col++)
  {
    tree_tile = tg.generate(TileType::TILE_TYPE_TREE);
    map->insert(start_coord.first, col, tree_tile);

    tree_tile = tg.generate(TileType::TILE_TYPE_TREE);
    map->insert(end_coord.first, col, tree_tile);
  }
}

// Generate the plants within the garden
void ShadeGardenGenerator::generate_plants(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  TilePtr garden_tile;
  TileGenerator tg;

  int rand;    
  // Turn the underlying tiles into grass.
  for (int row = start_coord.first+1; row < end_coord.first; row++)
  {
    for (int col = start_coord.second+1; col < end_coord.second; col++)
    {
      garden_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      map->insert(row, col, garden_tile);
      
      rand = RNG::range(1, 6);
      
      // Small chance of no plant.
      // Otherwise:
      
      ItemPtr plant;
      if (rand == 3)
      {
        // Generate a fiddlehead green - this is good eatin'.
        plant = ItemManager::create_item(ItemIdKeys::ITEM_ID_FIDDLEHEAD_GREEN);
      }
      else if (rand > 3)
      {
        // Generate a regular fern
        plant = ItemManager::create_item(ItemIdKeys::ITEM_ID_FERN);        
      }
      
      if (plant)
      {
        garden_tile->get_items()->add(plant);
      }
    }
  }  
}

// Generate the bench in the centre of the garden
void ShadeGardenGenerator::generate_features(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  int centre_row = (start_coord.first + end_coord.first) / 2;
  int centre_col = (start_coord.second + end_coord.second) / 2;

  FeaturePtr bench   = FeatureGenerator::generate_bench();
  TilePtr bench_tile = map->at(centre_row, centre_col);
  bench_tile->set_feature(bench);
  
  // Make sure there are no ferns, etc., generated over top of the bench.
  bench_tile->get_items()->clear();
}
