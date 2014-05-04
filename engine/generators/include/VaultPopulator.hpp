#pragma once
#include "Map.hpp"

// Populates a vault with creatures and items.
class VaultPopulator
{
  public:
    virtual void populate_vault(MapPtr map, const TileType tile_type, const Coordinate& vault_topleft, const Coordinate& vault_bottomright);

  protected:
    virtual void populate_vault_creatures(MapPtr map, const TileType tile_type, const std::set<Coordinate>& vault_coords);
    virtual void populate_vault_items(MapPtr map, const std::set<Coordinate>& vault_coords);

  private:
    static const int MIN_OUT_OF_DEPTH_INCR;
    static const int MAX_OUT_OF_DEPTH_INCR;
};

