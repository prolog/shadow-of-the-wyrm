#include "gtest/gtest.h"
#include "ItemProperties.hpp"
#include "Spellbook.hpp"

TEST(SW_World_NullInventory, serialization_id)
{
  NullInventory inv;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_NULL_INVENTORY, inv.get_class_identifier());
}

TEST(SW_World_NullInventory, saveload)
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

TEST(SW_World_NullInventory, items_are_not_persisted)
{
  NullInventory ni;
  SpellbookPtr book = std::make_shared<Spellbook>();
  book->set_id("book");

  ni.add_front(book);

  EXPECT_EQ(static_cast<uint>(0), ni.size());
  EXPECT_TRUE(ni.empty());

  ItemPtr item = ni.get_from_base_id("book");
  
  EXPECT_TRUE(item == nullptr);
}

TEST(SW_World_NullInventory, count_items)
{
  NullInventory ni;
  EXPECT_EQ(static_cast<uint>(0), ni.count_items());
}

TEST(SW_World_NullInventory, size)
{
  NullInventory ni;

  SpellbookPtr book = std::make_shared<Spellbook>();
  ni.add_front(book);

  EXPECT_EQ(static_cast<uint>(0), ni.size());
}

TEST(SW_World_NullInventory, empty)
{
  NullInventory ni;

  SpellbookPtr book = std::make_shared<Spellbook>();
  ni.add_front(book);

  EXPECT_TRUE(ni.empty());
}

TEST(SW_World_NullInventory, mark_is_useless)
{
  NullInventory ni;

  ni.mark_for_restack();

  EXPECT_FALSE(ni.get_marked_for_restack());
}

TEST(SW_World_NullInventory, get_allows_items)
{
  NullInventory ni;

  EXPECT_EQ(AllowsItemsType::DISALLOWS_ITEMS, ni.get_allows_items());
}

TEST(SW_World_NullInventory, add_items)
{
  NullInventory ni;
  ItemPtr item = std::make_shared<Spellbook>();
  ni.add_items({ item });
  EXPECT_EQ(static_cast<uint>(0), ni.count_items());
}

TEST(SW_World_NullInventory, merge_or_add)
{
  NullInventory ni;

  SpellbookPtr item = std::make_shared<Spellbook>();
  item->set_base_id("abc212");
  item->set_description_sid("ABC123");
  item->set_effect_type(EffectType::EFFECT_TYPE_BLESS);

  SpellbookPtr item2 = std::make_shared<Spellbook>();
  item2->set_base_id("abc212");
  item2->set_description_sid("ABC123");
  item2->set_effect_type(EffectType::EFFECT_TYPE_BLESS);

  SpellbookPtr item3 = std::make_shared<Spellbook>();
  item3->set_base_id("ddd333");
  item3->set_description_sid("DDD333");
  item3->set_effect_type(EffectType::EFFECT_TYPE_ETHER);

  EXPECT_FALSE(ni.merge_or_add(item3, InventoryAdditionType::INVENTORY_ADDITION_BACK));
  EXPECT_EQ(static_cast<uint>(0), ni.size());

  EXPECT_FALSE(ni.merge_or_add(item2, InventoryAdditionType::INVENTORY_ADDITION_BACK));
  EXPECT_EQ(static_cast<uint>(0), ni.size());

  EXPECT_FALSE(ni.merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK));
  EXPECT_EQ(static_cast<uint>(0), ni.size());
}

TEST(SW_World_NullInventory, merge_or_add_whole_inventory)
{
  SpellbookPtr item = std::make_shared<Spellbook>();
  item->set_base_id("abc212");
  item->set_description_sid("ABC123");
  item->set_effect_type(EffectType::EFFECT_TYPE_BLESS);

  std::shared_ptr<NullInventory> ni = std::make_shared<NullInventory>();
  ni->add(item);

  NullInventory ni2;
  ni2.merge_or_add(ni, InventoryAdditionType::INVENTORY_ADDITION_BACK);

  EXPECT_TRUE(ni->empty());
  EXPECT_TRUE(ni2.empty());
}

TEST(SW_World_NullInventory, transfer_to)
{
  SpellbookPtr item = std::make_shared<Spellbook>();
  item->set_base_id("abc212");
  item->set_description_sid("ABC123");
  item->set_effect_type(EffectType::EFFECT_TYPE_BLESS);

  std::shared_ptr<NullInventory> ni = std::make_shared<NullInventory>();
  ni->add(item);

  std::shared_ptr<NullInventory> ni2 = std::make_shared<NullInventory>();
  ni->transfer_to(ni2);

  EXPECT_TRUE(ni->empty());
  EXPECT_TRUE(ni2->empty());
}

TEST(SW_World_NullInventory, set_additional_property)
{
  NullInventory ni;
  ItemPtr item = std::make_shared<Spellbook>();
  ni.add_items({ item });
  ni.set_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDED, "1");
  EXPECT_EQ(static_cast<uint>(0), ni.count_items_with_property(ItemProperties::ITEM_PROPERTIES_BRANDED));
}

TEST(SW_World_NullInventory, count_items_without_property)
{
  NullInventory ni;
  ItemPtr item = std::make_shared<Spellbook>();
  item->set_additional_property("fdsa", "1");
  ni.add_items({ item });
  EXPECT_EQ(static_cast<uint>(0), ni.count_items_without_property("abc"));
}

TEST(SW_World_NullInventory, get_from_type)
{
  NullInventory ni;
  ItemPtr item = std::make_shared<Spellbook>();
  ni.add(item);
  vector<ItemPtr> itypes = ni.get_from_type(ItemType::ITEM_TYPE_SPELLBOOK);

  EXPECT_EQ(static_cast<uint>(0), itypes.size());
}

TEST(SW_World_NullInventory, no_drop_effect_sid)
{
  NullInventory ni;
  EXPECT_EQ("", ni.get_drop_effect_sid());
}

TEST(SW_World_NullInventory, has_item)
{
  NullInventory ni;

  ItemPtr item = std::make_shared<Spellbook>();
  item->set_base_id("book");

  ni.add(item);
  EXPECT_FALSE(ni.has_item("book"));
}

TEST(SW_World_NullInventory, get_all_from_base_id)
{
  NullInventory ni;

  ItemPtr item = std::make_shared<Spellbook>();
  item->set_base_id("book");

  ni.add(item);
  EXPECT_EQ(static_cast<uint>(0), ni.get_all_from_base_id("book").size());
}

TEST(SW_World_NullInventory, get_all_from_property)
{
  NullInventory ni;

  ItemPtr item = std::make_shared<Spellbook>();
  item->set_additional_property("fdsa", "asdf");

  ni.add(item);
  EXPECT_EQ(static_cast<uint>(0), ni.get_all_from_property("fdsa").size());
}

TEST(SW_World_NullInventory, get_all_from_property_and_required_value)
{
  NullInventory ni;

  ItemPtr item = std::make_shared<Spellbook>();
  item->set_additional_property("fdsa", "asdf");

  ni.add(item);
  EXPECT_EQ(static_cast<uint>(0), ni.get_all_from_property("fdsa", "asdf").size());
}
