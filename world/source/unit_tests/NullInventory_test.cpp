#include "gtest/gtest.h"
#include "Spellbook.hpp"

TEST(SL_World_NullInventory, serialization_id)
{
  NullInventory inv;

  EXPECT_EQ(CLASS_ID_NULL_INVENTORY, inv.get_class_identifier());
}

TEST(SL_World_NullInventory, saveload)
{
  std::shared_ptr<IInventory> inv = std::make_shared<NullInventory>();
  std::shared_ptr<IInventory> sinv2 = std::make_shared<NullInventory>();

  SpellbookPtr book = SpellbookPtr(new Spellbook());
  book->set_quantity(12);

  inv->add_front(book);

  ostringstream ss;

  inv->serialize(ss);

  istringstream iss(ss.str());

  sinv2->deserialize(iss);

  EXPECT_TRUE(*inv == *sinv2);
}

TEST(SL_World_NullInventory, items_are_not_persisted)
{
  NullInventory ni;
  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  ni.add_front(book);

  EXPECT_EQ(0, ni.size());
  EXPECT_TRUE(ni.empty());

  ItemPtr item = ni.get_from_base_id("book");
  
  EXPECT_TRUE(item == nullptr);
}
