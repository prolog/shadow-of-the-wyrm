#include <boost/make_shared.hpp>
#include "EquipmentCommandFactory.hpp"
#include "EquipmentCommandKeys.hpp"
#include "EquipmentCommands.hpp"

EquipmentCommandFactory::EquipmentCommandFactory()
{
}

EquipmentCommandFactory::~EquipmentCommandFactory()
{
}

CommandPtr EquipmentCommandFactory::create(const int key, const std::string& command_name)
{
  EquipmentCommandPtr command;

  if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD)
  {
    command = boost::make_shared<WearOrRemoveHeadCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_NECK)
  {
    command = boost::make_shared<WearOrRemoveNeckCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER)
  {
    command = boost::make_shared<WearOrRemoveRightFingerCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER)
  {
    command = boost::make_shared<WearOrRemoveLeftFingerCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED)
  {
    command = boost::make_shared<WearOrRemoveWieldedCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND)
  {
    command = boost::make_shared<WearOrRemoveOffHandCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_BODY)
  {
    command = boost::make_shared<WearOrRemoveBodyCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY)
  {
    command = boost::make_shared<WearOrRemoveAboutBodyCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_FEET)
  {
    command = boost::make_shared<WearOrRemoveFeetCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED)
  {
    command = boost::make_shared<WearOrRemoveRangedCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION)
  {
    command = boost::make_shared<WearOrRemoveAmmunitionCommand>();
  }
  else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
  {
    command = boost::make_shared<YourItemsCommand>();
  }
  else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
  {
    command = boost::make_shared<ExitEquipmentCommand>();
  }

  return command;
}

CommandFactoryType EquipmentCommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_EQUIPMENT;
}

CommandFactory* EquipmentCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier EquipmentCommandFactory::internal_class_identifier() const
{
  return CLASS_ID_EQUIPMENT_COMMAND_FACTORY;
}

