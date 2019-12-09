#include "gtest/gtest.h"
#include "FieldTile.hpp"
#include "RockTile.hpp"
#include "FirePillar.hpp"
#include "FeatureGenerator.hpp"

TEST(SW_Engine_Magic_TileMagicChecker, does_tile_block_spell)
{
  TileMagicChecker tmc;
  Spell spell;
  Spell incorp_spell;
  Spell dig_spell;

  Damage damage;
  damage.set_incorporeal(true);
  incorp_spell.set_damage(damage);

  dig_spell.set_effect(EffectType::EFFECT_TYPE_DIGGING);

  TilePtr rock = std::make_shared<RockTile>();
  TilePtr field = std::make_shared<FieldTile>();
  FeaturePtr fp = FeatureGenerator::generate_fire_pillar();

  // Solid tiles should block
  EXPECT_TRUE(tmc.does_tile_block_spell(rock, spell));

  // Regular tiles should not block
  EXPECT_FALSE(tmc.does_tile_block_spell(field, spell));

  // Blocking features should block
  field->set_feature(fp);

  EXPECT_TRUE(tmc.does_tile_block_spell(field, spell));

  // Incorporeal damage and digging effects should prevent blockage.
  EXPECT_FALSE(tmc.does_tile_block_spell(field, incorp_spell));
  EXPECT_FALSE(tmc.does_tile_block_spell(field, dig_spell));
}

