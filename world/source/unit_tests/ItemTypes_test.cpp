#include "gtest/gtest.h"

TEST(SW_World_ItemTypes, get_next)
{
  vector<std::pair<ItemStatus, ItemStatus>> cur_and_next = { {ItemStatus::ITEM_STATUS_CURSED, ItemStatus::ITEM_STATUS_UNCURSED}, 
                                                             {ItemStatus::ITEM_STATUS_UNCURSED, ItemStatus::ITEM_STATUS_BLESSED}, 
                                                             {ItemStatus::ITEM_STATUS_BLESSED, ItemStatus::ITEM_STATUS_BLESSED} };

  for (const auto& cn_pair : cur_and_next)
  {
    EXPECT_EQ(cn_pair.second, ItemStatuses::get_next(cn_pair.first));
  }
}

TEST(SW_World_ItemTypes, get_prev)
{
  vector<std::pair<ItemStatus, ItemStatus>> cur_and_prev = { {ItemStatus::ITEM_STATUS_CURSED, ItemStatus::ITEM_STATUS_CURSED},
                                                             {ItemStatus::ITEM_STATUS_UNCURSED, ItemStatus::ITEM_STATUS_CURSED},
                                                             {ItemStatus::ITEM_STATUS_BLESSED, ItemStatus::ITEM_STATUS_UNCURSED} };

  for (const auto& cp_pair : cur_and_prev)
  {
    EXPECT_EQ(cp_pair.second, ItemStatuses::get_prev(cp_pair.first));
  }
}
