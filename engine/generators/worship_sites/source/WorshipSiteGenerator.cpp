#include <boost/make_shared.hpp>
#include "RNG.hpp"
#include "CathedralGenerator.hpp"
#include "FortifiedChurchGenerator.hpp"
#include "SimpleChurchGenerator.hpp"
#include "GrandTempleGenerator.hpp"
#include "SnakingTempleGenerator.hpp"
#include "SimpleTempleGenerator.hpp"
#include "IslandSacrificeSiteGenerator.hpp"
#include "RockySacrificeSiteGenerator.hpp"
#include "OvergrownSacrificeSiteGenerator.hpp"
#include "WorshipSiteGenerator.hpp"

using std::string;
using boost::make_shared;

WorshipSiteGenerator::WorshipSiteGenerator()
{
}

WorshipSiteGenerator::~WorshipSiteGenerator()
{
}

// Generate a specific worship site
ChurchGeneratorPtr WorshipSiteGenerator::generate_worship_site(const WorshipSiteType site_type, const string& deity_id, MapPtr base_map)
{
  ChurchGeneratorPtr site_gen;

  switch(site_type)
  {
    case WORSHIP_SITE_CATHEDRAL:
      site_gen = make_shared<CathedralGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_FORTIFIED_CHURCH:
      site_gen = make_shared<FortifiedChurchGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_SIMPLE_CHURCH:
      site_gen = make_shared<SimpleChurchGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_GRAND_TEMPLE:
      site_gen = make_shared<GrandTempleGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_SNAKING_TEMPLE:
      site_gen = make_shared<SnakingTempleGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_SIMPLE_TEMPLE:
      site_gen = make_shared<SimpleTempleGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_ISLAND_SACRIFICE_SITE:
      site_gen = make_shared<IslandSacrificeSiteGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_ROCKY_SACRIFICE_SITE:
      site_gen = make_shared<RockySacrificeSiteGenerator>(deity_id, base_map);
      break;
    case WORSHIP_SITE_OVERGROWN_SACRIFICE_SITE:      
    default:
      site_gen = make_shared<OvergrownSacrificeSiteGenerator>(deity_id, base_map);
      break;
  }

  return site_gen;
}

