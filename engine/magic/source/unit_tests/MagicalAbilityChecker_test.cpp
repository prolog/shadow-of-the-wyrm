#include "gtest/gtest.h"

TEST(SW_Engine_Magic_MagicalAbilityChecker, has_magical_knowledge)
{
  CreaturePtr creature = std::make_shared<Creature>();
  MagicalAbilityChecker mac;
  IndividualSpellKnowledge isk;

  EXPECT_FALSE(mac.has_magical_knowledge(creature));

  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  sk.set_spell_knowledge("blasty", isk);

  EXPECT_FALSE(mac.has_magical_knowledge(creature));

  isk.set_castings(4);
  sk.set_spell_knowledge("blasty", isk);

  EXPECT_TRUE(mac.has_magical_knowledge(creature));
}

TEST(SW_Engine_Magic_MagicalAbilityChecker, has_power)
{
  CreaturePtr creature = std::make_shared<Creature>();
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