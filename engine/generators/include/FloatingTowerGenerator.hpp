#pragma once
#include "Generator.hpp"

class FloatingTowerGenerator : public SOTW::Generator
{
  public:
    FloatingTowerGenerator(const std::string& map_exit_id);
    virtual ~FloatingTowerGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;

    virtual std::pair<bool, bool> override_depth_update_defaults() const override;

  protected:
    virtual bool get_permanence_default() const override;

    std::pair<Coordinate, Coordinate> generate_tower(MapPtr map);
    void place_staircases(MapPtr map, const std::pair<Coordinate, Coordinate>& tower_boundaries);
    void generate_wall_structure(MapPtr map, const std::pair<Coordinate, Coordinate>& tower_boundaries);
    std::vector<Coordinate> get_stair_locations(MapPtr map, const Coordinate& centre, const std::pair<Coordinate, Coordinate>& tower_boundaries);
};
