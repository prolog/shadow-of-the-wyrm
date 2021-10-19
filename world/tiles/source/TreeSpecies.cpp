#include "TreeSpecies.hpp"

TreeSpecies::TreeSpecies()
: species_id(TreeSpeciesID::TREE_SPECIES_CYPRESS), tile_type(TileType::TILE_TYPE_EVERGREEN_TREE)
{
}

TreeSpeciesID TreeSpecies::get_tree_species() const
{
  return species_id;
}

TileType TreeSpecies::get_tile_type() const
{
  return tile_type;
}
