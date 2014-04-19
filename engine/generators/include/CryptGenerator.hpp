#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class CryptGenerator : public SL::Generator
{
  public:
    CryptGenerator(const std::string& new_map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual bool get_permanence_default() const override;

    // Creates the central crypt with the up-staircase.  The two coordinates refer
    // to the top-left and lower-right bounds, and the direction is the side of
    // the crypt on which the up-staircase has been placed.
    std::tuple<CardinalDirection, Coordinate, Coordinate> generate_central_crypt(MapPtr map);

    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);

    TileGenerator tg;
};
