#include "TreeSpecies.hpp"

TreeSpecies::TreeSpecies()
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
