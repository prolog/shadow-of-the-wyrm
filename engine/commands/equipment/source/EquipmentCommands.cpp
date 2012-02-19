#include "EquipmentCommands.hpp"
#include "EquipmentCommandKeys.hpp"

// Equipment-related base class
EquipmentCommand::EquipmentCommand(const std::string& equipment_command_name)
: Command(equipment_command_name)
{
}

bool EquipmentCommand::is_wear_or_remove_command() const
{
  return false;
}

// Wear/remove item
WearOrRemoveCommand::WearOrRemoveCommand(const std::string& wear_command_name)
: EquipmentCommand(wear_command_name)
{  
}

bool WearOrRemoveCommand::is_wear_or_remove_command() const
{
  return true;
}

// Head slot
WearOrRemoveHeadCommand::WearOrRemoveHeadCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD)
{
}

EquipmentWornLocation WearOrRemoveHeadCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_HEAD;
}

// Neck slot
WearOrRemoveNeckCommand::WearOrRemoveNeckCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_NECK)
{
}

EquipmentWornLocation WearOrRemoveNeckCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_NECK;
}

// Right ring slot
WearOrRemoveRightFingerCommand::WearOrRemoveRightFingerCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER)
{
}

EquipmentWornLocation WearOrRemoveRightFingerCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_RIGHT_FINGER;
}

// Left finger slot
WearOrRemoveLeftFingerCommand::WearOrRemoveLeftFingerCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER)
{
}

EquipmentWornLocation WearOrRemoveLeftFingerCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_LEFT_FINGER;
}

// Right hand slot
WearOrRemoveRightHandCommand::WearOrRemoveRightHandCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_HAND)
{
}

EquipmentWornLocation WearOrRemoveRightHandCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_RIGHT_HAND;
}

// Left hand slot
WearOrRemoveLeftHandCommand::WearOrRemoveLeftHandCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_HAND)
{
}

EquipmentWornLocation WearOrRemoveLeftHandCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_LEFT_HAND;
}

// Body slot
WearOrRemoveBodyCommand::WearOrRemoveBodyCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_BODY)
{
}

EquipmentWornLocation WearOrRemoveBodyCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_BODY;
}

// About body slot
WearOrRemoveAboutBodyCommand::WearOrRemoveAboutBodyCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY)
{
}

EquipmentWornLocation WearOrRemoveAboutBodyCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_ABOUT_BODY;
}

// Feet slot
WearOrRemoveFeetCommand::WearOrRemoveFeetCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_FEET)
{
}

EquipmentWornLocation WearOrRemoveFeetCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_FEET;
}

// View inventory
YourItemsCommand::YourItemsCommand()
: EquipmentCommand(EquipmentCommandKeys::YOUR_ITEMS)
{
}

// Exit the equipment processing
ExitEquipmentCommand::ExitEquipmentCommand()
: EquipmentCommand(EquipmentCommandKeys::EXIT_EQUIPMENT)
{
}
