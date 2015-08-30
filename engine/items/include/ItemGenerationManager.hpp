#pragma once
#include <vector>
#include "ActionManager.hpp"
#include "GenerationValues.hpp"

using ItemGenerationPair = std::pair<std::string, std::pair<std::shared_ptr<Item>, GenerationValues>>;
using ItemGenerationVec = std::vector<ItemGenerationPair>;

class ItemGenerationManager
{
  public:
    ItemGenerationManager();

    ItemGenerationVec generate_item_generation_vec(const int min_danger_level, const int max_danger_level, const Rarity rarity);

    // Generate an item from the given creature generation map, calling out to the ItemManager to do the actual creation.
    std::shared_ptr<Item> generate_item(ActionManager& am, ItemGenerationVec& item_generation_vec, const int enchant_points);
    
  protected:
    bool does_item_match_generation_criteria(const GenerationValues& gv, const int min_danger_level, const int max_danger_level, const Rarity rarity);
};
