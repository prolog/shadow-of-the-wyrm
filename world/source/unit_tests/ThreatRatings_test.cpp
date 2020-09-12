#include "gtest/gtest.h"

TEST(SW_World_ThreatRatings, serialization_id)
{
  ThreatRatings tr;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_THREAT_RATINGS, tr.get_class_identifier());
}

TEST(SW_World_ThreatRatings, saveload)
{
  ThreatRatings tr, tr2;

  ostringstream ss;

  tr.serialize(ss);

  istringstream iss(ss.str());

  tr2.deserialize(iss);

  EXPECT_TRUE(tr == tr2);
}

TEST(SW_World_ThreatRatings, clear)
{
  ThreatRatings tr;
  tr.add_or_update_threat("BX`12", 100);

  tr.clear();
  ThreatMap tm = tr.get_all_threats();

  EXPECT_EQ(0, tm.size());
}

TEST(SW_World_ThreatRatings, has_threat)
{
  ThreatRatings tr;
  string cr_id;
  vector<int> tvals = { 100, 133, 222 };

  for (int tval : tvals)
  {
    tr.add_or_update_threat(cr_id, tval);
    auto tdetails = tr.has_threat(cr_id);

    EXPECT_EQ(true, tdetails.first);
    EXPECT_EQ(tval, tdetails.second);
  }
}

TEST(SW_World_ThreatRatings, remove_threat)
{
  ThreatRatings tr;
  string cr_id = "ab123";
  tr.add_or_update_threat(cr_id, 100);

  EXPECT_EQ(true, tr.has_threat(cr_id).first);

  tr.remove_threat(cr_id, 100);

  EXPECT_EQ(false, tr.has_threat(cr_id).first);
}

TEST(SW_World_ThreatRatings, true_threats)
{
  ThreatRatings tr;
  vector<string> non_threats = { "nt1", "nt2", "nt3" };
  vector<string> true_threats = { "tt1", "tt2", "tt3" };

  for (int i = 0; i < 3; i++)
  {
    tr.add_or_update_threat(non_threats[i], ThreatConstants::DISLIKE_THREAT_RATING - 1);
    tr.add_or_update_threat(true_threats[i], ThreatConstants::DISLIKE_THREAT_RATING + 1);
  }

  set<string> tt_set = tr.get_true_threats_without_level();

  for (const string tti : tt_set)
  {
    EXPECT_TRUE(std::find(true_threats.begin(), true_threats.end(), tti) != true_threats.end());
  }
}
