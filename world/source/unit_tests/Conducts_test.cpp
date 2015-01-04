#include "gtest/gtest.h"

TEST(SL_World_Conducts, remaining_conducts)
{
  Conducts c;

  auto remaining = c.get_conducts();

  for (int i = static_cast<int>(ConductType::CONDUCT_TYPE_FOODLESS); i < static_cast<int>(ConductType::CONDUCT_SIZE); i++)
  {
    EXPECT_TRUE(remaining[i] == true);
  }

  c.break_conduct(ConductType::CONDUCT_TYPE_FOODLESS);
  c.break_conduct(ConductType::CONDUCT_TYPE_WEAPONLESS);

  remaining = c.get_conducts();

  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_AGNOSTIC)] == true);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_ILLITERATE)] == true);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_FOODLESS)] == false);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_WEAPONLESS)] == false);
}

TEST(SL_World_Conducts, serialization_id)
{
  Conducts c;
  EXPECT_EQ(ClassIdentifier::CLASS_ID_CONDUCTS, c.get_class_identifier());
}

TEST(SL_World_Conducts, saveload)
{
  Conducts c;
  
  c.break_conduct(ConductType::CONDUCT_TYPE_FOODLESS);

  Conducts c2;

  ostringstream ss;
  c.serialize(ss);

  istringstream iss(ss.str());

  c2.deserialize(iss);

  EXPECT_TRUE(c == c2);
}

