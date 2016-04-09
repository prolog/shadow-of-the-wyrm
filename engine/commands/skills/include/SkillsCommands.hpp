#pragma once
#include "Command.hpp"

class GeneralSkillsCommand : public Command
{
  public:
    GeneralSkillsCommand(const int key);
};

class MeleeWeaponSkillsCommand : public Command
{
  public:
    MeleeWeaponSkillsCommand(int key);
};

class RangedWeaponSkillsCommand : public Command
{
  public:
    RangedWeaponSkillsCommand(int key);
};

class MagicSkillsCommand : public Command
{
  public:
    MagicSkillsCommand(int key);
};

class SelectSkillCommand : public Command
{
  public:
    SelectSkillCommand(int key);
};

class ExitSkillsCommand : public Command
{
  public:
    ExitSkillsCommand(int key);
};

