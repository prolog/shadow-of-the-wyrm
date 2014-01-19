#include "gtest/gtest.h"
#include "Armour.hpp"

TEST(SL_Engine_Calculators_CreatureToHitCalculator, calculate_to_hit_bonus)
{
  CreatureToHitCalculator cthc;
  Creature c;
  
  CreaturePtr cp = std::make_shared<Creature>(c);
  
  // Add two items, make sure the creature's to-hit reflects
  // both.
  ArmourPtr item1 = ArmourPtr(new Armour());
  item1->set_to_hit(4);

  ArmourPtr item2 = ArmourPtr(new Armour());
  item2->set_to_hit(7);

  cp->get_equipment().set_item(item1, EQUIPMENT_WORN_BODY);
  cp->get_equipment().set_item(item2, EQUIPMENT_WORN_ABOUT_BODY);

  EXPECT_EQ(11, cthc.calculate_to_hit(cp));
}
