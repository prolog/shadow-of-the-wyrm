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
    void parse_spell_properties(const XMLNode& properties_node, Spell& spell, std::map<std::string, std::string>& properties);
    void create_statistics_modifiers_if_necessary(Spell& spell, const std::map<std::string, std::string>& properties);
};
