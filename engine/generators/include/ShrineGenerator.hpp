#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class ShrineGenerator : public SOTW::Generator
{
  public:
    ShrineGenerator(MapPtr base_map);

    virtual MapPtr generate() = 0;
    virtual MapPtr generate(const Dimensions& dim) = 0;

  protected:
    void add_dungeon_tiles_to_preset_locations(MapPtr map);
    void place_relic(MapPtr map, const int row, const int col);

    MapPtr base_map;
    TileGenerator tg;
};
