#pragma once
#include "SpellFailureConsequences.hpp"

class MarginalSpellFailureConsequences : public SpellFailureConsequences
{
  protected:
    virtual float get_damage_pct() const;
    virtual std::string get_damage_message_sid() const;

    virtual std::pair<Dice, std::vector<std::string>> get_summoned_creature_details() const;
    virtual std::string get_summoned_creatures_message_sid() const;
};

