#pragma once
#include "Command.hpp"
#include "EquipmentTypes.hpp"

// Base class for all equipment-related commands
class EquipmentCommand : public Command
{
  public:
    EquipmentCommand(const std::string& command_name, int key);
    virtual ~EquipmentCommand();
    
    virtual bool is_wear_or_remove_command() const;
};

using EquipmentCommandPtr = std::shared_ptr<EquipmentCommand>;

// Abstract intermediary class inherited by the various wear/remove class commands
class WearOrRemoveCommand : public EquipmentCommand
{
  public:
    WearOrRemoveCommand(const std::string& command_name, int key);
    
    virtual EquipmentWornLocation get_equipment_worn_location() const = 0;
    virtual bool is_wear_or_remove_command() const override;
};

class WearOrRemoveHeadCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveHeadCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveNeckCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveNeckCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveRightFingerCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveRightFingerCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveLeftFingerCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveLeftFingerCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveWieldedCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveWieldedCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveOffHandCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveOffHandCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveBodyCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveBodyCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveAroundBodyCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveAroundBodyCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveFeetCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveFeetCommand(int key);

    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveRangedCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveRangedCommand(int key);
    
    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class WearOrRemoveAmmunitionCommand : public WearOrRemoveCommand
{
  public:
    WearOrRemoveAmmunitionCommand(int key);
    
    virtual EquipmentWornLocation get_equipment_worn_location() const override;
};

class YourItemsCommand : public EquipmentCommand
{
  public:
    YourItemsCommand(int key);
};

class ExitEquipmentCommand : public EquipmentCommand
{
  public:
    ExitEquipmentCommand(int key);
};
