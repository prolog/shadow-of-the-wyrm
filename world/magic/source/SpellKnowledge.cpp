#include "SpellKnowledge.hpp"
#include "Serialize.hpp"

using namespace std;

bool SpellKnowledge::operator==(const SpellKnowledge& sp) const
{
  bool result = true;

  //  result = result && (spell_knowledge == sp.spell_knowledge);
  result = result && (most_recently_cast_spell_id == sp.most_recently_cast_spell_id);

  return result;
}

void SpellKnowledge::set_spell_knowledge(const string& spell_id, const IndividualSpellKnowledge& isk)
{
  spell_knowledge[spell_id] = isk;
}

IndividualSpellKnowledge SpellKnowledge::get_spell_knowledge(const string& spell_id) const
{
  IndividualSpellKnowledge isk;

  map<string, IndividualSpellKnowledge>::const_iterator s_it = spell_knowledge.find(spell_id);

  if (s_it != spell_knowledge.end())
  {
    isk = s_it->second;
  }

  return isk;
}

// Because we keep track of all spells ever learned (if they can't be cast, they're at 0),
// the "count_spells_known" function checks to see how many spells have non-zero castings
// available.
uint SpellKnowledge::count_spells_known() const
{
  uint spells_known = 0;

  for (const SpellKnowledgeMap::value_type& pair : spell_knowledge)
  {
    if (pair.second.get_castings() > 0) spells_known++;
  }

  return spells_known;
}

bool SpellKnowledge::get_knows_spells() const
{
  for (const auto& pair : spell_knowledge)
  {
    if (pair.second.get_castings() > 0)
    {
      return true;
    }
  }

  return false;
}

SpellKnowledgeMap SpellKnowledge::get_known_spells() const
{
  return spell_knowledge;
}

void SpellKnowledge::set_most_recently_cast_spell_id(const string& spell_id)
{
  most_recently_cast_spell_id = spell_id;
}

string SpellKnowledge::get_most_recently_cast_spell_id() const
{
  return most_recently_cast_spell_id;
}

bool SpellKnowledge::serialize(ostream& stream) const
{
  size_t num_spells = spell_knowledge.size();

  Serialize::write_size_t(stream, num_spells);

  if (num_spells > 0)
  {
    for (const SpellKnowledgeMap::value_type& sp_pair : spell_knowledge)
    {
      string spell_id = sp_pair.first;
      IndividualSpellKnowledge isk = sp_pair.second;

      Serialize::write_string(stream, spell_id);
      isk.serialize(stream);
    }
  }

  Serialize::write_string(stream, most_recently_cast_spell_id);

  return true;
}

bool SpellKnowledge::deserialize(istream& stream)
{
  size_t num_spells = 0;
  Serialize::read_size_t(stream, num_spells);

  if (num_spells > 0)
  {
    spell_knowledge.clear();

    for (uint i = 0; i < num_spells; i++)
    {
      string spell_id;
      IndividualSpellKnowledge isk;

      Serialize::read_string(stream, spell_id);
      isk.deserialize(stream);

      spell_knowledge[spell_id] = isk;
    }
  }

  Serialize::read_string(stream, most_recently_cast_spell_id);

  return true;
}

ClassIdentifier SpellKnowledge::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SPELL_KNOWLEDGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpellKnowledge_test.cpp"
#endif
