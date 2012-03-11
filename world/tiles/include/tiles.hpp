#pragma once

enum TileType
{
  TILE_TYPE_UNDEFINED = -1,
  TILE_TYPE_FIRST     = 0,
  TILE_TYPE_FIELD     = 0,
  TILE_TYPE_SCRUB     = 1,
  TILE_TYPE_WHEAT     = 2,
  TILE_TYPE_CAIRN     = 3,
  TILE_TYPE_TREE      = 4,
  TILE_TYPE_DESERT    = 5,
  TILE_TYPE_ROAD      = 6,
  TILE_TYPE_RIVER     = 7,
  TILE_TYPE_SEA       = 8,
  TILE_TYPE_SHOALS    = 9,
  TILE_TYPE_DUNGEON   = 10,
  TILE_TYPE_ROCK      = 11,
  TILE_TYPE_GRAVE     = 12,
  TILE_TYPE_MARSH     = 13,
  TILE_TYPE_REEDS     = 14,
  TILE_TYPE_HILLS     = 15,
  TILE_TYPE_MOUNTAINS = 16,
  TILE_TYPE_BEACH     = 17,
  TILE_TYPE_BUSH      = 18,
  TILE_TYPE_WEEDS     = 19,
  TILE_TYPE_SPRINGS   = 20,
  TILE_TYPE_FOREST    = 21,
  TILE_TYPE_UP_STAIRCASE = 22,
  TILE_TYPE_DOWN_STAIRCASE = 23,
  TILE_TYPE_CAVERN    = 24,
  TILE_TYPE_VILLAGE   = 25,
  TILE_TYPE_DUNGEON_COMPLEX = 26,
  TILE_TYPE_LAST      = 26
};

inline TileType operator--(TileType &tt, int)
{
  return tt = TileType(tt-1);
}

inline TileType operator++(TileType &tt, int)
{
  return tt = TileType(tt+1);
}
