#pragma once
#include "ChurchGenerator.hpp"

// Overgrown sacrificial site, hidden away from most eyes.  Used by
// the dread minions of Sceadugenga, who practice in silence and 
// secrecy.
// 
// Assumed: underlying tile type allows trees and weeds
class OvergrownSacrificeSiteGenerator : public ChurchGenerator
{
  public:
    OvergrownSacrificeSiteGenerator(const std::string& new_deity_id, MapPtr new_base_map);
    virtual ~OvergrownSacrificeSiteGenerator() = default;

    MapPtr generate(const Dimensions& dim) override;
    MapPtr generate() override;

    std::vector<std::string> get_generator_filters() const override;

  protected:
    void generate_site(MapPtr map);
    void generate_additional_brush(MapPtr map);
    void generate_altar(MapPtr map);

    static const std::string OVERGROWN_SACRIFICE_SITE_GENERATOR_FILTER;
};
