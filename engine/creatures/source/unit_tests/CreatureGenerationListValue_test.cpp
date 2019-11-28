#include "gtest/gtest.h"

TEST(SW_Engine_Creatures_CreatureGenerationListValue, values)
{
  string creature_base_id = "monster";
  string id_val = "abc123";
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_id(id_val);
  CreatureGenerationValues cgv;

  CreatureGenerationListValue cglv(creature_base_id, creature, cgv);

  EXPECT_EQ(creature_base_id, cglv.get_creature_base_id());
  EXPECT_EQ(id_val, cglv.get_creature()->get_id());
  EXPECT_EQ(cgv, cglv.get_creature_generation_values());
}