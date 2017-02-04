#include "gtest/gtest.h"

TEST(SW_World_RarityTypes, operatordecr)
{
  vector<pair<Rarity, Rarity>> val_and_decr = {{Rarity::RARITY_COMMON, Rarity::RARITY_COMMON},
                                               {Rarity::RARITY_UNCOMMON, Rarity::RARITY_COMMON},
                                               {Rarity::RARITY_RARE, Rarity::RARITY_UNCOMMON},
                                               {Rarity::RARITY_VERY_RARE, Rarity::RARITY_RARE}};

  for (const auto r_pair : val_and_decr)
  {
    Rarity expected = r_pair.second;
    Rarity actual = r_pair.first;
    actual--;

    EXPECT_EQ(expected, actual);
  }
}

