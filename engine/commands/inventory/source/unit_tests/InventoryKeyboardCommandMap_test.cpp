#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Inventory_InventoryKeyboardCommandMap, serialization_id)
{
  InventoryKeyboardCommandMap ikcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP, ikcm.get_class_identifier());
}

class SW_Engine_Commands_Inventory_InventoryKeyboardCommandMapFixture : public SW_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    InventoryKeyboardCommandMap ikcm;
};

void SW_Engine_Commands_Inventory_InventoryKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(ikcm);
}

TEST_F(SW_Engine_Commands_Inventory_InventoryKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  ikcm.serialize(ss);

  istringstream iss(ss.str());

  InventoryKeyboardCommandMap ikcm2;

  ikcm2.deserialize(iss);

  EXPECT_TRUE(ikcm == ikcm2);
}

