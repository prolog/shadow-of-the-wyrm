#pragma once
#include "TreeTileConfiguration.hpp"

class EvergreenTreeTileConfiguration : public TreeTileConfiguration
{
  public:
    virtual ~EvergreenTreeTileConfiguration() = default;

  protected:
    virtual void initialize_tree_species_details() override;
};

