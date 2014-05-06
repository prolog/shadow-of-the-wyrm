#pragma once
#include "Map.hpp"
#include "RarityTypes.hpp"

// Populates a vault with creatures and items.
class VaultPopulator
{
  public:
    virtual void populate_vault(MapPtr map, const TileType tile_type, const Coordinate& vault_topleft, const Coordinate& vault_bottomright);

  protected:
    virtual void populate_vault_creatures(MapPtr map, const TileType tile_type, const std::vector<Coordinate>& vault_coords, const int danger_level, const Rarity rarity);
    virtual void populate_vault_items(MapPtr map, const std::vector<Coordinate>& vault_coords, const int danger_level, const Rarity rarity);

  private:
    static const int MIN_OUT_OF_DEPTH_INCR;
    static const int MAX_OUT_OF_DEPTH_INCR;
};

