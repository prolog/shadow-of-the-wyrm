#pragma once
#include "TreeTileConfiguration.hpp"

class WeedsTileConfiguration : public TreeTileConfiguration
{
  public:
    virtual ~WeedsTileConfiguration() = default;

  protected:
    virtual void initialize_tree_species_details() override;
};

