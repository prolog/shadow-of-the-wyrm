#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class ScrubGenerator : public SOTW::Generator
{
  public:
    ScrubGenerator(const std::string& map_exit_id);
    virtual ~ScrubGenerator() = default;

    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual TilePtr generate_tile(MapPtr result_map, const int row, const int col, const int pct_chance_shield);

    TileGenerator tg;
};
