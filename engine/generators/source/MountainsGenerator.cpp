#include "MountainsGenerator.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

MountainsGenerator::MountainsGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_MOUNTAINS)
{
}

MapPtr MountainsGenerator::generate(const Dimensions& dimensions)
{
  TileGenerator tg;

  MapPtr result_map = std::make_shared<Map>(dimensions);
  Dimensions dim = result_map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int rand;
  TileType tile_type;
  TilePtr tile;

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      rand = RNG::range(1, 100);
      
      if (rand < 3)
      {
        tile_type = TileType::TILE_TYPE_TREE;
      }
      else if (rand < 5)
      {
        tile_type = TileType::TILE_TYPE_WEEDS;
      }
      else if (rand < 6)
      {
        tile_type = TileType::TILE_TYPE_BUSH;
      }
      else if (rand < 39)
      {
        tile_type = TileType::TILE_TYPE_CAIRN;
      }
      else if (rand < 53)
      {
       tile_type = TileType::TILE_TYPE_SCRUB;
      }
      else
      {
        tile_type = TileType::TILE_TYPE_FIELD;
      }
      
      tile = tg.generate(tile_type);

      // Did someone die here?
      // Probably, people die climbing mountains with alarming regularity.
      if (RNG::x_in_y_chance(1, 1000))
      {
        string item_id = ItemIdKeys::ITEM_ID_PILE_OF_BONES;

        if (RNG::percent_chance(50))
        {
          item_id = ItemIdKeys::ITEM_ID_INTACT_SKELETON;
        }

        ItemPtr corpse_details = ItemManager::create_item(item_id);

        if (corpse_details != nullptr)
        {
          tile->get_items()->add_front(corpse_details);
        }
      }

      result_map->insert(row, col, tile);
    }
  }
  
  return result_map;
}
