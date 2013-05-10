#pragma once

class SpellConstants
{
  public:
    static const int MAX_SPELL_BONUS;

    // The range at which beam spells use '*' instead of the usual symbols.
    static const unsigned int BEAM_BURST_RANGE;
    static const unsigned char BEAM_BURST_SYMBOL;

  protected:
    SpellConstants();
};

