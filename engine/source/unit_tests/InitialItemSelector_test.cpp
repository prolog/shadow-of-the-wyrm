#include "gtest/gtest.h"

// Local helper function
InitialItem make_populated_initial_item(const bool populate_random);

InitialItem make_populated_initial_item(const bool populate_random)
{
  InitialItem ii;

  ii.set_item_id("aaa");

  if (populate_random)
  {
    vector<string> random_ids;
    random_ids.push_back("ddd");

    ii.set_random_item_ids(random_ids);
  }

  map<string, string> racial_ids;
  racial_ids.insert(make_pair("elf", "elfpants"));
  racial_ids.insert(make_pair("dwarf", "dwarfpants"));
  racial_ids.insert(make_pair("cheri", "monkeypants"));

  ii.set_racial_item_ids(racial_ids);

  return ii;
}

TEST(SL_Engine_InitialItemSelector, base_id)
{
  InitialItem ii;
  InitialItemSelector iis;

  ii.set_item_id("monkeypants");

  map<string, string> racial_ids;
  racial_ids.insert(make_pair("elf", "elfpants"));

  EXPECT_EQ("monkeypants", iis.get_item_id("dwarf", ii));
}

TEST(SL_Engine_InitialItemSelector, random_id)
{
  InitialItemSelector iis;
  InitialItem ii = make_populated_initial_item(true);

  EXPECT_EQ("ddd", iis.get_item_id("dwarf", ii));
}

TEST(SL_Engine_InitialItemSelector, racial_id)
{
  InitialItemSelector iis;
  InitialItem ii = make_populated_initial_item(false);

  EXPECT_EQ("dwarfpants", iis.get_item_id("dwarf", ii)); 
}

