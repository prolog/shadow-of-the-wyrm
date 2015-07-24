#include "TileManipulatorFactory.hpp"
#include "DefaultTileManipulator.hpp"

ITileManipulatorPtr TileManipulatorFactory::create_tile_manipulator(TilePtr tile)
{
  ITileManipulatorPtr tm = std::make_shared<DefaultTileManipulator>();

  if (tile != nullptr)
  {
    TileType tile_type = tile->get_tile_type();

    // ...
  }

  return tm;
}
