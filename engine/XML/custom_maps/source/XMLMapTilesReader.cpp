#include <cctype>
#include "MapUtils.hpp"
#include "TileGenerator.hpp"
#include "SpringsTile.hpp"
#include "XMLMapTilesReader.hpp"

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

// Maps the XML tile (as a character) into a new TilePtr.
TilePtr XMLTileMapper::create_tile(const char xml_tile)
{
  TilePtr tile;

  if (xml_tile == '.')
  {
    tile = tg.generate(TILE_TYPE_DUNGEON);
  }
  else if (xml_tile == 'D')
  {
    tile = tg.generate(TILE_TYPE_DAIS);
  }
  else if (xml_tile == '<')
  {
    tile = tg.generate_staircase(STAIRCASE_UP);
  }
  else if (xml_tile == '>')
  {
    tile = tg.generate_staircase(STAIRCASE_DOWN);
  }
  else if (xml_tile == '#')
  {
    tile = tg.generate(TILE_TYPE_ROCK);
  }
  else if (xml_tile == '^')
  {
    tile = tg.generate(TILE_TYPE_MOUNTAINS);
  }
  else if (xml_tile == 'P')
  {
    tile = tg.generate(TILE_TYPE_PIER);
  }
  else if (xml_tile == 'T')
  {
    tile = tg.generate(TILE_TYPE_TREE);
  }
  else if (xml_tile == 'F')
  {
    tile = tg.generate(TILE_TYPE_FRUIT_TREE);
  }
  else if (xml_tile == ',')
  {
    tile = tg.generate(TILE_TYPE_FIELD);
  }
  else if (xml_tile == '*')
  {
    tile = tg.generate(TILE_TYPE_BUSH);
  }
  else if (xml_tile == '~')
  {
    tile = tg.generate(TILE_TYPE_RIVER);
  }
  else if (xml_tile == 'R')
  {
    tile = tg.generate(TILE_TYPE_ROCKY_EARTH);
  }
  else if (xml_tile == 'w')
  {
    tile = tg.generate(TILE_TYPE_WELL);
  }
  else if (xml_tile == 'r')
  {
    tile = tg.generate(TILE_TYPE_ROAD);
  }
  else if (xml_tile == 'S')
  {
    tile = tg.generate(TILE_TYPE_SEA);
  }
  else if (xml_tile == 's')
  {
    tile = tg.generate(TILE_TYPE_SHOALS);
  }
  else if (xml_tile == 'C')
  {
    tile = tg.generate(TILE_TYPE_CAIRN);
  }
  else if (xml_tile == '0')
  {
    tile = tg.generate(TILE_TYPE_BARROW);
  }
  else if ((xml_tile == '\'') || (xml_tile == '`'))
  {
    // Single quote indicates a regular freshwater spring.
    tile = tg.generate(TILE_TYPE_SPRINGS);

    // Backtick indicates hot springs.
    if (xml_tile == '`')
    {
      std::shared_ptr<SpringsTile> springs_tile = std::dynamic_pointer_cast<SpringsTile>(tile);

      if (springs_tile)
      {
        springs_tile->set_temperature(SPRINGS_TEMPERATURE_HOT);
      }
    }
  }

  return tile;
}

