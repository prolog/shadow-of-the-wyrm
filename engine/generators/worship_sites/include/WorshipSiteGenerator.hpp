#pragma once
#include "WorshipSiteTypes.hpp"
#include "ChurchGenerator.hpp"

class WorshipSiteGenerator
{
  public:
    static ChurchGeneratorPtr generate_worship_site(const WorshipSiteType site_type, const std::string& deity_id, const MapPtr base_map);

  protected:
    WorshipSiteGenerator();
    ~WorshipSiteGenerator();
};
