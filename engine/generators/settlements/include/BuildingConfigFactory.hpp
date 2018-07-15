#pragma once
#include <vector>
#include "ClassIdentifiers.hpp"

class BuildingConfigFactory
{
  public:
    std::vector<ClassIdentifier> create_shop_features() const;
    std::vector<std::string> create_shop_item_ids() const;

    // Returns a random subset of the possible house features.
    std::vector<ClassIdentifier> create_house_features() const;
    std::vector<std::string> create_house_item_ids() const;
};

