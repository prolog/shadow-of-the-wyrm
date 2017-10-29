#include "gtest/gtest.h"

class SW_Engine_Items_ItemGenerationManager : public ::testing::Test
{
  protected:
    ItemType generate_item_type_by_val(const int val)
    {
      return igm.generate_item_type_by_val(val);
    }
    
    ItemGenerationManager igm;
};

TEST_F(SW_Engine_Items_ItemGenerationManager, loot_distribution)
{
  std::map<ItemType, int> expected = {{ItemType::ITEM_TYPE_BOAT,1},
                                      {ItemType::ITEM_TYPE_CURRENCY, 2},
                                      {ItemType::ITEM_TYPE_AMULET, 2},
                                      {ItemType::ITEM_TYPE_MISC, 2},
                                      {ItemType::ITEM_TYPE_TOOL, 3},
                                      {ItemType::ITEM_TYPE_SPELLBOOK, 5},
                                      {ItemType::ITEM_TYPE_RING, 5},
                                      {ItemType::ITEM_TYPE_WAND, 6},
                                      {ItemType::ITEM_TYPE_AMMUNITION, 8},
                                      {ItemType::ITEM_TYPE_WEAPON, 10},
                                      {ItemType::ITEM_TYPE_ARMOUR, 10},
                                      {ItemType::ITEM_TYPE_POTION, 15},
                                      {ItemType::ITEM_TYPE_SCROLL, 15},
                                      {ItemType::ITEM_TYPE_FOOD, 16}};
  std::map<ItemType, int> p_cnt;

  for (int i = 1; i <= 100; i++)
  {
    ItemType itype = generate_item_type_by_val(i);

    auto p_it = p_cnt.find(itype);

    if (p_it != p_cnt.end())
    {
      p_cnt[itype]++;
    }
    else
    {
      p_cnt[itype] = 1;
    }
  }

  // Check to see if all the probabilities match what we expect.
  for (const auto& exp_pair : expected)
  {
    int actual = 0;
    auto p_it = p_cnt.find(exp_pair.first);

    if (p_it != p_cnt.end())
    {
      actual = p_it->second;
    }

    EXPECT_EQ(exp_pair.second, actual);
  }
}


