#include "CreatureActions.hpp"
#include "Serialize.hpp"

using namespace std;

// Creature action keys

const string CreatureActionKeys::ACTION_ATTACK_FRIENDLY = "AttackFriendlyCreature";
const string CreatureActionKeys::ACTION_CANNIBALISM = "Cannibalism";
const string CreatureActionKeys::ACTION_DESECRATE_GOOD = "DesecrateGood";
const string CreatureActionKeys::ACTION_DESECRATE_NEUTRAL = "DesecrateNeutral";
const string CreatureActionKeys::ACTION_DESECRATE_EVIL = "DesecrateEvil";
const string CreatureActionKeys::ACTION_GRAVEROBBING = "GraveRobbing";

bool CreatureActions::operator==(const CreatureActions& ca) const
{
  bool result = true;

  result = result && (creature_action_map == ca.creature_action_map);

  return result;
}

// Creature Actions 
void CreatureActions::set_action_value(const string& action, const bool val)
{
  creature_action_map[action] = val;
}

bool CreatureActions::get_action_value(const string& action) const
{
  bool action_val = false;
  CreatureActionMap::const_iterator a_it = creature_action_map.find(action);

  if (a_it != creature_action_map.end())
  {
    action_val = a_it->second;
  }

  return action_val;
}

bool CreatureActions::serialize(ostream& stream) const
{
  size_t size = creature_action_map.size();
  Serialize::write_size_t(stream, size);

  for (const auto& map_pair : creature_action_map)
  {
    Serialize::write_string(stream, map_pair.first);
    Serialize::write_bool(stream, map_pair.second);
  }

  return true;
}

bool CreatureActions::deserialize(istream& stream)
{
  size_t size = 0;
  Serialize::read_size_t(stream, size);

  if (size > 0)
  {
    creature_action_map.clear();
  }

  for (size_t i = 0; i < size; i++)
  {
    string key;
    bool value = false;

    Serialize::read_string(stream, key);
    Serialize::read_bool(stream, value);

    creature_action_map.insert(make_pair(key, value));
  }
  return true;
}

ClassIdentifier CreatureActions::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CREATURE_ACTIONS;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureActions_test.cpp"
#endif