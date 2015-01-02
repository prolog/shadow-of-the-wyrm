#pragma once
#include "common.hpp"
#include "Tile.hpp"
#include "WorshipSiteTile.hpp"
#include "StaircaseTile.hpp"
#include "AlignmentEnums.hpp"

class TileGenerator
{
  public:
    TileGenerator();
    TileGenerator(const bool generate);

    void set_generate_items(const bool new_generate_items);
    bool get_generate_items() const;

    TilePtr generate(const TileType& tile_type, const TileType& subtile_type = TileType::TILE_TYPE_UNDEFINED);
    WorshipSiteTilePtr generate_worship_site_tile(const AlignmentRange alignment, const std::string& deity_id, const WorshipSiteType worship_site_type);
    StaircaseTilePtr generate_staircase(const StaircaseType& stairs_type);

  protected:
    // Do any necessary configuration of the tile after it has been generated.
    void configure_tile(TilePtr tile);

    bool generate_items;
};
