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

CommandPtr ImmobileDecisionStrategy::get_decision_for_inventory(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_equipment(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr null;
  return null;
}

CommandPtr ImmobileDecisionStrategy::get_decision_for_tile_selection(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
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
  return CLASS_ID_IMMOBILE_DECISION_STRATEGY;
}