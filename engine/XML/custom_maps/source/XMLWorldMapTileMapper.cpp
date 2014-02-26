#include "XMLWorldMapTileMapper.hpp"

using namespace std;

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