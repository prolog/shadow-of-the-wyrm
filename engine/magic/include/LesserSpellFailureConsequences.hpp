#pragma once
#include "SpellFailureConsequences.hpp"

class LesserSpellFailureConsequences : public SpellFailureConsequences
{
  protected:
    virtual float get_damage_pct() const;
    virtual std::string get_damage_message_sid() const;
};

