#include <sstream>
#include "ActionCost.hpp"
#include "Serialize.hpp"

using namespace std;

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

bool ActionCost::serialize(ostream& stream) const
{
  Serialize::write_int(stream, cost);
  Serialize::write_bool(stream, turn_advanced);

  return true;
}

bool ActionCost::deserialize(istream& stream)
{
  Serialize::read_int(stream, cost);
  Serialize::read_bool(stream, turn_advanced);

  return true;
}

ClassIdentifier ActionCost::internal_class_identifier() const
{
  return CLASS_ID_ACTION_COST;
}

#ifdef UNIT_TESTS
#include "unit_tests/ActionCost_test.cpp"
#endif
