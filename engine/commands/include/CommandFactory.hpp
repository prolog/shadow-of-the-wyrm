#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "Command.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

enum CommandFactoryType
{
  COMMAND_FACTORY_TYPE_MAP = 0,
  COMMAND_FACTORY_TYPE_INVENTORY = 1,
  COMMAND_FACTORY_TYPE_EQUIPMENT = 2,
  COMMAND_FACTORY_TYPE_SELECT_TILE = 3
};

// The base CommandFactory, used for commands on the current map.  Other classes
// can subclass this and other classes to define commands for other screens
// (equipment, etc).
class CommandFactory
{
  public:
    CommandFactory();
    virtual ~CommandFactory();

    virtual CommandPtr create(const int key, const std::string& command_name);
    virtual CommandFactoryType get_factory_type() const;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};

typedef boost::shared_ptr<CommandFactory> CommandFactoryPtr;
