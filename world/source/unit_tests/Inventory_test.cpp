#include "gtest/gtest.h"
#include "Spellbook.hpp"
#include "Tool.hpp"

TEST(SL_World_Inventory, serialization_id)
{
  Inventory inv;

  EXPECT_EQ(CLASS_ID_INVENTORY, inv.get_class_identifier());
}

TEST(SL_World_Inventory, saveload)
{
  std::shared_ptr<Inventory> inv = std::make_shared<Inventory>();
  std::shared_ptr<Inventory> sinv2 = std::make_shared<Inventory>();

  SpellbookPtr book = SpellbookPtr(new Spellbook());
  book->set_quantity(12);

  inv->add_front(book);

  ostringstream ss;

  inv->serialize(ss);

  istringstream iss(ss.str());

  sinv2->deserialize(iss);

  EXPECT_TRUE(*inv == *sinv2);
}

TEST(SL_World_Inventory, items_are_persisted)
{
  Inventory inv;
  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  ToolPtr tool = std::make_shared<Tool>();
  tool->set_id("tool");

  inv.add(book);
  inv.add(tool);

  EXPECT_FALSE(inv.empty());
  EXPECT_EQ(2, inv.size());

  ItemPtr item = inv.get_from_id("book");
  ItemPtr item2 = inv.get_from_id("tool");

  EXPECT_TRUE(item != nullptr);
  EXPECT_TRUE(item2 != nullptr);
}
