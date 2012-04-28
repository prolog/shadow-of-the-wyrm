#pragma once
#include "BaseSettlementGenerator.hpp"
#include "Room.hpp"

// A scattered settlement is one where the buildings are randomly placed,
// and have a certain minimum distance between them.
class ScatteredSettlementGenerator : public BaseSettlementGenerator
{
  public:
    ScatteredSettlementGenerator(MapPtr new_base_map);
    ScatteredSettlementGenerator(MapPtr new_base_map, const int growth_rate);

    MapPtr generate(const Dimensions& dim);
    MapPtr generate();

  protected:
    void initialize();
    bool can_building_be_placed(const int row, const int col, const int height, const int width);
    void generate_scattered_settlement(MapPtr map);

    int min_distance_between_buildings;
    std::vector<Room> current_buildings;
};
