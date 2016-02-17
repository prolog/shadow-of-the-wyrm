#include "SpringsTile.hpp"
#include "XMLTileMapper.hpp"

// Maps the XML tile (as a character) into a new TilePtr.
TilePtr XMLTileMapper::create_tile(const char xml_tile)
{
  TilePtr tile;

  if (xml_tile == '.')
  {
    tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
  }
  else if (xml_tile == 'D')
  {
    tile = tg.generate(TileType::TILE_TYPE_DAIS);
  }
  else if (xml_tile == '<')
  {
    tile = tg.generate_staircase(StaircaseType::STAIRCASE_UP);
  }
  else if (xml_tile == '>')
  {
    tile = tg.generate_staircase(StaircaseType::STAIRCASE_DOWN);
  }
  else if (xml_tile == '#')
  {
    tile = tg.generate(TileType::TILE_TYPE_ROCK);
  }
  else if (xml_tile == '^')
  {
    tile = tg.generate(TileType::TILE_TYPE_MOUNTAINS);
  }
  else if (xml_tile == 'P')
  {
    tile = tg.generate(TileType::TILE_TYPE_PIER);
  }
  else if (xml_tile == 'T')
  {
    tile = tg.generate(TileType::TILE_TYPE_TREE);
  }
  else if (xml_tile == 'F')
  {
    tile = tg.generate(TileType::TILE_TYPE_FRUIT_TREE);
  }
  else if (xml_tile == ',')
  {
    tile = tg.generate(TileType::TILE_TYPE_FIELD);
  }
  else if (xml_tile == 'm')
  { 
    tile = tg.generate(TileType::TILE_TYPE_MARSH);
  }
  else if (xml_tile == '*')
  {
    tile = tg.generate(TileType::TILE_TYPE_BUSH);
  }
  else if (xml_tile == '~')
  {
    tile = tg.generate(TileType::TILE_TYPE_RIVER);
  }
  else if (xml_tile == 'R')
  {
    tile = tg.generate(TileType::TILE_TYPE_ROCKY_EARTH);
  }
  else if (xml_tile == 'W')
  {
    tile = tg.generate(TileType::TILE_TYPE_WEEDS);
  }
  else if (xml_tile == 'B')
  {
    tile = tg.generate(TileType::TILE_TYPE_BUSH);
  }
  else if (xml_tile == 'e')
  {
    tile = tg.generate(TileType::TILE_TYPE_REEDS);
  }
  else if (xml_tile == 'E')
  {
    tile = tg.generate(TileType::TILE_TYPE_EARTH);
  }
  else if (xml_tile == 'w')
  {
    tile = tg.generate(TileType::TILE_TYPE_WELL);
  }
  else if (xml_tile == 'r')
  {
    tile = tg.generate(TileType::TILE_TYPE_ROAD);
  }
  else if (xml_tile == 'S')
  {
    tile = tg.generate(TileType::TILE_TYPE_SEA);
  }
  else if (xml_tile == 's')
  {
    tile = tg.generate(TileType::TILE_TYPE_SHOALS);
  }
  else if (xml_tile == 'C')
  {
    tile = tg.generate(TileType::TILE_TYPE_CAIRN);
  }
  else if (xml_tile == 'c')
  {
    tile = tg.generate(TileType::TILE_TYPE_CRYPT);
  }
  else if (xml_tile == '0')
  {
    tile = tg.generate(TileType::TILE_TYPE_BARROW);
  }
  else if (xml_tile == '-')
  {
    tile = tg.generate(TileType::TILE_TYPE_SEWER);
  }
  else if (xml_tile == 'A')
  {
    tile = tg.generate(TileType::TILE_TYPE_AIR);
  }
  // JCD FIXME: Later add sewers, etc.
  else if ((xml_tile == '\'') || (xml_tile == '`'))
  {
    // Single quote indicates a regular freshwater spring.
    tile = tg.generate(TileType::TILE_TYPE_SPRINGS);

    // Backtick indicates hot springs.
    if (xml_tile == '`')
    {
      std::shared_ptr<SpringsTile> springs_tile = std::dynamic_pointer_cast<SpringsTile>(tile);

      if (springs_tile)
      {
        springs_tile->set_temperature(static_cast<int>(SpringsTemperature::SPRINGS_TEMPERATURE_HOT));
      }
    }
  }

  return tile;
}
