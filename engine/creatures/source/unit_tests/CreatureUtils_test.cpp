#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Creatures_CreatureUtils, can_pick_up)
{
  CreaturePtr c = std::make_shared<Creature>();
  c->set_size(CreatureSize::CREATURE_SIZE_MEDIUM);
  Statistic dex(10);
  c->set_dexterity(dex);

  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_quantity(90);

  ItemPtr amulet2 = std::make_shared<Amulet>();
  amulet2->set_quantity(3);

  ItemPtr amulet3 = std::make_shared<Amulet>();
  amulet3->set_quantity(30);

  c->get_inventory()->add_front(amulet);

  // Carrying capacity should be 100, so a proposed new total of 93
  // is fine.
  EXPECT_TRUE(CreatureUtils::can_pick_up(c, amulet2));

  // Carrying capacity should be 100, so a proposed new total of 120
  // should not be allowed.
  EXPECT_FALSE(CreatureUtils::can_pick_up(c, amulet3));
}

