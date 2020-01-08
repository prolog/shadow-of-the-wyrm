#include "BeamSpellTranslator.hpp"
#include "SpellConstants.hpp"

using namespace std;

std::map<Direction, pair<uchar, string>> BeamSpellTranslator::beam_symbols;

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
  beam_symbols = map<Direction, pair<uchar, string>>{{Direction::DIRECTION_NORTH_WEST, {'\\', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NWSE}},
                                                     {Direction::DIRECTION_NORTH, {'|', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NS}},
                                                     {Direction::DIRECTION_NORTH_EAST, {'/', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NESW}},
                                                     {Direction::DIRECTION_WEST, {'-', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_EW}},
                                                     {Direction::DIRECTION_NULL, {'*', SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST}},
                                                     {Direction::DIRECTION_EAST, {'-', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_EW}},
                                                     {Direction::DIRECTION_SOUTH_WEST, {'/', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NESW}},
                                                     {Direction::DIRECTION_SOUTH, {'|', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NS}},
                                                     {Direction::DIRECTION_SOUTH_EAST, {'\\', SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NWSE}},
                                                     {Direction::DIRECTION_UP, {'*', SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST}},
                                                     {Direction::DIRECTION_DOWN, {'*', SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST}}};
}

DisplayTile BeamSpellTranslator::create_display_tile(const uint spell_burst_range, const Direction beam_direction, const Colour colour)
{
  auto beam_symbol = beam_symbols[beam_direction];

  if (spell_burst_range <= SpellConstants::BEAM_BURST_RANGE)
  {
    beam_symbol.first = SpellConstants::BEAM_BURST_SYMBOL;
    beam_symbol.second = SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST;
  }

  Symbol s(beam_symbol.first, colour, SpritesheetLocation(SpritesheetIndex::SPRITESHEET_INDEX_SYSTEM, beam_symbol.second));
  DisplayTile dt(s);
  return dt;
}

#ifdef UNIT_TESTS
#include "unit_tests/BeamSpellTranslator_test.cpp"
#endif
