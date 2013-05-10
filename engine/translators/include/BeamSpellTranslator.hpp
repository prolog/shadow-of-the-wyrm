#pragma once
#include <map>
#include "common.hpp"
#include "DisplayTile.hpp"
#include "Colours.hpp"
#include "Directions.hpp"

// Class for translating a direction and a colour into a proper DisplayTile
// for a spell/wand beam.
class BeamSpellTranslator
{
  public:
    BeamSpellTranslator();
    DisplayTile create_display_tile(const uint spell_burst_range, const Direction beam_direction, const Colour colour);

  protected:
    void initialize_beam_symbols();
    static std::map<Direction, uchar> beam_symbols;
};
