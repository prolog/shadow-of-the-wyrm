#pragma once
#include "ChurchGenerator.hpp"

// The followers of Shiver conduct their sacrifices on small patches of land surrounded by man made moats.
// These sites are colloquially called "islands".
class IslandSacrificeSiteGenerator : public ChurchGenerator
{
  public:
    IslandSacrificeSiteGenerator(const std::string& new_deity_id, MapPtr new_base_map);

    MapPtr generate(const Dimensions& dim) override;
    MapPtr generate() override;

    std::vector<std::string> get_generator_filters() const override;

  protected:
    void generate_site(MapPtr map);
    void generate_island(MapPtr map);
    void generate_features(MapPtr map);

    static const std::string ISLAND_SACRIFICE_SITE_GENERATOR_FILTER;
};
