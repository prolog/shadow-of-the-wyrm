#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"
#include "Spellbook.hpp"
#include "SmithingConstants.hpp"
#include "Tool.hpp"

TEST(SW_World_Inventory, serialization_id)
{
  Inventory inv;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_INVENTORY, inv.get_class_identifier());
}

TEST(SW_World_Inventory, saveload)
{
  std::shared_ptr<Inventory> inv = std::make_shared<Inventory>();
  std::shared_ptr<Inventory> sinv2 = std::make_shared<Inventory>();

  SpellbookPtr book = SpellbookPtr(new Spellbook());
  book->set_quantity(12);

  inv->add_front(book);
  inv->mark_for_restack();

  ostringstream ss;

  inv->serialize(ss);

  istringstream iss(ss.str());

  sinv2->deserialize(iss);

  EXPECT_TRUE(*inv == *sinv2);
  EXPECT_TRUE(sinv2->get_marked_for_restack());
}

TEST(SW_World_Inventory, has_item_with_property)
{
  Inventory inv;

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  inv.add(book);

  EXPECT_FALSE(inv.has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));

  ToolPtr tool = std::make_shared<Tool>();
  tool->set_id("ore");
  tool->set_additional_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE, std::to_string(static_cast<int>(MaterialType::MATERIAL_TYPE_IRON)));

  inv.add(tool);

  EXPECT_TRUE(inv.has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));
}

TEST(SW_World_Inventory, count_items_with_property)
{
  Inventory inv;

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  inv.add(book);

  EXPECT_FALSE(inv.has_item_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));

  ToolPtr tool = std::make_shared<Tool>();
  tool->set_id("ore");
  tool->set_additional_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE, std::to_string(static_cast<int>(MaterialType::MATERIAL_TYPE_IRON)));

  inv.add(tool);

  EXPECT_EQ(1, inv.count_items_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));

  tool->set_quantity(3);

  EXPECT_EQ(3, inv.count_items_with_property(SmithingConstants::SMITHING_CONSTANTS_MATERIAL_TYPE));
}

TEST(SW_World_Inventory, count_items_without_property)
{
  Inventory inv;
  string prop = "prop";

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  inv.add(book);

  EXPECT_EQ(1, inv.count_items_without_property(prop));

  book->set_additional_property(prop, "1");

  EXPECT_EQ(0, inv.count_items_without_property(prop));
}

TEST(SW_World_Inventory, count_items)
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

TEST(SW_World_Inventory, items_are_persisted)
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

TEST(SW_World_Inventory, allows_items)
{
  Inventory i;

  EXPECT_TRUE(i.get_allows_items());
}

TEST(SW_World_Inventory, add_items)
{
  Inventory i;

  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  list<ItemPtr> items = {book};
  i.set_items(items);

  EXPECT_EQ(1, i.count_items());

  ToolPtr tool = std::make_shared<Tool>();
  tool->set_id("tool");

  items = {tool};
  i.add_items(items);

  EXPECT_EQ(2, i.count_items());
}

TEST(SW_World_Inventory, set_additional_property)
{
  Inventory inv;
  ItemPtr item = std::make_shared<Spellbook>();
  ItemPtr item2 = std::make_shared<Spellbook>();
  inv.add_items({ item, item2 });
  inv.set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDED, "1");
  EXPECT_EQ(2, inv.count_items_with_property(ItemProperties::ITEM_PROPERTIES_BRANDED));
}

TEST(SW_World_Inventory, get_from_type)
{
  Inventory inv;

  ItemPtr item = std::make_shared<Spellbook>();
  ItemPtr item2 = std::make_shared<Spellbook>();
  ItemPtr item3 = std::make_shared<Amulet>();

  inv.add(item);
  inv.add(item3);
  inv.add(item2);

  vector<ItemPtr> items = inv.get_from_type(ItemType::ITEM_TYPE_SPELLBOOK);

  EXPECT_EQ(2, items.size());
}

TEST(SW_World_Inventory, no_drop_effect_sid)
{
  Inventory i;

  EXPECT_EQ("", i.get_drop_effect_sid());
}