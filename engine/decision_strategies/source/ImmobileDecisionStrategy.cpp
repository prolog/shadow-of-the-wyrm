#include <string>
#include <sstream>
#include "ImmobileDecisionStrategy.hpp"

using namespace std;

ImmobileDecisionStrategy::ImmobileDecisionStrategy(ControllerPtr new_controller)
: controller(new_controller)
{
}

CommandPtr ImmobileDecisionStrategy::get_decision(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands)
{
  CommandPtr command;

  // JCD FIXME: Logic goes here.

  return command;
}


// Monsters always return true...
bool ImmobileDecisionStrategy::get_confirmation()
{
  return true;
}
