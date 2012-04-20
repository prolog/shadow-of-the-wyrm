#include "WorshipSiteTile.hpp"

using std::string;

WorshipSiteTile::WorshipSiteTile()
: WorldMapLandmarkTile()
, site_type(WORSHIP_SITE_CATHEDRAL)
{
}

void WorshipSiteTile::set_deity_id(const string& new_deity_id)
{
  deity_id = new_deity_id;
}

string WorshipSiteTile::get_deity_id() const
{
  return deity_id;
}

void WorshipSiteTile::set_worship_site_type(const WorshipSiteType new_site_type)
{
  site_type = new_site_type;
}

WorshipSiteType WorshipSiteTile::get_worship_site_type() const
{
  return site_type;
}

