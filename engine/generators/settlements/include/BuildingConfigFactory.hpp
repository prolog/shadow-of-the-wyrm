#pragma once
#include <map>
#include <string>
#include <vector>
#include "ClassIdentifiers.hpp"

class BuildingConfigFactory
{
  public:
    BuildingConfigFactory();

    std::vector<ClassIdentifier> create_shop_features() const;
    std::vector<std::string> create_shop_item_ids() const;

    // Returns a random subset of the possible house features.
    std::vector<ClassIdentifier> create_house_or_workshop_features(const int pct_chance_workshop) const;
    std::vector<std::string> create_item_ids(const std::vector<ClassIdentifier>& features_present) const;
    std::vector<std::string> create_creature_ids(const std::vector<ClassIdentifier>& features_present) const;
    std::vector<ClassIdentifier> create_house_features() const;
    std::vector<ClassIdentifier> create_workshop_features() const;

  protected:
    void initialize_feature_items();
    void initialize_feature_creatures();

    // Each feature has a list of items with associated probabilities.
    static std::map<ClassIdentifier, std::vector<std::pair<std::string, int>>> feature_items;
    static std::map<ClassIdentifier, std::vector<std::pair<std::string, int>>> feature_creatures;
};

