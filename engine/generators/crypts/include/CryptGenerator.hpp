#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class CryptGenerator : public SL::Generator
{
  public:
    CryptGenerator(const std::string& new_map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual MapType get_map_type() const override;
    virtual bool get_permanence_default() const override;

    // Creates the central crypt with the up-staircase.  The two coordinates refer
    // to the top-left and lower-right bounds, and the direction is the side of
    // the crypt on which the up-staircase has been placed.
    std::tuple<Coordinate, Coordinate, Coordinate> generate_central_crypt(MapPtr map);

    // Generate the random features of the crypt
    void generate_crypt_features(const std::tuple<Coordinate, Coordinate, Coordinate>& loc_details, MapPtr map);

    // Generate skeletons around the perimeter
    void generate_perimeter_skeletons(const std::tuple<Coordinate, Coordinate, Coordinate>& loc_details, MapPtr map);
    // Generate the staircase to the surface.
    Coordinate generate_up_staircase(const Coordinate& top_left, const Coordinate& bottom_right, MapPtr map);

    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);

    TileGenerator tg;
};
