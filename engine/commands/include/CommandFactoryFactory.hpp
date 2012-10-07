#pragma once
#include "CommandFactory.hpp"
#include "ClassIdentifiers.hpp"

typedef std::map<ClassIdentifier, boost::shared_ptr<CommandFactory>> CommandFactorySerializationMap;

// I am so sorry.  "FactoryFactory"?  It sounds so enterprisey.  Maybe 
// I could leverage synergies and SaaS, too.
class CommandFactoryFactory
{
  public:
    static CommandFactoryPtr create_command_factory(const ClassIdentifier ci);

  protected:
    static void initialize_command_factory_map();
    static CommandFactorySerializationMap command_factory_map;
};

