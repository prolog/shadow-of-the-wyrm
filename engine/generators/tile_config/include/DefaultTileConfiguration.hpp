#pragma once
#include "ITileConfiguration.hpp"

class DefaultTileConfiguration : public ITileConfiguration
{
  public:
    virtual ~DefaultTileConfiguration() = default;

    virtual void configure(TilePtr tile, const Season season) const override;
    virtual void initialize() override;
};

