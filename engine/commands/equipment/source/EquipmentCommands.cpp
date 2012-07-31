#include "EquipmentCommands.hpp"
#include "EquipmentCommandKeys.hpp"

// Equipment-related base class
EquipmentCommand::EquipmentCommand(const std::string& equipment_command_name)
: Command(equipment_command_name)
{
}

EquipmentCommand::~EquipmentCommand()
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

// Wielded slot
WearOrRemoveWieldedCommand::WearOrRemoveWieldedCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED)
{
}

EquipmentWornLocation WearOrRemoveWieldedCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_WIELDED;
}

// Off hand slot
WearOrRemoveOffHandCommand::WearOrRemoveOffHandCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND)
{
}

EquipmentWornLocation WearOrRemoveOffHandCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_OFF_HAND;
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

// Ranged slot
WearOrRemoveRangedCommand::WearOrRemoveRangedCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED)
{
}

EquipmentWornLocation WearOrRemoveRangedCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_RANGED_WEAPON;
}

// Ammunition slot
WearOrRemoveAmmunitionCommand::WearOrRemoveAmmunitionCommand()
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION)
{
}

EquipmentWornLocation WearOrRemoveAmmunitionCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_AMMUNITION;
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
