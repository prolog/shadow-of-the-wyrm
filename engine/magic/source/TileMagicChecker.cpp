#include "TileMagicChecker.hpp"

// A tile blocks a spell if it has a movement multiplier of 0 (it's solid
// and impassable) or if there is a blocking feature present.
bool TileMagicChecker::does_tile_block_spell(TilePtr tile, const Spell& spell) const
{
  bool tile_blocks = false;

  // Block if it's solid or has a blocking feature
  if (!tile || tile->get_movement_multiplier() == 0 || tile->has_blocking_feature())
  {
    tile_blocks = true;
  }

  // ...unblock if it's a digging spell or incorporeal damage.
  if (spell.get_effect() == EffectType::EFFECT_TYPE_DIGGING || spell.get_damage().get_incorporeal())
  {
    tile_blocks = false;
  }

  return tile_blocks;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileMagicChecker_test.cpp"
#endif