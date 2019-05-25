#pragma once
#include "IActionManager.hpp"

// Look up information about an item in the item codex.
class ItemCodexAction : public IActionManager
{
  public:
    ActionCostValue item_details(CreaturePtr creature) const;
    ActionCostValue item_details(CreaturePtr creature, const EquipmentWornLocation ewl);
    ActionCostValue item_details(ItemPtr item);
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

protected:
    friend class ActionManager;
    ItemCodexAction();

    // Figure out what creature best matches the search text, if anything
    // matches at all.
    ItemPtr get_codex_item(const std::string& item_search_text) const;

    // Show the screen with the codex item
    void display_codex_item(ItemPtr item) const;

    static const std::string TEMPLATE_SIGNIFIER;
    static const std::string STRING_REPLACEMENT;
};

