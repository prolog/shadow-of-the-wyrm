#pragma once
#include <string>
#include "common.hpp"

// Keys for tile descriptions - used for when a single tile type (e.g.,
// TileType::TILE_TYPE_TREE) can have different descriptions.
class TileDescriptionKeys
{
  public:
    // Used by TileType::TILE_TYPE_TREE:
    static const std::string FLORA_TILE_DESC_ASPEN;
    static const std::string FLORA_TILE_DESC_MAPLE;
    static const std::string FLORA_TILE_DESC_YEW;
    static const std::string FLORA_TILE_DESC_OAK;
    static const std::string FLORA_TILE_DESC_MOUNTAIN_ASH;
    static const std::string FLORA_TILE_DESC_ASH;
    static const std::string FLORA_TILE_DESC_BIRCH;
    static const std::string FLORA_TILE_DESC_CYPRESS;
    static const std::string FLORA_TILE_DESC_WALNUT;

    // Used by TileType::TILE_TYPE_EVERGREEN_TREE:
    static const std::string FLORA_TILE_DESC_FIR;
    static const std::string FLORA_TILE_DESC_CEDAR;
    static const std::string FLORA_TILE_DESC_PINE;
    static const std::string FLORA_TILE_DESC_SPRUCE;

    // Used by TileType::TILE_TYPE_FRUIT_TREE:
    static const std::string FLORA_TILE_DESC_APPLE;
    static const std::string FLORA_TILE_DESC_CHERRY;
    static const std::string FLORA_TILE_DESC_PEACH;
    static const std::string FLORA_TILE_DESC_PLUM;
    static const std::string FLORA_TILE_DESC_PEAR;
    static const std::string FLORA_TILE_DESC_OLIVE;

    // Used by TileType::TILE_TYPE_MAGICAL_TREE
    static const std::string FLORA_TILE_DESC_GOLDEN_APPLE;
    static const std::string FLORA_TILE_DESC_SILVER_APPLE;

    // Used by TileType::TILE_TYPE_WEED:
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
    static const std::string FLORA_TILE_DESC_WEED13;
    static const std::string FLORA_TILE_DESC_WEED14;
    static const std::string FLORA_TILE_DESC_WEED15;
    static const std::string FLORA_TILE_DESC_WEED16;
    static const std::string FLORA_TILE_DESC_WEED17;
    static const std::string FLORA_TILE_DESC_WEED18;
    static const std::string FLORA_TILE_DESC_WEED19;
    static const std::string FLORA_TILE_DESC_WEED20;
    static const std::string FLORA_TILE_DESC_WEED21;
    static const std::string FLORA_TILE_DESC_WEED22;
    static const std::string FLORA_TILE_DESC_WEED23;
    static const std::string FLORA_TILE_DESC_WEED24;
    static const std::string FLORA_TILE_DESC_WEED25;

    static const std::string TILE_DESCRIPTION_DISTANCE_FROM;

  protected:
    TileDescriptionKeys();
};

