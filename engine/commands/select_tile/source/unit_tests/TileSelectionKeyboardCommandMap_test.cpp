#include "gtest/gtest.h"

TEST(SL_Engine_Commands_SelectTile_TileSelectionKeyboardCommandMap, serialization_id)
{
  TileSelectionKeyboardCommandMap tskcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP, tskcm.get_class_identifier());
}

class SL_Engine_Commands_SelectTile_TileSelectionKeyboardCommandMapFixture : public SL_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    TileSelectionKeyboardCommandMap tskcm;
};

void SL_Engine_Commands_SelectTile_TileSelectionKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(tskcm);
}

TEST_F(SL_Engine_Commands_SelectTile_TileSelectionKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  tskcm.serialize(ss);

  istringstream iss(ss.str());

  TileSelectionKeyboardCommandMap tskcm2;

  tskcm2.deserialize(iss);

  EXPECT_TRUE(tskcm == tskcm2);
}
