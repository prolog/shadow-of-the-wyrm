#include <boost/foreach.hpp>
#include "ActionCoordinator.hpp"

using namespace std;

void ActionCoordinator::set(const map<string, CreaturePtr>& creatures)
{
  creature_action_order.clear();
  
  for (map<string, CreaturePtr>::const_iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
  {
    if (c_it->second)
    {
      ActionCost ac; // Default initially - will be 0.
      string creature_id = c_it->first;
      creature_action_order.insert(make_pair(ac, creature_id));
    }
  }
}

void ActionCoordinator::add(const ActionCost& ac, const string& creature_id)
{
  creature_action_order.insert(make_pair(ac, creature_id));
}

void ActionCoordinator::clear()
{
  creature_action_order.clear();
}

void ActionCoordinator::update_actions()
{
  // Remove the first item from the map, and update the remaining costs based on the current minus the cost of the first.
  multimap<ActionCost, string> new_action_ordering;

  if (!creature_action_order.empty())
  {
    ActionOrderIterator ac_it = creature_action_order.begin();
    pair<ActionCost, string> next_action = *(ac_it);
    creature_action_order.erase(ac_it);
    
    ActionCostValue next_action_cost_value = next_action.first.get_cost();
    
    for (ActionOrderIterator reorder_it = creature_action_order.begin(); reorder_it != creature_action_order.end(); reorder_it++)
    {
      ActionCost ac = reorder_it->first;
      ac.set_cost(ac.get_cost() - next_action_cost_value);
      
      new_action_ordering.insert(make_pair(ac, reorder_it->second));
    }
  }
  
  creature_action_order = new_action_ordering;
}

// Return the creature ID of the next creature to act.
string ActionCoordinator::get_next_creature_id() const
{
  string next_creature_id;

  if (!creature_action_order.empty())
  {
    next_creature_id = creature_action_order.begin()->second;
  }
  
  return next_creature_id;
}

// Get the cost of the next action - used to determine how much
// to increment the world's calendar by, among other things.
ActionCost ActionCoordinator::get_next_action_cost() const
{
  ActionCost next_action_cost;
  
  if (!creature_action_order.empty())
  {
    next_action_cost = creature_action_order.begin()->first;
  }
  
  return next_action_cost;
}

// Return the creature ID of the next creature to act,
// and then remove the first item from the map via update()
string ActionCoordinator::get_next_creature_id_and_update_actions()
{
  string creature_id = get_next_creature_id();
  update_actions();
  return creature_id;
}

// Check to see if there are any creatures in the queue.
bool ActionCoordinator::has_actions() const
{
  return (!creature_action_order.empty());
}
