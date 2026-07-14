#pragma once
#include "Generator.hpp"

class IcebergGenerator : public SOTW::Generator
{
  public:
    IcebergGenerator(const std::string& map_exit_id);
    virtual ~IcebergGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    void fill_with_overlay(MapPtr map, const TileType fill_tt, const TileType overlay_tt, const int y_bound, const int x_bound);

    static const int Y_DIVISOR_MIN, Y_DIVISOR_MAX, X_DIVISOR_MIN, X_DIVISOR_MAX;
};
