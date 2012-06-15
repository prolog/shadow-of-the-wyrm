#include <sstream>
#include "ActionCost.hpp"

using std::ostringstream;
using std::string;

ActionCost::ActionCost(const ActionCostValue new_cost)
: cost(new_cost)
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
