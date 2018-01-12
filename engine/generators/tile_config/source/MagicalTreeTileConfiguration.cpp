#include "MagicalTreeTileConfiguration.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileDescriptionKeys.hpp"

using namespace std;

MagicalTreeTileConfiguration::MagicalTreeTileConfiguration()
: FruitTreeTileConfiguration({})
{
  initialize_fruit_ids();
}

void MagicalTreeTileConfiguration::initialize_fruit_ids()
{
  // Magical fruit appears year-round.
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_GOLDEN_APPLE, Season::SEASON_WINTER), "_golden_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_GOLDEN_APPLE, Season::SEASON_SPRING), "_golden_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_GOLDEN_APPLE, Season::SEASON_SUMMER), "_golden_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_GOLDEN_APPLE, Season::SEASON_AUTUMN), "_golden_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_SILVER_APPLE, Season::SEASON_WINTER), "_silver_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_SILVER_APPLE, Season::SEASON_SPRING), "_silver_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_SILVER_APPLE, Season::SEASON_SUMMER), "_silver_apple"));
  fruit_ids.insert(make_pair(make_pair(TreeSpeciesID::TREE_SPECIES_SILVER_APPLE, Season::SEASON_AUTUMN), "_silver_apple"));

}

void MagicalTreeTileConfiguration::initialize_tree_species_details()
{
  tree_species_ids = {TreeSpeciesID::TREE_SPECIES_GOLDEN_APPLE, TreeSpeciesID::TREE_SPECIES_SILVER_APPLE};

  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_GOLDEN_APPLE, TileDescriptionKeys::FLORA_TILE_DESC_GOLDEN_APPLE));
  tree_species_description_sids.insert(make_pair(TreeSpeciesID::TREE_SPECIES_SILVER_APPLE, TileDescriptionKeys::FLORA_TILE_DESC_SILVER_APPLE));
}

pair<int, int> MagicalTreeTileConfiguration::get_fruit_range() const
{
  return make_pair(1, 1);
}
