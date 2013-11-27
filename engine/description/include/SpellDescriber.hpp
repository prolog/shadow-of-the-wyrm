#pragma once
#include "Creature.hpp"
#include "IDescriber.hpp"
#include "Spell.hpp"

// A class used to describe a spell, including a creature's knowledge of that
// spell.
class SpellDescriber : public IDescriber
{
  public:
    SpellDescriber(CreaturePtr creature, const Spell& new_spell);

    std::string describe() const override;

  protected:
    void initialize_shape_abbreviation_sids();

    std::string describe_range() const;

    CreaturePtr creature;
    Spell spell;

    static std::map<SpellShapeType, std::string> shape_abbreviation_sids;
};
