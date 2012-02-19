#include <boost/make_shared.hpp>
#include "EquipmentCommandFactory.hpp"
#include "EquipmentCommandKeys.hpp"
#include "EquipmentCommands.hpp"

using boost::make_shared;

EquipmentCommandFactory::EquipmentCommandFactory()
{
}

EquipmentCommandFactory::~EquipmentCommandFactory()
{
}

CommandPtr EquipmentCommandFactory::create(const std::string& command_name)
{
  EquipmentCommandPtr command;

  if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD)
  {
    command = make_shared<WearOrRemoveHeadCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_NECK)
  {
    command = make_shared<WearOrRemoveNeckCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER)
  {
    command = make_shared<WearOrRemoveRightFingerCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER)
  {
    command = make_shared<WearOrRemoveLeftFingerCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_HAND)
  {
    command = make_shared<WearOrRemoveRightHandCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_HAND)
  {
    command = make_shared<WearOrRemoveLeftHandCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_BODY)
  {
    command = make_shared<WearOrRemoveBodyCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY)
  {
    command = make_shared<WearOrRemoveAboutBodyCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_FEET)
  {
    command = make_shared<WearOrRemoveFeetCommand>();
  }
  else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
  {
    command = make_shared<YourItemsCommand>();
  }
  else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
  {
    command = make_shared<ExitEquipmentCommand>();
  }

  return command;
}
