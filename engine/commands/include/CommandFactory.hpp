#pragma once
#include <string>
#include "Command.hpp"

class CommandFactory
{
  public:
    static CommandPtr create(const std::string& command_name);

  protected:
    CommandFactory();
    ~CommandFactory();
};
