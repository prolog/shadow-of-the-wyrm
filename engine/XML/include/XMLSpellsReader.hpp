#pragma once
#include "Spell.hpp"
#include "XMLReader.hpp"

class XMLNode;

class XMLSpellsReader : public XMLReader
{
  public:
    XMLSpellsReader();
    ~XMLSpellsReader();

    SpellMap get_spells(const XMLNode& spells_node);

  protected:
    Spell parse(const XMLNode& spell_node);
};
