#pragma once
#include "Command.hpp"

class KeybindingsCommand : public Command
{
  public:
    KeybindingsCommand(const int key);
};

class ExitHelpCommand : public Command
{
  public:
    ExitHelpCommand(int key);
};
