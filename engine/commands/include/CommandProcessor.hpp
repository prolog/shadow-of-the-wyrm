#pragma once
#include "Command.hpp"

class CommandProcessor
{
  public:
    static void process(CommandPtr command);

  protected:
    CommandProcessor();
    ~CommandProcessor();
};
