#pragma once
#include "DefaultTileConfiguration.hpp"

class FieldTileConfiguration : public DefaultTileConfiguration
{
  public:
    virtual void configure(TilePtr tile, const Season season) const override;
};

