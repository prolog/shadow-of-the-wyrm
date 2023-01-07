#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class FieldGenerator : public SOTW::Generator
{
  public:
    FieldGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dimensions) override;

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col, const int pct_chance_shield);

    TileGenerator tg;
};
