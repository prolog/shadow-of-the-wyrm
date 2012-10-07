#pragma once
#include "CommandFactory.hpp"
#include "ClassIdentifiers.hpp"

typedef std::map<ClassIdentifier, CommandFactoryPtr> CommandFactorySerializationMap;

// I am so sorry.  "FactoryFactory"?  It sounds so enterprisey.  Maybe 
// I could leverage synergies and SaaS, too.
class CommandFactoryFactory
{
  public:
    static CommandFactoryPtr create_command_factory(const ClassIdentifier ci);

  protected:
    CommandFactoryFactory();
    ~CommandFactoryFactory();

    static void initialize_command_factory_map();
    static CommandFactorySerializationMap command_factory_map;
};

