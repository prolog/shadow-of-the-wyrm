#pragma once
#include "common.hpp"
#include "Tile.hpp"
#include "WorshipSiteTile.hpp"
#include "StaircaseTile.hpp"
#include "AlignmentEnums.hpp"

class TileGenerator
{
  public:
    static TilePtr generate(const TileType& tile_type, const TileType& subtile_type = TILE_TYPE_UNDEFINED, const bool generate_random_items = true);
    static WorshipSiteTilePtr generate_worship_site_tile(const AlignmentRange alignment, const std::string& deity_id, const WorshipSiteType worship_site_type);
    static StaircaseTilePtr generate_staircase(const StaircaseType& stairs_type);

  protected:
    // Do any necessary configuration of the tile after it has been generated.
    static void configure_tile(TilePtr tile);
};
