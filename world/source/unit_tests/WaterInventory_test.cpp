#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_World_WaterInventory, add)
{
  ItemPtr amulet = std::make_shared<Amulet>();
  WaterInventory wi;

  bool val = wi.add(amulet);
  EXPECT_FALSE(val);
  EXPECT_EQ(0, wi.size());

  ItemPtr fl_amulet = std::make_shared<Amulet>();
  fl_amulet->set_floats(true);
  val = wi.add(fl_amulet);

  EXPECT_TRUE(val);
  EXPECT_EQ(1, wi.size());
}

TEST(SW_World_WaterInventory, add_front)
{
  ItemPtr amulet = std::make_shared<Amulet>();
  WaterInventory wi;

  bool val = wi.add_front(amulet);
  EXPECT_FALSE(val);
  EXPECT_EQ(0, wi.size());

  ItemPtr fl_amulet = std::make_shared<Amulet>();
  fl_amulet->set_id("1");
  fl_amulet->set_floats(true);
  val = wi.add_front(fl_amulet);

  EXPECT_TRUE(val);
  EXPECT_EQ(1, wi.size());

  ItemPtr fl_amulet_2 = std::make_shared<Amulet>();
  fl_amulet_2->set_id("0");
  fl_amulet_2->set_floats(true);
  wi.add_front(fl_amulet_2);

  EXPECT_EQ(2, wi.size());

  const auto& items = wi.get_items_cref();

  EXPECT_EQ(2, items.size());
  int cnt = 0;

  for (ItemPtr i : items)
  {
    EXPECT_EQ(std::to_string(cnt++), i->get_id());
  }
}

TEST(SW_World_WaterInventory, set_items)
{
  WaterInventory wi;
  ItemPtr item = std::make_shared<Amulet>();
  item->set_floats(true);

  list<ItemPtr> items;
  item->set_id("abc123");
  items.push_back(item);
  wi.set_items(items);

  items = wi.get_items_ref();
  
  EXPECT_EQ(1, items.size());
  EXPECT_EQ("abc123", items.front()->get_id());

  items.clear();

  item = std::make_shared<Amulet>();
  item->set_id("cde321");
  item->set_floats(true);
  items.push_back(item);
  item = std::make_shared<Amulet>();
  item->set_id("321321");
  item->set_floats(true);
  items.push_back(item);

  wi.set_items(items);

  items = wi.get_items_cref();

  EXPECT_EQ(2, items.size());
  EXPECT_EQ("cde321", items.front()->get_id());
  EXPECT_EQ("321321", items.back()->get_id());
}

TEST(SW_World_WaterInventory, add_items)
{
  WaterInventory wi;
  ItemPtr item = std::make_shared<Amulet>();
  item->set_floats(true);

  list<ItemPtr> items;
  item->set_id("abc123");
  items.push_back(item);
  wi.add_items(items);

  items = wi.get_items_ref();

  EXPECT_EQ(1, items.size());
  EXPECT_EQ("abc123", items.front()->get_id());

  items.clear();

  item = std::make_shared<Amulet>();
  item->set_floats(true);
  item->set_id("cde321");
  items.push_back(item);
  item = std::make_shared<Amulet>();
  item->set_floats(true);
  item->set_id("321321");
  items.push_back(item);

  wi.add_items(items);

  items = wi.get_items_cref();

  EXPECT_EQ(3, items.size());
  EXPECT_EQ("abc123", items.front()->get_id());
  EXPECT_EQ("321321", items.back()->get_id());
}

TEST(SW_World_WaterInventory, serialization_id)
{
  WaterInventory wi;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WATER_INVENTORY, wi.get_class_identifier());
}
