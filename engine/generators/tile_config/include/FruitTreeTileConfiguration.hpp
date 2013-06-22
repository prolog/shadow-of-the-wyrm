#pragma once
#include "TreeTileConfiguration.hpp"

typedef std::map<std::pair<TreeSpeciesID, Season>, std::string> FruitProductionMap;

class FruitTreeTileConfiguration : public TreeTileConfiguration
{
  public:
    FruitTreeTileConfiguration();

  protected:
    virtual void initialize_tree_species_details();
    virtual void initialize_fruit_ids();

    void configure_additional_features(TilePtr tile, const Season season, const TreeSpeciesID tree_species_id) const;

    FruitProductionMap fruit_ids;
};

