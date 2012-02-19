#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "Command.hpp"

// The base CommandFactory, used for commands on the current map.  Other classes
// can subclass this and other classes to define commands for other screens
// (equipment, etc).
class CommandFactory
{
  public:
    CommandFactory();
    virtual ~CommandFactory();

    virtual CommandPtr create(const std::string& command_name);
};

typedef boost::shared_ptr<CommandFactory> CommandFactoryPtr;
