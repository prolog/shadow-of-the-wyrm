#pragma once
#include "Generator.hpp"

class IcebergGenerator : public SOTW::Generator
{
  public:
    IcebergGenerator(const std::string& map_exit_id);
    virtual ~IcebergGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    void carve_edges(MapPtr map);

    static const int Y_DIVISOR_MIN, Y_DIVISOR_MAX, X_DIVISOR_MIN, X_DIVISOR_MAX;
};
