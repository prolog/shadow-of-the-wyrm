#include "AirTile.hpp"
#include "NullInventory.hpp"
#include "MovementTextKeys.hpp"
#include "TileDangerConfirmationKeys.hpp"

using namespace std;

AirTile::AirTile()
{
  items = std::make_shared<NullInventory>();
}

TileType AirTile::get_tile_type() const
{
  return TileType::TILE_TYPE_AIR;
}

TileSuperType AirTile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_AIR;
}

string AirTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_AIR;
}

bool AirTile::get_danger_flag(CreaturePtr cr) const
{
  if (cr && cr->has_status(StatusIdentifiers::STATUS_ID_FLYING))
  {
    return false;
  }

  return true;
}

string AirTile::get_danger_confirmation_sid() const
{
  return TileDangerConfirmationKeys::TILE_DANGER_AIR;
}

string AirTile::get_no_exit_up_message_sid() const
{
  return MovementTextKeys::ACTION_MOVE_NO_EXIT_UP_AIR;
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

