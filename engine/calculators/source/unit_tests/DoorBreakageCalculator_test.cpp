#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_DoorBreakageCalculator, calculate_pct_chance_breakage)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Statistic str(17);
  creature->set_strength(str);

  DoorBreakageCalculator dbc;
  DoorPtr wood_door = std::make_shared<Door>();
  wood_door->set_material_type(MaterialType::MATERIAL_TYPE_WOOD);

  EXPECT_EQ(2, dbc.calculate_pct_chance_breakage(creature, wood_door));

  DoorPtr bone_door = std::make_shared<Door>();
  bone_door->set_material_type(MaterialType::MATERIAL_TYPE_BONE);

  EXPECT_EQ(2, dbc.calculate_pct_chance_breakage(creature, bone_door));

  str.set_current(20);
  str.set_base(20);
  creature->set_strength(str);

  EXPECT_EQ(3, dbc.calculate_pct_chance_breakage(creature, bone_door));

  DoorPtr stone_door = std::make_shared<Door>();
  stone_door->set_material_type(MaterialType::MATERIAL_TYPE_STONE);

  EXPECT_EQ(0, dbc.calculate_pct_chance_breakage(creature, stone_door));

  str.set_current(60);
  str.set_base(60);
  creature->set_strength(str);

  EXPECT_EQ(3, dbc.calculate_pct_chance_breakage(creature, stone_door));

  DoorPtr iron_door = std::make_shared<Door>();
  iron_door->set_material_type(MaterialType::MATERIAL_TYPE_IRON);
  
  EXPECT_EQ(0, dbc.calculate_pct_chance_breakage(creature, iron_door));

  str.set_current(73);
  str.set_base(73);
  creature->set_strength(str);

  EXPECT_EQ(4, dbc.calculate_pct_chance_breakage(creature, iron_door));

  DoorPtr steel_door = std::make_shared<Door>();
  steel_door->set_material_type(MaterialType::MATERIAL_TYPE_STEEL);

  EXPECT_EQ(1, dbc.calculate_pct_chance_breakage(creature, steel_door));

  str.set_current(99);
  str.set_base(99);
  creature->set_strength(str);

  EXPECT_EQ(9, dbc.calculate_pct_chance_breakage(creature, steel_door));
}

