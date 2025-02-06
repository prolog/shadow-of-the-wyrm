#pragma once
#include "Generator.hpp"

class WheatFieldGenerator : public SOTW::Generator
{
  public:
    WheatFieldGenerator(const std::string& map_exit_id);
    virtual ~WheatFieldGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    void place_scarecrow(MapPtr map);

    static const int PCT_CHANCE_SCARECROW;
    static const int PCT_CHANCE_LIVING_SCARECROW;
};
