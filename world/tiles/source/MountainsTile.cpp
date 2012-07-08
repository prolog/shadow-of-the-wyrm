#include "MountainsTile.hpp"
#include "StringConstants.hpp"

using std::string;

TileType MountainsTile::get_tile_type() const
{
  return TILE_TYPE_MOUNTAINS;
}

std::string MountainsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_MOUNTAINS;
}

bool MountainsTile::get_dangerous() const
{
  return true;
}

string MountainsTile::get_danger_confirmation_sid() const
{
  string danger_confirmation = TileDangerConfirmationKeys::TILE_DANGER_MOUNTAINS;
  return danger_confirmation;
}

#ifdef UNIT_TESTS
#include "unit_tests/MountainsTile_test.cpp"
#endif
