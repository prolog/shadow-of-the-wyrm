#include <string>
#include <sstream>
#include "ImmobileDecisionStrategy.hpp"

using namespace std;

ImmobileDecisionStrategy::ImmobileDecisionStrategy(ControllerPtr new_controller)
: NPCDecisionStrategy(new_controller)
{
}

DecisionStrategy* ImmobileDecisionStrategy::copy()
{
  return new ImmobileDecisionStrategy(*this);
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_inventory(CommandFactory* /*command_factory*/, KeyboardCommandMap* /*keyboard_commands*/)
{
  CommandPtr null;
  return null;
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_equipment(CommandFactory* /*command_factory*/, KeyboardCommandMap* /*keyboard_commands*/)
{
  CommandPtr null;
  return null;
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_tile_selection(CommandFactory* /*command_factory*/, KeyboardCommandMap* /*keyboard_commands*/)
{
  CommandPtr null;
  return null;
}

bool ImmobileDecisionStrategy::can_move() const
{
  return false;
}

ClassIdentifier ImmobileDecisionStrategy::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_IMMOBILE_DECISION_STRATEGY;
}

#ifdef UNIT_TESTS
#include "unit_tests/ImmobileDecisionStrategy_test.cpp"
#endif

