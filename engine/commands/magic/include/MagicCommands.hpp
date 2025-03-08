#pragma once
#include "Command.hpp"

class SpellCommand : public Command
{
  public:
    virtual ~SpellCommand() = default;

    int get_spell_index() const;

  protected:
    SpellCommand(const int spell_idx, const int key);
    int spell_index;
};

class SelectSpellCommand : public SpellCommand
{
  public:
    SelectSpellCommand(const int spell_idx, const int key);
};

class ArcanaCommand : public SpellCommand
{
  public:
    ArcanaCommand(const int spell_idx, const int key);

    static const std::string ARCANA_ID;
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

