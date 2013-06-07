#pragma once
#include <string>

class SpellFailureTextKeys
{
  public:
    static const std::string SPELL_FAILURE_DAMAGE_MARGINAL;
    static const std::string SPELL_FAILURE_DAMAGE_LESSER;
    static const std::string SPELL_FAILURE_DAMAGE_SEVERE;

    static const std::string SPELL_FAILURE_SUMMONED_CREATURES_MARGINAL;
    static const std::string SPELL_FAILURE_SUMMONED_CREATURES_LESSER;
    static const std::string SPELL_FAILURE_SUMMONED_CREATURES_SEVERE;

  protected:
    SpellFailureTextKeys();
};
