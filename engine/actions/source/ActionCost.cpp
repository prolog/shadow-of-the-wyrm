#include <sstream>
#include "ActionCost.hpp"

using std::ostringstream;
using std::string;

ActionCost::ActionCost()
: cost(0)
{
}

ActionCost::ActionCost(const ActionCostValue new_cost)
: cost(new_cost)
{
}

bool ActionCost::operator==(const ActionCost& rhs) const
{
  return (cost == rhs.cost);
}

bool ActionCost::operator!=(const ActionCost& rhs) const
{
  return !operator==(rhs);
}

bool ActionCost::operator< (const ActionCost& rhs) const
{
  return (cost < rhs.cost);
}

bool ActionCost::operator> (const ActionCost& rhs) const
{
  return  operator<(rhs);
}

bool ActionCost::operator<=(const ActionCost& rhs) const
{
  return !operator>(rhs);
}

bool ActionCost::operator>=(const ActionCost& rhs) const
{
  return !operator<(rhs);
}

void ActionCost::set_cost(const ActionCostValue new_cost)
{
  cost = new_cost;
}

ActionCostValue ActionCost::get_cost() const
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
 
  ss << cost << ":" << turn_advanced;
 
  return ss.str();
}
