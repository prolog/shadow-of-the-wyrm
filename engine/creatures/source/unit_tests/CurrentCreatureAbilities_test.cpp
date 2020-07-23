#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "ImmobileDecisionStrategy.hpp"
#include "MobileDecisionStrategy.hpp"

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_speak)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_speak(nullptr));
  EXPECT_TRUE(cca.can_speak(creature));

  Status s;
  s.set_value(true);

  creature->set_status(StatusIdentifiers::STATUS_ID_PARALYSIS, s);
  EXPECT_FALSE(cca.can_speak(creature));

  creature->remove_status(StatusIdentifiers::STATUS_ID_PARALYSIS);
  creature->set_status(StatusIdentifiers::STATUS_ID_MUTE, s);

  EXPECT_FALSE(cca.can_speak(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_give_orders)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_give_orders(nullptr));
  EXPECT_FALSE(cca.can_give_orders(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, 30);

  EXPECT_TRUE(cca.can_give_orders(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, 0);
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MUSIC, 30);

  EXPECT_TRUE(cca.can_give_orders(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MUSIC, 0);
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_LEADERSHIP, 30);

  EXPECT_TRUE(cca.can_give_orders(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_focus)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_focus(nullptr));
  EXPECT_TRUE(cca.can_focus(creature));

  Status s;
  s.set_value(true);

  creature->set_status(StatusIdentifiers::STATUS_ID_RAGE, s);

  EXPECT_FALSE(cca.can_focus(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_see)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_see(nullptr));
  EXPECT_TRUE(cca.can_see(creature));

  Status s;
  s.set_value(true);

  creature->set_status(StatusIdentifiers::STATUS_ID_BLINDED, s);

  EXPECT_FALSE(cca.can_see(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_hear)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_hear(nullptr));
  EXPECT_TRUE(cca.can_hear(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_move)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();
  DecisionStrategyPtr dec = std::make_unique<MobileDecisionStrategy>(nullptr);
  creature->set_decision_strategy(std::move(dec));

  EXPECT_FALSE(cca.can_move(nullptr));
  EXPECT_TRUE(cca.can_move(creature));

  Status s;
  s.set_value(true);

  creature->set_status(StatusIdentifiers::STATUS_ID_PARALYSIS, s);

  EXPECT_FALSE(cca.can_move(creature));

  creature->remove_status(StatusIdentifiers::STATUS_ID_PARALYSIS);
  creature->set_status(StatusIdentifiers::STATUS_ID_SPELLBOUND, s);

  EXPECT_FALSE(cca.can_move(creature));

  creature->remove_status(StatusIdentifiers::STATUS_ID_SPELLBOUND);

  EXPECT_TRUE(cca.can_move(creature));

  AmuletPtr amulet = std::make_shared<Amulet>();
  Weight w;
  w.set_weight(9999, 0);
  amulet->set_weight(w);
  
  creature->get_inventory()->add(amulet);

  EXPECT_FALSE(cca.can_move(creature));

  creature->get_inventory()->clear();

  EXPECT_TRUE(cca.can_move(creature));
  
  dec = std::make_unique<ImmobileDecisionStrategy>(nullptr);
  creature->set_decision_strategy(std::move(dec));

  EXPECT_FALSE(cca.can_move(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_act)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_act(nullptr));
  EXPECT_TRUE(cca.can_act(creature));

  Status s;
  s.set_value(true);

  creature->set_status(StatusIdentifiers::STATUS_ID_PARALYSIS, s);

  EXPECT_FALSE(cca.can_act(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_read)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_read(nullptr));
  EXPECT_FALSE(cca.can_read(creature));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_LITERACY, 30);
  EXPECT_TRUE(cca.can_read(creature));
}

TEST(SW_Engine_Creatures_CurrentCreatureAbilities, can_select_movement_direction)
{
  CurrentCreatureAbilities cca;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_FALSE(cca.can_select_movement_direction(nullptr));
  EXPECT_TRUE(cca.can_select_movement_direction(creature));

  Status s;
  s.set_value(true);

  creature->set_status(StatusIdentifiers::STATUS_ID_STUNNED, s);

  EXPECT_FALSE(cca.can_select_movement_direction(creature));
}
