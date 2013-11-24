#include "BeamSpellTranslator.hpp"
#include "SpellConstants.hpp"

using namespace std;

std::map<Direction, uchar> BeamSpellTranslator::beam_symbols;

// On construction, initialize the static map of beam symbols if this has
// not been done.
BeamSpellTranslator::BeamSpellTranslator()
{
  if (beam_symbols.empty())
  {
    initialize_beam_symbols();
  }
}

// Initialize the static map of beam symbols.
void BeamSpellTranslator::initialize_beam_symbols()
{
  beam_symbols.clear();
  beam_symbols = map<Direction, uchar>{{DIRECTION_NORTH_WEST, '\\'},
                                       {DIRECTION_NORTH, '|'},
                                       {DIRECTION_NORTH_EAST, '/'},
                                       {DIRECTION_WEST, '-'},
                                       {DIRECTION_NULL, '*'},
                                       {DIRECTION_EAST, '-'},
                                       {DIRECTION_SOUTH_WEST, '/'},
                                       {DIRECTION_SOUTH, '|'},
                                       {DIRECTION_SOUTH_EAST, '\\'},
                                       {DIRECTION_UP, '<'},
                                       {DIRECTION_DOWN, '>'}};
}

DisplayTile BeamSpellTranslator::create_display_tile(const uint spell_burst_range, const Direction beam_direction, const Colour colour)
{
  uchar beam_symbol = beam_symbols[beam_direction];

  if (spell_burst_range <= SpellConstants::BEAM_BURST_RANGE)
  {
    beam_symbol = SpellConstants::BEAM_BURST_SYMBOL;
  }

  DisplayTile dt(beam_symbol, colour);
  return dt;
}

#ifdef UNIT_TESTS
#include "unit_tests/BeamSpellTranslator_test.cpp"
#endif