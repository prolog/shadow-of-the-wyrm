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
    command = std::make_shared<WearOrRemoveHeadCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_NECK)
  {
    command = std::make_shared<WearOrRemoveNeckCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER)
  {
    command = std::make_shared<WearOrRemoveRightFingerCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER)
  {
    command = std::make_shared<WearOrRemoveLeftFingerCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED)
  {
    command = std::make_shared<WearOrRemoveWieldedCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND)
  {
    command = std::make_shared<WearOrRemoveOffHandCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_BODY)
  {
    command = std::make_shared<WearOrRemoveBodyCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY)
  {
    command = std::make_shared<WearOrRemoveAboutBodyCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_FEET)
  {
    command = std::make_shared<WearOrRemoveFeetCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED)
  {
    command = std::make_shared<WearOrRemoveRangedCommand>();
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION)
  {
    command = std::make_shared<WearOrRemoveAmmunitionCommand>();
  }
  else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
  {
    command = std::make_shared<YourItemsCommand>();
  }
  else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
  {
    command = std::make_shared<ExitEquipmentCommand>();
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

#ifdef UNIT_TESTS
#include "unit_tests/EquipmentCommandFactory_test.cpp"
#endif