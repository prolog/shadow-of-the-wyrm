#pragma once
#include "DefaultTileConfiguration.hpp"

class TreeTileConfiguration : public DefaultTileConfiguration
{
  public:
    TreeTileConfiguration();

    virtual void configure(TilePtr tile) const;

  protected:
    virtual std::string get_random_species() const;

    virtual void initialize_tree_species();
    std::vector<std::string> tree_species_description_sids;
};

