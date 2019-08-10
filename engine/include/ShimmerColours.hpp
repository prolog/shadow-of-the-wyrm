#pragma once
#include <vector>
#include "Colours.hpp"
#include "ISerializable.hpp"

class ShimmerColours : public ISerializable
{
  public:
    ShimmerColours();
    ShimmerColours(const std::vector<Colour>& sh_colours, const int pct_chance_shimmer = BASE_PCT_CHANCE_SHIMMER);
    bool operator==(const ShimmerColours& sc) const;

    Colour get_passable_colour() const;
    Colour get_impassable_colour() const;
    Colour get_feature_colour() const;
    Colour get_shimmer_colour() const;
    int get_pct_chance_shimmer() const;

    std::vector<Colour> get_raw_colours() const;

    bool serialize(std::ostream& stream) const;
    bool deserialize(std::istream& stream);

    static const int BASE_PCT_CHANCE_SHIMMER;

  protected:
    std::vector<Colour> colours;
    int pct_chance_shimmer;

    bool is_valid() const;
    Colour get_colour_or_undefined(const size_t idx) const;

    static const size_t PASSABLE_IDX;
    static const size_t IMPASSABLE_IDX;
    static const size_t FEATURE_IDX;
    static const size_t SHIMMER_IDX;
    static const size_t VALID_SIZE;

  private:
    ClassIdentifier internal_class_identifier() const;
};

