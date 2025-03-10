#pragma once
#include "DefaultTileConfiguration.hpp"

class CairnTileConfiguration : public DefaultTileConfiguration
{
  public:
    virtual void configure(TilePtr tile, const Season season) const override;
    virtual ~CairnTileConfiguration() = default;
};
