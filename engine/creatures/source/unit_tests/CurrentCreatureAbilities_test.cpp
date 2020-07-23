#include "gtest/gtest.h"

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