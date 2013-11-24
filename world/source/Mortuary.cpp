#include "Mortuary.hpp"
#include "Serialize.hpp"

using namespace std;

bool Mortuary::operator==(const Mortuary& m) const
{
  bool result = true;

  result = result && (creatures_killed == m.creatures_killed);

  return result;
}

// Update the death toll.
void Mortuary::add_creature_kill(const string& creature_id)
{
  MortuaryCountMap::iterator m_it = creatures_killed.find(creature_id);

  if (m_it != creatures_killed.end())
  {
    creatures_killed[creature_id] = m_it->second + 1;
  }
  else
  {
    creatures_killed.insert(make_pair(creature_id, 1));
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
    num_killed = m_it->second;
  }

  return num_killed;
}

// Get the total number of creatures killed.
uint Mortuary::get_num_creatures_killed() const
{
  uint num_killed = 0;

  for (const MortuaryCountMap::value_type& pair : creatures_killed)
  {
    num_killed += pair.second;
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
      Serialize::write_uint(stream, pair.second);
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

      uint creature_count = 0;
      Serialize::read_uint(stream, creature_count);

      creatures_killed.insert(make_pair(creature_id, creature_count));
    }
  }

  return true;
}

ClassIdentifier Mortuary::internal_class_identifier() const
{
  return CLASS_ID_MORTUARY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Mortuary_test.cpp"
#endif

