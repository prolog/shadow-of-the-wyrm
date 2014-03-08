#pragma once
#include "Command.hpp"

class SpellCommand : public Command
{
  public:
    int get_spell_index() const;

  protected:
    SpellCommand(const int spell_idx, const int key);
    int spell_index;
};

class SelectSpellCommand : public SpellCommand
{
  public:
    SelectSpellCommand(const int spell_idx, const int key);
    
//    virtual EquipmentWornLocation get_equipment_worn_location() const = 0;
};

class NextPageMagicCommand : public Command
{
  public:
    NextPageMagicCommand(int key);
};

class PreviousPageMagicCommand : public Command
{
  public:
    PreviousPageMagicCommand(int key);
};

class ExitMagicCommand : public Command
{
  public:
    ExitMagicCommand(int key);
};

