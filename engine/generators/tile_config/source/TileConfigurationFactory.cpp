#include <boost/make_shared.hpp>
#include "CairnTileConfiguration.hpp"
#include "FieldTileConfiguration.hpp"
#include "TreeTileConfiguration.hpp"
#include "TileConfigurationFactory.hpp"

ITileConfigurationPtr TileConfigurationFactory::tile_configurations[TILE_TYPE_LAST];
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
  BOOST_STATIC_ASSERT(TILE_TYPE_LAST == 40);

  ITileConfigurationPtr field_config = boost::make_shared<FieldTileConfiguration>(); 
  tile_configurations[TILE_TYPE_FIELD] = field_config;

  ITileConfigurationPtr cairn_config = boost::make_shared<CairnTileConfiguration>();
  tile_configurations[TILE_TYPE_CAIRN] = cairn_config;

  ITileConfigurationPtr tree_config = boost::make_shared<TreeTileConfiguration>();
  tile_configurations[TILE_TYPE_TREE] = tree_config;
  tile_configurations[TILE_TYPE_EVERGREEN_TREE] = tree_config;
}

// Create the tile configuration shared pointer for the given tile type.
// If no configuration pointer exists in the map, create a default
// configuration, and insert it into the map for next time for faster
// lookup.
ITileConfigurationPtr TileConfigurationFactory::create_tile_configuration(const TileType tile_type)
{
  ITileConfigurationPtr tile_config;

  tile_config = tile_configurations[tile_type];

  if (!tile_config)
  {
    tile_config = boost::make_shared<DefaultTileConfiguration>();
    tile_configurations[tile_type] = tile_config;
  }

  return tile_config;
}

