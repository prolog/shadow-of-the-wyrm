#include "XMLWorldMapTileMapper.hpp"

using namespace std;

// Always suppress the potential generation of items on world map tiles.
// This is done by ensuring that the TileGenerator belonging to the
// parent class is set up appropriately.
XMLWorldMapTileMapper::XMLWorldMapTileMapper()
{
  tg.set_generate_items(false);
}

// Maps the world map XML tile (as a character) into a new TilePtr.
TilePtr XMLWorldMapTileMapper::create_tile(const char xml_tile)
{
  TilePtr tile;

  if (xml_tile == '~')
  {
    tile = tg.generate(TILE_TYPE_SEA);
  }
  else if (xml_tile == 'K')
  {
    tile = tg.generate(TILE_TYPE_KEEP);
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
  else if (xml_tile == '^')
  {
    tile = tg.generate(TILE_TYPE_MOUNTAINS);
  }
  else if (xml_tile == 'C')
  {
    tile = tg.generate(TILE_TYPE_CRYPT);
  }
  else if (xml_tile == 'c')
  {
    tile = tg.generate(TILE_TYPE_CAVERN);
  }
  else if (xml_tile == 'r')
  {
    tile = tg.generate(TILE_TYPE_ROCKY_EARTH);
  }
  else if (xml_tile == 'm')
  {
    tile = tg.generate(TILE_TYPE_MARSH);
  }
  else if (xml_tile == 'M')
  { 
    tile = tg.generate(TILE_TYPE_MINE);
  }
  else
  {
    // So, the user's specified a tile that doesn't exist (I'm going to assume
    // it was some nebulous "user" and not "Julian Day", because otherwise
    // my brittle self-esteem will shatter like the icy film over a puddle on
    // a cold March day).  This...is not good.  So, raise an alert to the fact
    // that the symbol couldn't be mapped.
    string bad_tile_type_msg = "Could not find tile type: " + xml_tile;
    BOOST_ASSERT_MSG(false, bad_tile_type_msg.c_str());
  }

  return tile;
}