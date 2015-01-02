#include "AirTile.hpp"
#include "NullInventory.hpp"
#include "TileDangerConfirmationKeys.hpp"

using namespace std;

AirTile::AirTile()
{
  items = std::make_shared<NullInventory>();
}

TileType AirTile::get_tile_type() const
{
  return TILE_TYPE_AIR;
}

TileSuperType AirTile::get_tile_super_type() const
{
  return TILE_SUPER_TYPE_AIR;
}

string AirTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_AIR;
}

bool AirTile::get_dangerous(CreaturePtr creature) const
{
  // TODO: Update this to check status of Flying effect.
  return true;
}

string AirTile::get_danger_confirmation_sid() const
{
  return TileDangerConfirmationKeys::TILE_DANGER_AIR;
}

Tile* AirTile::clone()
{
  return new AirTile(*this);
}

ClassIdentifier AirTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AIR_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/AirTile_test.cpp"
#endif

