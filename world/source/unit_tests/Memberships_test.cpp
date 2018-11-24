#include "gtest/gtest.h"

TEST(SW_World_Memberships, exclusions)
{
  Membership thief("thief", "SOME_SID", {"wizards"});
  Membership rangers("rangers", "ANOTHER_SID", {});
  Membership dwarves("dwarves", "THIRD_SID", {"elves"});

  Memberships m;

  m.add_membership("thief", thief);
  m.add_membership("rangers", rangers);
  m.add_membership("dwarves", dwarves);

  set<string> exclusions = m.get_excluded_memberships();
  auto s_it = exclusions.find("wizards");

  EXPECT_TRUE(s_it != exclusions.end());

  s_it = exclusions.find("elves");

  EXPECT_TRUE(s_it != exclusions.end());

  s_it = exclusions.find("not in set");

  EXPECT_FALSE(s_it != exclusions.end());

  Membership the_elvesssss;
  bool added = m.add_membership("elves", the_elvesssss);

  EXPECT_FALSE(added);
}

TEST(SW_World_Memberships, serialization_id)
{
  Memberships memberships;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MEMBERSHIPS, memberships.get_class_identifier());
}

TEST(SW_World_Memberships, saveload)
{
  Memberships mem;
  Memberships mem2;

  Membership m1("asdf", "fdsa", {"aasdf"});
  Membership m2("111", "222", {"fdsafdsafdsa"});

  mem.add_membership("asdf", m1);
  mem.add_membership("111", m2);

  ostringstream ss;
  mem.serialize(ss);
  
  istringstream iss(ss.str());

  mem2.deserialize(iss);

  EXPECT_TRUE(mem == mem2);
}

TEST(SW_World_Membership, serialization_id)
{
  Membership membership;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MEMBERSHIP, membership.get_class_identifier());
}

TEST(SW_World_Membership, saveload)
{
  Membership mem("fdsafdsa", "asfdasdf", {});
  Membership mem2;

  ostringstream ss;
  mem.serialize(ss);

  istringstream iss(ss.str());

  mem2.deserialize(iss);

  EXPECT_TRUE(mem == mem2);
}

