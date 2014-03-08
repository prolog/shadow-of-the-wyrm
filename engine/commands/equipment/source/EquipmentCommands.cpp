#include "EquipmentCommands.hpp"
#include "EquipmentCommandKeys.hpp"

// Equipment-related base class
EquipmentCommand::EquipmentCommand(const std::string& equipment_command_name, const int key)
: Command(equipment_command_name, key)
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
WearOrRemoveCommand::WearOrRemoveCommand(const std::string& wear_command_name, const int key)
: EquipmentCommand(wear_command_name, key)
{  
}

bool WearOrRemoveCommand::is_wear_or_remove_command() const
{
  return true;
}

// Head slot
WearOrRemoveHeadCommand::WearOrRemoveHeadCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD, key)
{
}

EquipmentWornLocation WearOrRemoveHeadCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_HEAD;
}

// Neck slot
WearOrRemoveNeckCommand::WearOrRemoveNeckCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_NECK, key)
{
}

EquipmentWornLocation WearOrRemoveNeckCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_NECK;
}

// Right ring slot
WearOrRemoveRightFingerCommand::WearOrRemoveRightFingerCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER, key)
{
}

EquipmentWornLocation WearOrRemoveRightFingerCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_RIGHT_FINGER;
}

// Left finger slot
WearOrRemoveLeftFingerCommand::WearOrRemoveLeftFingerCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER, key)
{
}

EquipmentWornLocation WearOrRemoveLeftFingerCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_LEFT_FINGER;
}

// Wielded slot
WearOrRemoveWieldedCommand::WearOrRemoveWieldedCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED, key)
{
}

EquipmentWornLocation WearOrRemoveWieldedCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_WIELDED;
}

// Off hand slot
WearOrRemoveOffHandCommand::WearOrRemoveOffHandCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND, key)
{
}

EquipmentWornLocation WearOrRemoveOffHandCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_OFF_HAND;
}

// Body slot
WearOrRemoveBodyCommand::WearOrRemoveBodyCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_BODY, key)
{
}

EquipmentWornLocation WearOrRemoveBodyCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_BODY;
}

// About body slot
WearOrRemoveAboutBodyCommand::WearOrRemoveAboutBodyCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY, key)
{
}

EquipmentWornLocation WearOrRemoveAboutBodyCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_ABOUT_BODY;
}

// Feet slot
WearOrRemoveFeetCommand::WearOrRemoveFeetCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_FEET, key)
{
}

EquipmentWornLocation WearOrRemoveFeetCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_FEET;
}

// Ranged slot
WearOrRemoveRangedCommand::WearOrRemoveRangedCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED, key)
{
}

EquipmentWornLocation WearOrRemoveRangedCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_RANGED_WEAPON;
}

// Ammunition slot
WearOrRemoveAmmunitionCommand::WearOrRemoveAmmunitionCommand(const int key)
: WearOrRemoveCommand(EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION, key)
{
}

EquipmentWornLocation WearOrRemoveAmmunitionCommand::get_equipment_worn_location() const
{
  return EQUIPMENT_WORN_AMMUNITION;
}

// View inventory
YourItemsCommand::YourItemsCommand(const int key)
: EquipmentCommand(EquipmentCommandKeys::YOUR_ITEMS, key)
{
}

// Exit the equipment processing
ExitEquipmentCommand::ExitEquipmentCommand(const int key)
: EquipmentCommand(EquipmentCommandKeys::EXIT_EQUIPMENT, key)
{
}
