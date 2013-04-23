#pragma once
#include "Tile.hpp"

// Class to check whether a tile blocks a spell.  If a tile is a wall, etc,
// then the tile should not be included in the spell's calculations.
class TileMagicChecker
{
  public:
    bool does_tile_block_spell(TilePtr tile) const;
};
