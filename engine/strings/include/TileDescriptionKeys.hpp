#pragma once
#include <string>

// Keys for tile descriptions - used for when a single tile type (e.g.,
// TILE_TYPE_TREE) can have different descriptions.
class TileDescriptionKeys
{
  public:
    // Used by TILE_TYPE_TREE:
    static const std::string FLORA_TILE_DESC_ASPEN;
    static const std::string FLORA_TILE_DESC_MAPLE;
    static const std::string FLORA_TILE_DESC_YEW;
    static const std::string FLORA_TILE_DESC_OAK;
    static const std::string FLORA_TILE_DESC_MOUNTAIN_ASH;
    static const std::string FLORA_TILE_DESC_ASH;
    static const std::string FLORA_TILE_DESC_BIRCH;
    static const std::string FLORA_TILE_DESC_CYPRESS;
    static const std::string FLORA_TILE_DESC_WALNUT;
        
  protected:
    TileDescriptionKeys();
};

