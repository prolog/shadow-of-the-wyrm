#include <boost/algorithm/string/replace.hpp>
#include "ItemTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ItemTextKeys::ItemTextKeys()
{
}

ItemTextKeys::~ItemTextKeys()
{
}

string ItemTextKeys::get_value(const uint value)
{
  string msg = StringTable::get(ITEM_VALUE);
  boost::replace_first(msg, "%s", to_string(value));

  return msg;
}

// Public
const string ItemTextKeys::ITEM_GLOW = "ITEM_GLOW";
const string ItemTextKeys::ITEM_MULTIPLE = "ITEM_MULTIPLE";

// Protected
const string ItemTextKeys::ITEM_VALUE = "ITEM_VALUE";


