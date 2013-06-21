#include "FruitTreeTileConfiguration.hpp"
#include "TileDescriptionKeys.hpp"

void FruitTreeTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids.push_back(TREE_SPECIES_APPLE);
  tree_species_ids.push_back(TREE_SPECIES_CHERRY);
  tree_species_ids.push_back(TREE_SPECIES_PEACH);
  tree_species_ids.push_back(TREE_SPECIES_PLUM);
  tree_species_ids.push_back(TREE_SPECIES_PEAR);

  tree_species_description_sids.insert(make_pair(TREE_SPECIES_APPLE, TileDescriptionKeys::FLORA_TILE_DESC_APPLE));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_CHERRY, TileDescriptionKeys::FLORA_TILE_DESC_CHERRY));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_PEACH, TileDescriptionKeys::FLORA_TILE_DESC_PEACH));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_PLUM, TileDescriptionKeys::FLORA_TILE_DESC_PLUM));
  tree_species_description_sids.insert(make_pair(TREE_SPECIES_PEAR, TileDescriptionKeys::FLORA_TILE_DESC_PEAR));
}

