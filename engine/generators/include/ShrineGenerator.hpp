#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class ShrineGenerator : public SOTW::Generator
{
  public:
    ShrineGenerator(MapPtr base_map);
    virtual ~ShrineGenerator() = default;

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual MapPtr generate_shrine() = 0;

    void add_dungeon_tiles_to_preset_locations(MapPtr map);
    void place_relic(MapPtr map, const int row, const int col);
    bool get_permanence_default() const override;

    MapPtr base_map;
    TileGenerator tg;
};
