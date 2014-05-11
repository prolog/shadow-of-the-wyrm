#pragma once
#include "Command.hpp"

class NextPageScreenCommand : public Command
{
  public:
    NextPageScreenCommand(int key);
};

class PreviousPageScreenCommand : public Command
{
  public:
    PreviousPageScreenCommand(int key);
};


