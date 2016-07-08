#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class CrossShrineGenerator : public SOTW::Generator
{
  public:
    CrossShrineGenerator(MapPtr base_map);

    virtual MapPtr generate(const Dimensions& dim) override;
    virtual MapPtr generate();

  protected:
    void generate_building(MapPtr map, const int start_row, const int start_col, const int mid_row, const int shrine_height, const int shrine_width);
    void generate_entrances(MapPtr map, const int start_row, const int shrine_height, const int mid_row);

    MapPtr base_map;
    TileGenerator tg;
};

