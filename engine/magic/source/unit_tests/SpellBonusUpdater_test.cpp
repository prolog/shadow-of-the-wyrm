#include "gtest/gtest.h"

TEST(SW_Engine_Magic_SpellBonusUpdater, add_successful_casting)
{
  SpellBonusUpdater sbu;
  IndividualSpellKnowledge isk;

  // First time incrementing (from 0): successful
  EXPECT_TRUE(sbu.add_successful_casting(isk));

  // Base is incremented to 1.
  // Current is reset to 0.
  // Adding another casting brings current to 1, which means that the
  // base is increased to 2, cur to 0.
  EXPECT_TRUE(sbu.add_successful_casting(isk));

  // Cur is increased to 1, which is less than the base of 2, so the
  // base is not incremented.
  EXPECT_FALSE(sbu.add_successful_casting(isk));

  // Cur is increase to 2, which equals the base of 2, so the base is
  // incremented to 3.
  EXPECT_TRUE(sbu.add_successful_casting(isk));

  // Base should be 3, now.
  EXPECT_EQ(3, isk.get_bonus().get_base());
}

TEST(SW_Engine_Magic_SpellBonusUpdater, spell_bonus_respects_maximum)
{
  SpellBonusUpdater sbu;
  IndividualSpellKnowledge isk;

  int max_bonus = SpellConstants::MAX_SPELL_BONUS;

  Statistic bonus = isk.get_bonus();
  bonus.set_current(max_bonus - 2);
  bonus.set_base(max_bonus - 1);

  isk.set_bonus(bonus);

  EXPECT_TRUE(sbu.add_successful_casting(isk));

  bonus.set_current(max_bonus-1);
  bonus.set_base(max_bonus);

  EXPECT_FALSE(sbu.add_successful_casting(isk));
}