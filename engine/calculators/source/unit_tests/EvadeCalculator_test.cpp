#include "gtest/gtest.h"
#include <boost/make_shared.hpp>

using boost::make_shared;

TEST(SL_Engine_Calculators_EvadeCalculator, calculate_evade_bonus)
{
  Creature c;
  
  c.set_strength(10);
  c.set_dexterity(10);
  c.set_agility(20);
  c.set_health(10);
  c.set_intelligence(15);
  c.set_willpower(15);
  c.set_charisma(10);
  c.set_valour(50);
  c.set_spirit(50);
  
  CreaturePtr cp = make_shared<Creature>(c);
  
  // Agility > 10
  EXPECT_EQ(5, EvadeCalculator::calculate_evade(cp));
  
  // Agility < 10
  cp->set_agility(5);
  EXPECT_EQ(-2, EvadeCalculator::calculate_evade(cp));
  
  // Valour > 50
  cp->set_agility(15);
  cp->set_valour(68);
  EXPECT_EQ(-1, EvadeCalculator::calculate_evade(cp));
  
  // Valour < 50
  cp->set_valour(5);
  EXPECT_EQ(11, EvadeCalculator::calculate_evade(cp));
}
