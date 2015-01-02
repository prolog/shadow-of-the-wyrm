#include <string>
#include <sstream>
#include "MobileDecisionStrategy.hpp"

using namespace std;

MobileDecisionStrategy::MobileDecisionStrategy(ControllerPtr new_controller)
: NPCDecisionStrategy(new_controller)
{
}

DecisionStrategy* MobileDecisionStrategy::copy()
{
  return new MobileDecisionStrategy(*this);
}

CommandPtr MobileDecisionStrategy::get_decision_for_inventory(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}

CommandPtr MobileDecisionStrategy::get_decision_for_equipment(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}

CommandPtr MobileDecisionStrategy::get_decision_for_tile_selection(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}

bool MobileDecisionStrategy::can_move() const
{
  return true;
}

ClassIdentifier MobileDecisionStrategy::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MOBILE_DECISION_STRATEGY;
}

#ifdef UNIT_TESTS
#include "unit_tests/MobileDecisionStrategy_test.cpp"
#endif

