#pragma once
#include <vector>
#include "Colours.hpp"
class ShimmerColours
{
  public:
    ShimmerColours(const std::vector<Colour>& sh_colours);

    Colour get_passable_colour() const;
    Colour get_impassable_colour() const;
    Colour get_feature_colour() const;
    Colour get_shimmer_colour() const;
    int get_pct_chance_shimmer() const;

  protected:
    std::vector<Colour> colours;

    bool is_valid() const;
    Colour get_colour_or_undefined(const size_t idx) const;

    static const int PCT_CHANCE_SHIMMER;
    static const size_t PASSABLE_IDX;
    static const size_t IMPASSABLE_IDX;
    static const size_t FEATURE_IDX;
    static const size_t SHIMMER_IDX;
    static const size_t VALID_SIZE;
};

