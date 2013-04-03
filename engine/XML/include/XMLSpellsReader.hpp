#pragma once
#include "Spell.hpp"

class XMLNode;

class XMLSpellsReader
{
  public:
    XMLSpellsReader();
    ~XMLSpellsReader();

    SpellMap get_spells(const XMLNode& spells_node);

  protected:
    Spell parse(const XMLNode& spell_node);
};
