#pragma once
#include <boost/shared_ptr.hpp>
#include "Tile.hpp"
#include "ISeason.hpp"

// ITileConfiguration allows configuring tiles in a variety of ways after
// creation - some times may have items generated (rocks on fields,
// branches on trees), while others may have certain, class-specific
// values set (fruit generation information on fruit trees, etc).
class ITileConfiguration
{
  public:
    virtual ~ITileConfiguration() {};
    
    virtual void configure(TilePtr tile) const = 0;
    virtual void update_for_season(TilePtr tile, ISeasonPtr season) const = 0;
};

typedef boost::shared_ptr<ITileConfiguration> ITileConfigurationPtr;