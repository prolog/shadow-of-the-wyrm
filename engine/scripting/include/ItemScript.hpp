#pragma once
#include <string>
#include <vector>
#include "Creature.hpp"

class ScriptEngine;

// ItemScripts run when particular events (e.g., ammunition being
// destroyed) fire. It is also used for general item-related scripting fns.
class ItemScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& item_script, const std::string& item_event, const std::string& base_item_id, const std::map<std::string, std::string>& item_properties, const std::string& original_creature_id, const int row, const int col);
    std::vector<std::string> execute_get_treasure_items(ScriptEngine& se);

  protected:
    static const std::string ITEM_MODULE_NAME;
    static const std::string ITEM_FUNCTION_NAME;
    static const std::string GET_TREASURE_ITEMS_FUNCTION_NAME;
};

