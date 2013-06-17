#pragma once
#include "ITileConfiguration.hpp"

class DefaultTileConfiguration : public ITileConfiguration
{
  public:
    virtual void configure(TilePtr tile) const;
    virtual void update_for_season(TilePtr tile, ISeasonPtr season) const;
};

