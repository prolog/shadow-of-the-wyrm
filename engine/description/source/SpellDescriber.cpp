#include "SpellDescriber.hpp"
#include "Conversion.hpp"
#include "StringTable.hpp"

using namespace std;

SpellDescriber::SpellDescriber(const Spell& new_spell)
: spell(new_spell)
{
}

// The description of the spell for the spellcasting UI screen.
string SpellDescriber::describe() const
{
  string spell_description;

  spell_description = "JCD FIXME SPELLDESCRIBER";

  return spell_description;
}

