#pragma once
#include "DefaultTileConfiguration.hpp"

class WheatTileConfiguration : public DefaultTileConfiguration
{
  public:
    virtual void configure(TilePtr tile, const Season season) const override;
    virtual ~WheatTileConfiguration() = default;
};
