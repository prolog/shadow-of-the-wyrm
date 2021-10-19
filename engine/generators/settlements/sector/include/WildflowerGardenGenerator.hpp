#pragma once
#include "GardenSectorFeature.hpp"

class WildflowerGardenGenerator : public GardenSectorFeature
{
  public:
    WildflowerGardenGenerator(const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);
    std::pair<std::pair<int, int>, std::map<int, std::string>> get_wildflower_details() const;

    virtual void plant_flower(TilePtr tile);

  protected:
    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    void initialize_generator();
    void populate_wildflower_ids();
    
    void seed_flowers(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);
    
    std::map<int, std::string> wildflower_item_ids;
    int wildflower_rand_min;
    int wildflower_rand_max;
};
