#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class RectangularShrineGenerator : public SOTW::Generator
{
  public:
    RectangularShrineGenerator(MapPtr base_map);

    virtual MapPtr generate(const Dimensions& dim) override;
    virtual MapPtr generate();

  protected:
    void create_entrances(MapPtr map, const int start_row, const int start_col, const int height, const int width, const int mid_row, const int mid_col);
    void place_pillars_and_statues(MapPtr map, const int start_row, const int start_col, const int height, const int width, const int mid_row, const int mid_col);
    void generate_pillar_or_statue(MapPtr map, const std::vector<Coordinate>& coordinates, const bool generate_pillar);
    void place_relic(MapPtr map, const int mid_row, const int mid_col);

    MapPtr base_map;
    TileGenerator tg;
};

