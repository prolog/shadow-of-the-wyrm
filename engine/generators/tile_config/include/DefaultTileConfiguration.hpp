#pragma once
#include "ITileConfiguration.hpp"

class DefaultTileConfiguration : public ITileConfiguration
{
  public:
    virtual void configure(TilePtr tile) const;
};

