#include "OrderedGraveyardGenerator.hpp"

OrderedGraveyardGenerator::OrderedGraveyardGenerator(const std::string& new_map_exit_id)
: GraveyardGenerator(new_map_exit_id)
{
}

// Add the graves in a neat, orderly manner.
void OrderedGraveyardGenerator::add_graves(MapPtr map)
{
  Dimensions dim = map->size();
  
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  for (int y = 2; y < rows - 2; y++)
  {
    for (int x = 2; x < cols - 2; x++)
    {
      if ((x%5) + (y % 3) == 0)
      {
        TilePtr grave = generate_tile(map, y, x);
        map->insert(y, x, grave);
      }
    }
  }
}



