#pragma once
#include "TreeTileConfiguration.hpp"

using FruitProductionMap = std::map<std::pair<TreeSpeciesID, Season>, std::string>;

class FruitTreeTileConfiguration : public TreeTileConfiguration
{
  public:
    FruitTreeTileConfiguration();
    FruitTreeTileConfiguration(const FruitProductionMap& preset_map);

  protected:
    virtual void initialize_tree_species_details() override;
    virtual void initialize_fruit_ids();
    virtual std::pair<int, int> get_fruit_range() const;
    virtual int get_pct_chance_fruit() const;

    void configure_additional_features(TilePtr tile, const Season season, const TreeSpeciesID tree_species_id) const override;

    FruitProductionMap fruit_ids;
};

