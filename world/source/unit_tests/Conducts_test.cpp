#include "gtest/gtest.h"

TEST(SW_World_Conducts, remaining_conducts)
{
  Conducts c;

  auto remaining = c.get_conducts();

  for (int i = static_cast<int>(ConductType::CONDUCT_TYPE_FOODLESS); i < static_cast<int>(ConductType::CONDUCT_SIZE); i++)
  {
    EXPECT_TRUE(remaining[i] == true);
  }

  c.break_conduct(ConductType::CONDUCT_TYPE_FOODLESS);
  c.break_conduct(ConductType::CONDUCT_TYPE_WEAPONLESS);
  c.break_conduct(ConductType::CONDUCT_TYPE_NO_GRAVEDIGGING);
  c.break_conduct(ConductType::CONDUCT_TYPE_QUESTLESS);

  remaining = c.get_conducts();

  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_CORPSELESS)] == true);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_AGNOSTIC)] == true);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_ILLITERATE)] == true);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_FOODLESS)] == false);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_WEAPONLESS)] == false);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_NO_GRAVEDIGGING)] == false);
  EXPECT_TRUE(remaining[static_cast<int>(ConductType::CONDUCT_TYPE_SILENT)] == true);
}

TEST(SW_World_Conducts, get_num_broken_conducts)
{
  Conducts c;

  EXPECT_EQ(0, c.get_num_broken_conducts());

  c.break_conduct(ConductType::CONDUCT_TYPE_AGNOSTIC);
  c.break_conduct(ConductType::CONDUCT_TYPE_QUESTLESS);

  EXPECT_EQ(2, c.get_num_broken_conducts());
}

TEST(SW_World_Conducts, serialization_id)
{
  Conducts c;
  EXPECT_EQ(ClassIdentifier::CLASS_ID_CONDUCTS, c.get_class_identifier());
}

TEST(SW_World_Conducts, saveload)
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

