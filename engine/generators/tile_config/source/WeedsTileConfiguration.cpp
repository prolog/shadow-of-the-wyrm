#include "WeedsTileConfiguration.hpp"
#include "TileDescriptionKeys.hpp"

void WeedsTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids.push_back(TREE_SPECIES_WEED1);
  tree_species_ids.push_back(TREE_SPECIES_WEED2);
  tree_species_ids.push_back(TREE_SPECIES_WEED3);
  tree_species_ids.push_back(TREE_SPECIES_WEED4);
  tree_species_ids.push_back(TREE_SPECIES_WEED5);
  tree_species_ids.push_back(TREE_SPECIES_WEED6);
  tree_species_ids.push_back(TREE_SPECIES_WEED7);
  tree_species_ids.push_back(TREE_SPECIES_WEED8);
  tree_species_ids.push_back(TREE_SPECIES_WEED9);
  tree_species_ids.push_back(TREE_SPECIES_WEED10);
  tree_species_ids.push_back(TREE_SPECIES_WEED11);
  tree_species_ids.push_back(TREE_SPECIES_WEED12);

  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED1, TileDescriptionKeys::FLORA_TILE_DESC_WEED1));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED2, TileDescriptionKeys::FLORA_TILE_DESC_WEED2));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED3, TileDescriptionKeys::FLORA_TILE_DESC_WEED3));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED4, TileDescriptionKeys::FLORA_TILE_DESC_WEED4));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED5, TileDescriptionKeys::FLORA_TILE_DESC_WEED5));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED6, TileDescriptionKeys::FLORA_TILE_DESC_WEED6));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED7, TileDescriptionKeys::FLORA_TILE_DESC_WEED7));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED8, TileDescriptionKeys::FLORA_TILE_DESC_WEED8));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED9, TileDescriptionKeys::FLORA_TILE_DESC_WEED9));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED10, TileDescriptionKeys::FLORA_TILE_DESC_WEED10));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED11, TileDescriptionKeys::FLORA_TILE_DESC_WEED11));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_WEED12, TileDescriptionKeys::FLORA_TILE_DESC_WEED12));
}

