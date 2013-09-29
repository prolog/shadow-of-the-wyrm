#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "ShadeGardenGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

ShadeGardenGenerator::ShadeGardenGenerator(MapPtr base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width)
: GardenGenerator(base_map, map_window_start_row, map_window_start_col, map_window_height, map_window_width)
{
}

// Generate the shade garden
void ShadeGardenGenerator::generate()
{
  generate_tree_cover();
  generate_plants();
  generate_features();
}

// Generate the trees surrounding the garden
void ShadeGardenGenerator::generate_tree_cover()
{
  TileGenerator tg;
  TilePtr tree_tile;

  for (int row = window_start_row; row <= window_end_row_inc; row++)
  {
    tree_tile = tg.generate(TILE_TYPE_TREE);
    map->insert(row, window_start_col, tree_tile);

    tree_tile = tg.generate(TILE_TYPE_TREE);
    map->insert(row, window_end_col_inc, tree_tile);
  }

  for (int col = window_start_col; col <= window_end_col_inc; col++)
  {
    tree_tile = tg.generate(TILE_TYPE_TREE);
    map->insert(window_start_row, col, tree_tile);

    tree_tile = tg.generate(TILE_TYPE_TREE);
    map->insert(window_end_row_inc, col, tree_tile);
  }
}

// Generate the plants within the garden
void ShadeGardenGenerator::generate_plants()
{
  TilePtr garden_tile;
  TileGenerator tg;

  int rand;    
  // Turn the underlying tiles into grass.
  for (int row = window_start_row+1; row < window_end_row_inc; row++)
  {
    for (int col = window_start_col+1; col < window_end_col_inc; col++)
    {
      garden_tile = tg.generate(TILE_TYPE_FIELD);
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
        garden_tile->get_items().add(plant);
      }
    }
  }  
}

// Generate the bench in the centre of the garden
void ShadeGardenGenerator::generate_features()
{
  int centre_row = (window_start_row + window_end_row_inc) / 2;
  int centre_col = (window_start_col + window_end_col_inc) / 2;

  FeaturePtr bench   = FeatureGenerator::generate_bench();
  TilePtr bench_tile = map->at(centre_row, centre_col);
  bench_tile->set_feature(bench);
  
  // Make sure there are no ferns, etc., generated over top of the bench.
  bench_tile->get_items().clear();
}
