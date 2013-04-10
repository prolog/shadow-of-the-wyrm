#pragma once
#include "Command.hpp"

class SelectSpellCommand : public Command
{
  public:
    SelectSpellCommand();
    
//    virtual EquipmentWornLocation get_equipment_worn_location() const = 0;
};

class NextPageMagicCommand : public Command
{
  public:
    NextPageMagicCommand();
};

class PreviousPageMagicCommand : public Command
{
  public:
    PreviousPageMagicCommand();
};

class ExitMagicCommand : public Command
{
  public:
    ExitMagicCommand();
};

