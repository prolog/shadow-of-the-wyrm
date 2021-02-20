#include "gtest/gtest.h"

TEST(SW_Engine_Creatures_CreatureGenerationIndex, get)
{
  CreatureGenerationList creature_list;

  CreatureGenerationValues cgv;
  cgv.set_danger_level(6);
  CreatureGenerationListValue cglv("abc123", nullptr, cgv);

  creature_list.push_back(cglv);
  CreatureGenerationIndex cgi(creature_list);

  CreatureGenerationList cgl2 = cgi.get();
  EXPECT_TRUE(creature_list == cgl2);

  CreatureGenerationIndex cgi_empty;
  EXPECT_TRUE(cgi_empty.get().empty());
}

TEST(SW_Engine_Creatures_CreatureGenerationIndex, get_danger_level)
{
  CreatureGenerationList creature_list;

  CreatureGenerationValues cgv;
  cgv.set_danger_level(3);
  CreatureGenerationListValue cglv("abc123", nullptr, cgv);

  CreatureGenerationValues cgv2;
  cgv2.set_danger_level(6);
  CreatureGenerationListValue cglv2("def456", nullptr, cgv2);

  creature_list.push_back(cglv);
  creature_list.push_back(cglv2);

  CreatureGenerationIndex cgi(creature_list);
  CreatureGenerationList cgl = cgi.get(3);

  EXPECT_EQ(1, cgl.size());
  EXPECT_EQ(3, cgl[0].get_creature_generation_values().get_danger_level());

  CreatureGenerationIndex cgi_empty;
  EXPECT_TRUE(cgi_empty.get(3).empty());
}
