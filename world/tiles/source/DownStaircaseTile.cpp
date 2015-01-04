#include "DownStaircaseTile.hpp"

TileType DownStaircaseTile::get_tile_type() const
{
  return TileType::TILE_TYPE_DOWN_STAIRCASE;
}

StaircaseType DownStaircaseTile::get_staircase_type() const
{
  return StaircaseType::STAIRCASE_DOWN;
}

std::string DownStaircaseTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DOWN_STAIRCASE;
}

Tile* DownStaircaseTile::clone()
{
  return new DownStaircaseTile(*this);
}

ClassIdentifier DownStaircaseTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DOWN_STAIRCASE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DownStaircaseTile_test.cpp"
#endif
