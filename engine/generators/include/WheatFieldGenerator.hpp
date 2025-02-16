#pragma once
#include "Generator.hpp"

class WheatFieldGenerator : public SOTW::Generator
{
  public:
    WheatFieldGenerator(const std::string& map_exit_id);
    virtual ~WheatFieldGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    void generate_field(MapPtr map);
    
    void generate_divisions(MapPtr map, const std::vector<std::pair<Coordinate, Coordinate>>& divisions, const int count);
    std::vector<std::pair<Coordinate, Coordinate>> divide_field(MapPtr map, const std::vector<std::pair<Coordinate, Coordinate>>& divisions, const int count);
    
    void place_scarecrow(MapPtr map);

    static const int PCT_CHANCE_SCARECROW;
    static const int PCT_CHANCE_LIVING_SCARECROW;
};
