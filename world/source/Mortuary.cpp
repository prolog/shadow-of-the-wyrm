#include "Mortuary.hpp"
#include "Serialize.hpp"

using namespace std;

bool MortuaryEntry::operator==(const MortuaryEntry& me) const
{
  bool result = true;

  result = result && (count == me.count);
  result = result && (max == me.max);

  return result;
}

bool Mortuary::operator==(const Mortuary& m) const
{
  bool result = true;

  result = result && (creatures_killed == m.creatures_killed);

  return result;
}

// Update the death toll.
void Mortuary::add_creature_kill(const string& creature_id, const bool is_unique)
{
  MortuaryCountMap::iterator m_it = creatures_killed.find(creature_id);

  if (m_it != creatures_killed.end())
  {
    MortuaryEntry& me = creatures_killed[creature_id];
    me.count += 1;
  }
  else
  {
    MortuaryEntry me;

    me.max = (is_unique) ? 1 : -1;
    me.count = 1;

    creatures_killed.insert(make_pair(creature_id, me));
  }
}

MortuaryCountMap Mortuary::get_creatures_killed() const
{
  return creatures_killed;
}

// Get the number of a particular type of creature that have been killed.
uint Mortuary::get_num_creature_killed(const string& creature_id) const
{
  uint num_killed = 0;

  MortuaryCountMap::const_iterator m_it = creatures_killed.find(creature_id);

  if (m_it != creatures_killed.end())
  {
    num_killed = m_it->second.count;
  }

  return num_killed;
}

// Get the total number of creatures killed.
uint Mortuary::get_num_creatures_killed() const
{
  uint num_killed = 0;

  for (const MortuaryCountMap::value_type& pair : creatures_killed)
  {
    num_killed += pair.second.count;
  }

  return num_killed;
}

// Get the number of uniques killed.
uint Mortuary::get_num_uniques_killed() const
{
  uint num_killed = 0;

  for (const MortuaryCountMap::value_type& pair : creatures_killed)
  {
    if (pair.second.max == 1)
    {
      num_killed += pair.second.count;
    }
  }

  return num_killed;
}

bool Mortuary::serialize(ostream& stream) const
{
  size_t ck_size = creatures_killed.size();
  Serialize::write_size_t(stream, ck_size);

  if (ck_size > 0)
  {
    for (const MortuaryCountMap::value_type& pair : creatures_killed)
    {
      Serialize::write_string(stream, pair.first);
      Serialize::write_int(stream, pair.second.max);
      Serialize::write_int(stream, pair.second.count);
    }
  }

  return true;
}

bool Mortuary::deserialize(istream& stream)
{
  size_t ck_size = 0;
  Serialize::read_size_t(stream, ck_size);

  if (ck_size > 0)
  {
    creatures_killed.clear();

    for (uint i = 0; i < ck_size; i++)
    {
      string creature_id;
      Serialize::read_string(stream, creature_id);

      int creature_max = 0;
      Serialize::read_int(stream, creature_max);

      int creature_count = 0;
      Serialize::read_int(stream, creature_count);

      MortuaryEntry me;

      me.max = creature_max;
      me.count = creature_count;

      creatures_killed.insert(make_pair(creature_id, me));
    }
  }

  return true;
}

ClassIdentifier Mortuary::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MORTUARY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Mortuary_test.cpp"
#endif

