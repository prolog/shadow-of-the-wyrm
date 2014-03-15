#pragma once
#include "Command.hpp"

class NextPageMenuCommand : public Command
{
  public:
    NextPageMenuCommand(int key);
};

class PreviousPageMenuCommand : public Command
{
  public:
    PreviousPageMenuCommand(int key);
};


