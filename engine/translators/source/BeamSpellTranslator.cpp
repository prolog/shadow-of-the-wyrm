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

  beam_symbols.insert(make_pair(DIRECTION_NORTH_WEST, '\\'));
  beam_symbols.insert(make_pair(DIRECTION_NORTH, '|'));
  beam_symbols.insert(make_pair(DIRECTION_NORTH_EAST, '/'));
  beam_symbols.insert(make_pair(DIRECTION_WEST, '-'));
  beam_symbols.insert(make_pair(DIRECTION_NULL, '*'));
  beam_symbols.insert(make_pair(DIRECTION_EAST, '-'));
  beam_symbols.insert(make_pair(DIRECTION_SOUTH_WEST, '/'));
  beam_symbols.insert(make_pair(DIRECTION_SOUTH, '|'));
  beam_symbols.insert(make_pair(DIRECTION_SOUTH_EAST, '\\'));
  beam_symbols.insert(make_pair(DIRECTION_UP, '<'));
  beam_symbols.insert(make_pair(DIRECTION_DOWN, '>'));
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