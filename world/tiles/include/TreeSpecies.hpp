#pragma once
#include "TileIDs.hpp"
#include "tiles.hpp"

// Wraps a tree species and a tile type.  E.g., maple is a tree, cherry
// is a fruit tree, fir is an evergreen, weed1 is a weed, etc.
class TreeSpecies
{
  public:
    TreeSpeciesID get_tree_species() const;
    TileType get_tile_type() const;

  protected:
    TreeSpecies();
    friend class TreeSpeciesFactory;

    TreeSpeciesID species_id;
    TileType tile_type;
};

