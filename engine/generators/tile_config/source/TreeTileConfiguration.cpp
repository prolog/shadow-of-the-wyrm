#include "TreeTileConfiguration.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"

using namespace std;

TreeTileConfiguration::TreeTileConfiguration()
{
  if (tree_species_description_sids.empty())
  {
    initialize_tree_species();
  }
}

void TreeTileConfiguration::initialize_tree_species()
{
  tree_species_description_sids.push_back("FLORA_TILE_DESC_ASPEN");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_MAPLE");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_YEW");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_OAK");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_MOUNTAIN_ASH");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_ASH");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_BIRCH");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_CYPRESS");
  tree_species_description_sids.push_back("FLORA_TILE_DESC_WALNUT");
}

string TreeTileConfiguration::get_random_species() const
{
  return tree_species_description_sids.at(RNG::range(0, tree_species_description_sids.size() - 1));
}

void TreeTileConfiguration::configure(TilePtr tile) const
{
  ItemManager::create_item_with_probability(1, 100, tile->get_items(), ItemIdKeys::ITEM_ID_BRANCH);

  tile->set_additional_property(TileProperties::TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID, get_random_species());
}

