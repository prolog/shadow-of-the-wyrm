#include "SeaTile.hpp"
#include "MovementTextKeys.hpp"
#include "WaterInventory.hpp"
#include "WaterTypes.hpp"

SeaTile::SeaTile()
{
  items = std::make_shared<WaterInventory>();
}

TileType SeaTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SEA;
}

TileSuperType SeaTile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
}

WaterType SeaTile::get_water_type() const
{
  return WaterType::WATER_TYPE_SALT;
}

std::string SeaTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SEA;
}

std::string SeaTile::get_no_exit_down_message_sid() const
{
  return MovementTextKeys::ACTION_MOVE_NO_EXIT_DOWN_SEA;
}

Tile* SeaTile::clone()
{
  return new SeaTile(*this);
}

ClassIdentifier SeaTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SEA_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SeaTile_test.cpp"
#endif
