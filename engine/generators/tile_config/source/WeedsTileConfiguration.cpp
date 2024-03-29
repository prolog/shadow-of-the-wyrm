#include "WeedsTileConfiguration.hpp"
#include "TileDescriptionKeys.hpp"

void WeedsTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids = { TreeSpeciesID::TREE_SPECIES_WEED1, 
                       TreeSpeciesID::TREE_SPECIES_WEED2, 
                       TreeSpeciesID::TREE_SPECIES_WEED3, 
                       TreeSpeciesID::TREE_SPECIES_WEED4, 
                       TreeSpeciesID::TREE_SPECIES_WEED5, 
                       TreeSpeciesID::TREE_SPECIES_WEED6, 
                       TreeSpeciesID::TREE_SPECIES_WEED7, 
                       TreeSpeciesID::TREE_SPECIES_WEED8, 
                       TreeSpeciesID::TREE_SPECIES_WEED9, 
                       TreeSpeciesID::TREE_SPECIES_WEED10, 
                       TreeSpeciesID::TREE_SPECIES_WEED11, 
                       TreeSpeciesID::TREE_SPECIES_WEED12, 
                       TreeSpeciesID::TREE_SPECIES_WEED13, 
                       TreeSpeciesID::TREE_SPECIES_WEED14, 
                       TreeSpeciesID::TREE_SPECIES_WEED15, 
                       TreeSpeciesID::TREE_SPECIES_WEED16, 
                       TreeSpeciesID::TREE_SPECIES_WEED17, 
                       TreeSpeciesID::TREE_SPECIES_WEED18, 
                       TreeSpeciesID::TREE_SPECIES_WEED19, 
                       TreeSpeciesID::TREE_SPECIES_WEED20,
                       TreeSpeciesID::TREE_SPECIES_WEED21,
                       TreeSpeciesID::TREE_SPECIES_WEED22,
                       TreeSpeciesID::TREE_SPECIES_WEED23,
                       TreeSpeciesID::TREE_SPECIES_WEED24,
                       TreeSpeciesID::TREE_SPECIES_WEED25,
  };

  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED1, TileDescriptionKeys::FLORA_TILE_DESC_WEED1));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED2, TileDescriptionKeys::FLORA_TILE_DESC_WEED2));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED3, TileDescriptionKeys::FLORA_TILE_DESC_WEED3));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED4, TileDescriptionKeys::FLORA_TILE_DESC_WEED4));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED5, TileDescriptionKeys::FLORA_TILE_DESC_WEED5));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED6, TileDescriptionKeys::FLORA_TILE_DESC_WEED6));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED7, TileDescriptionKeys::FLORA_TILE_DESC_WEED7));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED8, TileDescriptionKeys::FLORA_TILE_DESC_WEED8));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED9, TileDescriptionKeys::FLORA_TILE_DESC_WEED9));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED10, TileDescriptionKeys::FLORA_TILE_DESC_WEED10));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED11, TileDescriptionKeys::FLORA_TILE_DESC_WEED11));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED12, TileDescriptionKeys::FLORA_TILE_DESC_WEED12));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED13, TileDescriptionKeys::FLORA_TILE_DESC_WEED13));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED14, TileDescriptionKeys::FLORA_TILE_DESC_WEED14));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED15, TileDescriptionKeys::FLORA_TILE_DESC_WEED15));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED16, TileDescriptionKeys::FLORA_TILE_DESC_WEED16));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED17, TileDescriptionKeys::FLORA_TILE_DESC_WEED17));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED18, TileDescriptionKeys::FLORA_TILE_DESC_WEED18));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED19, TileDescriptionKeys::FLORA_TILE_DESC_WEED19));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED20, TileDescriptionKeys::FLORA_TILE_DESC_WEED20));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED21, TileDescriptionKeys::FLORA_TILE_DESC_WEED21));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED22, TileDescriptionKeys::FLORA_TILE_DESC_WEED22));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED23, TileDescriptionKeys::FLORA_TILE_DESC_WEED23));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED24, TileDescriptionKeys::FLORA_TILE_DESC_WEED24));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WEED25, TileDescriptionKeys::FLORA_TILE_DESC_WEED25));
}

