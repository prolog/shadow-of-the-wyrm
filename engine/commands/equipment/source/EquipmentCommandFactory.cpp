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
    command = std::make_shared<WearOrRemoveHeadCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_NECK)
  {
    command = std::make_shared<WearOrRemoveNeckCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER)
  {
    command = std::make_shared<WearOrRemoveRightFingerCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER)
  {
    command = std::make_shared<WearOrRemoveLeftFingerCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED)
  {
    command = std::make_shared<WearOrRemoveWieldedCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND)
  {
    command = std::make_shared<WearOrRemoveOffHandCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_BODY)
  {
    command = std::make_shared<WearOrRemoveBodyCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_AROUND_BODY)
  {
    command = std::make_shared<WearOrRemoveAroundBodyCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_FEET)
  {
    command = std::make_shared<WearOrRemoveFeetCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED)
  {
    command = std::make_shared<WearOrRemoveRangedCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION)
  {
    command = std::make_shared<WearOrRemoveAmmunitionCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
  {
    command = std::make_shared<YourItemsCommand>(key);
  }
  else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
  {
    command = std::make_shared<ExitEquipmentCommand>(key);
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