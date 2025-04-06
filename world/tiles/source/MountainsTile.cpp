#include "MountainsTile.hpp"
#include "TileDangerConfirmationKeys.hpp"

using std::string;

TileType MountainsTile::get_tile_type() const
{
  return TileType::TILE_TYPE_MOUNTAINS;
}

std::string MountainsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_MOUNTAINS;
}

bool MountainsTile::get_danger_flag(CreaturePtr cr) const
{
  if (cr && cr->get_skills().get_value(SkillType::SKILL_GENERAL_MOUNTAIN_LORE) == Skills::MAX_SKILL_VALUE)
  {
    return false;
  }

  return true;
}

string MountainsTile::get_danger_confirmation_sid() const
{
  string danger_confirmation = TileDangerConfirmationKeys::TILE_DANGER_MOUNTAINS;
  return danger_confirmation;
}

// Mountains are real big and therefore real blocky
// But they should only block LOS, not movement!
bool MountainsTile::get_is_blocking_visually(CreaturePtr /*creature*/) const
{
  return true;
}

SkillType MountainsTile::get_treasure_skill() const
{
  return SkillType::SKILL_GENERAL_MOUNTAIN_LORE;
}

Tile* MountainsTile::clone()
{
  return new MountainsTile(*this);
}

ClassIdentifier MountainsTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MOUNTAINS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/MountainsTile_test.cpp"
#endif
