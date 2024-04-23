#include "gtest/gtest.h"
#include "Weapon.hpp"
#include "Armour.hpp"
#include "Amulet.hpp"

TEST(SW_World_Equipment, get_item)
{
  Equipment e;
  AmuletPtr amulet = std::make_shared<Amulet>();
  string id = "abc123";
  amulet->set_id(id);

  e.set_item(amulet, EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  ItemPtr i = e.get_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  EXPECT_EQ(id, i->get_id());

  i = e.get_item(EquipmentWornLocation::EQUIPMENT_WORN_BODY);

  EXPECT_TRUE(i == nullptr);
}

TEST(SW_World_Equipment, get_item_from_id)
{
  Equipment e;
  AmuletPtr amulet = std::make_shared<Amulet>();
  string id = "abc123";
  amulet->set_id(id);

  e.set_item(amulet, EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  ItemPtr i = e.get_item_from_id("fjdlksafdjsalkf");
  EXPECT_TRUE(i == nullptr);

  i = e.get_item_from_id(id);
  EXPECT_TRUE(i != nullptr);
}

TEST(SW_World_Equipment, remove_item)
{
  Equipment e;
  ArmourPtr a = std::make_shared<Armour>();
  string id = "fdkj4j32j4kr";
  a->set_id(id);

  e.set_item(a, EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY);

  EXPECT_TRUE(e.has_item(EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY));

  e.remove_item(EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY);

  EXPECT_FALSE(e.has_item(EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY));
}

TEST(SW_World_Equipment, can_equip_multiple_items)
{
  Equipment e;

  for (int i = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); i < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); i++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(i);

    if (ewl == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION)
    {
      EXPECT_TRUE(e.can_equip_multiple_items(ewl));
    }
    else
    {
      EXPECT_FALSE(e.can_equip_multiple_items(ewl));
    }
  }
}

TEST(SW_World_Equipment, has_item)
{
  Equipment e;

  EXPECT_FALSE(e.has_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK));

  AmuletPtr amulet = std::make_shared<Amulet>();

  e.set_item(amulet, EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  EXPECT_TRUE(e.has_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK));
}

TEST(SW_World_Equipment, is_digging_implement_equipped)
{
  Equipment e;

  EXPECT_FALSE(e.is_digging_implement_equipped());

  ItemPtr weapon = ItemPtr(new MeleeWeapon());
  e.set_item(weapon, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  EXPECT_FALSE(e.is_digging_implement_equipped());

  weapon->set_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_HARDNESS, "7");

  EXPECT_TRUE(e.is_digging_implement_equipped());
}

TEST(SW_World_Equipment, serialization_id)
{
  Equipment eq;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_EQUIPMENT, eq.get_class_identifier());
}

TEST(SW_World_Equipment, saveload)
{
  Equipment e, e2;

  ItemPtr weapon = ItemPtr(new MeleeWeapon());
  ItemPtr body_armour = ItemPtr(new Armour());
  ItemPtr amulet = ItemPtr(new Amulet());

  weapon->set_quantity(1);
  weapon->set_description_sid("test");

  amulet->set_description_sid("test2");

  body_armour->set_description_sid("test3");

  e.set_item(weapon, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
  e.set_item(body_armour, EquipmentWornLocation::EQUIPMENT_WORN_BODY);
  e.set_item(amulet, EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  ostringstream ss;

  e.serialize(ss);

  istringstream iss(ss.str());

  e2.deserialize(iss);

  EXPECT_TRUE(e == e2);
}
