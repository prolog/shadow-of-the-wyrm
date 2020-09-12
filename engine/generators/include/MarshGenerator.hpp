#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class MarshGenerator : public SOTW::Generator
{
  public:
    MarshGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);
    virtual void    add_random_trees_bushes_weeds_and_reeds(MapPtr current_map);
    virtual void    add_bog_iron(MapPtr current_map);
    TileGenerator tg;

    const int XY_CHANCE_BERRIES_X;
    static const int XY_CHANCE_BERRIES_Y;
    static const int PCT_CHANCE_BOG_IRON;
};
