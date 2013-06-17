#pragma once
#include "DefaultTileConfiguration.hpp"

class TreeTileConfiguration : public DefaultTileConfiguration
{
  public:
    virtual void configure(TilePtr tile) const;
};

