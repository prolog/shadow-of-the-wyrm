#pragma once
#include "IDescriber.hpp"
#include "Spell.hpp"

class SpellDescriber : public IDescriber
{
  public:
    SpellDescriber(const Spell& new_spell);

    std::string describe() const;

  protected:
    Spell spell;
};
