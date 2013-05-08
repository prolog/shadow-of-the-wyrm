#include <sstream>
#include "SpellDescriber.hpp"
#include "Conversion.hpp"
#include "Skills.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

SpellDescriber::SpellDescriber(CreaturePtr new_creature, const Spell& new_spell)
: creature(new_creature), spell(new_spell)
{
}

// The description of the spell for the spellcasting UI screen.
string SpellDescriber::describe() const
{
  stringstream ss;

  SpellKnowledge& sk = creature->get_spell_knowledge_ref();

  Skills skills;
  string spell_name = StringTable::get(spell.get_spell_name_sid());
  string spell_category = StringTable::get(skills.get_skill(spell.get_magic_category())->get_skill_name_sid());
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell.get_spell_id());

  ss << spell_name 
     << " (" << spell_category << ")" 
     << " [" 
             << "#:" << isk.get_castings()
             << ", " << StringTable::get(TextKeys::RANGE_ABRV) << ":" << spell.get_range()
             << ", " << StringTable::get(TextKeys::ARCANA_POINTS_ABRV) << ":" << spell.get_ap_cost()
             << ", +"<< isk.get_bonus().get_base()
     <<  "]";

  return ss.str();
}

