#pragma once
#include "TreeTileConfiguration.hpp"

class WeedsTileConfiguration : public TreeTileConfiguration
{
  protected:
    virtual void initialize_tree_species_details() override;
};

