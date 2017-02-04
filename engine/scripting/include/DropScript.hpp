#pragma once
#include <string>
#include "common.hpp"
#include "Creature.hpp"
#include "Item.hpp"

class ScriptEngine;

// Allows creatures to react to drop events.
class DropScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& drop_script, const std::string& dropping_creature_id, CreaturePtr reacting_creature, ItemPtr item, const Coordinate& drop_location);
  
  protected:
    static const std::string DROP_MODULE_NAME;
    static const std::string DROP_FUNCTION_NAME;
};

