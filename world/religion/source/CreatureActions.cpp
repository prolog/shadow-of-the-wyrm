#include "CreatureActions.hpp"

using namespace std;

// Creature action keys

const string CreatureActionKeys::ACTION_ATTACK_FRIENDLY = "ACTION_ATTACK_FRIENDLY";


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

