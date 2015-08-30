#pragma once
#include <memory>
#include "CalendarTypes.hpp"
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
    
    virtual void configure(TilePtr tile, const Season season) const = 0;

    // Initializes any members of the TileConfiguration.
    virtual void initialize() = 0;
};

using ITileConfigurationPtr = std::shared_ptr<ITileConfiguration>;