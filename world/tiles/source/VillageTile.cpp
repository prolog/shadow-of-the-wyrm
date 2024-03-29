#include "Serialize.hpp"
#include "TileProperties.hpp"
#include "VillageTile.hpp"

using namespace std;

VillageTile::VillageTile()
{
  // Default, can be overridden later.
  tile_subtype = TileType::TILE_TYPE_FIELD;
  settlement_type = SettlementType::SETTLEMENT_TYPE_ORDERLY_VILLAGE;
}

VillageTile::VillageTile(const TileType new_tile_subtype)
: settlement_type(SettlementType::SETTLEMENT_TYPE_WALLED)
{
  tile_subtype = new_tile_subtype;
}

bool VillageTile::operator==(const VillageTile& vt) const
{
  bool result = true;

  result = Tile::operator==(vt);
  result = result && (village_race_id == vt.village_race_id);
  result = result && (settlement_type == vt.settlement_type);

  return result;
}

bool VillageTile::display_description_on_arrival() const
{
  return true;
}

TileType VillageTile::get_tile_type() const
{
  return TileType::TILE_TYPE_VILLAGE;
}

string VillageTile::get_tile_description_sid() const
{
  if (has_name())
  {
    return TileTextKeys::TILE_DESC_NAMED_VILLAGE;
  }
  else
  {
    return TileTextKeys::TILE_DESC_VILLAGE;
  }
}

void VillageTile::set_village_race_id(const string& new_village_race_id)
{
  village_race_id = new_village_race_id;
}

string VillageTile::get_village_race_id() const
{
  return village_race_id;
}

void VillageTile::set_village_name(const string& new_name)
{
  set_additional_property(TileProperties::TILE_PROPERTY_NAME, new_name);
}

string VillageTile::get_village_name() const
{
  return get_additional_property(TileProperties::TILE_PROPERTY_NAME);
}

void VillageTile::set_settlement_type(const SettlementType new_settlement_type)
{
  settlement_type = new_settlement_type;
}

SettlementType VillageTile::get_settlement_type() const
{
  return settlement_type;
}

bool VillageTile::serialize(ostream& stream) const
{
  WorldMapLandmarkTile::serialize(stream);

  Serialize::write_string(stream, village_race_id);
  Serialize::write_enum(stream, settlement_type);

  return true;
}

bool VillageTile::deserialize(istream& stream)
{
  WorldMapLandmarkTile::deserialize(stream);

  Serialize::read_string(stream, village_race_id);
  Serialize::read_enum(stream, settlement_type);

  return true;
}

Tile* VillageTile::clone()
{
  return new VillageTile(*this);
}

ClassIdentifier VillageTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_VILLAGE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/VillageTile_test.cpp"
#endif
