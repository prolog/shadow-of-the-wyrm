#pragma once
#include <map>
#include <string>
#include <memory>
#include "Command.hpp"
#include "ISerializable.hpp"

enum CommandFactoryType
{
  COMMAND_FACTORY_TYPE_MAP = 0,
  COMMAND_FACTORY_TYPE_INVENTORY = 1,
  COMMAND_FACTORY_TYPE_EQUIPMENT = 2,
  COMMAND_FACTORY_TYPE_SELECT_TILE = 3,
  COMMAND_FACTORY_TYPE_MAGIC = 4,
  COMMAND_FACTORY_TYPE_SCREEN = 5
};

// The base CommandFactory, used for commands on the current map.  Other classes
// can subclass this and other classes to define commands for other screens
// (equipment, etc).
class CommandFactory : public ISerializable
{
  public:
    CommandFactory();
    virtual ~CommandFactory();

    virtual CommandPtr create(const int key, const std::string& command_name);
    virtual CommandFactoryType get_factory_type() const;

    virtual CommandFactory* clone();

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<CommandFactory> CommandFactoryPtr;
