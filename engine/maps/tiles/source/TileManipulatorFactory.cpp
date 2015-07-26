#include "TileManipulatorFactory.hpp"
#include "DefaultTileManipulator.hpp"
#include "GraveTileManipulator.hpp"

ITileManipulatorPtr TileManipulatorFactory::create_tile_manipulator(TilePtr tile)
{
  ITileManipulatorPtr tm = std::make_shared<DefaultTileManipulator>();

  if (tile != nullptr)
  {
    TileType tile_type = tile->get_tile_type();

    // Graves are a special case for digging - can lead to buried treasure/
    // deity hatred.
    if (tile_type == TileType::TILE_TYPE_GRAVE || tile_type == TileType::TILE_TYPE_BARROW)
    {
      tm = std::make_shared<GraveTileManipulator>();
    }
  }

  return tm;
}
