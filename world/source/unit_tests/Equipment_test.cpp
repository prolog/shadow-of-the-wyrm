#include "gtest/gtest.h"
#include "Weapon.hpp"
#include "Armour.hpp"
#include "Amulet.hpp"

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
