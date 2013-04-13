#pragma once
#include "Command.hpp"

class SpellCommand : public Command
{
  public:
    int get_spell_index() const;

  protected:
    SpellCommand(const int spell_idx);
    int spell_index;
};

class SelectSpellCommand : public SpellCommand
{
  public:
    SelectSpellCommand(const int spell_idx);
    
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

