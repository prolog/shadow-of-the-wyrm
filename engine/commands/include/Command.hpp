#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

class Command
{
  public:
    std::string get_name() const;

  protected:
    // friend class ...
    Command(const std::string& name);

    std::string command_name;
};

typedef boost::shared_ptr<Command> CommandPtr;
