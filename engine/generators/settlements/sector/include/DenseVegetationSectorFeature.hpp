#pragma once
#include <vector>
#include "SectorFeature.hpp"

class DenseVegetationSectorFeature : public SectorFeature
{
  public:
    DenseVegetationSectorFeature(const std::vector<TileType>& new_base_terrain_types, const std::vector<std::string>& new_item_ids, const int new_pct_chance_item);

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    std::vector<TileType> base_terrain_types;
    std::vector<std::string> item_ids;
    int pct_chance_item;
};
