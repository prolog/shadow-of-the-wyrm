#include "gtest/gtest.h"
#include "Armour.hpp"

TEST(SW_Engine_Calculators_CreatureAdditionalDamageCalculator, calculate_addl_damage_bonus)
{
  CreatureAdditionalDamageCalculator cadc;
  Creature c;
  
  CreaturePtr cp = std::make_shared<Creature>(c);
  
  ArmourPtr item1 = ArmourPtr(new Armour());
  item1->set_addl_damage(3);

  ArmourPtr item2 = ArmourPtr(new Armour());
  item2->set_addl_damage(6);

  cp->get_equipment().set_item(item1, EquipmentWornLocation::EQUIPMENT_WORN_HEAD);
  cp->get_equipment().set_item(item2, EquipmentWornLocation::EQUIPMENT_WORN_FEET);

  EXPECT_EQ(9, cadc.calculate_additional_damage(cp));
}

