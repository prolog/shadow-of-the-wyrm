#include <cctype>
#include "MapUtils.hpp"
#include "TileGenerator.hpp"
#include "SpringsTile.hpp"
#include "XMLMapTilesReader.hpp"
#include "XMLTileMapper.hpp"

using namespace std;

// Parse the tiles into a proper tile map that would be used in-game,
// using the provided string.
TilesContainer XMLMapTilesReader::parse_tiles(const XMLNode& tiles_node, const int rows, const int cols)
{
  TilesContainer tiles;

  int cur_row = 0;
  int cur_col = 0;

  if (!tiles_node.is_null())
  {
    string tile_str = XMLUtils::get_node_value(tiles_node);
    size_t tiles_size = tile_str.size();

    XMLTileMapper tile_mapper;

    if (!tile_str.empty())
    {
      for (string::const_iterator s_it = tile_str.begin(); s_it != tile_str.end(); s_it++)
      {
        if (!isspace(*s_it))
        {
          TilePtr tile = tile_mapper.create_tile(*s_it);

          if (tile)
          {
            std::string tile_key = MapUtils::convert_coordinate_to_map_key(make_pair(cur_row, cur_col));
            tiles.insert(make_pair(tile_key, tile));

            if (++cur_col >= cols)
            {
              cur_col = 0;
              cur_row++;
            }
          }
          else
          {
            int x = 1;
          }
        }
      }
    }
  }

  return tiles;
}


