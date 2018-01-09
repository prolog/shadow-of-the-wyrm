#pragma once

enum struct TileSuperType
{
  TILE_SUPER_TYPE_UNDEFINED = -1,
  TILE_SUPER_TYPE_GROUND = 0,
  TILE_SUPER_TYPE_WATER = 1,
  TILE_SUPER_TYPE_AIR = 2
};

// Tile types for the C++ code.
enum struct TileType
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
  TILE_TYPE_BARRACKS  = 27,
  TILE_TYPE_CASTLE    = 28,
  TILE_TYPE_CHURCH    = 29,
  TILE_TYPE_GRAVEYARD = 30,
  TILE_TYPE_KEEP      = 31,
  TILE_TYPE_LIBRARY   = 32,
  TILE_TYPE_SITE_OF_DEATH = 33,
  TILE_TYPE_TEMPLE    = 34,
  TILE_TYPE_DAIS      = 35,
  TILE_TYPE_PIER      = 36,
  TILE_TYPE_BARROW    = 37,
  TILE_TYPE_WILD_ORCHARD = 38,
  TILE_TYPE_FRUIT_TREE = 39,
  TILE_TYPE_EVERGREEN_TREE = 40,
  TILE_TYPE_ROCKY_EARTH = 41,
  TILE_TYPE_MINE      = 42,
  TILE_TYPE_WELL      = 43,
  TILE_TYPE_CRYPT     = 44,
  TILE_TYPE_AIR       = 45,
  TILE_TYPE_EARTH     = 46,
  TILE_TYPE_SEWER_COMPLEX = 47,
  TILE_TYPE_SEWER     = 48,
  TILE_TYPE_SHRINE    = 49,
  TILE_TYPE_SEABED    = 50,
  TILE_TYPE_AQUATIC_VEGETATION = 51,
  TILE_TYPE_FLOATING_TOWER = 52,
  TILE_TYPE_VOID      = 53,
  TILE_TYPE_MAGICAL_TREE = 54,
  TILE_TYPE_LAST      = 55
};

// Tile types for the Lua API
#define CTILE_TYPE_UNDEFINED -1
#define CTILE_TYPE_FIRST 0
#define CTILE_TYPE_FIELD 0
#define CTILE_TYPE_SCRUB 1
#define CTILE_TYPE_WHEAT 2
#define CTILE_TYPE_CAIRN 3
#define CTILE_TYPE_TREE 4
#define CTILE_TYPE_DESERT 5
#define CTILE_TYPE_ROAD 6
#define CTILE_TYPE_RIVER 7
#define CTILE_TYPE_SEA 8
#define CTILE_TYPE_SHOALS 9
#define CTILE_TYPE_DUNGEON 10
#define CTILE_TYPE_ROCK 11
#define CTILE_TYPE_GRAVE 12
#define CTILE_TYPE_MARSH 13
#define CTILE_TYPE_REEDS 14
#define CTILE_TYPE_HILLS 15
#define CTILE_TYPE_MOUNTAINS 16
#define CTILE_TYPE_BEACH 17
#define CTILE_TYPE_BUSH 18
#define CTILE_TYPE_WEEDS 19
#define CTILE_TYPE_SPRINGS 20
#define CTILE_TYPE_FOREST 21
#define CTILE_TYPE_UP_STAIRCASE 22
#define CTILE_TYPE_DOWN_STAIRCASE 23
#define CTILE_TYPE_CAVERN 24
#define CTILE_TYPE_VILLAGE 25
#define CTILE_TYPE_DUNGEON_COMPLEX 26
#define CTILE_TYPE_BARRACKS 27
#define CTILE_TYPE_CASTLE 28
#define CTILE_TYPE_CHURCH 29
#define CTILE_TYPE_GRAVEYARD 30
#define CTILE_TYPE_KEEP 31
#define CTILE_TYPE_LIBRARY 32
#define CTILE_TYPE_SITE_OF_DEATH 33
#define CTILE_TYPE_TEMPLE 34
#define CTILE_TYPE_DAIS 35
#define CTILE_TYPE_PIER 36
#define CTILE_TYPE_BARROW 37
#define CTILE_TYPE_WILD_ORCHARD 38
#define CTILE_TYPE_FRUIT_TREE 39
#define CTILE_TYPE_EVERGREEN_TREE 40
#define CTILE_TYPE_ROCKY_EARTH 41
#define CTILE_TYPE_MINE 42
#define CTILE_TYPE_WELL 43
#define CTILE_TYPE_CRYPT 44
#define CTILE_TYPE_AIR 45
#define CTILE_TYPE_EARTH 46
#define CTILE_TYPE_SEWER_COMPLEX 47
#define CTILE_TYPE_SEWER 48
#define CTILE_TYPE_SHRINE 49
#define CTILE_TYPE_SEABED 50
#define CTILE_TYPE_AQUATIC_VEGETATION 51
#define CTILE_TYPE_FLOATING_TOWER 52
#define CTILE_TYPE_VOID 53
#define CTILE_TYPE_MAGICAL_TREE 54
#define CTILE_TYPE_LAST 555

