#include "gtest/gtest.h"

TEST(SW_Engine_Strings_DateTextKeys, wind_sids)
{
  std::map<std::pair<int, int>, std::string> range_and_sids = { { { 0, 1}, DateTextKeys::WIND_CALM},
                                                                { { 2, 11 }, DateTextKeys::WIND_LIGHT_BREEZE },
                                                                { { 12, 35 }, DateTextKeys::WIND_STRONG_BREEZE },
                                                                { { 36, 65 }, DateTextKeys::WIND_GALE },
                                                                { { 66, 100 }, DateTextKeys::WIND_STORM } };

  for (auto rs_pair : range_and_sids)
  {
    pair<int, int> range = rs_pair.first;
    string expected_sid = rs_pair.second;

    for (int i = range.first; i <= range.second; i++)
    {
      EXPECT_EQ(expected_sid, DateTextKeys::get_wind_sid(i));
    }
  }
}
