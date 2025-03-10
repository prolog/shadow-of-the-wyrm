#include "TreeTileConfiguration.hpp"
#include "Conversion.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "RNG.hpp"
#include "TileDescriptionKeys.hpp"

using namespace std;

void TreeTileConfiguration::initialize()
{
  if (tree_species_ids.empty())
  {
    clear_tree_species_details();
    initialize_tree_species_details();
  }
}

void TreeTileConfiguration::clear_tree_species_details()
{
  tree_species_ids.clear();
  tree_species_description_sids.clear();
}

void TreeTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids = { TreeSpeciesID::TREE_SPECIES_ASPEN, TreeSpeciesID::TREE_SPECIES_MAPLE, TreeSpeciesID::TREE_SPECIES_YEW, TreeSpeciesID::TREE_SPECIES_OAK, TreeSpeciesID::TREE_SPECIES_MOUNTAIN_ASH, TreeSpeciesID::TREE_SPECIES_ASH, TreeSpeciesID::TREE_SPECIES_BIRCH, TreeSpeciesID::TREE_SPECIES_WALNUT };

  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_ASPEN, TileDescriptionKeys::FLORA_TILE_DESC_ASPEN));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_MAPLE, TileDescriptionKeys::FLORA_TILE_DESC_MAPLE));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_YEW, TileDescriptionKeys::FLORA_TILE_DESC_YEW));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_OAK, TileDescriptionKeys::FLORA_TILE_DESC_OAK));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_MOUNTAIN_ASH, TileDescriptionKeys::FLORA_TILE_DESC_MOUNTAIN_ASH));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_ASH, TileDescriptionKeys::FLORA_TILE_DESC_ASH));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_BIRCH, TileDescriptionKeys::FLORA_TILE_DESC_BIRCH));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_WALNUT, TileDescriptionKeys::FLORA_TILE_DESC_WALNUT));
}

TreeSpeciesID TreeTileConfiguration::get_species(TilePtr tile) const
{
  TreeSpeciesID species_id = tree_species_ids.at(RNG::range(0, tree_species_ids.size() - 1));

  if (tile != nullptr)
  {
    string species_tile_id = tile->get_additional_property(ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID);

    if (!species_tile_id.empty())
    {
      species_id = static_cast<TreeSpeciesID>(String::to_int(species_tile_id));
    }
  }

  return species_id;
}

void TreeTileConfiguration::configure(TilePtr tile, const Season season) const
{
  if (tile != nullptr)
  {
    IInventoryPtr tile_inv = tile->get_items();
    bool branch_created = ItemManager::create_item_with_probability(1, 100, tile_inv, ItemIdKeys::ITEM_ID_BRANCH);

    if (!branch_created)
    {
      ItemManager::create_item_with_probability(1, 400, tile_inv, ItemIdKeys::ITEM_ID_BOUGH);
    }

    if (RNG::x_in_y_chance(1, 300))
    {
      string fungus_id = ItemIdKeys::ITEM_IDS_FUNGUS.at(RNG::range(0, ItemIdKeys::ITEM_IDS_FUNGUS.size() - 1));
      ItemManager::create_item_with_probability(1, 1, tile_inv, fungus_id);
    }

    // If a species ID has already been provided, use that; otherwise, generate
    // a random allowable species.
    TreeSpeciesID species_id = get_species(tile);

    auto s_it = tree_species_description_sids.find(species_id);

    if (s_it != tree_species_description_sids.end())
    {
      tile->set_additional_property(TileProperties::TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID, s_it->second);
    }

    configure_additional_features(tile, season, species_id);
  }
}

// Configure any additional features of the tree - this will typically be
// overridden by any subclasses.
void TreeTileConfiguration::configure_additional_features(TilePtr /*tile*/, const Season /*season*/, const TreeSpeciesID /*tree_species_id*/) const
{
}
