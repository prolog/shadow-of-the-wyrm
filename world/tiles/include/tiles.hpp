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
constexpr auto CTILE_TYPE_UNDEFINED = -1;
constexpr auto CTILE_TYPE_FIRST = 0;
constexpr auto CTILE_TYPE_FIELD = 0;
constexpr auto CTILE_TYPE_SCRUB = 1;
constexpr auto CTILE_TYPE_WHEAT = 2;
constexpr auto CTILE_TYPE_CAIRN = 3;
constexpr auto CTILE_TYPE_TREE = 4;
constexpr auto CTILE_TYPE_DESERT = 5;
constexpr auto CTILE_TYPE_ROAD = 6;
constexpr auto CTILE_TYPE_RIVER = 7;
constexpr auto CTILE_TYPE_SEA = 8;
constexpr auto CTILE_TYPE_SHOALS = 9;
constexpr auto CTILE_TYPE_DUNGEON = 10;
constexpr auto CTILE_TYPE_ROCK = 11;
constexpr auto CTILE_TYPE_GRAVE = 12;
constexpr auto CTILE_TYPE_MARSH = 13;
constexpr auto CTILE_TYPE_REEDS = 14;
constexpr auto CTILE_TYPE_HILLS = 15;
constexpr auto CTILE_TYPE_MOUNTAINS = 16;
constexpr auto CTILE_TYPE_BEACH = 17;
constexpr auto CTILE_TYPE_BUSH = 18;
constexpr auto CTILE_TYPE_WEEDS = 19;
constexpr auto CTILE_TYPE_SPRINGS = 20;
constexpr auto CTILE_TYPE_FOREST = 21;
constexpr auto CTILE_TYPE_UP_STAIRCASE = 22;
constexpr auto CTILE_TYPE_DOWN_STAIRCASE = 23;
constexpr auto CTILE_TYPE_CAVERN = 24;
constexpr auto CTILE_TYPE_VILLAGE = 25;
constexpr auto CTILE_TYPE_DUNGEON_COMPLEX = 26;
constexpr auto CTILE_TYPE_BARRACKS = 27;
constexpr auto CTILE_TYPE_CASTLE = 28;
constexpr auto CTILE_TYPE_CHURCH = 29;
constexpr auto CTILE_TYPE_GRAVEYARD = 30;
constexpr auto CTILE_TYPE_KEEP = 31;
constexpr auto CTILE_TYPE_LIBRARY = 32;
constexpr auto CTILE_TYPE_SITE_OF_DEATH = 33;
constexpr auto CTILE_TYPE_TEMPLE = 34;
constexpr auto CTILE_TYPE_DAIS = 35;
constexpr auto CTILE_TYPE_PIER = 36;
constexpr auto CTILE_TYPE_BARROW = 37;
constexpr auto CTILE_TYPE_WILD_ORCHARD = 38;
constexpr auto CTILE_TYPE_FRUIT_TREE = 39;
constexpr auto CTILE_TYPE_EVERGREEN_TREE = 40;
constexpr auto CTILE_TYPE_ROCKY_EARTH = 41;
constexpr auto CTILE_TYPE_MINE = 42;
constexpr auto CTILE_TYPE_WELL = 43;
constexpr auto CTILE_TYPE_CRYPT = 44;
constexpr auto CTILE_TYPE_AIR = 45;
constexpr auto CTILE_TYPE_EARTH = 46;
constexpr auto CTILE_TYPE_SEWER_COMPLEX = 47;
constexpr auto CTILE_TYPE_SEWER = 48;
constexpr auto CTILE_TYPE_SHRINE = 49;
constexpr auto CTILE_TYPE_SEABED = 50;
constexpr auto CTILE_TYPE_AQUATIC_VEGETATION = 51;
constexpr auto CTILE_TYPE_FLOATING_TOWER = 52;
constexpr auto CTILE_TYPE_VOID = 53;
constexpr auto CTILE_TYPE_MAGICAL_TREE = 54;
constexpr auto CTILE_TYPE_LAST = 55;

