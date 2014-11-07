#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SL_Engine_Items_ItemPropertyFilter, passes_test)
{
  ItemPropertyFilter ipf(make_pair("foo", ""));
  
  ItemPtr amulet = std::make_shared<Amulet>();

  EXPECT_FALSE(ipf.passes_filter(amulet));

  amulet->set_additional_property("foo", "17");

  EXPECT_TRUE(ipf.passes_filter(amulet));

  // Will only match items with additional property "foo" with the
  // exact value "18".
  ItemPropertyFilter ipf2(make_pair("foo", "18"));

  EXPECT_FALSE(ipf2.passes_filter(amulet));

  amulet->set_additional_property("foo", "18");

  EXPECT_TRUE(ipf2.passes_filter(amulet));
}

