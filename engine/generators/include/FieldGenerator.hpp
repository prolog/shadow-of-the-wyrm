#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class FieldGenerator : public SOTW::Generator
{
  public:
    using SOTW::Generator::generate;

    FieldGenerator(const std::string& map_exit_id);
    virtual ~FieldGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dimensions) override;

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col, const int pct_chance_shield, const bool pct_chance_wild_grain);

    TileGenerator tg;
};
