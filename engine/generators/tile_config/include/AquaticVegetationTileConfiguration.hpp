#pragma once
#include "DefaultTileConfiguration.hpp"

class AquaticVegetationTileConfiguration : public DefaultTileConfiguration
{
  public:
    virtual void configure(TilePtr tile, const Season season) const override;
    virtual ~AquaticVegetationTileConfiguration() = default;
};

