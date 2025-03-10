#pragma once
#include <unordered_map>
#include "DefaultTileConfiguration.hpp"
#include "TileIDs.hpp"

class TreeTileConfiguration : public DefaultTileConfiguration
{
  public:
    virtual ~TreeTileConfiguration() = default;

    virtual void configure(TilePtr tile, const Season season) const override;
    virtual void initialize() override;

  protected:
    virtual TreeSpeciesID get_species(TilePtr tile) const;
    virtual void configure_additional_features(TilePtr tile, const Season season, const TreeSpeciesID tree_species_id) const;

    void clear_tree_species_details();
    virtual void initialize_tree_species_details();

    std::vector<TreeSpeciesID> tree_species_ids;
    std::unordered_map<TreeSpeciesID, std::string> tree_species_description_sids;
};
