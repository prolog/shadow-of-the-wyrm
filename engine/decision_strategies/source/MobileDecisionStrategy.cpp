#include <string>
#include <sstream>
#include "MobileDecisionStrategy.hpp"

using namespace std;

MobileDecisionStrategy::MobileDecisionStrategy(ControllerPtr new_controller)
: controller(new_controller)
{
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

bool MobileDecisionStrategy::can_move() const
{
  return true;
}
