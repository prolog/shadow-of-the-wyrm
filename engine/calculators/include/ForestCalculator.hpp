#pragma once
#include <map>
#include "common.hpp"
#include "tiles.hpp"

// A class used to determine the probabilities of certain forest features
// when generating a general thing of that type.
//
// For example, when generating a tree, what is the probability that it is
// evergreen or deciduous?  If it is deciduous, what is the probability
// that it is fruit-bearing?
class ForestCalculator
{
  public:
    ForestCalculator();

    // Returns the same value as calculate_pct_chance_evergreen, but is
    // more appropriate for checking for shield/muskeg-type bimes, rather
    // than checking on a specific type of tree.
    int calculate_pct_chance_shield(const int world_height, const Coordinate& world_loc);

    // Given a total pct chance of 100, P(evergreen) + P(deciduous) = 100.
    int calculate_pct_chance_evergreen(const int world_height, const Coordinate& world_loc);
    int calculate_pct_chance_deciduous(const int world_height, const Coordinate& world_loc);

    int calculate_pct_chance_fruit(const TileType terrain_type);

  protected:
    void initialize_fruit_probability_map();

    static std::map<TileType, int> fruit_probability_map;
};

