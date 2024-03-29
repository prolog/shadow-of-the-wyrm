#include "FruitTreeTileConfiguration.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileDescriptionKeys.hpp"

using namespace std;

FruitTreeTileConfiguration::FruitTreeTileConfiguration()
{
  if (fruit_ids.empty())
  {
    initialize_fruit_ids();
  }
}

FruitTreeTileConfiguration::FruitTreeTileConfiguration(const FruitProductionMap& fpm)
: fruit_ids(fpm)
{
}

void FruitTreeTileConfiguration::initialize_fruit_ids()
{
  // Tasty fruit is only available in the summer months!
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_APPLE, Season::SEASON_SUMMER), "_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_CHERRY, Season::SEASON_SUMMER), "_cherries"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_PEACH, Season::SEASON_SUMMER), "_peach"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_PLUM, Season::SEASON_SUMMER), "_plum"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_PEAR, Season::SEASON_SUMMER), "_pear"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_OLIVE, Season::SEASON_SUMMER), "_olive"));
}

void FruitTreeTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids = { TreeSpeciesID::TREE_SPECIES_APPLE, TreeSpeciesID::TREE_SPECIES_CHERRY, TreeSpeciesID::TREE_SPECIES_PEACH, TreeSpeciesID::TREE_SPECIES_PLUM, TreeSpeciesID::TREE_SPECIES_PEAR, TreeSpeciesID::TREE_SPECIES_OLIVE };

  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_APPLE, TileDescriptionKeys::FLORA_TILE_DESC_APPLE));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_CHERRY, TileDescriptionKeys::FLORA_TILE_DESC_CHERRY));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_PEACH, TileDescriptionKeys::FLORA_TILE_DESC_PEACH));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_PLUM, TileDescriptionKeys::FLORA_TILE_DESC_PLUM));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_PEAR, TileDescriptionKeys::FLORA_TILE_DESC_PEAR));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_OLIVE, TileDescriptionKeys::FLORA_TILE_DESC_OLIVE));
}

void FruitTreeTileConfiguration::configure_additional_features(TilePtr tile, const Season season, const TreeSpeciesID tree_species_id) const
{
  FruitProductionMap::const_iterator f_it = fruit_ids.find(make_pair(tree_species_id, season));

  if (f_it != fruit_ids.end() && tile != nullptr)
  {
    if (RNG::percent_chance(get_pct_chance_fruit()))
    {
      pair<int, int> fruit_range = get_fruit_range();
      int num_pieces = RNG::range(fruit_range.first, fruit_range.second);
      string fruit_id = f_it->second;

      ItemPtr fruit = ItemManager::create_item(fruit_id, static_cast<uint>(num_pieces));

      if (fruit != nullptr)
      {
        tile->get_items()->merge_or_add(fruit, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }
  }
}

std::pair<int, int> FruitTreeTileConfiguration::get_fruit_range() const
{
  return make_pair(1, 6);
}

int FruitTreeTileConfiguration::get_pct_chance_fruit() const
{
  return 60;
}
