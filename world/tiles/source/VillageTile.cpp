#include "VillageTile.hpp"

using std::string;

VillageTile::VillageTile()
{
  // Default, can be overridden later.
  tile_subtype = TILE_TYPE_FIELD;
  settlement_type = SETTLEMENT_TYPE_ORDERLY_VILLAGE;
}

VillageTile::VillageTile(const TileType new_tile_subtype)
{
  tile_subtype = new_tile_subtype;
}

bool VillageTile::display_description_on_arrival() const
{
  return true;
}

TileType VillageTile::get_tile_type() const
{
  return TILE_TYPE_VILLAGE;
}

string VillageTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_VILLAGE;
}

void VillageTile::set_village_race_id(const string& new_village_race_id)
{
  village_race_id = new_village_race_id;
}

string VillageTile::get_village_race_id() const
{
  return village_race_id;
}

void VillageTile::set_settlement_type(const SettlementType new_settlement_type)
{
  settlement_type = new_settlement_type;
}

SettlementType VillageTile::get_settlement_type() const
{
  return settlement_type;
}

#ifdef UNIT_TESTS
#include "unit_tests/VillageTile_test.cpp"
#endif
