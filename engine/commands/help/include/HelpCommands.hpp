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

class IntroductionRoguelikesCommand : public Command
{
  public:
    IntroductionRoguelikesCommand(int key);
};

class SOTWHistoryCommand : public Command
{
  public:
    SOTWHistoryCommand(int key);
};

class StrategyBasicsCommand : public Command
{
  public:
    StrategyBasicsCommand(int key);
};