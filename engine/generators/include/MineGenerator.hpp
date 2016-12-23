#pragma once
#include "Generator.hpp"
#include "Room.hpp"

class MineGenerator : public SOTW::Generator
{
  public:
    MineGenerator(const std::string& map_exit_id);

    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual MapType get_map_type() const override;

    void generate_room(MapPtr map);

    void generate_wall_segments(MapPtr map);
    void generate_magici_shards(MapPtr map);
    CardinalDirection get_random_direction(const std::vector<CardinalDirection>& cd);
    std::vector<Coordinate> generate_random_feature(const int y, const int x, const CardinalDirection cd);
    void generate_rock_feature(MapPtr map, const std::vector<Coordinate>& feature);

    void generate_traps(MapPtr map);
    void place_staircases(MapPtr map);
    bool get_permanence_default() const override;

    static const int MINE_MIN_TRAPS;
    static const int MINE_MAX_TRAPS_DIVISOR;
    static const int MINE_MAX_SEGMENTS_MULTIPLIER;
};

