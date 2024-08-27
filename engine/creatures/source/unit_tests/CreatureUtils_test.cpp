#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "ImmobileDecisionStrategy.hpp"

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
  EXPECT_TRUE(get<0>(CreatureUtils::can_pick_up(c, amulet2)));

  c->get_inventory()->add_front(amulet2);

  // Carrying capacity should be 100, so a proposed new total of 120
  // should not be allowed.
  auto pickup_details = CreatureUtils::can_pick_up(c, amulet3);
  EXPECT_FALSE(get<0>(pickup_details));
  EXPECT_EQ(7, get<1>(pickup_details));
}

TEST(SW_Engine_CreatureUtils, has_negative_status)
{
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(CreatureUtils::has_negative_status(nullptr));
  EXPECT_FALSE(CreatureUtils::has_negative_status(creature));

  Status s;
  creature->set_status(StatusIdentifiers::STATUS_ID_WATER_BREATHING, s);

  EXPECT_FALSE(CreatureUtils::has_negative_status(creature));

  creature->set_status(StatusIdentifiers::STATUS_ID_STONE, s);

  EXPECT_TRUE(CreatureUtils::has_negative_status(creature));
}

TEST(SW_Engine_CreatureUtils, has_followers_in_fov)
{
  CreatureMap cm = CreatureUtils::get_followers_in_fov(nullptr);

  EXPECT_TRUE(cm.empty());

  string l_id = "leader";
  CreaturePtr c = std::make_shared<Creature>();
  c->set_id(l_id);
  DecisionStrategyPtr d = std::make_unique<ImmobileDecisionStrategy>(nullptr);
  Dimensions dim;
  MapPtr fov_map = std::make_shared<Map>(dim);
  d->set_fov_map(fov_map);
  c->set_decision_strategy(std::move(d));

  cm = CreatureUtils::get_followers_in_fov(c);

  EXPECT_TRUE(cm.empty());

  CreaturePtr c2 = std::make_shared<Creature>();
  c->get_decision_strategy()->get_fov_map()->get_creatures_ref().insert(make_pair("id", c2));

  cm = CreatureUtils::get_followers_in_fov(c);

  EXPECT_TRUE(cm.empty());

  c2->set_leader_and_at_ease(l_id);

  cm = CreatureUtils::get_followers_in_fov(c);

  EXPECT_FALSE(cm.empty());
  EXPECT_EQ(1, cm.size());
}

TEST(SW_Engine_Creatures_CreatureUtils, has_primordial_essence)
{
  Game& game = Game::instance();
  Spell pri_spell;
  string pspell_id = "p_test";
  pri_spell.set_magic_category(SkillType::SKILL_MAGIC_PRIMORDIAL);
  const SpellMap& old_spells = game.get_spells_ref();

  SpellMap spells;
  spells[pspell_id] = pri_spell;
  game.set_spells(spells);

  CreaturePtr creature = std::make_shared<Creature>();
  EXPECT_EQ(false, CreatureUtils::has_primordial_essence(creature));

  Damage d;
  d.set_damage_type(DamageType::DAMAGE_TYPE_SHADOW);
  creature->set_base_damage(d);

  EXPECT_EQ(true, CreatureUtils::has_primordial_essence(creature));

  d.set_damage_type(DamageType::DAMAGE_TYPE_POUND);
  creature->set_base_damage(d);

  EXPECT_EQ(false, CreatureUtils::has_primordial_essence(creature));

  SpellKnowledge sk;
  IndividualSpellKnowledge isk;
  isk.set_castings(30);
  sk.set_spell_knowledge(pspell_id, isk);
  creature->set_spell_knowledge(sk);

  EXPECT_EQ(true, CreatureUtils::has_primordial_essence(creature));

  game.set_spells(old_spells);
}

TEST(SW_Engine_Creatures_CreatureUtils, is_grouped)
{
  CreaturePtr c1 = std::make_shared<Creature>();
  CreaturePtr c2 = std::make_shared<Creature>();
  string leader_id = "bob";

  EXPECT_FALSE(CreatureUtils::is_grouped(nullptr, nullptr));
  EXPECT_FALSE(CreatureUtils::is_grouped(c1, nullptr));
  EXPECT_FALSE(CreatureUtils::is_grouped(nullptr, c1));
  EXPECT_FALSE(CreatureUtils::is_grouped(c1, c2));

  c1->set_leader_and_at_ease(leader_id);

  EXPECT_FALSE(CreatureUtils::is_grouped(c1, c2));

  c2->set_id("bob");

  EXPECT_TRUE(CreatureUtils::is_grouped(c1, c2));

  c2->set_id("not_bob");
  c2->set_leader_and_at_ease(leader_id);

  EXPECT_TRUE(CreatureUtils::is_grouped(c1, c2));
}
