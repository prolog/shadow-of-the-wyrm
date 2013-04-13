#include "gtest/gtest.h"
#include <boost/make_shared.hpp>

TEST(SL_Engine_Magic_MagicalAbilityChecker, has_magical_knowledge)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  MagicalAbilityChecker mac;

  EXPECT_FALSE(mac.has_magical_knowledge(creature));

  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  sk.set_spell_knowledge("blasty", 12);

  EXPECT_TRUE(mac.has_magical_knowledge(creature));
}

TEST(SL_Engine_Magic_MagicalAbilityChecker, has_power)
{
  CreaturePtr creature = boost::make_shared<Creature>();
  MagicalAbilityChecker mac;

  Spell spell;
  spell.set_ap_cost(4);

  EXPECT_FALSE(mac.has_sufficient_power(creature, spell));

  Statistic ap(4);
  creature->set_arcana_points(ap);
  
  EXPECT_TRUE(mac.has_sufficient_power(creature, spell));

  ap.set_base(12);
  ap.set_current(12);
  creature->set_arcana_points(ap);

  EXPECT_TRUE(mac.has_sufficient_power(creature, spell));
}