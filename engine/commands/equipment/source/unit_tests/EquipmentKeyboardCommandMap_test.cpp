#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Equipment_EquipmentKeyboardCommandMap, serialization_id)
{
  EquipmentKeyboardCommandMap ekcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP, ekcm.get_class_identifier());
}

class SL_Engine_Commands_Equipment_EquipmentKeyboardCommandMapFixture : public SL_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    EquipmentKeyboardCommandMap ekcm;
};

void SL_Engine_Commands_Equipment_EquipmentKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(ekcm);
}

TEST_F(SL_Engine_Commands_Equipment_EquipmentKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  ekcm.serialize(ss);

  istringstream iss(ss.str());

  EquipmentKeyboardCommandMap ekcm2;

  ekcm2.deserialize(iss);

  EXPECT_TRUE(ekcm == ekcm2);
}
