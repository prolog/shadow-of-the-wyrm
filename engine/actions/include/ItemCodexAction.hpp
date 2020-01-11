#pragma once
#include <vector>
#include "Colours.hpp"
#include "IActionManager.hpp"
#include "CodexDescriber.hpp"

// Look up information about an item in the item codex.
class ItemCodexAction : public IActionManager
{
  public:
    ActionCostValue item_details(CreaturePtr creature) const;
    ActionCostValue item_details(CreaturePtr creature, const EquipmentWornLocation ewl) const;
    ActionCostValue item_details(CreaturePtr creature, ItemPtr item, const bool skip_blindness_checks = true) const;
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

protected:
    friend class ActionManager;
    ItemCodexAction();

    // Figure out what creature best matches the search text, if anything
    // matches at all.
    ItemPtr get_codex_item(const std::string& item_search_text) const;

    // Show the screen with the codex item
    void display_codex_item(ItemPtr item) const;

    // Add certain features to the codex screen
    void add_symbol_and_description_to_codex(ItemPtr item, CodexDescriber* codex_desc, const std::string& separator, std::vector<std::pair<Colour, std::string>>& codex_text, std::deque<Symbol>& codex_symbols) const;
    void add_synopsis_to_codex(ItemPtr item, CodexDescriber* codex_desc, const std::string& separator, std::vector<std::pair<Colour, std::string>>& codex_text) const;
    void add_resistances_to_codex(ItemPtr item, CodexDescriber* codex_desc, const std::string& separator, std::vector<std::pair<Colour, std::string>>& codex_text) const;
    void add_speed_details_to_codex(ItemPtr item, CodexDescriber* codex_desc, const std::string& separator, std::vector<std::pair<Colour, std::string>>& codex_text) const;
    void add_item_details_to_codex(ItemPtr item, CodexDescriber* codex_desc, const std::string& separator, std::vector<std::pair<Colour, std::string>>& codex_text) const;
    void add_description_to_codex(ItemPtr item, CodexDescriber* codex_desc, const std::string& separator, std::vector<std::pair<Colour, std::string>>& codex_text) const;

    static const std::string TEMPLATE_SIGNIFIER;
    static const std::string STRING_REPLACEMENT;
};

