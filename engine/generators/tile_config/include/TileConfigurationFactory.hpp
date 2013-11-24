#pragma once
#include <unordered_map>
#include "ITileConfiguration.hpp"

// A class for creating ITileConfigurationPtrs based on the provided
// TileType.
class TileConfigurationFactory
{
  public:
    TileConfigurationFactory();

    ITileConfigurationPtr create_tile_configuration(const TileType tile_type);

  protected:
    void initialize_tile_configuration_map();

    static ITileConfigurationPtr tile_configurations[TILE_TYPE_LAST];
    static bool tile_configurations_initialized;
};
