#pragma once
#include "TreeSpecies.hpp"

class TreeSpeciesFactory
{
  public:
    TreeSpecies create_tree_species(const TreeSpeciesID species_id);
};
