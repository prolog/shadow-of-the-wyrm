#include "gtest/gtest.h"

Quest get_test_quest();
Quest get_test_quest()
{
  Quest q("a", "b", {}, "c", "d", "map", "e", {});
  return q;
}

TEST(SW_World_Quest, desc_params)
{
  vector<string> params = {"a", "b", "C"};
  Quest q = get_test_quest();
  q.set_quest_description_parameter_sids(params);

  EXPECT_EQ(params, q.get_quest_description_parameter_sids());
}

TEST(SW_World_Quest, serialization_id)
{
  Quest q = get_test_quest();

  EXPECT_EQ(ClassIdentifier::CLASS_ID_QUEST, q.get_class_identifier());
}

TEST(SW_World_Quest, saveload)
{
  Quest q = get_test_quest();
  Quest q2;

  ostringstream ss;

  q.serialize(ss);

  istringstream iss(ss.str());

  q2.deserialize(iss);

  EXPECT_TRUE(q == q2);
}

TEST(SW_World_Quests, add_quest)
{
  Quests q;
  Quest q1 = get_test_quest();

  q.add_new_quest("q", q1);

  EXPECT_FALSE(q.is_quest_in_progress("fdsa"));
  EXPECT_TRUE(q.is_quest_in_progress("q"));
}

TEST(SW_World_Quests, move_quest_to_completed_status)
{
  Quests q;
  Quest q1 = get_test_quest();

  EXPECT_FALSE(q.is_quest_in_progress("q1"));
  q.add_new_quest("q1", q1);
  EXPECT_TRUE(q.is_quest_in_progress("q1"));
  EXPECT_FALSE(q.is_quest_completed("q1"));
  q.set_quest_completed("q1");
  EXPECT_FALSE(q.is_quest_in_progress("q1"));
  EXPECT_TRUE(q.is_quest_completed("q1"));
}

TEST(SW_World_Quests, serialization_id)
{
  Quests q;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_QUESTS, q.get_class_identifier());
}

TEST(SW_World_Quests, saveload)
{
  Quests q;
  Quests q_deser;

  Quest q1("a", "b", {}, "c", "d", "map", "e", {});
  Quest q2("f", "g", {}, "h", "i", "map2", "j", {});
  Quest q3("k", "l", {}, "m", "n", "map3", "o", {});

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

