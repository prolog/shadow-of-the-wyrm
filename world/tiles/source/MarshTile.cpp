#include "MarshTile.hpp"

TileType MarshTile::get_tile_type() const
{
  return TileType::TILE_TYPE_MARSH;
}

std::string MarshTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_MARSH;
}

int MarshTile::get_movement_multiplier() const
{
  return 2;
}

SkillType MarshTile::get_treasure_skill() const
{
  return SkillType::SKILL_GENERAL_MARSH_LORE;
}

Tile* MarshTile::clone()
{
  return new MarshTile(*this);
}

ClassIdentifier MarshTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MARSH_TILE;
}


#ifdef UNIT_TESTS
#include "unit_tests/MarshTile_test.cpp"
#endif
