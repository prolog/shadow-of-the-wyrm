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
    void generate_ew_wall_segments(MapPtr map);
    void generate_ns_wall_segments(MapPtr map);
    CardinalDirection get_random_direction(const std::vector<CardinalDirection>& cd);

    void generate_traps(MapPtr map);
    void place_staircases(MapPtr map);
    bool get_permanence_default() const override;

    static const int MINE_MIN_TRAPS;
    static const int MINE_MAX_TRAPS;

    static const int MIN_EW_SEGMENTS;
    static const int MIN_NS_SEGMENTS;
    static const int MAX_EW_DIVISOR;
    static const int MAX_NS_DIVISOR;
    static const int MAX_SEGMENT_ATTEMPTS;
    static const int MIN_SEGMENT_WIDTH;
    static const int MAX_SEGMENT_WIDTH;
    static const int MIN_SEGMENT_HEIGHT;
    static const int MAX_SEGMENT_HEIGHT;
};

