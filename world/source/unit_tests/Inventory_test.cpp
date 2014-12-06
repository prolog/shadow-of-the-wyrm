#include "gtest/gtest.h"
#include "Conversion.hpp"
#include "Spellbook.hpp"
#include "SmithingConstants.hpp"
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

TEST(SL_World_Inventory, has_item_with_property)
{
  Inventory inv;

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  inv.add(book);

  EXPECT_FALSE(inv.has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));

  ToolPtr tool = std::make_shared<Tool>();
  tool->set_id("ore");
  tool->set_additional_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE, Integer::to_string(MATERIAL_TYPE_IRON));

  inv.add(tool);

  EXPECT_TRUE(inv.has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));
}

TEST(SL_World_Inventory, count_items_with_property)
{
  Inventory inv;

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  inv.add(book);

  EXPECT_FALSE(inv.has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));

  ToolPtr tool = std::make_shared<Tool>();
  tool->set_id("ore");
  tool->set_additional_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE, Integer::to_string(MATERIAL_TYPE_IRON));

  inv.add(tool);

  EXPECT_EQ(1, inv.count_items_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));

  tool->set_quantity(3);

  EXPECT_EQ(3, inv.count_items_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));
}

TEST(SL_World_Inventory, count_items)
{
  Inventory inv;

  EXPECT_EQ(0, inv.count_items("book"));

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_base_id("book");
  book->set_id("book");
  book->set_quantity(4);

  inv.add(book);

  EXPECT_EQ(4, inv.count_items("book"));

  SpellbookPtr book2 = std::make_shared<Spellbook>();
  book2->set_base_id("book");
  book2->set_id("book2");
  book2->set_quantity(4);

  inv.add(book2);
  
  EXPECT_EQ(8, inv.count_items("book"));
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
