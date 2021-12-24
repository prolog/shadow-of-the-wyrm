#pragma once
#include <vector>
#include "ActionManager.hpp"
#include "GenerationValues.hpp"
#include "ItemGenerationConstraints.hpp"

using ItemGenerationPair = std::pair<std::string, std::pair<std::shared_ptr<Item>, GenerationValues>>;
using ItemGenerationMap = std::map<ItemType, std::map<Rarity, std::vector<ItemGenerationPair>>>;

class ItemGenerationManager
{
  public:
    ItemGenerationManager();

    // Generates an item type that can be used for generating a new item within
    // a given danger/rarity range.
    ItemType generate_item_type() const;
    ItemGenerationMap generate_item_generation_map(const ItemGenerationConstraints& igc);
    std::vector<std::string> get_item_ids(const ItemGenerationMap& igm);

    // Generate an item from the given creature generation map, calling out to the ItemManager to do the actual creation.
    std::shared_ptr<Item> generate_item(ActionManager& am, ItemGenerationMap& item_generation_map, const Rarity rarity, const std::vector<ItemType>& item_type_restrictions, const int enchant_points);
    
  protected:
    friend class SW_Engine_Items_ItemGenerationManager;

    void initialize_spellbook_squelch_pct();

    ItemType generate_item_type_by_val(const int rng_val) const;

    bool does_item_match_generation_criteria(const GenerationValues& gv, const int min_danger_level, const int max_danger_level, const Rarity rarity, const std::vector<ItemType>& item_type_restrictions, const int min_value);
    Rarity get_item_rarity(const Rarity generation_rarity) const;

    int spellbook_squelch_pct;
    std::map<Rarity, std::vector<std::pair<Rarity, int>>> rarity_chances;
};
