#include <boost/algorithm/string/replace.hpp>
#include "DeityTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Strings for Prayer
DeityTextKeys::DeityTextKeys()
{
}

DeityTextKeys::~DeityTextKeys()
{
}

string DeityTextKeys::get_prayer_message(const string& deity_sid)
{
  string prayer_message = StringTable::get(DeityTextKeys::PRAYER_INITIAL_MESSAGE);
  boost::replace_first(prayer_message, "%s", StringTable::get(deity_sid));
  
  return prayer_message;
}

const string DeityTextKeys::PRAYER_INITIAL_MESSAGE  = "PRAYER_INITIAL_MESSAGE";
const string DeityTextKeys::PRAYER_DO_NOTHING       = "PRAYER_DO_NOTHING";
const string DeityTextKeys::PRAYER_FULL_HP          = "PRAYER_FULL_HP";
const string DeityTextKeys::PRAYER_FULL_AP          = "PRAYER_FULL_AP";
const string DeityTextKeys::PRAYER_RESTORE_STATUS   = "PRAYER_RESTORE_STATUS";
const string DeityTextKeys::DEITY_ACTION_DISPLEASED = "DEITY_ACTION_DISPLEASED"; 
