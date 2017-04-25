#pragma once
#include "Generator.hpp"

class FloatingTowerGenerator : public SOTW::Generator
{
  public:
    FloatingTowerGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    std::pair<Coordinate, Coordinate> generate_tower(MapPtr map);
    void place_staircases(MapPtr map, const std::pair<Coordinate, Coordinate>& tower_boundaries);
};
