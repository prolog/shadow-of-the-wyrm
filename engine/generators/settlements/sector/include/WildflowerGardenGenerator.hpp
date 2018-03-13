#pragma once
#include "SectorFeature.hpp"

class WildflowerGardenGenerator : public SectorFeature
{
  public:
    WildflowerGardenGenerator();

  protected:
    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    void initialize_generator();
    void populate_wildflower_ids();
    
    void seed_flowers(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    
    std::map<int, std::string> wildflower_item_ids;
    int wildflower_rand_min;
    int wildflower_rand_max;
};
