#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

class Command
{
  public:
    std::string get_name() const;

  protected:
    friend class CommandFactory;
    Command(const std::string& name);
    virtual ~Command();

    std::string command_name;
};

typedef boost::shared_ptr<Command> CommandPtr;
