#include "XMLWorldMapTileMapper.hpp"

// Maps the world map XML tile (as a character) into a new TilePtr.
TilePtr XMLWorldMapTileMapper::create_tile(const char xml_tile)
{
  TilePtr tile;

  if (xml_tile == '~')
  {
    tile = tg.generate(TILE_TYPE_SEA);
  }
  else if (xml_tile == 'F')
  {
    tile = tg.generate(TILE_TYPE_FOREST);
  }
  else if (xml_tile == 'f')
  {
    tile = tg.generate(TILE_TYPE_FIELD);
  }
  else if (xml_tile == 'O')
  {
    tile = tg.generate(TILE_TYPE_WILD_ORCHARD);
  }
  else if (xml_tile == 'd')
  {
    tile = tg.generate(TILE_TYPE_DUNGEON_COMPLEX);
  }
  else if (xml_tile == 'g')
  {
    tile = tg.generate(TILE_TYPE_GRAVEYARD);
  }
  else if (xml_tile == 'v')
  {
    tile = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_FIELD);
  }

  return tile;
}