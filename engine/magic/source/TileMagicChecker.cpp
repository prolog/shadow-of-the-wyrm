#include "TileMagicChecker.hpp"

// A tile blocks a spell if it has a movement multiplier of 0 (it's solid
// and impassable) or if there is a blocking feature present.
bool TileMagicChecker::does_tile_block_spell(TilePtr tile) const
{
  bool tile_blocks = false;

  if (!tile || tile->get_movement_multiplier() == 0 || tile->has_blocking_feature())
  {
    tile_blocks = true;
  }

  return tile_blocks;
}

