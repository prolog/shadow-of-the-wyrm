#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

// ItemScripts run when particular events (e.g., ammunition being
// destroyed) fire.
class ItemScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& attack_script, const std::string& item_event, const std::string& base_item_id, const std::string& original_creature_id, const int row, const int col);

  protected:
    static const std::string ITEM_MODULE_NAME;
    static const std::string ITEM_FUNCTION_NAME;
};

