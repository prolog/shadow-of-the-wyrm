#include "NullReadStrategy.hpp"

using namespace std;

ActionCostValue NullReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  return get_action_cost_value(creature);
}

pair<string, string> NullReadStrategy::get_player_and_monster_read_sids() const
{
  pair<string,string> no_sids;
  return no_sids;
}

// Trying to read an unreadable type of item should never happen!
ActionCostValue NullReadStrategy::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}


