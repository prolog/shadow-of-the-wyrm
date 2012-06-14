#include <sstream>
#include "ActionCost.hpp"

using std::ostringstream;
using std::string;

ActionCost::ActionCost(const std::string& new_id, const uint new_cost)
: id(new_id), cost(new_cost)
{
}

bool ActionCost::operator==(const ActionCost& rhs)
{
  return (cost == rhs.cost);
}

bool ActionCost::operator!=(const ActionCost& rhs)
{
  return !operator==(rhs);
}

bool ActionCost::operator< (const ActionCost& rhs)
{
  return (cost < rhs.cost);
}

bool ActionCost::operator> (const ActionCost& rhs)
{
  return  operator<(rhs);
}

bool ActionCost::operator<=(const ActionCost& rhs)
{
  return !operator>(rhs);
}

bool ActionCost::operator>=(const ActionCost& rhs)
{
  return !operator<(rhs);
}


string ActionCost::get_action_creature_id() const
{
  return id;
}

unsigned int ActionCost::get_cost() const
{
  return cost;
}

bool ActionCost::get_turn_advanced() const
{
  return (cost > 0);
}

string ActionCost::str() const
{
  ostringstream ss;
 
  ss << id << ":" << cost << ":" << turn_advanced;
 
  return ss.str();
}
