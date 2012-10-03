#pragma once
#include "Creature.hpp"
#include "Environment.hpp"
#include "SerializationTypes.hpp"

class Serialization
{
  public:
    static void save(CreaturePtr creature);
    static SerializationReturnCode load();
};

