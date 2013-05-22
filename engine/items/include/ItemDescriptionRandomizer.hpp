#pragma once
#include <vector>
#include <utility>
#include "Item.hpp"

class ItemDescriptionRandomizer
{
  public:
    ItemDescriptionRandomizer(const std::vector<ItemType>& randomize_types);

    // Randomize the unidentified description and unidentified usage
    // description SIDs in the given ItemMap&.
    void randomize(ItemMap& items);

  protected:
    std::vector<ItemType> types_to_randomize;    
};

