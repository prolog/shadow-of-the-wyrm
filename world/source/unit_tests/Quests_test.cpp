#include "gtest/gtest.h"

TEST(SL_World_Quest, serialization_id)
{
  Quest q;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_QUEST, q.get_class_identifier());
}

TEST(SL_World_Quest, saveload)
{
  Quest q("a", "b", "c", "d");
  Quest q2;

  ostringstream ss;

  q.serialize(ss);

  istringstream iss(ss.str());

  q2.deserialize(iss);

  EXPECT_TRUE(q == q2);
}

TEST(SL_World_Quests, add_quest)
{
  Quests q;
  Quest q1("a", "b", "c", "d");

  q.add_new_quest("q", q1);

  EXPECT_FALSE(q.is_quest_in_progress("fdsa"));
  EXPECT_TRUE(q.is_quest_in_progress("q"));
}

TEST(SL_World_Quests, move_quest_to_completed_status)
{
  Quests q;
  Quest q1("a", "b", "c", "d");

  EXPECT_FALSE(q.is_quest_in_progress("q1"));
  q.add_new_quest("q1", q1);
  EXPECT_TRUE(q.is_quest_in_progress("q1"));
  EXPECT_FALSE(q.is_quest_completed("q1"));
  q.set_quest_completed("q1");
  EXPECT_FALSE(q.is_quest_in_progress("q1"));
  EXPECT_TRUE(q.is_quest_completed("q1"));
}

TEST(SL_World_Quests, serialization_id)
{
  Quests q;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_QUESTS, q.get_class_identifier());
}

TEST(SL_World_Quests, saveload)
{
  Quests q;
  Quests q_deser;

  Quest q1("a", "b", "c", "d");
  Quest q2("e", "f", "g", "h");
  Quest q3("i", "j", "k", "l");

  q.add_new_quest("q1", q1);
  q.add_new_quest("q2", q2);
  q.add_new_quest("q3", q3);

  q.set_quest_completed("q2");

  ostringstream ss;

  q.serialize(ss);

  istringstream iss(ss.str());

  q_deser.deserialize(iss);

  EXPECT_TRUE(q == q_deser);
}

