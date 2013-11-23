#include "gtest/gtest.h"

// Local helper function
InitialItem make_populated_initial_item(const bool populate_random);

InitialItem make_populated_initial_item(const bool populate_random)
{
  InitialItem ii;
  Dice d;

  ii.set_item_id("aaa");
  ii.set_item_quantity(d);

  if (populate_random)
  {
    vector<pair<string, Dice>> random_ids;
    random_ids.push_back(make_pair("ddd", d));

    ii.set_random_item_ids(random_ids);
  }

  map<string, pair<string, Dice>> racial_ids;
  racial_ids.insert(make_pair("elf", make_pair("elfpants", d)));
  racial_ids.insert(make_pair("dwarf", make_pair("dwarfpants", d)));
  racial_ids.insert(make_pair("cheri", make_pair("monkeypants", d)));

  ii.set_racial_item_ids(racial_ids);

  return ii;
}

TEST(SL_Engine_InitialItemSelector, empty)
{
  InitialItem ii;
  InitialItemSelector iis;
  string empty_string;
  
  EXPECT_EQ(empty_string, iis.get_item_details("dwarf", ii).first);
}

TEST(SL_Engine_InitialItemSelector, no_base_id_and_race_not_found)
{
  InitialItemSelector iis;
  InitialItem ii = make_populated_initial_item(false);
  ii.set_item_id("");
  
  EXPECT_EQ("", iis.get_item_details("nina_cow", ii).first);  
}

TEST(SL_Engine_InitialItemSelector, base_id)
{
  InitialItem ii;
  InitialItemSelector iis;

  ii.set_item_id("monkeypants");

  map<string, string> racial_ids;
  racial_ids.insert(make_pair("elf", "elfpants"));

  EXPECT_EQ("monkeypants", iis.get_item_details("dwarf", ii).first);
}

TEST(SL_Engine_InitialItemSelector, random_id)
{
  InitialItemSelector iis;
  InitialItem ii = make_populated_initial_item(true);

  EXPECT_EQ("ddd", iis.get_item_details("dwarf", ii).first);
}

TEST(SL_Engine_InitialItemSelector, racial_id)
{
  InitialItemSelector iis;
  InitialItem ii = make_populated_initial_item(false);

  EXPECT_EQ("dwarfpants", iis.get_item_details("dwarf", ii).first); 
}

