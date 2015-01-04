#include "UpStaircaseTile.hpp"

TileType UpStaircaseTile::get_tile_type() const
{
  return TileType::TILE_TYPE_UP_STAIRCASE;
}

StaircaseType UpStaircaseTile::get_staircase_type() const
{
  return StaircaseType::STAIRCASE_UP;
}

std::string UpStaircaseTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_UP_STAIRCASE;
}

Tile* UpStaircaseTile::clone()
{
  return new UpStaircaseTile(*this);
}

ClassIdentifier UpStaircaseTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_UP_STAIRCASE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/UpStaircaseTile_test.cpp"
#endif
