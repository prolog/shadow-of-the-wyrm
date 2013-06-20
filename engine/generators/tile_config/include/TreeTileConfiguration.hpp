#pragma once
#include <boost/unordered_map.hpp>
#include "DefaultTileConfiguration.hpp"
#include "TileIDs.hpp"

class TreeTileConfiguration : public DefaultTileConfiguration
{
  public:
    TreeTileConfiguration();

    virtual void configure(TilePtr tile) const;

  protected:
    virtual TreeSpeciesID get_random_species() const;
    virtual void configure_additional_features(TilePtr tile, const TreeSpeciesID tree_species_id) const;

    virtual void initialize_tree_species_details();

    std::vector<TreeSpeciesID> tree_species_ids;
    boost::unordered_map<TreeSpeciesID, std::string> tree_species_description_sids;
};
