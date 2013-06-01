#pragma once
#include "SpellFailureConsequences.hpp"

class MarginalSpellFailureConsequences : public SpellFailureConsequences
{
  protected:
    virtual float get_damage_pct() const;
    virtual std::string get_damage_message_sid() const;
};

