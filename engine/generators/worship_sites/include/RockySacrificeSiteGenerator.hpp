#pragma once
#include "ChurchGenerator.hpp"

class RockySacrificeSiteGenerator : public ChurchGenerator
{
  public:
    RockySacrificeSiteGenerator(const std::string& deity_name, MapPtr base_map);

    virtual MapPtr generate() override;
    virtual MapPtr generate(const Dimensions& dim) override;

    std::vector<std::string> get_generator_filters() const override;

protected:
    virtual void generate_site(MapPtr map);
    virtual void generate_stones(MapPtr map);
    
    virtual void generate_features(MapPtr map);
    virtual void generate_pillars(MapPtr map);
    virtual void generate_altar(MapPtr map);

    static const std::string ROCKY_SACRIFICE_SITE_GENERATOR_FILTER;
};
