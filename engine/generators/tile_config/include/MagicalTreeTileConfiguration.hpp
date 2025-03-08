#pragma once
#include "FruitTreeTileConfiguration.hpp"

using FruitProductionMap = std::map<std::pair<TreeSpeciesID, Season>, std::string>;

class MagicalTreeTileConfiguration : public FruitTreeTileConfiguration
{
  public:
    MagicalTreeTileConfiguration();
    virtual ~MagicalTreeTileConfiguration() = default;

  protected:
    virtual void initialize_tree_species_details() override;
    virtual void initialize_fruit_ids() override;
    virtual std::pair<int, int> get_fruit_range() const override;
    virtual int get_pct_chance_fruit() const;
};

