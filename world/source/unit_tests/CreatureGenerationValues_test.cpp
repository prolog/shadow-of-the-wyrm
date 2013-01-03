#include "gtest/gtest.h"

TEST(SL_World_CreatureGenerationValues, serialization_id)
{
  CreatureGenerationValues cgv;

  EXPECT_EQ(CLASS_ID_CREATURE_GENERATION_VALUES, cgv.get_class_identifier());
}

TEST(SL_World_CreatureGenerationValues, saveload)
{
  CreatureGenerationValues cgv, cgv2;

  cgv.set_current(1);
  cgv.incr_current();
  cgv.set_maximum(4);
  cgv.set_friendly(true);
  cgv.set_rarity(Rarity(10));

  cgv.add_allowable_terrain_type(TILE_TYPE_BARRACKS);
  cgv.add_allowable_terrain_type(TILE_TYPE_MARSH);
  cgv.add_allowable_terrain_type(TILE_TYPE_PIER);

  Dice hp(5, 6, 7);
  cgv.set_initial_hit_points(hp);
  cgv.set_base_experience_value(105);

  ostringstream ss;

  cgv.serialize(ss);

  istringstream iss(ss.str());

  cgv2.deserialize(iss);

  EXPECT_TRUE(cgv == cgv2);
}

