#include <sstream>
#include "SpellDescriber.hpp"
#include "Conversion.hpp"
#include "Skills.hpp"
#include "SpellcastingTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

map<SpellShapeType, string> SpellDescriber::shape_abbreviation_sids;

SpellDescriber::SpellDescriber(CreaturePtr new_creature, const Spell& new_spell)
: creature(new_creature), spell(new_spell)
{
  initialize_shape_abbreviation_sids();
}

void SpellDescriber::initialize_shape_abbreviation_sids()
{
  static_assert(SpellShapeType::SPELL_SHAPE_LAST == SpellShapeType(7), "Unexpected SPELL_SHAPE_LAST value.");

  shape_abbreviation_sids.clear();
  shape_abbreviation_sids = map<SpellShapeType, string>{{SpellShapeType::SPELL_SHAPE_TARGET_SELF, SpellcastingTextKeys::SPELLCASTING_TARGET_SELF_ABRV},
                                                        {SpellShapeType::SPELL_SHAPE_BEAM, SpellcastingTextKeys::SPELLCASTING_BEAM_ABRV},
                                                        {SpellShapeType::SPELL_SHAPE_REFLECTIVE_BEAM, SpellcastingTextKeys::SPELLCASTING_REFLECTIVE_BEAM_ABRV},
                                                        {SpellShapeType::SPELL_SHAPE_CONE, SpellcastingTextKeys::SPELLCASTING_CONE_ABRV},
                                                        {SpellShapeType::SPELL_SHAPE_BALL, SpellcastingTextKeys::SPELLCASTING_BALL_ABRV},
                                                        {SpellShapeType::SPELL_SHAPE_CROSS, SpellcastingTextKeys::SPELLCASTING_CROSS_ABRV},
                                                        {SpellShapeType::SPELL_SHAPE_STORM, SpellcastingTextKeys::SPELLCASTING_STORM_ABRV}};
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
             << ", " << StringTable::get(TextKeys::RANGE_ABRV) << ":" << describe_range()
             << ", " << StringTable::get(TextKeys::ARCANA_POINTS_ABRV) << ":" << spell.get_ap_cost()
             << ", +"<< isk.get_bonus().get_base()
     <<  "]";

  return ss.str();
}

// Describe the range by using the appropriate abbreviation, based on the range
// and the spell type.
string SpellDescriber::describe_range() const
{
  stringstream ss;

  ss << spell.get_range() << StringTable::get(shape_abbreviation_sids.find(spell.get_shape().get_spell_shape_type())->second);

  return ss.str();
}