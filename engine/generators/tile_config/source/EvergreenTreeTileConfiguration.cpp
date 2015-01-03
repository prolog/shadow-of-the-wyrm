#include "EvergreenTreeTileConfiguration.hpp"
#include "TileDescriptionKeys.hpp"


void EvergreenTreeTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids = {TreeSpeciesID::TREE_SPECIES_FIR, TreeSpeciesID::TREE_SPECIES_CEDAR, TreeSpeciesID::TREE_SPECIES_SPRUCE, TreeSpeciesID::TREE_SPECIES_PINE};

  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_FIR, TileDescriptionKeys::FLORA_TILE_DESC_FIR));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_CEDAR, TileDescriptionKeys::FLORA_TILE_DESC_CEDAR));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_SPRUCE, TileDescriptionKeys::FLORA_TILE_DESC_SPRUCE));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_PINE, TileDescriptionKeys::FLORA_TILE_DESC_PINE));
}
