#include <boost/foreach.hpp>
#include "SpellKnowledge.hpp"
#include "Serialize.hpp"

using namespace std;

bool SpellKnowledge::operator==(const SpellKnowledge& sp)
{
  bool result = true;

  result = result && (spell_knowledge == sp.spell_knowledge);
  result = result && (most_recently_cast_spell_id == sp.most_recently_cast_spell_id);

  return result;
}

void SpellKnowledge::set_spell_knowledge(const string& spell_id, const uint cast_count)
{
  spell_knowledge[spell_id] = cast_count;
}

uint SpellKnowledge::get_spell_knowledge(const string& spell_id) const
{
  uint cast_count = 0;

  map<string, uint>::const_iterator s_it = spell_knowledge.find(spell_id);

  if (s_it != spell_knowledge.end())
  {
    cast_count = s_it->second;
  }

  return cast_count;
}

uint SpellKnowledge::count_spells_known() const
{
  return spell_knowledge.size();
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

bool SpellKnowledge::serialize(ostream& stream)
{
  size_t num_spells = spell_knowledge.size();

  Serialize::write_size_t(stream, num_spells);

  if (num_spells > 0)
  {
    BOOST_FOREACH(SpellKnowledgeMap::value_type& sp_pair, spell_knowledge)
    {
      string spell_id = sp_pair.first;
      uint spell_count = sp_pair.second;

      Serialize::write_string(stream, spell_id);
      Serialize::write_uint(stream, spell_count);
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
      uint spell_count = 0;

      Serialize::read_string(stream, spell_id);
      Serialize::read_uint(stream, spell_count);

      spell_knowledge[spell_id] = spell_count;
    }
  }

  Serialize::read_string(stream, most_recently_cast_spell_id);

  return true;
}

ClassIdentifier SpellKnowledge::internal_class_identifier() const
{
  return CLASS_ID_SPELL_KNOWLEDGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpellKnowledge_test.cpp"
#endif
