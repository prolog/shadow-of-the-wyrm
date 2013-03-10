#pragma once
#include <map>
#include "ActionManager.hpp"
#include "GenerationValues.hpp"

typedef std::map<std::string, std::pair<boost::shared_ptr<Item>, GenerationValues> > ItemGenerationMap;

class ItemGenerationManager
{
  public:
    ItemGenerationManager();

    ItemGenerationMap generate_item_generation_map(const int danger_level, const Rarity rarity);

    // Generate an item from the given creature generation map, calling out to the ItemManager to do the actual creation.
    boost::shared_ptr<Item> generate_item(ActionManager& am, ItemGenerationMap& item_generation_map);
    
  protected:
    bool does_item_match_generation_criteria(const GenerationValues& gv, const int danger_level, const Rarity rarity);
};
