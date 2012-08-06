#include <string>
#include <sstream>
#include "ImmobileDecisionStrategy.hpp"

using namespace std;

ImmobileDecisionStrategy::ImmobileDecisionStrategy(ControllerPtr new_controller)
: controller(new_controller)
{
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
