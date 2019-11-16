#pragma once
#include "CommandFactory.hpp"
#include "ClassIdentifiers.hpp"

using CommandFactorySerializationMap = std::map<ClassIdentifier, std::shared_ptr<CommandFactory>>;

// I am so sorry.  "FactoryFactory"?  It sounds so enterprisey.  Maybe 
// I could leverage synergies and SaaS, too.
class CommandFactoryFactory
{
  public:
    CommandFactoryFactory();
    ~CommandFactoryFactory();

    CommandFactoryPtr create_command_factory(const ClassIdentifier ci);

  protected:
    CommandFactorySerializationMap command_factory_map;
};

