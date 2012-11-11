#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Inventory_InventoryKeyboardCommandMap, serialization_id)
{
  InventoryKeyboardCommandMap ikcm;

  EXPECT_EQ(CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP, ikcm.get_class_identifier());
}

class SL_Engine_Commands_Inventory_InventoryKeyboardCommandMapFixture : public SL_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    InventoryKeyboardCommandMap ikcm;
};

void SL_Engine_Commands_Inventory_InventoryKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(ikcm);
}

TEST_F(SL_Engine_Commands_Inventory_InventoryKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  ikcm.serialize(ss);

  istringstream iss(ss.str());

  InventoryKeyboardCommandMap ikcm2;

  ikcm2.deserialize(iss);

  EXPECT_TRUE(ikcm == ikcm2);
}

