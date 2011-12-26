#pragma once
#include <string>

class Command
{
  public:
    std::string get_name() const;

  protected:
    // friend class ...
    Command(const std::string& name);

    std::string command_name;
};
