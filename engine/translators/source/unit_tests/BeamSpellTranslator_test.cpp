#include "gtest/gtest.h"
#include "Spell.hpp"

TEST(SW_Engine_Translators_BeamSpellTranslator, burst_symbol_used_when_in_range)
{
  BeamSpellTranslator bst;

  Spell spell;
  spell.set_range(SpellConstants::BEAM_BURST_RANGE);

  DisplayTile dt = bst.create_display_tile(spell.get_range(), Direction::DIRECTION_NORTH, Colour::COLOUR_WHITE);
  uchar beam_csym = dt.get_symbol().get_symbol();

  EXPECT_EQ(SpellConstants::BEAM_BURST_SYMBOL, beam_csym);

  spell.set_range(SpellConstants::BEAM_BURST_RANGE + 2);
  dt = bst.create_display_tile(spell.get_range(), Direction::DIRECTION_SOUTH, Colour::COLOUR_BLUE);
  beam_csym = dt.get_symbol().get_symbol();

  EXPECT_FALSE(SpellConstants::BEAM_BURST_SYMBOL == beam_csym);
}

