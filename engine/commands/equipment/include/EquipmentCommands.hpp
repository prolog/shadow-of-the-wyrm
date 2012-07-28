#pragma once
#include "Command.hpp"
#include "EquipmentTypes.hpp"

// Base class for all equipment-related commands
class EquipmentCommand : public Command
{
  public:
    EquipmentCommand(const std::string& command_name);
    virtual ~EquipmentCommand();
    
    virtual bool is_wear_or_remove_command() const;
};

typedef boost::shared_ptr<EquipmentCommand> EquipmentCommandPtr;

// Abstract intermediary class inherited by the various wear/remove class commands
class WearOrRemoveCommand : public EquipmentCommand
{
  public:
    WearOrRemoveCommand(const std::string& command_name);
    
    virtual EquipmentWornLocation get_equipment_worn_location() const = 0;
    virtual bool is_wear_or_remove_command() const;
};

class WearOrRemoveHeadCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveHeadCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveNeckCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveNeckCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveRightFingerCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveRightFingerCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveLeftFingerCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveLeftFingerCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveRightHandCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveRightHandCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveLeftHandCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveLeftHandCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveBodyCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveBodyCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveAboutBodyCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveAboutBodyCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveFeetCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveFeetCommand();

    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveRangedCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveRangedCommand();
    
    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class WearOrRemoveAmmunitionCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveAmmunitionCommand();
    
    virtual EquipmentWornLocation get_equipment_worn_location() const;
};

class YourItemsCommand : public EquipmentCommand
{
  public:
    YourItemsCommand();
};

class ExitEquipmentCommand : public EquipmentCommand
{
  public:
    ExitEquipmentCommand();
};
