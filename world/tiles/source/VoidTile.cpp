#include "VoidTile.hpp"
#include "MovementTextKeys.hpp"

TileType VoidTile::get_tile_type() const
{
  return TileType::TILE_TYPE_VOID;
}

std::string VoidTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_VOID;
}

std::string VoidTile::get_no_exit_up_message_sid() const
{
  return MovementTextKeys::ACTION_MOVE_NO_EXIT_COSMOS;
}

std::string VoidTile::get_no_exit_down_message_sid() const
{
  return MovementTextKeys::ACTION_MOVE_NO_EXIT_COSMOS;
}

Tile* VoidTile::clone()
{
  return new VoidTile(*this);
}

ClassIdentifier VoidTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_VOID_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/VoidTile_test.cpp"
#endif
