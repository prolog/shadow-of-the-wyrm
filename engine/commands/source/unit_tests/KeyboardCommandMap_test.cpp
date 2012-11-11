#include "RNG.hpp"

TEST(SL_Engine_Commands_KeyboardCommandMap, serialization_id)
{
  KeyboardCommandMap kcm;

  EXPECT_EQ(CLASS_ID_KEYBOARD_COMMAND_MAP, kcm.get_class_identifier());
}

// Definitions for the test fixture
void SL_Engine_Commands_KeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(kcm);
}

void SL_Engine_Commands_KeyboardCommandMapFixture::initialize_kcm_for_unit_tests(KeyboardCommandMap& key_map)
{
  if (!key_map.command_mapping.empty())
  {
    int num_items_to_remove = RNG::range(1, key_map.command_mapping.size());

    // Remove some items at random so that we know that save/load worked correctly.
    // Otherwise, it might work just by creating a new keyboard command map.
    for (int i = 0; i < num_items_to_remove; i++)
    {
      key_map.command_mapping.erase(key_map.command_mapping.begin());
    }
  }
}

TEST_F(SL_Engine_Commands_KeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  kcm.serialize(ss);

  istringstream iss(ss.str());

  KeyboardCommandMap kcm2;

  kcm.deserialize(iss);

  EXPECT_TRUE(kcm == kcm2);
}