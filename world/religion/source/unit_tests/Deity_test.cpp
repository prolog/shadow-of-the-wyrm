#include "gtest/gtest.h"

TEST(SW_World_Religion_Deity, serialization_id)
{
  Deity d;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DEITY, d.get_class_identifier());
}

TEST(SW_World_Religion_Deity, saveload)
{
  Deity d, d2;

  d.set_id("foo");
  d.set_name_sid("test");
  d.set_description_sid("asdf");
  d.set_short_description_sid("short_sid");
  d.set_anger_message_sid("anger_sid");
  d.set_death_message_sid("death_msg");
  d.set_alignment_range(AlignmentRange::ALIGNMENT_RANGE_GOOD);

  vector<string> crowning_gifts;
  crowning_gifts.push_back("big_club");

  d.set_crowning_gifts(crowning_gifts);

  d.set_dislike("cats", true);
  
  Modifier initial(1,2,3,4,5,6,7);
  d.set_initial_modifier(initial);

  d.set_user_playable(true);

  EXPECT_FALSE(d == d2);

  ostringstream ss;
  
  d.serialize(ss);

  istringstream iss(ss.str());

  d2.deserialize(iss);

  EXPECT_TRUE(d == d2);
}
