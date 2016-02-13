#include "CairnTileConfiguration.hpp"
#include "EvergreenTreeTileConfiguration.hpp"
#include "FieldTileConfiguration.hpp"
#include "FruitTreeTileConfiguration.hpp"
#include "TreeTileConfiguration.hpp"
#include "TileConfigurationFactory.hpp"
#include "WeedsTileConfiguration.hpp"

ITileConfigurationPtr TileConfigurationFactory::tile_configurations[static_cast<int>(TileType::TILE_TYPE_LAST)];
bool TileConfigurationFactory::tile_configurations_initialized = false;

TileConfigurationFactory::TileConfigurationFactory()
{
  if (tile_configurations_initialized == false)
  {
    initialize_tile_configuration_map();
    tile_configurations_initialized = true;
  }
}

// Create any special tile configuration classes for particular tile
// types.
void TileConfigurationFactory::initialize_tile_configuration_map()
{
  static_assert(TileType::TILE_TYPE_LAST == TileType(49), "Unexpected TileType::TILE_TYPE_LAST value.");

  ITileConfigurationPtr field_config = std::make_shared<FieldTileConfiguration>(); 
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_FIELD)] = field_config;

  ITileConfigurationPtr rocky_earth_config = std::make_shared<CairnTileConfiguration>();
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_ROCKY_EARTH)] = rocky_earth_config;

  ITileConfigurationPtr cairn_config = std::make_shared<CairnTileConfiguration>();
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_CAIRN)] = cairn_config;

  ITileConfigurationPtr weeds_config = std::make_shared<WeedsTileConfiguration>();
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_WEEDS)] = weeds_config;

  ITileConfigurationPtr tree_config = std::make_shared<TreeTileConfiguration>();
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_TREE)] = tree_config;

  ITileConfigurationPtr evergreen_tree_config = std::make_shared<EvergreenTreeTileConfiguration>();
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_EVERGREEN_TREE)] = evergreen_tree_config;

  ITileConfigurationPtr fruit_tree_config = std::make_shared<FruitTreeTileConfiguration>();
  tile_configurations[static_cast<int>(TileType::TILE_TYPE_FRUIT_TREE)] = fruit_tree_config;

  // Now that the configurations have been created, loop over them
  // and initialize them.
  for (int t = static_cast<int>(TileType::TILE_TYPE_FIRST); t < static_cast<int>(TileType::TILE_TYPE_LAST); t++)
  {
    ITileConfigurationPtr tile_config = tile_configurations[t];
    
    if (tile_config)
    {
      tile_config->initialize();
    }
  }
}

// Create the tile configuration shared pointer for the given tile type.
// If no configuration pointer exists in the map, create a default
// configuration, and insert it into the map for next time for faster
// lookup.
ITileConfigurationPtr TileConfigurationFactory::create_tile_configuration(const TileType tile_type)
{
  ITileConfigurationPtr tile_config;

  tile_config = tile_configurations[static_cast<int>(tile_type)];

  if (!tile_config)
  {
    tile_config = std::make_shared<DefaultTileConfiguration>();
    tile_config->initialize();
    tile_configurations[static_cast<int>(tile_type)] = tile_config;
  }

  return tile_config;
}

