#pragma once
#include "Tile.hpp"

// Additional utilities for Tiles, TileTypes, etc., that don't belong on Tile
// itself.
class TileUtils
{
  public:
    static TileType get_opposite_tile_type(const TileType tt);

    // Grave features need to set the underlying dig chances on the tile
    // to that of a grave tile (so that plundering the feature has the
    // same chance as e.g. plundering a grave tile).  This convenience 
    // function does that.
    static void set_grave_feature(TilePtr tile, FeaturePtr grave_feature);

  protected:
    TileUtils();
    ~TileUtils();
};

