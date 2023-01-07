#include "DesertTile.hpp"

TileType DesertTile::get_tile_type() const
{
  return TileType::TILE_TYPE_DESERT;
}

std::string DesertTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DESERT;
}

SkillType DesertTile::get_treasure_skill() const
{
  return SkillType::SKILL_GENERAL_DESERT_LORE;
}

Tile* DesertTile::clone()
{
  return new DesertTile(*this);
}

ClassIdentifier DesertTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DESERT_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DesertTile_test.cpp"
#endif
