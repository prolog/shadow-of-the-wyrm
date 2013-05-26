#pragma once

class SpellConstants
{
  public:
    static const int MAX_SPELL_BONUS;

    // The range at which beam spells use '*' instead of the usual symbols.
    static const unsigned int BEAM_BURST_RANGE;
    static const unsigned char BEAM_BURST_SYMBOL;
    static const int SPELL_FAILURE_MILDLY_BAD;
    static const int SPELL_FAILURE_BAD;
    static const int SPELL_FAILURE_SUPER_BAD;
    static const int MIN_CASTINGS;
    static const int BASE_MIN_CASTINGS;
    static const int BASE_MAX_CASTINGS;

  protected:
    SpellConstants();
};

