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

    // Used by TILE_TYPE_EVERGREEN_TREE:
    static const std::string FLORA_TILE_DESC_FIR;
    static const std::string FLORA_TILE_DESC_CEDAR;
    static const std::string FLORA_TILE_DESC_PINE;
    static const std::string FLORA_TILE_DESC_SPRUCE;

    // Used by TILE_TYPE_FRUIT_TREE:
    static const std::string FLORA_TILE_DESC_APPLE;
    static const std::string FLORA_TILE_DESC_CHERRY;
    static const std::string FLORA_TILE_DESC_PEACH;
    static const std::string FLORA_TILE_DESC_PLUM;
    static const std::string FLORA_TILE_DESC_PEAR;

    // Used by TILE_TYPE_WEED:
    static const std::string FLORA_TILE_DESC_WEED1;
    static const std::string FLORA_TILE_DESC_WEED2;
    static const std::string FLORA_TILE_DESC_WEED3;
    static const std::string FLORA_TILE_DESC_WEED4;
    static const std::string FLORA_TILE_DESC_WEED5;
    static const std::string FLORA_TILE_DESC_WEED6;
    static const std::string FLORA_TILE_DESC_WEED7;
    static const std::string FLORA_TILE_DESC_WEED8;
    static const std::string FLORA_TILE_DESC_WEED9;
    static const std::string FLORA_TILE_DESC_WEED10;
    static const std::string FLORA_TILE_DESC_WEED11;
    static const std::string FLORA_TILE_DESC_WEED12;
        
  protected:
    TileDescriptionKeys();
};

