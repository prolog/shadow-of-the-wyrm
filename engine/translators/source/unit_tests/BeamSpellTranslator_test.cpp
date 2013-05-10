#include "gtest/gtest.h"
#include "Spell.hpp"

TEST(SL_Engine_Translators_BeamSpellTranslator, burst_symbol_used_when_in_range)
{
  BeamSpellTranslator bst;

  Spell spell;
  spell.set_range(SpellConstants::BEAM_BURST_RANGE);

  DisplayTile dt = bst.create_display_tile(spell.get_range(), DIRECTION_NORTH, COLOUR_WHITE);

  EXPECT_EQ(SpellConstants::BEAM_BURST_SYMBOL, dt.get_symbol());

  spell.set_range(SpellConstants::BEAM_BURST_RANGE + 2);

  dt = bst.create_display_tile(spell.get_range(), DIRECTION_SOUTH, COLOUR_BLUE);

  EXPECT_FALSE(SpellConstants::BEAM_BURST_SYMBOL == dt.get_symbol());
}

