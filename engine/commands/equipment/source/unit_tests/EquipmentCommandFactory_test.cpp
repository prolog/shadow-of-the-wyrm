#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Equipment_EquipmentCommandFactory, serialization_id)
{
  EquipmentCommandFactory ecf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_EQUIPMENT_COMMAND_FACTORY, ecf.get_class_identifier());
}

