#include "Serialize.hpp"
#include "WorshipSiteTile.hpp"

using namespace std;

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

bool WorshipSiteTile::serialize(ostream& stream) const
{
  WorldMapLandmarkTile::serialize(stream);

  Serialize::write_string(stream, deity_id);
  Serialize::write_enum(stream, site_type);

  return true;
}

bool WorshipSiteTile::deserialize(istream& stream)
{
  WorldMapLandmarkTile::deserialize(stream);

  Serialize::read_string(stream, deity_id);
  Serialize::read_enum(stream, site_type);

  return true;
}

ClassIdentifier WorshipSiteTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WORSHIP_SITE_TILE;
}
