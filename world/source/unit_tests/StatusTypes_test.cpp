#include "gtest/gtest.h"

TEST(SW_World_StatusTypes, is_status_identifier)
{
  vector<string> status_ids = {StatusIdentifiers::STATUS_ID_BLINDED, 
                               StatusIdentifiers::STATUS_ID_BLOODIED, 
                               StatusIdentifiers::STATUS_ID_DRUNK, 
                               StatusIdentifiers::STATUS_ID_EXPOSED, 
                               StatusIdentifiers::STATUS_ID_FLYING, 
                               StatusIdentifiers::STATUS_ID_HASTE, 
                               StatusIdentifiers::STATUS_ID_HIDE, 
                               StatusIdentifiers::STATUS_ID_INCORPOREAL, 
                               StatusIdentifiers::STATUS_ID_MUTE, 
                               StatusIdentifiers::STATUS_ID_PARALYSIS, 
                               StatusIdentifiers::STATUS_ID_POISON, 
                               StatusIdentifiers::STATUS_ID_RAGE, 
                               StatusIdentifiers::STATUS_ID_SATED, 
                               StatusIdentifiers::STATUS_ID_SLOWNESS, 
                               StatusIdentifiers::STATUS_ID_TIMEWALK, 
                               StatusIdentifiers::STATUS_ID_WATER_BREATHING };
  vector<string> not_ids = {"dsa", "aaa", "some_spell!"};

  for (const string& s : status_ids)
  {
    EXPECT_TRUE(StatusIdentifiers::is_status_identifier(s));
  }

  for (const string& s : not_ids)
  {
    EXPECT_FALSE(StatusIdentifiers::is_status_identifier(s));
  }
}
